/*
 * Authors:
 *   Brian Hackett  <bhackett@stanford.edu>
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
 *
 * Copyright (c) 2005-2006,
 *   The Board of Trustees of The Leland Stanford Junior University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The names of the contributors may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Parser for specification files */

%{

open Clpautil
open Spec
open Ast 

module A = Array


let new_goal gbody = 
  { 
    sfa = cur_sfa ();
    body = gbody; 
    vars_used = VarSet.empty;
    nonlocals = VarSet.empty;
    menv = empty_menv
  }
 
(* Take the conjunction of two AST goals, simplifying the result if possible *)
let conjoin g0 g1 = new_goal (match (g0.body, g1.body) with 
        (Ag_conjunction c0, Ag_conjunction c1) -> Ag_conjunction (c0 @ c1)
      | (Ag_conjunction c0, _) -> Ag_conjunction (c0 @ [g1])
      | (_, Ag_conjunction c1) -> Ag_conjunction (g0 :: c1)
      | (_, _) -> Ag_conjunction [g0; g1])
      
let disjoin g0 g1 = new_goal (match (g0.body, g1.body) with 
        (Ag_disjunction c0, Ag_disjunction c1) -> Ag_disjunction (c0 @ c1)
      | (Ag_disjunction c0, _) -> Ag_disjunction (c0 @ [g1])
      | (_, Ag_disjunction c1) -> Ag_disjunction (g0 :: c1)
      | (_, _) -> Ag_disjunction [g0; g1])

let new_pred name args = {p_name = name; p_args = args; p_type_renaming = id;
                          p_disambiguation = dsymbol_empty}

let term2pred term =
  match term with
    | At_call p -> p
    | _ -> parse_error "Term is not a predicate"

let term2goal term =
  let p = term2pred term in
    match p.p_name with
      | "\\=" -> new_goal (Ag_negation (new_goal (Ag_find 
                    {s_session = None; s_pred = {p with p_name = "equal"}})))
      | "=" -> new_goal (Ag_find 
                    {s_session = None; s_pred = {p with p_name = "equal"}})
      | _ -> new_goal (Ag_find {s_session = None; s_pred = p})

let rec list2term tailo head =
  match head with
    | [] -> (match tailo with 
        | Some tail -> tail 
        | None -> At_sum ("nil", [||])
      )
    | x::xs -> At_sum ("cons", [|x; list2term tailo xs|])

%}

%token EOF
%token QUERY COLON EQUAL NOTEQUAL BNFDEF VBAR PERIOD ARROW SEMICOLON COMMA
%token QUESTION PLUS TURNSTILE TILDE
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token IMPORT USING PREDICATE SESSION ANALYZE TYPE OPERATOR IN OUT
%token ORDER CONTAINING SUCCEEDS ZERO ONCE MANY
%token ALL SOME IMPLIES IFF ASSERT VEE
%token AMPAMP BARBAR BANG LT LE GT GE EQEQ BANGEQ MINUS TIMES DIVIDE CARET
%token <Big_int.big_int> INT
%token <float> FLOAT
%token <string> STRING SYMBOL HSYMBOL DSYMBOL VAR ANYVAR BACKTICKOP

%right SEMICOLON
%right COMMA
%nonassoc SOME ALL
%right IFF IMPLIES
%right TILDE
%nonassoc EQUAL NOTEQUAL
%left AMPAMP BARBAR
%right BANG
%nonassoc EQEQ BANGEQ LT LE GT GE
%left CARET
%left BACKTICKOP
%left PLUS MINUS 
%left TIMES DIVIDE
%nonassoc ARROW
%nonassoc RPAREN

%start sentences
%type <Ast.ast_rule list> sentences

%%

sentences   :  EOF                 { [] }
            |  rule sentences      { $1::$2 }
            |  import sentences    { $1 @ $2 }
            |  define sentences    { $2 }
            |  analyze sentences   { $2 }
            |  using sentences     { $2 }

import      :  IMPORT STRING PERIOD
               {
                 match cur_sfa () with
                   | Sfa_file (curfile,_) ->
                       !parse_file $2 [Filename.dirname curfile]
                   | _ -> failwith "Invalid SFA"
               }

define      :  PREDICATE mtpred succeeds PERIOD
               {
                 let (name,mtargs) = $2 in
                 let targs = A.map thd3 mtargs in  
                 let mode = A.map fst3 mtargs in
                 ignore (add_predicate (cur_sfa()) Pk_regular name targs 
                            [(mode,$3)])

               }
            |  PREDICATE mtpred ORDER orderlist succeeds PERIOD
               {
                 let (name,mtargs) = $2 in
                 let targs = A.map thd3 mtargs in  
                 let mode = A.map fst3 mtargs in
                 let predda = add_predicate (cur_sfa()) Pk_regular name targs 
                     [(mode,$5)] in
                 let var_ind x =
                   try find_num (fun i -> snd3 mtargs.(i) = Some x)
                         0 (A.length mtargs)
                   with Not_found ->
                     parse_error ("Missing variable name: " ^ x) in
                 List.iter (fun (xsrc,xtgt) ->
                   add_order predda (var_ind xsrc,var_ind xtgt)) $4
               }
            |  SESSION tpred PERIOD
               {
                 add_session (cur_sfa()) ($2,None)
               }
            |  SESSION tpred CONTAINING LBRACKET containing RBRACKET PERIOD
               {
                 add_session (cur_sfa()) ($2,Some $5)
               }
            |  TYPE typhead PERIOD   { () }
            |  TYPE sumtype PERIOD   { add_sum_values (cur_sfa ()) $2 }
            |  TYPE aliastype PERIOD { add_alias_type (cur_sfa ()) $2 }
            |  OPERATOR SYMBOL EQUAL predsym PERIOD 
               {add_operator (cur_sfa ()) $2 $4}

orderlist   :  LBRACKET VAR COMMA VAR RBRACKET  { [$2,$4] }
            |  LBRACKET VAR COMMA VAR RBRACKET orderlist  { ($2,$4)::$6 }

succeeds    :  /* EMPTY */                          { [] }
            |  SUCCEEDS LBRACKET succlist RBRACKET  { $3 }

succlist    :  succ                 { [$1] }
            |  succ COMMA succlist  { $1::$3 }

succ        :  ZERO  { Sk_zero }
            |  ONCE  { Sk_once }
            |  MANY  { Sk_many }

containing  :  SYMBOL                   { [$1]   }
            |  SYMBOL COMMA containing  { $1::$3 }

rule        :  rule_body { {r_body = fst $1; rl_sfa = snd $1; 
                            r_type_vmap = type_vmap_empty} } 

rule_body   :  goal PERIOD                  { (Ar_flat $1, $1.sfa) }
            |  SYMBOL COLON sfa_spred TURNSTILE goal PERIOD
                { (Ar_horn_clause (Some $1, fst $3, $5), snd $3) }
            |  SYMBOL COLON sfa_spred TURNSTILE PERIOD
                { (Ar_horn_clause (Some $1, fst $3, 
                                  new_goal (Ag_conjunction [])), snd $3) }
            |  SYMBOL COLON ASSERT goal PERIOD
                { (Ar_assertion (Some $1, $4), $4.sfa) }
            |  sfa_spred TURNSTILE goal PERIOD  
                { (Ar_horn_clause (None, fst $1, $3), snd $1) }
            |  sfa_spred TURNSTILE PERIOD  
                { (Ar_horn_clause (None, fst $1, new_goal (Ag_conjunction [])),
                  snd $1)}
            |  ASSERT goal PERIOD
                { (Ar_assertion (None, $2), $2.sfa) }
            |  QUERY pred PERIOD    { (Ar_query (term2pred $2), cur_sfa ()) }

analyze     :  ANALYZE term PERIOD  { add_analyze (term2pred $2) }

using       :  USING SYMBOL PERIOD  { add_package $2 }

spred       :  term { {s_session = None; s_pred = term2pred $1} }
            |  pred ARROW pred
                { {s_session = Some (term2pred $1); s_pred = term2pred $3} }

sfa_spred   :  spred { ($1,cur_sfa()) }

goal        : term                      { term2goal $1 } %prec COMMA
            | pred ARROW pred           { new_goal (Ag_find
                {s_session = Some (term2pred $1); s_pred = term2pred $3})}
            | PLUS spred                { new_goal (Ag_add $2) }
            | goal COMMA goal           { conjoin $1 $3 }
            | goal SEMICOLON goal       { disjoin $1 $3 }
            | goal IMPLIES goal         { new_goal (Ag_implies ($1, $3)) }
            | LPAREN goal RPAREN        { $2 }  
            | TILDE goal                { new_goal (Ag_negation $2) }
            | QUESTION pred             { new_goal (Ag_wait (term2pred $2)) }
            | VEE goal COLON pred   
                { new_goal (Ag_collection ($2, term2pred $4)) }
            | ALL  varlist goal         { new_goal (Ag_all  ($2, $3)) }
            | SOME varlist goal         { new_goal (Ag_some ($2, $3)) } 


varlist      : LBRACKET varlist_body RBRACKET   { $2 }
             | LBRACKET RBRACKET                { [] }
varlist_body : VAR                              { [$1] }
             | VAR COMMA varlist_body           { $1::$3 }

predsym  :     SYMBOL   { $1 }
            |  HSYMBOL  { $1 }
            |  DSYMBOL  { $1 }

pred        :  predsym LPAREN RPAREN            { At_call (new_pred $1 [||])}
            |  predsym LPAREN termlist RPAREN   
                { At_call (new_pred $1 (A.of_list $3))}

tpred       :  predsym LPAREN RPAREN            { ($1,[||]) }
            |  predsym LPAREN targlist RPAREN   
                { ($1,A.of_list (List.map snd $3)) }
mtpred      :  predsym LPAREN RPAREN            { ($1,[||]) }
            |  predsym LPAREN mtarglist RPAREN  { ($1,A.of_list $3) }

termlist    :  term                   { [$1] }
            |  term COMMA termlist    { $1::$3 }
targlist    :  targ                   { [$1] }
            |  targ COMMA targlist    { $1::$3 }
mtarglist   :  mtarg                  { [$1] }
            |  mtarg COMMA mtarglist  { $1::$3 }

 
term        :  ANYVAR                              { At_anyvar $1 }
            |  VAR                                 { At_var $1 }
            |  STRING                              { At_string $1 }
            |  INT                                 { At_int $1 }
            |  FLOAT                               { At_float $1 }
            |  SYMBOL                              { At_sum ($1,[||]) }
            |  SYMBOL LBRACE termlist RBRACE       { At_sum ($1,A.of_list $3) }
            |  pred                                { $1 }
            |  LBRACKET RBRACKET                   { list2term None [] }
            |  LBRACKET termlist RBRACKET            { list2term None $2 }
            |  LBRACKET termlist VBAR term RBRACKET  { list2term (Some $4) $2 }
            |  LPAREN term RPAREN   { $2 } 
            |  term EQUAL  term     { At_call (new_pred "="  [|$1;$3|]) }
            |  term NOTEQUAL term   { At_call (new_pred "\\=" [|$1;$3|]) }
            |  term PLUS   term     { At_call (new_pred "+"  [|$1;$3|]) }
            |  term MINUS  term     { At_call (new_pred "-"  [|$1;$3|]) }
            |  term TIMES  term     { At_call (new_pred "*"  [|$1;$3|]) }
            |  term DIVIDE term     { At_call (new_pred "/"  [|$1;$3|]) }
            |  term AMPAMP term     { At_call (new_pred "&&" [|$1;$3|]) }
            |  term BARBAR term     { At_call (new_pred "||" [|$1;$3|]) }
            |  BANG term            { At_call (new_pred "!"  [|$2|]) }
            |  MINUS term           { At_call (new_pred "uminus" [|$2|]) }
                %prec TIMES
            |  term GT term         { At_call (new_pred ">"  [|$1;$3|]) }
            |  term GE term         { At_call (new_pred ">=" [|$1;$3|]) }
            |  term LT term         { At_call (new_pred "<"  [|$1;$3|]) }
            |  term LE term         { At_call (new_pred "<=" [|$1;$3|]) }
            |  term EQEQ term       { At_call (new_pred "==" [|$1;$3|]) }
            |  term BANGEQ term     { At_call (new_pred "!=" [|$1;$3|]) }
            |  term CARET term      { At_call (new_pred "^"  [|$1;$3|]) }
            |  term BACKTICKOP term { At_call (new_pred $2   [|$1;$3|]) }

targ        :  typ            { check_type $1; (None,$1) }
            |  VAR COLON typ  { check_type $3; (Some $1,$3) }
            |  VAR            { (None,vt_var $1) }
            |  VAR COLON VAR  { (Some $1,vt_var $3) }
typhead     :  typ            { add_type (cur_sfa ()) $1; $1 }
typ         :  SYMBOL         { make_type $1 [||] }
            |  SYMBOL polytyp { make_type $1 $2 }
polytyp     :  LBRACKET targlist RBRACKET  { A.of_list (List.map snd $2) }

mtarg       :  mode targ   { ($1,fst $2,snd $2) }
mode        :  /* EMPTY */ { false }
            |  OUT         { false }
            |  IN          { true }

ttuple      :  LBRACE targlist RBRACE  { A.of_list (List.map snd $2) }

aliastype   :  typhead EQUAL typ       { check_type $3; ($1,$3) }
sumtype     :  typhead BNFDEF sumlist  { ($1,$3) }

sumlist     :  sumval               { [($1,cur_sfa ())] }
            |  sumval VBAR sumlist  { ($1,cur_sfa ())::$3 }

sumval      :  SYMBOL         { ($1,[||]) }
            |  SYMBOL ttuple  { ($1,$2) }

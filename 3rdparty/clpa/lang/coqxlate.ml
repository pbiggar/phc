(*
 * coqxlate.ml 
 * 
 * Translation of CLPA programs to Coq source code.
 *
 * Authors:
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
 *)


open Clpautil
open Flags
open Spec
open Specio
open Ast

module A = Array
module H = Hashtbl
module PQ = Prioqueue
module S = String
module IO = Streamio
module V = Vector
module U = Unix
module E = Libevent

(* CLP parsing *)

(* Slice AST sentences into sets of rules and assertions *)
let slice_ast sentences =
  let (hcs, ass) = List.fold_left (fun (hcs, ass) s -> 
    match s.r_body with
      | Ar_flat g ->
	  rule_error g.sfa "Non-horn clause rules cannot be converted to Coq"
      | Ar_query (_,_) ->  (hcs, ass)
      | Ar_horn_clause (_,_,_,_) -> (s::hcs, ass)
      | Ar_assertion (_,_) -> (hcs, s::ass)
  ) ([], []) sentences in
  (* We reverse the lists to preserve the order of the assertions. *)
  (List.rev hcs, List.rev ass)

(* Grouping of types and clauses into SCCs. Coq requires that we state 
 * definitions before uses, so we need to topologically sort the type and
 * clause lists *)
module Pg = Graph.Make(OrderedString)

(* For each predicate name, the list of rules that can be used to produce it *)
let predicate_constructors : (string, ast_rule list) H.t = H.create 100

(* For each predicate P, on which other predicates does the definition of P
 * depend *)
let rule_depgraph : Pg.t = Pg.create ()

(* For each type T, on which other types does the definition of T depend? *)
let type_depgraph : Pg.t = Pg.create ()


(* Add a rule to the the set of rules that define a predicate, and
 * compute a dependencies between that predicate and the predicates
 * appearing in the rule body *)
let compute_rule_deps (r:ast_rule) : unit = 
  let rec add_goal_deps (hp:Pg.n) (g:ast_goal) : unit =
    match g.body with
      | Ag_conjunction gs -> List.iter (add_goal_deps hp) gs
      | Ag_disjunction gs -> List.iter (add_goal_deps hp) gs
      | Ag_find sp -> 
          let predname = sp.s_pred.p_name in
            if sp.s_session = None && 
              not (H.mem find_handlers predname) then
              ignore (Pg.mk_edge rule_depgraph hp 
			 (Pg.mk_node rule_depgraph predname))
      | Ag_add _ ->
          rule_error g.sfa "Rules with add goals cannot be converted to Coq"
      | Ag_wait _ ->
          rule_error g.sfa "Rules with wait goals cannot be converted to Coq"
      | Ag_negation sg -> add_goal_deps hp sg
      | Ag_implies (g1, g2) -> add_goal_deps hp g1; add_goal_deps hp g2
      | Ag_some (_, g) -> add_goal_deps hp g
      | Ag_all (_, g) -> add_goal_deps hp g
      | Ag_collection (_,_) -> failwith "Collection predicates not yet supported"
  in
    match r.r_body with 
      | Ar_horn_clause (nameo, head, _, body) ->
	  if head.s_session <> None then 
            failwith "Predicates added to sessions not yet supported";
	    (* Add rule to the constructor list *)
          let cs = try H.find predicate_constructors head.s_pred.p_name 
	           with Not_found -> [] in
          H.replace predicate_constructors head.s_pred.p_name (r::cs);
          add_goal_deps (Pg.mk_node rule_depgraph head.s_pred.p_name) body
      | _ -> unreachable ()

module NameSet = Set.Make(OrderedString)

(* For each type definition, compute the dependencies of its definition *)
let type_is_builtin typ =
    let kind = H.find types typ in
    match (typ, kind) with 
    | (_, T_abstract) -> true
    | ("list", _) -> true
    | ("bool", _) -> true
    | ("maybe", _) -> true
    | ("t_pair", _) -> true
    | _ -> false

let rec type_find_types_used (t:t_val_type) : NameSet.t =
    try let (name, args) = break_type t in
        let ts0 = if type_is_builtin name then NameSet.empty else
            NameSet.singleton name in
        List.fold_left (fun vs a -> NameSet.union vs (type_find_types_used a))
            ts0 (A.to_list args)
    with Unexpected _ -> NameSet.empty

let predtype_find_types_used (pt:t_pred_type) : NameSet.t =
    let (_, args) = pt in
    List.fold_left (fun ts a -> NameSet.union ts (type_find_types_used a))
        NameSet.empty (A.to_list args)

let compute_fsym_deps (tn:Pg.n) (fsym:string) =
    let (fargstype, _) = H.find sumvalues fsym in
    let tdeps = predtype_find_types_used fargstype in
    NameSet.iter (fun t -> ignore (Pg.mk_edge type_depgraph tn 
        (Pg.mk_node type_depgraph t))) tdeps

let compute_type_def_deps (typ: string) (def:t_type_def) =
    if not (type_is_builtin typ) then
    let tnode = Pg.mk_node type_depgraph typ in
    match def with 
    | T_alias atyp ->
        let tdeps = type_find_types_used atyp in
        NameSet.iter (fun t -> ignore (Pg.mk_edge type_depgraph tnode
            (Pg.mk_node type_depgraph t))) tdeps
    | T_sumtype fsyms ->
        List.iter (compute_fsym_deps tnode) fsyms
    | T_abstract -> ()

let compute_type_deps () =
    H.iter compute_type_def_deps types


open Pp
open Pputil

(* Indent value *)
let shiftwidth = 2

(* Pretty print a type constructor, renaming as necessary *)
let ppTypeConstructor tc = match tc with 
  | "maybe" -> text "option"
  | "int" -> text "Z"
  | "float" -> text "Q"
  | _ -> text tc

(* Pretty print a function symbol name, renaming as necessary *)
let ppFSym fs = match fs with
  | "yes" -> text "Some"
  | "no" -> text "None"
  | _ -> text fs

(* Pretty print the name of a predicate, apply any necessary renamings *)
let ppPredicateName name =
    match name with 
    | "list_nodup" -> text "NoDup"
    | _ -> text name

(* Pretty print a type *)
let rec ppType needbrackets typ = 
  try
    let (tc,targs) = break_type typ in
    let tcdoc = ppTypeConstructor tc in
      if A.length targs = 0 then tcdoc
      else
        let tstr = tcdoc ^^ break ^^
          ppListSep (List.map (ppType true) (Array.to_list targs)) 
            (text "," ^^ break) in
        agrp (if needbrackets then text "(" ^^ tstr ^^ text ")" else tstr)
  with Unexpected _ ->
    let var = rev_vt_var typ in
    text var

(* Print a type in a mangled form suitable for use as part of an identifier *)
let rec ppTypeFlat typ =
  try
    let (tc,targs) = break_type typ in
    let tcdoc = ppTypeConstructor tc in
      if A.length targs = 0 then tcdoc
      else
        tcdoc ^^ text "_" ^^
          ppListSep (List.map (ppType true) (Array.to_list targs)) 
            (text "_")
  with Unexpected _ ->
    let var = rev_vt_var typ in
    text var

(* Pretty print a predicate type *)
let ppPredicateType pred result =
  let psym = H.find symbols pred in
  if A.length psym.s_args = 0 then
    result
  else
    fgrp (
        ppListSep (List.map (ppType false) (Array.to_list psym.s_args))
            (text " ->" ^^ break) ^^
        text " ->" ^^ break ^^ result
    )

(* Pretty print a variable name, replacing the leading underscore of don't care
 * variables if relevant *)
let ppVar v = 
    text (
        if v.[0] = '_' then 
            "v" ^ (String.sub v 1 ((String.length v) - 1)) 
        else 
            v
    )

(* Pretty print a term *)
let rec ppTerm t =
    match t with 
      | At_anyvar name 
      | At_var name -> ppVar name
      | At_string s -> text ("\"" ^ s ^ "\"")
      | At_int i -> text (Big_int.string_of_big_int i)
      | At_float f -> text (string_of_float f)
      | At_sum (name, args) ->
          let xargs = List.map ppTerm (A.to_list args) in
            if xargs = [] then ppFSym name
            else 
              agrp (
                text "(" ^^
                  ppFSym name ^^ break ^^
                  ppListSep xargs break ^^
                  text ")"
              )
      | At_call (_, _) -> failwith "At_call ppTerm unimplemented"

(* Pretty print a predicate *)
let ppPredicate tvm p =
    let args = p.p_args in
    match p.p_name with 
    | "equal" -> agrp (ppTerm args.(0) ^^ text " =" ^^ break ^^
                       ppTerm args.(1))
    | "lessthan" -> 
	let lt_stvar = (H.find symbols "lessthan").s_args.(0) in
        let lt_type = vmap_type tvm (p.p_type_renaming lt_stvar) in
	  
	  agrp (ppTypeFlat lt_type ^^ text "_lt " ^^ ppTerm args.(0) 
		 ^^ break ^^ ppTerm args.(1))
    | "list_mem" -> agrp (text "In" ^^ break ^^ ppTerm args.(1) ^^ break ^^
                          ppTerm args.(0))
    | "list_append" -> agrp (ppTerm args.(0) ^^ break ^^ text "++" ^^ break ^^
                          ppTerm args.(1) ^^ break ^^ text "=" ^^ break ^^
                          ppTerm args.(2))
    | "int_mul" -> agrp(text "Zmult" ^^ break ^^ ppTerm args.(0) ^^ break ^^
			ppTerm args.(1) ^^ text " =" ^^ break ^^
			ppTerm args.(2))
    | _ ->
        if A.length args = 0 then text p.p_name 
        else
            agrp (
                ppPredicateName p.p_name ^^ break ^^
                ppListSep (List.map ppTerm (Array.to_list args)) break
            )

(* Pretty print the definition of a function symbol *)
let ppFSymDef (fsym:string) : doc =
    let ((_, argtyps), rtyp) = H.find sumvalues fsym in
    let argtypl = A.to_list argtyps in
    fgrp (nest shiftwidth (
        text "| " ^^ text fsym ^^ text ":" ^^ break ^^
        (if argtypl = [] then empty else 
            ppListSep (List.map (ppType false) (A.to_list argtyps)) 
            (break ^^ text "-> ") ^^
            break ^^ text "-> ") ^^ 
        (ppType false rtyp)
    ))
    

(* Pretty print the definition of a type *)
let ppTypeDef (typ:string) : doc =
    let def = H.find types typ in
    hgrp (nest shiftwidth (
        match def with
        | T_alias ntyp -> 
            text "Definition " ^^ text typ ^^ text ": Set" ^^ break ^^ 
            fgrp (text ":=" ^^ break ^^ ppType false ntyp)
        | T_sumtype fsyms -> 
            text "Inductive " ^^ text typ ^^ text ": Set" ^^ break ^^ 
            vgrp (text ":=" ^^ break ^^ 
                ppListSep (List.map ppFSymDef fsyms) break)
        | _ -> unreachable ()
    ))

(* Pretty print axioms expressing that each type has a total order defined
 * by its structure *)
let ppTypeOrderDef (typ:string) : doc =
   text "Parameter " ^^ text typ ^^ text "_lt : " ^^ text typ ^^ text " -> " ^^
   text typ ^^ text " -> Prop." ^^ break ^^
   text "Axiom " ^^ text typ ^^ text "_total_order : forall e1 e2 : " ^^ 
   text typ ^^
   text ", {" ^^ text typ ^^ text "_lt e1 e2} + {e1 = e2} + {" ^^ text typ ^^
   text "_lt e2 e1}."

(* Pretty print code to existentially quantify a set of variables *)
let ppExistsVars vs =   
    if vs = [] then empty else 
    fgrp (nest shiftwidth (
        ppListSep 
            (List.map (fun v -> text "exists " ^^ ppVar v ^^ text ",") vs)
            break ^^
        break
    ))

(* Pretty print code to universally quantify a set of variables *)
let ppUnivVars vs gdoc =
    if vs = [] then gdoc else 
    fgrp (nest shiftwidth (
        text "forall" ^^ break ^^
        ppListSep (List.map ppVar vs) break ^^
        text "," ^^ break ^^ gdoc
    ))
        
(* Pretty print a goal *) 
let rec ppGoal tvm toplevel g = 
    match g.body with 
    | Ag_conjunction cs -> 
        let (xcs, vars) = map_foldl (fun c vars ->
            let (c', cvars) = ppGoal tvm false c in
            (c', VarSet.union vars cvars)
          ) cs VarSet.empty in
        let xg = if toplevel then
            agrp (ppListSep xcs (break ^^ text  "-> ")) 
          else
            nest shiftwidth (agrp (ppListSep xcs (break ^^ text "/\\ " ))) in
        (xg, vars)
    | Ag_disjunction ds -> 
        let (xds, vars) = map_foldl (fun d vars ->
            let (d', dvars) = ppGoal tvm false d in
            (d', VarSet.union vars dvars)
          ) ds VarSet.empty in
        let xg = nest shiftwidth 
            (agrp (ppListSep xds (text " \\/ " ^^ break))) in
        (xg, vars)
    | Ag_negation ng ->
        (* Existentially quantifiers cannot be lifted across negation, so
         * introduce existential quantifiers for any non-local variables here *)
        let (nstr, nvars) = ppGoal tvm false ng in
        let quants = VarSet.diff nvars g.nonlocals in
        (text "not (" ^^ ppExistsVars (VarSet.elements quants) ^^ nstr ^^ 
         text ")", g.nonlocals)
    | Ag_implies (g1, g2) ->
        let (g1str, vars1) = ppGoal tvm false g1 in
        let (g2str, vars2) = ppGoal tvm false g2 in
        let eq1 = VarSet.diff vars1 g1.nonlocals in
        let eq2 = VarSet.diff vars2 g2.nonlocals in
        let implvars = VarSet.diff (VarSet.union vars1 vars2) 
            (VarSet.union eq1 eq2) in
        (nest shiftwidth (agrp (
            text "(" ^^ 
            ppUnivVars (VarSet.elements (VarSet.diff implvars g.nonlocals)) (
                ppExistsVars (VarSet.elements eq1) ^^ g1str ^^ break ^^
                text "-> " ^^ 
                ppExistsVars (VarSet.elements eq2) ^^ g2str) ^^ text ")"
        )),
        VarSet.inter implvars g.nonlocals)
         (*
  | Ag_iff (g1, g2) ->
      let (vars1, g1str) = ppGoal false g1 in
      let (vars2, g2str) = ppGoal false g2 in
      (VarSet.union vars1 vars2, "(" ^ g1str ^ " <-> " ^ g2str ^ ")")
  | Ag_some (vs, g) ->      
      let (vars, gstr) = ppGoal false g in
      (VarSet.diff vars vs, "(" ^ (sep_string_of_list "" 
        (fun v -> "exists " ^ v ^ ", ") (VarSet.elements vs)) ^ gstr ^ ")")
  *)
    | Ag_some (vs, qg) ->      
        let (qstr, qvars) = ppGoal tvm false qg in
        (
            text "(" ^^ ppExistsVars vs ^^ 
            ppExistsVars (VarSet.elements (VarSet.diff 
                (VarSet.diff qvars g.nonlocals) (varset_of_list vs))) ^^ 
            qstr ^^ 
            text ")",
            g.nonlocals
        )
    | Ag_all (vs, qg) ->      
        (* Existentially quantifiers cannot be lifted across universal
         * quantifiers, so introduce existential quantifiers for any 
         * non-local variables here *)
        let (qstr, qvars) = ppGoal tvm false qg in
        let quants = VarSet.elements (VarSet.diff qvars 
            (VarSet.union (varset_of_list vs) g.nonlocals)) in
        (
            text "(" ^^
            ppUnivVars vs (ppExistsVars quants ^^ qstr) ^^
            text ")",
            g.nonlocals
        )
    | Ag_find sp ->
        if sp.s_session <> None then failwith "Unimplemented" else
        (ppPredicate tvm sp.s_pred, g.vars_used)
    | _ -> (text "unimpl", VarSet.empty)

(* Pretty print a rule *)
let ppRule pred n r = 
    match r.r_body with 
    | Ar_horn_clause (nameo, head, _, body) ->
        let name = match nameo with 
            | Some name -> name 
            | None -> pred ^ (string_of_int n) in
        let (bodys, bodyvars) = ppGoal r.r_type_vmap true body in
        (* Handle the common case of a rule with an empty body specially *)
        let bdoc = match body.body with
            | Ag_conjunction [] -> empty
            | _ -> bodys ^^ break ^^ text "-> " in
        let headvars = spredicate_vars_used head in
        let vars = VarSet.union headvars bodyvars in
        let heads = ppPredicate r.r_type_vmap head.s_pred in
    (*      if bodys = "" then " " else "\n      " ^ bodys ^ "\n      -> ") ^^*)
            fgrp (nest shiftwidth (
                text "| " ^^ text name ^^ text ":" ^^ break ^^
                ppUnivVars (VarSet.elements vars) (bdoc ^^ heads)
            ))
    | _ -> unreachable ()

(* Can a given predicate be implicitly defined in the current session? *)
let predicateIsImplicit pred =
    SymbolSet.mem pred (H.find sessions !analysis_session)

let ppImplicitRule pred =
    let sym = H.find symbols pred in
    let nargs = A.length sym.s_args in
    let vars = fold_num_down (fun n a -> ("v" ^ (string_of_int n))::a) 
                    [] nargs 0 in
    nest shiftwidth (fgrp (
        text "| " ^^ text pred ^^ text "_implicit: forall " ^^
        ppListSep (List.map text vars) break ^^
        text ", In (" ^^ text !analysis_session ^^ text "_" ^^ text pred ^^
        break ^^
        ppListSep (List.map text vars) break ^^ text ") implicit_session" ^^ 
        break ^^ text "-> " ^^
        text pred ^^ break ^^
        ppListSep (List.map text vars) break 
    ))

(* Pretty print a predicate definition *)
let ppPredicateDef pred =
    let cs = try List.rev (H.find predicate_constructors pred) 
             with Not_found -> [] in
    let ss = if predicateIsImplicit pred then [ppImplicitRule pred] else [] in
    let ss' = List.rev (snd (List.fold_left (fun (n,rs) c ->
        (n+1, (ppRule pred n c)::rs)) (1, ss) cs)) in
    nest shiftwidth (
        text pred ^^ 
        text ": " ^^ 
        (ppPredicateType pred (text "Prop")) ^^ 
        text " :=" ^^ break ^^
        vgrp (ppListSep ss' break)
    )

(* Pretty print a type representing the types of predicates that can be
 * present in a given session *)
let ppSessionPredicate session pred =
    let typename = text (session ^ "_" ^ pred) in
    fgrp (nest shiftwidth (
      text "| " ^^ typename ^^ text ":" ^^ break ^^
      ppPredicateType pred (text session ^^ text "_predicate")
    ))
      
(* Translate a CLP file to Coq source *)
let xlate_program program =
  let sentences = Frontend.check_ast (Frontend.parse_clp program) in

  IO.printf "(* Coq translation of %s *)\n" program;
  IO.printf "Require Import builtins.\n\n";

  (* Compute a type dependency graph and output the rules SCC by SCC in
   * a topologically sorted order *)
  compute_type_deps ();

  let typedepscc = Pg.compute_scc type_depgraph in
  let typedepsccmems = H.create 10 in
  Pg.iter_scc type_depgraph typedepscc (H.add typedepsccmems);
  let typedeptpo = Pg.topsort type_depgraph typedepscc in
  List.iter (fun sccid -> try
    let mems = H.find typedepsccmems sccid in
    IO.printf "%s\n" (ppToString 72 (
        ppListSep (List.map ppTypeDef mems) (break ^^ text "with ") ^^
        text "."
    ));
    IO.printf "%s\n\n" (ppToString 72 (
        ppListSep (List.map ppTypeOrderDef mems) break
    ))
  with Not_found -> ()) (List.rev typedeptpo);

  (* Sessions. For each session we define a type representing the possible
   * predicate values that may inhabit the session, and we represent the 
   * session as a list of such predicates *)
  H.iter (fun session predset -> IO.printf "%s\n\n" (ppToString 72 (
    nest shiftwidth (vgrp (
        text "Inductive " ^^ text session ^^ text "_predicate: Set :=" ^^
        break ^^ 
        ppListSep (List.map (ppSessionPredicate session) 
                (SymbolSet.elements predset)) break ^^
        text "."
    )) ^^ break ^^ break ^^
    fgrp (text "Definition " ^^ text session ^^ 
    text "_predicates : Set := list" ^^ break ^^
    text session ^^ text "_predicate." ) ^^ break
  ))) sessions;

  (* We also construct a type that is a discriminated union of all possible
   * types of session, and represent the input session data as a list of such
   * session objects *)
  let slist = H.fold (fun s _ acc -> s::acc) sessions [] in
  IO.printf "%s\n\n" (ppToString 72 (
    nest shiftwidth (vgrp (
        text "Inductive session: Set :=" ^^ break ^^
        ppListSep (List.map (fun session ->
            text "| " ^^ text session ^^ text ": " ^^
            ppPredicateType session (text session ^^ text "_predicates" ^^
                                     break ^^ text "-> session")
        ) slist) break ^^
        text "."
    ))
  ));

  IO.printf "Variable implicit_session : %s_predicates.\n\n" !analysis_session;

  let (rules, assertions) = slice_ast sentences in  
  (* Construct a rule dependency graph and output the rules SCC by SCC in
   * a topologically sorted order *)
  List.iter compute_rule_deps rules;

  let ruledepscc = Pg.compute_scc rule_depgraph in
  let ruledepsccmems = H.create 10 in
  Pg.iter_scc rule_depgraph ruledepscc (H.add ruledepsccmems);
  let ruledeptpo = Pg.topsort rule_depgraph ruledepscc in 

  List.iter (fun sccid -> try 
        let mems = H.find ruledepsccmems sccid in
        IO.printf "%s\n\n" (ppToString 72 (
            text "Inductive " ^^
            ppListSep (List.map ppPredicateDef mems) (break ^^ text "with ") ^^
            text "." ^^ break ^^
	    text "Hint Constructors " ^^
	    ppListSep (List.map text mems) break ^^ text " : clpa."
        ))
  with Not_found -> ()) (List.rev ruledeptpo);

  (* Print out the list of assertions as hypotheses *)
  let assert_id = ref 0 in
  List.iter (fun assertion ->
    match assertion.r_body with
      | Ar_assertion (nameo, goal) ->
	  let (gdoc, vars) = ppGoal assertion.r_type_vmap false goal in
	  let name = 
	    match nameo with
	      | None -> incr assert_id; 
		  "assert_" ^ (string_of_int !assert_id)
	      | Some name -> name in
	  IO.printf "%s\n" (ppToString 72 (vgrp (
	    text "Variable " ^^
	    text name ^^ text ":" ^^ break ^^
	    ppUnivVars (VarSet.elements vars) gdoc ^^
	    text "." ^^ break ^^
	    text "Hint Resolve " ^^ text name ^^ text ": clpa."
	  )))
      | _ -> unreachable ()
  ) assertions

(* Main *)

let usage = "Usage: clpa [options] program.clp*"

let main () = 
  let programs : string list ref = ref [] in
  let add_program = prepend programs in
  let options = Arg.align [
    ("-I", Arg.String (prepend Frontend.source_dirs),
     "dir  Extra directory to be searched for source code");
    ("--debug", Arg.String set_debug,
     "flag  Set debug flag");
    ("--list-debug", Arg.Unit list_all_debug,
     "  List all possible debug flags");
  ] in
  Arg.parse options (add_program) usage;
  if !programs = [] then (Arg.usage options usage; exit 1);
  List.iter xlate_program !programs
let main = make_track_1 "main" main

let _ = main()

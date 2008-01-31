(* Logic program abstract syntax trees and symbol tables 
 *
 * Authors:
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
 *   Brian Hackett  <bhackett@stanford.edu>
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


open Spec
open Clpautil
open Flags

module A = Array
module H = Hashtbl
module S = String
module IO = Streamio

(* Sets of symbols *)
module SymbolSet = Set.Make(OrderedString)

(* Sets and maps of variables *)
type t_var = string
module VarSet = Set.Make(OrderedString)
module VarMap = Map.Make(OrderedString)

let varmap_keys vm = VarMap.fold (fun k _ s -> VarSet.add k s) vm VarSet.empty
let varmap_restrict vm vs = VarMap.fold 
  (fun k v m -> if VarSet.mem k vs then VarMap.add k v m else m) vm VarMap.empty
let varmap_remove_keys vm vs = VarMap.fold
  (fun k v m -> if VarSet.mem k vs then m else VarMap.add k v m) vm VarMap.empty
let varmap_union vm1 vm2 = VarMap.fold VarMap.add vm2 vm1

let varset_of_list l = 
    List.fold_left (fun set elt -> VarSet.add elt set) VarSet.empty l

type t_type_renaming = t_val_type -> t_val_type

(* A mode environment, indicating the state of all variables wrt a goal. *)
type mode_env = {
  (* Variables used by this goal, and which were bound either elsewhere
   * within this goal, or by an earlier goal *)
  used    : VarSet.t;
  (* Variables that are *always* bound by this goal *)
  bound   : VarSet.t;
  (* Variables that are either (a) sometimes but not always bound by this goal,
   * or (b) are used (implicitly) existentially quantified within this goal,
   * such as in a negation or collection, and thus can't be reused later *)
  noreuse : VarSet.t;
}

let empty_menv = {
  bound = VarSet.empty; 
  used = VarSet.empty; 
  noreuse = VarSet.empty;
}

(* Disambiguated symbols *)
type t_dsymbol = string 
let dsymbol_empty = ""

type ast_term =
  | At_anyvar of string
  | At_var    of string
  | At_string of string
  | At_int    of Big_int.big_int
  | At_float  of float
  | At_sum    of string * ast_term array (* f{...} *)
  | At_call   of ast_pred
and ast_pred = {
  p_name: string;
  p_args: ast_term array;

  (* Which overloaded version of a predicate are we referring to?
   * Filled in by type-checking. *)
  mutable p_disambiguation: t_dsymbol;

  mutable p_type_renaming: t_type_renaming;
} 

type ast_spred = {
  s_session : ast_pred option;
  s_pred    : ast_pred;
}


type ast_goal = {
  (* Location of the goal in the source *)
  sfa : sfa;                
  
  (* The contents of this goal *)
  mutable body : ast_goal_body;     

  (* The set of implicitly quantified variables used by this goal and its 
   * subgoals. Variables that are use explicitly quantified within this goal
   * are not included in this set. *)
  mutable vars_used : VarSet.t; 

  (* The non-local variables in the goal, i.e. variables that are used both 
   * inside and outside the goal. *)
  nonlocals : VarSet.t; 

  (* A mode environment for this goal, filled in by mode checking *)
  mutable menv : mode_env;  
}

and ast_goal_body =
    Ag_conjunction of ast_goal list
  | Ag_disjunction of ast_goal list
  | Ag_find        of ast_spred
  | Ag_wait        of ast_pred 
  | Ag_add         of ast_spred
  | Ag_negation    of ast_goal
  | Ag_implies     of ast_goal * ast_goal
  | Ag_some        of t_var list * ast_goal
  | Ag_all         of t_var list * ast_goal
  | Ag_collection  of ast_goal * ast_pred

type ast_rule_body = 
    Ar_flat        of ast_goal
  | Ar_horn_clause of string option * ast_spred * ast_goal
  | Ar_query       of ast_pred
  | Ar_assertion   of string option * ast_goal

type ast_rule = {
  r_body : ast_rule_body;
  rl_sfa : sfa;

  (* Type environment for the rule. Filled in by type checking. *)
  mutable r_type_vmap: t_type_vmap;
}

type ast = ast_rule list

let rec string_of_ast_term t = match t with
  | At_anyvar v -> v
  | At_var    v -> v
  | At_string s -> "\"" ^ s ^ "\""
  | At_int    i -> Big_int.string_of_big_int i
  | At_float  f -> string_of_float f
  | At_sum  (name,args) -> 
      if name = list_cons_name || name = list_nil_name then
        string_of_ast_list t
      else if A.length args = 0 then name
      else
	name ^ "{" ^ (sep_string_of_array "," string_of_ast_term args) ^ "}"
  | At_call p -> string_of_ast_pred p
and string_of_ast_list l = 
  let rec svals prev l = 
    match l with
      | At_sum (name, [|x;xs|]) when name = list_cons_name ->
	  (if prev then "," else "") ^ (string_of_ast_term x) ^ (svals true xs)
      | At_sum (name, [||]) when name = list_nil_name -> ""
      | _ -> "|" ^ (string_of_ast_term l) in
    "[" ^ (svals false l) ^ "]"
and string_of_ast_pred p =
  let argstr = sep_string_of_array "," string_of_ast_term p.p_args in
     (p.p_name) ^ "(" ^ argstr ^ ")"


(* Global symbol table *)
type symbol_kind =
    Sk_predicate
  | Sk_session
  | Sk_type
  | Sk_sum_value
  | Sk_analyze

type t_symbol_def = {
  s_name  : string;
  s_arity : int;
  s_variable_arity : bool; (* If true, then this symbol has variable arity
			    * with a minimum arity of s_arity *)  
  s_kind  : symbol_kind;
  s_disambiguations : t_dsymbol list;
}

(* Predicate symbol table *)

type t_predicate_kind = 
  | Pk_session
  | Pk_add_handler
  | Pk_find_handler
  | Pk_collect_handler
  | Pk_regular

type t_predicate_def = {
  pd_sfa   : sfa;
  pd_kind  : t_predicate_kind;
  pd_args  : t_val_type array; (* Argument types, if any *)
  (* All known predicate modes. Each predicate can have multiple modes *)
  pd_modes : (t_pred_mode * Spec.t_succeeds list) list;

  (* Has this predicate been used with the '?' wait operator? *)
  mutable pd_magic : bool; 

  (* Does this predicate appear in an external session? *)
  mutable pd_in_session: bool;

  (* All known orderings for this predicate *)
  mutable pd_orders: (int * int) list;
}

type t_type_kind =
  | T_alias of t_val_type
  | T_sumtype of string list
  | T_abstract

type t_type_def = {
  td_kind : t_type_kind;
  td_args : t_val_type array;
  td_sfa  : sfa;
}

(* Opened packages *)
let packages : (string,unit) H.t = H.create 10

(* Types of arguments to all known symbols *)
let symbols : (string, t_symbol_def) H.t = H.create 100

(* Definitions of all known predicates. Since predicates can be overloaded
 * the table key contains disambiguated symbols as its key. *)
let predicates : (t_dsymbol, t_predicate_def) H.t = H.create 100

(* All defined types (sumtypes or type aliases). No types can be redefined,
 * even to the same contents. *)
let types : (string, t_type_def) H.t = H.create 10

(* All types with predicate orderings over them *)
let order_types : (t_val_type,unit) H.t = H.create 10

(* All sumvalue*sumtype pairs, indexed by the name of the sumtype value *)
let sumvalues : (string,t_pred_type * t_val_type) H.t = H.create 10

(* For each session, an optional hashtable containing a list of predicate
 * names that may be present in a session. Predicates occurring in sessions
 * may not be overloaded, so there is no need for disambiguation information. 
 *)
let sessions : (string, SymbolSet.t) H.t = H.create 10

(* Session names that must be used with an external session *)
let sess_handlers = [clear_pred_name;process_dep_name]

(* Analysis directives *)
let analysis_session = ref ""
let analysis_name = ref ""
let analysis_topdown = ref None  (* Some topdown if set *)
let analysis_eager = ref false
let analysis_priority = ref None (* Some prio if set *)

let reset_type_checking() =
  H.clear packages;
  H.clear symbols;
  H.clear types;
  H.clear predicates;
  H.clear order_types;
  H.clear sessions;
  H.clear sumvalues;
  analysis_session := "";
  analysis_name := "";
  analysis_topdown := None;
  analysis_eager := false;
  analysis_priority := None

let add_symbol sfa kind name arity vararg dsymbolo =
  let ds = 
    try 
      let osym = H.find symbols name in
	if kind <> osym.s_kind then
	  rule_error sfa ("Multiple declarations of different kinds: " ^ name)
	else if arity <> osym.s_arity || vararg <> osym.s_variable_arity then
	  rule_error sfa ("Multiple declarations with different arities: " 
			   ^ name)
	else osym.s_disambiguations
    with Not_found -> [] in
  let dsym = match dsymbolo with 
    | None -> name
    | Some d -> d in
    if (kind = Sk_predicate || kind = Sk_session) 
      && List.mem dsym ds then rule_error sfa 
      ("Multiple declarations of: " ^ name);
    H.replace symbols name 
      {s_name = name; s_arity = arity; s_variable_arity = vararg; 
       s_kind = kind; s_disambiguations = dsym::ds};
    dsym
      
let get_symbol sfa kind name =
  try let osym = H.find symbols name in
    (* special case for Sk_session, which can also be used as Sk_predicate *)
    if kind <> osym.s_kind && (kind <> Sk_predicate || 
       osym.s_kind <> Sk_session) then
      rule_error sfa ("Bad symbol kind: " ^ name)
    else osym
  with Not_found -> rule_error sfa ("Unknown symbol: " ^ name)

let check_succeeds sfa name succeeds =
  (* sanity-check: succeeds can't include both Sk_once and Sk_many *)
  if List.exists ((=)Sk_once) succeeds &&
     List.exists ((=)Sk_many) succeeds then
    rule_error sfa ("Predicate " ^ name ^
      " has both 'once' and 'many' in 'succeeds' clause")

let add_predicate sfa kind name targs modes = 
  let (arity,vararg) = match is_pred_vargs targs with 
    | None -> (A.length targs, false)
    | Some (req, _) -> (A.length req, true) in
  let dsym = add_symbol sfa Sk_predicate name arity vararg None in
  List.iter (o (check_succeeds sfa name) snd) modes;
  H.replace predicates dsym {
    pd_sfa = sfa;
    pd_kind = kind;
    pd_args = targs;
    pd_modes = modes;
    pd_magic = (if kind = Pk_regular && 
      exists_array ((=) true) (fst (List.hd modes)) then true else false);
    pd_in_session = false;
    pd_orders = [];
  };
    dsym

let add_session sfa ((name,targs),contentso) =
  let dsym = add_symbol sfa Sk_session name (A.length targs) false None in
  H.replace predicates dsym {
    pd_sfa = sfa;
    pd_kind = Pk_session;
    pd_args = targs;
    pd_modes = [];
    pd_magic = false;
    pd_in_session = false;
    pd_orders = [];
  };
  match contentso with
      None -> ()
    | Some contents -> 
        let cs = try H.find sessions name with Not_found -> SymbolSet.empty in
        (* Every session implicitly contains a predicate with the same name as 
         * the session *)
        let cs' = SymbolSet.add name cs in 
        let cs'' = List.fold_left (fun s p -> SymbolSet.add p s) cs' 
	  contents in
        H.replace sessions name cs''

let add_operator sfa operator alias =  
  let sym = get_symbol sfa Sk_predicate alias in
  let pda = match sym.s_disambiguations with
    | [pda] -> pda
    | _ -> rule_error sfa "Target of operator declaration must be unambiguous"
  in
    ignore (add_symbol sfa Sk_predicate operator sym.s_arity false (Some pda))
  
(* Declare a type *)  
let add_type sfa typ = 
  let (name,targs) = break_type typ in
    ignore (add_symbol sfa Sk_type name (A.length targs) false None)

(* Define a type *)
let define_type sfa typ kind =
  let (name, targs) = break_type typ in
    if H.mem types name then
      rule_error sfa ("Type redefinition: " ^ name)
    else H.add types name {
      td_sfa = sfa;
      td_kind = kind;
      td_args = targs;
    }

(* Define an alias type *)
let add_alias_type sfa (atyp,ntyp) =
  define_type sfa atyp (T_alias ntyp)

(* Define a sum type *)
let add_sum_values sfa (typ,preds) =
  let fsyms = List.map (o fst fst) preds in
  define_type sfa typ (T_sumtype fsyms);
  List.iter (fun ((pname,pargs),sfa) ->
    ignore (add_symbol sfa Sk_sum_value pname (A.length pargs) 
	       (is_pred_vargs pargs <> None) None);
    H.add sumvalues pname ((pname,pargs), typ)) preds

(* Flatten a disambiguated name into a string for use by the backend. 
 * Currently the disambiguated names _are_ strings, so this is just the 
 * identity. *)
let mangle_name dsym = dsym

let add_order predda (a0,a1) =
  let def = (H.find predicates predda) in
  def.pd_orders <- (a0,a1)::def.pd_orders;
  let targs = def.pd_args in
    H.replace order_types targs.(a0) ();
    H.replace order_types targs.(a1) ()

let add_package name =
  if not (H.mem packages name) then begin
    H.add packages name ();
    try 
      let pack = get_package name in
      let sfa = Sfa_package name in
      List.iter (fun ((n,a),_) -> 
	ignore (add_predicate sfa Pk_add_handler n a []))
        pack.p_add_handlers;
      List.iter (fun ((n,a),ms,_) -> 
	ignore (add_predicate sfa Pk_find_handler n a ms))
        pack.p_find_handlers;
      List.iter (fun ((n,a),m,_) -> 
	ignore (add_predicate sfa Pk_collect_handler n a [m,[]]))
        pack.p_collect_handlers;
      List.iter (fun ((n,a),orders) ->
        let pn = 
	  add_predicate sfa Pk_regular n a [A.make (A.length a) false, []] in
          List.iter (add_order pn) orders)
        pack.p_predicates;
      List.iter (add_session sfa) pack.p_sessions;
      List.iter (fun (t,vals) -> add_type sfa t; 
        add_sum_values sfa (t, List.map (fun v -> (v,sfa)) vals))
        pack.p_sumtypes;
      List.iter (fun t -> add_type sfa t; 
        define_type sfa t T_abstract) pack.p_abstypes;
      List.iter (fun (op,alias) -> add_operator sfa op alias) pack.p_operators
    with Not_found ->
      parse_error ("Unknown package: " ^ name)
  end

let _ = add_symbol Sfa_none Sk_analyze "session_name" 1 false None
let _ = add_symbol Sfa_none Sk_analyze "analysis_name" 1 false None
let _ = add_symbol Sfa_none Sk_analyze "topdown" 0 false None
let _ = add_symbol Sfa_none Sk_analyze "bottomup" 0 false None
let _ = add_symbol Sfa_none Sk_analyze "eager" 0 false None
let _ = add_symbol Sfa_none Sk_analyze "priority" 1 false None

let add_analyze pred =
  try match pred.p_name with
      "session_name" ->
	let sname = match pred.p_args with [|At_string s|] -> s | _ ->
	  parse_error "String literal expected as argument to session_name" in
          if !analysis_session <> "" then
            parse_error "Analysis session set multiple times";
          ignore (get_symbol (cur_sfa ()) Sk_session sname);
          analysis_session := sname
    | "analysis_name" ->
	let aname = match pred.p_args with [|At_string s|] -> s | _ ->
	  parse_error "String literal expected as argument to analysis_name" in
          if !analysis_name <> "" then
            parse_error "Analysis name set multiple times";
          analysis_name := aname
    | "topdown" ->
        if !analysis_topdown <> None then
          parse_error "Analysis topdown/bottomup set multiple times";
        analysis_topdown := Some true
    | "bottomup" ->
        if !analysis_topdown <> None then
          parse_error "Analysis topdown/bottomup set multiple times";
        analysis_topdown := Some false
    | "eager" ->
        if !analysis_eager <> false then
          parse_error "Analysis eager set multiple times";
        analysis_eager := true
    | "priority" ->
        if !analysis_priority <> None then
          parse_error "Analysis priority set multiple times";
	let prio = match pred.p_args with [|At_int i|] -> i | _ ->
	  parse_error "Integer literal expected as argument to priority" in
        analysis_priority := Some (Big_int.int_of_big_int prio)
    | _ ->
        parse_error ("Unknown symbol: " ^ pred.p_name)
  with Unexpected _ ->
    parse_error ("Bad argument type for " ^ (string_of_ast_pred pred))

let set_analysis_session sess =
  if !analysis_session <> "" then
    parse_error "Analysis session set multiple times";
  ignore (get_symbol (cur_sfa ()) Sk_session sess);
  analysis_session := sess

let set_analysis_name name =
  if !analysis_name <> "" then
    parse_error "Analysis name set multiple times";
  analysis_name := name

let set_analysis_topdown topdown =
  if !analysis_topdown <> None then
    parse_error "Analysis topdown/bottomup set multiple times";
  analysis_topdown := Some topdown

let rec remove_aliases typ =
    try let (name,args) = break_type typ in
        try (
	  let tdef = H.find types name in
	    match tdef.td_kind with
	      | T_alias atyp ->
		  (let (nname,nargs) = break_type atyp in
		     match make_type_vmap args tdef.td_args with
		       | Some tvm ->
			   remove_aliases (make_type nname 
					      (A.map (vmap_type tvm) nargs))
		       | None -> parse_error "Alias type mismatch")
              | _ -> raise Not_found)
        with Not_found -> make_type name (A.map remove_aliases args)
  with Unexpected _ -> typ

(* Check a symbol with arguments for common errors:
 * - Missing or wrong kind of prototype.
 * - Incorrect number of arguments.
 **)
let check_symbol kind sfa (name,argnum,str) =
  let sym = get_symbol sfa kind name in
    if sym.s_variable_arity then
      (if argnum < sym.s_arity then
	rule_error sfa ("Variable arity symbol '" ^ name ^ 
	 "' requires at least " ^ (string_of_int sym.s_arity) ^ " arguments"))
    else
      if argnum <> sym.s_arity then
        rule_error sfa ("Incorrect arity for symbol '" ^ name ^ 
	"'; expected " ^ (string_of_int sym.s_arity) ^ " arguments, got " ^ 
	(string_of_int argnum))

let filt_typ2sym typ =
  let (n,a) = break_type typ in (n,A.length a,string_of_type typ)
let check_type v = check_symbol Sk_type (Spec.cur_sfa ()) (filt_typ2sym v)

let get_pred_def p = H.find predicates p.p_disambiguation

let get_all_modes pred =
  let pd = get_pred_def pred in
  let arity = A.length pred.p_args in
  match pd.pd_modes with
      [] -> [A.make arity false, []]
    | modes -> modes
let get_mode p = List.hd (get_all_modes p)

let all_out_mode p = forall_array ((=) false) (fst (get_mode p))

(* Well-formedness checking *)

(* Check an AST rule for well-formedness:
 * - symbol does not exist
 * - incorrect number of arguments
 *)
let ast_check_rule rule =
  let rec check_term sfa t = 
    match t with 
      | At_sum (name, args) ->	  
	  check_symbol Sk_sum_value sfa 
	    (name, A.length args, string_of_ast_term t);
	  A.iter (check_term sfa) args
      | At_call p ->
	  check_symbol Sk_predicate sfa
	    (p.p_name, (A.length p.p_args) + 1, string_of_ast_term t);
	  (if (H.find symbols p.p_name).s_variable_arity then rule_error sfa 
	    "Variable arity predicates cannot be used as functions");
	  A.iter (check_term sfa) p.p_args	  
      | _ -> () in

  let filt_pred2sym p =
    (p.p_name,A.length p.p_args,string_of_ast_pred p) in
  let check_predicate sfa kind p = 
    A.iter (check_term sfa) p.p_args;
    check_symbol kind sfa (filt_pred2sym p) in
  let check_spred sfa spo pred = 
    check_predicate sfa Sk_predicate pred ;
    match spo with
	None -> ()
      | Some s -> 
          check_predicate sfa Sk_session s ;
          let sname = s.p_name in
          let pname = pred.p_name in
            if not (List.mem pname sess_handlers) then
              (try let scontents = H.find sessions sname in
		     if not (SymbolSet.mem pname scontents) then
		       rule_error sfa 
			 ("Predicate " ^ pname ^ " is not a valid member of "
			   ^ "session " ^ sname)
		with Not_found -> ()
              ) in

  let rec ast_check_goal goal =
    match goal.body with
        Ag_conjunction goals -> List.iter ast_check_goal goals
      | Ag_disjunction goals -> List.iter ast_check_goal goals
      | Ag_find  sp   -> check_spred goal.sfa sp.s_session sp.s_pred
      | Ag_wait  pred -> check_predicate goal.sfa Sk_predicate pred
      | Ag_add   sp   -> check_spred goal.sfa sp.s_session sp.s_pred
      | Ag_some (_,goal) -> ast_check_goal goal
      | Ag_all  (_,goal) -> ast_check_goal goal
      | Ag_implies (g1,g2) -> ast_check_goal g1; ast_check_goal g2
      | Ag_negation goal -> ast_check_goal goal
      | Ag_collection (cgoal, cpred) -> 
          ast_check_goal cgoal; 
          check_predicate goal.sfa Sk_predicate cpred in
  match rule.r_body with 
      Ar_flat goal ->  ast_check_goal goal
    | Ar_horn_clause (_, head, body) -> 
        check_spred rule.rl_sfa head.s_session head.s_pred;
        ast_check_goal body
    | Ar_query pred -> check_predicate rule.rl_sfa Sk_predicate pred
    | Ar_assertion (_, goal) -> ast_check_goal goal


(* Check that every predicate listed as possibly present in a session has a 
 * declaration *)
let session_check () =
  H.iter (fun s preds -> 
    let sym = H.find symbols s in
    let pd = H.find predicates (List.hd sym.s_disambiguations) in
    SymbolSet.iter (fun pred -> 
      let psym = get_symbol pd.pd_sfa Sk_predicate pred in
	match psym.s_disambiguations with
	  | [da] -> (H.find predicates da).pd_in_session <- true
	  | _ -> rule_error pd.pd_sfa ("Overloaded predicate '" ^ pred ^ 
			       "' may not be used in session definition.")
    ) preds
  ) sessions


(* Don't-care variable renaming
 *
 * Ensure each "don't care" variable has a unique name by adding a numeric
 * id to disambiguate, if necessary. Both the type checker and Coq extraction
 * rely on the uniqueness of variable names.
 *)
let dont_care_disambiguate_rule rule =
  let rec dc_disambiguate_term t dvm =
    match t with 
      | At_anyvar v ->
	  let n = try VarMap.find v dvm + 1 with Not_found -> 0 in
	  let dvm' = VarMap.add v n dvm in
	    if n <> 0 then
              let t' = At_anyvar (v ^ (string_of_int n)) in
		(* If we changed the variable name the new variable name may 
		 * also be in use. But we can solve that problem recursively. *)
		dc_disambiguate_term t' dvm'
	    else
              (t, dvm')
      | At_sum (fsym, fargs) ->
	  let (fargs', dvm') = map_foldl dc_disambiguate_term (A.to_list fargs)
            dvm in
	    (At_sum (fsym, A.of_list fargs'), dvm')
      | At_call p ->
	  let (fargs', dvm') = map_foldl dc_disambiguate_term 
	    (A.to_list p.p_args) dvm in
	    (At_call {p with p_args = A.of_list fargs'}, dvm')
      | _ -> (t, dvm)
    in

  let dc_disambiguate_pred pred dvm =
    let (args', dvm') = map_foldl dc_disambiguate_term (A.to_list pred.p_args) 
        dvm in
    ({pred with p_args = A.of_list args'}, dvm') in

  let dc_disambiguate_spred spred dvm =
    let (spo', dvm') =
      match spred.s_session with
      | None -> (None, dvm)
      | Some sp -> let (sp', dvm') = dc_disambiguate_pred sp dvm in
                   (Some sp', dvm')
      in
    let (pred', dvm'') = dc_disambiguate_pred spred.s_pred dvm' in
    ({s_session = spo'; s_pred = pred'}, dvm'') in

  let rec dc_disambiguate_goal goal dvm =
    match goal.body with
      Ag_conjunction goals ->
        List.fold_right dc_disambiguate_goal goals dvm 
    | Ag_disjunction goals ->
        List.fold_right dc_disambiguate_goal goals dvm
    | Ag_find sp   ->
        let (sp', dvm') = dc_disambiguate_spred sp dvm in
        goal.body <- Ag_find sp'; dvm'
    | Ag_wait  pred ->
        let (pred', dvm') = dc_disambiguate_pred pred dvm in
        goal.body <- Ag_wait pred'; dvm'
    | Ag_add   sp   ->
        let (sp', dvm') = dc_disambiguate_spred sp dvm in
        goal.body <- Ag_add sp'; dvm'
    | Ag_some (vs, goal) ->
        dc_disambiguate_goal goal dvm 
    | Ag_all  (vs, goal) ->
        dc_disambiguate_goal goal dvm 
    | Ag_implies (g1,g2) ->
        o (dc_disambiguate_goal g1) (dc_disambiguate_goal g2) dvm
    | Ag_negation goal ->
        dc_disambiguate_goal goal dvm 
    | Ag_collection (cgoal, cpred) ->
        let dvm' = dc_disambiguate_goal cgoal dvm in
        let (cpred', dvm'') = dc_disambiguate_pred cpred dvm' in
        goal.body <- Ag_collection (cgoal, cpred'); dvm''
    in
  match rule.r_body with
  | Ar_horn_clause (nameo, head, body) ->
      let (head', dvm)  = dc_disambiguate_spred head VarMap.empty in
      ignore (dc_disambiguate_goal body dvm);
      {rule with r_body = Ar_horn_clause (nameo, head', body)}
  | Ar_flat goal -> 
      ignore (dc_disambiguate_goal goal VarMap.empty);
      {rule with r_body = Ar_flat goal}
  | Ar_query pred ->
      {rule with r_body = 
         Ar_query (fst (dc_disambiguate_pred pred VarMap.empty))}
  | Ar_assertion (nameo, goal) ->
      ignore (dc_disambiguate_goal goal VarMap.empty);
      {rule with r_body = Ar_assertion (nameo, goal)}


(* Variable renaming
 *
 * Functions for creating and applying variable substitutions to rules.
 *)
 
(* Construct a renaming for a set of variables. The renamed variables are
 * given unique prefixes of the form rXYZ_, where XYZ is an arbitrary numeric
 * constant. Since the first letter of the prefix is lower case, the programmer
 * cannot create variables that could clash with the results of renaming.
 *)
let rename_id = ref 0
let make_renaming (vars: VarSet.t) : string VarMap.t =
    VarSet.fold (fun v remap ->
        incr rename_id;
        VarMap.add v ("r" ^ (string_of_int !rename_id) ^ "_" ^ v) remap
    ) vars VarMap.empty

let rename_var remap v = try VarMap.find v remap with Not_found -> v

let varset_apply_renaming remap varset = VarMap.fold 
    (fun v v' s0 ->
        if VarSet.mem v s0 then
            VarSet.add v' (VarSet.remove v s0)
        else
            s0
    ) remap varset


(* Apply a variable substitution to the variables occurring in a goal and
 * the various objects that occur within goals. 
 *
 * The only interesting case here is the treatment of variables bound by an
 * explicit quantifier, which are not renamed, since they're different
 * variables.
 *)

let rec term_rename_vars (remap:string VarMap.t) (t:ast_term) : ast_term =
  match t with 
    | At_var v ->
        let v' = try VarMap.find v remap with Not_found -> v in
	  At_var v'
    | At_sum (fsym, args) ->
        let args' = List.map (term_rename_vars remap) (A.to_list args) in
        At_sum (fsym, A.of_list args')
    | At_call p ->
        let args' = List.map (term_rename_vars remap) (A.to_list p.p_args) in
        At_call {p with p_args = A.of_list args'}
    | _ -> t

let predicate_rename_vars (remap: string VarMap.t) (pred:ast_pred) : ast_pred =
    let args' = List.map (term_rename_vars remap) (A.to_list pred.p_args) in
    {pred with p_args = A.of_list args'}

let spredicate_rename_vars (remap: string VarMap.t) (spred:ast_spred) 
    : ast_spred =
    let session' = match spred.s_session with
        | None -> None
        | Some session -> Some (predicate_rename_vars remap session) in
    let predicate' = predicate_rename_vars remap spred.s_pred in
    { s_session = session'; s_pred = predicate' }

let rec goal_rename_vars (remap: string VarMap.t) (goal:ast_goal) : ast_goal =
    let body' = match goal.body with
    | Ag_conjunction cs -> 
        Ag_conjunction (List.map (goal_rename_vars remap) cs)
    | Ag_disjunction ds -> 
        Ag_disjunction (List.map (goal_rename_vars remap) ds)
    | Ag_implies (g1, g2) ->
        let g1' = goal_rename_vars remap g1 in
        let g2' = goal_rename_vars remap g2 in
        Ag_implies (g1', g2')
    | Ag_negation ng ->
        Ag_negation (goal_rename_vars remap ng)
    | Ag_some (vs, g) ->
        (* Remove any explicitly quantified variables from the mapping *)
        let remap' = VarSet.fold VarMap.remove (varset_of_list vs) remap in
        let g' = goal_rename_vars remap' g in
        Ag_some (vs, g')
    | Ag_all (vs, g) ->
        (* Remove any explicitly quantified variables from the mapping *)
        let remap' = VarSet.fold VarMap.remove (varset_of_list vs) remap in
        let g' = goal_rename_vars remap' g in
        Ag_all (vs, g')
    | Ag_find spredicate ->
        Ag_find (spredicate_rename_vars remap spredicate)
    | Ag_wait predicate ->
        Ag_wait (predicate_rename_vars remap predicate)
    | Ag_add spredicate ->
        Ag_add (spredicate_rename_vars remap spredicate)
    | Ag_collection (goal, cpred) ->
        Ag_collection (goal_rename_vars remap goal, 
                       predicate_rename_vars remap cpred) 
    in
    let vars_used' = varset_apply_renaming remap goal.vars_used in
    let nonlocals' = varset_apply_renaming remap goal.nonlocals in
    { goal with body = body'; vars_used = vars_used'; nonlocals = nonlocals' }


(* Variable scoping and implicit quantifier elaboration
 *
 * Semantically every variable that does not occur in the head of a clause 
 * is considered to be implicitly existentially quantified around its closest 
 * enclosing scope. Variables that do occur in the head of the clause are
 * implicitly universally quantified outside the rule.
 *
 * We evaluate scopes using two passes:
 * 1. The set of all variables used in the clause is determined, including
 *    don't care variables, but excluding variables that occur explicitly
 *    quantified (since these already have an explicit scope). We 
 *    include don't care variables in this pass, since we'd like to treat
 *    variables uniformly in the Coq extraction pass.
 * 2. Each variable is pushed as far down in the abstract syntax tree as
 *    possible in attempt to find the "most local" scope. Explicit quantifiers
 *    are unfolded at this stage.
 *
 *)


(* Find the set of variables used in a term *)
let rec term_vars_used t =
  match t with
    | At_anyvar v
    | At_var v -> VarSet.singleton v
    | At_sum (_, args) ->
	List.fold_left VarSet.union VarSet.empty (List.map term_vars_used 
						     (A.to_list args))
    | At_call p ->
	List.fold_left VarSet.union VarSet.empty (List.map term_vars_used 
						     (A.to_list p.p_args))
    | _ -> VarSet.empty

(* Find the set of variables used in a predicate *)
let predicate_vars_used p =
  let args = A.to_list p.p_args in
    List.fold_left VarSet.union VarSet.empty (List.map term_vars_used args)

(* Find the set of variables used in a session-predicate pair *)
let spredicate_vars_used s =
  VarSet.union (predicate_vars_used s.s_pred)
    (match s.s_session with
     | None -> VarSet.empty
     | Some p -> predicate_vars_used p)
  
(* For each goal in a list of goals, compute the set of variables referenced 
 * in the following goals in the list *)
let goals_vars_after gs =
  let rec gvu_2 va glist =
    match glist with 
    | [] -> []
    | g::gs -> va::(gvu_2 (VarSet.union va g.vars_used) gs) in
  List.rev (gvu_2 VarSet.empty (List.rev gs))

let scope_infer_rule r =
  (* Find the list of variables used in each goal without explicit 
   * quantification *)
  let rec goal_vars_used g =
    let used = match g.body with 
      | Ag_conjunction cs -> List.fold_left VarSet.union VarSet.empty 
          (List.map goal_vars_used cs)
      | Ag_disjunction ds -> List.fold_left VarSet.union VarSet.empty 
          (List.map goal_vars_used ds)
      | Ag_find sp -> spredicate_vars_used sp
      | Ag_wait p -> predicate_vars_used p
      | Ag_add sp -> spredicate_vars_used sp
      | Ag_negation g -> goal_vars_used g
      | Ag_implies (g1,g2) -> 
            VarSet.union (goal_vars_used g1) (goal_vars_used g2)
      | Ag_some (vs, g) -> VarSet.union (goal_vars_used g) (varset_of_list vs)
      | Ag_all (vs, g) -> VarSet.union (goal_vars_used g) (varset_of_list vs)
      | Ag_collection (g, p) -> 
          VarSet.union (goal_vars_used g) (predicate_vars_used p)
      in
      g.vars_used <- used; 
      used in

  (* Find non-local variables in an AST rule, and rename away any quantified
   * variables that clash with names outside their scope *)
  let rec find_nonlocals g outside =
      match g.body with
      | Ag_conjunction cs -> 
          let varsafter = goals_vars_after cs in
          let l = List.combine cs varsafter in
          let (cs', inside) = map_foldl (fun (c, vs) v ->
            (find_nonlocals c (VarSet.union outside (VarSet.union v vs)),
             VarSet.union v c.vars_used)) l VarSet.empty in
          { g with body = Ag_conjunction cs'; 
                   nonlocals = VarSet.inter outside inside }
      | Ag_disjunction ds ->
          let varsafter = goals_vars_after ds in
          let l = List.combine ds varsafter in
          let (ds', inside) = map_foldl (fun (d, vs) v ->
            (find_nonlocals d (VarSet.union outside (VarSet.union v vs)),
             VarSet.union v d.vars_used)) l VarSet.empty in
          { g with body = Ag_disjunction ds'; 
                   nonlocals = VarSet.inter outside inside }
      | Ag_negation ng ->
          { g with body = Ag_negation (find_nonlocals ng outside);
                   nonlocals = VarSet.inter outside ng.vars_used }
      | Ag_implies (g1, g2) ->
          let g1' = find_nonlocals g1 (VarSet.union outside g2.vars_used) in
          let g2' = find_nonlocals g2 (VarSet.union outside g1.vars_used) in
          { g with body = Ag_implies (g1', g2');
                   nonlocals = VarSet.inter outside 
                        (VarSet.union g1'.vars_used g2'.vars_used)}
      | Ag_some (vs, g) ->
          let vset = varset_of_list vs in
          let clash = VarSet.inter vset outside in
          let remap = make_renaming clash in
          let g' = goal_rename_vars remap g in
          let vs' = List.map (rename_var remap) vs in
          let g'' = find_nonlocals g' (VarSet.union outside vset) in
          { g with body = Ag_some (vs', g'');
                   nonlocals = VarSet.inter outside g.vars_used}
      | Ag_all (vs, g) ->
          let vset = varset_of_list vs in
          let clash = VarSet.inter vset outside in
          let remap = make_renaming clash in
          let g' = goal_rename_vars remap g in
          let vs' = List.map (rename_var remap) vs in
          let g'' = find_nonlocals g' (VarSet.union outside vset) in
          { g with body = Ag_all (vs', g'');
                   nonlocals = VarSet.inter outside g.vars_used}
      | Ag_collection (cgoal, cpred) ->
          let cgoal' = find_nonlocals cgoal 
            (VarSet.union outside (predicate_vars_used cpred)) in
          { g with body = Ag_collection (cgoal', cpred);
                   nonlocals = VarSet.inter outside g.vars_used }
      | _ -> { g with nonlocals = VarSet.inter outside g.vars_used } in
  match r.r_body with
  | Ar_horn_clause (nameo, head, body) ->
     let headvars = spredicate_vars_used head in
     ignore (goal_vars_used body);
     let body' = find_nonlocals body headvars in
     {r with r_body = Ar_horn_clause (nameo, head, body')}
  | Ar_flat goal -> 
     ignore (goal_vars_used goal); 
     let goal' = find_nonlocals goal VarSet.empty in
     {r with r_body = Ar_flat goal'}
  | Ar_query pred -> r
  | Ar_assertion (nameo, goal) ->
     ignore (goal_vars_used goal); 
     let goal' = find_nonlocals goal VarSet.empty in
     {r with r_body = Ar_assertion (nameo, goal')}

(* get the main predicate information for use in checking *)
let pred_info rp =
    (rp.p_name,rp.p_args,string_of_ast_pred rp)

(* Parsing hooks *)
let parse_file : (string -> string list -> ast_rule list) ref = 
  ref (fun _ _ -> [])

(* AST pretty printing support
 *
 * This code is mainly for debugging purposes, where it is nice to be able to 
 * print out a representation of the AST. *)
open Pp
open Pputil

(* Pretty print a term *)
let ppTerm term = text (string_of_ast_term term)

(* Pretty print a predicate *)
let ppPredicate predicate = 
  text predicate.p_name ^^ text "(" ^^ 
    ppListSep (List.map ppTerm (A.to_list predicate.p_args)) (text ", ") ^^
    text ")"

(* Pretty print a session/predicate pair *)
let ppSPredicate spred = 
    (match spred.s_session with
     | None         -> empty
     | Some session -> (ppPredicate session) ^^ (text "->")
    ) ^^
    ppPredicate spred.s_pred

(* Pretty print a goal *)
let rec ppGoalBody goalbody = 
    let sw = 4 in
    agrp (match goalbody with
    | Ag_conjunction cs   -> 
        text "(" ^^ break ^^
        ppListSep (List.map (o (nest sw) ppGoal) cs) (text "," ^^ break)
        ^^ break ^^ text ")" 
    | Ag_disjunction ds   -> 
        nest sw (
            text "(" ^^ break ^^
            ppListSep (List.map ppGoal ds) (text ";" ^^ break)
        ) ^^ break ^^ text ")" 
    | Ag_find spred       -> ppSPredicate spred
    | Ag_wait pred        -> text "?" ^^ ppPredicate pred
    | Ag_add  spred       -> text "+" ^^ ppSPredicate spred
    | Ag_negation goal    -> 
        text "~ (" ^^ break ^^ nest sw (ppGoal goal) ^^ break ^^ text ")"
    | Ag_implies (g1, g2) -> 
        text "(" ^^ break ^^
        agrp (
            nest sw (ppGoal g1) ^^ 
            break ^^ text "=>" ^^ break ^^ 
            nest sw (ppGoal g2)
        ) ^^
        break ^^ text ")" 
    | Ag_some    (vs, g)  -> 
        text "some [" ^^
        ppListSep (List.map text vs) (text ", ") ^^
        text "] " ^^ ppGoal g
    | Ag_all     (vs, g)  ->
        text "all [" ^^
        ppListSep (List.map text vs) (text ", ") ^^
        text "] " ^^ ppGoal g
    | Ag_collection (goal, cpred) ->
        text "\\/" ^^ ppGoal goal ^^ text ":" ^^ ppPredicate cpred
    )
and ppGoal goal =
    vgrp (
        break ^^
        text "% Nonlocals: " ^^ 
        ppListSep (List.map text (VarSet.elements goal.nonlocals)) 
            (text ", ") ^^ break ^^
        text "% Vars used: " ^^ 
        ppListSep (List.map text (VarSet.elements goal.vars_used)) 
            (text ", ") ^^ break ^^
        ppGoalBody goal.body
    )

(* Pretty print an AST rule *)
let ppRule rule = 
    let ppNameO nameo = 
       match nameo with 
       | None      -> empty
       | Some name -> text name ^^ text ":" ^^ break in 
    let sw = 4 in
    (match rule.r_body with
     | Ar_horn_clause (nameo, head, body) -> 
        fgrp (nest sw (
            ppNameO nameo
            ^^ ppSPredicate head
            ^^ break ^^ text ":-"  
            ^^ ppGoal body
        ))
     | Ar_flat goal       -> ppGoal goal
     | Ar_query pred -> text "?- " ^^ ppPredicate pred
     | Ar_assertion (nameo, goal) -> ppNameO nameo ^^ text "assert " ^^ 
	 ppGoal goal

    ) ^^ text "."

(* Pretty print an AST *)
let ppAST (rules: ast_rule list) : doc =
    List.fold_left (fun a b -> a ^^ break ^^ break ^^ b) empty 
        (List.map ppRule rules) 


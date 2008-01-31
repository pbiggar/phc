(* Medium-level logic representation
 *
 * AST -> MLR conversion
 * Stratification
 * Magic sets transformation
 * MLR -> Spec rule conversion
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

open Spec
open Clpautil
open Flags
open Ast

module A = Array
module H = Hashtbl
module IO = Streamio

type t_spred = {
  sp_session : t_pred option;
  sp_pred    : t_pred;
}

type ml_goal_kind =
  | Mg_find
  | Mg_negation    
  | Mg_collection of t_pred
  | Mg_add       (* Only used internally by this file *)
  | Mg_wait      (* Only used internally by this file *)

type ml_goal = {
  mlg_kind     : ml_goal_kind;
  mlg_spred    : t_spred;
  mlg_mode     : (t_pred_mode * t_determinism * bool) option; 
  (* None = has a find or add handler. 
   * Some (mode, determinism, always magic) = Normal predicate, 
   * used with the given mode and determinism. The always magic flag indicates
   * that the predicate should be subject to the magic sets transformation, 
   * irrespective of whether it is necessary according to the mode. This will
   * be true of predicates used with '?' but with no input arguments. *)
  mlg_sfa      : sfa;
  mlg_stratum  : int;
  mlg_priority : t_priority list;
  mutable mlg_id : int;
}

type ml_rule = ml_goal list

let string_of_spred sp = 
  (match sp.sp_session with
    | None -> ""
    | Some s -> (full_string_of_pred s) ^ "->") ^
    (full_string_of_pred sp.sp_pred)

let string_of_ml_goal g = 
  let spstr = string_of_spred g.mlg_spred in
  match g.mlg_kind with 
    | Mg_find          -> spstr
    | Mg_negation      -> "~" ^ spstr
    | Mg_collection cp -> "\\/" ^ spstr ^ ":" ^ (full_string_of_pred cp)
    | Mg_add           -> "+" ^ spstr
    | Mg_wait          -> "?" ^ spstr
    
(* Convert an AST to a MLR representation, flattening goals and performing
 * horn-clause conversion.
 * 
 * Definitions:
 *  * A predicate is "magic" if it is the target of a '?' operation or appears
 *    in the head of a horn clause and has input arguments.
 *  * A predicate is "black magic" if querying that predicate may lead to
 *    predicates that do not unify with the query being added (not including
 *    predicates added as a result of queries within the evaluation of the
 *    outer query).
 *
 * We make the following passes;
 * 1) black-magic inference --- infer black magic predicates.
 * 2) normal-form conversion --- flatten rules into normal logic programs 
 *
 *)

let ast_to_mlr (rules:ast_rule list) : ml_rule list =
  let subgoal_id = ref 0 in
  let make_subgoal_name () =
    let name = "$subgoal" ^ (string_of_int !subgoal_id) in
      incr subgoal_id; name in

  let var_id = ref 0 in
  let fresh_variable () = 
    let v = "fv" ^ (string_of_int !var_id) in 
      incr var_id; v in
    (* Construct an MLR goal *)
  let make_goal kind spred mode sfa = {
    mlg_kind  = kind;
    mlg_spred = spred;
    mlg_mode  = mode;
    mlg_sfa   = sfa;
    mlg_priority = [];
    mlg_stratum = -1;
    mlg_id = 0;
  } in
    (* Get the mode that in which a predicate is used, together with a flag
     * indicating whether this predicate should always be treated as magic, or 
     * None if it is a handler/session predicate *)
  let get_pred_mode p = 
    let pd = get_pred_def p in
      if pd.pd_kind = Pk_regular then 
	let (mode, determinism) = List.hd pd.pd_modes in
	  Some (mode, determinism, pd.pd_magic) 
      else None in
    (* Convert an AST term into an backend value, together with a rule
     * fragment that must be evaluated before using the value. The rule 
     * fragment represents the unfolding of function calls within the term. *)
  let rec flatten_term (t:ast_term) sfa : t_val * ml_goal list =
    match t with
      | At_anyvar _ -> (anyval, [])
      | At_var v    -> (var2val v, [])
      | At_string s -> (str2val s, [])
      | At_int i    -> (int2val i, [])
      | At_float f  -> (flt2val f, [])
      | At_sum (name, args) -> 
	  let (xargs, rfrag) = flatten_term_args args sfa in
	    (sum2val (name, xargs), rfrag)
      | At_call pred -> 
	  let ovar = fresh_variable () in
	  let pred' = 
	    { pred with p_args = A.append pred.p_args [|At_var ovar|] } in
	    (var2val ovar, 
	    flatten_pred_goal {s_session = None; s_pred = pred'} Mg_find sfa)
  and flatten_term_args args sfa : t_val array * ml_goal list =
    let (xargs, rfrag) = map_foldl (fun at rfrag0 ->
      let (v, rfrag1) = flatten_term at sfa in
	(v, rfrag0 @ rfrag1)
    ) (A.to_list args) [] in
      (A.of_list xargs, rfrag)
  and flatten_pred mangle p sfa : t_pred * ml_goal list = 
    let (xargs, rfrag) = flatten_term_args p.p_args sfa in
    let xname = if mangle then mangle_name p.p_disambiguation else
	p.p_name in
      (rep2pred (xname, xargs), rfrag)
  and flatten_spred (sp:ast_spred) sfa : t_spred * ml_goal list = 
    match sp.s_session with 
      | None -> 
	  let (xp, rfrag) = flatten_pred true sp.s_pred sfa in
	    ({sp_session = None; sp_pred = xp}, rfrag)
      | Some s -> 
	  let (xs, srfrag) = flatten_pred false s sfa in
	  let mangle_pred = List.mem sp.s_pred.p_name sess_handlers in
	  let (xp, prfrag) = flatten_pred mangle_pred sp.s_pred sfa in
	    ({sp_session = Some xs; sp_pred = xp}, srfrag @ prfrag)
  and flatten_pred_goal (spred:ast_spred) kind sfa : ml_goal list =
    let (xspred, sprfrag) = flatten_spred spred sfa in
    let mode = get_pred_mode spred.s_pred in
      sprfrag @ [make_goal kind xspred mode sfa] in

  (* Take a list of AST goals and return a set of MLR rules and a goal list 
   * that evaluating the goal list together with the rules
   * is equivalent to evaluating the disjunction of the AST goals *)
  let rec make_subgoal sfa menv (gs : ast_goal list) (kind : ml_goal_kind) 
      : ml_goal list list * ml_goal list =
    match gs with 
      | [{body = Ag_find sp}] -> ([], flatten_pred_goal sp kind sfa) 
      | _ ->
	  let name = make_subgoal_name () in
	  let used = VarSet.diff menv.used menv.bound in
	  let inargs = List.map var2val (VarSet.elements used) in
	  let outargs = List.map var2val (VarSet.elements menv.bound) in
	  let mode = Some (A.of_list ((List.map (fun _ -> true) inargs) @ 
	    (List.map (fun _ -> false) outargs)), [Sk_zero;Sk_many], false) in
	  let pred = {
	    sp_session = None; 
	    sp_pred = rep2pred (name, Array.of_list (inargs @ outargs))} in
	  let (xrs, drfs) = List.split (List.map flatten_goal gs) in
	  let drs = List.map (fun rf ->
	      (if inargs = [] then rf else 
		  (make_goal Mg_wait pred mode sfa)::rf) @
		[make_goal Mg_add pred mode sfa]) drfs in
	  let orf = [make_goal kind pred mode sfa] in
	    (List.flatten (drs::xrs), orf)

  (* Goal to interpreter rule translation. Translating a goal produces a
   * (rules, rule fragment) tuple. *)
  and flatten_goal goal = match goal.body with
      Ag_conjunction cs -> List.fold_left (fun (rs,r) c ->
        let (crs, cr) = flatten_goal c in (rs @ crs, r @ cr)) ([],[]) cs
    | Ag_disjunction ds -> make_subgoal goal.sfa goal.menv ds Mg_find
    | Ag_find sp -> ([], flatten_pred_goal sp Mg_find goal.sfa)
    | Ag_wait pred ->
	let (xpred, rfrag) = flatten_pred true pred goal.sfa in
	let mode = get_pred_mode pred in
        ([], rfrag @ [make_goal Mg_wait {sp_session = None; sp_pred = xpred}
			 mode goal.sfa])
    | Ag_add sp -> ([], flatten_pred_goal sp Mg_add goal.sfa)
    | Ag_negation g -> make_subgoal goal.sfa goal.menv [g] Mg_negation
    | Ag_collection (g,c) -> 
	let (xpred, rfrag) = flatten_pred true c goal.sfa in
	let (lrules, lrfrag) = make_subgoal goal.sfa g.menv [g] 
	  (Mg_collection xpred) in
	  (lrules, rfrag @ lrfrag)
    | Ag_some (_, g) -> make_subgoal goal.sfa g.menv [g] Mg_find 
    | _ -> unreachable () in
    
  let flatten_rule rule = match rule.r_body with 
      Ar_flat goal -> let (rs, rf) = flatten_goal goal in rf::rs
    | Ar_horn_clause (_, head, body) -> 
       let (rules, brfrag) = flatten_goal body in 
       let (hspred, hsprfrag) = flatten_spred head rule.rl_sfa in
       let mode = get_pred_mode head.s_pred in
       let allout = all_out_mode head.s_pred in
       let r = 
	 (if allout then [] else [make_goal Mg_wait hspred mode rule.rl_sfa]) @
	 brfrag @ hsprfrag @ [make_goal Mg_add hspred mode rule.rl_sfa] in
	 r::rules
    | Ar_query pred -> 
       let (xpred, rfrag) = flatten_pred true pred rule.rl_sfa in
       let (pname, pargs) = pred2rep xpred in  
       let qspred = {sp_session = None; sp_pred = rep2pred 
	 (query_pred_name, A.append [|str2val pname|] pargs)} in
	 (if rfrag <> [] then 
	   rule_error rule.rl_sfa "Query predicates cannot invoke functions");
	 [[make_goal Mg_find {sp_session = None; sp_pred = xpred} (Some
	      (A.map (fun _ -> false) pargs, [Sk_zero;Sk_many], false))
	      rule.rl_sfa; make_goal Mg_add qspred None rule.rl_sfa]]
    | Ar_assertion (_, goal) ->
       let msg = Printf.sprintf "Assertion failed at %s" 
	 (string_of_sfa goal.sfa) in
       let fail_pred = {sp_session = None; sp_pred = rep2pred 
	   (assertion_failure_name, [|str2val msg|])} in
       let (rs, rf) = make_subgoal goal.sfa goal.menv [goal] Mg_negation in
	 (rf @ [make_goal Mg_add fail_pred None rule.rl_sfa])::rs
       
    in
  List.fold_left (fun rs ar -> (flatten_rule ar) @ rs) [] rules


(* Per-predicate stratification.
 * Create a dependency graph between predicate, abstracting each predicate by
 * its name (i.e. arguments are not considered). The result is a list of 
 * strata, where each stratum is a list of predicates. We ignore cycles
 * across negation/collections within a stratum here --- ordering them is
 * the responsibility of the stratification refinement pass.
 *
 *)

let debug_print_mismatched_addwait = register_debug "print_mismatched_addwait"
  "Print mismatched add-wait predicate pairs"

module OrderedInt = struct
  type t = int
  let compare (a:int) (b:int) = compare a b
end
module PredHashType = struct
  type t = string * int
  let equal (s1:string * int) (s2:string * int) = (s1 = s2)
  let hash = H.hash
end
module PredG = Graph.Make (OrderedInt)
module PredHash = Hashcons.Make (PredHashType)
let id2pred = PredHash.id2a
let pred2id = PredHash.a2id

let debug_print_strata = register_debug "print_strata"
  "Print strata after initial stratification"

let calculate_strata (rules :  ml_rule list) 
    : (int * (string * int, int) H.t) =
  let graph = PredG.create () in
    
  (* List of (add, wait) dependencies that don't unify with each other *)
  let mismatched_deps : (int * int) list ref = ref [] in

  (* Unique id numbers for add handlers or session adds *)
  let special_add_id : int ref = ref 0 in

  let add_node p = ignore (PredG.mk_node graph p) in
  let add_edge p0 p1 =
    let srcn = PredG.mk_node graph p0 in
    let tgtn = PredG.mk_node graph p1 in
      ignore (PredG.mk_edge graph srcn tgtn) in

  let add_goal_deps ((finds, waits) : int list * t_pred list) 
      (g : ml_goal) : int list * t_pred list =
    let (pname, pargs) = pred2rep g.mlg_spred.sp_pred in
      match g.mlg_kind with 
	| Mg_wait -> 
	    add_node (pred2id (pname, 0));
	    (finds, g.mlg_spred.sp_pred::waits)
	| Mg_add  -> 
	    if fst (pred2rep g.mlg_spred.sp_pred) <> "$query" then begin
	      let nid = 
		if g.mlg_spred.sp_session <> None || g.mlg_mode = None then
		  (incr special_add_id; !special_add_id) else 0 in
	      let pid = pred2id (pname, nid) in
		add_node pid;
		g.mlg_id <- nid;
		List.iter (fun wpred -> 
		  let (wpname, wpargs) = pred2rep wpred in
		  let wpid = pred2id (wpname, 0) in
		    if (g.mlg_spred.sp_session <> None || wpname <> pname 
			 || make_vmap pargs wpargs = None) then
		      mismatched_deps := (pid, wpid)::!mismatched_deps
		) waits;
		List.iter (fun depid -> add_edge depid pid) finds
	    end;
	    (finds, waits)
	| _ -> 
	    if g.mlg_spred.sp_session <> None || g.mlg_mode = None then 
	      (finds, waits) 
	    else 
	      let pid = pred2id (pname, 0) in
		add_node pid; 
		(pid::finds, waits) in
    
  let add_rule_deps (r : ml_goal list) : unit =
    ignore (List.fold_left add_goal_deps ([], []) r) in

  List.iter add_rule_deps rules;



  (* For each mismatched add->wait dependency, add extra edges indicating that
   * the added predicate depends on every predicate that could lead to a 
   * query of the wait predicate. This ensures that the add predicate is
   * stratified above every predicate that could lead to a change in the
   * magic set on which it depends. *)

  let rec dfs (visit: PredG.n -> unit) (visited: PredG.NodeSet.t) (n:PredG.n) =
    if PredG.NodeSet.mem n visited then
      visited 
    else
      (visit n;
       let visited = PredG.NodeSet.add n visited in
	 List.fold_left (dfs visit) visited (PredG.get_succs graph n)) in

  List.iter (fun (add, wait) ->
    if debug_print_mismatched_addwait () then
      IO.printf "Mismatched: Add %s %d after Wait %s %d\n" 
	(fst (id2pred add)) (snd (id2pred add))
	(fst (id2pred wait)) (snd (id2pred wait));
    ignore (dfs (fun n -> 
      let p = PredG.get_data graph n in
	if debug_print_mismatched_addwait () then
	  IO.printf "Mismatched: Adding extra dep edge %s %d -> %s %d\n" 
	    (fst (id2pred p)) (snd (id2pred p)) (fst (id2pred add))
	    (snd (id2pred add));
	add_edge p add
    ) PredG.NodeSet.empty (PredG.get_node graph wait))
  ) !mismatched_deps;

  let interscc = PredG.compute_scc graph in
  let sccmap : (int, int list) H.t = H.create 10 in
    PredG.iter_scc graph interscc (H.add sccmap);
    let intertpo = PredG.topsort graph interscc in
    let sccs = List.fold_right (fun rp scclist ->
        try let scc = H.find sccmap rp in scc::scclist
        with Not_found -> scclist) intertpo [] in
    let pred_stratum : (string * int, int) H.t = H.create 1000 in
      list_iteri (fun stratum scc ->
	if debug_print_strata () then 
	  IO.printf "SCC %d: %s\n" stratum 
	    (sep_string_of_list " " (fun p -> 
	      let (name, id) = id2pred p in name ^ " " ^ (string_of_int id)
	    ) scc);
	List.iter (fun pid -> H.add pred_stratum (id2pred pid) stratum) scc
      ) sccs;
      (List.length sccs, pred_stratum)

let stratify_rules (rules : ml_rule list) : ml_rule list array =
  let (nstrata, pred_stratum) = calculate_strata rules in
  let strata = A.make (nstrata + 1) [] in

  let stratify_goal (g : ml_goal) (rtails : (int * ml_goal list) list) =
    let gstratum = match g.mlg_spred.sp_session, g.mlg_kind with 
      | None, _
      | _, Mg_add ->
	  (let pname = fst (pred2rep g.mlg_spred.sp_pred) in
	     try H.find pred_stratum (pname, g.mlg_id) 
	     with Not_found -> if pname = "$query" then nstrata else -1)
      | Some _, _ -> -1 in

      match g.mlg_kind with 
	| Mg_add -> 
	    let (eq,neq) = List.partition (o ((=) gstratum) fst) rtails in
	    (match eq with 
	      | [] -> 
		  (gstratum, [{g with mlg_stratum = gstratum}])::neq
	      | [(_, rtail)] -> 
		  (gstratum, {g with mlg_stratum = gstratum}::rtail)::neq
	      | _ -> unreachable ()
	    )
	| _ -> List.map (fun (n,t) -> 
	    (n, {g with mlg_stratum = gstratum}::t)) rtails in

  let stratify_rule (r : ml_goal list) : unit = 
    let rtails = List.fold_right stratify_goal r [] in
      List.iter (fun (stratum, r) ->
	strata.(stratum) <- r::strata.(stratum)
      ) rtails in

    List.iter stratify_rule rules;
    strata

(* Magic sets transformation *)
let magic_pred_name pn = "mgc$" ^ pn

let magic_sets (rules:ml_rule list) : ml_rule list =
  let magic_sets_goal (g : ml_goal) (rtail : ml_goal list) : ml_goal list =
    let (pname, pargs) = pred2rep g.mlg_spred.sp_pred in
    if g.mlg_kind = Mg_wait then
      {g with mlg_kind = Mg_find ; mlg_spred = { g.mlg_spred with sp_pred = 
	  rep2pred (magic_pred_name pname, pargs)}}::rtail
    else if g.mlg_kind = Mg_add then g::rtail
    else
	match g.mlg_mode, g.mlg_spred.sp_session with
	  | None, _
	  | _, Some _ -> g::rtail
	  | Some (mode, det, always_magic), _ ->
	      if not always_magic && 
		forall_array ((=) false) mode then g::rtail else
		let mgc_args = 
		    A.mapi (fun i v -> if mode.(i) then v else anyval) pargs in
		let mgc_spred = {
		  sp_session = None;
		  sp_pred = rep2pred (magic_pred_name pname, mgc_args)
		} in
		  { g with mlg_kind = Mg_add; 
		    mlg_spred = mgc_spred }::g::rtail in
  let magic_sets_rule (r : ml_rule) : ml_rule =
    List.fold_right magic_sets_goal r [] in

  List.map magic_sets_rule rules


(* MLR to backend rule conversion *)
let mlr_to_backend (rules : ml_rule list) : t_rule list =
  let xlate_kind = function
    | Mg_add          -> Tp_add
    | Mg_find         -> Tp_find 
    | Mg_negation     -> Tp_negated
    | Mg_collection c -> Tp_collect c
    | _               -> unreachable () in
  let make_rpred kind spred priority stratum sfa = {
    r_priority = priority;
    r_kind     = xlate_kind kind;
    r_session  = spred.sp_session;
    r_pred     = spred.sp_pred;
    r_sfa      = sfa;
    r_stratum  = stratum;
  } in
  let xlate_goal (g:ml_goal) : t_rpred =
    make_rpred g.mlg_kind g.mlg_spred g.mlg_priority g.mlg_stratum g.mlg_sfa in

  let xlate_rule (r:ml_goal list) : t_rule =
    List.map xlate_goal r in

    List.map xlate_rule rules



(* Pretty printing support *)
open Pp
open Pputil

let ppRule goals = 
  fgrp (nest 4 (
    ppListSep (List.map (o text string_of_ml_goal) goals)
		   (text "," ^^ break)
    ^^ text "."
  )) 


let ppRules (rules : ml_goal list list) : doc =
  vgrp (ppListSep (List.map ppRule rules) break)

let debug_dump_after_mlr_conversion = register_debug 
  "dump_after_mlr_conversion" "Dump MLR after AST -> MLR conversion"
let debug_dump_after_mlr_stratification = register_debug 
  "dump_after_mlr_strat" "Dump MLR after stratification"
let debug_dump_after_mlr_magic_sets = register_debug 
  "dump_after_mlr_magicsets" "Dump MLR after the magic sets transformation"

let ast_to_spec ast =
  let mlr = ast_to_mlr ast in
  if debug_dump_after_mlr_conversion () then
    Pp.ppToFile stdout 72 (ppRules mlr);
  let strata = stratify_rules mlr in
  if debug_dump_after_mlr_stratification () then
    A.iteri (fun stratum rules ->
      IO.printf "\nStratum: %d\n" stratum;
      Pp.ppToFile stdout 72 (ppRules rules)
    ) strata;
  let strata = A.map magic_sets strata in
  if debug_dump_after_mlr_magic_sets () then
    A.iteri (fun stratum rules ->
      IO.printf "\nStratum: %d\n" stratum;
      Pp.ppToFile stdout 72 (ppRules rules)
    ) strata;
  A.map mlr_to_backend strata

let reset_mlr () = PredHash.clean ()

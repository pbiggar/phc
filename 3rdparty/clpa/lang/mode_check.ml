(*
 * Mode checking for CLPA programs
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
open Ast

module A = Array
module H = Hashtbl
module S = String
module IO = Streamio

(* Mode Checking *)
let union_menv m0 m1 = {
  bound = VarSet.union m0.bound m1.bound;
  used = VarSet.union m0.used m1.used; 
  noreuse = VarSet.union m0.noreuse m1.noreuse
}

exception Mode_error of string
let mode_error s = raise (Mode_error s)

let add_var mprev m x l =
  if VarSet.mem x mprev.noreuse then
    mode_error ("Can't reuse variable \'" ^ x ^ "\' at " ^ l)
  else { m with bound = VarSet.add x m.bound }

let has_function_mode pred =
  let rec is_function_mode margs =
    match margs with
      | [] -> false
      | [false] -> true
      | x::xs -> if x then is_function_mode xs else false in
    List.exists (fun (m,det) ->
      is_function_mode (A.to_list m) && det = [Sk_once]
    ) (get_all_modes pred)

(* check each non-ground value in v, marking as consumed any ground vars.
 * m is the environment for the goal currently being checked,
 * mprev indicates any variables bound or noreuse due to previous goals *)
let rec check_ground must_ground mprev m loc v =
  match v with
    | At_anyvar _ -> 
        if must_ground then mode_error ("Free wildcard \'_\' at " ^ loc) else m
    | At_var x ->
	if VarSet.mem x m.bound || VarSet.mem x mprev.bound then 
	  { m with used = VarSet.add x m.used }
	else if must_ground then
	  mode_error ("Free variable \'" ^ x ^ "\' at " ^ loc)
	else
	  add_var mprev m x loc	    
    | At_sum (_, args) ->
	A.fold_left (fun m av ->
          check_ground must_ground mprev m (string_of_ast_term v) av) m args
    | At_call p ->
	if has_function_mode p then
	  A.fold_left (fun m av ->
            check_ground true mprev m (string_of_ast_term v) av) m p.p_args
	else
	  mode_error ("Predicate '" ^ (mangle_name p.p_disambiguation) ^ 
                      "' used as function must have a mode with " ^
                      "last argument 'out' and a succeeds 'once' determinism")
    | _ -> m

(* most common ways of checking wildcards/variables *)
let must_ground = check_ground true 
let add_ground = check_ground false

(* check that a pred mode is matched by a name/args for a given operation *)
let check_find_mode mprev m pred mode =
  fold_array2 (fun m mv av -> check_ground mv mprev m (string_of_ast_pred pred)
    av) m mode pred.p_args
let check_wait_mode mprev m pred mode =
  fold_array2 (fun m mv av ->
    if mv then add_ground mprev m (string_of_ast_pred pred) av else m) m mode 
    pred.p_args
let check_add_mode mprev m pred mode =
  fold_array2 (fun m mv av ->
    (if mv then add_ground else must_ground) mprev m (string_of_ast_pred pred)
      av) m mode pred.p_args

(* check that a find operation on a pred is matched by at least one mode
 * for that pred *)
let check_all_find_modes mprev m pred =
  let rec check_list mprev m modes = match modes with 
      [] -> failwith "Missing mode"
    | [mode,_] -> check_find_mode mprev m pred mode
    | (mode,_)::xs -> try check_find_mode mprev m pred mode
                  with Mode_error _ -> check_list mprev m xs in
  check_list mprev m (get_all_modes pred)

let bad_pred name msg = mode_error ("Predicate " ^ name ^ msg)

(* check an external session access through pred 'name' for mode errors *)
let check_session_mode sp mprev = match sp.s_session with
  | Some s ->
      let psym = sp.s_pred.p_disambiguation in
      if (H.find predicates psym).pd_kind <> Pk_regular && 
        not (List.exists ((=) sp.s_pred.p_name) sess_handlers) then
        bad_pred sp.s_pred.p_name " cannot be used with an external session";
      let (_,sargs,spstr) = pred_info s in
        A.fold_left (fun m sav ->
          must_ground mprev m spstr sav) empty_menv sargs
  | None ->
      if List.exists ((=) sp.s_pred.p_name) sess_handlers then
        bad_pred sp.s_pred.p_name " must be used with an external session";
      empty_menv

(* report an error if a set is non-empty *)
let check_empty_set sfa msg =
  VarSet.iter (fun v -> rule_warning sfa ("Variable " ^ v ^ msg))

(* Mode check a rule by doing a forward scan over the goals keeping track
 * of how each variable has been used so far.
 * Also checks for:
 * - adding preds with find handlers
 * - finding preds with add handlers
 * - variables appearing only once
 *)
let mode_check rule =
  (* Mode check a goal, given a mode environment which provides a list
   * of bound and non-reusable variables. The result of mode checking is stored
   * in the menv field of the goal. *)
  let rec mode_check_goal mprev goal = try
    match goal.body with 
      Ag_conjunction subgoals -> 
        goal.menv <- List.fold_left (fun m conjunct ->
            mode_check_goal (union_menv mprev m) conjunct ;
            union_menv m conjunct.menv) empty_menv subgoals
    | Ag_disjunction subgoals -> 
        List.iter (mode_check_goal mprev) subgoals;
        let boundlist   = List.map (fun g -> g.menv.bound)   subgoals in
        let usedlist    = List.map (fun g -> g.menv.used)    subgoals in
        let noreuselist = List.map (fun g -> g.menv.noreuse) subgoals in
        let anybound = List.fold_left VarSet.union VarSet.empty boundlist in
        let allbound = List.fold_left VarSet.inter anybound boundlist in
        let used     = List.fold_left VarSet.union VarSet.empty usedlist in
        let noreuse  = List.fold_left VarSet.union VarSet.empty noreuselist in
          List.iter (fun g ->
            check_empty_set g.sfa
              " is bound by some disjunction subgoals but not used"
              (VarSet.diff (VarSet.diff g.menv.bound g.menv.used) allbound))
            subgoals;
          goal.menv <- {
            bound = allbound;
            used = VarSet.diff used (VarSet.diff anybound allbound);
            noreuse = VarSet.union noreuse (VarSet.diff anybound allbound);
          }
    | Ag_find spred ->
        if (get_pred_def spred.s_pred).pd_kind = Pk_add_handler then
          bad_pred spred.s_pred.p_name " cannot be used in find operations";
        let msp = check_session_mode spred mprev in 
          goal.menv <- check_all_find_modes mprev msp spred.s_pred
    | Ag_wait pred ->
        let pd = get_pred_def pred in
	  pd.pd_magic <- true;
	  if pd.pd_kind = Pk_add_handler then
            bad_pred pred.p_name " cannot be used in find operations";
          goal.menv <- check_wait_mode mprev empty_menv pred 
            (fst (get_mode pred))
    | Ag_add spred ->
        let kind = (get_pred_def spred.s_pred).pd_kind in
	if kind <> Pk_regular && kind <> Pk_add_handler then
          bad_pred spred.s_pred.p_name " cannot be used in add operations";
        let msp = check_session_mode spred mprev in 
        let mode = get_mode spred.s_pred in
        let ma = check_add_mode mprev msp spred.s_pred (fst mode) in
          check_empty_set goal.sfa " is bound but not used within add"
            (VarSet.diff (VarSet.diff ma.bound msp.bound) ma.used);
          goal.menv <-  {
            bound = msp.bound;
            used = ma.used;
            noreuse = VarSet.union ma.noreuse (VarSet.diff ma.bound msp.bound);
          }
    | Ag_negation subgoal ->
        mode_check_goal mprev subgoal;
        check_empty_set subgoal.sfa " is bound but not used by negation"
          (VarSet.diff subgoal.menv.bound subgoal.menv.used);
        goal.menv <- {
          bound = VarSet.empty;
          used = subgoal.menv.used;
          noreuse = VarSet.union subgoal.menv.bound subgoal.menv.noreuse;
        }
    | Ag_collection (lambda, cp) ->
        mode_check_goal mprev lambda;
        let ml = union_menv mprev lambda.menv in
        let mode = get_mode cp in
        let mcoll = check_find_mode ml empty_menv cp (fst mode) in
        check_empty_set lambda.sfa " is bound but not used by collection"
          (VarSet.diff lambda.menv.bound 
            (VarSet.union lambda.menv.used mcoll.used));
        goal.menv <- {
          bound = mcoll.bound;
          used = VarSet.union lambda.menv.used mcoll.used;
          noreuse = VarSet.union lambda.menv.bound lambda.menv.noreuse;
        }
    | Ag_some (vs, qgoal) ->
        mode_check_goal mprev qgoal;
        let vset = varset_of_list vs in
        goal.menv <- {
          bound = VarSet.diff qgoal.menv.noreuse vset;
          used = VarSet.diff qgoal.menv.used vset;
          noreuse = VarSet.diff qgoal.menv.noreuse vset;
        }
    | _ -> unreachable ()
    with Mode_error err -> rule_error goal.sfa err in
  (* Mode check a rule *)
  let m = match rule.r_body with 
      Ar_flat goal ->
        (* check last predicate is always an add *)
        let rec check_last_add goal =
          match goal.body with
              Ag_add _ -> ()
            | Ag_conjunction goals ->
                check_last_add (List.hd (List.rev goals))
            | _ ->
                rule_warning goal.sfa "Last predicate in goal is not an add" in
        check_last_add goal;
        mode_check_goal empty_menv goal;
        goal.menv
    | Ar_horn_clause (_, head, body) -> (try
	let hdef = get_pred_def head.s_pred in
        let mode = fst (get_mode head.s_pred) in
	if exists_array ((=) true) mode then begin
	  (if head.s_session <> None then
	    mode_error 
	      "Rule head with external session cannot have 'in' arguments");
	  hdef.pd_magic <- true
	end;
        let mqhead =
          check_wait_mode empty_menv empty_menv head.s_pred mode in
        mode_check_goal mqhead body;
        let munion = union_menv mqhead body.menv in
        let munion = union_menv munion 
	  (check_session_mode head munion) in
        let munion = check_add_mode empty_menv munion head.s_pred mode in
          munion
       with Mode_error err -> rule_error body.sfa err)
    | Ar_query p -> empty_menv
    | Ar_assertion (_, goal) ->
        mode_check_goal empty_menv goal;
        goal.menv in
  check_empty_set rule.rl_sfa " is bound but not used in rule"
    (VarSet.diff m.bound m.used)

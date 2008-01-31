(*
 * Type checking for logic programs.
 * Largely inspired by the type-checking algorithm of Mycroft-O'Keefe, which
 * in turn is similar to Hindley-Milner typing.
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

exception Type_error of string

type tenv = {
  unifier: t_type_vmap;

  (* In each type environment we record the set of disambiguation choices that
   * we make. On completion of type-checking if we have found an unambiguous
   * type environment, then we update each predicate with its disambiguation *)
  choices: (ast_pred * t_dsymbol) list;
}

(* Type check an AST rule *)
let type_check rule =
  (* Unique ID number used to supply fresh type variable names *)
  let renames : int ref = ref 0 in
  (* Produce a function that replaces each unique type variable in
   * a type with a fresh variable *)
  let next_rename () : t_type_renaming =
    let nstr = (string_of_int !renames) ^ "%" in
      incr renames; rename_type nstr in
  (* Skolemize a type, removing all type variables. leave vt_any alone as
   * this will only be used for special handler predicates like print() *)
  let rec skolem_type typ =
    try let x = rev_vt_var typ in
      make_type (x ^ "$") [||]
    with Unexpected _ -> try let (n,args) = break_type typ in
      make_type n (A.map skolem_type args)
    with Unexpected _ -> typ in

  let type_unify (tenvs:tenv list) (x:t_val_type) (y:t_val_type) =
    map_filter (fun e -> 
      match add_type_vmap e.unifier x y with
        | None -> None
        | Some u -> Some {e with unifier = u}
    ) tenvs in
  let type_unify_lists (tenvs:tenv list) (atypes:t_val_type list) 
      (tylists:t_val_type list list) : (tenv list list) =
    List.map (List.fold_left2 type_unify tenvs atypes) tylists in
  let type_args_unify tenvs pname pargs rename (atypes:t_val_type list) 
      (targsl:t_val_type array list) =
    let targsl' = List.map (fun targsa ->
      let targsa' = A.map (o rename remove_aliases) targsa in
      let ntargs = A.length targsa' in  
        match is_pred_vargs targsa' with
          | None -> A.to_list targsa'
          | Some (req,opt) -> (A.to_list req) @
              (repeat opt ((List.length atypes) - ntargs + 1))
    ) targsl in
    let tenvs' = type_unify_lists tenvs atypes targsl' in
      if List.for_all ((=) []) tenvs' then begin
        (* try to find simple type error: one environment, mismatched types *)
        (match tenvs,targsl' with
             [env],[targs] ->
               for i = 0 to A.length pargs - 1 do
                 if add_type_vmap env.unifier (List.nth atypes i) (List.nth targs i) = None then
                   raise (Type_error (Printf.sprintf
                     "%s %s for %s: Expected %s, Inferred %s\n"
                     "Type mismatch in argument" (string_of_ast_term pargs.(i)) pname
                     (string_of_type (List.nth targs i))
                     (string_of_type (vmap_type env.unifier (List.nth atypes i)))))
               done;
           | _ -> ());
        raise (Type_error (Printf.sprintf
          "%s %s\n Expected:\n  %s\n Inferred:\n  %s\n"
          "Type mismatch in arguments for" pname 
          (sep_string_of_list "\n  "
              (sep_string_of_array "," string_of_type) targsl)
          (sep_string_of_list "\n  "
              (fun e -> 
                sep_string_of_list "," 
                  (o string_of_type (vmap_type e.unifier)) atypes) tenvs)))
      end else tenvs' in
  let type_pred_unify tenvs p atypes is_add =
    let rename = p.p_type_renaming in
    let defs = (H.find symbols p.p_name).s_disambiguations in
    let targs = List.map 
      (fun da -> 
        let targs = (H.find predicates da).pd_args in
          if is_add then A.map (o skolem_type rename) targs else targs
      ) defs in       
    let tenvsl = type_args_unify tenvs p.p_name p.p_args rename atypes targs in
      List.fold_left2 (fun acc da tenvs ->
        (List.map (fun e -> {e with choices = (p, da)::e.choices}) tenvs) @
          acc) [] defs tenvsl in

  (* Infer a type for a term in a set of type enviroments. Returns a 
   * (type, updated type environments) tuple. Note that only one type
   * is returned, although it may mean completely different things in each
   * type environment. If no type can be inferred for the term, then
   * a Type_error exception is thrown *)
  let rec type_infer_term v tenvs =
    match v with 
      | At_anyvar aname -> (vt_var ("_" ^ aname), tenvs)
      | At_var name -> (vt_var name, tenvs)
      | At_string _ -> (vt_str, tenvs)
      | At_int _    -> (vt_int, tenvs)
      | At_float _  -> (vt_flt, tenvs)
      | At_sum (name, args) ->
          let (itargs,tenvs) = type_infer_term_list (Array.to_list args) 
            tenvs in
          let ((_, targs),sumtyp) = H.find sumvalues name in
          let rename = next_rename() in
          let tenvs' = List.hd (type_args_unify tenvs name args rename itargs 
                                   [targs]) in
            (rename (remove_aliases sumtyp), tenvs')
      | At_call p ->
           let (itargs,tenvs) = type_infer_term_list (Array.to_list p.p_args) 
            tenvs in
          let rename = next_rename() in
          let rettyp = rename (vt_var "%RV") in
            p.p_type_renaming <- rename; 
            (rettyp, type_pred_unify tenvs p (itargs @ [rettyp]) false)
  and type_infer_term_list tenvs terms = 
    (map_foldl type_infer_term) tenvs terms in

  let type_check_pred tenvs pred is_add sfa =
    try let (itargs,tenvs) = type_infer_term_list (Array.to_list pred.p_args) 
      tenvs in
      pred.p_type_renaming <- next_rename();
      type_pred_unify tenvs pred itargs is_add
    with Type_error err -> rule_error sfa err in

  let type_check_spred tenvs sp is_add sfa =
    let tenvs' = match sp.s_session with
      | Some sp -> type_check_pred tenvs sp is_add sfa
      | None -> tenvs in
      type_check_pred tenvs' sp.s_pred is_add sfa in
  (* Walk through a goal, maintaining a set of type environments.
   * For add operations the types must be at least as general as the prototype,
   * For find operations the types must be unifiable with the prototype *)
  let rec type_check_goal tenv goal =
    match goal.body with
        Ag_conjunction goals -> List.fold_left type_check_goal tenv goals
      | Ag_disjunction goals -> List.fold_left type_check_goal tenv goals
      | Ag_find spred -> type_check_spred tenv spred false goal.sfa
      | Ag_wait  pred ->  type_check_pred tenv pred false goal.sfa
      | Ag_add   spred -> type_check_spred tenv spred true goal.sfa
      | Ag_negation goal -> type_check_goal tenv goal
      | Ag_implies (g1, g2) -> type_check_goal (type_check_goal tenv g1) g2
      | Ag_some (_, goal) 
      | Ag_all  (_, goal) -> type_check_goal tenv goal
      | Ag_collection (cgoal, cpred) ->
          let tenv' = type_check_goal tenv cgoal in
          type_check_pred tenv' cpred false goal.sfa in
  let empty_tenv = [{choices = []; unifier = type_vmap_empty}] in
  let tenvs = match rule.r_body with 
      Ar_flat goal             -> 
        type_check_goal empty_tenv goal
    | Ar_horn_clause (_, head, body) -> 
        let tenv = type_check_goal empty_tenv body in
        type_check_spred tenv head true rule.rl_sfa
    | Ar_query pred -> 
        type_check_pred empty_tenv pred false rule.rl_sfa
    | Ar_assertion (nameo, goal) ->
        type_check_goal empty_tenv goal in
    match tenvs with 
      | [] -> failwith "Internal error: empty set of type environments"
      | [tenv] -> 
          (* Add the disambiguation information we inferred to predicates,
           * and save the unifier for use by Coq extraction. *)
          List.iter (fun (p, d) -> p.p_disambiguation <- d) tenv.choices;
          rule.r_type_vmap <- tenv.unifier
      | t1::t2::_ -> 
          (* Iterate through the choices we made until we come to a choice that
           * differs between the two enviroments, which we can report as an
           * unresolved ambiguity *)
          let (c1,c2) = find2 (fun c1 c2 -> (snd c1) <> (snd c2)) 
            (List.rev t1.choices) (List.rev t2.choices) in
          rule_error rule.rl_sfa ("Unresolved ambiguity of '" ^ 
                                    (fst c1).p_name ^
           "'; possible choices include: " ^ (mangle_name (snd c1)) ^ " and " ^
          (mangle_name (snd c2)))



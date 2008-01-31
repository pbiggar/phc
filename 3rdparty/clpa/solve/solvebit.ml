(*
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
 *)

(* SAT-based boolean constraint solving *)

open Clpautil
open Flags
open Spec

module H = Hashtbl
module V = Vector
module IO = Streamio

open Biteval

let eqvar_gid : int ref = ref (-1)

type t_sat_var     = int
type t_sat_literal = int
type t_sat_clause  = t_sat_literal list

(* Convert SAT variables to positive and negative SAT literals *)
let lit_pos (v : t_sat_var) : t_sat_literal = 2*v
let lit_neg (v : t_sat_var) : t_sat_literal = 2*v + 1

exception Timed_out
type t_sat_solver = {
  ss_name         : string;     (* Name of this SAT Solver *)
  ss_priority     : int;        (* Preference position of this SAT solver. 
                                   Higher is more preferred *)

  ss_reset        : unit -> unit;

  ss_get_var      : t_val -> t_sat_var;
  ss_add_clause   : int -> t_sat_clause -> unit;
  
  ss_sat          : unit -> bool;
  ss_sat_asn      : unit -> (t_val, bool) H.t option;

  ss_new_clause_group    : unit -> int;
  ss_remove_clause_group : int -> unit;
}

(* SAT Solver registration *)
let sat_solver : t_sat_solver ref = ref {
  ss_name         = "dummy_satsolver";
  ss_priority     = -1;
  ss_reset        = (fun _ -> ());
  ss_get_var      = (fun _  -> failwith "get_var called on dummy SAT solver");
  ss_add_clause   = 
    (fun _ _  -> failwith "add_clause called on dummy SAT solver");
  ss_sat          = (fun _  -> failwith "sat called on dummy SAT solver");
  ss_sat_asn      = (fun _  -> failwith "sat_asn called on dummy SAT solver");
  ss_new_clause_group = 
    (fun _  -> failwith "num_contexts called on dummy SAT solver");
  ss_remove_clause_group = 
    (fun _  -> failwith "push_context called on dummy SAT solver");
}

let register_sat_solver (s:t_sat_solver) : unit =
  if   s.ss_priority > !sat_solver.ss_priority then (
    sat_solver := s ;
    eqvar_gid := s.ss_new_clause_group ()
  ) else ()

let reset_fns : (unit -> unit) list ref = ref []
let reset() = List.iter (fun f -> f()) !reset_fns

(* Satisfiability *)

(* Satisfying assignments constructed from SAT *)
type bassign = int
let tbl_assigns : (t_val,bool) H.t V.t = V.create 10

(* Per-bval solver results and solve times (in seconds) *)
let tbl_results : (bval,(bassign option)*float) H.t = H.create 10

let _ = prepend reset_fns (fun () ->
  !sat_solver.ss_reset ();
  eqvar_gid := !sat_solver.ss_new_clause_group ();
  V.clear tbl_assigns;
  H.clear tbl_results)

let debug_commit_cnf = register_debug "sat_commit_cnf"
  "Print committed CNF formulas"

let commit_cnf gid cnf =
  let rec process_dfs = function
      df0::df1::dfxs when df0 = df1 -> process_dfs (df1::dfxs)
    | df::dfxs ->
        if debug_commit_cnf() then
          IO.printf "commit_cnf: %s\n" (string_of_df df);
        let rec filter_df res = function
            (x0,p0)::(x1,p1)::xpxs when x0 = x1 ->
              if p0 = p1 then filter_df res ((x1,p1)::xpxs) else []
          | (x,p)::xpxs ->
              filter_df ((x,p)::res) xpxs
          | [] -> res in
        let compare_xp (x0,_) (x1,_) = compare x0 x1 in
        let df = filter_df [] (list_sort compare_xp df) in
          if df <> [] then begin
            let df = list_map
              (fun (x,p) -> let zx = !sat_solver.ss_get_var x in
                 if p then lit_pos zx else lit_neg zx) df in
            !sat_solver.ss_add_clause gid df 
          end;
          process_dfs dfxs
    | [] -> () in
  match cnf with
      Some dfs -> process_dfs (list_sort compare dfs)
    | None -> failwith "Can't commit trivially false CNF"

let debug_sat_solve = register_debug "sat_solve"
  "Print result of each SAT query"

let sat_solve bv =
  let start = Sys.time() in
  let bv = simplify bv in
    try fst (H.find tbl_results bv)
    with Not_found ->
      if debug_sat_solve() then
        IO.printf "sat: %s\n" (string_of_bval !print_level bv);
      let res = match get_cnf true bv with
          None     -> None 
        | Some []  -> Some (V.append tbl_assigns (H.create 10)) 
        | Some cnf ->
            let gid = !sat_solver.ss_new_clause_group () in
            List.iter (commit_cnf !eqvar_gid) (get_uncommitted_cnfs ());
            commit_cnf gid (Some cnf);
            let res =
              try match !sat_solver.ss_sat_asn () with
                  Some assign -> Some (V.append tbl_assigns assign)
                | None        -> None
              with Timed_out ->
                !sat_solver.ss_remove_clause_group gid;
                pred_unexpected "SAT solver timed out" in
            !sat_solver.ss_remove_clause_group gid; res in
      if debug_sat_solve() then
        IO.printf "result: %s\n" (if res <> None then "SAT" else "UNSAT");
      let elapsed = Sys.time() -. start in
        H.add tbl_results bv (res,elapsed); res
let sat_solve = make_track_1 "sat_solve" sat_solve

let apply_assignment av v =
  let assign = V.get tbl_assigns av in
  let cache = H.create 10 in
  let rec evaluate v = match get_bval v with
      Bb_const b -> b
    | Bb_var x -> (try H.find assign x with Not_found -> false)
    | Bb_unop(Bo_eq,v) -> evaluate v
    | Bb_unop(Bo_not,v) -> not (evaluate v)
    | Bb_binop(op,vals) ->
        try H.find cache v
        with Not_found ->
          let combfn = if op = Bo_and then (&&) else (||) in
          let res = list_fold_right (o combfn evaluate)
                      (List.tl vals) (evaluate (List.hd vals)) in
            H.add cache v res; res in
  evaluate v

(* Spec integration *)

let vt_bassign typ = make_type "bval_asn" [|typ|]
let vk_bassign = register_val_kind {
  vki_tostring = (fun _ a -> "ASN#" ^ (string_of_int a));
  vki_compare = compare;
  vki_dump = (fun _ _ -> failwith "Cannot dump bassign");
  vki_load = (fun _ -> failwith "Cannot load bassign");
}

let val2bassign = val2cst vk_bassign
let bassign2val = cst2val vk_bassign

(* Packages *)

let add_handlers = ref []
let find_handlers = ref []

let vt_xvar = vt_var "X"
let vt_xbval = vt_bval vt_xvar
let vt_xbassign = vt_bassign vt_xvar

let _ = prepend find_handlers
  (("#sat",[|vt_bval vt_any|]),[[|true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     if sat_solve (val2bval args.(0)) <> None then [name,args] else [])

let _ = prepend find_handlers
  (("#satasn",[|vt_xbval;vt_xbassign|]),[[|true;false|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     let res = sat_solve (val2bval args.(0)) in
     match res with
         None -> []
       | Some ar -> 
         [name,[|args.(0);bassign2val ar|]])

let _ = prepend find_handlers
  (("#asng",[|vt_xbassign;vt_xbval|]),[[|true;true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     let asn = val2bassign args.(0) in
     if apply_assignment asn (val2bval args.(1)) then [name,args] else [])

let stats_sat_counts = register_stats "sat_counts"
  "Summarize SAT solver problems and times"

let write_sat_counts() =
  if stats_sat_counts() then begin
    (* keep track of (total queries, total time, maximum time) *)
    let (q,t,m) = H.fold (fun _ (_,time) (q,t,m) ->
                            (q+1,t+.time,max m time)) tbl_results (0,0.,0.) in
      IO.printf "SAT Solving Stats:\n";
      IO.printf "  Count: %d\n" q;
      if q <> 0 then begin
        let avg = t /. (float_of_int q) in
          IO.printf " Total:   %.3f\n" t;
          IO.printf " Average: %.3f\n" avg;
          IO.printf " Max:     %.3f\n" m
      end
  end

let _ = register_package { empty_package with
  p_name = "solve_sat";
  p_writeout = write_sat_counts;
  p_reset = reset;
  p_add_handlers = !add_handlers;
  p_find_handlers = !find_handlers;
  p_abstypes = [vt_xbassign];
}

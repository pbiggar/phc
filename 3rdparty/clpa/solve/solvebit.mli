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

type bassign
val apply_assignment : bassign -> Biteval.bval -> bool

(* Spec integration *)

(* type of bassigns, polymorphic in the type of the original formula *)
val vt_bassign : Spec.t_val_type -> Spec.t_val_type

val val2bassign : Spec.t_val -> bassign
val bassign2val : bassign -> Spec.t_val


(* SAT solver interface *)
type t_sat_var     = int
type t_sat_literal = int 
type t_sat_clause  = t_sat_literal list

exception Timed_out
type t_sat_solver = {
  ss_name         : string;     (* Name of this SAT Solver *)
  ss_priority     : int;        (* Preference position of this SAT solver. 
                                   Higher is more preferred *)

  (* Completely reset the SAT solver, deleting all variables, clause groups 
   * and clauses *)
  ss_reset        : unit -> unit;

  ss_get_var      : Spec.t_val -> t_sat_var;
  ss_add_clause   : int -> t_sat_clause -> unit;

  ss_sat          : unit -> bool;
  ss_sat_asn      : unit -> (Spec.t_val, bool) Hashtbl.t option;

  ss_new_clause_group    : unit -> int;
  ss_remove_clause_group : int -> unit;
}

val register_sat_solver : t_sat_solver -> unit

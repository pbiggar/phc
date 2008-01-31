(*
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

(* minisat.ml -- OCaml interface to MiniSAT *)

(* Based on the OCaml zChaff interface by Yichen Xie (yxie@cs.stanford.edu)
 * Based on Andy Chou's implementation for an older version of zChaff. *)

type satsolver

type status =
    Unsatisfiable
  | Satisfiable
  | TimedOut

let stt2str stt =
  match stt with
      Unsatisfiable -> "Unsatisfiable"
    | Satisfiable   -> "Satisfiable"
    | TimedOut      -> "TimedOut"

type var = int

external new_solver: unit -> satsolver = "ms_init"
external new_var : satsolver -> int = "ms_new_var"

external add_clause: satsolver -> int -> int list -> int -> unit 
    = "ms_add_clause"

external new_clause_group : satsolver -> int  = "ms_new_clause_group"
external remove_clause_group : satsolver -> int -> unit = 
    "ms_remove_clause_group"

external set_time_limit: satsolver -> int -> unit = "ms_set_time_limit"

external solve: satsolver -> status = "ms_solve"
external get_assign: satsolver -> int -> int = "ms_get_assign"

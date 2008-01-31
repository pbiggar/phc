(*
 * Authors:
 *   Yichen Xie  <yxie@cs.stanford.edu>
 *
 * Copyright (c) 2004,
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

(* zchaff.ml -- ocaml interface to zchaff
 * based on andy chou's implementation for an older version of zchaff
 *)

type satm

type status =
    Undetermined
  | Unsatisfiable
  | Satisfiable
  | TimedOut
  | MemOut
  | Aborted

let stt2str stt =
  match stt with
      Undetermined  -> "Undetermined"
    | Unsatisfiable -> "Unsatisfiable"
    | Satisfiable   -> "Satisfiable"
    | TimedOut      -> "TimedOut"
    | MemOut        -> "MemOut"
    | Aborted       -> "Aborted"

type var = int

external init: unit -> satm = "zc_init"
external version: unit -> string = "zc_version"
external release: satm -> unit = "zc_release"
external set_nvars: satm -> int -> unit = "zc_set_nvars"
external add_var: satm -> int = "zc_add_var"
external reset: satm -> unit = "zc_reset"

external enable_var_branch: satm -> int -> unit = "zc_enable_var_branch"
external disable_var_branch: satm -> int -> unit = "zc_disable_var_branch"

external add_clause_with_gid: satm -> int list -> int -> int -> unit 
  = "zc_add_clause"

let add_clause satm list len = add_clause_with_gid satm list len 0

external delete_clause_group : satm -> int -> unit = "zc_del_clause_group"
external merge_clause_group: satm -> int -> int -> unit 
  = "zc_merge_clause_group"

external alloc_clause_gid : satm -> int = "zc_alloc_clause_gid"

external is_set_clause_gid : satm -> int -> int -> bool 
  = "zc_is_set_clause_gid"
external set_clause_gid : satm -> int -> int -> unit = "zc_set_clause_gid"
external clear_clause_gid: satm -> int -> int -> unit = "zc_clear_clause_gid"

external get_volatile_gid: satm -> int = "zc_get_volatile_gid"
external get_global_gid: satm -> int = "zc_get_global_gid"

external set_time_limit: satm -> float -> unit = "zc_set_time_limit"
external set_mem_limit: satm -> int -> unit = "zc_set_mem_limit"

external solve: satm -> status = "zc_solve"
external get_assign: satm -> int -> int = "zc_get_assign"

external set_randomness: satm -> int -> unit = "zc_set_randomness"
external set_randseed: satm -> int -> unit = "zc_set_randseed"

external mem_usage: satm -> int = "zc_mem_usage"
external cpu_time: satm -> float = "zc_cpu_time"

external num_literals: satm -> int = "zc_num_literals"
external num_clauses: satm -> int = "zc_num_clauses"
external num_vars: satm -> int = "zc_num_vars"
external num_decisions: satm -> int = "zc_num_decisions"

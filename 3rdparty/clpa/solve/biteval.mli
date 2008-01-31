(*
 * Authors:
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

type bval = int

type unop =
    Bo_eq
  | Bo_not

type binop =
    Bo_and
  | Bo_or

type bbit =
    Bb_const of bool
  | Bb_var of Spec.t_val  (* abstract leaf *)
  | Bb_unop of unop * bval
  | Bb_binop of binop * bval list

val string_of_bval : int (* depth limit *) -> bval -> string

(* Spec integration *)

val compare_bval : bval -> bval -> int

val dump_bval : Streamio.t_dump_fn -> bval -> unit
val load_bval : Streamio.t_load_fn -> bval

val val2bval : Spec.t_val -> bval
val bval2val : bval -> Spec.t_val

(* type of bvals, polymorphic in the leaf type *)
val vt_bval : Spec.t_val_type -> Spec.t_val_type

(* CNF formulas *)

(* disjunctive form: a | ~b | c *)
type df = (Spec.t_val * bool) list

(* conjunctive normal form: (a | ~b) & (~c | ~d). None indicates false *)
type cnf = df list option

val string_of_df : df -> string
val string_of_cnf : cnf -> string

(* Bit value construction *)

val btrue : bval
val bfalse : bval

(* all simplifications of priority at most the specified level will be used.
 * 0 is no simplification, increasing uses more expensive strategies *)
type simplify_level = int

val get_level : bval -> simplify_level
val get_bval : bval -> bbit

val add_var : Spec.t_val -> bval
val add_unop : simplify_level -> unop -> bval -> bval
val add_binop : simplify_level -> binop -> bval list -> bval

(* apply equivalence-preserving simplifications according to the levels on
 * each bit to yield a new bit value *)
val simplify : bval -> bval

(* accumulate information on the abstract leaf variables of a given bval
 * according to the given function *)
val extract_bval : bval -> (Spec.t_val -> 'a list) -> 'a list

(* Evaluation *)

val get_cnf : bool -> bval -> cnf

type eqvar
val bval2eqvar : Spec.t_val -> eqvar

(* gets and clears all uncommitted cnfs *)
val get_uncommitted_cnfs : unit -> cnf list

(* gets the true/false definition CNFs for a given eqvar *)
val get_eqvar_cnfs : eqvar -> cnf * cnf

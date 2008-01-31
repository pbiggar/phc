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

(* stp.ml
 * OCaml interface to Vijay Ganesh's SAT-based Theorem Prover (STP) *)

(* The type of STP boolean expressions *)
type bexpr

(* The type of STP bitvector expressions *)
type bv

(* The type of STP counterexamples *)
type counterexample

external vc_reset : unit -> unit = "mlstp_vc_reset"

(* Push a checkpoint onto the STP context stack *)
external vc_push : unit -> unit = "mlstp_vc_push"
external vc_pop  : unit -> unit = "mlstp_vc_pop"

(* Assert a formula in the current solver context *)
external vc_assert : bexpr -> unit = "mlstp_vc_assert"

(* Test an expression for validity *)
external vc_query : bexpr -> bool = "mlstp_vc_query"

(* Fetch the counterexample from a current invalid context. It is an error
 * to call this operation any time except immediately after a failing
 * validity query. It is however possible to inspect the result counterexample
 * at any later time. *)
external vc_get_counterexample: unit -> counterexample 
  = "mlstp_get_counterexample"

external vc_get_bexpr_from_counterexample: counterexample -> bexpr -> bexpr
  = "mlstp_get_term_from_counterexample"
external vc_get_bv_from_counterexample: counterexample -> bv -> bv
  = "mlstp_get_term_from_counterexample"

external vc_print_counterexample : unit -> unit = "mlstp_print_counterexample"

(* Three-valued logical bit (trit) *)
type trit =
    False
  | True
  | Unknown 

external vc_get_bval : bexpr -> trit = "mlstp_get_bval" 

(* Boolean operations *)
external b_newvar : string -> bexpr = "mlstp_bvar_new"

(* True and false constants *)
external b_true  : unit -> bexpr = "mlstp_true"
external b_false : unit -> bexpr = "mlstp_false"

external b_not     : bexpr -> bexpr = "mlstp_lnot"

external b_and     : bexpr -> bexpr -> bexpr = "mlstp_land"
external b_or      : bexpr -> bexpr -> bexpr = "mlstp_lor"
external b_implies : bexpr -> bexpr -> bexpr = "mlstp_limplies"
external b_iff     : bexpr -> bexpr -> bexpr = "mlstp_liff"

external b_ite     : bexpr -> bexpr -> bexpr -> bexpr = "mlstp_lite"

external string_of_bexpr   : bexpr -> string = "mlstp_string_of_expr"

(* Bitvector operations *)

external bv_newvec      : string -> (* # bits *) int -> bv = "mlstp_bv_new"
external bv_from_int    : (* # bits *) int -> int -> bv = "mlstp_bv_from_int"
external bv_from_bexpr  : bexpr -> bv = "mlstp_bv_from_bexpr"
external bv_nbits       : bv -> int = "mlstp_bv_nbits"
external string_of_bv   : bv -> string = "mlstp_string_of_expr2"
external bv_concat : bv -> bv -> bv = "mlstp_bv_concat"
external bv_extract : bv -> (* high bit # *) int -> (* low bit # *) int -> bv
  = "mlstp_bv_extract"
external bv_bit_extract : bv -> (* bit # *) int -> bexpr = "mlstp_bv_bit_extract"

(* Bitwise operations *)
external bv_ite : bexpr -> bv -> bv -> bv = "mlstp_bv_ite"

external bv_and    : bv -> bv -> bv = "mlstp_bv_and"
external bv_or     : bv -> bv -> bv = "mlstp_bv_or"
external bv_xor    : bv -> bv -> bv = "mlstp_bv_xor"
external bv_not    : bv -> bv       = "mlstp_bv_not"
external bv_lshift_const : bv -> int -> bv = "mlstp_bv_lshift_const"
external bv_rshift_const : bv -> int -> bv = "mlstp_bv_rshift_const"
external bv_lshift : int -> bv -> bv -> bv = "mlstp_bv_lshift"
external bv_srshift : int -> bv -> bv -> bv = "mlstp_bv_srshift"
external bv_urshift : int -> bv -> bv -> bv = "mlstp_bv_rshift"


let rec bv_from_big_int bits ival = 
  if bits <= 8 then
    bv_from_int bits (Big_int.int_of_big_int ival)
  else
    let (q,r) = Big_int.quomod_big_int ival (Big_int.big_int_of_int 256) in
      bv_concat 
	(bv_from_big_int (bits - 8) q) 
	(bv_from_int 8 (Big_int.int_of_big_int r))

external int_of_bv: bv -> int = "mlstp_int_of_bvec"

let big_int_of_unsigned_bv bv =
  let rec get_int nbits bv acc =
    if nbits <= 8 then
      Big_int.add_big_int (Big_int.mult_int_big_int 256 acc) 
        (Big_int.big_int_of_int (int_of_bv bv))
    else
      let acc' = Big_int.add_big_int (Big_int.mult_int_big_int 256 acc) 
        (Big_int.big_int_of_int 
            (int_of_bv (bv_extract bv (nbits - 1) (nbits - 8)))) in
        get_int (nbits - 8) bv acc' in
    get_int (bv_nbits bv) bv Big_int.zero_big_int

let big_int_of_signed_bv bv =
  let nbits = bv_nbits bv in
  let sign = vc_get_bval (bv_bit_extract bv (nbits - 1)) = True in
  if sign then Big_int.sub_big_int 
    (Big_int.minus_big_int (big_int_of_unsigned_bv (bv_not bv)))
    Big_int.unit_big_int
  else big_int_of_unsigned_bv bv



external bv_sign_extend : bv -> int -> bv = "mlstp_bv_sign_extend" 

(* Arithmetic operations *)
external bv_negate : bv -> bv              = "mlstp_bv_negate"
external bv_plus   : int -> bv -> bv -> bv = "mlstp_bv_plus"
external bv_minus  : int -> bv -> bv -> bv = "mlstp_bv_minus"
external bv_mult   : int -> bv -> bv -> bv = "mlstp_bv_mult"
external bv_udiv   : int -> bv -> bv -> bv = "mlstp_bv_udiv"
external bv_umod   : int -> bv -> bv -> bv = "mlstp_bv_umod"
external bv_sdiv   : int -> bv -> bv -> bv = "mlstp_bv_sdiv"
external bv_smod   : int -> bv -> bv -> bv = "mlstp_bv_smod"

(* Bitvector comparisons *)
external bv_eq  : bv -> bv -> bexpr = "mlstp_bv_eq"
external bv_ult : bv -> bv -> bexpr = "mlstp_bv_ult"
external bv_ule : bv -> bv -> bexpr = "mlstp_bv_ule"
external bv_ugt : bv -> bv -> bexpr = "mlstp_bv_ugt"
external bv_uge : bv -> bv -> bexpr = "mlstp_bv_uge"
external bv_slt : bv -> bv -> bexpr = "mlstp_bv_slt"
external bv_sle : bv -> bv -> bexpr = "mlstp_bv_sle"
external bv_sgt : bv -> bv -> bexpr = "mlstp_bv_sgt"
external bv_sge : bv -> bv -> bexpr = "mlstp_bv_sge"

(* Array operations *)

type bvarray

external bva_new: string -> int -> int -> bvarray = "mlstp_bva_new"
external bva_read:   bvarray -> (* index *) bv -> (* size *) int -> bv
  = "mlstp_bva_read"
external bva_write:  bvarray -> (* index *) bv -> (* value *) bv -> bvarray
  = "mlstp_bva_write"
external bva_eq: bvarray -> bvarray -> bexpr = "mlstp_bva_eq"
external string_of_bvarray : bvarray -> string = "mlstp_string_of_expr"

exception Bad_generation of string
let _ = Callback.register_exception "Bad generation" (Bad_generation "")


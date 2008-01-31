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

type ipval = int  (* Ax + B *)

type cstop =
    Co_eq
  | Co_ne
  | Co_lt
  | Co_gt
  | Co_le
  | Co_ge

type varkind =
    Vk_float
  | Vk_int
  | Vk_binary

(* Spec integration *)

(* type of ipvals, polymorphic in the linear variable type *)
val vt_ipval : Spec.t_val_type -> Spec.t_val_type

(* type of leaves in boolean formulas over ipvals *)
val vt_cstvar : Spec.t_val_type -> Spec.t_val_type -> Spec.t_val_type

val val2ipval : Spec.t_val -> ipval
val ipval2val : ipval -> Spec.t_val

val vt_ip_cstop : Spec.t_val_type
val val2cstop : Spec.t_val -> cstop
val val2varkind : Spec.t_val -> varkind

(* Formula construction *)

val iv_var : Spec.t_val -> varkind -> ipval
val iv_flt : float -> ipval
val iv_add : ipval -> ipval -> ipval
val iv_sub : ipval -> ipval -> ipval
val iv_mul : ipval -> float -> ipval
val iv_div : ipval -> float -> ipval

val add_cst_bvar : ipval -> cstop -> float -> Biteval.bval
val add_bit_bvar : Spec.t_val -> Biteval.bval

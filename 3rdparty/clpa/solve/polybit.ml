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

(* sumtypes for compactly constructing solve_bit and solve_mip formulas *)

open Builtin
open Spec
open Clpautil
open Biteval
open Solvemip

module A = Array

let vt_xvar = vt_var "IX"
let vt_yvar = vt_var "BX"

let vt_iv_rep typ = make_type "iv_rep" [|typ|]
let vt_xiv_rep = vt_iv_rep vt_xvar

let iv_rep = (vt_xiv_rep,[
  ("iv",[|vt_ipval vt_xvar|]);
  ("ix",[|vt_xvar|]);
  ("n",[|vt_int|]);
  ("f",[|vt_flt|]);
  ("add",[|vt_vargs vt_xiv_rep|]);
  ("sub",[|vt_xiv_rep;vt_xiv_rep|]);
  ("mul",[|vt_xiv_rep;vt_int|]);
  ("div",[|vt_xiv_rep;vt_int|]);
  ("fmul",[|vt_xiv_rep;vt_flt|]);
  ("fdiv",[|vt_xiv_rep;vt_flt|]);
])

let ival2flt = o Big_int.float_of_big_int val2int

let rec to_iv v =
  let (name,args) = val2sum v in match name with
      "iv" -> val2ipval args.(0)
    | "ix" -> iv_var args.(0) Vk_int
    | "n" -> iv_flt (ival2flt args.(0))
    | "f" -> iv_flt (val2flt args.(0))
    | "add" -> List.fold_right (o iv_add to_iv) (A.to_list args) (iv_flt 0.)
    | "sub" -> iv_sub (to_iv args.(0)) (to_iv args.(1))
    | "mul" -> iv_mul (to_iv args.(0)) (ival2flt args.(1))
    | "div" -> iv_div (to_iv args.(0)) (ival2flt args.(1))
    | "fmul" -> iv_mul (to_iv args.(0)) (val2flt args.(1))
    | "fdiv" -> iv_div (to_iv args.(0)) (val2flt args.(1))
    | _ -> pred_unexpected "Malformed iv_rep"

let to_iv_handler =
  (("to_iv",[|vt_xiv_rep;vt_ipval vt_xvar|]),[[|true;false|]],
   fun (name,args) -> [name,[|args.(0);ipval2val (to_iv args.(0))|]])

let vt_xcst = vt_cstvar vt_xvar vt_yvar

let vt_gv_rep ctyp btyp = make_type "gv_rep" [|ctyp;btyp|]
let vt_xgv_rep = vt_gv_rep vt_xvar vt_yvar

let gv_rep = (vt_xgv_rep,[
  ("gv",[|vt_bval vt_xcst|]);
  ("gx",[|vt_yvar|]);
  ("gtrue",[||]);
  ("gfalse",[||]);
  ("not",[|vt_xgv_rep|]);
  ("and",[|vt_vargs vt_xgv_rep|]);
  ("or",[|vt_vargs vt_xgv_rep|]);
  ("imply",[|vt_xgv_rep;vt_xgv_rep|]);
  ("iff",[|vt_xgv_rep;vt_xgv_rep|]);
  ("cst",[|vt_xiv_rep;vt_ip_cstop;vt_xiv_rep|]);
])

let rec to_g v =
  let imply v0 v1 =
    add_binop 100 Bo_or [add_unop 100 Bo_not (to_g v0);to_g v1] in
  let (name,args) = val2sum v in match name with
      "gv" -> val2bval args.(0)
    | "gx" -> add_bit_bvar args.(0)
    | "gtrue" -> btrue
    | "gfalse" -> bfalse
    | "not" -> add_unop 100 Bo_not (to_g args.(0))
    | "and" -> add_binop 100 Bo_and (A.to_list (A.map to_g args))
    | "or" -> add_binop 100 Bo_or (A.to_list (A.map to_g args))
    | "imply" -> imply args.(0) args.(1)
    | "iff" -> add_binop 100 Bo_and
        [imply args.(0) args.(1); imply args.(1) args.(0)]
    | "cst" ->
        let diff = iv_sub (to_iv args.(0)) (to_iv args.(2)) in
          add_cst_bvar diff (val2cstop args.(1)) 0.
    | _ -> pred_unexpected "Malformed gv_rep"

let to_g_handler =
  (("to_g",[|vt_xgv_rep;vt_bval vt_xcst|]),[[|true;false|]],
   fun (name,args) -> [name,[|args.(0);bval2val (to_g args.(0))|]])

let _ = register_package { empty_package with
  p_name = "polybit";
  p_find_handlers = [to_iv_handler; to_g_handler];
  p_sumtypes = [iv_rep; gv_rep];
}

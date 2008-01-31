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

open Spec
open Clpautil
open Big_int

let find_handlers = ref []
let collect_handlers = ref []
let operators = ref []

let _ = prepend collect_handlers
  (("int_min_all",[|vt_int;vt_int|]),[|true;false|],
   fun (name,args) matches -> match matches with
       [] -> []
     | (_,x)::xs -> 
       let res = List.fold_left
                   (fun n (_,args) -> min_big_int n (val2int args.(0)))
                 (val2int x.(0)) xs in
       [name,[|anyval;int2val res|]])

let _ = prepend collect_handlers
  (("int_max_all",[|vt_int;vt_int|]),[|true;false|],
   fun (name,args) matches -> match matches with
       [] -> []
     | (_,x)::xs -> 
       let res = List.fold_left
                   (fun n (_,args) -> max_big_int n (val2int args.(0)))
                 (val2int x.(0)) xs in
       [name,[|anyval;int2val res|]])

let _ = prepend collect_handlers
  (("int_add_all",[|vt_int;vt_int|]),[|true;false|],
   fun (name,args) matches ->
     let res = List.fold_left
                 (fun n (_,args) -> add_big_int n (val2int args.(0)))
               zero_big_int matches in
     [name,[|anyval;int2val res|]])

let n2n_handler pred fn =
  ((pred,[|vt_int;vt_int|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let n = val2int args.(0) in
     let nr = fn n in
       [name,[|args.(0);int2val nr|]])

let _ = prepend find_handlers (n2n_handler "int_neg" minus_big_int)
let _ = prepend find_handlers (n2n_handler "int_abs" abs_big_int)
let _ = prepend operators ("uminus", "int_neg")

let nn2n_handler pred fn =
  ((pred,[|vt_int;vt_int;vt_int|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let n0 = val2int args.(0) in
     let n1 = val2int args.(1) in
     let nr = try fn n0 n1
              with Division_by_zero ->
                     pred_unexpected "Divide by zero"
                 | Invalid_argument "power_big_int_positive_big_int" ->
                     pred_unexpected "Negative exponent" in
       [name,[|args.(0);args.(1);int2val nr|]])

(* implement some bitwise functions not supplied by Big_int *)
let rec bitwise_big_int fn n0 n1 =
  let s0 = sign_big_int n0 in
  if s0 < 0 then
    pred_unexpected
      ("Bitwise operation on negative: " ^ (string_of_big_int n0));
  let s1 = sign_big_int n1 in
  if s1 < 0 then
    pred_unexpected
      ("Bitwise operation on negative: " ^ (string_of_big_int n1));
  if s0 = 0 && s1 = 0 then zero_big_int
  else
    let (q0,r0) = quomod_big_int n0 (big_int_of_int 256) in
    let (q1,r1) = quomod_big_int n1 (big_int_of_int 256) in
    let tail = bitwise_big_int fn q0 q1 in
    let bits = fn (int_of_big_int r0) (int_of_big_int r1) in
      add_int_big_int bits (mult_int_big_int 256 tail)

let _ = prepend find_handlers (nn2n_handler "int_add" add_big_int)
let _ = prepend find_handlers (nn2n_handler "int_sub" sub_big_int)
let _ = prepend find_handlers (nn2n_handler "int_mul" mult_big_int)
let _ = prepend find_handlers (nn2n_handler "int_div" div_big_int)
let _ = prepend find_handlers (nn2n_handler "int_mod" mod_big_int)
let _ = prepend find_handlers (nn2n_handler "int_exp" power_big_int_positive_big_int)
let _ = prepend find_handlers (nn2n_handler "int_max" max_big_int)
let _ = prepend find_handlers (nn2n_handler "int_min" min_big_int)
let _ = prepend find_handlers (nn2n_handler "int_band" (bitwise_big_int (land)))
let _ = prepend find_handlers (nn2n_handler "int_bor" (bitwise_big_int (lor)))
let _ = prepend find_handlers (nn2n_handler "int_bxor" (bitwise_big_int (lxor)))

let _ = prepend operators ("+", "int_add")
let _ = prepend operators ("-", "int_sub")
let _ = prepend operators ("*", "int_mul")
let _ = prepend operators ("/", "int_div")
let _ = prepend operators ("mod", "int_mod")
let _ = prepend operators ("exp", "int_exp")
let _ = prepend operators ("and", "int_band")
let _ = prepend operators ("or", "int_bor")
let _ = prepend operators ("xor", "int_bxor")


let nn2b_handler pred fn =
  ((pred,[|vt_int;vt_int|]),[[|true;true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     let n0 = val2int args.(0) in
     let n1 = val2int args.(1) in
       if fn n0 n1 then [name,args] else [])

let _ = prepend find_handlers (nn2b_handler "int_eq" eq_big_int)
let _ = prepend find_handlers (nn2b_handler "int_ne" (fun n0 n1 -> not (eq_big_int n0 n1)))
let _ = prepend find_handlers (nn2b_handler "int_lt" lt_big_int)
let _ = prepend find_handlers (nn2b_handler "int_gt" gt_big_int)
let _ = prepend find_handlers (nn2b_handler "int_le" le_big_int)
let _ = prepend find_handlers (nn2b_handler "int_ge" ge_big_int)

let counter = ref 0
let _ = prepend find_handlers
  (("counter",[|vt_int|]),[[|false|],[]],
   fun (name,args) ->
     incr counter; [name,[|sint2val (!counter - 1)|]])

let _ = register_package { empty_package with
  p_name = "intops";
  p_reset = (fun () -> counter := 0);
  p_find_handlers = !find_handlers;
  p_collect_handlers = !collect_handlers;
  p_operators = !operators;
}

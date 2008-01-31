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

module S = String

let find_handlers = ref []
let operators = ref []

let _ = prepend find_handlers
  (("str_len",[|vt_str;vt_int|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let str = val2str args.(0) in
     let len = sint2val (S.length str) in
       [name,[|args.(0);len|]])

let cat_handler fnname = 
  ((fnname,[|vt_str;vt_str;vt_str|]),
   [([|true;true;false|], [Sk_once]); 
    ([|true;false;true|], [Sk_zero;Sk_once]);
    ([|false;true;true|], [Sk_zero;Sk_once])],
   fun (name,args) ->
     if is_val_const args.(0) && is_val_const args.(1) then
       let str0 = val2str args.(0) in
       let str1 = val2str args.(1) in
       let sr = str0 ^ str1 in
         [name,[|args.(0);args.(1);str2val sr|]]
     else if is_val_const args.(0) && is_val_const args.(2) then
       let str0 = val2str args.(0) in
       let rstr = val2str args.(2) in
       let (len0,rlen) = (S.length str0, S.length rstr) in
         if rlen >= len0 && S.sub rstr 0 len0 = str0 then
           let sr = S.sub rstr len0 (rlen - len0) in
             [name,[|args.(0);str2val sr;args.(2)|]]
         else []
     else if is_val_const args.(1) && is_val_const args.(2) then
       let str1 = val2str args.(1) in
       let rstr = val2str args.(2) in
       let (len1,rlen) = (S.length str1, S.length rstr) in
         if rlen >= len1 && S.sub rstr (rlen - len1) len1 = str1 then
           let sr = S.sub rstr 0 (rlen - len1) in
             [name,[|str2val sr;args.(1);args.(2)|]]
         else []
     else pred_unexpected "Underconstrained")

let _ = prepend find_handlers (cat_handler "str_cat")
let _ = prepend operators ("^", "str_cat")

let _ = prepend find_handlers
  (("str_sub",[|vt_str;vt_int;vt_int;vt_str|]),
   [([|true;true;true;false|],[Sk_once]);
    ([|true;false;false;true|],[Sk_zero;Sk_many])],
   fun (name,args) ->
     if is_val_const args.(3) then
       let str = val2str args.(0) in
       let fstr = val2str args.(3) in
       let vlen = sint2val (S.length fstr) in
       let rec find_all str vrs offset =
         try let pos = string_find str fstr in
           find_all (S.sub str (pos + 1) (S.length str - pos - 1))
             ((sint2val (pos + offset))::vrs) (pos + offset + 1)
         with Not_found -> vrs in
       List.map (fun pos -> (name,[|args.(0);pos;vlen;args.(3)|]))
         (find_all str [] 0)
     else
       let str = val2str args.(0) in
       let pos = val2sint args.(1) in
       let len = val2sint args.(2) in
         try let sr = S.sub str pos len in
           [name,[|args.(0);args.(1);args.(2);str2val sr|]]
         with Invalid_argument _ -> pred_unexpected "Bad substring")

let _ = prepend find_handlers
  (("str_hash",[|vt_str;vt_int|]),
   [([|true;false|],[Sk_once])],
   fun (name,args) ->
     let str = val2str args.(0) in
     let h = Hashtbl.hash str in
       [name,[|args.(0);sint2val h|]])

let _ = register_package { empty_package with
  p_name = "strops";
  p_find_handlers = !find_handlers;
  p_operators = !operators;
}

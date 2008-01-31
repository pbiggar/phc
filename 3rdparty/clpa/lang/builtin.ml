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

module A = Array
module S = String
module H = Hashtbl
module IO = Streamio
open Spec
open Clpautil

exception Found of int

let add_handlers = ref []
let find_handlers = ref []
let collect_handlers = ref []

let vt_xvar = vt_var "X"
let vt_yvar = vt_var "Y"

(* special preds referenced by spec.ml *)

let _ = prepend add_handlers
  ((clear_pred_name,[||]),
   fun _ -> raise Handle_clear_preds)

let _ = prepend add_handlers
  ((assertion_failure_name,[|vt_str|]),
   fun (name,args) -> raise (Handle_assertion_failure (val2str args.(0))))

let _ = prepend add_handlers
  ((process_dep_name,[|vt_str;vt_vargs vt_any|]),
   fun (name,args) ->
     let sname = val2str args.(0) in
     let len = Array.length args in
     raise (Handle_process_dep (rep2pred (sname, Array.sub args 1 (len-1))))
  )

let _ = prepend add_handlers
  ((derivation_pred_name,[|vt_int;vt_vargs vt_any|]),
   fun (name,args) ->
     let depth = val2sint args.(0) in
       raise (Handle_print_derivation (depth,rep2pred (name,args))))

let printed_queries : (t_val array,unit) H.t = H.create 10
let _ = prepend add_handlers
  ((query_pred_name,[|vt_str;vt_vargs vt_any|]),
   fun (name,args) ->
     if not (H.mem printed_queries args) then begin
       H.add printed_queries args () ;
       let pred = (val2str args.(0),A.sub args 1 (A.length args - 1)) in
         IO.printf "%s.\n" (string_of_pred !print_level (rep2pred pred))
     end)

let _ = prepend find_handlers
  ((equal_pred_name,[|vt_xvar; vt_xvar|]),
  [([|true;false|],[Sk_zero;Sk_once]); ([|false;true|],[Sk_zero;Sk_once])],
   fun (name,args) -> [name,[|args.(0);args.(0)|]])

(* normal preds using the regular interface *)

let _ = prepend find_handlers
  (("notequal", [|vt_xvar;vt_xvar|]),[[|true;true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     if compare_vals args.(0) args.(1) <> 0 then [name,args] else [])

let _ = prepend find_handlers
  (("lessthan", [|vt_xvar;vt_xvar|]),[[|true;true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     if compare_vals args.(0) args.(1) < 0 then [name,args] else [])

let _ = prepend find_handlers
  (("tostring", [|vt_xvar;vt_str|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     if not (is_val_const args.(0)) then pred_unexpected "Non-constant arg";
     [name,[|args.(0);str2val (full_string_of_val args.(0))|]])

let _ = prepend find_handlers
  (("toint", [|vt_xvar;vt_int|]),[[|true;false|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     if not (is_val_const args.(0)) then pred_unexpected "Non-constant arg";
     try [name,[|args.(0);int2val (val2int args.(0))|]]
     with Unexpected _ ->
     try [name,[|args.(0);int2val (Big_int.big_int_of_int (int_of_float (val2flt args.(0))))|]]
     with Unexpected _ ->
     try [name,[|args.(0);int2val (Big_int.big_int_of_string (val2str args.(0)))|]]
     with Unexpected _ -> [])

let _ = prepend find_handlers
  (("tofloat", [|vt_xvar;vt_flt|]),[[|true;false|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     if not (is_val_const args.(0)) then pred_unexpected "Non-constant arg";
     try [name,[|args.(0);flt2val (val2flt args.(0))|]]
     with Unexpected _ ->
     try [name,[|args.(0);flt2val (Big_int.float_of_big_int (val2int args.(0)))|]]
     with Unexpected _ ->
     try [name,[|args.(0);flt2val (float_of_string (val2str args.(0)))|]]
     with Failure "float_of_string" -> pred_unexpected "Bad float string"
        | Unexpected _ -> [])

let printed : (t_val array,unit) H.t = H.create 10
let _ = prepend add_handlers
  (("print",[|vt_vargs vt_any|]),
   fun (name,args) ->
     if not (H.mem printed args) then begin
       H.add printed args ();
       IO.printf "%s\n"
         (sep_string_of_array " " (string_of_val !print_level) args)
     end)

let printed_strings : (t_val,unit) H.t = H.create 10
let _ = prepend add_handlers
  (("print_string",[|vt_str|]),
   fun (name,args) ->
     if not (H.mem printed_strings args.(0)) then begin
       H.add printed_strings args.(0) ();
       IO.printf "%s\n" (val2str args.(0))
     end)

(* TODO: do something smarter with warnings *)
let warnings : (t_val array,unit) H.t = H.create 10
let _ = prepend add_handlers
  (("warning",[|vt_str;vt_vargs vt_any|]),
   fun (name,args) ->
     if not (H.mem warnings args) then begin
       H.add warnings args ();
       let strarr = A.mapi
         (fun i -> if i = 0 then val2str else string_of_val !print_level) args 
         in
       let str = sep_string_of_array " " id strarr in
         IO.printf "WARNING: %s\n" str
     end)

let _ = prepend collect_handlers
  (("count_all",[|vt_xvar;vt_int|]),[|true;false|],
   fun (name,_) matches ->
     let len = List.length matches in
       [name,[|anyval;sint2val len|]])

let _ = prepend find_handlers
  (("list_mem",[|vt_list (vt_xvar);vt_xvar|]),
  [[|true;false|],[Sk_zero;Sk_many]],
   fun (name,args) ->
     list_map (fun v -> (name,[|args.(0);v|])) (val2list args.(0)))

let _ = prepend find_handlers
  (("list_nth",[|vt_list (vt_xvar);vt_int;vt_xvar|]),
  [[|true;false;false|],[Sk_zero;Sk_many]],
   fun (name,args) ->
     let list = val2list args.(0) in
     fst (map_foldl (fun v n -> (name,[|args.(0);sint2val n;v|]), n+1) list 0))

let _ = prepend find_handlers
  (("list_length",[|vt_list vt_xvar;vt_int|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let len = List.length (val2list args.(0)) in
       [name,[|args.(0);sint2val len|]])

let _ = prepend find_handlers
  (("list_sort",[|vt_list vt_xvar;vt_list vt_xvar|]),
  [[|true;false|],[Sk_once]],
   fun (name,args) ->
     let list = list_sort compare_vals (val2list args.(0)) in
       [name,[|args.(0);list2val None list|]])

let _ = prepend find_handlers
  (("list_nodup",[|vt_list vt_xvar|]),[[|true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     let list = list_sort compare_vals (val2list args.(0)) in
     let rec contains_dups list = match list with
       | [] -> false
       | [x] -> false
       | x::y::zs -> (compare_vals x y = 0) || (contains_dups (y::zs)) in
     if contains_dups list then []
     else [name,[|args.(0)|]])

let _ = prepend find_handlers
  (("list_rmdup",[|vt_list vt_xvar;vt_list vt_xvar|]),
  [[|true;false|],[Sk_once]],
   fun (name,args) ->
     let list = val2list args.(0) in
     let rec filter_dups list prev = match list with
         [] -> prev
       | x::xs ->
           if List.exists ((=)x) prev then filter_dups xs prev
           else filter_dups xs (x::prev) in
     let nlist = List.rev (filter_dups list []) in
       [name,[|args.(0);list2val None nlist|]])

let rec break_list acc left right =
  match right with
    | [] -> (left,[])::acc
    | x::xs -> let left' = x::left in break_list ((left',xs)::acc) left' xs

let _ = prepend find_handlers
  (("list_append",[|vt_list vt_xvar;vt_list vt_xvar;vt_list vt_xvar|]),
   [([|true;true;false|],[Sk_once]); ([|false;false;true|],[Sk_many])],
   fun (name,args) -> 
     if (is_val_const args.(0)) && (is_val_const args.(1)) then 
       let lista = val2list args.(0) in
       let listb = val2list args.(1) in
	 [name,[|args.(0);args.(1);list2val None (lista @ listb)|]]
     else
       let list = val2list args.(2) in
       let pairs = break_list [([],list)] [] list in
         List.map (fun (l,r) ->
	   (name, [|list2val None (List.rev l); list2val None r; args.(2)|])
	   ) pairs
  )

let _ = prepend find_handlers
  (("list_reverse",[|vt_list vt_xvar;vt_list vt_xvar|]),
  [[|true;false|],[Sk_once]],
   fun (name,args) ->
     let list = List.rev (val2list args.(0)) in
       [name,[|args.(0);list2val None list|]])

let _ = prepend collect_handlers
  (("list_all",[|vt_xvar;vt_list vt_xvar|]),[|true;false|],
   fun (name,_) matches ->
     let list = list_map (fun (_,args) -> args.(0)) matches in
     let list = list_sort compare_vals list in
       [name,[|anyval;list2val None list|]])

let vt_pair ltyp rtyp = make_type "t_pair" [|ltyp;rtyp|]
let sum_pair = (vt_pair vt_xvar vt_yvar,[
  ("pair",[|vt_xvar;vt_yvar|]);
])
let pair2val a b = sum2val ("pair", [|a;b|])
let val2pair v   = let (sname, sargs) = val2sum v in
  if sname <> "pair" then pred_unexpected "Bad format (val2pair)" else
  (sargs.(0), sargs.(1))

(* Boolean type *)
let vt_bool = make_type "bool" [||]
let sum_bool = (vt_bool, [("true",[||]); ("false",[||])])

let val2bool v =
  let (name,_) = val2sum v in
    if name = "true" then true
    else if name = "false" then false
    else pred_unexpected "Bad format (val2bool)"
let bool2val b =
  let name = if b then "true" else "false" in
    sum2val (name,[||])

(* Maybe type *)
let vt_maybe typ = make_type "maybe" [|typ|]
let sum_maybe = (vt_maybe vt_xvar ,[
  ("yes",[|vt_xvar|]);
  ("no",[||]);
])

let maybex2val f v = 
    match v with
        None -> sum2val ("no",[||])
      | Some v -> sum2val ("yes",[|f v|])

let reset () =
  H.clear printed; 
  H.clear printed_strings;
  H.clear printed_queries;
  H.clear warnings

let _ = register_package { empty_package with
  p_name = "builtin";
  p_reset = reset;
  p_add_handlers = !add_handlers;
  p_find_handlers = !find_handlers;
  p_collect_handlers = !collect_handlers;
  p_sumtypes = [sum_list;sum_pair;sum_maybe;sum_bool];
  p_abstypes = [vt_str;vt_int;vt_flt];
}

let _ = set_package_builtin "builtin"

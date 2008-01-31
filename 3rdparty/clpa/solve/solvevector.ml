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

(* Bitvector operations represented using boolean formulas *)

open Clpautil
open Flags
open Spec
open Builtin
open Biteval
open Solvebit
open Big_int

module A = Array
module H = Hashtbl
module V = Vector
module IO = Streamio

let reset_fns : (unit -> unit) list ref = ref []
let reset() = List.iter (fun f -> f()) !reset_fns

type bvval = int

(* bitvector representation of a fixed-width number:
 * sign: is this number signed?
 * overflow: is this number a product of an overflowing computation?
 * bits: the bits of the number, in LSB-first order
 *)
type bvec = bool * bval * (bval array)

let tbl_bvecs : bvec V.t = V.create 10
let _ = prepend reset_fns (fun () -> V.clear tbl_bvecs)

let get_bvec bv = V.get tbl_bvecs bv
let add_bvec bvv = V.append tbl_bvecs bvv

let string_of_bvec d v = cvt_val_depth d
  (let (s,oflow,vec) = get_bvec v in
     "[" ^ (if s then "s" else "u") ^ "|"
         ^ (string_of_val (d-1) (bval2val oflow)) ^ "|"
         ^ (sep_string_of_array ";" (o (string_of_val (d-1)) bval2val) vec) 
         ^ "]")

(* Bitvector operation caches *)

(* cached conversion/casting between other types of values *)

type x2bvop =
    Vo_cvt_int
  | Vo_cvt_bval
  | Vo_cvt_bvec

let tbl_x2bv : (x2bvop*t_val*bool*int, bvval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_x2bv)

(* Table for #id_bv *)
let tbl_id2bv : (t_val*bool*bool*int, bvval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_id2bv)

(* cached bitvector operations *)

type bv2bvop =
    Vo_neg
  | Vo_bnot

let tbl_opbv2bv : (bv2bvop*bvval, bvval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_opbv2bv)

type bvbv2bvop =
    Vo_add
  | Vo_sub
  | Vo_band
  | Vo_bor
  | Vo_bxor

let tbl_opbvbv2bv : (bvbv2bvop*bvval*bvval, bvval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_opbvbv2bv)

type bvn2bvop =
    Vo_mul
  | Vo_shl
  | Vo_shr

(* big_int is an abstract type so we need to override the default equality
 * when building a hash table using them in keys *)
module BVNHashType = struct
  type t = bvn2bvop * bvval * big_int
  let equal (op0,v0,n0) (op1,v1,n1) =
    op0 = op1 && v0 = v1 && Big_int.eq_big_int n0 n1
  let hash = H.hash
end
module BVNH = H.Make(BVNHashType)

let tbl_opbvn2bv : bvval BVNH.t = BVNH.create 10
let _ = prepend reset_fns (fun () -> BVNH.clear tbl_opbvn2bv)

type bv2gop =
    Vo_eqz
  | Vo_nez
  | Vo_oflow

let tbl_opbv2g : (bv2gop*bvval, bval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_opbv2g)

type bvbv2gop =
    Vo_eq
  | Vo_ne
  | Vo_lt
  | Vo_gt
  | Vo_le
  | Vo_ge

let tbl_opbvbv2g : (bvbv2gop*bvval*bvval, bval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_opbvbv2g)

(* Bitvector operations *)

(* Based in part on earlier implementation by Yichen Xie
 * <yxie@cs.stanford.edu> *)

let big_two = big_int_of_int 2
let get_bit n i =
  assert (sign_big_int n <> ~-1);
  let bit = (mod_big_int (div_big_int n (power_int_positive_int 2 i)) big_two) in
    eq_big_int bit unit_big_int
let set_bit n i b =
  assert (sign_big_int n <> ~-1);
  if get_bit n i = b then n
  else if b then add_big_int n (power_int_positive_int 2 i)
  else sub_big_int n (power_int_positive_int 2 i)

(* bitvector unops/binops have a max simplify level of 4 to only constant
 * fold and avoid expensive simplifications *)
let add_bnot v = add_unop 4 Bo_not v
let add_band v0 v1 = add_binop 4 Bo_and [v0;v1]
let add_bor  v0 v1 = add_binop 4 Bo_or  [v0;v1]

let add_beq v0 v1 =
  let a = add_band v0 v1 in
  let b = add_band (add_bnot v0) (add_bnot v1) in
    add_bor a b

let add_bne v0 v1 =
  let a = add_band v0 (add_bnot v1) in
  let b = add_band v1 (add_bnot v0) in
    add_bor a b

let add_blt v0 v1 = add_band (add_bnot v0) v1

(* v0 & v1 || v0 & v2 || v1 & v2 *)
let add_carry v0 v1 v2 =
  let a = add_band v0 v1 in
  let b = add_band v0 v2 in
  let c = add_band v1 v2 in
    add_bor a (add_bor b c)

(* v0 ^ v1 ^ v2 *)
let add_sum v0 v1 v2 =
  add_bne v0 (add_bne v1 v2)

(* Perform a signedness cast on a bitvector, checking for overflow *)
let sign_cast (s0,o0,vec) s =
    let olen = A.length vec in
    if s = s0 then 
        (s, o0, vec)
    else
        (s, add_bor o0 vec.(olen - 1), vec)

(* Change the length of a bitvector, checking for overflow *)
let length_cast (s0,o0,vec) len =
    let olen = A.length vec in
    let sign_bit = if s0 then vec.(olen - 1) else bfalse in
    if olen <= len then
        (* upcast or no change - no overflow possible *)
        (s0, o0, A.init len (fun i -> if i < olen then vec.(i) else sign_bit))
    else (
        (* downcast *)
        if s0 then
            (* Check all the amputated bits and the new sign bit are equal to
             * the original sign bit *)
            let o =
                fold_num (fun i vr -> add_bor vr (add_bne vec.(i) sign_bit)) 
                o0 (len - 1) (olen - 1) in
            (s0, o, A.init len (fun i -> vec.(i)))
        else
            (* Check all the amputated bits are 0 *)
            let o = fold_num (fun i vr -> add_bor vr vec.(i)) o0 len (olen - 1)
                in
            (s0, o, A.init len (fun i -> vec.(i)))
    )

let do_cast bv s len = 
  let len0 = Array.length (thd3 bv) in
  if len >= len0 then
    sign_cast (length_cast bv len) s
  else
    length_cast (sign_cast bv s) len
 
let force_agree (s0,o0,vec0) (s1,o1,vec1) =
  (* if the signed/unsigned differ then force to unsigned *)
  let s = if s0 = s1 then s0 else false in
  (* if the lengths differ then sign extend the shorter one *)
  let len = max (A.length vec0) (A.length vec1) in
  let (_, no0, nv0) = do_cast (s0,o0,vec0) s len in
  let (_, no1, nv1) = do_cast (s1,o1,vec1) s len in
    (s, no0, nv0, no1, nv1)

let do_bnot (s,o,vec) =
  (s,o, A.init (A.length vec) (fun i -> add_bnot vec.(i)))

let do_band bv0 bv1 =
  let (s,o0,vec0,o1,vec1) = force_agree bv0 bv1 in
    (s, add_bor o0 o1,
        A.init (A.length vec0) (fun i -> add_band vec0.(i) vec1.(i)))

let do_bor bv0 bv1 =
  let (s,o0,vec0,o1,vec1) = force_agree bv0 bv1 in
    (s, add_bor o0 o1,
        A.init (A.length vec0) (fun i -> add_bor vec0.(i) vec1.(i)))

let do_bxor bv0 bv1 =
  let (s,o0,vec0,o1,vec1) = force_agree bv0 bv1 in
    (s, add_bor o0 o1,
        A.init (A.length vec0) (fun i -> add_bne vec0.(i) vec1.(i)))

let do_unconstrained v s o len =
  let mk_bit i =
    let sum = ("b_vbit", [|v;sint2val i|]) in
      add_var (sum2val sum) in
  let obit = if o then mk_bit ~-1 else bfalse in
  (s, obit, A.init len mk_bit)

let do_onebit v s len =
  (s, bfalse, A.init len (fun i -> if i = 0 then v else bfalse))

let do_zero = do_onebit bfalse
let do_one = do_onebit btrue

let do_add bv0 bv1 =
  let (s,o0,vec0,o1,vec1) = force_agree bv0 bv1 in
  (* create an array of dummy carry bits, make them zero initially *)
  let len = A.length vec0 in
  let carry = A.create (len + 1) bfalse in
  let add_nth_bit i =
    carry.(i+1) <- add_carry carry.(i) vec0.(i) vec1.(i);
    add_sum carry.(i) vec0.(i) vec1.(i) in
  let vec = A.init len add_nth_bit in
  let oflow = add_bor (add_bor o0 o1)
    (if s
        (* A signed addition overflows if the carry into the sign bit is
         * not equal to the carry out of the sign bit *)
     then add_bne carry.(len) carry.(len - 1)
     else carry.(len)
    ) in
    (s, oflow, vec)

(* Subtraction is like addition, except that the carry in bit is set,
 * one of the vectors is inverted and the overflow condition is negated in 
 * the unsigned case *)
let do_sub bv0 bv1 =
  let (s,o0,vec0,o1,vec1) = force_agree bv0 bv1 in
  let len = A.length vec0 in
  let carry = A.create (len + 1) bfalse in
  carry.(0) <- btrue ;
  let add_nth_bit i =
    carry.(i+1) <- add_carry carry.(i) vec0.(i) (add_bnot vec1.(i));
    add_sum carry.(i) vec0.(i) (add_bnot vec1.(i)) in
  let vec = A.init len add_nth_bit in
  let oflow = add_bor (add_bor o0 o1)
    (if s
        (* A signed subtraction overflows if the carry into the sign bit is
         * not equal to the carry out of the sign bit *)
     then add_bne carry.(len) carry.(len - 1)
     else add_bnot carry.(len)
    ) in
  (s, oflow, vec)

let do_neg (s,o,vec) =
  do_add (do_bnot (s,o,vec)) (do_one s (A.length vec))

let do_const n s len =
  let add_bit n i = if get_bit n i then btrue else bfalse in
  if sign_big_int n = ~-1 then
    let nn = minus_big_int n in
      do_neg (s, bfalse, A.init len (add_bit nn))
  else (s, bfalse, A.init len (add_bit n))

let do_shl (s,o0,vec) (n:int) =
  assert (n >= 0);
  let len = A.length vec in
  (* Check that all of the shifted out and new sign bits are equal to the
   * old sign bit (0 in the case of an unsigned bitvector)
   *)
  let ostart = max 0 (if s then len - n - 1 else len - n) in
  let sbit = if s then vec.(len - 1) else bfalse in 
  let o = fold_num (fun i vr -> add_bor vr (add_bne sbit vec.(i))) o0 ostart 
      len in
    (s, o, A.init len (fun i -> if i < n then bfalse else vec.(i-n)))

(* XXX: Handle overflow better? *)
let do_shr (s,o,vec) (n:int) =
  assert (n >= 0);
  let len = A.length vec in
  let shb = if s then vec.(len - 1) else bfalse in
    (s, o, A.init len (fun i -> if i >= len - n then shb else vec.(i+n)))

(* carry save adder: (s,c) where s + c = bv1 + bv2 + bv3 *)
let do_csa vec0 vec1 vec2 =
  let len = A.length vec0 in
  let carry = A.init (len + 1)
         (fun i ->
            if i = 0 then bfalse
            else let i = i - 1 in
              add_carry vec0.(i) vec1.(i) vec2.(i)) in
  let sum = A.init (len + 1) (fun i -> 
        if i < len then add_sum vec0.(i) vec1.(i) vec2.(i) else bfalse) in
  (sum, carry)

let rec do_sum s len = function
    [] -> do_zero s len
  | [bv] -> bv
  | [bv0; bv1] -> do_add bv0 bv1
  | bv0::bv1::bv2::rest ->
      let (_,o0,vec0) = bv0 in
      let (_,o1,vec1) = bv1 in
      let (_,o2,vec2) = bv2 in
      let (sum, carry) = do_csa vec0 vec1 vec2 in
      let o = add_bor o0 (add_bor o1 (add_bor o2 (
        if s
        (* A signed addition overflows if the carry into the sign bit is
         * not equal to the carry out of the sign bit *)
        then add_bne carry.(len) carry.(len - 1)
        else carry.(len)
      ))) in
      let bvr0 = (s, o, Array.sub sum 0 len) in
      let bvr1 = (s, bfalse, Array.sub carry 0 len) in
      do_cast (do_sum s len (bvr0::bvr1::rest)) s len

let do_mul (s,o,vec) n =
  let sums n = fold_num (fun i sums ->
    if get_bit n i then (do_shl (s,o,vec) i)::sums
    else sums) [] 0 (A.length vec) in
  if sign_big_int n = ~-1 then
    let nn = minus_big_int n in
      do_neg (do_sum s (A.length vec) (sums nn))
  else do_sum s (A.length vec) (sums n)

let do_nez (s,o,vec) =
  fold_num (fun i vr -> add_bor vr vec.(i)) bfalse 0 (A.length vec)

let do_eq bv0 bv1 =
  let (_,_,vec0,_,vec1) = force_agree bv0 bv1 in
    fold_num (fun i vr -> add_band vr (add_beq vec0.(i) vec1.(i)))
      btrue 0 (A.length vec0)

let do_ne bv0 bv1 =
  let (_,_,vec0,_,vec1) = force_agree bv0 bv1 in
    fold_num (fun i vr -> add_bor vr (add_bne vec0.(i) vec1.(i)))
      bfalse 0 (A.length vec0)

let do_cmp bv0 bv1 =
  let (s,_,vec0,_,vec1) = force_agree bv0 bv1 in
  let len = A.length vec0 in
  let ltv = if s then add_blt vec1.(len-1) vec0.(len-1)
            else      add_blt vec0.(len-1) vec1.(len-1) in
  let eqv =           add_beq vec0.(len-1) vec1.(len-1) in
    fold_num_down (fun i (ltv,eqv) ->
      let ltv = add_bor ltv
        (add_band eqv (add_blt vec0.(i) vec1.(i))) in
      let eqv = add_band eqv
        (add_beq vec0.(i) vec1.(i)) in
      (ltv,eqv))
    (ltv,eqv) (len - 2) (-1)

let undo_const (s,o,vec) getfn =
  let (neg,vec) =
    if s && (getfn vec.(A.length vec - 1)) then
      (true, thd3 (do_neg (s,o,vec)))
    else (false, vec) in
  let bits = A.map getfn vec in
  let n = fold_num (fun i n -> set_bit n i bits.(i))
            zero_big_int 0 (A.length vec) in
    if neg then minus_big_int n else n

(* Spec integration *)

let compare_bvec bvv0 bvv1 =
  let (s0,o0,vec0) = get_bvec bvv0 in
  let (s1,o1,vec1) = get_bvec bvv1 in
  let cmp0 = compare s0 s1 in
  let cmp1 = compare_bval o0 o1 in
    if cmp0 <> 0 then cmp0
    else if cmp1 <> 0 then cmp1
    else compare_arrays compare_bval vec0 vec1

let dump_bvec ds bvv =
  let (s,o,vec) = get_bvec bvv in
    IO.dump_bool ds s;
    dump_bval ds o;
    IO.dump_array ds dump_bval vec

let load_bvec ls =
  let s = IO.load_bool ls in
  let o = load_bval ls in
  let vec = IO.load_array ls load_bval in
    add_bvec (s,o,vec)

let debug_bvec_full = register_debug "bvec_full" "Always print bvec values"
let debug_bvec_simp = register_debug "bvec_simp" "Never print bvec values"

let vt_bvec typ0 typ1 = make_type "bvec" [|typ0;typ1|]
let vk_bvec = register_val_kind {
  vki_tostring = (fun depth v ->
    if debug_bvec_full() || not (debug_bvec_simp()) then
      string_of_bvec depth v
    else "BV#" ^ (string_of_int v));
  vki_compare = compare_bvec;
  vki_dump = dump_bvec;
  vki_load = load_bvec;
}

let val2bvec = val2cst vk_bvec
let bvec2val = cst2val vk_bvec

let vt_xvar = vt_var "X"
let vt_yvar = vt_var "Y"

(* bval type for bitvector generated formulas, each var is either one b_vbit
 * of a vector, or is an extra b_abit *)
let vt_bvec_bit typ0 typ1 = make_type "bvecbit" [|typ0;typ1|]
let sum_bvec_bit = (vt_bvec_bit vt_xvar vt_yvar,[
  ("b_vbit",[|vt_xvar;vt_int|]);
  ("b_abit",[|vt_yvar|]);
])

(* Bit vector package *)

let find_handlers = ref []
let collect_handlers = ref []
let operators = ref []

let vt_xbvec = vt_bvec vt_xvar vt_yvar
let vt_xbval = vt_bval (vt_bvec_bit vt_xvar vt_yvar)
let vt_xbassign = vt_bassign (vt_bvec_bit vt_xvar vt_yvar)

(* Reset the overflow bit of a vector *)
let sanitize_oflow (s,_,bits) = (s,bfalse,bits)

(* Merge a vector and guard with another bitvector. This function is 
 * intended for use with foldl *)
let merge_vecs bv0 (bv1v, g1) =
  let bv1 = get_bvec bv1v in
  let (s,o0,vec0,o1,vec1) = force_agree bv0 bv1 in
    (s, add_bor o0 (add_band o1 g1),
        A.init (A.length vec0) (fun i -> add_bor vec0.(i) 
            (add_band g1 vec1.(i))))

let _ = prepend collect_handlers
  (("#bv_all",[|vt_xbvec;vt_xbval;vt_xbvec|]),[|true;true;false|],
   fun (name,args) matches ->
     let select = List.map (fun (_,args) ->
                    (val2bvec args.(0),val2bval args.(1))) matches in
     let vec = List.fold_left merge_vecs (do_zero true 1) select in
     let bvr = add_bvec vec in
       [name,[|anyval;anyval;bvec2val bvr|]])

let _ = prepend find_handlers
  (("#asnbv",[|vt_xbassign;vt_xbvec;vt_int|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let av = val2bassign args.(0) in
     let bv = val2bvec args.(1) in
     let nr = undo_const (get_bvec bv) (apply_assignment av) in
       [name,[|args.(0);args.(1);int2val nr|]])

let _ = prepend find_handlers
  (("#bv_bit",[|vt_xbvec;vt_int;vt_xbval|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let (_,o,vec) = get_bvec (val2bvec args.(0)) in
     let n = val2sint args.(1) in
       if n = -1 then [name,[|args.(0);args.(1);bval2val o|]]
       else if n < 0 || n >= A.length vec then pred_unexpected "Bad bit number"
       else [name,[|args.(0);args.(1);bval2val vec.(n)|]])

let _ = prepend find_handlers
  (("#bv_guard",[|vt_xbvec;vt_xbval;vt_xbvec|]),
  [[|true;true;false|],[Sk_once]],
   fun (name, args) ->
     let (s, o, bs) = get_bvec (val2bvec args.(0)) in  
     let g = val2bval (args.(1)) in
     let bvr = add_bvec (s, add_band o g,
        A.init (A.length bs) (fun i -> add_band g bs.(i))) in
     [name,[|args.(0);args.(1);bvec2val bvr|]])


let x2bv_handler pred param op =
  ((pred,[|param;vt_bool;vt_int;vt_xbvec|]),
  [[|true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let x = args.(0) in
     let s = Builtin.val2bool args.(1) in
     let len = val2sint args.(2) in
     let bvr =
       try H.find tbl_x2bv (op,x,s,len)
       with Not_found ->
         let bvvr = match op with
             Vo_cvt_int -> do_const (val2int x) s len
           | Vo_cvt_bval -> do_onebit (val2bval x) s len
           | Vo_cvt_bvec -> do_cast (sanitize_oflow (get_bvec (val2bvec x))) 
                            s len in
         let bvr = add_bvec bvvr in
           H.add tbl_x2bv (op,x,s,len) bvr; bvr in
     [name,[|args.(0); args.(1); args.(2); bvec2val bvr|]])

let _ = prepend find_handlers (x2bv_handler "#int_bv"  vt_int   Vo_cvt_int)
let _ = prepend find_handlers (x2bv_handler "#g_bv"    vt_xbval Vo_cvt_bval)
let _ = prepend find_handlers (x2bv_handler "#bv_cast" vt_xbvec Vo_cvt_bvec)

let _ = prepend find_handlers 
  (("#id_bv",[|vt_xvar;vt_bool;vt_bool;vt_int;vt_xbvec|]),
   [[|true;true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let x = args.(0) in
     let s = Builtin.val2bool args.(1) in
     let o = Builtin.val2bool args.(2) in
     let len = val2sint args.(3) in
     let bvr =
       try H.find tbl_id2bv (x,s,o,len)
       with Not_found ->
         let bvvr = do_unconstrained x s o len in
         let bvr = add_bvec bvvr in
           H.add tbl_id2bv (x,s,o,len) bvr; bvr in
     [name,[|args.(0); args.(1); args.(2); args.(3); bvec2val bvr|]])

let _ = prepend find_handlers
  (("#bv_int",[|vt_xbvec;vt_int|]),[[|true;false|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     let bvr = val2bvec args.(0) in
     let (s,oflow,vec) = get_bvec bvr in
     let getfn b =
       if b = btrue then true
       else if b = bfalse then false
       else raise Not_found in
     (try let n = undo_const (s,oflow,vec) getfn in
        [name,[|args.(0);int2val n|]]
      with Not_found -> []))

let bv2bv_handler pred op =
  ((pred,[|vt_xbvec;vt_xbvec|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let bv = val2bvec args.(0) in
     let bvr =
       try H.find tbl_opbv2bv (op,bv)
       with Not_found ->
         let bvv = sanitize_oflow (get_bvec bv) in
         let bvvr = match op with
             Vo_neg -> do_neg bvv
           | Vo_bnot -> do_bnot bvv in
         let bvr = add_bvec bvvr in
           H.add tbl_opbv2bv (op,bv) bvr; bvr in
     [name,[|args.(0);bvec2val bvr|]])

let _ = prepend find_handlers (bv2bv_handler "#bv_neg"  Vo_neg)
let _ = prepend find_handlers (bv2bv_handler "#bv_bnot" Vo_bnot)

let bvbv2bv_handler pred op =
  ((pred,[|vt_xbvec;vt_xbvec;vt_xbvec|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bv0 = val2bvec args.(0) in
     let bv1 = val2bvec args.(1) in
     let bvr =
       try H.find tbl_opbvbv2bv (op,bv0,bv1)
       with Not_found ->
         let bvv0 = sanitize_oflow (get_bvec bv0) in
         let bvv1 = sanitize_oflow (get_bvec bv1) in
         let bvvr = match op with
             Vo_add -> do_add bvv0 bvv1
           | Vo_sub -> do_sub bvv0 bvv1
           | Vo_band -> do_band bvv0 bvv1
           | Vo_bor -> do_bor bvv0 bvv1
           | Vo_bxor -> do_bxor bvv0 bvv1 in
         let bvr = add_bvec bvvr in
           H.add tbl_opbvbv2bv (op,bv0,bv1) bvr; bvr in
     [name,[|args.(0);args.(1);bvec2val bvr|]])

let _ = prepend find_handlers (bvbv2bv_handler "#bv_add"  Vo_add)
let _ = prepend find_handlers (bvbv2bv_handler "#bv_sub"  Vo_sub)
let _ = prepend find_handlers (bvbv2bv_handler "#bv_band" Vo_band)
let _ = prepend find_handlers (bvbv2bv_handler "#bv_bor"  Vo_bor)
let _ = prepend find_handlers (bvbv2bv_handler "#bv_bxor" Vo_bxor)
let _ = prepend operators ("+", "#bv_add")
let _ = prepend operators ("-", "#bv_sub")

let bvn2bv_handler pred op =
  ((pred,[|vt_xbvec;vt_int;vt_xbvec|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bv = val2bvec args.(0) in
     let n = val2int args.(1) in
     let bvr =
       try BVNH.find tbl_opbvn2bv (op,bv,n)
       with Not_found ->
         let bvv = sanitize_oflow (get_bvec bv) in
         let bvvr = match op with
             Vo_mul -> do_mul bvv n
           | Vo_shl -> do_shl bvv (int_of_big_int n)
           | Vo_shr -> do_shr bvv (int_of_big_int n) in
         let bvr = add_bvec bvvr in
           BVNH.add tbl_opbvn2bv (op,bv,n) bvr; bvr in
     [name,[|args.(0);args.(1);bvec2val bvr|]])

let _ = prepend find_handlers (bvn2bv_handler "#bv_mul" Vo_mul)
let _ = prepend find_handlers (bvn2bv_handler "#bv_shl" Vo_shl)
let _ = prepend find_handlers (bvn2bv_handler "#bv_shr" Vo_shr)
let _ = prepend operators ("*", "#bv_mul")

let bv2g_handler pred op =
  ((pred,[|vt_xbvec;vt_xbval|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let bv = val2bvec args.(0) in
     let br =
       try H.find tbl_opbv2g (op,bv)
       with Not_found ->
         let bvv = get_bvec bv in
         let br = match op with
             Vo_eqz -> add_bnot (do_nez bvv)
           | Vo_nez -> do_nez bvv
           | Vo_oflow -> snd3 bvv in
         H.add tbl_opbv2g (op,bv) br; br in
     [name,[|args.(0);bval2val br|]])

let _ = prepend find_handlers (bv2g_handler "#bv_eqz" Vo_eqz)
let _ = prepend find_handlers (bv2g_handler "#bv_nez" Vo_nez)
let _ = prepend find_handlers (bv2g_handler "#bv_oflow" Vo_oflow)

let bvbv2g_handler pred op =
  ((pred,[|vt_xbvec;vt_xbvec;vt_xbval|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bv0 = val2bvec args.(0) in
     let bv1 = val2bvec args.(1) in
     let br =
       try H.find tbl_opbvbv2g (op,bv0,bv1)
       with Not_found ->
         let bvv0 = get_bvec bv0 in
         let bvv1 = get_bvec bv1 in
         let br = match op with
             Vo_eq -> do_eq bvv0 bvv1
           | Vo_ne -> do_ne bvv0 bvv1
           | Vo_lt -> fst (do_cmp bvv0 bvv1)
           | Vo_gt -> fst (do_cmp bvv1 bvv0)
           | Vo_le -> let (ltv,eqv) = do_cmp bvv0 bvv1 in
                        add_bor ltv eqv
           | Vo_ge -> let (ltv,eqv) = do_cmp bvv1 bvv0 in
                        add_bor ltv eqv in
         H.add tbl_opbvbv2g (op,bv0,bv1) br; br in
     [name,[|args.(0);args.(1);bval2val br|]])

let _ = prepend find_handlers (bvbv2g_handler "#bv_eq" Vo_eq)
let _ = prepend find_handlers (bvbv2g_handler "#bv_ne" Vo_ne)
let _ = prepend find_handlers (bvbv2g_handler "#bv_lt" Vo_lt)
let _ = prepend find_handlers (bvbv2g_handler "#bv_gt" Vo_gt)
let _ = prepend find_handlers (bvbv2g_handler "#bv_le" Vo_le)
let _ = prepend find_handlers (bvbv2g_handler "#bv_ge" Vo_ge)
let _ = prepend operators ("==", "#bv_eq")
let _ = prepend operators ("!=", "#bv_ne")
let _ = prepend operators ("<", "#bv_lt")
let _ = prepend operators (">", "#bv_gt")
let _ = prepend operators ("<=", "#bv_le")
let _ = prepend operators (">=", "#bv_ge")

let _ = prepend find_handlers 
  (("#bv_split",[|vt_xbvec;vt_bool;vt_xbval;vt_list vt_xbval|]),
   [([|true;false;false;false|],[Sk_once]); 
    ([|false;true;true;true|],[Sk_once])],
   fun (name,args) ->
     if (is_val_const args.(0)) then
       let bvr = val2bvec args.(0) in
       let (s,oflow,vec) = get_bvec bvr in
       let bitlist = List.map bval2val (Array.to_list vec) in
        [name,[|args.(0); bool2val s; bval2val oflow; list2val None bitlist|]]
     else
       let s = val2bool args.(1) in
       let oflow = val2bval args.(2) in
       let vec = Array.of_list (List.map val2bval (val2list args.(3))) in
       let bvec = add_bvec (s, oflow, vec) in
        [name,[|bvec2val bvec; args.(1); args.(2); args.(3)|]])

let _ = register_package { empty_package with
  p_name = "solve_bitvector";
  p_reset = reset;
  p_find_handlers = !find_handlers;
  p_collect_handlers = !collect_handlers;
  p_sumtypes = [sum_bvec_bit];
  p_abstypes = [vt_xbvec];
  p_operators = !operators;
}

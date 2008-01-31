
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

(* Interface to the STP theorem prover *)

open Clpautil
open Flags
open Spec
open Big_int
open Builtin

module H = Hashtbl
module V = Vector
module IO = Streamio

open Biteval

let reset_fns : (unit -> unit) list ref = ref []
let reset() = List.iter (fun f -> f()) !reset_fns

let _ = prepend reset_fns Stp.vc_reset

type bvval = int

(* STP does not distinguish between signed and unsigned bitvectors, rather
 * signed and unsigned versions of operators are provided where they differ.
 * In our interface here we instead distinguish between signed and unsigned
 * bitvectors, and pick the appropriate version of an operation based on the
 * signs of the arguments. *)
type bvec = {
  signed: bool;
  bv: Stp.bv;
}

type bbit = Stp.bexpr

let tbl_bbits : bbit V.t = V.create 10
let _ = prepend reset_fns (fun () -> V.clear tbl_bbits)

let get_bbit bv = V.get tbl_bbits bv
let add_bbit bvv = V.append tbl_bbits bvv

let tbl_bvecs : bvec V.t = V.create 10
let _ = prepend reset_fns (fun () -> V.clear tbl_bvecs)

let get_bvec bv = V.get tbl_bvecs bv
let add_bvec bvv = V.append tbl_bvecs bvv

(* ID  -> bit expression mapping *)
let tbl_id2bvar : (t_val, Stp.bexpr) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_id2bvar)

(* ID -> bitvector mapping *)
let tbl_id2bv : (t_val * bool * int, bvval) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_id2bv)

type x2bop =
  | Bbo_cvt_val
  | Bbo_cvt_bval
  | Bbo_not

type bb2bop =
  | Bbo_and
  | Bbo_or
  | Bbo_implies
  | Bbo_iff
 
type x2bvop =
  | Vo_cvt_int
  | Vo_cvt_bval

type bv2bvop =
    Vo_neg
  | Vo_bnot
  | Vo_to_unsigned
  | Vo_to_signed

type bvbv2bvop =
    Vo_add
  | Vo_sub
  | Vo_band
  | Vo_bor
  | Vo_bxor
  | Vo_mul
  | Vo_div
  | Vo_mod
  | Vo_shl
  | Vo_shr 

type bvn2bvop =
  | Vo_shl_const
  | Vo_shr_const
  | Vo_length_cast

type bv2gop =
  | Vo_eqz
  | Vo_nez

type bvbv2gop =
  | Vo_eq
  | Vo_ne
  | Vo_lt
  | Vo_gt
  | Vo_le
  | Vo_ge

(* Satisfiability *)

(* Satisfying assignments constructed from SAT *)
let tbl_assigns : Stp.counterexample V.t = V.create 10
let _ = prepend reset_fns (fun () -> V.clear tbl_assigns)

(* Per-bval solver results and solve times (in seconds) *)
let tbl_results : (t_val, (int option)*float) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_results)

let debug_stp_solve = register_debug "stp_solve"
  "Print result of each STP query"

(* Get the STP variable corresponding to an abstract leaf *)
let bvar_id = ref 0
let get_bvar x =
  try H.find tbl_id2bvar x
  with Not_found ->
    let zx = Stp.b_newvar ("B" ^ (string_of_int !bvar_id)) in
    incr bvar_id;
    H.add tbl_id2bvar x zx; zx

(* Convert a bval to a STP bexpr *)
let rec bval_to_stp_bexpr (bv:bval) =
  match get_bval bv with
      Bb_const  c   -> if c then Stp.b_true () else Stp.b_false ()
    | Bb_var    v   -> get_bvar v
    | Bb_unop  (Bo_eq,v) -> bval_to_stp_bexpr v
    | Bb_unop  (Bo_not,v) -> Stp.b_not (bval_to_stp_bexpr v)
    | Bb_binop (Bo_and,vs) -> List.fold_left 
        (fun a v -> Stp.b_and (bval_to_stp_bexpr v) a) (Stp.b_true ()) vs
    | Bb_binop (Bo_or,vs) -> List.fold_left 
        (fun a v -> Stp.b_or (bval_to_stp_bexpr v) a) (Stp.b_false ()) vs
        
(* Spec integration *)

let find_handlers = ref []
let collect_handlers = ref []
let operators = ref []

let vt_xvar = vt_var "X"
let vt_yvar = vt_var "Y"
let vt_zvar = vt_var "Z"

let vt_cexample typ0 typ1 = make_type "t_stp_counterexample" [|typ0;typ1|]
let vk_cexample = register_val_kind {
  vki_tostring = (fun _ a -> "CEX#" ^ (string_of_int a));
  vki_compare = (fun _ _ -> failwith "Cannot compare counterexamples");
  vki_dump = (fun _ _ -> failwith "Cannot dump counterexamples");
  vki_load = (fun _ -> failwith "Cannot load counterexamples");
}

let val2cexample = val2cst vk_cexample
let cexample2val = cst2val vk_cexample

let vt_bvec typ0 typ1 = make_type "t_stp_bvec" [|typ0;typ1|]
let vk_bvec = register_val_kind {
  vki_tostring = (fun _ v -> 
(* "BV#" ^ (string_of_int v)); *)
    let testid = ref 0 in
    let bv = get_bvec v in
    incr testid;
    (Stp.string_of_bexpr (Stp.bv_eq bv.bv (Stp.bv_newvec ("STR#"^(string_of_int !testid)) (Stp.bv_nbits bv.bv)))));
  vki_compare = (fun _ _ -> failwith "Cannot compare bvecs");
  vki_dump = (fun _ _ -> failwith "Cannot dump bvec");
  vki_load = (fun _ -> failwith "Cannot load bvec");
}

let val2bvec = val2cst vk_bvec
let bvec2val = cst2val vk_bvec

let vt_bbit typ0 = make_type "t_stp_bit" [|typ0|]
let vk_bbit = register_val_kind {
  vki_tostring = (fun _ v -> (Stp.string_of_bexpr (get_bbit v)));
  vki_compare = (fun _ _ -> failwith "Cannot compare bbits");
  vki_dump = (fun _ _ -> failwith "Cannot dump bbit");
  vki_load = (fun _ -> failwith "Cannot load bbit");
}

let val2bbit = val2cst vk_bbit
let bbit2val = cst2val vk_bbit

let vt_xbvec = vt_bvec vt_xvar vt_yvar

let vt_xbbit = vt_bbit vt_xvar
let vt_xcexample = vt_cexample vt_xvar vt_yvar

(* Packages *)

let x2b_handler pred param op =
  ((pred,[|param;vt_xbbit|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let x = args.(0) in
     let bvvr = match op with
       | Bbo_cvt_val -> get_bvar x
       | Bbo_cvt_bval -> if Builtin.val2bool x then Stp.b_true () 
	 else Stp.b_false ()
       | Bbo_not -> Stp.b_not (get_bbit (val2bbit x)) in
     let bvr = add_bbit bvvr in
       [name,[|args.(0); bbit2val bvr|]])


let _ = prepend find_handlers (x2b_handler "id_s"   vt_yvar  Bbo_cvt_val)
let _ = prepend find_handlers (x2b_handler "bool_s" Builtin.vt_bool
				  Bbo_cvt_bval)
let _ = prepend find_handlers (x2b_handler "s_not"   vt_xbbit Bbo_not)
let _ = prepend operators ("!", "s_not")

let bb2b_handler pred op =
  ((pred,[|vt_xbbit;vt_xbbit;vt_xbbit|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let x = get_bbit (val2bbit args.(0)) in
     let y = get_bbit (val2bbit args.(1)) in
     let bvvr = match op with
       | Bbo_and -> Stp.b_and x y
       | Bbo_or  -> Stp.b_or x y 
       | Bbo_implies -> Stp.b_implies x y
       | Bbo_iff -> Stp.b_iff x y in
     let bvr = add_bbit bvvr in
       [name,[|args.(0); args.(1); bbit2val bvr|]])

let _ = prepend find_handlers (bb2b_handler "s_and"      Bbo_and)
let _ = prepend find_handlers (bb2b_handler "s_or"       Bbo_or)
let _ = prepend find_handlers (bb2b_handler "s_iff"      Bbo_iff)
let _ = prepend find_handlers (bb2b_handler "s_implies"  Bbo_implies)

let _ = prepend operators ("&&", "s_and")
let _ = prepend operators ("||", "s_or")
let _ = prepend operators ("implies", "s_implies")
let _ = prepend operators ("iff", "s_iff")

let bb2b_collect_handler name op basecase = 
  ((name,[|vt_xbbit;vt_xbbit|]),[|true;false|],
   fun (name,args) matches -> 
       let res = List.fold_left (fun b0 (_,args) ->
	 let b1 = get_bbit (val2bbit args.(0)) in
	   op b0 b1
       ) (basecase ()) matches in
       [name,[|anyval;bbit2val (add_bbit res)|]])

let _ = prepend collect_handlers (bb2b_collect_handler "s_or_all" Stp.b_or
				     Stp.b_false)
let _ = prepend collect_handlers (bb2b_collect_handler "s_and_all" Stp.b_and
				     Stp.b_true)

let stp_valid bv contextv =
  let start = Sys.time() in
    try fst (H.find tbl_results bv)
    with Not_found ->      
      let bexpr = get_bbit (val2bbit bv) in
      let context = get_bbit (val2bbit contextv) in
      if debug_stp_solve () then IO.printf "Expression: %s, Context %s\n" 
	(Stp.string_of_bexpr bexpr) (Stp.string_of_bexpr context);
      Stp.vc_push ();
      Stp.vc_assert context;
      let valid = Stp.vc_query bexpr in
      let elapsed = Sys.time() -. start in
      let res = if valid then None else Some (V.append tbl_assigns 
        (Stp.vc_get_counterexample ())) in
      Stp.vc_pop ();
      if debug_stp_solve () then begin
        IO.printf "result: %s, %f seconds\n" (if res <> None then "INVALID" else "VALID")
	  elapsed;
	Stp.vc_print_counterexample ()
      end;

        H.add tbl_results bv (res,elapsed); res
let stp_valid = make_track_2 "stp_valid" stp_valid


let _ = prepend find_handlers
  (("stp_valid",[|vt_xbbit;vt_xbbit|]),[[|true;true|],[Sk_zero;Sk_once]],
   fun (name,args) ->
     if stp_valid args.(0) args.(1) = None 
     then [name,args] else [])


let _ = prepend find_handlers
  (("stp_invalid", [|vt_xbbit;vt_xbbit;vt_xcexample|]), 
  [[|true;true;false|], [Sk_zero; Sk_once]],
  fun (name, args) ->
    match stp_valid args.(0) args.(1) with 
      | None    -> []
      | Some ce -> [name, [|args.(0); args.(1); cexample2val ce|]])

let _ = prepend find_handlers
  (("cexample_g",[|vt_xcexample;vt_xbbit|]),[[|true;true|],[Sk_zero; Sk_once]],
   fun (name,args) ->
     let ce = V.get tbl_assigns (val2cexample args.(0)) in
     if Stp.vc_get_bval (Stp.vc_get_bexpr_from_counterexample ce 
                            (get_bbit (val2bbit args.(1)))) = Stp.True 
     then [name,args] else [])

let stats_stp_counts = register_stats "stp_counts"
  "Summarize SAT solver problems and times"

let write_stp_counts() =
  if stats_stp_counts() then begin
    (* keep track of (total queries, total time, maximum time) *)
    let (q,t,m) = H.fold (fun _ (_,time) (q,t,m) ->
                            (q+1,t+.time,max m time)) tbl_results (0,0.,0.) in
      IO.printf "SAT Solving Stats:\n";
      IO.printf "  Count: %d\n" q;
      if q <> 0 then begin
        let avg = t /. (float_of_int q) in
          IO.printf " Total:   %.3f\n" t;
          IO.printf " Average: %.3f\n" avg;
          IO.printf " Max:     %.3f\n" m
      end
  end


(* Bitvectors *)

let _ = prepend collect_handlers
  (("sbv_all",[|vt_xbvec;vt_xbbit;vt_xbvec|]),[|true;true;false|],
   fun (name,args) matches -> match matches with
     | [] -> []
     | (_, x)::xs ->
       let bv0 = get_bvec (val2bvec x.(0)) in
       let len0 = Stp.bv_nbits bv0.bv in
       let g0 = get_bbit (val2bbit x.(1)) in
       let res = List.fold_left (fun bv (_,args) ->
	 let bv1 = get_bvec (val2bvec args.(0)) in
	 let len1 = Stp.bv_nbits bv1.bv in
	 let g1 = get_bbit (val2bbit args.(1)) in
	   if bv1.signed <> bv0.signed then 
	     pred_unexpected "Mismatching signedness in arguments to bv_all";
	   Stp.bv_or bv (Stp.bv_ite g1 bv1.bv (Stp.bv_from_int len1 0))
       ) (Stp.bv_ite g0 bv0.bv (Stp.bv_from_int len0 0)) xs in
       let bvr = add_bvec {signed = bv0.signed; bv = res} in
       [name,[|anyval;anyval;bvec2val bvr|]])

 let _ = prepend find_handlers
  (("cexample_bv",[|vt_xcexample;vt_xbvec;vt_int|]),
  [[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let av = V.get tbl_assigns (val2cexample args.(0)) in
     let bv = get_bvec (val2bvec args.(1)) in
     let cbv = Stp.vc_get_bv_from_counterexample av bv.bv in
     let nr = if bv.signed then Stp.big_int_of_signed_bv cbv else 
         Stp.big_int_of_unsigned_bv cbv in
       [name,[|args.(0);args.(1);int2val nr|]]) 

let _ = prepend find_handlers
  (("sbv_nbits",[|vt_xbvec;vt_int|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let bvec = get_bvec (val2bvec args.(0)) in
       [name,[|args.(0);sint2val (Stp.bv_nbits bvec.bv)|]])

let _ = prepend find_handlers
  (("sbv_bit",[|vt_xbvec;vt_int;vt_xbbit|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bvec = get_bvec (val2bvec args.(0)) in
     let n = val2sint args.(1) in
     let b = Stp.bv_bit_extract bvec.bv n in
       [name,[|args.(0);args.(1);bbit2val (add_bbit b)|]])

let _ = prepend find_handlers
  (("sbv_guard",[|vt_xbvec;vt_xbbit;vt_xbvec|]),
  [[|true;true;false|],[Sk_once]],
   fun (name, args) ->
     let bvec = get_bvec (val2bvec args.(0)) in  
     let g = get_bbit (val2bbit (args.(1))) in
     let bvr = add_bvec {bvec with bv = (Stp.bv_ite g bvec.bv 
			    (Stp.bv_from_int (Stp.bv_nbits bvec.bv) 0))} in
     [name,[|args.(0);args.(1);bvec2val bvr|]])


let x2bv_handler pred param op =
  ((pred,[|param;vt_bool;vt_int;vt_xbvec|]),
  [[|true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let x = args.(0) in
     let vsigned = val2bool args.(1) in
     let len = val2sint args.(2) in
     let bvvr = match op with
       | Vo_cvt_int -> Stp.bv_from_big_int len (val2int x)
       | Vo_cvt_bval -> Stp.bv_concat 
	   (Stp.bv_from_int (len - 1) 0) 
	     (Stp.bv_from_bexpr (get_bbit (val2bbit x))) in
     let bvr = add_bvec {signed = vsigned; bv = bvvr} in
       [name,[|args.(0); args.(1); args.(2); bvec2val bvr|]])

let _ = prepend find_handlers (x2bv_handler "int_sbv" vt_int   Vo_cvt_int)
let _ = prepend find_handlers (x2bv_handler "g_sbv"   vt_xbbit Vo_cvt_bval)

let bvec_id = ref 0
let _ = prepend find_handlers 
  (("id_sbv",[|vt_yvar;vt_bool;vt_int;vt_xbvec|]),
   [[|true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let x = args.(0) in
     let vsigned = val2bool args.(1) in
     let len = val2sint args.(2) in
     let bvr =
       try H.find tbl_id2bv (x,vsigned,len)
       with Not_found ->
(*	 let name = (if vsigned then "S" else "U") ^ 
	   (string_of_int len) ^ (full_string_of_val x) in*)
	 let name = "V" ^ (string_of_int !bvec_id) in
         let bvvr = {signed = vsigned; bv = Stp.bv_newvec name len} in
         let bvr = add_bvec bvvr in
	   incr bvec_id;
           H.add tbl_id2bv (x,vsigned,len) bvr; bvr in
     [name,[|args.(0); args.(1); args.(2); bvec2val bvr|]])

let bv2bv_handler pred op =
  ((pred,[|vt_xbvec;vt_xbvec|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let bvv = get_bvec (val2bvec args.(0)) in
     let bvvr = match op with
       | Vo_neg -> 
	   if not bvv.signed then pred_unexpected 
	     "Unsigned bitvector passed to sbv_neg"; 
           {bvv with bv = Stp.bv_negate bvv.bv}
       | Vo_bnot -> {bvv with bv = Stp.bv_not bvv.bv}
       | Vo_to_signed -> {bvv with signed = true}
       | Vo_to_unsigned -> {bvv with signed = false} in
       [name,[|args.(0);bvec2val (add_bvec bvvr)|]])

let _ = prepend find_handlers (bv2bv_handler "sbv_neg"  Vo_neg)
let _ = prepend find_handlers (bv2bv_handler "sbv_bnot" Vo_bnot)
let _ = prepend find_handlers (bv2bv_handler "sbv_to_signed" Vo_to_signed)
let _ = prepend find_handlers (bv2bv_handler "sbv_to_unsigned" Vo_to_unsigned)

let _ = prepend operators ("uminus", "sbv_neg")

(* Check that the signs of two bitvectors agree. Returns the common sign *)
let check_signs bv1 bv2 =
  let string_of_signed s = if s then "signed" else "unsigned" in
  if bv1.signed <> bv2.signed then pred_unexpected 
    ("Mismatching signs " ^ (string_of_signed bv1.signed) ^ " and " ^
	(string_of_signed bv2.signed));
  bv1.signed

let bvbv2bv_handler pred op =
  ((pred,[|vt_xbvec;vt_xbvec;vt_xbvec|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bvv0 = get_bvec (val2bvec args.(0)) in
     let bvv1 = get_bvec (val2bvec args.(1)) in
     let nbits = Stp.bv_nbits bvv0.bv in
     let signed = if op <> Vo_shl && op <> Vo_shr then check_signs bvv0 bvv1 
       else bvv0.signed in
     let bvvr = match op with
         Vo_add -> Stp.bv_plus nbits bvv0.bv bvv1.bv
       | Vo_sub -> Stp.bv_minus nbits bvv0.bv bvv1.bv
       | Vo_band -> Stp.bv_and bvv0.bv bvv1.bv
       | Vo_bor -> Stp.bv_or bvv0.bv bvv1.bv
       | Vo_bxor -> Stp.bv_xor bvv0.bv bvv1.bv
       | Vo_mul -> Stp.bv_mult nbits bvv0.bv bvv1.bv
       | Vo_div -> (if signed then Stp.bv_sdiv else Stp.bv_udiv) 
	   nbits bvv0.bv bvv1.bv
       | Vo_mod -> (if signed then Stp.bv_smod else Stp.bv_umod) 
	   nbits bvv0.bv bvv1.bv
       | Vo_shl -> if bvv1.signed then pred_unexpected
	     "Argument to left shift must be unsigned";
	   Stp.bv_lshift nbits bvv0.bv bvv1.bv
       | Vo_shr -> if bvv1.signed then pred_unexpected
	     "Argument to right shift must be signed";
	   (if signed then Stp.bv_srshift else Stp.bv_urshift)
	     nbits bvv0.bv bvv1.bv in
     let bvr = add_bvec {signed = signed; bv = bvvr} in
       [name,[|args.(0);args.(1);bvec2val bvr|]])

let _ = prepend find_handlers (bvbv2bv_handler "sbv_add"  Vo_add)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_sub"  Vo_sub)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_band" Vo_band)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_bor"  Vo_bor)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_bxor" Vo_bxor)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_mul"  Vo_mul)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_div"  Vo_div)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_mod"  Vo_mod)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_shl"  Vo_shl)
let _ = prepend find_handlers (bvbv2bv_handler "sbv_shr"  Vo_shr)
let _ = prepend operators ("+", "sbv_add")
let _ = prepend operators ("-", "sbv_sub")
let _ = prepend operators ("and", "sbv_band")
let _ = prepend operators ("or", "sbv_bor")
let _ = prepend operators ("xor", "sbv_bxor")
let _ = prepend operators ("*", "sbv_mul")
let _ = prepend operators ("/", "sbv_div")
let _ = prepend operators ("mod", "sbv_mod")
let _ = prepend operators ("shl", "sbv_shl")
let _ = prepend operators ("shr", "sbv_shr")

let bvn2bv_handler pred op =
  ((pred,[|vt_xbvec;vt_int;vt_xbvec|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bvv = get_bvec (val2bvec args.(0)) in
     let n = val2sint args.(1) in
     let bvvr = match op with
       | Vo_length_cast -> 
	   if bvv.signed then Stp.bv_sign_extend bvv.bv n else 
	     let bvl = Stp.bv_nbits bvv.bv in
  	       if bvl > n then 
		 Stp.bv_concat (Stp.bv_from_int (n - bvl) 0) bvv.bv
	       else Stp.bv_extract bvv.bv (n-1) 0
       | Vo_shl_const -> Stp.bv_lshift_const bvv.bv n
       | Vo_shr_const -> Stp.bv_rshift_const bvv.bv n in
     let bvr = add_bvec {bvv with bv = bvvr} in
       [name,[|args.(0);args.(1);bvec2val bvr|]])
(*
let _ = prepend find_handlers (bvn2bv_handler "sbv_shl_const" Vo_shl_const)
let _ = prepend find_handlers (bvn2bv_handler "sbv_shr_const" Vo_shr_const)
*)

let _ = prepend find_handlers (bvn2bv_handler "sbv_length_cast" Vo_length_cast)

let bv2g_handler pred op =
  ((pred,[|vt_xbvec;vt_xbbit|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let bvv = (get_bvec (val2bvec args.(0))).bv in
     let bvz = Stp.bv_from_int (Stp.bv_nbits bvv) 0 in
     let br = match op with
         Vo_eqz -> Stp.bv_eq bvv bvz
       | Vo_nez -> Stp.b_not (Stp.bv_eq bvv bvz) in
	   [name,[|args.(0);bbit2val (add_bbit br)|]])

let _ = prepend find_handlers (bv2g_handler "sbv_eqz" Vo_eqz)
let _ = prepend find_handlers (bv2g_handler "sbv_nez" Vo_nez)

let bvbv2g_handler pred op =
  ((pred,[|vt_xbvec;vt_xbvec;vt_xbbit|]),[[|true;true;false|],[Sk_once]],
   fun (name,args) ->
     let bvv0 = get_bvec (val2bvec args.(0)) in
     let bvv1 = get_bvec (val2bvec args.(1)) in
     let signed = check_signs bvv0 bvv1 in
     let br = match op with
         Vo_eq  -> Stp.bv_eq bvv0.bv bvv1.bv
       | Vo_ne  -> Stp.b_not (Stp.bv_eq bvv0.bv bvv1.bv)
       | Vo_lt -> (if signed then Stp.bv_slt else Stp.bv_ult) bvv0.bv bvv1.bv
       | Vo_le -> (if signed then Stp.bv_sle else Stp.bv_ule) bvv0.bv bvv1.bv
       | Vo_gt -> (if signed then Stp.bv_sgt else Stp.bv_ugt) bvv0.bv bvv1.bv
       | Vo_ge -> (if signed then Stp.bv_sge else Stp.bv_uge) bvv0.bv bvv1.bv in
       [name,[|args.(0);args.(1);bbit2val (add_bbit br)|]])

let _ = prepend find_handlers (bvbv2g_handler "sbv_eq" Vo_eq)
let _ = prepend find_handlers (bvbv2g_handler "sbv_ne" Vo_ne)
let _ = prepend find_handlers (bvbv2g_handler "sbv_lt" Vo_lt)
let _ = prepend find_handlers (bvbv2g_handler "sbv_gt" Vo_gt)
let _ = prepend find_handlers (bvbv2g_handler "sbv_le" Vo_le)
let _ = prepend find_handlers (bvbv2g_handler "sbv_ge" Vo_ge)
let _ = prepend operators ("==", "sbv_eq")
let _ = prepend operators ("!=", "sbv_ne")
let _ = prepend operators ("<", "sbv_lt")
let _ = prepend operators ("<=", "sbv_le")
let _ = prepend operators (">", "sbv_gt")
let _ = prepend operators (">=", "sbv_ge")


(*
let _ = prepend find_handlers 
  (("#sbv_split",[|vt_xbvec;vt_bool;vt_xbval;vt_list vt_xbval|]),
   [[|true;false;false;false|];[|false;true;true;true|]],
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

*)

(* Arrays *)

(* ID -> array mapping *)
let tbl_id2bvarray : (t_val*int*bool*int, int) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_id2bvarray)

type bvarray = {
  a_signed: bool; (* Are the contents signed? *)
  bva: Stp.bvarray;
}

let tbl_bvarray : bvarray V.t = V.create 10
let _ = prepend reset_fns (fun () -> V.clear tbl_bvarray)

let get_bvarray bv = V.get tbl_bvarray bv
let add_bvarray bvv = V.append tbl_bvarray bvv

let vt_bvarray typ0 typ1 typ2 = make_type "t_stp_array" [|typ0;typ1;typ2|]
let vk_bvarray = register_val_kind {
  vki_tostring = (fun _ v -> "A#" ^ (string_of_int v));(*(Stp.string_of_bvarray (get_bvarray v)));*)
  vki_compare = (fun _ _ -> failwith "Cannot compare bvarrays");
  vki_dump = (fun _ _ -> failwith "Cannot dump barrays");
  vki_load = (fun _ -> failwith "Cannot load barrays");
}

let val2bvarray = val2cst vk_bvarray
let bvarray2val = cst2val vk_bvarray
let vt_xbvarray = vt_bvarray vt_xvar vt_yvar vt_zvar

let arr_id = ref 0
let _ = prepend find_handlers 
  (("id_array",[|vt_zvar;vt_int;vt_bool;vt_int;vt_xbvarray|]),
   [[|true;true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let x = args.(0) in
     let idxlen = val2sint args.(1) in
     let valsigned = val2bool args.(2) in
     let vallen = val2sint args.(3) in
     let bvr =
       try H.find tbl_id2bvarray (x,idxlen,valsigned,vallen)
       with Not_found ->
	 (*let name = (string_of_int idxlen) ^ (if valsigned then "S" else "U") ^
	   (string_of_int vallen) ^ (full_string_of_val x) in*)
	 let name = "A" ^ (string_of_int !arr_id) in
         let bvvr = Stp.bva_new name idxlen vallen in
         let bvr = add_bvarray {a_signed = valsigned; bva = bvvr} in
	   incr arr_id;
           H.add tbl_id2bvarray (x,idxlen,valsigned,vallen) bvr; bvr in
     [name,[|args.(0); args.(1); args.(2); args.(3); bvarray2val bvr|]])

let _ = prepend find_handlers 
  (("load",[|vt_xbvarray;vt_xbvec;vt_int;vt_xbvec|]),
   [[|true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let a0 = get_bvarray (val2bvarray args.(0)) in
     let idx = get_bvec (val2bvec args.(1)) in
     let len = val2sint args.(2) in
     let bvr = add_bvec 
       {signed = a0.a_signed; bv = Stp.bva_read a0.bva idx.bv len} in
     [name,[|args.(0); args.(1); args.(2); bvec2val bvr|]])

let _ = prepend find_handlers 
  (("store",[|vt_xbvarray;vt_xbvec;vt_xbvec;vt_xbvarray|]),
   [[|true;true;true;false|],[Sk_once]],
   fun (name,args) ->
     let a0 = get_bvarray (val2bvarray args.(0)) in
     let idx = get_bvec (val2bvec args.(1)) in
     let value = get_bvec (val2bvec args.(2)) in
     if a0.a_signed <> value.signed then pred_unexpected
       "Sign mismatch in array store";
     let bvr = add_bvarray 
       {a0 with bva = Stp.bva_write a0.bva idx.bv value.bv} in
     [name,[|args.(0); args.(1); args.(2); bvarray2val bvr|]])

let _ = register_package { empty_package with
  p_name = "solve_stp";
  p_writeout = write_stp_counts;
  p_reset = reset;
  p_find_handlers = !find_handlers;
  p_collect_handlers = !collect_handlers;
  p_operators = !operators;
  p_abstypes = [vt_xcexample; vt_xbvec; vt_xbbit; vt_xbvarray];
}

(*
 let _ = 
  let bv1 = Stp.bv_from_int 17 31487 in
  let bv2 = Stp.bv_from_big_int 17 (Big_int.big_int_of_int 31487) in
  IO.printf "%s\n" (Stp.string_of_bexpr (Stp.bv_eq bv1 bv2))
*)

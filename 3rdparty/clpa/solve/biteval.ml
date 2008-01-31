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

(* Boolean formula representation and evaluation
 * Formalas may be constructed and either translated into CNFs, eagerly
 * reduced to BDDs, or a combination of the two.
 * Leaves are abstract, except for true/false *)

open Clpautil
open Flags
open Spec

module IO = Streamio
module H = Hashtbl
module V = Vector

type bval = int

type unop =
    Bo_eq
  | Bo_not

type binop =
    Bo_and
  | Bo_or

type bbit =
    Bb_const of bool
  | Bb_var of t_val
  | Bb_unop of unop * bval
  | Bb_binop of binop * bval list

type simplify_level = int

type binfo = {
  mutable bi_bit : bbit;
  mutable bi_simp : bool;
  bi_simp_level : simplify_level;
}

let reset_fns : (unit -> unit) list ref = ref []
let reset() = List.iter (fun f -> f()) !reset_fns

(* CNFs *)

type df = (t_val * bool) list
type cnf = df list option

(* Bit evaluation info *)

(* Since there may be many boolean formula clients who may need to interact
 * with each other, and since there is only one Cuddy, all bit evaluation
 * stuff is global *)

let tbl_bvals : binfo V.t = V.create 10

let add_bval bit simp level = V.append tbl_bvals
  { bi_bit = bit; bi_simp = simp; bi_simp_level = level; }

let set_simp v = (V.get tbl_bvals v).bi_simp <- true

let get_bval v = (V.get tbl_bvals v).bi_bit
let get_level v = (V.get tbl_bvals v).bi_simp_level

let btrue : bval = add_bval (Bb_const true) true 100
let bfalse : bval = add_bval (Bb_const false) true 100

let _ = prepend reset_fns (fun () -> V.shrink tbl_bvals 2)

let tbl_bvar2val  : (t_val,bval) H.t = H.create 10
let tbl_unop2val  : (unop*bval,bval) H.t = H.create 10
let tbl_binop2val : (binop*bval list,bval) H.t = H.create 10
let tbl_mvals     : (binop*t_val,bval) H.t = H.create 10

let _ = prepend reset_fns (fun () ->
  H.clear tbl_bvar2val;
  H.clear tbl_unop2val;
  H.clear tbl_binop2val;
  H.clear tbl_mvals)

let rec compare_bval v0 v1 =
  assert (V.get tbl_bvals v0).bi_simp;
  assert (V.get tbl_bvals v1).bi_simp;
  if v0 = v1 then 0
  else match (get_bval v0,get_bval v1) with
      (Bb_const b0,Bb_const b1) -> compare b0 b1
    | (Bb_const _,_) -> ~-1
    | (_,Bb_const _) -> 1
    | (Bb_var v0,Bb_var v1) -> compare_vals v0 v1
    | (Bb_var _,_) -> ~-1
    | (_,Bb_var _) -> 1
    | (Bb_unop(op0,v0),Bb_unop(op1,v1)) ->
        let cmp = compare op0 op1 in
          if cmp <> 0 then cmp else compare_bval v0 v1
    | (Bb_unop _,_) -> ~-1
    | (_,Bb_unop _) -> 1
    | (Bb_binop(op0,vals0),Bb_binop(op1,vals1)) ->
        let cmp = compare op0 op1 in
          if cmp <> 0 then cmp else compare_lists compare_bval vals0 vals1

(* find the number of distinct sub-formulas in a bval *)
let size_of_bval v =
  let seen : (bval,unit) H.t = H.create 10 in
  let rec get_size v =
    if H.mem seen v then 0
    else let _ = H.add seen v () in
      match get_bval v with
          Bb_const _ -> 0
        | Bb_var _ -> 1
        | Bb_unop(_,v) -> 1 + (get_size v)
        | Bb_binop(_,vals) -> List.fold_left (+) 1
            (List.map get_size vals) in
  get_size v

let extract_bval v fn =
  let seen = H.create 10 in
  let rec extract v = match get_bval v with
      Bb_const _ -> ()
    | Bb_var x -> List.iter (fun z -> H.replace seen z ()) (fn x)
    | Bb_unop(_,v) -> extract v
    | Bb_binop(_,vals) -> List.iter extract vals in
  extract v; H.fold (fun z _ list -> z::list) seen []

(* Stringifying *)

let debug_bval_nocompress = register_debug "bval_nocompress"
  "Do not compress extremely long bval strings into BIT[LEN]"

let string_of_bval d v =
  let buf = Buffer.create 10000 in
  let push_str s =
    Buffer.add_string buf s;
    if Buffer.length buf > 10000 && not (debug_bval_nocompress()) then
      failwith "push_str" in
  let rec crawl d v =
    if d = 0 then push_str "..."
    else match get_bval v with
        Bb_const true -> push_str "T"
      | Bb_const false -> push_str "F"
      | Bb_var xv -> push_str (string_of_val (d-1) xv)
      | Bb_unop(Bo_eq,v) -> crawl (d-1) v
      | Bb_unop(Bo_not,v) -> push_str "!"; crawl (d-1) v
      | Bb_binop(op,vals) ->
          push_str "(";
          let opstr = if op = Bo_and then "&" else "|" in
          let rec process = function
              v::vxs ->
                crawl (d-1) v;
                push_str (if vxs = [] then ")" else opstr);
                process vxs
            | [] -> () in
          process vals in
  try crawl d v; Buffer.contents buf
  with (Failure "push_str") ->
    "BIT[" ^ (string_of_int (size_of_bval v)) ^ "]"

let string_of_df df =
  let string_of_xp (xv,p) =
    (if p then "" else "~") ^ (full_string_of_val xv) in
  "(" ^ (sep_string_of_list "|" string_of_xp df) ^ ")"

let string_of_cnf = function
    Some cnf -> sep_string_of_list "&" string_of_df cnf
  | None -> "F"

(* Simplification *)

let simplifiers :
  (int * (simplify_level -> bbit -> bval option)) list ref = ref []
let add_simplifier priority fn =
  let compare (n0,_) (n1,_) = compare n0 n1 in
    simplifiers := list_merge compare !simplifiers [priority,fn]

let follow_eq v = match get_bval v with
    Bb_unop(Bo_eq,v) -> v
  | _ -> v

let debug_bval_simplify = register_debug "bval_simplify"
  "Print bval simplification steps performed"

(* set fixed and fold operations up as much as possible *)
let rec simplify v =
  let rec try_simplifiers v prev =
    try let newv = findopt_list (fun (priority,fn) ->
                     if get_level v < priority then None
                     else fn (get_level v) (get_bval v)) !simplifiers in
      try_simplifiers newv (newv::prev)
    with Not_found -> (v,prev) in
  if (V.get tbl_bvals v).bi_simp then follow_eq v
  else begin
    let (resv,newvs) = try_simplifiers v [] in
      if debug_bval_simplify() then begin
        IO.printf "Initial: %s\n" (string_of_bval !print_level v);
        List.iter (fun newv ->
            IO.printf "Simplified: %s\n" (string_of_bval !print_level newv))
          (List.rev newvs)
      end;
      (V.get tbl_bvals resv).bi_simp <- true;
      if resv <> v then begin
        (V.get tbl_bvals v).bi_simp <- true;
        (V.get tbl_bvals v).bi_bit <- Bb_unop(Bo_eq,resv)
      end;
      follow_eq v
  end

let simplify = make_track_1 "simplify" simplify

let add_var x =
  try H.find tbl_bvar2val x
  with Not_found ->
    let vr = add_bval (Bb_var x) true 100 in
      H.add tbl_bvar2val x vr; vr

let add_unop level op v =
  try follow_eq (H.find tbl_unop2val (op,v))
  with Not_found ->
    let vr = simplify (add_bval (Bb_unop(op,v)) false level) in
      H.add tbl_unop2val (op,v) vr; vr

let add_binop level op = function
    [] -> if op = Bo_and then btrue else bfalse
  | [v] -> v
  | vals -> let vals = list_sort compare_bval vals in
      try follow_eq (H.find tbl_binop2val (op,vals))
      with Not_found ->
        let vr = simplify (add_bval (Bb_binop(op,vals)) false level) in
          H.add tbl_binop2val (op,vals) vr; vr

let rec is_negation level v nv =
  match (get_bval v, get_bval nv) with
      (Bb_unop(Bo_not,nv'),_) when nv = nv' -> true
    | (_,Bb_unop(Bo_not,v')) when v = v' -> true
    | (Bb_const b, Bb_const nb) when b <> nb -> true
    | (Bb_binop(vop,vals),Bb_binop(nvop,nvals)) when vop <> nvop ->
        get_level v >= level &&
        get_level nv >= level &&
        List.for_all (fun v -> List.exists (is_negation level v) nvals) vals &&
        List.for_all (fun nv -> List.exists (is_negation level nv) vals) nvals
    | _ -> false

(* simplify degenerate binops with 0 or 1 members *)
let _ = add_simplifier 3 (fun _ -> function
    Bb_binop(op,[]) -> Some (if op = Bo_and then btrue else bfalse)
  | Bb_binop(op,[v]) -> Some v
  | _ -> None)

(* constant fold booleans out of unops/binops *)
let _ = add_simplifier 4 (fun level -> function
    Bb_unop(Bo_eq,v') -> Some v'
  | Bb_unop(Bo_not,v') ->
      (match get_bval v' with
           Bb_const true -> Some bfalse
         | Bb_const false -> Some btrue
         | Bb_unop(Bo_not,nv') -> Some nv'
         | _ -> None)
  | Bb_binop(Bo_and,vals) ->
      if List.exists ((=)bfalse) vals then Some bfalse
      else let vals' = List.filter ((<>)btrue) vals in
        if vals <> vals' then Some (add_binop level Bo_and vals') else None
  | Bb_binop(Bo_or,vals) ->
      if List.exists ((=)btrue) vals then Some btrue
      else let vals' = List.filter ((<>)bfalse) vals in
        if vals <> vals' then Some (add_binop level Bo_or vals') else None
  | _ -> None)

(* apply demorgan's rule to any negated binop where the negated children
 * outnumber the non-negated children *)
let _ = add_simplifier 5 (fun level -> function
    Bb_unop(Bo_not,v) ->
      (match get_bval v with
           Bb_binop(op,vals) when get_level v >= 5 ->
             let level = min level (get_level v) in
             let (pos,neg) = List.fold_left (fun (pos,neg) v ->
               match get_bval v with
                   Bb_unop(Bo_not,_) -> (pos,neg+1)
                 | _ -> (pos+1,neg)) (0,0) vals in
             if neg > pos then
               let op' = (if op = Bo_and then Bo_or else Bo_and) in
               let vals = List.map (add_unop level Bo_not) vals in
                 Some (add_binop level op' vals)
             else None
         | _ -> None)
  | _ -> None)

(* flatten binops with the same kind together: A&(B&C) => A&B&C
 * apply demorgan's rule to any negated binops of the opposite kind *)
let _ = add_simplifier 6 (fun level -> function
    Bb_binop(op,vals) ->
      let (vals',level) = list_fold_right (fun v (vals',level) ->
        match get_bval v with
            Bb_binop(sop,svals) when op = sop && get_level v >= 6 ->
              (list_merge compare_bval vals' svals, min level (get_level v))
          | Bb_unop(Bo_not,nv) when get_level v >= 6 ->
              (match get_bval nv with
                   Bb_binop(nop,nsvals) when op <> nop && get_level nv >= 6 ->
                     let svals = List.map (add_unop level Bo_not) nsvals in
                     let svals = list_sort compare_bval svals in
                       (list_merge compare_bval vals' svals,
                        min (min level (get_level v)) (get_level nv))
                 | _ -> (v::vals',min level (get_level v)))
          | _ -> (v::vals',level)) vals ([],level) in
      if vals <> vals' then Some (add_binop level op vals') else None
  | _ -> None)

(* remove duplicates from binops and check for contradictions *)
let _ = add_simplifier 7 (fun level -> function
    Bb_binop(op,vals) ->
      let contradiction = List.exists (fun v ->
        List.exists (is_negation 7 v) vals) vals in
      if contradiction then
        Some (if op = Bo_and then bfalse else btrue)
      else let vals' = rmdups_list compare_bval vals in
        if vals <> vals' then Some (add_binop level op vals') else None
  | _ -> None)

(* simplify X&Y => X&(Y[X->true]), X|Y => X|(Y[X->false]) *)
let _ = add_simplifier 21 (fun level -> function
    Bb_binop(op,vals) ->
      let has_val topv v =
        not (v = topv) && List.exists ((=)v) vals in
      let has_neg topv v =
        not (is_negation 21 v topv) && List.exists (is_negation 21 v) vals in
      let rec map_sub topv v =
        if has_val topv v then (if op = Bo_and then btrue else bfalse)
        else if has_neg topv v then (if op = Bo_and then bfalse else btrue)
        else let level = get_level v in
          if level < 21 then v else
            match get_bval v with
                Bb_binop(sop,svals) ->
                  add_binop level sop (List.map (map_sub topv) svals)
              | Bb_unop(sop,nv) -> add_unop level sop (map_sub topv nv)
              | _ -> v in
      let vals' = List.map (fun v -> map_sub v v) vals in
        if vals <> vals' then Some (add_binop level op vals') else None
  | _ -> None)

(* simplify (X&Y)|(X&Z) => X&(Y|Z), aka diamond property *)
let _ = add_simplifier 22 (fun level -> function
    Bb_binop(op,vals) when List.length vals > 1 ->
      let vals' = List.map (fun v0 ->
        match get_bval v0 with
            Bb_binop(op0,vals0) when op <> op0 && get_level v0 >= 22 ->
             (try findopt_list (fun v1 ->
                match get_bval v1 with
                    Bb_binop(op1,vals1) when
                        op0 = op1 && vals0 <> vals1 && get_level v1 >= 22 ->
                      let common = List.filter
                        (fun v -> List.exists ((=)v) vals1) vals0 in
                      if common <> [] then
                        let sep0 = add_binop (min level (get_level v0)) op0
                          (List.filter (fun v ->
                             not (List.exists ((=)v) common)) vals0) in
                        let sep1 = add_binop (min level (get_level v1)) op1
                          (List.filter (fun v ->
                             not (List.exists ((=)v) common)) vals1) in
                        let csep = add_binop level op [sep0;sep1] in
                          Some (add_binop level op0 (csep::common))
                      else None
                  | _ -> None) vals
              with Not_found -> v0)
          | _ -> v0) vals in
      if vals <> vals' then Some (add_binop level op vals') else None
  | _ -> None)

(* CNF Evaluation *)

(* Based in part on earlier implementation by Yichen Xie
 * <yxie@cs.stanford.edu> *)

let tbl_reshash : (bval*bool,cnf) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear tbl_reshash)

type eqvar = int
let eqvar_count = ref 0

let eqvar_kind = register_val_kind {
  vki_tostring = (fun _ x -> "EQX#" ^ (string_of_int x));
  vki_compare = compare;
  vki_dump = (fun _ _ -> failwith "Cannot dump eqvar");
  vki_load = (fun _ -> failwith "Cannot load eqvar");
}
let bval2eqvar = val2cst eqvar_kind

let tbl_val2eqvar : (bval,t_val) H.t = H.create 10
let tbl_eqvar2def : (eqvar,cnf*cnf) H.t = H.create 10
let uncommitted_cnfs : cnf list ref = ref []
let get_eqvar_cnfs = H.find tbl_eqvar2def

let _ = prepend reset_fns (fun () ->
  eqvar_count := 0;
  H.clear tbl_val2eqvar;
  H.clear tbl_eqvar2def;
  uncommitted_cnfs := [])

let rec get_cnf p cv =
  try H.find tbl_reshash (cv,p)
  with Not_found ->
    let res = match get_bval cv with
        Bb_const b ->
          if b = p then Some [] else None
      | Bb_var x ->
          if p then Some [[(x,true)]] else Some [[(x,false)]]
      | Bb_unop (op,cv') ->
          (match op with
               Bo_eq -> get_cnf p cv'
             | Bo_not -> get_cnf (not p) cv')
      | Bb_binop (op,cvs) ->
          let combfn = (match op with
              Bo_and -> (if p then cnf_and else cnf_or) p
            | Bo_or  -> (if p then cnf_or else cnf_and) p) in
          let cnfs = List.map (fun cv -> (follow_eq cv,get_cnf p cv)) cvs in
            snd (List.fold_left combfn (List.hd cnfs) (List.tl cnfs)) in
    H.add tbl_reshash (cv,p) res; res

and cnf_and p (cv0,cnf0) (cv1,cnf1) =
  let ncv = add_binop 0 (if p then Bo_and else Bo_or) [cv0;cv1] in
  let reduce_cnf (cv,cnf) =
    if List.length (get_some cnf) > 5 then [[ (add_eqvar cv,p) ]]
    else (get_some cnf) in
  if cnf0 = None || cnf1 = None then (ncv,None)
  else (ncv,Some ((reduce_cnf (cv0,cnf0)) @ (reduce_cnf (cv1,cnf1))))

and cnf_or p (cv0,cnf0) (cv1,cnf1) =
  let ncv = add_binop 0 (if p then Bo_or else Bo_and) [cv0;cv1] in
  match (cnf0,cnf1) with
      (None, x)
    | (x, None) -> (ncv,x)
    | (Some [], _)
    | (_, Some []) -> (ncv,Some [])
    | (Some [[x]], y)
    | (y, Some [[x]]) -> (ncv,clause_or x y)
    | (Some [x], Some [y]) when List.length x + List.length y < 10 ->
        (ncv,Some ([x @ y]))
    | (y, Some [_]) ->
        let x = add_eqvar cv1 in
          (ncv,clause_or (x,p) y)
    | (Some _, y) ->
        let x = add_eqvar cv0 in
          (ncv,clause_or (x,p) y)

and clause_or (x,p) cnf = match cnf with
    Some cnf -> Some (List.fold_left (fun cnf df -> ((x,p)::df)::cnf) [] cnf)
  | None -> Some [[(x,p)]]

and add_eqvar cv =
  try H.find tbl_val2eqvar cv
  with Not_found ->
    let tcnf = get_cnf true cv in
    let fcnf = get_cnf false cv in
    let x = cst2val eqvar_kind !eqvar_count in
      incr eqvar_count;
      prepend uncommitted_cnfs (clause_or (x,false) tcnf);
      prepend uncommitted_cnfs (clause_or (x,true) fcnf);
      H.add tbl_val2eqvar cv x;
      H.add tbl_eqvar2def (!eqvar_count - 1) (tcnf,fcnf); x

let get_uncommitted_cnfs() =
  let res = !uncommitted_cnfs in
    uncommitted_cnfs := []; res

(* Spec integration *)

let dump_bval ds v =
  let dumped : (bval,unit) H.t = H.create 10 in
  let rec dumper ds v =
    if H.mem dumped v then (IO.dump_byte ds 0x00; IO.dump_int ds v)
    else match get_bval v with
        Bb_const b ->
          IO.dump_byte ds 0x01;
          IO.dump_bool ds b
      | Bb_var xv ->
          IO.dump_byte ds 0x02;
          H.add dumped v (); IO.dump_int ds v;  (* share common leaves *)
          dump_val ds xv
      | Bb_unop(op,v) ->
          IO.dump_byte ds 0x03;
	  IO.dump_int ds (get_level v);
          IO.dump_byte ds (match op with
                               Bo_eq -> 0x10
                             | Bo_not -> 0x11);
          dumper ds v
      | Bb_binop(op,vals) ->
          IO.dump_byte ds 0x04;
          H.add dumped v (); IO.dump_int ds v;  (* share common binops *)
	  IO.dump_int ds (get_level v);
          IO.dump_byte ds (match op with
                               Bo_and -> 0x20;
                             | Bo_or -> 0x21);
          IO.dump_list ds dumper vals in
  dumper ds (simplify v)

let load_bval ls =
  let loaded : (bval,bval) H.t = H.create 10 in
  let rec loader ls =
    match IO.load_byte ls with
        0x00 ->
          let oldbv = IO.load_int ls in
            (try H.find loaded oldbv
             with Not_found -> IO.loaderror "load_bval_share")
      | 0x01 -> if IO.load_bool ls then btrue else bfalse
      | 0x02 ->
          let oldbv = IO.load_int ls in
          let newbv = add_var (load_val ls) in
            H.add loaded oldbv newbv; newbv
      | 0x03 ->
          let level = IO.load_int ls in
          let op = (match IO.load_byte ls with
                        0x10 -> Bo_eq
                      | 0x11 -> Bo_not
                      | _ -> IO.loaderror "load_bval_unop") in
          let v = loader ls in
          let newbv = add_unop level op v in
            set_simp newbv; newbv
      | 0x04 ->
          let oldbv = IO.load_int ls in
          let level = IO.load_int ls in
          let op = (match IO.load_byte ls with
                        0x20 -> Bo_and
                      | 0x21 -> Bo_or
                      | _ -> IO.loaderror "load_bval_binop") in
          let vals = IO.load_list ls loader in
          let newbv = add_binop level op vals in
            H.add loaded oldbv newbv;
            set_simp newbv; newbv
      | _ -> IO.loaderror "load_bval" in
  loader ls

let debug_bval_full = register_debug "bval_full" "Always print bval values"
let debug_bval_simp = register_debug "bval_simp" "Never print bval values"

let vt_bval typ = make_type "bval" [|typ|]
let vk_bval = register_val_kind {
  vki_tostring = (fun depth v ->
    if debug_bval_full() || not (debug_bval_simp()) then
      string_of_bval depth (simplify v)
    else "B#" ^ (string_of_int v));
  vki_compare = compare_bval;
  vki_dump = dump_bval;
  vki_load = load_bval;
}

let val2bval = val2cst vk_bval
let bval2val = cst2val vk_bval

(* Packages *)

let find_handlers = ref []
let collect_handlers = ref []
let operators = ref []

let vt_xvar = vt_var "X"
let vt_xbval = vt_bval vt_xvar

let _ = prepend find_handlers
  (("#bool_g",[|Builtin.vt_bool;vt_bval vt_any|]),
   [([|true;false|],[Sk_once]); ([|false;true|], [Sk_zero;Sk_once])],
   fun (name,args) ->
     if not (is_val_const args.(1)) then
         let v = if Builtin.val2bool args.(0) then btrue else bfalse in
           [name,[|args.(0);bval2val v|]]
     else
       match get_bval (simplify (val2bval args.(1))) with
           Bb_const bv -> [name,[|Builtin.bool2val bv;args.(1)|]]
         | _ -> [])

let _ = prepend find_handlers
  (("#id_g",[|vt_xvar;vt_xbval|]),
   [([|true;false|], [Sk_once]); ([|false;true|], [Sk_zero;Sk_once])],
   fun (name,args) ->
     if not (is_val_const args.(1)) then
       [name,[|args.(0);bval2val (add_var args.(0))|]]
     else
       match get_bval (simplify (val2bval args.(1))) with
           Bb_var bx -> [name,[|bx;args.(1)|]]
         | _ -> [])

let _ = prepend find_handlers
  (("#g_id",[|vt_xbval;vt_xvar|]),[[|true;false|],[]],
   fun (name,args) ->
     let vars = extract_bval (simplify (val2bval (args.(0)))) (fun x -> [x]) in
       List.map (fun v -> (name,[|args.(0);v|])) vars)

let _ = prepend find_handlers
  (("#g_size",[|vt_bval vt_any;vt_int|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let size = size_of_bval (simplify (val2bval args.(0))) in
       [name,[|args.(0);sint2val size|]])

let merge_handler pred op =
  ((pred,[|vt_xbval;vt_xbval|]),[|true;false|],
   fun (name,_) matches ->
     let bvals = List.map (fun (_,args) -> val2bval args.(0)) matches in
     let v = add_binop 100 op bvals in
       [name,[|anyval;bval2val v|]])

let _ = prepend collect_handlers (merge_handler "#and_all" Bo_and)
let _ = prepend collect_handlers (merge_handler "#or_all" Bo_or)

let unop_handler pred op =
  ((pred,[|vt_xbval;vt_xbval|]),
   [([|true;false|], [Sk_once]); ([|false;true|], [Sk_zero;Sk_once])],
   fun (name,args) ->
     if not (is_val_const args.(1)) then
       let bvr = add_unop 100 op (val2bval args.(0)) in
         [name,[|args.(0);bval2val bvr|]]
     else
       match get_bval (simplify (val2bval args.(1))) with
           Bb_unop(vop,bv) when vop = op ->
             [name,[|bval2val bv;args.(1)|]]
         | _ -> [])

let _ = prepend find_handlers (unop_handler "#not" Bo_not)
let _ = prepend operators ("!", "#not")

let unop_level_handler pred op =
  ((pred,[|vt_xbval;vt_int;vt_xbval|]),
   [([|true;true;false|],[Sk_once]); ([|false;false;true|],[Sk_zero;Sk_once])],
   fun (name,args) ->
     if not (is_val_const args.(2)) then
       let level = val2sint args.(1) in
       let bvr = add_unop level op (val2bval args.(0)) in
         [name,[|args.(0);args.(1);bval2val bvr|]]
     else let v = simplify (val2bval args.(2)) in
       match get_bval v with
           Bb_unop(vop,bv) when vop = op ->
             [name,[|bval2val bv;sint2val (get_level v);args.(2)|]]
         | _ -> [])

let _ = prepend find_handlers (unop_level_handler "#not_lv" Bo_not)

let binop_handler pred op =
  ((pred,[|vt_xbval;vt_xbval;vt_xbval|]),
   [([|true;true;false|],[Sk_once]); ([|false;false;true|],[Sk_zero;Sk_once])],
   fun (name,args) ->
     if not (is_val_const args.(2)) then
       let bvr = add_binop 100 op [val2bval args.(0);val2bval args.(1)] in
         [name,[|args.(0);args.(1);bval2val bvr|]]
     else let v = simplify (val2bval args.(2)) in
       match get_bval v with
           Bb_binop(vop,bvals) when vop = op ->
             let bv0 = List.hd bvals in
             let bv1 = match List.tl bvals with
                 [bv1] -> bv1
               | bvxs -> add_binop (get_level v) op bvxs in
             [name,[|bval2val bv0;bval2val bv1;args.(2)|]]
         | _ -> [])

let _ = prepend find_handlers (binop_handler "#and" Bo_and)
let _ = prepend find_handlers (binop_handler "#or" Bo_or)
let _ = prepend operators ("&&", "#and")
let _ = prepend operators ("||", "#or")

let binop_level_handler pred op =
  ((pred,[|vt_xbval;vt_xbval;vt_int;vt_xbval|]),
   [([|true;true;true;false|], [Sk_once]);
    ([|false;false;false;true|], [Sk_zero; Sk_once])],
   fun (name,args) ->
     if not (is_val_const args.(3)) then
       let level = val2sint args.(2) in
       let bvr = add_binop level op [val2bval args.(0);val2bval args.(1)] in
         [name,[|args.(0);args.(1);args.(2);bval2val bvr|]]
     else let v = simplify (val2bval args.(3)) in
       match get_bval v with
           Bb_binop(vop,bvals) when vop = op ->
             let bv0 = List.hd bvals in
             let bv1 = match List.tl bvals with
                 [bv1] -> bv1
               | bvxs -> add_binop (get_level v) op bvxs in
             let level = get_level v in
             [name,[|bval2val bv0;bval2val bv1;sint2val level;args.(3)|]]
         | _ -> [])

let _ = prepend find_handlers (binop_level_handler "#and_lv" Bo_and)
let _ = prepend find_handlers (binop_level_handler "#or_lv" Bo_or)

let _ = prepend find_handlers
  (("#simplify",[|vt_xbval;vt_xbval|]),[[|true;false|], [Sk_once]],
   fun (name,args) ->
     let bvr = simplify (val2bval args.(0)) in
       [name,[|args.(0);bval2val bvr|]])

let _ = register_package { empty_package with
  p_name = "biteval";
  p_reset = reset;
  p_find_handlers = !find_handlers;
  p_collect_handlers = !collect_handlers;
  p_abstypes = [vt_xbval];
  p_operators = !operators;
}

let _ = set_package_builtin "biteval"

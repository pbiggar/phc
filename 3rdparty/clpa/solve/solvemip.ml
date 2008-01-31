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

(* Mixed integer-program constraint solving *)

open Builtin
open Clpautil
open Flags
open Spec
open Biteval

module IO = Streamio
module A = Array
module H = Hashtbl
module V = Vector

module LP = Lpsolve

let reset_fns : (unit -> unit) list ref = ref []
let reset() = List.iter (fun f -> f()) !reset_fns

(* Linear constraints *)

type ipvar = int  (* variable ID *)
type ipval = int  (* linear formula ID *)

type cstop =
    Co_eq
  | Co_ne
  | Co_lt
  | Co_gt
  | Co_le
  | Co_ge

type t_formula     = (float * ipvar) list  (* Ax *)
type t_off_formula = t_formula * float     (* Ax + B *)
type t_sconstraint = float * t_formula     (* B <= Ax *)

(* more natural constraint type, translated to sconstraints for solver *)
type t_constraint =
    C_cst of t_formula * cstop * float  (* generic Ax cmp B *)
  | C_bit of ipvar                      (* single bit x >= 1 for binary x *)

(* disjunction over sets of linear constraints, representing the truth value
 * of some bit formula *)
type t_sconstraint_bit = t_sconstraint list list

(* Linear constraint variable representation *)

type varkind =
    Vk_float
  | Vk_int
  | Vk_binary

type ipvarinfo = {
  ipv_tag : t_val;  (* unique value represented by the variable *)
  ipv_kind : varkind;
}

let tbl_ipvars : ipvarinfo V.t = V.create 10
let tbl_id2ipvar : (t_val,ipvar) H.t = H.create 10

let _ = prepend reset_fns (fun () ->
  V.clear tbl_ipvars; H.clear tbl_id2ipvar)

let add_ipvar tv k =
  try let ix = H.find tbl_id2ipvar tv in
    if (V.get tbl_ipvars ix).ipv_kind <> k then
      pred_unexpected "Conflicting variable kinds"
    else ix
  with Not_found ->
    let ix = V.append tbl_ipvars {
      ipv_tag = tv;
      ipv_kind = k;
    } in H.add tbl_id2ipvar tv ix; ix

(* stringifying *)

(* hack: turning this on tidies up constraint printing a bit.
 * watch for reentrance *)
let pretty_print = ref false

let string_of_float n =
  if !pretty_print && floor n = n then string_of_int (int_of_float n)
  else string_of_float n

let string_of_formula d ax =
  let strs = list_map (fun (a,x) ->
    let xv = (V.get tbl_ipvars x).ipv_tag in
    let xs =
      if !pretty_print then
        try val2str xv with Unexpected _ -> string_of_val d xv
      else string_of_val d xv in
    let sep = if !pretty_print then "*" else "" in
    if a = 0. then xs
    else if a = 1. then "+" ^ xs
    else if a = ~-.1. then "-" ^ xs
    else if a > 0. then "+" ^ (string_of_float a) ^ sep ^ xs
    else (string_of_float a) ^ sep ^ xs) ax in
  let res = String.concat "" (list_sort compare strs) in
    if res = "" then res
    else if res.[0] = '+' then String.sub res 1 (String.length res - 1)
    else res

let string_of_off_formula d (ax,b) = cvt_val_depth d
  (let axs = string_of_formula (d-1) ax in
     if axs = "" then string_of_float b
     else if b = 0. then axs
     else if b > 0. then axs ^ "+" ^ (string_of_float b)
     else axs ^ (string_of_float b))

let string_of_sconstraint d (b,ax) = cvt_val_depth d
  ((string_of_float b) ^ " <= " ^ (string_of_formula (d-1) ax))

let string_of_constraint d c = cvt_val_depth d
  (match c with
       C_cst (ax,op,b) ->
         let cstr = match op with
             Co_eq -> " == "
           | Co_ne -> " != "
           | Co_lt -> " < "
           | Co_gt -> " > "
           | Co_le -> " <= "
           | Co_ge -> " >= " in
         let (lax,rax) =
           if !pretty_print then
             List.fold_left (fun (lax,rax) (a,x) ->
               if a > 0. then ((a,x)::lax,rax)
                         else (lax,(~-.a,x)::rax)) ([],[]) ax
           else (ax,[]) in
         let (lb,rb) =
           if !pretty_print then
             if b < 0. then (~-.b,0.) else (0.,b)
           else (0.,b) in
         (string_of_off_formula (d-1) (lax,lb)) ^ cstr ^
         (string_of_off_formula (d-1) (rax,rb))
     | C_bit x ->
         let xv = (V.get tbl_ipvars x).ipv_tag in
           if !pretty_print then
             try val2str xv with Unexpected _ -> string_of_val d xv
           else string_of_val d xv)

(* Formula representation *)

let tbl_ipvals : t_off_formula V.t = V.create 10
let tbl_form2ipval : (t_off_formula,ipval) H.t = H.create 10

let _ = prepend reset_fns (fun () ->
  V.clear tbl_ipvals; H.clear tbl_form2ipval)

let get_ipval = V.get tbl_ipvals
let add_ipval form =
  try H.find tbl_form2ipval form
  with Not_found ->
    let iv = V.append tbl_ipvals form in
      H.add tbl_form2ipval form iv; iv

let formula_add ax0 ax1 =
  let rec filter_ax = function
      (c0,x0)::(c1,x1)::axs when x0 = x1 ->
        if c0 = ~-.c1 then filter_ax axs else filter_ax ((c0+.c1,x0)::axs)
    | (c,x)::axs -> (c,x)::(filter_ax axs)
    | [] -> [] in
  let compare_ax (_,x0) (_,x1) =
    let v0 = (V.get tbl_ipvars x0).ipv_tag in
    let v1 = (V.get tbl_ipvars x1).ipv_tag in
      compare (full_string_of_val v0) (full_string_of_val v1) in
  filter_ax (list_sort compare_ax (ax0 @ ax1))
let off_formula_add (ax0,b0) (ax1,b1) = (formula_add ax0 ax1, b0 +. b1)

let formula_scale ax c = list_map (fun (a,x) -> (c*.a,x)) ax
let off_formula_scale (ax,b) c =
  (* special case 0 as 0 and -0 are considered different for equality *)
  (formula_scale ax c, if b = 0. then 0. else c*.b)

let iv_var v k = add_ipval ([1.,add_ipvar v k],0.)
let iv_flt n = add_ipval ([],n)
let iv_add v0 v1 = add_ipval (off_formula_add (get_ipval v0) (get_ipval v1))
let iv_sub v0 v1 = add_ipval (off_formula_add (get_ipval v0)
                                (off_formula_scale (get_ipval v1) ~-.1.))
let iv_mul v n = add_ipval (off_formula_scale (get_ipval v) n)
let iv_div v n = add_ipval (off_formula_scale (get_ipval v) (1./.n))

(* comparison *)

let compare_ipvar x0 x1 =
  let i0 = V.get tbl_ipvars x0 in
  let i1 = V.get tbl_ipvars x1 in
  let cmp = compare i0.ipv_kind i1.ipv_kind in
    if cmp <> 0 then cmp else compare_vals i0.ipv_tag i1.ipv_tag

let compare_formula =
  compare_lists (fun (a0,x0) (a1,x1) ->
    let cmp = compare a0 a1 in
      if cmp <> 0 then cmp else compare_ipvar x0 x1)

(* serialization *)

let dump_ipvar ds x =
  let info = V.get tbl_ipvars x in
    dump_val ds info.ipv_tag;
    IO.dump_byte ds (match info.ipv_kind with
                         Vk_float -> 0x30
                       | Vk_int -> 0x31
                       | Vk_binary -> 0x32)

let load_ipvar ls =
  let tv = load_val ls in
  let k = match IO.load_byte ls with
      0x30 -> Vk_float
    | 0x31 -> Vk_int
    | 0x32 -> Vk_binary
    | _ -> IO.loaderror "load_ipvar" in
  add_ipvar tv k

let dump_formula ds ax = IO.dump_list ds
  (fun ds (a,x) -> IO.dump_float ds a; dump_ipvar ds x) ax
let load_formula ls = IO.load_list ls
  (fun ls -> let a = IO.load_float ls in (a,load_ipvar ls))

let dump_off_formula ds (ax,b) = dump_formula ds ax; IO.dump_float ds b
let load_off_formula ls = let ax = load_formula ls  in (ax,IO.load_float ls)

let dump_constraint ds = function
    C_cst (ax,op,b) ->
      IO.dump_byte ds 0x01;
      dump_formula ds ax;
      IO.dump_byte ds (match op with
                           Co_eq -> 0x40
                         | Co_ne -> 0x41
                         | Co_lt -> 0x42
                         | Co_gt -> 0x43
                         | Co_le -> 0x44
                         | Co_ge -> 0x45);
      IO.dump_float ds b
  | C_bit x ->
      IO.dump_byte ds 0x02;
      dump_ipvar ds x
let load_constraint ls =
  match IO.load_byte ls with
      0x01 ->
        let ax = load_formula ls in
        let op = match IO.load_byte ls with
            0x40 -> Co_eq
          | 0x41 -> Co_ne
          | 0x42 -> Co_lt
          | 0x43 -> Co_gt
          | 0x44 -> Co_le
          | 0x45 -> Co_ge
          | _ -> IO.loaderror "load_constraint" in
        let b = IO.load_float ls in
          C_cst (ax,op,b)
    | 0x02 ->
        C_bit (load_ipvar ls)
    | _ -> IO.loaderror "load_constraint"

(* Constraint representation *)

(* cstvars are boolean variables representing linear constraints *)
type cstvar = int
let tbl_csts : t_constraint V.t = V.create 10
let tbl_cst2bvar : (t_constraint,cstvar) H.t = H.create 10

let _ = prepend reset_fns (fun () -> V.clear tbl_csts; H.clear tbl_cst2bvar)

let add_constraint cst =
  try H.find tbl_cst2bvar cst
  with Not_found ->
    let cx = V.append tbl_csts cst in
      H.add tbl_cst2bvar cst cx; cx

let dump_cstvar ds x = dump_constraint ds (V.get tbl_csts x)
let load_cstvar ls = add_constraint (load_constraint ls)

let compare_cstvar x0 x1 =
  match (V.get tbl_csts x0, V.get tbl_csts x1) with
      (C_cst(f0,op0,b0),C_cst(f1,op1,b1)) ->
        let cmp0 = compare op0 op1 in
        let cmp1 = compare b0 b1 in
          if cmp0 <> 0 then cmp0
          else if cmp1 <> 0 then cmp1
          else compare_formula f0 f1
    | (C_cst(_,_,_),_) -> ~-1
    | (_,C_cst(_,_,_)) -> 1
    | (C_bit x0,C_bit x1) -> compare_ipvar x0 x1

let debug_ipcst_full = register_debug "ipcst_full" "Always print ipcst values"
let debug_ipcst_simp = register_debug "ipcst_simp" "Never print ipcst values"

let vt_cstvar ctyp btyp = make_type "ipcst" [|ctyp;btyp|]
let cstvar_kind = register_val_kind {
  vki_tostring = (fun depth v ->
    if debug_ipcst_full() || not (debug_ipcst_simp()) then
      "(" ^ (string_of_constraint depth (V.get tbl_csts v)) ^ ")"
    else "CV#" ^ (string_of_int v));
  vki_compare = compare_cstvar;
  vki_dump = dump_cstvar;
  vki_load = load_cstvar;
}

let apply_cstop op axr b = match op with
    Co_eq -> axr = b
  | Co_ne -> not (axr = b)
  | Co_lt -> axr < b
  | Co_gt -> axr > b
  | Co_le -> axr <= b
  | Co_ge -> axr >= b

let rec simplify_cstop ax b =
  let mina = List.fold_left (fun mina (a,_) ->
    let a = abs_float a in
      if mina = 0. || a < mina then a else mina) 0. ax in
  if mina <> 1. then
    let nax = List.map (fun (a,x) -> (a /. mina,x)) ax in
    let nb = b /. mina in
      (* did we avoid introducing new fractions? *)
      if List.for_all (fun (na,_) -> floor na = na) nax && floor nb = nb then
        simplify_cstop nax nb
      else (ax,b)
  else (ax,b)

let add_cst_bvar v op b' =
  let (ax,b) = get_ipval v in
    if ax = [] then
      if apply_cstop op b b' then btrue else bfalse
    else
      let (nax,nb) = simplify_cstop ax (b'-.b) in
        add_var (cst2val cstvar_kind (add_constraint (C_cst(nax,op,nb))))
let add_bit_bvar v =
  let x = add_ipvar v Vk_binary in
    add_var (cst2val cstvar_kind (add_constraint (C_bit x)))

let bvar2cst xv =
  V.get tbl_csts (val2cst cstvar_kind xv)

(* Satisfying assignments *)

let apply_ipassignment_formula av ax =
  if ax = [] then 0.
  else
    List.fold_left (fun res (a,x) ->
      try let xn = H.find av x in res +. (xn *. a)
      with Not_found -> res) 0. ax

let rec apply_ipassignment_bit av bv =
  match get_bval bv with
      Bb_const b -> b
    | Bb_var xv ->
        (match bvar2cst xv with
             C_cst (ax,op,b) ->
               let axr = apply_ipassignment_formula av ax in
                 apply_cstop op axr b
           | C_bit x ->
               let axr = apply_ipassignment_formula av [1.,x] in
                 axr >= 1.)
    | Bb_unop (op,bv') ->
        (match op with
             Bo_eq -> apply_ipassignment_bit av bv'
           | Bo_not -> not (apply_ipassignment_bit av bv'))
    | Bb_binop (op,bvals) ->
        let combfn = if op = Bo_and then (&&) else (||) in
          list_fold_right (o combfn (apply_ipassignment_bit av))
            (List.tl bvals) (apply_ipassignment_bit av (List.hd bvals))

let print_ipassignment av title =
  IO.printf "IP Assign %s\n" title;
  let strs = H.fold (fun x v strs ->
    let xs = full_string_of_val (V.get tbl_ipvars x).ipv_tag in
    let vs = string_of_float v in
      (xs ^ ": " ^ vs)::strs) av [] in
  List.iter (IO.printf "%s\n") (list_sort compare strs)

(* Constraint optimization *)

(* evaluation cacheing, currently only done for disjunctions *)
let tbl_cst_reshash : (bval*bool,t_sconstraint_bit) H.t = H.create 10

(* optimal assignments constructed from lp_solve *)
type iassign = int
let tbl_assigns : (ipvar,float) H.t V.t = V.create 10

(* per-bval solver results (Some (form,ismax) for non-sat problems)
 * and solve times *)
let tbl_results : (bval*(ipval*bool) option,
                   ((float*iassign) option)*float) H.t = H.create 10

let _ = prepend reset_fns (fun () ->
  H.clear tbl_cst_reshash; V.clear tbl_assigns; H.clear tbl_results)

(* new binary variables introduced to model disjunctions *)
let orbit_kind = register_val_kind {
  vki_tostring = (fun _ x -> "ORX#" ^ (string_of_int x));
  vki_compare = compare;
  vki_dump = (fun _ _ -> failwith "Cannot dump or-bit");
  vki_load = (fun _ -> failwith "Cannot load or-bit");
}
let orbit_count = ref 0
let _ = prepend reset_fns (fun () -> orbit_count := 0)

let cstbit_and bit0 bit1 =
  List.flatten (list_map (fun csts ->
    list_map (list_merge compare csts) bit1) bit0)

let cstbit_or bit0 bit1 =
  (* make a new binary variable y to select either csts0 or csts1:
   *   B0 <= A0x OR B1 <= A1x
   *   B0 <= A0x + Cy AND B1 <= A1x + C(1-y)
   *   B0 <= A0x + Cy AND B1 - C <= A1x - Cy
   * C must be large enough such that f + C >= n hold for all possible f;
   * otherwise the search space will be inappropriately restricted.
   *
   * We currently use C=2^16 because with larger values lp_solve (apparently)
   * performs rounding errors leading to bogus results.
   *
   * This is a serious issue that needs revisiting *)
  match (bit0,bit1) with
      ([],[csts])
    | ([csts],[]) -> [csts]
    | ([csts0],[csts1]) ->
        let c = Int64.to_float (Int64.shift_left Int64.one 16) in
        let y = add_ipvar (cst2val orbit_kind !orbit_count) Vk_binary in
        let _ = incr orbit_count in
        let csts0 = list_map (fun (b,ax) -> (b,(c,y)::ax)) csts0 in
        let csts1 = list_map (fun (b,ax) -> (b-.c,(~-.c,y)::ax)) csts1 in
          [list_sort compare (csts0 @ csts1)]
    | _ -> failwith "Unexpected cstbit format"

(*
(* simple but much less efficient disjunction. this effectively forces
 * branch-and-bound on ALL disjunctions, which is usually intractable *)
let cstbit_or bit0 bit1 = bit0 @ bit1
*)

let cstbit_combine isand bits = List.fold_left
  (if isand then cstbit_and else cstbit_or) (if isand then [[]] else []) bits

let rec get_constraints p bv =
  try H.find tbl_cst_reshash (bv,p) with Not_found ->
  match get_bval bv with
      Bb_const b ->
        if b = p then [[]] else []
    | Bb_var xv ->
        (match bvar2cst xv with
             C_cst (ax,op,b) ->
               (* convert to simple representation *)
               let negate ax = formula_scale ax ~-.1. in
                 list_sort compare (match (p,op) with
                     (true,Co_eq) | (false,Co_ne) ->
                       [[(b,ax);(~-.b,negate ax)]]
                   | (true,Co_ne) | (false,Co_eq) ->
                       cstbit_or [[b+.1.,ax]] [[~-.b+.1.,negate ax]]
                   | (true,Co_lt) | (false,Co_ge) ->
                       [[~-.b+.1.,negate ax]]
                   | (true,Co_gt) | (false,Co_le) ->
                       [[b+.1.,ax]]
                   | (true,Co_le) | (false,Co_gt) ->
                       [[~-.b,negate ax]]
                   | (true,Co_ge) | (false,Co_lt) ->
                       [[b,ax]])
           | C_bit x ->
               (* convert to 1 <= x or 0 <= -x *)
               if p then [[1.,[1.,x]]] else [[0.,[~-.1.,x]]])
    | Bb_unop (op,bv') ->
        (match op with
             Bo_eq -> get_constraints p bv'
           | Bo_not -> get_constraints (not p) bv')
    | Bb_binop (op,bvals) ->
        let bits = List.map (get_constraints p) bvals in
        let res = cstbit_combine ((op = Bo_and) = p) bits in
          H.add tbl_cst_reshash (bv,p) res; res

let get_constraints p bv =
  try get_constraints p bv
  with Stack_overflow ->
    pred_unexpected "ERROR: Could not construct LP constraints"

(*
let get_constraints p bv =
  let all_csts : t_sconstraint list ref = ref [] in
  let handled_eqvars : (eqvar,unit) H.t = H.create 10 in
  let rec handle_cnf cnf = List.iter (fun df ->
    let disjs = List.fold_right (fun (xv,p) disjs ->
      try match bvar2cst xv with
          C_cst (ax,op,b) ->
            (* convert to simple representation *)
            let negate ax = formula_scale ax ~-.1. in
              (match (p,op) with
                   (true,Co_eq) | (false,Co_ne) ->
                     [(b,ax);(~-.b,negate ax)]::disjs
                 | (true,Co_ne) | (false,Co_eq) ->
                     [b+.1.,ax]::[~-.b+.1.,negate ax]::disjs
                 | (true,Co_lt) | (false,Co_ge) ->
                     [~-.b+.1.,negate ax]::disjs
                 | (true,Co_gt) | (false,Co_le) ->
                     [b+.1.,ax]::disjs
                 | (true,Co_le) | (false,Co_gt) ->
                     [~-.b,negate ax]::disjs
                 | (true,Co_ge) | (false,Co_lt) ->
                     [b,ax]::disjs)
        | C_bit x ->
            (* convert to 1 <= x *)
            [1.,[1.,x]]::disjs
      with Unexpected "Bad format" ->
        let eqv = bval2eqvar xv in
          (* add the CNFs and convert to 1 <= x *)
          if not (H.mem handled_eqvars eqv) then begin
            H.add handled_eqvars eqv ();
            let (tcnf,fcnf) = get_eqvar_cnfs eqv in
              handle_cnf (get_some tcnf); handle_cnf (get_some fcnf)
          end;
          [1.,[1.,(add_ipvar xv Vk_binary)]]::disjs) df [] in
    match disjs with
        [csts] -> List.iter (prepend all_csts) csts
      | _ ->
          let dylist = list_map (fun csts ->
            let c = 4000000000. in
            let y = add_ipvar (cst2val orbit_kind !orbit_count) Vk_binary in
            let _ = incr orbit_count in
            let csts = list_map (fun (b,ax) -> (b-.c,(~-.c,y)::ax)) csts in
              (csts,y)) disjs in
          List.iter (prepend all_csts) (List.flatten (list_map fst dylist));
          prepend all_csts (1.,list_map (fun (_,y) -> (1.,y)) dylist)) cnf in
  match get_cnf p bv with
      None -> []
    | Some cnf -> handle_cnf cnf; [!all_csts]
*)

(* the sanitization functions apply satisfiability-preserving transforms
 * to sets of lp_solve rows. if we don't do these, lp_solve tends to go crazy,
 * generating stupid error messages or going into an infinite recursion *)

(* if there are rows x-By >= 0 and -x+By >= 0 then replace x with By in all
 * other rows *)
let sanitize_alignment rows =
  let (ubos,lbos) = List.fold_left (fun (ubos,lbos) (b,(len,ax)) ->
    match (b,ax) with
        (0.,[(cx,x);(cy,y)]) ->
               if cx = 1. then ((x,y,~-.cy)::ubos,lbos)
          else if cy = 1. then ((y,x,~-.cx)::ubos,lbos)
          else if cx = ~-.1. then (ubos,(x,y,cy)::lbos)
          else if cy = ~-.1. then (ubos,(y,x,cx)::lbos)
          else (ubos,lbos)
      | _ -> (ubos,lbos)) ([],[]) rows in
  let eqbos = List.filter (fun t -> List.exists ((=)t) lbos) ubos in
  let eqbos = List.map (fun (x,y,c) ->
                if c < 1. && c > ~-.1. then (y,x,1./.c) else (x,y,c)) eqbos in
  let get_eqbo x = findopt_list (fun (x',y,c) ->
                     if x = x' then Some (y,c) else None) eqbos in
  List.map (fun (b,(len,ax)) ->
    let ax = List.map (fun (a,x) ->
      try let (y,c) = get_eqbo x in
        if List.exists (o ((=)y) snd) ax then (a,x)
        else (a*.c,y)
      with Not_found -> (a,x)) ax in
    (b,(len,ax))) rows

(* if there is a row Ax >= B where all x are integer vars and all A divide
 * into integers by some N (we just pick the minimum absolute value in A)
 * then divide all A by N, and divide B by N and round up to the nearest
 * integer (since Ax must be an integer). *)
let sanitize_rounding col2var rows =
  List.map (fun (b,(len,ax)) ->
    let (minf,allint) = List.fold_left (fun (minf,allint) (a,x) ->
      let k = (V.get tbl_ipvars (V.get col2var x)).ipv_kind in
        (min minf (abs_float a), allint && (k = Vk_int || k = Vk_binary)))
      (10000.,true) ax in
    let alldiv = List.for_all (fun (a,_) ->
      a /. minf = (float_of_int (int_of_float (a /. minf)))) ax in
    if allint && alldiv then
      let ax = List.map (fun (a,x) -> (a /. minf,x)) ax in
      let b = ceil (b /. minf) in
        (b,(len,ax))
    else (b,(len,ax))) rows

(* remove rows with a single column and generate the corresponding bounds.
 * look for contradictory bounds on the same column *)
let sanitize_bounds rows =
  let bounds : (int*bool,float) H.t = H.create 10 in
  let rows = List.fold_right (fun (b,(len,acol)) rows ->
    match acol with
        [a,col] ->
          (if a <> 0. then let is_lobo = a > 0. in
             H.replace bounds (col,is_lobo)
               (try (if is_lobo then max else min)
                  (b /. a) (H.find bounds (col,is_lobo))
                with Not_found -> (b /. a)));
          rows
      | _ -> (b,(len,acol))::rows) rows [] in
  let contradiction = H.fold (fun (col,is_lobo) bound c -> c || (is_lobo &&
      (try bound > H.find bounds (col,false) with Not_found -> false)))
    bounds false in
  (rows,bounds,contradiction)

let debug_lpsolve = register_debug "ipcst_lpsolve"
  "Print lp_solve solving details"
let debug_lpcsts = register_debug "ipcst_lpcsts"
  "Print constraints fed to lp_solve"
let debug_lpbval = register_debug "ipcst_lpbval"
  "Print bvals for problems fed to lp_solve"

let do_solve lpm =
  LP.set_bb_dir lpm LP.LP_BranchFloor;
  LP.set_bb_rule lpm (LP.LP_PseudoNonIntSelect,[LP.LP_BreadthFirstMode]);
  LP.set_timeout lpm 10;
  if IO.suppress_external_output() then
    LP.set_verbose lpm LP.LP_Neutral
  else if debug_lpsolve() then
    (LP.print lpm; LP.set_verbose lpm LP.LP_Normal)
  else LP.set_verbose lpm LP.LP_Important;
  LP.solve lpm

let minimize_one_cst objform csts =
  if debug_lpcsts() then begin
    IO.printf "Constraint Set:\n";
    List.iter (o (IO.printf "%s\n") (string_of_sconstraint !print_level)) csts
  end;
  let col2var : ipvar V.t = V.create 10 in
  let _ = V.append col2var ~-1 in (* lp_solve column numbering starts at 1 *)
  let var2col : (ipvar,int) H.t = H.create 10 in
  let map_formula ax = (List.length ax, list_map (fun (a,x) ->
    try (a,H.find var2col x)
    with Not_found ->
      let col = V.append col2var x in
        H.add var2col x col; (a,col)) ax) in
  let rows = list_map (fun (b,ax) -> (b,map_formula ax)) csts in
  let rows = sanitize_alignment rows in
  let rows = sanitize_rounding col2var rows in
  let (rows,bounds,contradiction) = sanitize_bounds rows in
  let (obj,objoff) = (map_formula (fst objform), snd objform) in
  (* if there are contradictory bounds the result is infeasible *)
  if contradiction then None
  (* if there are no cols then the result is simply the objective *)
  else if V.size col2var = 1 then begin
    Some (objoff,H.create 10)
  end else begin
    let lpm = LP.make 0 (V.size col2var - 1) in
    H.iter (fun iv col -> let kind = (V.get tbl_ipvars iv).ipv_kind in
      if not (H.mem bounds (col,true)) && kind <> Vk_binary then
        LP.set_lower_bnd lpm col (~-.(LP.get_infinite lpm));
      match kind with
          Vk_float -> ()
        | Vk_int -> LP.set_isint lpm col true
        | Vk_binary -> LP.set_isbinary lpm col true) var2col;
    LP.set_add_rowmode lpm true;
    LP.set_obj lpm obj;
    List.iter (fun (b,cax) ->
      match snd cax with
          [(a,col)] ->
            if a > 0. then LP.set_lower_bnd lpm col (b /. a)
            else if a < 0. then LP.set_upper_bnd lpm col (b /. a)
        | _ -> LP.add_row lpm cax LP.LPc_Ge b) rows;
    H.iter (fun (col,is_lobo) bnd ->
      if is_lobo then LP.set_lower_bnd lpm col bnd
      else LP.set_upper_bnd lpm col bnd) bounds;
    (* degenerate case: lp_solve crashes if there are more cols than rows
     * we fix this by adding dummy rows: 0 >= 0   ......   don't laugh *)
    while (LP.get_nrows lpm < LP.get_ncols lpm) do
      LP.add_row lpm (0,[]) LP.LPc_Ge 0.
    done;
    LP.set_add_rowmode lpm false;
    let res = match do_solve lpm with
        LP.LP_Optimal
      | LP.LP_Unbounded ->
          let assign = H.create 10 in
            H.iter (fun x col ->
              H.add assign x (LP.get_assign lpm col)) var2col;
            Some ((LP.get_obj lpm) +. objoff, assign)
      | LP.LP_Infeasible -> None
      | lpstt -> LP.delete lpm;
          pred_unexpected ("LP Solver error: " ^ LP.lpstt2str lpstt) in
      LP.delete lpm; flush stdout; res
  end

let minimize_cst objform bv =
  if debug_lpbval() then
    IO.printf "Minimizing: %s, Subject to: %s\n"
      (string_of_off_formula !print_level objform) 
      (string_of_bval !print_level bv);
  let cstbit = get_constraints true bv in
  let resasn = List.fold_left (fun resasn csts ->
    let nresasn = minimize_one_cst objform csts in
      match (resasn,nresasn) with
          (None,x)
        | (x,None) -> x
        | (Some(obj0,asn0),Some(obj1,asn1)) ->
            if obj0 < obj1 then Some(obj0,asn0)
                           else Some(obj1,asn1)) None cstbit in
  match resasn with
      Some (obj,assign) ->
        if debug_lpbval() then begin
          IO.printf "Found optimal: %.2f\n" obj;
          print_ipassignment assign ""
        end;
        Some (obj,V.append tbl_assigns assign)
    | None ->
        if debug_lpbval() then
          IO.printf "Infeasible.\n";
        None

(* Spec integration *)

let compare_ipval of0 of1 =
  let (f0,b0) = V.get tbl_ipvals of0 in
  let (f1,b1) = V.get tbl_ipvals of1 in
  let cmp = compare b0 b1 in
    if cmp <> 0 then cmp else compare_formula f0 f1

(* Value kind for ipvals *)
let vt_ipval typ = make_type "ipval" [|typ|]
let vk_ipval = register_val_kind {
  vki_tostring = (fun depth v ->
    string_of_off_formula depth (V.get tbl_ipvals v));
  vki_compare = compare_ipval;
  vki_dump = (fun ds v -> dump_off_formula ds (V.get tbl_ipvals v));
  vki_load = (fun ls -> add_ipval (load_off_formula ls));
}

let val2ipval = val2cst vk_ipval
let ipval2val = cst2val vk_ipval

let vt_ipassign ctyp btyp = make_type "ipval_asn" [|ctyp;btyp|]
let vk_ipassign = register_val_kind {
  vki_tostring = (fun _ a -> "IASN#" ^ (string_of_int a));
  vki_compare = compare;
  vki_dump = (fun _ _ -> failwith "Cannot dump ipassign");
  vki_load = (fun _ -> failwith "Cannot load ipassign");
}

let val2ipassign = val2cst vk_ipassign
let ipassign2val = cst2val vk_ipassign

(* Packages *)

let vt_ip_kind = make_type "ipkind" [||]
let ip_kinds = (vt_ip_kind,[
  (Vk_float,"ip_float");
  (Vk_int,"ip_int");
  (Vk_binary,"ip_binary");
])
let val2varkind = val2enum ip_kinds

let vt_ip_cstop = make_type "ipcstop" [||]
let ip_cstops = (vt_ip_cstop,[
  (Co_eq,"ip_eq");
  (Co_ne,"ip_ne");
  (Co_lt,"ip_lt");
  (Co_gt,"ip_gt");
  (Co_le,"ip_le");
  (Co_ge,"ip_ge");
])
let val2cstop = val2enum ip_cstops

let add_handlers = ref []
let find_handlers = ref []

let val2form v = (V.get tbl_ipvals) (val2ipval v)

let vt_xvar = vt_var "IX"
let vt_yvar = vt_var "BX"
let vt_xcst = vt_cstvar vt_xvar vt_yvar
let vt_xbval = vt_bval vt_xcst
let vt_xipval = vt_ipval vt_xvar
let vt_xipassign = vt_ipassign vt_xvar vt_yvar

let ipsat_solve bv ivmaxo =
  let bv = simplify (val2bval bv) in
    try fst (H.find tbl_results (bv,ivmaxo))
    with Not_found ->
      let (f,flip) = match ivmaxo with
          Some (iv,true) ->
            (off_formula_scale (V.get tbl_ipvals iv) ~-.1.,true)
        | Some (iv,false) ->
            (V.get tbl_ipvals iv,false)
        | None -> (([],0.),false) in
      let start = Sys.time() in
      let res = match minimize_cst f bv with
          Some(n,asn) -> Some ((if flip then ~-.n else n), asn)
        | None -> None in
      let elapsed = Sys.time() -. start in
        H.add tbl_results (bv,ivmaxo) (res,elapsed); res
let ipsat_solve = make_track_2 "ipsat_solve" ipsat_solve

let _ = prepend find_handlers
  (("#ip_sat",[|vt_xbval|]),[[|true|]],
   fun (name,args) ->
     if (ipsat_solve args.(0) None) <> None then [name,args] else [])

let _ = prepend find_handlers
  (("#ip_sat_asn",[|vt_xbval;vt_xipassign|]),[[|true;false|]],
   fun (name,args) ->
     match ipsat_solve args.(0) None with
         Some(_,ar) ->
           [name,[|args.(0);ipassign2val ar|]]
       | None -> [])

let opt_handler pred ismax =
  ((pred,[|vt_xbval;vt_xipval;vt_flt|]),
   [[|true;true;false|]],
   fun (name,args) ->
     match ipsat_solve args.(0) (Some(val2ipval args.(1),ismax)) with
         Some(nvr,_) -> [name,[|args.(0);args.(1);flt2val nvr|]]
       | None -> [])

let _ = prepend find_handlers (opt_handler "#ip_maximize" true)
let _ = prepend find_handlers (opt_handler "#ip_minimize" false)

let optasn_handler pred ismax =
  ((pred,[|vt_xbval;vt_xipval;vt_flt;vt_xipassign|]),
   [[|true;true;false;false|]],
   fun (name,args) ->
     match ipsat_solve args.(0) (Some(val2ipval args.(1),ismax)) with
         Some(nvr,ar) ->
           [name,[|args.(0);args.(1);flt2val nvr;ipassign2val ar|]]
       | None -> [])

let _ = prepend find_handlers (optasn_handler "#ip_maximize_asn" true)
let _ = prepend find_handlers (optasn_handler "#ip_minimize_asn" false)

let _ = prepend find_handlers
  (("#ip_asn",[|vt_xipassign;vt_xipval;vt_flt|]),[[|true;true;false|]],
   fun (name,args) ->
     let av = V.get tbl_assigns (val2ipassign args.(0)) in
     let (ax,b) = val2form args.(1) in
     let nr = (apply_ipassignment_formula av ax) +. b in
       [name,[|args.(0);args.(1);flt2val nr|]])

let _ = prepend find_handlers
  (("#ip_asn_g",[|vt_xipassign;vt_xbval|]),[[|true;true|]],
   fun (name,args) ->
     let av = V.get tbl_assigns (val2ipassign args.(0)) in
     let bv = val2bval args.(1) in
       if apply_ipassignment_bit av bv then [name,args] else [])

let _ = prepend find_handlers
  (("#ip_asn_var",[|vt_xipassign;vt_xvar;vt_flt|]),[[|true;false;false|]],
   fun (name,args) ->
     let assign = V.get tbl_assigns (val2ipassign args.(0)) in
       H.fold (fun x n res ->
         let entry = V.get tbl_ipvars x in
           if entry.ipv_kind <> Vk_binary then
             (name,[|args.(0);entry.ipv_tag;flt2val n|])::res
           else res) assign [])

(* TODO: the resulting type might be somewhat broken if #id_ipval is used
 * to create a binary variable of type vt_yvar *)
let _ = prepend find_handlers
  (("#ip_asn_bit",[|vt_xipassign;vt_yvar;vt_bool|]),[[|true;false;false|]],
   fun (name,args) ->
     let assign = V.get tbl_assigns (val2ipassign args.(0)) in
       H.fold (fun x n res ->
         let entry = V.get tbl_ipvars x in
           if entry.ipv_kind = Vk_binary then
             try ignore (val2cst orbit_kind entry.ipv_tag); res
             with Unexpected _ ->
               (name,[|args.(0);entry.ipv_tag;bool2val (n<>0.)|])::res
           else res) assign [])

let printed : (t_val array,unit) H.t = H.create 10
let _ = prepend reset_fns (fun () -> H.clear printed)

let _ = prepend add_handlers
  (("#ip_asn_print",[|vt_ipassign vt_any vt_any;vt_vargs vt_any|]),
   fun (name,args) ->
     if not (H.mem printed args) then begin
       H.add printed args ();
       let assign = V.get tbl_assigns (val2ipassign args.(0)) in
       let oargs = A.sub args 1 (A.length args - 1) in
       let ttl = sep_string_of_array " " (string_of_val !print_level) oargs in
         print_ipassignment assign ttl
     end)

let _ = prepend find_handlers
  (("#id_ipval",[|vt_xvar;vt_ip_kind;vt_xipval|]),[[|true;true;false|]],
   fun (name,args) ->
     if not (is_val_const args.(0)) then pred_unexpected "ID not const";
     let kind = val2enum ip_kinds args.(1) in
     let ivr = iv_var args.(0) kind in
       [name,[|args.(0);args.(1);ipval2val ivr|]])

let _ = prepend find_handlers
  (("#flt_ipval",[|vt_flt;vt_xipval|]),[[|true;false|]],
   fun (name,args) ->
     let ivr = iv_flt (val2flt args.(0)) in
       [name,[|args.(0);ipval2val ivr|]])

let _ = prepend find_handlers
  (("#ip_add",[|vt_xipval;vt_xipval;vt_xipval|]),[[|true;true;false|]],
   fun (name,args) ->
     let ivr = iv_add (val2ipval args.(0)) (val2ipval args.(1)) in
       [name,[|args.(0);args.(1);ipval2val ivr|]])

let _ = prepend find_handlers
  (("#ip_sub",[|vt_xipval;vt_xipval;vt_xipval|]),[[|true;true;false|]],
   fun (name,args) ->
     let ivr = iv_sub (val2ipval args.(0)) (val2ipval args.(1)) in
       [name,[|args.(0);args.(1);ipval2val ivr|]])

let _ = prepend find_handlers
  (("#ip_mul",[|vt_xipval;vt_flt;vt_xipval|]),[[|true;true;false|]],
   fun (name,args) ->
     let ivr = iv_mul (val2ipval args.(0)) (val2flt args.(1)) in
       [name,[|args.(0);args.(1);ipval2val ivr|]])

let _ = prepend find_handlers
  (("#ip_div",[|vt_xipval;vt_flt;vt_xipval|]),[[|true;true;false|]],
   fun (name,args) ->
     let ivr = iv_div (val2ipval args.(0)) (val2flt args.(1)) in
       [name,[|args.(0);args.(1);ipval2val ivr|]])

let _ = prepend find_handlers
  (("#ip_cst",[|vt_xipval;vt_ip_cstop;vt_flt;vt_xbval|]),
   [[|true;true;true;false|];[|false;false;false;true|]],
   fun (name,args) ->
     if not (is_val_const args.(3)) then
       let bvr = add_cst_bvar (val2ipval args.(0))
                   (val2cstop args.(1)) (val2flt args.(2)) in
         [name,[|args.(0);args.(1);args.(2);bval2val bvr|]]
     else
       match get_bval (simplify (val2bval args.(3))) with
           Bb_var xv ->
             (match bvar2cst xv with
                  C_cst (ax,op,b) ->
                    let iv = add_ipval (ax,0.) in
                    let opv = enum2val ip_cstops op in
                      [name,[|ipval2val iv;opv;flt2val b;args.(3)|]]
                | _ -> [])
         | _ -> [])

let _ = prepend find_handlers
  (("#ip_bit",[|vt_yvar;vt_xbval|]),
   [[|true;false|];[|false;true|]],
   fun (name,args) ->
     if not (is_val_const args.(1)) then
       let bvr = add_bit_bvar args.(0) in
         [name,[|args.(0);bval2val bvr|]]
     else
       match get_bval (simplify (val2bval args.(1))) with
           Bb_var xv ->
             (match bvar2cst xv with
                  C_bit x ->
                    let v = (V.get tbl_ipvars x).ipv_tag in
                      [name,[|v;args.(1)|]]
                | _ -> [])
         | _ -> [])

let _ = prepend find_handlers
  (("#ip_any_id",[|vt_xbval;vt_xvar|]),[[|true;false|]],
   fun (name,args) ->
     let xvars = extract_bval (simplify (val2bval args.(0))) (fun xv ->
       match bvar2cst xv with
           C_cst (ax,_,_) ->
             List.map (fun (_,x) -> (V.get tbl_ipvars x).ipv_tag) ax
         | _ -> []) in
     List.map (fun v -> (name,[|args.(0);v|])) xvars)

let _ = prepend find_handlers
  (("#ip_any_bit",[|vt_xbval;vt_yvar|]),[[|true;false|]],
   fun (name,args) ->
     let yvars = extract_bval (simplify (val2bval args.(0))) (fun xv ->
       match bvar2cst xv with
           C_bit x -> [(V.get tbl_ipvars x).ipv_tag]
         | _ -> []) in
     List.map (fun v -> (name,[|args.(0);v|])) yvars)

let vt_ip_terms typ = make_type "ipval_terms" [|typ|]
let sum_ip_terms = (vt_ip_terms vt_xvar,[
  ("term_z",[||]);
  ("term_ax",[|vt_flt;vt_xvar;vt_ip_terms vt_xvar|])
])

let _ = prepend find_handlers
  (("#ip_split",[|vt_xipval;vt_ip_terms vt_xvar;vt_flt|]),
   [[|true;false;false|]],
   fun (name,args) ->
     let (ax,b) = val2form args.(0) in
     let nilv = sum2val ("term_z",[||]) in
     let termv = List.fold_left (fun tailv (a,x) ->
       let tv = (V.get tbl_ipvars x).ipv_tag in
         sum2val ("term_ax",[|flt2val a;tv;tailv|])) nilv ax in
     [name,[|args.(0);termv;flt2val b|]])

let _ = prepend find_handlers
  (("#ip_pretty_ipval",[|vt_ipval vt_str;vt_str|]),
   [[|true;false|]],
   fun (name,args) ->
     pretty_print := true;
     let s = full_string_of_val args.(0) in
     pretty_print := false;
       [name,[|args.(0);str2val s|]])

let _ = prepend find_handlers
  (("#ip_pretty_bval",[|vt_bval (vt_cstvar vt_str vt_str);vt_str|]),
   [[|true;false|]],
   fun (name,args) ->
     pretty_print := true;
     let s = full_string_of_val args.(0) in
     pretty_print := false;
       [name,[|args.(0);str2val s|]])

let stats_ipsat_counts = register_stats "ipsat_counts"
  "Summarize integer constraint solver problems and times"

let write_ipsat_counts() =
  if stats_ipsat_counts() then begin
    (* keep track of (total queries, total time, maximum time) *)
    let (q,t,m) = H.fold (fun _ (_,time) (q,t,m) ->
                            (q+1,t+.time,max m time)) tbl_results (0,0.,0.) in
      IO.printf "IP SAT Solving Stats:\n";
      IO.printf "  Count: %d\n" q;
      if q <> 0 then begin
        let avg = t /. (float_of_int q) in
          IO.printf " Total:   %.3f\n" t;
          IO.printf " Average: %.3f\n" avg;
          IO.printf " Max:     %.3f\n" m
      end
  end

let _ = register_package { empty_package with
  p_name = "solve_mip";
  p_writeout = write_ipsat_counts;
  p_reset = reset;
  p_add_handlers = !add_handlers;
  p_find_handlers = !find_handlers;
  p_sumtypes = [make_enum_sum ip_kinds; make_enum_sum ip_cstops; sum_ip_terms];
  p_abstypes = [vt_xipval; vt_xipassign; vt_xcst];
}

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

module A = Array
module B = Buffer
module H = Hashtbl
module PQ = Prioqueue
module V = Vector
module IO = Streamio
open Clpautil
open Flags

(* t_vals are 31 bit integers encoding any variable or constant value
 * being operated on. The layout is as follows: [| kind[7]; id[24] |]
 * The lowest bit of kind indicates whether the val is constant (ground) *)
type t_val = int
type t_typ = t_val

type t_val_kind = int
type t_val_id = int

let v_cst v  = (v land 0x01000000) <> 0
let v_kind v =  v land 0x7f000000
let v_id v   =  v land 0x00ffffff

let is_val_const = v_cst

type t_pred = t_val * t_val array

type t_rpred_kind =
    Tp_find
  | Tp_add
  | Tp_negated
  | Tp_collect of t_pred

type t_priority =
    Rp_fix of int
  | Rp_var of t_val * bool

(* Source file locations *)
type sfa = 
  | Sfa_package  of string        (* In a built-in package *)
  | Sfa_file     of string * int  (* In a source file at a given line *)
  | Sfa_none                      (* Nowhere in particular. e.g. if something
				   * is missing. *)

type t_rpred = {
  r_priority : t_priority list;
  r_stratum  : int;
  r_kind : t_rpred_kind;
  r_session : t_pred option;
  r_pred : t_pred;
  r_sfa : sfa;
}

type t_rule = t_rpred list

let string_of_sfa sfa =
  match sfa with
    | Sfa_package package -> "package \"" ^ package ^ "\""
    | Sfa_file (file,line) -> file ^ ":" ^ (string_of_int line)
    | Sfa_none -> "analysis"

(* all preds/sessions for the find ops used to derive a pred or a rule *)
type t_pdrvs = (t_pred option * t_pred) list

exception Unexpected of string
let pred_unexpected s = raise (Unexpected s)

module VHashedType = struct
  type t = t_val
  let equal (v1 : t_val) (v2 : t_val) = (v1 = v2)
  let hash = Hashtbl.hash
end
module VH = H.Make(VHashedType)

let compare_int_arrays (arr0 : int array) (arr1 : int array) =
    let rec compare_int_arrays2 (i:int) (arr0 : int array) (arr1 : int array) =
        if i < 0 then 0 
        else if arr0.(i) < arr1.(i) then -1
        else if arr0.(i) > arr1.(i) then 1
        else compare_int_arrays2 (i - 1) arr0 arr1
    in
    let len0 = A.length arr0 in
    let len1 = A.length arr1 in
    if len0 = len1 then 
        compare_int_arrays2 (len0 - 1) arr0 arr1 
    else 
       (if len0 < len1 then -1 else 1)

let pred_compare ((n1,a1) : t_pred) ((n2,a2) : t_pred) =
    if n1 = n2 then
        compare_int_arrays a1 a2
    else if n1 < n2 then -1 else 1

let reset_fns : (unit -> unit) list ref = ref []
let reset() = List.iter (fun f -> f()) !reset_fns

(* Registering constant value kinds *)

(* Strings and other values are hash-consed when being operated on internally.
 * ID is unique across the process, with strings being converted
 * between ID and textual representation at file and user I/O. *)

module StrHashType = struct
  type t = string
  let equal (s1:string) (s2:string) = (s1 = s2)
  let hash = H.hash
end
module StrHash = Hashcons.Make(StrHashType)
let id2str = StrHash.id2a
let str2id = StrHash.a2id

module IntHashType = struct
  type t = Big_int.big_int
  let equal = Big_int.eq_big_int
    (* big_int can't be hashed directly by H.hash; their contents are opaque *)
  let hash = o H.hash Big_int.string_of_big_int
end
module IntHash = Hashcons.Make(IntHashType)
let id2int = IntHash.id2a
let int2id = IntHash.a2id
 
module FltHashType = struct
  type t = float
  let equal (f1:float) (f2:float) = (f1 = f2) 
  let hash = H.hash
end
module FltHash = Hashcons.Make(FltHashType)
let id2flt = FltHash.id2a
let flt2id = FltHash.a2id

module SumHashType = struct
  type t = t_val * t_val array
  let equal (s1:t) (s2:t) = ((pred_compare s1 s2) = 0)
  let hash = H.hash
end
module SumHash = Hashcons.Make(SumHashType)
let id2sum = SumHash.id2a
let sum2id = SumHash.a2id

let _ = prepend reset_fns StrHash.clean
let _ = prepend reset_fns IntHash.clean
let _ = prepend reset_fns FltHash.clean
let _ = prepend reset_fns SumHash.clean

type t_val_kind_info = {
  vki_tostring : int -> int -> string;
  vki_compare  : int -> int -> int;
  vki_dump     : Streamio.t_dump_fn -> int -> unit;
  vki_load     : Streamio.t_load_fn -> int;
}

let vk_info : t_val_kind_info V.t = V.create 64
let register_var_val_kind vki = (V.append vk_info vki) lsl 25
let register_val_kind vki = (register_var_val_kind vki) lor 0x01000000

let v_info v =
  try V.get vk_info ((v_kind v) lsr 25)
  with Not_found ->
    failwith ("Bad vk_info: " ^ (string_of_int ((v_kind v) lsr 25)))

let print_level : int ref = ref ~-1
let cvt_val_depth d s = if d <> 0 then s else "..."

let string_of_val d v = try (v_info v).vki_tostring d (v_id v)
                        with Unexpected msg -> "***" ^ msg ^ "***"

let compare_vals v0 v1 =
  if v_cst v0 && v_cst v1 then
    let (k0,k1) = (v_kind v0, v_kind v1) in
      if v0 = v1 then 0
      else if k0 = k1 then (v_info v0).vki_compare (v_id v0) (v_id v1)
      else if k0 < k1 then ~-1 else 1
  else pred_unexpected ("Can't compare non-const values "
                        ^ (string_of_val !print_level v0) ^ " and "
                        ^ (string_of_val !print_level v1))

let compare_sums (n0,t0) (n1,t1) =
  let cmp = compare_vals n0 n1 in
    if cmp <> 0 then cmp else compare_arrays compare_vals t0 t1

let cst2val k id = assert (v_id id = id); k lor id
let val2cst k v = if v_kind v = k then v_id v
                  else pred_unexpected "Bad format (val2cst)" 

let load_val ls =
  let k = (IO.load_byte ls) lsl 24 in
  let id = (v_info k).vki_load ls in cst2val k id

let dump_val ds v =
  IO.dump_byte ds ((v_kind v) lsr 24);
  (v_info v).vki_dump ds (v_id v)

let load_sum ls = let name = load_val ls in (name, IO.load_array ls load_val)
let dump_sum ds (name,t) = dump_val ds name; IO.dump_array ds dump_val t

(* have to define string_of_sum later as the special printing method used
 * for lists introduces some hideous cyclic dependencies *)
let string_of_sum = ref (fun _ _ -> failwith "missing string_of_sum")

let val_rep = id

(* Built-in types of values *)

let vk_any = register_var_val_kind {
  vki_tostring = (fun _ _ -> "_");
  vki_compare = (fun _ _ -> failwith "not reachable");
  vki_dump = (fun _ _ -> ());
  vki_load = (fun _ -> 0)
}

let vk_var = register_var_val_kind {
  vki_tostring = (fun _ id -> id2str id);
  vki_compare = (fun _ _ -> failwith "not reachable");
  vki_dump = (fun ds id -> IO.dump_string ds (id2str id));
  vki_load = (o str2id IO.load_string);
}

let vk_sum = register_var_val_kind {
  vki_tostring = (fun d id -> !string_of_sum d (id2sum id));
  vki_compare = (fun _ _ -> failwith "not reachable");
  vki_dump = (fun ds id -> dump_sum ds (id2sum id));
  vki_load = (o sum2id load_sum);
}

let vk_csum = register_val_kind {
  vki_tostring = (fun d id -> !string_of_sum d (id2sum id));
  vki_compare = (fun id0 id1 -> compare_sums (id2sum id0) (id2sum id1));
  vki_dump = (fun ds id -> dump_sum ds (id2sum id));
  vki_load = (o sum2id load_sum);
}

let vk_str = register_val_kind {
  vki_tostring = (fun _ id -> "\"" ^ (id2str id) ^ "\"");
  vki_compare = (fun id0 id1 -> compare (id2str id0) (id2str id1));
  vki_dump = (fun ds id -> IO.dump_string ds (id2str id));
  vki_load = (o str2id IO.load_string);
}

let vk_int = register_val_kind {
  vki_tostring = (fun _ id    -> Big_int.string_of_big_int (id2int id));
  vki_compare  = (fun id0 id1 -> Big_int.compare_big_int (id2int id0) (id2int id1));
  vki_dump     = (fun ds id   -> IO.dump_bigint ds (id2int id));
  vki_load     = (fun ls      -> int2id (IO.load_bigint ls));
}

let vk_flt = register_val_kind {
  vki_tostring = (fun _ id -> string_of_float (id2flt id));
  vki_compare = (fun id0 id1 -> compare (id2flt id0) (id2flt id1));
  vki_dump = (fun ds id -> IO.dump_float ds (id2flt id));
  vki_load = (o flt2id IO.load_float);
}

let a_cst = forall_array v_cst

let anyval = cst2val vk_any 0
let var2val x = cst2val vk_var  (str2id x)
let str2val s = cst2val vk_str  (str2id s)
let int2val n = cst2val vk_int  (int2id n)
let flt2val f = cst2val vk_flt  (flt2id f)
let sum2val s = cst2val (if a_cst (snd s) then vk_csum else vk_sum) (sum2id s)

let val2var x = id2str (val2cst vk_var x)
let val2str s = id2str (val2cst vk_str s)
let val2int n = id2int (val2cst vk_int n)
let val2flt f = id2flt (val2cst vk_flt f)
let val2sum v = id2sum (val2cst (if v_cst v then vk_csum else vk_sum) v)

let sint2val n = int2val (Big_int.big_int_of_int n)
let val2sint v = Big_int.int_of_big_int (val2int v)

(* Value unification and manipulation *)
module OrderedVal = struct
  type t = t_val
  let compare (a:t) (b:t) = compare a b 
  (* NB. Do not remove the arguments to compare. OCaml cannot deduce the
   * types of the arguments to compare in this case:
   * let compare = compare
   * so it compiles it using a generic type-inspecting comparison function
   * which is slow. *)
end
module VMap = Map.Make(OrderedVal)

(* variable unifier map. maps vk_var values to the value they unify with *)
type t_vmap = t_val VMap.t

let vmap_empty = VMap.empty

let rec vmap_val vm v =
  if v_cst v then v
  else if v_kind v = vk_any then v
  else if v_kind v = vk_var then
    try vmap_val vm (VMap.find v vm) 
    with Not_found -> v
  else if v_kind v = vk_sum then
    let (n,t) = val2sum v in sum2val (n,A.map (vmap_val vm) t)
  else assert false

let rec rename_val pfx v =
  if v_cst v then v
  else if v_kind v = vk_any then v
  else if v_kind v = vk_var then var2val (pfx ^ (val2var v))
  else if v_kind v = vk_sum then
    let (n,t) = val2sum v in sum2val (n,A.map (rename_val pfx) t)
  else assert false

let string_of_vmap vm =
  let vmlist = VMap.fold (fun k v l -> (k,v)::l) vm [] in
  let tostring (xv,v) = (val2var xv) ^ "->" ^ (string_of_val !print_level v) in
    "(" ^ (sep_string_of_list "," tostring vmlist) ^ ")"

let rec occurs vs v =
  if vs = v then true
  else if is_val_const v then false
  else try exists_array (occurs vs) (snd (val2sum v))
       with Unexpected _ -> false

let rec add_vmap (vm:t_vmap) v0 v1 =
  let v0 = vmap_val vm v0 in
  let v1 = vmap_val vm v1 in
  let k0 = v_kind v0 in
  let k1 = v_kind v1 in
    if k0 = vk_any || k1 = vk_any then Some vm
    else if v0 = v1 then Some vm
    else if k0 = vk_var then
      if occurs v0 v1 then None else Some (VMap.add v0 v1 vm)
    else if k1 = vk_var then
      if occurs v1 v0 then None else Some (VMap.add v1 v0 vm)
    else
      (try let (n0,t0) = val2sum v0 in
           let (n1,t1) = val2sum v1 in
         if n0 = n1 then add_vmap_array vm t0 t1
         else None
       with Unexpected _ -> None)

and add_vmap_array vm a0 a1 = 
  let rec non_unifiable_const i =
    if i < 0 then false
    else if a0.(i) <> a1.(i) && v_cst a0.(i) && v_cst a1.(i) then true
    else non_unifiable_const (i-1) in
  let rec add_vmap_array_part vmo i =
    if i < 0 then vmo
    else match vmo with
        Some vm -> add_vmap_array_part (add_vmap vm a0.(i) a1.(i)) (i-1)
      | None -> None in
  let l0 = A.length a0 in
  let l1 = A.length a1 in
    if l0 <> l1 then None
    else if non_unifiable_const (l0-1) then None
    else add_vmap_array_part (Some vm) (l0-1)

let make_vmap a0 a1 =
  match add_vmap_array vmap_empty a0 a1 with
      Some vm -> Some (VMap.map (vmap_val vm) vm)
    | None -> None

let map_pred fn (name,args) = (name, A.map fn args)
let map_predo fn = function Some p -> Some (map_pred fn p) | None -> None
let map_rpred fn rp =
  let pri = List.map (function
      Rp_fix n -> Rp_fix n
    | Rp_var(v,fwd) -> Rp_var(fn v,fwd)) rp.r_priority in
  let kind = match rp.r_kind with
      Tp_collect cp -> Tp_collect(map_pred fn cp)
    | kind -> kind in
  let session = map_predo fn rp.r_session in
  let pred = map_pred fn rp.r_pred
  in {
    r_priority = pri;
    r_stratum = rp.r_stratum;
    r_kind = kind;
    r_session = session;
    r_pred = pred;
    r_sfa = rp.r_sfa;
  }
let map_rule fn = list_map (map_rpred fn)

let vmap_pred vm  = if vm = vmap_empty then id else map_pred  (vmap_val vm)
let vmap_predo vm = if vm = vmap_empty then id else map_predo (vmap_val vm)
let vmap_rule vm  = if vm = vmap_empty then id else map_rule  (vmap_val vm)
let vmap_rpred vm = if vm = vmap_empty then id else map_rpred (vmap_val vm)
let vmap_vmap vm vt = VMap.fold (fun k v m -> VMap.add k v m) vt vm

let rec is_val_any v =
  if v_kind v = vk_any then true
  else if v_kind v = vk_sum then
    let (_,args) = val2sum v in
      exists_array is_val_any args
  else false

(* Value types *)

(* t_val types are represented as t_vals. possible types are variables and
 * sumtype values *)
type t_val_type = t_val
type t_pred_type = string * t_val_type array

let make_type name typs = sum2val (str2val name, typs)
let break_type typ = let (v,args) = val2sum typ in (val2str v,args)
let string_of_type = string_of_val ~-1

type t_type_vmap = t_vmap
let type_vmap_empty = vmap_empty
let add_type_vmap = add_vmap
let make_type_vmap = make_vmap
let vmap_type = vmap_val
let rename_type = rename_val

let vt_any = anyval
let vt_var = var2val
let vt_str = make_type "string" [||]
let vt_int = make_type "int" [||]
let vt_flt = make_type "float" [||]
let vt_list typ = make_type "list" [|typ|]

let rev_vt_var = val2var

let vt_vargs typ = sum2val (str2val "...", [|typ|])
let is_pred_vargs args =
  try let (name,opt) = val2sum args.(A.length args - 1) in
    if name = str2val "..." then
      Some (A.sub args 0 (A.length args - 1), opt.(0))
    else None
  with _ -> None

(* Predicate modes/ordering/succeeds *)

type t_pred_mode = bool array
type t_pred_order = int * int

type t_succeeds =
    Sk_zero
  | Sk_once
  | Sk_many
type t_determinism = t_succeeds list
(* Fields of tuple: Magic pred name, pred name, mode, valid success counts *)
type t_pred_succeeds = string option * string * t_pred_mode * t_succeeds list

(* Printing *)

let string_of_pred d (name,args) =
  let argstr = sep_string_of_array "," (string_of_val d) args in
    (val2str name) ^ "(" ^ argstr ^ ")"

let string_of_pdrv = function
    (None,p)    -> string_of_pred !print_level p
  | (Some sp,p) -> (string_of_pred !print_level sp) ^ "->" ^ 
                   (string_of_pred !print_level p)

let string_of_rpred rp =
  let sstr = string_of_pdrv (rp.r_session,rp.r_pred) in
    match rp.r_kind with
        Tp_find -> sstr
      | Tp_add -> "+" ^ sstr
      | Tp_negated -> "~" ^ sstr
      | Tp_collect cp -> "\\/" ^ sstr ^ ":" ^ (string_of_pred !print_level cp)

let string_of_rule rule =
  (sep_string_of_list ", " string_of_rpred rule) ^ "."

let full_string_of_val = string_of_val ~-1
let full_string_of_pred = string_of_pred ~-1

(* Registration *)

type t_pred_rep = string * t_val array
let rep2pred (n,args) = (str2val n,args)
let pred2rep (n,args) = (val2str n,args)

(* overwite sum2val/val2sum with different types *)
let sum2val (s,a) = sum2val (str2val s,a)
let val2sum v = let (v,a) = val2sum v in (val2str v,a)

type t_package = {
  p_name : string;
  p_writeout : unit -> unit;
  p_reset : unit -> unit;
  p_add_handlers : (t_pred_type * (t_pred_rep -> unit)) list;
  p_find_handlers : (t_pred_type * ((t_pred_mode * t_succeeds list) list) * 
    (t_pred_rep -> t_pred_rep list)) list;
  p_collect_handlers : (t_pred_type *
    t_pred_mode * (t_pred_rep -> t_pred_rep list -> t_pred_rep list)) list;
  p_predicates : (t_pred_type * t_pred_order list) list;
  p_sessions : (t_pred_type * string list option) list;
  p_sumtypes : (t_val_type * t_pred_type list) list;
  p_abstypes : t_val_type list;
  p_operators : (string * string) list;
}

let empty_package = {
  p_name = "";
  p_writeout = (fun () -> ());
  p_reset = (fun () -> ());
  p_add_handlers = [];
  p_find_handlers = [];
  p_collect_handlers = [];
  p_predicates = [];
  p_sessions = [];
  p_sumtypes = [];
  p_abstypes = [];
  p_operators = [];
}

(* all known packages *)
let packages : (string, t_package) H.t = H.create 10

let register_package pack =
  assert (not (H.mem packages pack.p_name));
  H.replace packages pack.p_name pack

let get_package = H.find packages

let builtin_packages : string list ref = ref []
let set_package_builtin = prepend builtin_packages
let get_builtin_packages() = !builtin_packages

type 'a val_enum = t_val_type * ('a * string) list

let make_enum_sum (name,vals) =
  (name, List.map (fun (_,s) -> (s,[||])) vals)

let enum2val (name,vals) x =
  let (_,s) = List.find (o ((=)x) fst) vals in
    sum2val (s,[||])

let val2enum (name,vals) v =
  let (s,_) = val2sum v in
    try fst (List.find (o ((=)s) snd) vals)
    with Not_found -> pred_unexpected "Bad format (val2enum)"

(* Lists and sum printing *)

(* define list sumtype *)
let list_nil_name = "nil"
let list_cons_name = "cons"
let sum_list = (vt_list (vt_var "X"),[
  (list_cons_name,[|vt_var "X";vt_list (vt_var "X")|]);
  (list_nil_name,[||]);
])

let rec val2list v =
  let (n,args) = id2sum (v_id v) in
  let name = id2str (v_id n) in
    if name = list_cons_name then args.(0)::(val2list args.(1))
    else if name = list_nil_name then []
    else pred_unexpected "Value is not a list"

let rec list2val tail = function
    [] -> (match tail with Some v -> v | None -> sum2val (list_nil_name,[||]))
  | v::xs -> sum2val (list_cons_name,[|v;list2val tail xs|])

let debug_explicit_lists = register_debug "explicit_lists" 
  "Print lists with explicit cons and nil elements"

let string_of_list d v =
  let rec svals prev d v =
    if v_kind v = vk_sum || v_kind v = vk_csum then
      let (n,args) = id2sum (v_id v) in
      let name = id2str (v_id n) in
        if name = list_cons_name then
          let tail = cvt_val_depth d (svals true (d-1) args.(1)) in
            (if prev then "," else "") ^ (string_of_val (d-1) args.(0)) ^ tail
        else ""
    else "|" ^ (string_of_val (d-1) v)  (* Don't care or normal variable *) in
  "[" ^ (svals false d v) ^ "]"

(* get final string_of_sum function, special-casing cons/nil lists *)
let _ = string_of_sum := fun d (name,t) -> cvt_val_depth d
  (let nstr = id2str (v_id name) in
     if not (debug_explicit_lists ()) && 
       (nstr = list_cons_name || nstr = list_nil_name) then
       string_of_list d (sum2val (nstr,t))
     else
       let ts = sep_string_of_array "," (string_of_val (d-1)) t in
         nstr ^ (if t <> [||] then "{" ^ ts ^ "}" else ""))

(* Corpus structures *)

module Corpus = functor (I : Set.OrderedType) -> struct
module IS = Set.Make(I)

(* The corpus of known predicates/rules is a multiply indexed tree.
 * Each tree node is either a short list of predicates/rules,
 * or has one or more indexes for the same set of predicates/rules.
 * Each index is a predicate argument number N, a hash table
 * of subtrees T, and a list of predicates/rules L.
 * Each subtree of T contains all predicates/rules with a particular value
 * for argument N, and L contains all predicates/rules which match
 * any value for argument N.
 *
 * Querying a particular predicate with wildcards/variables is amortized
 * O(N*R), where N is the number of arguments and R is the number of
 * matching predicates. Hash indexes are created lazily.
 * Whenever are searching a tree for a predicate/rule, where the predicate
 * specifies a value for some argument but there are no indexes supporting
 * a search on that argument, a new index is created.
 *
 * Adding a particular predicate is O(N*N), where N is the number of
 * arguments.
 **)

type t_corpustree =
    Tc_list of IS.t * int
  | Tc_hash of t_corpusindex list
and t_corpusindex = int * t_corpustree VH.t * IS.t ref

type t = {
  c_tree : t_corpustree VH.t;
  c_getpred : I.t -> t_pred
}

let new_corpus getpred = {
  c_tree = VH.create 10;
  c_getpred = getpred;
}

let corpus_clear c = VH.clear c.c_tree

let rec corpus_iter_from fn = function
    Tc_list (ents,_) -> IS.iter fn ents
  | Tc_hash inds ->
      let (_,hsh,ents) = List.hd inds in
        VH.iter (fun _ -> corpus_iter_from fn) hsh;
        IS.iter fn !ents

let corpus_iter c fn = VH.iter (fun _ -> corpus_iter_from fn) c.c_tree

let rec corpus_add_from getpred hsh key pinds args value =
  let index_of_list ents = try
    let len = A.length args in
    let ind = find_num (fun i -> not (List.exists ((=) i) pinds)) 0 len in
    let newhsh = VH.create 10 in
    let newents = ref IS.empty in
      IS.iter (fun ent ->
        let (_,args) = getpred ent in
        let newkey = args.(ind) in
          if v_cst newkey then
            try match VH.find newhsh newkey with
                Tc_list (ents,len) ->
                  VH.replace newhsh newkey (Tc_list (IS.add ent ents, len+1))
              | _ -> failwith "Not reachable"
            with Not_found ->
              VH.add newhsh newkey (Tc_list (IS.singleton ent, 1))
          else newents := (IS.add ent !newents)) ents;
      Some (ind,newhsh,newents)
    with Not_found -> None in
  try match VH.find hsh key with
      Tc_list (ents,len) ->
        if IS.mem value ents then false
        else if len >= 5 then
          match index_of_list (IS.add value ents) with
              Some index -> VH.replace hsh key (Tc_hash [index]); true
            | None -> VH.replace hsh key (Tc_list (IS.add value ents, len+1)); true
        else (VH.replace hsh key (Tc_list (IS.add value ents, len+1)); true)
    | Tc_hash indexes ->
        List.fold_left (fun res (n,hsh,ents) ->
          if v_cst args.(n) then
            corpus_add_from getpred hsh args.(n) (n::pinds) args value
          else if IS.mem value !ents then false
          else (ents := IS.add value !ents; true)) false indexes
  with Not_found -> VH.add hsh key (Tc_list (IS.singleton value, 1)); true

let corpus_add c v =
  let (name,args) = c.c_getpred v in
    corpus_add_from c.c_getpred c.c_tree name [] args v

let rec corpus_find_from getpred hsh key pinds args =
  let add_vmas ents vmas =
    IS.fold (fun ent vmas ->
      let (name,entargs) = getpred ent in
        match make_vmap args entargs with
            Some vm -> (vm,ent)::vmas
          | None -> vmas) ents vmas in
  let reindex previndexes pinds = try
    let len = A.length args in
    let ind = find_num (fun i -> not (List.exists ((=) i) pinds)
                          && v_cst (A.get args i)) 0 len in
    let newhsh = VH.create 10 in
    let newents = ref IS.empty in
      corpus_iter_from (fun ent ->
        let (_,args) = getpred ent in
          if v_cst args.(ind) then
            ignore (corpus_add_from getpred newhsh args.(ind)
                      (ind::pinds) args ent)
          else newents := IS.add ent !newents) (Tc_hash previndexes);
      Some(ind,newhsh,newents)
    with Not_found -> None in
  try match VH.find hsh key with
      Tc_list (ents,_) -> add_vmas ents []
    | Tc_hash indexes ->
        try findopt_list (fun (n,hsh,ents) ->
          if v_cst args.(n) then
            Some (add_vmas !ents (corpus_find_from getpred hsh args.(n)
                                    (n::pinds) args))
          else None) indexes
        with Not_found ->
          match reindex indexes pinds with
              Some (n,newhsh,ents) ->
                VH.replace hsh key (Tc_hash (indexes @ [n,newhsh,ents]));
                add_vmas !ents (corpus_find_from getpred newhsh args.(n)
                                  (n::pinds) args)
            | None ->
                let (n,subhsh,ents) = List.hd indexes in
                let vmas = VH.fold
                  (fun key _ vmas -> vmas @
                     (corpus_find_from getpred subhsh key
                        (n::pinds) args)) subhsh [] in
                  add_vmas !ents vmas
  with Not_found -> []

let corpus_find c (name,args) =
  try corpus_find_from c.c_getpred c.c_tree name [] args
  with Invalid_argument "fold_array2" ->
    IO.printf "ERROR: Inconsistent argument counts for %s\n"
      (full_string_of_pred (name,args));
    []

end (* Corpus *)

module LogicCorpusItem = struct 
  type t = t_pred 
  let compare = pred_compare
end
module LogicCorpus = Corpus(LogicCorpusItem)

type t_rulepos = int * int
module RuleCorpusItem = struct
  type t = t_pred * t_rulepos * t_vmap
  let compare ((p1,(r1,l1),v1) : t) ((p2,(r2,l2),v2) : t) =
    if      r1 < r2 then -1
    else if r1 > r2 then 1
    else if l1 < l2 then -1
    else if l1 > l2 then 1
    else 
      let pc = pred_compare p1 p2 in
      if pc <> 0 then pc else compare v1 v2 
end
module RuleCorpus = Corpus(RuleCorpusItem)

(* External sessions *)

type t_ext_session = {

  (* identifying name for this external session *)
  es_name : t_pred;

  (* store all preds in this external session, sorted only by pred name *)
  es_logic_corpus : t_val array list ref VH.t;
}

let new_ext_session name = {
  es_name = name;
  es_logic_corpus = VH.create 10;
}
let get_ext_session_name s = s.es_name

type ext_callbacks = {
  cb_find : t_pred list (* sesslist *) -> t_ext_session list;
  cb_add : t_pred (* sess *) -> t_pred (* pred *) -> unit;
  cb_clear : t_pred (* sess *) -> unit;
  cb_process_dep : t_pred (* sess1 *) -> t_pred (* sess2 *) -> unit;
}
let ext_cb : ext_callbacks ref = ref {
  cb_find = (fun _ -> failwith "No callback");
  cb_add = (fun _ _ -> failwith "No callback");
  cb_clear = (fun _ -> failwith "No callback");
  cb_process_dep = (fun _ _ -> failwith "No callback");
}

let ext_time = ref 0.
let ext_call fn =
  let s = Unix.gettimeofday() in
  let res = fn() in
  let e = Unix.gettimeofday() in
    ext_time := !ext_time +. (e -. s); res

let ext_sessions : (t_pred,t_ext_session) H.t = H.create 10
let ext_pending : (t_pred,unit) H.t = H.create 10
let add_ext_pending sp =
  if not (H.mem ext_sessions sp) then
    H.replace ext_pending sp ()
let get_ext_session sp =
  try H.find ext_sessions sp
  with Not_found ->
    H.replace ext_pending sp ();
    let splist = H.fold (fun sp () splist -> sp::splist) ext_pending [] in
    let eslist = ext_call (fun () -> !ext_cb.cb_find splist) in
      List.iter (fun es -> H.add ext_sessions es.es_name es) eslist;
      assert (H.mem ext_sessions sp);
      H.clear ext_pending;
      H.find ext_sessions sp

let find_ext_logic es (name,args) =
  try let list = VH.find es.es_logic_corpus name in
    List.fold_left (fun rvms fargs ->
      match make_vmap args fargs with
          Some vm -> (vm,(name,fargs))::rvms
        | None -> rvms) [] !list
  with Not_found -> []

let add_ext_logic es (name,args) =
  let list =
    try VH.find es.es_logic_corpus name
    with Not_found ->
      let list = ref [] in VH.add es.es_logic_corpus name list; list in
  prepend list args

let iter_ext_logic es fn =
  VH.iter (fun name list ->
             List.iter (fun args -> fn (name,args)) !list) es.es_logic_corpus

let _ = prepend reset_fns (fun () ->
  ext_time := 0.; H.clear ext_sessions; H.clear ext_pending)

(* Current session *)

(* handlers for packages used in this session, indexed by pred name *)
let s_add_handlers : (t_pred -> unit) VH.t = VH.create 10
let s_find_handlers : (t_pred -> t_pred list) VH.t = VH.create 10
let s_collect_handlers : (t_pred -> t_pred list -> t_pred list) VH.t = VH.create 10

(* all known preds *)
let s_logic_corpus : LogicCorpus.t = LogicCorpus.new_corpus id

(* store all negated/collection queries that have been performed *)
let s_negate_corpus : LogicCorpus.t = LogicCorpus.new_corpus id

(* store all (head,ruleid,vmap) rule continuations.
 * track the number of visits and continuations for each rule with s_rules *)
let s_rule_corpus : RuleCorpus.t = RuleCorpus.new_corpus fst3
let s_rules : (t_rpred array * int ref * int ref) array array ref = 
  ref (A.of_list [])

(* predicates with orders on them, indexed by predicate name *)
let s_pred_orders : t_pred_order VH.t = VH.create 10

(* all forward ordering edges added due to the pred_order predicates *)
let s_order_edges : (unit VH.t) VH.t = VH.create 10

(* maximum length of a path to each value in the forward order graph.
 * smaller length is higher priority in forward traversals,
 * larger length is higher priority in backward traversals *)
let s_order_distance : int VH.t = VH.create 10

(* derivations for known preds and rule continuations *)
let s_logic_drvs : (t_pred,t_pdrvs) H.t = H.create 10
let s_rule_drvs : (t_pred * t_rulepos * t_vmap,t_pdrvs) H.t = H.create 10

let _ = prepend reset_fns (fun () ->
  VH.clear s_add_handlers;
  VH.clear s_find_handlers;
  VH.clear s_collect_handlers;
  LogicCorpus.corpus_clear s_logic_corpus;
  LogicCorpus.corpus_clear s_negate_corpus;
  RuleCorpus.corpus_clear s_rule_corpus;
  s_rules := A.of_list [];
  VH.clear s_pred_orders;
  VH.clear s_order_edges;
  VH.clear s_order_distance;
  H.clear s_logic_drvs;
  H.clear s_rule_drvs)

(* Special predicate handlers *)

let debug_derivs = register_debug "derivs"
  "Track predicate derivations for use by print_derivation()"

(* unique adds, total adds, find attempts, find successes *)
type t_predstats = int ref * int ref * int ref * int ref
let pred_stats : t_predstats VH.t = VH.create 10
let get_pred_stats name =
  try VH.find pred_stats name
  with Not_found ->
    let stats = (ref 0,ref 0,ref 0,ref 0) in
      VH.add pred_stats name stats; stats

let print_pred_counts() =
  let count_compare (_,(u0,_,_,_)) (_,(u1,_,_,_)) = compare u1 u0 in
  let count_string (u,t,a,s) = Printf.sprintf "%8dU %8dT %8dA %8dS" u t a s in
  let (u,t,a,s,counts) = VH.fold (fun name (nu,nt,na,ns) (u,t,a,s,counts) ->
     (u+ !nu,t+ !nt,a+ !na,s+ !ns,(val2str name,(!nu,!nt,!na,!ns))::counts))
    pred_stats (0,0,0,0,[]) in
  let counts = List.sort count_compare (("Total",(u,t,a,s))::counts) in
  let maxlen = List.fold_left (fun len (name,_) ->
                 max len (String.length name)) 0 counts in
    IO.printf "Pred Counts: (U)nique adds, (T)otal adds,";
    IO.printf " (A)ttempted finds, (S)uccessful finds\n";
    List.iter (fun (name,v) ->
      let rem = String.make (maxlen - String.length name) ' ' in
        IO.printf "%s:%s %s\n" name rem (count_string v)) counts

let print_rule_counts() =
  IO.printf "Rule Counts: (Visits) (Continuations) \n";
  A.iter (A.iter (fun (ra,visits,conts) ->
    IO.printf "%8d %8d: %s\n" !visits !conts
      (string_of_rule (A.to_list ra)))) !s_rules

exception Handle_clear_preds
let clear_handler sname =
  ext_call (fun () -> !ext_cb.cb_clear sname); Some []

exception Handle_process_dep of t_pred
let process_dep_handler sname dep =
  ext_call (fun () -> !ext_cb.cb_process_dep sname dep); Some []

exception Handle_print_derivation of int * t_pred

exception Handle_assertion_failure of string

let printed_drvs : (t_pred,unit) H.t = H.create 10
let derivation_handler depth pred drvs =
  let rec print_drv tab depth pred drvs =
    if drvs <> [] && not (H.mem printed_drvs pred) then begin
      H.add printed_drvs pred ();
      if depth > 0 then begin
        IO.printf "%s%s: %s\n" tab (string_of_pred !print_level pred)
          (sep_string_of_list " " string_of_pdrv drvs);
        List.iter (fun (sname,pred) ->
          if sname = None then
            try let drvs = H.find s_logic_drvs pred in
              print_drv (tab ^ "  ") (depth-1) pred drvs
            with Not_found -> ()) drvs
      end else IO.printf "%s%s: ...\n" tab (string_of_pred !print_level pred)
    end in
    if debug_derivs() then print_drv "" depth pred drvs;
    Some []
    

let clear_pred_name = "clear_old_preds"
let process_dep_name = "process_dependency"
let derivation_pred_name = "print_derivation"
let query_pred_name = "$query"
let equal_pred_name = "equal"
let assertion_failure_name = "assertfail"

let _ = prepend reset_fns (fun () ->
  VH.clear pred_stats; H.clear printed_drvs)

(* Logic and ordering *)

let order_distance v =
  try VH.find s_order_distance v with Not_found -> 0

(* rule continuation as used in the pending rule queue *)
type t_rule_cont = t_rpred * t_rulepos * t_vmap * t_pdrvs

let cont_priority (hd0,_,_,_) (hd1,_,_,_) =
  let rec priority pri0 pri1 =
    match (pri0,pri1) with
        [],[] -> 0
      | (Rp_fix n0)::tail0, (Rp_fix n1)::tail1 ->
          let cmp = compare n0 n1 in
            if cmp <> 0 then cmp else priority tail0 tail1
      | (Rp_var (v0,fwd0))::tail0, (Rp_var (v1,fwd1))::tail1 ->
          assert ((not (fwd0 || fwd1)) || (fwd0 && fwd1));
          let cmp =
            if fwd0 then compare (order_distance v0) (order_distance v1)
            else compare (order_distance v1) (order_distance v0) in
          if cmp <> 0 then cmp else priority tail0 tail1
      | _ -> assert false in
  priority hd0.r_priority hd1.r_priority



(* Queue of pending rules for evaluation *)
let s_rule_queues : t_rule_cont PQ.t array ref = ref (A.of_list [])

  (* Index all rule continuations whose priority depends on value order 
   * distance. If the value distance changes (increases, lowering priority) 
   * then affected continuations need to be removed and resorted. *)
let s_queue_orders : (int * PQ.qref) VH.t = VH.create 10


let rule_queue_add stratum (head,tailpos,tailvmap,pdrvs) =
  let qref = PQ.insert !s_rule_queues.(stratum)
    (head,tailpos,tailvmap,pdrvs) in
    List.iter (function
        Rp_var (v,_) -> VH.add s_queue_orders v (stratum,qref)
      | _ -> ()) head.r_priority;
    if head.r_session <> None && head.r_kind <> Tp_add then
      add_ext_pending (get_some head.r_session)

let rule_queue_min stratum = PQ.remove_min !s_rule_queues.(stratum)

(* add ordering edge betweeen v0 and v1, calculate new distances *)
let add_order_edge v0 v1 =
  let edges v =
    try VH.find s_order_edges v
    with Not_found ->
      let hsh = VH.create 10 in VH.add s_order_edges v hsh; hsh in
  let rec set_distance stack v n =
    if List.exists ((=)v) stack then
      IO.printf "WARNING: Ordering cycle on %s\n"
        (string_of_val !print_level v)
    else if order_distance v < n then begin
      VH.replace s_order_distance v n;
      (* resort any affected queue elements *)
      let rlist = VH.find_all s_queue_orders v in
      let clist = List.map (fun (stratum,r) -> 
	(stratum,r,PQ.remove !s_rule_queues.(stratum) r)) rlist in
        List.iter (function
                       (stratum,r,Some cont) -> PQ.reinsert 
			 !s_rule_queues.(stratum) cont r
                     | (_,r,None) -> ()) clist;
      VH.iter (fun nv _ -> set_distance (v::stack) nv (n + 1)) (edges v)
    end in
  let hsh = edges v0 in
  if not (VH.mem hsh v1) then begin
    VH.replace hsh v1 ();
    set_distance [] v1 (order_distance v0 + 1)
  end

let debug_order_edges = register_debug "order_edges"
  "Print added ordering edges"

(* Add pred to s and get any pending rule/vm continuations.
 * Returns None if the fact already existed in the database, Some cs
 * if the fact was new. *)
let add_logic_rvms drvs (n,args) =
  let (unique,total,_,_) = get_pred_stats n in
    incr total;
    if LogicCorpus.corpus_add s_logic_corpus (n,args) then begin
      incr unique;
      List.iter (fun (a0,a1) ->
          if debug_order_edges() then
            IO.printf "Ordering edge %s: %s -> %s\n"
              (full_string_of_pred (n,args))
              (full_string_of_val args.(a0)) (full_string_of_val args.(a1));
          add_order_edge args.(a0) args.(a1))
        (VH.find_all s_pred_orders n);
      if debug_derivs() then H.add s_logic_drvs (n,args) drvs;
      Some (RuleCorpus.corpus_find s_rule_corpus (n,args))
    end else None

let find_logic_vms (n,args) =
  let (_,_,attempts,successes) = get_pred_stats n in
  let res = LogicCorpus.corpus_find s_logic_corpus (n,args) in
    incr attempts; successes := !successes + (List.length res); res

let rule_corpus_add stratum spo drvs (head,tailpos,tailvmap) =
  (* don't add the rule if a matching fact cannot be added later:
   * there is a find handler, or spo is a different session from s *)
  if VH.mem s_find_handlers (fst head) || spo <> None then true
  else if RuleCorpus.corpus_add s_rule_corpus (head,tailpos,tailvmap) then 
  begin
    if debug_derivs() then H.add s_rule_drvs (head,tailpos,tailvmap) drvs;
    incr (thd3 (!s_rules.(stratum).(fst tailpos)));
    true
  end else false

let _ = prepend reset_fns (fun () ->
  s_rule_queues := A.of_list [];
  VH.clear s_queue_orders)

(* Processing Functions *)

let add_session_logic es =
  ignore (LogicCorpus.corpus_add s_logic_corpus es.es_name);
  iter_ext_logic es (o ignore (add_logic_rvms []))

let iter_logic fn = LogicCorpus.corpus_iter s_logic_corpus fn

let logic_corpus_add spo pred drvs sfa =
  try (VH.find s_add_handlers (fst pred)) pred; Some []
  with Unexpected str ->
        IO.printf "ERROR: %s: +%s: %s\n" (string_of_sfa sfa) 
	  (string_of_pred !print_level pred) str; Some []
     | Handle_clear_preds -> clear_handler (get_some spo)
     | Handle_process_dep dep -> process_dep_handler (get_some spo) dep
     | Handle_print_derivation (d,pred) -> derivation_handler d pred drvs
     | Not_found ->
         match spo with
             Some sp -> ext_call (fun () -> !ext_cb.cb_add sp pred; Some [])
           | None -> add_logic_rvms drvs pred

let logic_corpus_find spo pred sfa =
  try let preds = (VH.find s_find_handlers (fst pred)) pred in
    if spo <> None then
      IO.printf "ERROR: External session used with find handler: %s\n"
        (string_of_pred !print_level pred);
    List.fold_left (fun res fpred ->
      match make_vmap (snd pred) (snd fpred) with
          Some vm -> (vm,fpred)::res
        | None -> res) [] preds
  with Unexpected str ->
         IO.printf "ERROR: %s: %s: %s\n" (string_of_sfa sfa) 
	   (string_of_pred !print_level pred) str; []
     | Not_found ->
         match spo with
             Some sp -> find_ext_logic (get_ext_session sp) pred
           | None -> find_logic_vms pred

let debug_add_rule = register_debug "add_rule"
  "Print each added rule continuation"
let debug_add_logic = register_debug "add_logic"
  "Print each added predicate"

let debug_eval_rule = register_debug "eval_rule"
  "Print each evaluated rule continuation"

(* add all rules and fixpoint logic to completion/timeout *)
let rec fixpoint_stratum stratum rqitems =
  let print_rule_cont msg (rhead,rtailpos,rvmap,_) =
    let (rule,_,_) = !s_rules.(stratum).(fst rtailpos) in
    let rtail = fold_num_down (fun i rs -> (rule.(i))::rs) []
      ((A.length rule) - 1) ((snd rtailpos) - 1) in
    let rpriostr = sep_string_of_list " "
      (function Rp_fix n -> string_of_int n
              | Rp_var(v,fwd) ->
                  (string_of_val !print_level v) ^ (if fwd then "+" else "-"))
      rhead.r_priority in
    IO.printf "%s(%d): [%s] %s\n" msg stratum rpriostr
      (string_of_rule (rhead::(vmap_rule rvmap rtail))) in
  let add_drv (spo,pred) drvs =
    if VH.mem s_find_handlers (fst pred) then drvs else (spo,pred)::drvs in

  let rec add_rule (rid, rpos) rvmap drvs =
    let (rule,visits,_) = !s_rules.(stratum).(rid) in
    incr visits;
    if rpos < A.length rule then begin
      let nhead = (vmap_rpred rvmap rule.(rpos)) in
      let npos = (rid, rpos + 1) in
	if nhead.r_stratum < stratum then
	  eval_rule nhead npos rvmap drvs
	else
	  let cont = (nhead, npos, rvmap, drvs) in
            if debug_add_rule() then
              print_rule_cont "add_rule" cont;
            rule_queue_add stratum cont
    end
  and add_rule_tuple (a,b,c) = add_rule a b c
  and eval_rule rhead rtailpos rvmap rdrvs =      
    if debug_eval_rule() then
      print_rule_cont "eval_rule" (rhead,rtailpos,rvmap,rdrvs);
    let (spo,pred) = (rhead.r_session,rhead.r_pred) in
    match rhead.r_kind with
        Tp_find ->
          if rhead.r_stratum < stratum || 
	    rule_corpus_add stratum spo rdrvs (pred,rtailpos,rvmap) then
            let vmlist = logic_corpus_find spo pred rhead.r_sfa in
            let rhash = H.create 10 in
              List.iter (fun (vm,lp) ->
                if not (H.mem rhash vm) then begin
                  H.add rhash vm ();
                  add_rule rtailpos (vmap_vmap vm rvmap)
                    (add_drv (spo,lp) rdrvs) 
                end) vmlist
      | Tp_negated ->
          let vmlist = logic_corpus_find spo pred rhead.r_sfa in
            if vmlist = [] then begin
              if spo = None then 
                ignore (LogicCorpus.corpus_add s_negate_corpus pred) ;
              add_rule rtailpos rvmap rdrvs
            end
      | Tp_add ->
          if debug_add_logic() then
            IO.printf "add_logic(%d): %s\n" stratum 
	      (string_of_pred !print_level pred);
          let rename = (string_of_int (fst rtailpos)) ^ "%" in
          let pred = map_pred (rename_val rename) pred in
            (match logic_corpus_add spo pred rdrvs rhead.r_sfa with
	      | None -> ()
	      | Some rvmlist -> 
		  if spo = None &&
		    LogicCorpus.corpus_find s_negate_corpus pred <> [] then
		    IO.printf "ERROR: Invalidated negation/collection: %s\n"
		      (string_of_pred !print_level pred);
		  let nrules = List.map (fun (vm,(nhead,ntailpos,nvmap)) ->
		    let ndrvs =
                      if debug_derivs() then H.find s_rule_drvs 
			(nhead,ntailpos,nvmap)
                      else [] in
		      (ntailpos,(vmap_vmap vm nvmap),
                      (add_drv (None,pred) ndrvs))) rvmlist in
		    if rhead.r_stratum < stratum then
		      fixpoint_stratum rhead.r_stratum nrules 
		    else
		      List.iter add_rule_tuple nrules
	    );
	    add_rule rtailpos rvmap rdrvs
      | Tp_collect cp ->
          if spo = None then
            ignore (LogicCorpus.corpus_add s_negate_corpus pred);
          try let matches = List.map (fun (vm,_) -> map_pred (vmap_val vm) cp)
                              (logic_corpus_find spo pred rhead.r_sfa) in
              let preds = (VH.find s_collect_handlers (fst cp)) cp matches in
                List.iter (fun fcp ->
                  match make_vmap (snd cp) (snd fcp) with
                      Some vm -> add_rule rtailpos (vmap_vmap vm rvmap) rdrvs
                    | None -> ()) preds
          with Unexpected str ->
            IO.printf "ERROR: %s: %s: %s\n" (string_of_sfa rhead.r_sfa) 
	      (string_of_rpred rhead) str in
    if debug_eval_rule () then 
      IO.printf "Entering stratum %d\n" stratum;
    List.iter add_rule_tuple rqitems;
    try while true do
	let (rhead,rtailpos,rvmap,rdrvs) = rule_queue_min stratum in
	  eval_rule rhead rtailpos rvmap rdrvs
      done 
    with PQ.Empty -> 
      if debug_eval_rule () then 
	IO.printf "Leaving stratum %d\n" stratum
	
let add_session_rules rules =
  s_rules := A.map (fun rs ->
    A.of_list (List.map (fun r -> (A.of_list r, ref 0, ref 0)) rs)
  ) rules;
  s_rule_queues := A.init (A.length !s_rules) (fun i ->
    PQ.create cont_priority (fun (hd,_,_,_) -> string_of_rpred hd)
  );
  A.iteri (fun stratum rules ->
    let rqitems = A.mapi (fun i _ -> ((i,0),vmap_empty,[])) rules in
      fixpoint_stratum stratum (A.to_list rqitems)
  ) !s_rules
  
let add_session_rules = make_track_1 "add_session_rules" add_session_rules

let check_succeeds allsucceeds =
  List.iter (fun (mnameo,name,mode,succeeds) ->
    let args = A.init (A.length mode)
                 (fun i -> var2val ("%" ^ (string_of_int i))) in
    let pred = rep2pred (name,args) in
    let mhits = match mnameo with
      | None -> [vmap_empty,(anyval,[||])]
      | Some mname ->
          let mgcargs = A.mapi (fun i v -> if mode.(i) then v else anyval) 
            args in
          let mgcpred = rep2pred (mname,mgcargs) in
            LogicCorpus.corpus_find s_logic_corpus mgcpred in
      List.iter (fun (vm,_) ->
        let npred = vmap_pred vm pred in
        let nhits = LogicCorpus.corpus_find s_logic_corpus npred in
        let nhits_count = List.length nhits in
        let count_ok = match nhits_count with
            0 -> List.mem Sk_zero succeeds
          | 1 -> List.mem Sk_once succeeds || List.mem Sk_many succeeds
          | _ -> List.mem Sk_many succeeds in
        if not count_ok then begin
          IO.printf "WARNING: Predicate %s succeeded %d times:"
            (full_string_of_pred npred) nhits_count;
          List.iter (fun (_,nhit) ->
            IO.printf " %s" (full_string_of_pred nhit)) nhits;
          IO.printf "\n"
        end) mhits) allsucceeds

let check_succeeds = make_track_1 "check_succeeds" check_succeeds

let add_package pname =
  let pack = H.find packages pname in
    List.iter (fun ((name,_),addfn) ->
      VH.add s_add_handlers (str2val name)
        (fun p -> addfn (pred2rep p)))
      pack.p_add_handlers;
    List.iter (fun ((name,_),_,findfn) ->
      VH.add s_find_handlers (str2val name)
        (fun p -> List.map rep2pred (findfn (pred2rep p))))
      pack.p_find_handlers;
    List.iter (fun ((name,_),_,collectfn) ->
      VH.add s_collect_handlers (str2val name)
        (fun p plist -> List.map rep2pred
                          (collectfn (pred2rep p) (List.map pred2rep plist))))
      pack.p_collect_handlers

let add_pred_order name (src,tgt) =
  VH.add s_pred_orders (str2val name) (src,tgt)

let debug_no_catch = register_debug "no_catch"
  "Do not trap exceptions thrown by interpreter"
let debug_no_succeeds = register_debug "no_succeeds"
  "Do not check 'succeeds' directives"

let stats_pred_counts = register_stats "pred_counts"
  "Print add/find counts for each pred"
let stats_rule_counts = register_stats "rule_counts"
  "Print continuation counts for each rule"
let stats_pred_counts_timeout = register_stats "pred_counts_timeout"
  "Print add/find counts only when a timeout occurs"

type anly_spec = {
  as_session : t_ext_session option;
  as_rules : t_rule list array;
  as_packages : string list;
  as_orders : (string,t_pred_order) Hashtbl.t;
  as_succeeds : t_pred_succeeds list;
}

type anly_status =
    Ar_success
  | Ar_timeout of float
  | Ar_failure of string
  | Ar_ext_error of string

let run_analysis timeout cbs aspc =
  Signal.set_sigalrm timeout;
  ext_cb := cbs;
  List.iter add_package aspc.as_packages;
  H.iter (fun name (src,tgt) -> add_pred_order name (src,tgt)) aspc.as_orders;
  let b = Unix.gettimeofday() in
  let success =
   try 
     (match aspc.as_session with None -> () | Some es -> add_session_logic es);
     add_session_rules aspc.as_rules;
     if not (debug_no_succeeds()) then
       check_succeeds aspc.as_succeeds;
     Ar_success
   with Signal.Signal "SIGALRM" ->
          if stats_pred_counts_timeout() then
            print_pred_counts();
          Ar_timeout !ext_time
      | Handle_assertion_failure msg ->
	  Ar_failure msg
      | exn when not (Signal.is_signal exn) ->
          if debug_no_catch() then raise exn
          else Ar_failure ("Unknown exception: " ^ (Printexc.to_string exn)) in
  Signal.set_sigalrm 0;  (* there is technically a race with SIGALRM here *)
  let e = Unix.gettimeofday() in
  if stats_pred_counts() then print_pred_counts();
  if stats_rule_counts() then print_rule_counts();
    (success, e -. b -. !ext_time)

let writeout_packages packs =
  List.iter (fun name -> (H.find packages name).p_writeout()) packs

let reset_packages packs =
  List.iter (fun name -> (H.find packages name).p_reset()) packs;
  reset()

let curfile = ref ""
let curline = ref 1
let cur_sfa () = Sfa_file (!curfile, !curline)

let change_sfa (file,line) =
  let oldfile = !curfile in
  let oldline = !curline in
    curfile := file;
    curline := line;
    (oldfile,oldline)

let debug_parse_warnings = register_debug "parse_warnings"
  "Warn instead of fail on non-fatal parse-time errors"

let num_warnings = ref 0

let parse_error desc =
  Printf.eprintf "%s: parse error: %s\n"
    (string_of_sfa (cur_sfa ())) desc; exit 1
let rule_error sfa desc =
  Printf.eprintf "%s: parse error: %s\n"
    (string_of_sfa sfa) desc; exit 1
let rule_warning sfa desc =
  Printf.printf "%s: warning: %s\n"
    (string_of_sfa sfa) desc; incr num_warnings

let check_warnings() =
  if !num_warnings > 0 && not (debug_parse_warnings ()) then
    (Printf.eprintf "parse error: Warnings treated as errors\n"; exit 1);
  num_warnings := 0;

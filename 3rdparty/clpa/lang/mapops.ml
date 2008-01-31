(*
 * Authors:
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
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

(* Built-in map/set ADT implementations *)

module A = Array
module S = String
module H = Hashtbl
module IO = Streamio
open Spec
open Clpautil

let vt_kvar = vt_var "X"
let vt_vvar = vt_var "Y"

(* Set ADT implementation *)

let set_add_handlers = ref []
let set_find_handlers = ref []
let set_collect_handlers = ref []

module SetHashType = struct
  type t     = t_val list  (* sorted, no duplicates *)
  let  equal (s1:t) (s2:t) = (s1 = s2)
  let  hash  = H.hash
end
module SetHash = Hashcons.Make(SetHashType)
let id2set = SetHash.id2a
let set2id = SetHash.a2id

let set2str d mid = cvt_val_depth d
  (let sl = List.fold_right (fun v l -> 
     (string_of_val (d-1) v)::l) 
     (id2set mid) [] in
   "[" ^ (sep_string_of_list "; " id sl) ^ "]")

let set_compare id0 id1 =
  compare_lists compare_vals (id2set id0) (id2set id1)

let set_dump ds id = IO.dump_list ds dump_val (id2set id)

let set_load ls =
  let elts = IO.load_list ls load_val in
    set2id elts

let vk_set = register_val_kind {
    vki_tostring = set2str;
    vki_compare  = set_compare;
    vki_dump     = set_dump;
    vki_load     = set_load;
}
let vt_set v  = make_type "set" [|v|]
let set2val s = cst2val vk_set (set2id s)
let val2set v = id2set (val2cst vk_set v)

let _ = prepend set_find_handlers
  (("set_empty",[|vt_set vt_vvar|]),[[|false|],[Sk_once]],
   fun (name,args) ->
     [name, [|set2val []|]])

let _ = prepend set_find_handlers
  (("set_singleton",
    [|vt_vvar;vt_set vt_vvar|]),
    [([|true;false|],[Sk_once]); ([|false;true|], [Sk_zero;Sk_once])],
   fun (name,args) ->
     if is_val_const args.(1) then
       match val2set args.(1) with
           [v] -> [name,[|v;args.(1)|]]
         | _ -> []
     else [name, [|args.(0);set2val [args.(0)]|]])

let _ = prepend set_find_handlers
  (("set_insert",
    [|vt_vvar;vt_set vt_vvar;vt_set vt_vvar|]),
    [[|true;true;false|], [Sk_once]],
   fun (name,args) ->
     let set  = val2set args.(1) in
     let nset =
       if List.exists ((=)args.(0)) set then set
       else List.sort compare_vals (args.(0)::set) in
     [name, [|args.(0);args.(1);set2val nset|]])

let _ = prepend set_find_handlers
  (("set_member",
    [|vt_set vt_vvar;vt_vvar|]), [[|true;false|], [Sk_zero;Sk_many]],
   fun (name,args) ->
     let set = val2set args.(0) in
     let res =
       if is_val_const args.(1) then
         if List.exists ((=)args.(1)) set then [args.(1)] else []
       else set in
     List.map (fun v -> (name, [|args.(0);v|])) res)

let _ = prepend set_find_handlers
  (("set_remove",
    [|vt_vvar;vt_set vt_vvar;vt_set vt_vvar|]),
    [[|true;true;false|], [Sk_once]],
   fun (name,args) ->
     let set  = val2set args.(1) in
     let nset = List.filter ((<>)args.(0)) set in
     [name, [|args.(0);args.(1);set2val nset|]])

let ss2s_handler pred op =
  ((pred,
    [|vt_set vt_vvar; vt_set vt_vvar; vt_set vt_vvar|]),
    [[|true; true; false|], [Sk_once]],
   fun (name,args) ->
     let s0 = val2set args.(0) in
     let s1 = val2set args.(1) in
     [name, [|args.(0);args.(1);set2val (op s0 s1)|]])

let union s0 s1 =
  let missing = List.filter (fun v -> not (List.exists ((=)v) s1)) s0 in
    List.sort compare_vals (missing @ s1)
let _ = prepend set_find_handlers (ss2s_handler "set_union" union)

let intersect s0 s1 =
  List.filter (fun v -> List.exists ((=)v) s1) s0
let _ = prepend set_find_handlers (ss2s_handler "set_intersect" intersect)

let difference s0 s1 =
  List.filter (fun v -> not (List.exists ((=)v) s1)) s0
let _ = prepend set_find_handlers (ss2s_handler "set_difference" difference)

let ss2b_handler pred op =
  ((pred,
    [|vt_set vt_vvar; vt_set vt_vvar|]),
    [[|true; true|], [Sk_zero;Sk_once]],
   fun (name,args) ->
     let s0 = val2set args.(0) in
     let s1 = val2set args.(1) in
       if op s0 s1 then [name, [|args.(0);args.(1)|]] else [])

let _ = prepend set_find_handlers (ss2b_handler "set_subset"
  (fun s0 s1 -> not (List.exists (fun v -> not (List.exists ((=)v) s1)) s0)))
let _ = prepend set_find_handlers (ss2b_handler "set_superset"
  (fun s0 s1 -> not (List.exists (fun v -> not (List.exists ((=)v) s0)) s1)))

let _ = prepend set_find_handlers
  (("set_to_sorted_list",
    [|vt_set vt_vvar; vt_list vt_vvar|]),
    [[|true; false|], [Sk_once]],
   fun (name,args) ->
     let set  = val2set args.(0) in
       [name,[|args.(0);list2val None set|]])

let _ = prepend set_find_handlers
  (("set_of_list",
    [|vt_list vt_vvar; vt_set vt_vvar|]),
    [[|true; false|], [Sk_once]],
   fun (name,args) ->
     let list = val2list args.(0) in
     let set = List.sort compare_vals (List.fold_left (fun s v ->
       if (List.exists ((=)v) s) then s else v::s) [] list) in
     [name, [|args.(0);set2val set|]])

let _ = prepend set_collect_handlers
  (("set_all",[|vt_vvar;vt_set vt_vvar|]),[|true;false|],
   fun (name,_) matches ->
     let set = List.sort compare_vals (List.fold_left (fun s (_,args) ->
       if (List.exists ((=)args.(0)) s) then s else args.(0)::s) [] matches) in
     [name,[|anyval;set2val set|]])

let _ = prepend set_collect_handlers
  (("set_union_all",[|vt_set vt_vvar;vt_set vt_vvar|]),[|true;false|],
   fun (name,_) matches ->
     let set = List.fold_left (fun s (_,args) ->
       union s (val2set args.(0))) [] matches in
     [name,[|anyval;set2val set|]])

let _ = prepend set_collect_handlers
  (("set_intersect_all",[|vt_set vt_vvar;vt_set vt_vvar|]),[|true;false|],
   fun (name,_) matches ->
     match matches with
         (_,args)::rest ->
           let fs = val2set args.(0) in
           let set = List.fold_left (fun s (_,args) ->
             intersect s (val2set args.(0))) fs rest in
           [name,[|anyval;set2val set|]]
       | [] -> [])

let set_reset () =
  SetHash.clean ()

let _ = register_package { empty_package with
  p_name = "set";
  p_reset = set_reset;
  p_add_handlers = !set_add_handlers;
  p_find_handlers = !set_find_handlers;
  p_collect_handlers = !set_collect_handlers;
  p_abstypes = [vt_set vt_vvar];
}

(* Map ADT implementation *)

let map_add_handlers = ref []
let map_find_handlers = ref []
let map_collect_handlers = ref []

module MapHashType = struct
  type t     = (t_val * t_val) list  (* sorted by key, no duplicate keys *)
  let  equal (m1:t) (m2:t) = (m1 = m2)
  let  hash  = H.hash
end
module MapHash = Hashcons.Make(MapHashType)
let id2map = MapHash.id2a
let map2id = MapHash.a2id

let compare_vals_map (k0,v0) (k1,v1) =
  let cmp = compare_vals k0 k1 in
    if cmp <> 0 then cmp else compare_vals v0 v1

let map2str d mid = cvt_val_depth d
  (let sl = List.fold_right (fun (k,v) l ->
     ((string_of_val (d-1) k) ^ " -> " ^ (string_of_val (d-1) v))::l) 
     (id2map mid) [] in
   "[" ^ (sep_string_of_list "; " id sl) ^ "]")

let map_compare id0 id1 =
  compare_lists compare_vals_map (id2map id0) (id2map id1)

let map_dump ds id =
  List.iter (fun (k,v) ->
    IO.dump_bool ds true;
    dump_val ds k;
    dump_val ds v
  ) (id2map id);
  IO.dump_bool ds false

let map_load ls =
  let m = ref [] in
  while IO.load_bool ls do
    let k = load_val ls in
    let v = load_val ls in
    m := (k,v)::!m
  done;
  map2id (List.rev !m)

let vk_map = register_val_kind {
    vki_tostring = map2str;
    vki_compare  = map_compare;
    vki_dump     = map_dump;
    vki_load     = map_load;
}
let vt_map k v  = make_type "map" [|k;v|]
let map2val m = cst2val vk_map (map2id m)
let val2map v = id2map (val2cst vk_map v)

let _ = prepend map_find_handlers
  (("map_empty",[|vt_map vt_kvar vt_vvar|]),[[|false|], [Sk_once]],
   fun (name,args) ->
     [name, [|cst2val vk_map (map2id [])|]])

let _ = prepend map_find_handlers
  (("map_insert",
    [|vt_kvar;vt_vvar;vt_map vt_kvar vt_vvar;vt_map vt_kvar vt_vvar|]),
    [[|true;true;true;false|], [Sk_once]],
   fun (name,args) ->
     let map  = val2map args.(2) in
     let fmap = List.filter (o ((<>)args.(0)) fst) map in
     let nmap = List.sort compare_vals_map ((args.(0),args.(1))::fmap) in
     [name, [|args.(0);args.(1);args.(2);map2val nmap|]])

let _ = prepend map_find_handlers
  (("map_search",
    [|vt_map vt_kvar vt_vvar;vt_kvar;vt_vvar|]), 
    [[|true;false;false|], [Sk_zero;Sk_many]],
   fun (name,args) ->
     let map  = val2map args.(0) in
     let res =
       if is_val_const args.(1) then
         try let (_,v) = List.find (o ((=)args.(1)) fst) map in [args.(1),v]
         with Not_found -> []
       else map in
     List.map (fun (k,v) -> (name, [|args.(0);k;v|])) res)

let _ = prepend map_find_handlers
  (("map_remove",
    [|vt_kvar;vt_map vt_kvar vt_vvar;vt_map vt_kvar vt_vvar|]),
    [[|true;true;false|], [Sk_once]],
   fun (name,args) ->
     let map  = val2map args.(1) in
     let nmap = List.filter (o ((<>)args.(0)) fst) map in
     [name, [|args.(0);args.(1);map2val nmap|]])
     
let _ = prepend map_find_handlers
  (("map_to_sorted_list",
    [|vt_map vt_kvar vt_vvar;vt_list (Builtin.vt_pair vt_kvar vt_vvar)|]),
    [[|true;false|], [Sk_once]],
   fun (name,args) ->
     let map  = val2map args.(0) in
     let l = List.map (fun (k,v) -> (Builtin.pair2val k v)) map in
       [name,[|args.(0);list2val None l|]])

let _ = prepend map_find_handlers
  (("map_of_list",
    [|vt_list (Builtin.vt_pair vt_kvar vt_vvar);vt_map vt_kvar vt_vvar|]),
    [[|true;false|], [Sk_once]],
   fun (name,args) ->
     let list = val2list args.(0) in
     let map = List.sort compare_vals_map (List.fold_left (fun m p ->
       let (k,v) = Builtin.val2pair p in
         if (List.exists (o ((=)k) fst) m) then m else (k,v)::m) [] list) in
     [name, [|args.(0);map2val map|]])
  
let _ = prepend map_collect_handlers
  (("map_all",[|vt_kvar;vt_vvar;vt_map vt_kvar vt_vvar|]),[|true;true;false|],
   fun (name,_) matches ->
     (* Sort the collected values to ensure canonicality of the map that is
      * produced in case of duplicates *)
     let list = List.map (fun (_,args) -> (args.(0),args.(1))) matches in
     let list = List.sort compare_vals_map list in
     let map = List.sort compare_vals_map (List.fold_left (fun m (k,v) ->
       if (List.exists (o ((=)k) fst) m) then
         pred_unexpected "Duplicate keys in matching predicates"
       else (k,v)::m) [] list) in
     [name,[|anyval;anyval;map2val map|]])

let map_reset () =
  MapHash.clean ()

let _ = register_package { empty_package with
  p_name = "map";
  p_reset = map_reset;
  p_add_handlers = !map_add_handlers;
  p_find_handlers = !map_find_handlers;
  p_collect_handlers = !map_collect_handlers;
  p_abstypes = [vt_map vt_kvar vt_vvar];
}

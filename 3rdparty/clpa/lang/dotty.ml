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

(* Predicates for generating Dot graph files *)

open Spec
open Clpautil
open Flags
open Builtin

module H = Hashtbl
module A = Array
module V = Vector
module IO = Streamio

(* Dot graphs *)

let vt_nvar = vt_var "N"
let vt_evar = vt_var "E"

let vt_dgattr = make_type "t_dg_attr" [||] 
let sum_dgattr = (vt_dgattr, [("dg_attr", [|vt_str;vt_str|])])

let vt_dgnode n = make_type "t_dg_node" [|n|]
let sum_dgnode = (vt_dgnode vt_nvar, [
  ("dg_node", [|vt_nvar;vt_list vt_dgattr|])
])

let vt_dgedge n = make_type "t_dg_edge" [|n|]
let sum_dgedge = (vt_dgedge vt_nvar, [
  ("dg_edge", [|vt_nvar;vt_nvar;vt_list vt_dgattr|])
])

let vt_dotgraph n = make_type "t_dotgraph" [|n|]
let sum_dotgraph = (vt_dotgraph vt_nvar, [
    ("dotgraph", [|vt_list (vt_dgnode vt_nvar); vt_list (vt_dgedge vt_nvar)|])
])
		 

type dgattrs = (string * string) list

type dotgraph = {
  dg_name : string;
  dg_directed : bool;

  dg_graphattrs : dgattrs;
  dg_nodeattrs : dgattrs;
  dg_edgeattrs : dgattrs;

  dg_nodes : (t_val, dgattrs) H.t;
  dg_edges : (t_val*t_val*dgattrs) list;
}

let output_dotgraph fout dg =
  let out = IO.fprintf fout "%s" in
  let attr2str (attr,vs) = attr ^ "=\"" ^ (String.escaped vs) ^ "\"" in
  let attrs2str btxt atxt attrs =
    if attrs = [] then ""
    else btxt ^ " [" ^ (sep_string_of_list "," attr2str attrs) ^ "]" ^ atxt in
  let escp = o String.escaped (string_of_val !print_level) in
  let (gs,es) = if dg.dg_directed then ("digraph","->") else ("graph","--") in
    out (gs ^ " \"" ^ (String.escaped dg.dg_name) ^ "\" {\n");
    out (attrs2str "  graph" ";\n" dg.dg_graphattrs);
    out (attrs2str "  node"  ";\n" dg.dg_nodeattrs);
    out (attrs2str "  edge"  ";\n" dg.dg_edgeattrs);
    H.iter (fun vname attrs ->
      out ("  \"" ^ (escp vname) ^ "\"");
      out ((attrs2str "" "" attrs) ^ ";\n")) dg.dg_nodes;
    List.iter (fun (sname,tname,attrs) ->
      out ("  \"" ^ (escp sname) ^ "\" " ^ es ^ " \"" ^ (escp tname) ^ "\"");
      out ((attrs2str "" "" attrs) ^ ";\n")) dg.dg_edges;
    out "}\n"

let dotgraphs : dotgraph V.t = V.create 10
let dotgraph_hash : (string, int) H.t = H.create 10

let debug_dotty_database = register_debug "dotty_database"
  "Write dotty graphs into dotty.db"

let write_dotgraphs () =
  V.iter (fun graph ->
    if H.length graph.dg_nodes > 0  then
      let fout =
        if debug_dotty_database() then
          IO.open_dbentry "dotty" graph.dg_name IO.Pt_trunc
        else IO.open_file (graph.dg_name ^ ".dot") IO.Pt_trunc in
      output_dotgraph fout graph;
      IO.close_stream fout) dotgraphs

(* Dot package *)

let add_handlers = ref []

let check_const args =
  if exists_array (o not is_val_const) args then
    pred_unexpected "Underconstrained"

let val2attr v = let a = snd (val2sum v) in (val2str a.(0), val2str a.(1))
let val2node v = 
  let a = snd (val2sum v) in (a.(0), List.map val2attr (val2list a.(1)))
let val2edge v = 
  let a = snd (val2sum v) in (a.(0), a.(1), List.map val2attr (val2list a.(2)))

let _ = prepend add_handlers
  (("dotty_graph",[|vt_str; vt_bool; vt_dotgraph vt_any;vt_list vt_dgattr;
		    vt_list vt_dgattr; vt_list vt_dgattr|]),
   fun (name,args) ->
     check_const args;
     let dgname = val2str args.(0) in
     let directed = val2bool args.(1) in
     let dotgraph = snd (val2sum args.(2)) in
     let nodes = List.map val2node (val2list dotgraph.(0)) in
     let edges = List.map val2edge (val2list dotgraph.(1)) in
     let nh = H.create 10 in
     List.iter (fun (n, a) -> H.add nh n a) nodes;
     List.iter (fun (n1, n2, _) -> 
       if not (H.mem nh n1) then H.add nh n1 [];
       if not (H.mem nh n2) then H.add nh n2 []
     ) edges;
     let dgr = {
       dg_name = dgname;
       dg_directed = directed;

       dg_graphattrs = List.map val2attr (val2list args.(3));
       dg_nodeattrs = List.map val2attr (val2list args.(4));
       dg_edgeattrs = List.map val2attr (val2list args.(5));

       dg_nodes = nh;
       dg_edges = edges;
     } in
       try ignore (H.find dotgraph_hash dgname)
       with Not_found ->
         let dgr = V.append dotgraphs dgr in
           H.add dotgraph_hash dgname dgr
  )

let _ = register_package { empty_package with
  p_name = "dotty";
  p_writeout = write_dotgraphs;
  p_reset = (fun () -> V.clear dotgraphs; H.clear dotgraph_hash);
  p_add_handlers = !add_handlers;
  p_sumtypes = [sum_dgattr;sum_dgnode;sum_dgedge;sum_dotgraph];
}

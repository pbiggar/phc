(*
 * Authors:
 *   Yichen Xie  <yxie@cs.stanford.edu>
 *
 * Copyright (c) 2004,
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

(* graph.ml -- general purpose graph library *)

module V = Vector

module type OrderedType = sig
  type t
  val compare: t -> t -> int
end

module Make = functor (OrderedData: OrderedType) -> struct
  type data = OrderedData.t
      
  type n = int				(* type of node_id *)
  type e = n * n
  type node = { node_id : n;
		data: data;
		mutable preds: node list;
		mutable succs: node list
	      }

  module OrderedEdge = struct
    type t = e				(* from node to node *)
    let compare ((a0,a1) : int * int) ((b0,b1) : int * int) : int = 
      if a0 = b0 then compare a1 b1 else compare a0 b0
  end

  module OrderedNode = struct
    type t = n 
    let compare (a : int) (b : int) : int = compare a b
  end
    
  module NodeSet = Set.Make (OrderedNode)
  type nodeset = NodeSet.t

  module M = Map.Make (OrderedData)
  module E = Set.Make (OrderedEdge)

  module NM = Map.Make (OrderedNode)
  module NS = Set.Make (OrderedNode)

  type t = { mutable g_nmap : node M.t;	(* data -> node *)
	     mutable g_edges : E.t;	(* e set  *)
	     mutable g_nodes : nodeset; (* node set *)
	     g_nvec : node Vector.t;	(* node id -> node *)
	     mutable g_nnodes : int;	(* number of nodes *)
	     mutable g_nid : int	(* next node id *)
	   }

  let create () = { g_nmap = M.empty;
		    g_edges = E.empty;
		    g_nodes = NodeSet.empty;
		    g_nvec = V.create 16;
		    g_nnodes = 0;
		    g_nid = 0
		  }

  (* node id -> node *)
  let lookup_node g nid = V.get g.g_nvec nid
    
  (* node id -> data *)
  let get_data g nid =
    let n = lookup_node g nid 
    in n.data

  (* data -> node id *)
  let get_node g d =
    let n = M.find d g.g_nmap
    in n.node_id

  let list_remove e l = List.filter (fun x -> x != e) l

  let query_edge g nid1 nid2 = E.mem (nid1, nid2) g.g_edges

  let edge_from e = fst e
  let edge_to e = snd e

  let mk_edge' g n1 n2 =
    if not (query_edge g n1.node_id n2.node_id) then begin
      g.g_edges <- E.add (n1.node_id, n2.node_id) g.g_edges;
      n1.succs <- n2::n1.succs;
      n2.preds <- n1::n2.preds
    end

  let rm_edge' g n1 n2 =
    if query_edge g n1.node_id n2.node_id then begin
      g.g_edges <- E.remove (n1.node_id, n2.node_id) g.g_edges;
      n1.succs <- list_remove n2 n1.succs;
      n2.preds <- list_remove n2 n1.preds
    end

  let mk_edge g nid1 nid2 : e =
    (* let _ = assert (nid1 <> nid2) in *)
    let n1 = lookup_node g nid1
    and n2 = lookup_node g nid2
    in let _ = mk_edge' g n1 n2
    in (n1.node_id, n2.node_id)

  let rm_edge g (e: e) =
    let (nid1, nid2) = e in
    let n1 = lookup_node g nid1
    and n2 = lookup_node g nid2
    in rm_edge' g n1 n2

  let mk_node' g d : node =
    let n = { node_id = g.g_nid;
	      data = d;
	      preds = [];
	      succs = []
	    }
    in let _ = 
      begin
	g.g_nmap <- M.add d n g.g_nmap;
	g.g_nodes <- NodeSet.add n.node_id g.g_nodes;
	V.set g.g_nvec n.node_id n;
	g.g_nnodes <- g.g_nnodes + 1;
	g.g_nid <- g.g_nid + 1;
      end
    in n

  let mk_node g d : n =
    let n =
      try M.find d g.g_nmap
      with Not_found -> mk_node' g d
    in n.node_id
      
  let rm_node' g n =
    List.iter (fun p -> rm_edge' g p n) n.preds;
    List.iter (fun s -> rm_edge' g n s) n.succs;
    g.g_nnodes <- g.g_nnodes - 1;
    g.g_nmap <- M.remove n.data g.g_nmap;
    g.g_nodes <- NodeSet.remove n.node_id g.g_nodes;
    V.unset g.g_nvec n.node_id

  let rm_node g nid =
    let n = lookup_node g nid
    in rm_node' g n

  let num_nodes g = g.g_nnodes
  let is_empty g = (g.g_nnodes = 0)

  let get_succs g nid =
    let n = lookup_node g nid
    in List.map (fun s -> s.node_id) n.succs

  let get_preds g nid =
    let n = lookup_node g nid
    in List.map (fun p -> p.node_id) n.preds

  let get_edges g = E.elements g.g_edges

  (* g' is the destination, g is the source *)
  let merge_map g' f g =
    M.iter
      (fun d -> fun n -> ignore (mk_node g' (f d)))
      g.g_nmap
    ;
    E.iter
      (fun (nid1, nid2) ->
	 ignore (mk_edge g'
		   (get_node g' (f (get_data g nid1)))
		   (get_node g' (f (get_data g nid2)))))
      g.g_edges
    ;
    g'
    
  let merge dst src = merge_map dst (fun x -> x) src

  let map g f =
    merge_map (create ()) f g

  let clone g = map g (fun x -> x)

  type rgraph = {
    rg_nodemap : int V.t;		(* node id -> index *)
    rg_nodearr : node array;		(* index -> node *)
    rg_adjarry : bool array array	(* index -> index -> bool *)
  }

  (* returns abstract type for reachability *)
  let compute_reachability g : rgraph =
    let n = num_nodes g in 
    let node_list = 
      M.fold
	(fun d -> fun n -> fun l -> n::l)
	g.g_nmap [] 
    in 
    let rg = {
      rg_nodemap = V.create g.g_nid;
      rg_nodearr = Array.of_list node_list;
      rg_adjarry = Array.make_matrix n n false
    } in
    let _ =
      (* compute node_id -> index map *)
      for i = 0 to n-1 do
	V.set rg.rg_nodemap rg.rg_nodearr.(i).node_id i 
      done 
    in
    let _ =
      (* initialize adjacency table *)
      for i = 0 to n-1 do
	for j = 0 to n-1 do
	  rg.rg_adjarry.(i).(j) <- (E.mem 
				      (rg.rg_nodearr.(i).node_id, 
				       rg.rg_nodearr.(j).node_id) 
				      g.g_edges)
	done
      done 
    in
    let changed = ref true in
    let _ =
      while !changed do
	changed := false;
	for k = 0 to n-1 do
	  for i = 0 to n-1 do
	    for j = 0 to n-1 do
             if ((not (rg.rg_adjarry.(i).(j))) &&
		 (rg.rg_adjarry.(i).(k)) &&
		 (rg.rg_adjarry.(k).(j))) then 
	       begin
		 rg.rg_adjarry.(i).(j) <- true;
		 changed := true
	       end
	    done
	  done
	done
      done
    in rg

  let transitive_closure g =
    let rg = compute_reachability g in
    let n = num_nodes g
    in
      for i = 0 to n-1 do
	for j = 0 to n-1 do
	  if rg.rg_adjarry.(i).(j) then
	    mk_edge' g rg.rg_nodearr.(i) rg.rg_nodearr.(j)
	done
      done

  let nodes g = g.g_nodes

  let iter_nodes' g f =
    NodeSet.iter
      (fun n -> f (lookup_node g n))
      (nodes g)

  let iter_nodes g f =
    NodeSet.iter
      (fun n -> f (get_data g n))
      (nodes g)

  type scc = {
    scc_mem: NS.t NM.t;
    scc_rep: int V.t;
  }

  and scc_node = {
    mutable sn_visited : bool;
    mutable sn_dfsnum : int;
    mutable sn_low : int;
  }

  let compute_scc g =
    let scc_mem = ref NM.empty in
    let scc_rep = V.create (num_nodes g) in

    let sccvec = V.create (num_nodes g * 2) in

    let num = ref 0 and stack = ref [] in

    let get_sccnode n =
      let nid = n.node_id in
      if V.mem sccvec nid then 
	V.get sccvec nid
      else
	let entry = 
	  { sn_visited = false;
	    sn_dfsnum = -1;
	    sn_low = -1;
	  }
	in
	V.set sccvec nid entry;
	entry
    in

    let push n = stack := n.node_id :: !stack in
    let is_instack n =
      let id = n.node_id in
      let rec h = function
	  [] -> false
	| x::xs ->
	    if id = x then true
	    else h xs
      in
      h !stack
    in
    
    let rec visit_node n =
      let id = n.node_id in
      (* push it onto the stack *)
      push n;
      let sn = get_sccnode n in
      sn.sn_dfsnum <- !num;
      sn.sn_low <- !num;
      incr num;
      List.iter
	(fun succ -> 
	   let sn' = get_sccnode succ in
	   if sn'.sn_visited then begin
	     if is_instack succ then
	       sn.sn_low <- min sn.sn_low sn'.sn_dfsnum
	   end
	   else begin
	     sn'.sn_visited <- true;
	     visit_node succ;
	     sn.sn_low <- min sn.sn_low sn'.sn_low
	   end
	)
	n.succs;

      if sn.sn_low = sn.sn_dfsnum then begin
	(* found a new scc *)
	let rec f res = function
	    [] -> failwith "expecting to see the current node on the stack"
	  | x :: xs ->
	      let res = NS.add x res in
	      V.set scc_rep x id;	(* make the current node the rep *)
	      if x = id then (stack := xs; res)
	      else f res xs
	in
	let set = f NS.empty !stack in
	scc_mem := NM.add id set !scc_mem
      end
    in
    
    iter_nodes' g
      (fun n ->
	let sn = get_sccnode n in
	if not sn.sn_visited then begin
	  sn.sn_visited <- true;
	  visit_node n
	end
      );

    { scc_mem = !scc_mem;
      scc_rep = scc_rep;
    }

  let iter_scc g scc f =
    NM.iter
      (fun head members -> begin
	 f (get_data g head)
	   (NS.fold 
	      (fun m l ->
		 (get_data g m) :: l
	      )
	      members []
	   )
       end
      )
      scc.scc_mem

  let lookup_rep scc id = V.get scc.scc_rep id

  let lookup_mem scc id = NM.find id scc.scc_mem

  let is_rep scc id = (lookup_rep scc id) = id

  let topsort_from g scc roots = 
    (* do reverse post order traversal over the scc'ified graph *)
    let rpo = ref [] and visited = ref NS.empty in
    let rec visit id =
      assert (is_rep scc id);
      if not (NS.mem id !visited) then begin
	visited := NS.add id !visited;
	let members = lookup_mem scc id in
	
	let succs =
	  NS.fold 
	    (fun m res ->
	       let t = lookup_node g m in
	       (* compute the set of successors *)
	       List.fold_left
		 (fun res s -> 
		    (* enqueue the rep of each successor *)
		    let rep = lookup_rep scc s.node_id in
		    NS.add rep res
		 )
		 res t.succs
	    )
	    members NS.empty
	in

	(* visit successors *)
	NS.iter (fun n -> visit n) succs;

        (* enqueue scc members *)
	NS.iter
	  (fun m ->
	     let n = lookup_node g m in
	     rpo := n.data :: !rpo
	  )
	  members
      end
    in
    List.iter (fun n -> visit (lookup_rep scc n)) roots;
    !rpo

  (* return a list of nodes in g in topological order *)
  let topsort g scc =
    let roots = ref [] in
    iter_nodes' g (fun n -> roots := n.node_id :: !roots);
    topsort_from g scc (List.rev !roots)

end

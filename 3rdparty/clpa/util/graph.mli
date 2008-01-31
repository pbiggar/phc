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

(* graph.mli -- interface for general purpose library *)

module type OrderedType =
  sig
    type t
    val compare: t -> t -> int
  end

module Make : functor (OrderedData: OrderedType) -> sig
  type data = OrderedData.t		(* data type *)
      
  type t				(* type for the graph *)
  type n				(* type for node id *)
  type e				(* type for edges *)
    
  module OrderedNode : sig 
    type t = n
    val compare : t -> t -> int
  end

  module NodeSet : Set.S with type elt = n

  val create : unit -> t		(* create new graph *)

  val get_data : t -> n -> data		(* node id -> data *)
  val get_node : t -> data -> n		(* data -> node id *)

  val num_nodes : t -> int		(* number of nodes *)
  val is_empty : t -> bool		(* is empty? *)
  val query_edge : t -> n -> n -> bool	(* edges exists? *)

  val mk_node : t -> data -> n		(* make new node *)
  val rm_node : t -> n -> unit		(* remove node *)
  val mk_edge : t -> n -> n -> e	(* make new edge *)
  val rm_edge : t -> e -> unit		(* remove edge *)

  val edge_from : e -> n		(* the source of an edge *)
  val edge_to : e -> n		        (* the target of an edge *)

  val get_succs : t -> n -> n list	(* get successors of a node *)
  val get_preds : t -> n -> n list	(* get predecessors of a node *)
  val get_edges : t -> e list		(* list of edges *)

  val merge_map : t -> (data -> data) -> t -> t	(* merge_map dst f src *)
  val merge : t -> t -> t		(* merge dst src *)

  val map : t -> (data -> data) -> t	(* the map operation *)
  val clone : t -> t			(* clone a graph *)

  val transitive_closure : t -> unit	(* compute transitive closure *)

  val nodes : t -> NodeSet.t

  val iter_nodes : t -> (data -> unit) -> unit

  type scc

  val compute_scc : t -> scc

  val iter_scc : t -> scc -> (data -> data list -> unit) -> unit

  val topsort : t -> scc -> data list	(* return nodes in top order *)
  val topsort_from : t -> scc -> n list -> data list

end

(*
 * Various AST source -> source transformations
 *
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

open Spec
open Clpautil
open Flags
open Ast

module A = Array
module H = Hashtbl
module S = String
module IO = Streamio

(* Quantifier and implication arrow expansion.
 * In this pass we perform the following transformations:
 * - all [X] G is replaced with ~ (some [X] ~G)
 * - G1 => G2 is replaced with ~(G1, ~G2) 
 *
 * This pass is done before mode checking so we can remove any
 * useless double negations that are introduced by the unfolding process that
 * might make otherwise valid code ill-moded.
 *
 *)
 
let new_goal sfa body = {
  sfa = sfa;
  body = body;
  menv = empty_menv;
  vars_used = VarSet.empty;
  nonlocals = VarSet.empty
}

let quant_unfold_rule r =
  let rec quant_unfold_goal g =
    {g with body = match g.body with 
    | Ag_conjunction gs -> Ag_conjunction (List.map quant_unfold_goal gs)
    | Ag_disjunction gs -> Ag_disjunction (List.map quant_unfold_goal gs)
    | Ag_negation g -> Ag_negation (quant_unfold_goal g)
    | Ag_implies (g1,g2) -> Ag_negation (new_goal g.sfa (Ag_conjunction 
            [quant_unfold_goal g1;
             new_goal g.sfa (Ag_negation (quant_unfold_goal g2))]))
    | Ag_some (v,g) -> Ag_some (v, quant_unfold_goal g)
    | Ag_all (v,g) -> Ag_negation (new_goal g.sfa 
        (Ag_some (v, new_goal g.sfa (Ag_negation (quant_unfold_goal g)))))
    | Ag_collection (g,c) -> Ag_collection (quant_unfold_goal g, c)
    | _ -> g.body
    } in
  match r.r_body with
  | Ar_query _ -> r
  | Ar_flat goal -> {r with r_body = Ar_flat (quant_unfold_goal goal)}
  | Ar_horn_clause (nameo, head, body) -> 
      {r with r_body = Ar_horn_clause (nameo, head, quant_unfold_goal body)}
  | Ar_assertion (nameo, goal) ->
      {r with r_body = Ar_assertion (nameo, quant_unfold_goal goal)}

(* Double negation elimination *)
let neg_elim_rule r =
  let rec neg_elim_goal g =
    match g.body with 
    | Ag_conjunction gs -> 
        new_goal g.sfa (Ag_conjunction (List.map neg_elim_goal gs))
    | Ag_disjunction gs -> 
        new_goal g.sfa (Ag_disjunction (List.map neg_elim_goal gs))
    | Ag_some (v,g) -> 
        new_goal g.sfa (Ag_some (v, neg_elim_goal g))
    | Ag_collection (g,c) -> 
        new_goal g.sfa (Ag_collection (neg_elim_goal g, c))
    | Ag_negation ng -> 
        (match ng.body with
         | Ag_negation nng -> neg_elim_goal nng
         | _ -> new_goal g.sfa (Ag_negation (neg_elim_goal ng))
        )
    | _ -> g
    in
  match r.r_body with
  | Ar_query _ -> r
  | Ar_flat goal -> {r with r_body = Ar_flat (neg_elim_goal goal)}
  | Ar_horn_clause (nameo, head, body) -> 
      {r with r_body = Ar_horn_clause (nameo, head, neg_elim_goal body)}
  | Ar_assertion (nameo, goal) ->
      {r with r_body = Ar_assertion (nameo, neg_elim_goal goal)}


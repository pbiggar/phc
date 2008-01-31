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

(* Rule-ordering within strata *)

open Spec
open Clpautil
open Flags
open Ast

module IO = Streamio
module A = Array 
module H = Hashtbl 


(* Rule Ordering and Stratification *)

let orders : (string, int * int) H.t = H.create 100
let possible_orders : (string, bool list) H.t = H.create 100

let make_orders () =
  H.iter (fun predda def ->
    let targs = def.pd_args in
    let name = mangle_name predda in
      List.iter (fun o -> H.add orders name o) def.pd_orders;
      if is_pred_vargs targs = None then
	H.add possible_orders name (
          fold_num (fun i alist -> (H.mem order_types targs.(i))::alist)
            [] 0 (A.length targs))
  ) predicates

let get_possible_orders (name,args) =
  let bargs = A.to_list args in
    try 
      let poargs = H.find possible_orders name in
	List.map fst (List.filter snd (List.combine (List.rev bargs) poargs))
    with Not_found -> bargs

let get_orders (name,args) =
  List.fold_left (fun res (a0,a1) ->
    if not (is_val_any args.(a0)) && not (is_val_any args.(a1)) then
      (args.(a0),args.(a1))::res
    else res) [] (H.find_all orders name)

(* (fname,fargs) is an underconstrained magic version of (aname,args):
 * mgc$pred(A,B,_,_), +pred(A,B,C,D). *)
let magic_match (fname,fargs) (aname,aargs) =
  if fname <> (Mlr.magic_pred_name aname) then false
  else match make_vmap aargs fargs with
      Some vm -> (A.map (vmap_val vm) aargs) = aargs
    | None -> false

module OrderedRPred = struct type t = t_rpred let compare = compare end
module RPredG = Graph.Make (OrderedRPred)

let rp_succs graph rp =
  let n = RPredG.get_node graph rp in
  let succs = RPredG.get_succs graph n in
    List.map (RPredG.get_data graph) succs

let rp_preds graph rp =
  let n = RPredG.get_node graph rp in
  let preds = RPredG.get_preds graph n in
    List.map (RPredG.get_data graph) preds

let add_rp_edge graph rp0 rp1 cond =
  let srcn = RPredG.mk_node graph rp0 in
  let tgtn = RPredG.mk_node graph rp1 in
    if cond then ignore (RPredG.mk_edge graph srcn tgtn)

let debug_strat_sccs = register_debug "strat_sccs"
  "Print each stratification SCC"

let debug_strat_basis = register_debug "strat_basis"
  "Print all bases found for SCCs with negations"

let debug_strat_missing_basis = register_debug "strat_missing_basis"
  "Print full set of edges for missing SCC basis"

let debug_strat_reduces = register_debug "strat_reduces"
  "Print base reductions for SCCs with negation"

(* orderings between execution of two t_vals *)
type t_order_kind =
    Ord_same      (* v0/v1 are identical *)
  | Ord_forward   (* v0/v1 are a forward ordering *)
  | Ord_backward  (* v0/v1 are a backward ordering *)
type t_order = t_order_kind * t_val * t_val

let string_of_order_kind = function
    Ord_same -> "Ord_same"
  | Ord_forward -> "Ord_forward"
  | Ord_backward -> "Ord_backward"

(* get the orderings that can be used from args to nargs, given any forward
 * orderings forders. add Ord_forward and Ord_backward if the two values are
 * in both args and nargs, or Ord_same for values that are in both *)
let get_arg_orders name args nargs forders =
  let orders = ref [] in
  (* follow forward or backward edges transitively for values in nargs *)
  let rec search_orders fwd stack av v =
    List.iter (fun (sv,tv) ->
      let (sv,tv) = if fwd then (sv,tv) else (tv,sv) in
        if sv = v then begin
          if exists_array ((=)tv) nargs then
            let kind = if fwd then Ord_forward else Ord_backward in
              prepend orders (kind,av,tv)
          else if not (List.exists ((=)tv) stack) then
            search_orders fwd (tv::stack) av tv
        end) forders in
  List.iter (fun av ->
    search_orders true [] av av;
    search_orders false [] av av;
    if not (is_val_any av) && exists_array ((=)av) nargs then
      prepend orders (Ord_same,av,av)) (get_possible_orders (name,args));
  !orders

(* get the orderings given by asserting equivalence between args and nargs *)
let get_equiv_orders args nargs =
  fold_array2 (fun orders a na ->
    if not (is_val_any a) && not (is_val_any na) then
      (Ord_same,a,na)::orders
    else orders) [] args nargs

(* set priorities for all rule operations, generating
 * an interference graph and stratifying the operations based on
 * a topsort of the result, breaking cycles by looking at ordering info *)
let set_priorities rules = begin

  let has_vmap args0 args1 =
    make_vmap args0 (A.map (rename_val "%s") args1) <> None in

  let is_negcollect rp =
    rp.r_session = None &&
    (match rp.r_kind with Tp_negated | Tp_collect _ -> true | _ -> false) in

  (* get the forward orders in a rule *)
  let get_edge_orders rule =
    List.fold_left (fun orders rp ->
      if rp.r_session = None &&
         (rp.r_kind = Tp_find || rp.r_kind = Tp_add) then
        (get_orders (pred2rep rp.r_pred)) @ orders
      else orders) [] rule in

  (* (n,pred) is a find/negation/collection operation performed somewhere *)
  let r_negfinds : (string,t_rpred) H.t = H.create 10 in

  (* prepass to get finds/negates and orderings in rules *)
  List.iter (List.iter (fun rp ->
    if rp.r_session = None && rp.r_kind <> Tp_add then
      let (name,_) = pred2rep rp.r_pred in
        H.add r_negfinds name rp)) rules;

  (* the interference graph. each Tp_add and Tp_negate/Tp_collect
   * in the program is a node in this graph, with the following edges:
   * find r0 -> add r1 :
   *   resolving r0 can cause r1 to be added later in the same rule.
   *   doesn't include matching magic edges mgc$pred(ARGS) => +pred(ARGS)
   * negate r0 -> add r1 :
   *   resolving r0 can cause r1 to be added later in the same rule.
   * add r0 -> find r1 :
   *   r0 may match r1; adding r0 can invoke the tail for r1
   * add r0 -> negate r1 :
   *   r0 may match r1; adding r0 can change the result of r1
   * cycles in this graph containing negations are bad and must be resolved
   * by refining based on the orderings below *)
  let interferes : RPredG.t = RPredG.create() in

  (* all orderings that can be used for an edge in the interference graph.
   * these are used to refine the interference graph when SCCs are found *)
  let orderings : (t_rpred*t_rpred,t_order list) H.t = H.create 10 in

  let inter_edge rp0 rp1 orders =
    add_rp_edge interferes rp0 rp1 true;
    H.add orderings (rp0,rp1) orders in

  (* fill in the interference graph *)
  let rec get_interferes rforders pnegfinds = function
      [] -> ()
    | rp::rulexs ->
        let (name,args) = pred2rep rp.r_pred in
        if rp.r_session <> None then
          (* adds/finds on external sessions do not interfere with ordering *)
          get_interferes rforders pnegfinds rulexs
        else begin
          let pnegfinds = match rp.r_kind with
            Tp_add ->
              (* negate/find -> add edges *)
              List.iter (fun nrp ->
                let (nname,nargs) = pred2rep nrp.r_pred in
                  (* check for matching magic edges (finds only) *)
                  if not (magic_match (nname,nargs) (name,args)) then
                    let orders = get_arg_orders nname nargs args rforders in
                      inter_edge nrp rp orders) pnegfinds;
              (* add -> negate/find edges *)
              List.iter (fun nrp ->
                let (_,nargs) = pred2rep nrp.r_pred in
                  if has_vmap args nargs then
                    let orders = get_equiv_orders args nargs in
                      inter_edge rp nrp orders) (H.find_all r_negfinds name);
              pnegfinds
          | _ -> rp::pnegfinds in
          get_interferes rforders pnegfinds rulexs
        end in
  List.iter (fun rule ->
    let orders = get_edge_orders rule in
      get_interferes orders [] rule) rules;

  (* accumulated reversed priorities for each negation, reversed order *)
  let priority : (t_rpred,t_priority list) H.t = H.create 10 in
  let push_pri rp pri =
    try let list = H.find priority rp in
      H.replace priority rp (pri::list)
    with Not_found -> H.add priority rp [pri] in

  let print_inter_edge rp srp orders =
    IO.printf "  %s -> %s" (string_of_rpred rp) (string_of_rpred srp);
    List.iter (fun (k,v0,v1) ->
      IO.printf " [%s,%s,%s]" (string_of_order_kind k)
        (full_string_of_val v0) (full_string_of_val v1)) orders;
    IO.printf "\n" in

  let print_edge_list graph scc_mem rplist =
    List.iter (fun rp ->
      IO.printf "Edges for %s:\n" (string_of_rpred rp);
      let succs = List.filter (H.mem scc_mem) (rp_succs graph rp) in
      let preds = List.filter (H.mem scc_mem) (rp_preds graph rp) in
        List.iter (fun srp ->
          print_inter_edge rp srp (H.find orderings (rp,srp))) succs;
        List.iter (fun prp ->
          print_inter_edge prp rp (H.find orderings (prp,rp))) preds)
      rplist in

  (* split SCC apart by looking for a basis within the orderings on the SCC's
   * edges. a basis is an assignment of values to each rpred in the SCC
   * such that:
   * - for each SCC edge, there is an ordering edge between the two values
   *   assigned to the source and target of the edge
   * - at least one such ordering is directional (forward or backward)
   * - all directional orderings go in the same direction (forward or backward)
   * assuming that the ordering edges form an acyclic structure,
   * we can order runtime evaluation based on the depths of the various values
   * to avoid invalidated negate/collect due to the forward/backward edges
   * in the basis *)
  let refine_graph_ordering graph scc =
    let scc_mem : (t_rpred, unit) H.t = H.create 10 in
    List.iter (fun rp -> H.add scc_mem rp ()) scc;
    let scc_bases : (t_rpred, t_val list * t_val list) H.t = H.create 10 in
    (* keep track of whether we couldn't construct a forward or backward basis.
     * remember which rp we initially failed on *)
    let forward_failed = ref None in
    let backward_failed = ref None in
    if debug_strat_reduces() then
      IO.printf "Reducing stratification bases for %s\n"
        (sep_string_of_list " " string_of_rpred scc);
    let check_failed rp fbases bbases =
      if fbases = [] && !forward_failed = None then
        forward_failed := Some rp;
      if bbases = [] && !backward_failed = None then
        backward_failed := Some rp;
      if debug_strat_reduces() then
        IO.printf "Bases for %s: [%s] [%s]\n" (string_of_rpred rp)
          (sep_string_of_list " " full_string_of_val fbases)
          (sep_string_of_list " " full_string_of_val bbases) in
    (* setup initial candidate basis. for each node, those values for which
     * there is an ordering going to each node successor *)
    let init_bases rp =
      let succs = List.filter (H.mem scc_mem) (rp_succs graph rp) in
      let init_check badkind v =
        List.for_all (fun srp ->
          let orders = H.find orderings (rp,srp) in
            List.exists (fun (k,xv,_) ->
              xv = v && k <> badkind) orders) succs in
      let srp = List.hd succs in
      let bases = List.map snd3 (H.find orderings (rp,srp)) in
      (* filter out values already in use for a basis in a larger SCC *)
      let bases = List.filter (fun v ->
        List.for_all (function
            Rp_var(xv,_) -> v <> xv
          | Rp_fix _ -> true) (H.find priority rp)) bases in
      let fbases = List.filter (init_check Ord_backward) bases in
      let bbases = List.filter (init_check Ord_forward) bases in
        check_failed rp fbases bbases;
        H.add scc_bases rp (fbases,bbases) in
    List.iter init_bases scc;
    (* check the consistency of the basis, repeatedly removing candidate vals.
     * any candidate must (a) have edges to candidates in each successor,
     * and (b) have edges from candidates in each predecessor *)
    let rec refine_bases rp =
      let succs = List.filter (H.mem scc_mem) (rp_succs graph rp) in
      let preds = List.filter (H.mem scc_mem) (rp_preds graph rp) in
      let refine_check ofn badkind v =
        List.for_all (fun srp ->
          let sbases = ofn (H.find scc_bases srp) in
          let orders = H.find orderings (rp,srp) in
            List.exists (fun (k,xv,sv) ->
              v = xv && k <> badkind && List.mem sv sbases) orders) succs &&
        List.for_all (fun prp ->
          let pbases = ofn (H.find scc_bases prp) in
          let orders = H.find orderings (prp,rp) in
            List.exists (fun (k,pv,xv) ->
              v = xv && k <> badkind && List.mem pv pbases) orders) preds in
      let (fbases,bbases) = H.find scc_bases rp in
      let nfbases = List.filter (refine_check fst Ord_backward) fbases in
      let nbbases = List.filter (refine_check snd Ord_forward) bbases in
      if fbases <> nfbases || bbases <> nbbases then begin
        check_failed rp nfbases nbbases;
        H.replace scc_bases rp (nfbases,nbbases);
        List.iter refine_bases succs;
        List.iter refine_bases preds
      end in
    List.iter refine_bases scc;
    let initrp = List.hd scc in
    let (finit,binit) = H.find scc_bases initrp in
    let (forward,ofn,initv) =
      if finit = [] && binit = [] then begin
        let ffail = get_some !forward_failed in
        let bfail = get_some !backward_failed in
        IO.printf "Missing basis for ordering [Forward: %s] [Backward: %s]: %s\n"
          (string_of_rpred ffail) (string_of_rpred bfail)
          (sep_string_of_list " " string_of_rpred scc);
        print_edge_list graph scc_mem
          (if debug_strat_missing_basis() then scc else [ffail;bfail]);
        rule_error Sfa_none "Could not construct stratification basis"
      end else if finit = binit then begin
        IO.printf "Stratification SCC has no forward/backward ordering edges: %s\n"
          (sep_string_of_list " " string_of_rpred scc);
        IO.printf "SCC contains the following negation/collections:\n";
        List.iter (fun rp ->
          if is_negcollect rp then
            IO.printf "  %s\n" (string_of_rpred rp)) scc;
        if debug_strat_missing_basis() then
          print_edge_list graph scc_mem scc;
        rule_error Sfa_none "Stratification SCC missing forward/backward ordering edges"
      end else begin
        try let initv = List.find (fun v -> not (List.mem v binit)) finit in
          (true,fst,initv)
        with Not_found ->
          try let initv = List.find (fun v -> not (List.mem v finit)) binit in
            (false,snd,initv)
          with Not_found ->
            assert false
      end in
    if debug_strat_basis() then
      IO.printf "Basis: %s\n" (sep_string_of_list " " string_of_rpred scc);
    let use_base : (t_rpred, t_val) H.t = H.create 10 in
    let use_graph : RPredG.t = RPredG.create() in
    let rec fill_base rp v =
      if H.mem use_base rp then begin
        if H.find use_base rp <> v then begin
          IO.printf "Conflicting SCC: %s\n"
            (sep_string_of_list " " string_of_rpred scc);
          rule_error Sfa_none
            (Printf.sprintf "Conflicting basis for %s: %s %s"
               (string_of_rpred rp) (full_string_of_val v)
               (full_string_of_val (H.find use_base rp)))
        end
      end else begin
        H.add use_base rp v;
        let succs = List.filter (H.mem scc_mem) (rp_succs graph rp) in
          List.iter (fun srp ->
            let sbases = ofn (H.find scc_bases srp) in
            let orders = H.find orderings (rp,srp) in
            let (kind,_,sv) = List.find (fun (kind,rv,sv) ->
              v = rv && List.mem sv sbases) orders in
            add_rp_edge use_graph rp srp (kind = Ord_same);
            if debug_strat_basis() then
              print_inter_edge rp srp [kind,v,sv];
            fill_base srp sv) succs
      end in
    fill_base initrp initv;
    (forward,use_base,use_graph) in

  (* get a topsorted list of sccs for a graph *)
  let get_scc_list graph =
    let interscc = RPredG.compute_scc graph in
    let sccmap : (t_rpred,t_rpred list) H.t = H.create 10 in
      RPredG.iter_scc graph interscc (H.add sccmap);
    let intertpo = RPredG.topsort graph interscc in
      List.fold_right (fun rp scclist ->
        try let scc = H.find sccmap rp in scc::scclist
        with Not_found -> scclist) intertpo [] in

  (* is there a cycle for the given rpreds in an SCC? *)
  let has_cycle graph scc =
    if List.length scc > 1 then true
    else (* self cycle? *)
      let hd = RPredG.get_node graph (List.hd scc) in
        RPredG.query_edge graph hd hd in

  (* stratification of an interference graph.
   * identify all SCCs and stick priorities on them, then if they have a cycle
   * with negations break them up with ordering info if possible and recurse *)
  let rec stratify_graph graph tab =
    let scclist = get_scc_list graph in
    if debug_strat_sccs() then
      IO.printf "%sSCC List:\n" tab;
    ignore (List.fold_left (fun nextpri scc ->
      if debug_strat_sccs() then
        IO.printf "%s%s\n" tab (sep_string_of_list " " string_of_rpred scc);
      List.iter (fun rp -> push_pri rp (Rp_fix nextpri)) scc;
      let neglist = List.filter is_negcollect scc in
        if neglist <> [] && has_cycle graph scc then begin
          let (fwd,nbase,ngraph) = refine_graph_ordering graph scc in
            H.iter (fun rp v -> push_pri rp (Rp_var(v,fwd))) nbase;
            stratify_graph ngraph (tab ^ "  ")
        end;
        nextpri + 1)
      3 scclist) in
  stratify_graph interferes "";

  List.map (List.map
    (fun rp ->
       let pri =
         if is_negcollect rp then
           try List.rev (H.find priority rp)
           with Not_found -> [Rp_fix 2]
         else if rp.r_session <> None then [Rp_fix 1]
         else [Rp_fix 0] in
       { rp with r_priority = pri })) rules

  end (* set_negation_priorities *)
  
let make_succeeds() =
  H.fold (fun predda pdef allsucceeds ->
    if pdef.pd_kind = Pk_regular then
      let (mode,determinism) = List.hd pdef.pd_modes in
      if determinism <> [] then
        let name = mangle_name predda in
        let mnameo = if pdef.pd_magic then Some (Mlr.magic_pred_name name) 
	  else None in
          (mnameo,name,mode,determinism)::allsucceeds
      else allsucceeds
    else allsucceeds
  ) predicates []


let make_mutable rules =
  let muthsh = H.create 10 in
  A.iter (List.iter (List.iter (fun rp ->
    if rp.r_kind = Tp_add then
      match rp.r_session with
          Some sp -> H.add muthsh (fst (pred2rep sp)) ()
        | None -> ()))) rules;
  H.fold (fun name _ list -> name::list) muthsh []

let print_rules rules = 
  List.iter (fun r -> IO.printf "%s\n" (string_of_rule r)) rules
let debug_dump_rules = register_debug "dump_rules"
  "Dump interpreter rules after the compound goal removal pass"
let debug_dump_ast_after_typecheck = register_debug "dump_ast_after_typecheck"
  "Dump abstract syntax trees after type checking"
let debug_dump_ast_after_qexpand = register_debug "dump_ast_after_qexpand"
  "Dump abstract syntax trees after quantifier expansion"

(* Convert a list of rules to an analysis to be executed by the interpreter *)
let make_analysis rules = 
  let rules = Frontend.check_ast rules in
  if debug_dump_ast_after_typecheck () then
    Pp.ppToFile stdout 72 (Ast.ppAST rules);

  let rules = List.map (fun r ->
    Ast_transform.neg_elim_rule (Ast_transform.quant_unfold_rule r)) rules in
  if debug_dump_ast_after_qexpand () then
    Pp.ppToFile stdout 72 (Ast.ppAST rules);

  List.iter Mode_check.mode_check rules;

  check_warnings();

  let strata = Mlr.ast_to_spec rules in
  make_orders ();
  if debug_dump_rules () then 
    A.iteri (fun stratum rules -> 
      IO.printf "\nStratum: %d\n" stratum;
      print_rules rules
    ) strata;
  let strata = A.map set_priorities strata in
  let spec_rules = Specio.dump_rules_str strata in
  let res = 
  {
  Specio.a_name = !analysis_name;
  Specio.a_session = !analysis_session;
  Specio.a_topdown =
    (match !analysis_topdown with
         Some topdown -> topdown
       | None -> false);
  Specio.a_eager = !analysis_eager;
  Specio.a_priority =
    (match !analysis_priority with
         Some prio -> prio
       | None -> 0);
  Specio.a_packages =
    H.fold (fun name () packs -> name::packs) packages [];
  Specio.a_orders = H.copy orders;
  Specio.a_succeeds = make_succeeds();
  Specio.a_mutable = make_mutable strata;
  Specio.a_rules = spec_rules;
  } in
    H.clear orders;
    H.clear possible_orders;
    Mlr.reset_mlr ();
    res

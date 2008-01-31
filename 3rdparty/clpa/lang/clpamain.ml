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

(* Main CLPA program. *)

open Clpautil
open Flags
open Spec
open Specio

module A = Array
module H = Hashtbl
module PQ = Prioqueue
module Q = Queue
module S = String
module IO = Streamio
module V = Vector
module U = Unix
module E = Libevent

let quiet = ref false
let noquiet() = quiet := false

(* Process graph *)

(* if there is at least one onlyanalyze then we only analyze those sessions *)
let onlyanalyze = ref []
let add_onlyanalyze file =
  let chan = open_in file in
    try while true do
      prepend onlyanalyze (input_line chan)
    done with End_of_file -> ()

module OrderedPred = struct 
  type t = int 
  let compare (a : t) (b : t) : int = compare a b
end
module Pg = Graph.Make (OrderedPred)

module StrHashType = struct
  type t = string
  let equal (s1:string) (s2:string) = (s1 = s2)
  let hash = H.hash
end
module PgNodeHash = Hashcons.Make(StrHashType)

let id2node = PgNodeHash.id2a
let node2id = PgNodeHash.a2id

(* ordering given by a topological sort of the process graph.
 * maps each analyzed session to a topo index, where smaller topo indexes
 * should be processed earlier than later ones *)
type ordering_graph = (t_pred_str,int) H.t

let get_ordering_graph sname topdown =
  (* The process graph includes all sessions with a given name to be processed.
   * Each edge (src,dst) means that dst should be ordered before src
   * in the processing order. may contain cycles *)
  let pg : Pg.t = Pg.create() in
  let mk_node name = ignore (Pg.mk_node pg (node2id name)) in
  let mk_edge src dst =
    try
      let src = Pg.get_node pg (node2id src) in
      let dst = Pg.get_node pg (node2id dst) in
        (* if we're going top-down, reverse the process graph edges *)
        ignore (if topdown then Pg.mk_edge pg dst src
                           else Pg.mk_edge pg src dst)
    with Not_found -> () in
  let _ = match !onlyanalyze with
      [] ->
        if sname = "" then mk_node "" else
          List.iter mk_node (bdb_load_session_list sname);
        bdb_load_process_edges mk_edge ;
    | sesslist ->
        (* filter out any malformed or missing sessions *)
        let sesslist = List.filter (fun s ->
          try
            if s = "" then false
            else let pred = pred_name s in
              (ignore (Bdb.find (IO.get_db pred) s); true)
          with Malformed_pred_name _
             | Not_found ->
                 IO.printf "WARNING: Missing/malformed only-analyze: %s\n" s;
                 false) sesslist in
        List.iter mk_node (List.filter (o ((=)sname) pred_name) sesslist);
        (* only load the process edges if we're only-analyzing a large number
         * of functions. loading can take several minutes on a large system
         * like linux. analysis time may be longer when fixpointing *)
        if List.length sesslist > 100 then bdb_load_process_edges mk_edge in
  let scc = Pg.compute_scc pg in
  let tpo = Pg.topsort pg scc in
  (* create a 'base' ordering graph directly from the topo order given *)
  let baseog : (int,int) H.t = H.create (Pg.num_nodes pg * 2) in
  let _ = List.fold_left (fun n name -> H.add baseog name n; n - 1) 0 tpo in
  (* create the real ordering graph. the problem with the graph computed from
   * topo IDs is the traversal used may be post-order, which works fine for
   * a single threaded analysis but is inappropriate for a distributed one -
   * a caller will appear in the ordering directly after its two callees,
   * so if we have three workers then the caller may be analyzed before its
   * callees have finished.
   * solution is to construct a new ordering that adds all leaves at once,
   * removes their dependency edges to create new leaves, and repeats,
   * separating caller-callee pairs by as many unrelated nodes as possible *)
  let og : ordering_graph = H.create (Pg.num_nodes pg * 2) in
  let nexttopo = ref 0 in
  let nextiter = ref [] in
  let fill_nextiter() =
    nextiter := [];
    H.iter (fun name n ->
      let succs = List.map (Pg.get_data pg)
        (Pg.get_succs pg (Pg.get_node pg name)) in
      if not (H.mem og (id2node name)) &&
         List.for_all (fun s -> n <= H.find baseog s || H.mem og (id2node s)) 
           succs then
        prepend nextiter name) baseog in
  fill_nextiter();
  while (!nextiter <> []) do
    List.iter (fun name -> H.add og (id2node name) !nexttopo; incr nexttopo) 
        !nextiter;
    fill_nextiter()
  done;
  assert (H.length baseog = H.length og); 
  PgNodeHash.clean ();
  og
let get_ordering_graph =
  make_track_2 "get_ordering_graph" get_ordering_graph

(* Worklist *)

(* individual items in the worklist, unique identifier of session and analysis
 * name to use, extended info with t_workitem_info. The session name can be
 * the empty string, denoting a dummy (empty) session. *)
type t_workitem = t_pred_str * string
type t_workitem_info = {
  (* unique identifying info *)
  wi_sess: t_pred_str;   (* name of the session to analyze *)
  wi_anly : t_analysis;  (* analysis to use *)

  (* priority of this item according to the ordering graph for wi_analysis *)
  wi_priority : int;

  (* this item is currently pending analysis *)
  mutable wi_pending : bool;

  (* maximum pass# for this item that has started or finished analysis *)
  mutable wi_pass : int;

  (* this item failed analysis previously and should not be reanalyzed *)
  mutable wi_failed : int option;

  (* this item needs to be reanalyzed but we ran out of passes *)
  mutable wi_unanalyzed : bool;
}
type t_workitem_index = int

(* all analyses in use, indexed by analysis name *)
let wk_anly_map : (string,t_analysis) H.t = H.create 10

(* all analyses in use, indexed by the name of the session iterated over *)
let wk_anly_sess : (string,t_analysis) H.t = H.create 10

(* info for each zero-indexed t_workitem identifier *)
let wk_items : t_workitem_info V.t = V.create 10
let wk_item_hash : (t_workitem,t_workitem_index) H.t = H.create 10

(* priority function used for worklist *)
let work_priority n0 n1 =
  let i0 = V.get wk_items n0 in
  let i1 = V.get wk_items n1 in
    if i0.wi_anly.a_priority <> i1.wi_anly.a_priority then
      compare i0.wi_anly.a_priority i1.wi_anly.a_priority
    else if i0.wi_pass <> i1.wi_pass &&
            not i0.wi_anly.a_eager && not i1.wi_anly.a_eager then
      compare i0.wi_pass i1.wi_pass
    else if i0.wi_anly.a_name <> i1.wi_anly.a_name then
      compare i0.wi_anly.a_name i1.wi_anly.a_name
    else if i0.wi_sess <> i1.wi_sess then
      compare i0.wi_priority i1.wi_priority
    else failwith "Duplicate item in worklist"
let work_string n =
  let i = V.get wk_items n in
    i.wi_anly.a_name ^ ":" ^ i.wi_sess

(* priority queue of wk_item indexes that are pending analysis *)
let wk_pending : t_workitem_index PQ.t = PQ.create work_priority work_string

(* all session names which might change over the course of analysis *)
let wk_mutable_sess : (string,unit) H.t = H.create 10

(* items depending on the contents of each queried mutable summary session *)
let wk_depends : (t_pred_str,Lwhash.t) H.t = H.create 10

(* summary sessions with lists of contents we want to do batch merges for.
 * batch merges are done for any session which we've had to throw away stale
 * merges for previously. *)
let wk_merges : (t_pred_str,t_sess_str list) H.t = H.create 10

(* sessions with non-empty merge lists which are pending for batch merges.
 * associated with the time when this session was inserted, to ensure the
 * committed session does not remain stale past a certain time limit *)
let wk_pending_merges : (t_pred_str*float) Q.t = Q.create()

(* maximum pass index for any analyzed item *)
let wk_max_pass : int ref = ref 0

(* total number of sessions analyzed *)
let wk_total_analyzed : int ref = ref 0

(* total number of dependency edges added *)
let wk_total_depends : int ref = ref 0

(* total number of sessions that the maximum # of passes was reached for *)
let wk_total_unanalyzed : int ref = ref 0

(* number of items added in each anly/pass added due to changes in dependent
 * sessions, indexed by (sname,anly,pass#) *)
let wk_triggered : (string*string*int,int ref) H.t = H.create 10

(* maximum passes to perform, default is unlimited *)
let max_passes = ref 0

let add_work_item info =
  (* look for a duplicate item. this can happen sometimes
   * if we are creating new items on the fly based on analysis behavior *)
  let key = (info.wi_sess,info.wi_anly.a_name) in
    try H.find wk_item_hash key
    with Not_found ->
      let n = V.append wk_items info in
        H.replace wk_item_hash key n; n

let add_dependency_edge dep n =
  if !max_passes <> 1 && H.mem wk_mutable_sess (pred_name dep) then begin
    if not (H.mem wk_depends dep) then
      H.add wk_depends dep (Lwhash.create());
    let dhash = H.find wk_depends dep in
      if not (Lwhash.mem dhash n) then
        wk_total_depends := !wk_total_depends + 1;
      Lwhash.add dhash n
  end
let add_dependency_edge =
  make_track_2 "add_dependency_edge" add_dependency_edge

let add_new_work_item anly sess priority =
  let info = {
    wi_sess = sess;
    wi_anly = anly;
    wi_priority = priority;
    wi_pending = true;
    wi_pass = ~-1;
    wi_failed = None;
    wi_unanalyzed = false;
  } in
  let n = add_work_item info in
    if sess <> "" then add_dependency_edge sess n;
    ignore (PQ.insert wk_pending n)

(* Worklist checkpointing *)

let checkpt_freq = ref 0        (* in seconds. 0 == don't checkpoint *)
let checkpt_resume = ref false  (* whether to resume from initial checkpt *)

(* when was the last time we checkpointed? *)
let last_checkpt = ref (U.time())

(* checkpoint if we've passed the time threshold for doing so *)
let checkpt_make busy =
  if !checkpt_freq <> 0 &&
     (U.time() >= !last_checkpt +. (float_of_int !checkpt_freq)) then begin
    IO.bdb_checkpt();
    let (file,ds) = IO.init_dump_file (!IO.bdb_checkpt_dir ^ "/work.chk") in
    IO.dump_string ds "ITEMS";
    IO.dump_int ds (V.size wk_items);
    V.iter (fun i ->
      IO.dump_string ds i.wi_sess;
      IO.dump_string ds i.wi_anly.a_name;
      IO.dump_int ds i.wi_priority;
      let item = (i.wi_sess,i.wi_anly.a_name) in
      let (pending,pass) =
        if List.exists ((=)item) busy then (true,i.wi_pass-1)
        else (i.wi_pending,i.wi_pass) in
      IO.dump_bool ds pending;
      IO.dump_int ds pass;
      IO.dump_option ds IO.dump_int i.wi_failed;
      IO.dump_bool ds i.wi_unanalyzed) wk_items;
    IO.dump_string ds "DEPENDS";
    IO.dump_int ds (H.length wk_depends);
    H.iter (fun dep dhash ->
      IO.dump_string ds dep;
      IO.dump_int ds (Lwhash.length dhash);
      Lwhash.iter (fun n -> IO.dump_int ds n) dhash) wk_depends;
    IO.dump_string ds "MERGES";
    IO.dump_int ds (H.length wk_merges);
    H.iter (fun sname merges ->
      IO.dump_string ds sname;
      IO.dump_list ds IO.dump_string merges) wk_merges;
    IO.dump_string ds "TOTALS";
    IO.dump_int ds !wk_max_pass;
    IO.dump_int ds !wk_total_analyzed;
    IO.dump_int ds !wk_total_depends;
    IO.dump_int ds !wk_total_unanalyzed;
    IO.dump_string ds "TRIGGERED";
    IO.dump_int ds (H.length wk_triggered);
    H.iter (fun (sess,anly,pass) count ->
      IO.dump_string ds sess; IO.dump_string ds anly; IO.dump_int ds pass;
      IO.dump_int ds !count) wk_triggered;
    IO.close_dump_file file;
    IO.printf "*** Checkpointed after %d sessions\n" !wk_total_analyzed;
    last_checkpt := U.time()
  end
let checkpt_make =
  make_track_1 "checkpt_make" checkpt_make

let debug_clp_rules = register_debug "clp_rules"
  "Print the rules in each .clp file"
let debug_recover_depends = register_debug "recover_depends"
  "Print dependencies when recovering from checkpoint"

let checkpt_init pfiles dir =
  (* parse all the analysis .clp files we're using *)
  List.iter (fun pfile ->
    let anly = Ordering.make_analysis (Frontend.parse_clp pfile) in
      Ast.reset_type_checking ();
      (if debug_clp_rules() then
         let rules = (load_rules_str anly.a_rules) in
           A.iter (List.iter (o (IO.printf "%s\n") string_of_rule)) rules);
      if H.mem wk_anly_map anly.a_name then
        failwith ("Duplicate analysis name in worklist: " ^ anly.a_name);
      List.iter (fun sname ->
        H.replace wk_mutable_sess sname ()) anly.a_mutable;
      H.add wk_anly_map anly.a_name anly;
      H.add wk_anly_sess anly.a_session anly) pfiles;
  (* fill in worklist if we're resuming from a checkpoint.
   * otherwise construct initial worklist *)
  if !checkpt_resume then begin
    IO.bdb_checkpt_resume ();
    let (file,ls) = IO.init_load_file (!IO.bdb_checkpt_dir ^ "/work.chk") in
    assert (IO.load_string ls = "ITEMS");
    let itemslen = IO.load_int ls in
    for n = 0 to itemslen-1 do
      let sess = IO.load_string ls in
      let aname = IO.load_string ls in
      let priority = IO.load_int ls in
      let pending = IO.load_bool ls in
      let pass = IO.load_int ls in
      let failed = IO.load_option ls IO.load_int in
      let unanalyzed = IO.load_bool ls in
      let info = {
        wi_sess = sess;
        wi_anly = (try H.find wk_anly_map aname
                   with Not_found ->
                     failwith ("Checkpoint file requires analysis: " ^ aname));
        wi_priority = priority;
        wi_pending = pending;
        wi_pass = pass;
        wi_failed = failed;
        wi_unanalyzed = unanalyzed;
      } in
      let nn = add_work_item info in
        assert (n = nn);
        if pending then ignore (PQ.insert wk_pending n)
    done;
    assert (IO.load_string ls = "DEPENDS");
    let deplen = IO.load_int ls in
    for dj = 1 to deplen do
      let dep = IO.load_string ls in
      let dhash = Lwhash.create() in
      let dhashlen = IO.load_int ls in
        H.add wk_depends dep dhash;
        for hj = 1 to dhashlen do
          Lwhash.add dhash (IO.load_int ls)
        done;
        if debug_recover_depends() then begin
          IO.printf "Dependencies %s:" dep;
          Lwhash.iter (fun n ->
            let info = V.get wk_items n in
              IO.printf " (%s,%s)" info.wi_sess info.wi_anly.a_name) dhash;
          IO.printf "\n"
        end
    done;
    assert (IO.load_string ls = "MERGES");
    let mergelen = IO.load_int ls in
    for mj = 1 to mergelen do
      let sname = IO.load_string ls in
      let merges = IO.load_list ls IO.load_string in
        H.add wk_merges sname merges;
        if merges <> [] then Q.push (sname,U.time()) wk_pending_merges
    done;
    assert (IO.load_string ls = "TOTALS");
    wk_max_pass := IO.load_int ls;
    wk_total_analyzed := IO.load_int ls;
    wk_total_depends := IO.load_int ls;
    wk_total_unanalyzed := IO.load_int ls;
    assert (IO.load_string ls = "TRIGGERED");
    let triglen = IO.load_int ls in
    for tj = 1 to triglen do
      let sess = IO.load_string ls in
      let anly = IO.load_string ls in
      let pass = IO.load_int ls in
      let count = IO.load_int ls in
        H.add wk_triggered (sess,anly,pass) (ref count)
    done;
    IO.close_load_file file;
    IO.bdb_init dir;
    IO.printf "*** Resumed from checkpoint at %d sessions...\n"
      !wk_total_analyzed
  end else begin
    IO.bdb_init dir; (* initialize first so we can access process.db *)
    H.iter (fun _ anly ->
      let og = get_ordering_graph anly.a_session anly.a_topdown in
        H.iter (add_new_work_item anly) og) wk_anly_map
  end
let checkpt_init =
  make_track_2 "checkpt_init" checkpt_init

(* Worklist processing *)

let string_of_workitem (pass,(sname,aname)) =
  let istr = (if aname <> "" then aname ^ ": " else "") ^ sname in
  let pstr = if pass <> 0 then " [#" ^ (string_of_int pass) ^ "]" else "" in
    istr ^ pstr
let print_header (pass,item) =
  if not !quiet then
    IO.printf "Entering %s...\n" (string_of_workitem (pass,item))

let stats_memory_deltas = register_stats "memory_deltas"
  "Print memory deltas after each 100 worklist items"
let stats_time_deltas = register_stats "time_deltas"
  "Print time deltas after each 100 worklist items"
let stats_depends_deltas = register_stats "depends_deltas"
  "Print dependency counts after each 100 worklist items"

let stats_compact_memory_size = register_stats "compact_memory_size"
  "Compact and print heap size after each 10000 worklist items"

(* get the next available work item, raising No_work if none is available *)
exception No_work
let rec next_work_session() = try
  let n = PQ.remove_min wk_pending in
  let i = V.get wk_items n in
  if i.wi_failed <> None then
    next_work_session()  (* don't reanalyze failed sessions *)
  else begin
    wk_max_pass := max !wk_max_pass (i.wi_pass+1);
    i.wi_pass <- i.wi_pass + 1;
    i.wi_pending <- false;
    wk_total_analyzed := !wk_total_analyzed + 1;
    if !wk_total_analyzed mod 100 = 0 then begin
      if stats_memory_deltas() then begin
        let words = float_of_int (Gc.quick_stat()).Gc.heap_words in
          IO.printf "*** Memory deltas after %d sessions [%s heap size]:\n"
            !wk_total_analyzed (alloc_string words);
          print_alloc_deltas();
      end;
      if stats_time_deltas() then begin
        IO.printf "*** Timer deltas after %d sessions:\n"
          !wk_total_analyzed;
        print_time_deltas()
      end;
      if stats_depends_deltas() then begin
        IO.printf "*** Dependencies after %d sessions: %d\n"
          !wk_total_analyzed !wk_total_depends
      end;
      if !wk_total_analyzed mod 10000 = 0 then begin
        if stats_compact_memory_size() then
          let _ = Gc.compact() in
          let words = float_of_int (Gc.quick_stat()).Gc.heap_words in
            IO.printf "*** Compact memory size after %d sessions: %s\n"
              !wk_total_analyzed (alloc_string words)
      end;
    end;
    checkpt_make [(* FIXME *)];
    (i.wi_pass,(i.wi_sess,i.wi_anly.a_name))
  end with PQ.Empty -> raise No_work
let next_work_session =
  make_track_1 "next_work_session" next_work_session

let fail_work_session pass item status =
  let n = H.find wk_item_hash item in
  let i = V.get wk_items n in
    i.wi_failed <- Some pass;
    match status with
        Ar_success -> ()
      | Ar_timeout etime ->
          IO.printf "ERROR: %s: Analysis timed out (%.2f secs in callbacks)\n"
            (string_of_workitem (pass,item)) etime
      | Ar_failure str ->
          IO.printf "ERROR: %s: %s\n"
            (string_of_workitem (pass,item)) str
      | Ar_ext_error str ->
          IO.printf "ERROR: %s: Handling error %s\n"
            (string_of_workitem (pass,item)) str

let debug_sess_reanalyze = register_debug "sess_reanalyze"
  "Print session modifications causing reanalysis"

(* dep changed so add any items that depend on it to the lowest pass in which
 * they have not been analyzed yet *)
let update_work_dependency dep =
  if H.mem wk_depends dep then
   let dhash = H.find wk_depends dep in
   Lwhash.iter (fun n ->
    let i = V.get wk_items n in
    if i.wi_pending then () (* already pending *)
    else if i.wi_pass = !max_passes - 1 then
      i.wi_unanalyzed <- true
    else begin
      wk_max_pass := max !wk_max_pass (i.wi_pass+1);
      if debug_sess_reanalyze() then
        IO.printf "*** Update on %s, analyzing %s...\n"
          dep (string_of_workitem (i.wi_pass+1,(i.wi_sess,i.wi_anly.a_name)));
      let trigkey = (pred_name dep,i.wi_anly.a_name,i.wi_pass+1) in
        if not (H.mem wk_triggered trigkey) then
          H.add wk_triggered trigkey (ref 0);
        incr (H.find wk_triggered trigkey);
        i.wi_pending <- true;
        ignore (PQ.insert wk_pending n)
    end) dhash
let update_work_dependency =
  make_track_1 "update_work_dependency" update_work_dependency

let has_unanalyzed_work() = !wk_total_unanalyzed > 0

let stats_worklist_passes = register_stats "worklist_passes"
  "Print analysis counts for each worklist analysis/pass"
let print_worklist_passes() =
  let print_pass_info name anzy fail deps =
    let deps = List.sort (fun (_,tc0) (_,tc1) -> compare !tc1 !tc0) deps in
      IO.printf "%6s: %9d %9d " name anzy fail;
      List.iter (fun (sn,tc) -> IO.printf " %s:%d" sn !tc) deps;
      IO.printf "\n" in
  let print_all_pass_info anly =
    IO.printf "Analysis %s:\n" anly;
    IO.printf "Pass #:  Analyzed  Failures  SessionAdds ...\n";
    let passinfo =
      A.init (!wk_max_pass+1) (fun _ -> (ref 0,ref 0,ref [])) in
    let totanzy = ref 0 in
    let totfail = ref 0 in
    let totdeps = ref [] in
    V.iter (fun i ->
      if i.wi_anly.a_name = anly then begin
        for ipass = 0 to i.wi_pass do
          incr (fst3 passinfo.(ipass))
        done;
        totanzy := !totanzy + i.wi_pass + 1;
        match i.wi_failed with
            Some pass ->
              incr (snd3 passinfo.(pass));
              incr totfail
          | None -> ()
      end) wk_items;
    H.iter (fun (sname,ianly,pass) cref ->
      if ianly = anly then begin
        prepend (thd3 passinfo.(pass)) (sname,cref);
        try let (_,tcref) = List.find (o ((=)sname) fst) !totdeps in
          tcref := !tcref + !cref
        with Not_found -> prepend totdeps (sname,ref !cref)
      end) wk_triggered;
    A.iteri (fun pass (anzy,fail,deps) ->
      print_pass_info (string_of_int pass) !anzy !fail !deps) passinfo;
    print_pass_info "Total" !totanzy !totfail !totdeps in
  if stats_worklist_passes() then
    H.iter (fun anly _ -> print_all_pass_info anly) wk_anly_map

let has_reanalyzed pass item =
  let n = H.find wk_item_hash item in
  let i = V.get wk_items n in
    (i.wi_pass <> pass) || i.wi_pending

(* stick item back on the worklist, unless a later pass is already on it *)
let reanalyze_item pass item =
  let n = H.find wk_item_hash item in
  let i = V.get wk_items n in
    if i.wi_pass = pass && not i.wi_pending then begin
      i.wi_pass <- i.wi_pass - 1;
      i.wi_pending <- true;
      ignore (PQ.insert wk_pending n)
    end

(* some writes were performed to sess. add a new work item if sess
 * was previously empty and there is some analysis which runs over it *)
let check_new_item sess =
  List.iter (fun anly -> add_new_work_item anly sess 0)
    (H.find_all wk_anly_sess (pred_name sess))

let print_unanalyzed_work() =
  IO.printf "*** ERROR: Worklist limit reached with %d pending sessions\n"
    !wk_total_unanalyzed

(* per-session timeout *)
let timeout = ref 0

let must_load_session name =
  match bdb_load_session (full_string_of_pred name) with
      Some s ->
        (match load_session_str s with
             Some s -> s
           | None -> IO.printf "*** ERROR: Corrupt session %s\n"
                       (full_string_of_pred name); new_ext_session name)
    | None -> new_ext_session name

let setting_max_heap_size = register_setting "max_heap_size"
  "Maximum tolerated size of heap" 1500.

(* check the heap size used. if it is larger than the tolerated maximum,
 * compact it, and if it doesn't shrink enough, cleanly abort the analysis *)
exception Exceed_memory
let check_heap_size() =
  let max_bytes = setting_max_heap_size() *. 1048576. in
  let words = float_of_int (Gc.quick_stat()).Gc.heap_words in
    if words >= max_bytes /. bytes_per_word then begin
      Gc.compact();
      let nwords = float_of_int (Gc.quick_stat()).Gc.heap_words in
        IO.printf "*** WARNING: Memory compacted, %s -> %s\n"
          (alloc_string words) (alloc_string nwords);
        if nwords >= max_bytes *. 0.75 /. bytes_per_word then
          raise Exceed_memory
    end

(* Local processing *)

let setting_minor_heap = register_setting "minor_heap"
  "Size of GC minor heap" 100.

let local_process() =
  (* increase minor heap size greatly to reduce number of collections *)
  let minor_bytes = setting_minor_heap() *. 1048576. in
    Gc.set { (Gc.get()) with Gc.minor_heap_size =
               int_of_float (minor_bytes /. bytes_per_word) };
  let cur_item = ref ("","") in
  (* all sessions with added predicates or which have been cleared
   * by the currently analyzed session *)
  let cur_adds : (t_pred, bool * (t_pred list)) H.t = H.create 10 in
  let flush_adds() =
    H.iter (fun name (cleared,preds) ->
      let sname = full_string_of_pred name in
      let sesso = bdb_load_session sname in
        if sesso = None then check_new_item sname;
        match merge_session_str name sesso cleared preds with
            Some dstr ->
              bdb_dump_session sname dstr;
              update_work_dependency sname
          | None -> ()) cur_adds in
  (* all sess1->sess2 process order dependencies added by the currently
   * analyzed session *)
  let process_deps : (t_pred * t_pred) list ref = ref [] in
  let flush_process_deps () =
    if !process_deps <> [] then
      let deps = List.map (fun (sname,dep) ->
                   (full_string_of_pred sname,full_string_of_pred dep))  
                   !process_deps in
        bdb_add_process_edges (fst !cur_item) deps in
  (* clear callback state for new item *)
  let clear_cb_state newitem =
    cur_item := newitem;
    process_deps := [];
    H.clear cur_adds in
  (* callbacks for each session *)
  let ext_cb = {
    cb_find = (fun slist ->
      let n = H.find wk_item_hash !cur_item in
        List.map (fun sname ->
          add_dependency_edge (full_string_of_pred sname) n;
          must_load_session sname) slist);
    cb_add = (fun sname pred ->
      let (cleared,oldpreds) = try H.find cur_adds sname 
                               with Not_found -> (false, []) in
        H.replace cur_adds sname (cleared, (pred::oldpreds)));
    cb_clear = (fun sname ->
      let preds = try snd (H.find cur_adds sname) with Not_found -> [] in
        H.replace cur_adds sname (true, preds));
    cb_process_dep = (fun sname dep -> prepend process_deps (sname,dep));
  } in
  try while true do
    check_heap_size();
    let (pass,(sname,aname as item)) = next_work_session() in
    let so = if sname = "" then Some (None) else
        match bdb_load_session sname with
	  | Some sstr -> (match load_session_str sstr with
	    | Some s -> Some (Some s)
	    | None -> IO.printf "*** ERROR: Corrupt session %s\n" sname; None
	    )
	  | None -> None in
    match so with 
      | Some s ->
          print_header (pass,item);
          let anly = H.find wk_anly_map aname in
          let rules = load_rules_str anly.a_rules in
            clear_cb_state item;
            let (status,_) = run_analysis !timeout ext_cb
              { as_session = s;
		as_rules = rules;
		as_packages = anly.a_packages;
		as_orders = anly.a_orders;
                as_succeeds = anly.a_succeeds; } in
              if status = Ar_success then begin
                flush_adds();
                flush_process_deps();
                writeout_packages anly.a_packages
              end else fail_work_session pass item status;
              reset_packages anly.a_packages
      | None -> ()
  done with No_work ->
    (if has_unanalyzed_work() then
       print_unanalyzed_work()
     else if not !quiet then
       IO.printf "*** Analysis finished successfully.\n");
    print_worklist_passes()

(* Remote processing *)

type t_worker_job =
    Wj_busy of int (* pass# *) * t_workitem * float (* expected finish time *)
  | Wj_busy_merge of t_pred_str * t_sess_str list * float
  | Wj_idle
  | Wj_dead

type t_worker = {
  mutable tw_sock : IO.t_sock option;  (* socket for worker reads/writes *)
  tw_start : float;     (* absolute time this worker connected *)
  tw_finish : float;    (* absolute time this worker should be killed *)
  mutable tw_last_contact : float; (* when did we last contact this worker? *)
  mutable tw_job : t_worker_job;   (* current job *)

  (* stats *)
  mutable tw_live : float;  (* time this worker was available to run jobs *)
  mutable tw_used : float;  (* time this worker spent running jobs *)
  mutable tw_read : float;  (* bytes read from this worker's socket *)
  mutable tw_write : float; (* bytes written to this worker's socket *)
}
let dump_worker_message w msg = dump_sv2wk_message (get_some w.tw_sock) msg

(* list of all workers, including the deceased *)
let workers = ref []
let worker_count = ref 0 (* spawned workers minus killed workers *)

let debug_no_server_catch = register_debug "no_server_catch"
  "Do not trap exceptions thrown by server"
let stats_worker_usage = register_stats "worker_usage"
  "Print utilization stats for each worker at exit"
let stats_worker_usage_dead = register_stats "worker_usage_dead"
  "Print utilization stats after each worker death"

let setting_keepalive = register_setting "keepalive_time"
  "Frequency of keepalive messages sent to workers" 60.
let setting_response_slack = register_setting "response_slack"
  "Extra time to wait for worker response before dropping it" 60.
let setting_merge_limit = register_setting "merge_limit"
  "Maximum time to wait before batch merging stale sessions" 60.
let setting_lifetime_min = register_setting "lifetime_min"
  "Minimum worker lifetime when spawning workers" 600.
let setting_lifetime_max = register_setting "lifetime_max"
  "Maximum worker lifetime when spawning workers" 1200.
let setting_server_timeout = register_setting "server_timeout"
  "Server timeout if no workers are connected" 3600.

let print_worker_usage_header() =
  IO.printf "Worker#:  LiveTime  UsedTime  %%Util  ReadBytes  WriteBytes\n"
let print_worker_usage name live used read write =
  IO.printf "%7s: %9s %9s %6.2f %10s %11s\n" name
    (time_string live) (time_string used) (used /. live)
    (alloc_string read) (alloc_string write)

(* if non-zero then maximum workers spawned at any time using qsub *)
let worker_max = ref 0
let worker_cmd = ref ""

exception Server_timed_out
exception Server_finished

let remote_process() = begin
  (* block SIGPIPE *)
  Sys.set_signal Sys.sigpipe Sys.Signal_ignore;

  (* require a timeout for remote processing *)
  if !timeout = 0 then timeout := 600;

  (* settings to send to the workers *)
  let sets = {
    ws_timeout = !timeout;
    ws_print_level = !print_level;
    ws_debug_flags = get_all_debug();
    ws_stats_flags = get_all_stats();
    ws_settings = get_all_settings();
  } in

  let curtime = ref (U.time ()) in
  let busy = ref true in      (* are any workers currently processing jobs? *)

  (* signals a worker to die and resets its state so it doesn't get new jobs *)
  let kill_worker w =
    (try dump_worker_message w Ws_die
     with IO.Socket_closed_by_peer _ -> ());
    IO.socket_close (get_some w.tw_sock);
    if !worker_max <> 0 then decr worker_count;
    w.tw_live <- U.time() -. w.tw_start;
    let (read,write) = IO.socket_count_io (get_some w.tw_sock) in
    w.tw_read <- read;
    w.tw_write <- write;
    w.tw_job <- Wj_dead;
    w.tw_sock <- None;
    if stats_worker_usage_dead() then begin
      print_worker_usage "Dead Worker" w.tw_live w.tw_used w.tw_read w.tw_write
    end in

  let kill_worker_unexpected msg w =
    IO.printf "*** ERROR: %s" msg;
    (match w.tw_job with
         Wj_busy(pass,curitem,_) ->
           IO.printf ": %s\n" (string_of_workitem (pass,curitem))
       | Wj_busy_merge(sname,_,_) ->
           IO.printf ": merging %s\n" sname
       | _ -> IO.printf "\n");
    kill_worker w in
  let worker_disconnected =
    kill_worker_unexpected "Worker disconnected unexpectedly" in
  let worker_timed_out =
    kill_worker_unexpected "Worker timed out" in

  (* all job/session pairs which are actively being written *)
  let active_write_sessions : (t_pred_str,t_workitem_index option list) H.t = H.create 10 in
  let add_write_session name n =
    let list = try H.find active_write_sessions name with Not_found -> [] in
      H.replace active_write_sessions name (n::list) in
  let check_write_session name n =
    try List.mem n (H.find active_write_sessions name) with Not_found -> false in
  let clear_write_session name =
    H.remove active_write_sessions name in

  let push_merge_item name sess =
    let omerges = try H.find wk_merges name with Not_found -> [] in
      H.replace wk_merges name (sess::omerges);
      if omerges = [] then Q.push (name,!curtime) wk_pending_merges in
  let do_pending_merge_item() =
    if Q.is_empty wk_pending_merges then false
    else let (_,n) = Q.peek wk_pending_merges in
      (n +. setting_merge_limit() <= !curtime) || PQ.is_empty wk_pending in

  (* when committing worker results we need to make sure no stale results are
   * used to overwrite good previous results, causing potential non-termination
   * or incorrect results. a worker's results can be stale in two ways:
   * - it clears out a summary session, but one or more sessions it depends on
   *   have changed since it originally started analysis. just check if we have
   *   tried reanalyzing it since (either the pending flag or pass# in the
   *   worklist will have changed), as the work item will be readded whenever
   *   its dependencies change
   * - it merges new predicates into a session that has changed since it
   *   requested the original session for doing the merge. use the active write
   *   sessions to detect this. when the session is requested an entry is added
   *   and when the worker finishes the entry is checked; if it is still there
   *   it is removed and the merge committed, if not then it is stale.
   * if a worker result contains any stale portion then the entire
   * result is discarded *)

  (* check for timeouts on busy workers, and assign new jobs to idle ones *)
  let worker_idle = make_track_1 "worker_idle" (fun w -> try
    match w.tw_job with
        Wj_busy (_,_,finish_time)
      | Wj_busy_merge (_,_,finish_time) ->
          busy := true;
          (* drop a worker if it is late in answering *)
          if (!curtime >= finish_time +. setting_response_slack()) then
            worker_timed_out w
      | Wj_idle ->
          if w.tw_finish <> 0. && !curtime > w.tw_finish then begin
            (* worker's time expired, kill it and we'll spawn another later *)
            busy := true;
            kill_worker w
          end else if do_pending_merge_item() then begin
            let (sname,_) = Q.pop wk_pending_merges in
            let sesso = bdb_load_session sname in
            let merges = H.find wk_merges sname in
            let finish_time = !curtime +. (float_of_int !timeout) in
              busy := true;
              H.replace wk_merges sname [];
              add_write_session sname None;
              w.tw_job <- Wj_busy_merge (sname,merges,finish_time);
              dump_worker_message w (Ws_merge (sesso,merges));
              w.tw_last_contact <- !curtime
          end else begin
            try let (pass,(snameo,aname as item)) = next_work_session() in
              busy := true;
              let sesso = match snameo with
		| "" -> None
		| sname -> (match bdb_load_session sname with
                    | Some sess -> Some sess
                    | None -> raise No_work
		  ) in
              let finish_time = !curtime +. (float_of_int !timeout) in
                w.tw_job <- Wj_busy (pass,item,finish_time);
                dump_worker_message w (Ws_job (sesso,aname));
                w.tw_last_contact <- !curtime
            with No_work -> 
              if !curtime > w.tw_last_contact +. setting_keepalive() then begin
                dump_worker_message w Ws_keepalive;
                w.tw_last_contact <- !curtime
              end
          end
      | Wj_dead -> ()
    with IO.Socket_closed_by_peer _ -> worker_disconnected w) in

  (* handle a message from a worker *)
  let worker_read = make_track_3 "worker_read" (fun w _ s -> try
    match (w.tw_job,load_wk2sv_message s) with
        (Wj_busy (_,curitem,_), Ws_need_sessions (isread,nlist)) ->
          let n = H.find wk_item_hash curitem in
          let slist = List.map (fun name ->
            if isread then
              (add_dependency_edge name n; (name,bdb_load_session name))
            else if H.mem wk_merges name then
              (name,None)  (* result will be put into merge queue *)
            else begin
              add_write_session name (Some n);
              let sesso = bdb_load_session name in
                if sesso = None then check_new_item name;
                (name,sesso)
            end) nlist in
          dump_worker_message w (Ws_sessions slist)
      | (Wj_busy (pass,curitem,_), Ws_finished fin) ->
          let n = H.find wk_item_hash curitem in
          let stale = ref [] in
          List.iter (fun (cleared,sname,sess) ->
            if (if cleared then not (has_reanalyzed pass curitem)
                else check_write_session sname (Some n)) then begin
              clear_write_session sname;
              bdb_dump_session sname sess;
              update_work_dependency sname
            end else begin
              if cleared then prepend stale sname
              else push_merge_item sname sess
            end) fin.wf_adds;
          if fin.wf_pdeps <> [] then
            bdb_add_process_edges (fst curitem) fin.wf_pdeps;
          print_header (pass,curitem);
          IO.print_output fin.wf_output;
          if fin.wf_status <> Ar_success then
            fail_work_session pass curitem fin.wf_status;
          if !stale <> [] then begin
            IO.printf "*** WARNING: %s: Discarded partially stale result:"
              (string_of_workitem (pass,curitem));
            List.iter (IO.printf " %s") !stale;
            IO.printf "\n";
            reanalyze_item pass curitem
          end;
          w.tw_job <- Wj_idle;
          w.tw_used <- w.tw_used +. fin.wf_time
      | (Wj_busy_merge (sname,merges,_), Ws_finished_merge sesso) ->
          IO.printf "Merging %d batch for %s...\n" (List.length merges) sname;
          (match sesso with
               Some sess ->
                 if check_write_session sname None then begin
                   clear_write_session sname;
                   bdb_dump_session sname sess;
                   update_work_dependency sname
                 end else begin
                   IO.printf "*** WARNING: %s: Discarded stale merge\n" sname;
                   List.iter (push_merge_item sname) merges
                 end
             | None -> ());
          w.tw_job <- Wj_idle
      | _ -> ()
    with IO.Socket_closed_by_peer _ -> worker_disconnected w) in

  (* accept a new worker that connected to our listening socket *)
  let accept_worker = make_track_1 "accept_worker" (fun sock ->
    let mintime = setting_lifetime_min() in
    let maxtime = setting_lifetime_max() in
    let finish =
      if !worker_max = 0 then 0.
      else U.time() +. mintime +. (Random.float (maxtime -. mintime)) in
    let curtime = U.time() in
    let w = {
      tw_sock = Some sock;
      tw_start = curtime;
      tw_finish = finish;
      tw_last_contact = curtime;
      tw_live = 0.;
      tw_used = 0.;
      tw_read = 0.;
      tw_write = 0.;
      tw_job = Wj_idle;
    } in
    prepend workers w;
    IO.socket_set_data_cb sock (worker_read w);
    IO.socket_set_peerclosed_cb sock (fun _ -> worker_disconnected w);
    try 
      dump_sv2wk_message sock (Ws_settings sets);
      H.iter (fun _ anly -> dump_sv2wk_message sock (Ws_analysis anly))
        wk_anly_map
    with IO.Socket_closed_by_peer _ -> worker_disconnected w) in

  (* open up a socket and listen on it for new workers *)
  let (_,accept_addr,accept_port) = IO.server_socket accept_worker in
  let accept_str = U.string_of_inet_addr accept_addr in

  (* spawn a new worker via worker_cmd *)
  let spawn_worker = make_track_1 "spawn_worker" (fun () ->
    incr worker_count;
    let cmd = Printf.sprintf "%s %s %d" !worker_cmd accept_str accept_port in
      ignore (Sys.command cmd)) in

  IO.printf "Listening on %s:%d...\n" accept_str accept_port;

  let sv_timeout = ref (U.time() +. setting_server_timeout()) in
  let sv_tick_event = E.create () in
  let rec sv_tick_cb _ _ = 
    curtime := U.time ();
    if !curtime >= !sv_timeout then raise Server_timed_out;
    check_heap_size();
    if List.exists (fun w -> w.tw_job <> Wj_dead) !workers then begin
      busy := false;
      sv_timeout := !curtime +. setting_server_timeout();
      List.iter worker_idle !workers
    end;
    if not !busy then raise Server_finished;
    if !worker_count < !worker_max then spawn_worker ();
    E.add sv_tick_event (Some 0.5)
    in
  E.set sv_tick_event U.stdout [E.TIMEOUT] false sv_tick_cb;

  let sv_done = ref false in 
  while not !sv_done do
    E.add sv_tick_event (Some 0.5);
    try E.dispatch () with 
        Signal.Signal "SIGINT" -> 
          IO.printf "*** ERROR: SIGINT received, exiting...\n"; 
          sv_done := true
      | Server_timed_out ->
          IO.printf "*** ERROR: Timeout waiting for new workers, exiting...\n";
          sv_done := true
      | Exceed_memory ->
          IO.printf "*** ERROR: Server memory exceeded, exiting...\n";
          sv_done := true
      | Server_finished ->
          (if has_unanalyzed_work() then print_unanalyzed_work()
          else IO.printf "*** Analysis finished successfully.\n");
          sv_done := true
      | exn ->
          if debug_no_server_catch() then raise exn
          else match exn with
              U.Unix_error(err,fn,arg) ->
                IO.printf "*** ERROR: Unix error: %s, %s, %s"
                  (U.error_message err) fn arg
            | exn ->
                IO.printf "*** ERROR: Unknown exception: %s\n"
                  (Printexc.to_string exn)
  done;

  (* Kill any remaining workers *)
  List.iter (fun w -> if w.tw_job <> Wj_dead then kill_worker w) !workers;

  print_worklist_passes();
  if stats_worker_usage() then begin
    print_worker_usage_header();
    let (_,totlive,totused,totread,totwrite) =
      List.fold_right (fun w (i,totlive,totused,totread,totwrite) ->
        print_worker_usage (string_of_int i)
          w.tw_live w.tw_used w.tw_read w.tw_write;
        (i+1, totlive +. w.tw_live, totused +. w.tw_used,
         totread +. w.tw_read, totwrite +. w.tw_write))
      !workers (0,0.,0.,0.,0.) in
    print_worker_usage "Total" totlive totused totread totwrite
  end

end (* remote_process *)

(* Main *)

let usage = "Usage: clpa [options] program.clp*"

let main () = 
  let programs : string list ref = ref [] in
  let add_program = prepend programs in
  let useworkers : bool ref = ref false in
  let logic_dir : string ref = ref "." in
  let options = Arg.align [
    ("-I", Arg.String (prepend Frontend.source_dirs),
     "dir  Extra directory to be searched for source code");
    ("--logic", Arg.Set_string logic_dir,
     "dir  Set directory with logic/process info");
    ("--quiet", Arg.Set quiet,
     "  Only print query results");
    ("--no-quiet", Arg.Unit noquiet,
     "  Suppress --quiet");
    ("--debug", Arg.String set_debug,
     "flag  Set debug flag");
    ("--list-debug", Arg.Unit list_all_debug,
     "  List all possible debug flags");
    ("--stats", Arg.String set_stats,
     "flag  Set statistics flag");
    ("--list-stats", Arg.Unit list_all_stats,
     "  List all possible statistics flags");
    ("--setting", Arg.String set_setting,
     "name=n  Set new value for internal setting");
    ("--list-settings", Arg.Unit list_all_settings,
     "  List all possible internal settings");
    ("--print-level", Arg.Set_int print_level,
     "n  Maximum depth of terms to print (default unlimited)");
    ("--only-analyze", Arg.String add_onlyanalyze,
     "file.txt  File with list of sessions to run on");
    ("--no-fixpoint", Arg.Unit (fun () -> max_passes := 1),
     "  Do not enter the same session multiple times");
    ("--timeout", Arg.Set_int timeout,
     "secs  Maximum analysis time per session");
    ("--use-workers", Arg.Set useworkers,
     "  Use remote workers to resolve worklist");
    ("--spawn-workers", Arg.Set_int worker_max,
     "num  Maintain num workers by spawning with qsub");
    ("--spawn-cmd", Arg.Set_string worker_cmd,
     "str  Command to use for spawning a new worker");
    ("--checkpoint", Arg.Set_int checkpt_freq,
     "n  Checkpoint analysis state after every n seconds");
    ("--checkpoint-resume", Arg.Set checkpt_resume,
     " Resume analysis from checkpointed analysis state");
    ("--checkpoint-dir", Arg.Set_string IO.bdb_checkpt_dir,
     "dir  Directory to store/resume checkpoints from");
  ] in
  if A.length Sys.argv = 1 then (Arg.usage options usage; exit 1);
  Arg.parse options (add_program) usage;
  (if not !quiet then
     let args = List.map (fun s -> if S.contains s ' ' then "\"" ^ s ^ "\""
                          else s) (A.to_list Sys.argv) in
       IO.printf "%s: %s\n" (Sys.getcwd()) (S.concat " " args));
  if !worker_max > 0 && !worker_cmd = "" then
    (Printf.eprintf "--spawn-workers and --spawn-cmd must be used together\n";
     exit 1);
  if !programs <> [] then begin
    checkpt_init !programs !logic_dir;  (* calls bdb_init() *)
    if V.size wk_items = 0 then
      IO.printf "WARNING: No sessions to analyze, exiting...\n"
    else
      (try if !useworkers then remote_process() else local_process()
       with exn -> IO.bdb_finish(); raise exn);
    IO.bdb_finish()
  end
let main = make_track_1 "main" main

let _ = main()
let _ = if not !quiet then (print_allocs(); print_times())

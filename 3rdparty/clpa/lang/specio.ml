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

module A = Array
module B = Buffer
module H = Hashtbl
module IO = Streamio
module V = Vector
open Spec
open Clpautil
open Flags

type t_pred_str = string
type t_sess_str = string
type t_rules_str = string

type t_analysis = {
  a_name : string;
  a_session : string;
  a_topdown : bool;
  a_eager : bool;
  a_priority : int;
  a_packages : string list;
  a_rules : t_rules_str;
  a_orders : (string,t_pred_order) H.t;
  a_succeeds : t_pred_succeeds list;
  a_mutable : string list;
}

(* Value I/O *)

let load_pred ls =
  let name = load_val ls in
  let args = IO.load_array ls load_val in
    rep2pred (val2str name,args)

let dump_pred ds p =
  let (name,args) = pred2rep p in
    dump_val ds (str2val name);
    IO.dump_array ds dump_val args

let load_priority ls =
  match IO.load_byte ls with
      0x30 -> Rp_fix (IO.load_int ls)
    | 0x31 -> let fwd = IO.load_bool ls in Rp_var (load_val ls,fwd)
    | _ -> IO.loaderror "load_priority"

let dump_priority ds = function
    Rp_fix n -> IO.dump_byte ds 0x30; IO.dump_int ds n
  | Rp_var (v,fwd) -> IO.dump_byte ds 0x31; IO.dump_bool ds fwd; dump_val ds v

let dump_sfa ds = function
  | Sfa_package p -> IO.dump_byte ds 0x70; IO.dump_string ds p
  | Sfa_file (file,line) -> IO.dump_byte ds 0x71; IO.dump_string ds file;
      IO.dump_int ds line
  | Sfa_none -> IO.dump_byte ds 0x72

let load_sfa ls =
  match IO.load_byte ls with
    | 0x70 -> Sfa_package (IO.load_string ls)
    | 0x71 ->
	let file = IO.load_string ls in
	let line = IO.load_int ls in
	  Sfa_file (file, line)
    | 0x72 -> Sfa_none
    | _ -> IO.loaderror "load_sfa"

let load_rpred ls =
  let pri = IO.load_list ls load_priority in
  let stratum = IO.load_int ls in
  let kind = match IO.load_byte ls with
      0x20 -> Tp_find
    | 0x21 -> Tp_add
    | 0x22 -> Tp_negated
    | 0x23 -> Tp_collect (load_pred ls)
    | _ -> IO.loaderror "load_rpred" in
  let spo = IO.load_option ls load_pred in
  let pred = load_pred ls in
  let sfa = load_sfa ls
  in {
    r_priority = pri;
    r_stratum = stratum;
    r_kind = kind;
    r_session = spo;
    r_pred = pred;
    r_sfa = sfa;
  }

let dump_rpred ds rp =
  IO.dump_list ds dump_priority rp.r_priority;
  IO.dump_int ds rp.r_stratum;
  (match rp.r_kind with
       Tp_find          -> IO.dump_byte ds 0x20
     | Tp_add           -> IO.dump_byte ds 0x21
     | Tp_negated       -> IO.dump_byte ds 0x22
     | Tp_collect cp    -> IO.dump_byte ds 0x23; dump_pred ds cp);
  IO.dump_option ds dump_pred rp.r_session;
  dump_pred ds rp.r_pred;
  dump_sfa ds rp.r_sfa

let load_rule ls = IO.load_list ls load_rpred
let dump_rule ds = IO.dump_list ds dump_rpred

let load_analysis ls =
  let name = IO.load_string ls in
  let session = IO.load_string ls in
  let topdown = IO.load_bool ls in
  let eager = IO.load_bool ls in
  let priority = IO.load_int ls in
  let packages = IO.load_list ls IO.load_string in
  let rules = IO.load_string ls in
  let orders = H.create 10 in
    while IO.load_bool ls do
      let pname = IO.load_string ls in
      let src = IO.load_int ls in
      let tgt = IO.load_int ls in
        H.add orders pname (src,tgt)
    done;
  let succeeds = ref [] in
    while IO.load_bool ls do
      let mname = IO.load_option ls IO.load_string in
      let name = IO.load_string ls in
      let mode_len = IO.load_int ls in
      let mode = A.init mode_len (fun _ -> IO.load_bool ls) in
      let skinds = ref [] in
        while IO.load_bool ls do
          prepend skinds (match IO.load_byte ls with
                              0x30 -> Sk_zero
                            | 0x31 -> Sk_once
                            | 0x32 -> Sk_many
                            | _ -> IO.loaderror "load_skind")
        done;
        prepend succeeds (mname,name,mode,!skinds)
    done;
  let mutlist = IO.load_list ls IO.load_string in
  let res = {
    a_name = name;
    a_session = session;
    a_topdown = topdown;
    a_eager = eager;
    a_priority = priority;
    a_packages = packages;
    a_rules = rules;
    a_orders = orders;
    a_succeeds = !succeeds;
    a_mutable = mutlist;
  } in res

let dump_analysis ds anly =
  IO.dump_string ds anly.a_name;
  IO.dump_string ds anly.a_session;
  IO.dump_bool ds anly.a_topdown;
  IO.dump_bool ds anly.a_eager;
  IO.dump_int ds anly.a_priority;
  IO.dump_list ds IO.dump_string anly.a_packages;
  IO.dump_string ds anly.a_rules;
  H.iter (fun pname (src,tgt) ->
    IO.dump_bool ds true;
    IO.dump_string ds pname;
    IO.dump_int ds src;
    IO.dump_int ds tgt) anly.a_orders;
  IO.dump_bool ds false;
  List.iter (fun (mname,name,mode,skinds) ->
    IO.dump_bool ds true;
    IO.dump_option ds IO.dump_string mname;
    IO.dump_string ds name;
    IO.dump_int ds (A.length mode);
    A.iter (IO.dump_bool ds) mode;
    List.iter (fun skind ->
      IO.dump_bool ds true;
      IO.dump_byte ds (match skind with
                           Sk_zero -> 0x30
                         | Sk_once -> 0x31
                         | Sk_many -> 0x32)) skinds;
    IO.dump_bool ds false) anly.a_succeeds;
  IO.dump_bool ds false;
  IO.dump_list ds IO.dump_string anly.a_mutable

let load_rules_str str =
  let ls = IO.init_load_string str in
    IO.load_array ls (fun ls -> IO.load_list ls load_rule)
let dump_rules_str rules =
  let (ds,tds) = IO.init_dump_string() in
    IO.dump_array ds (fun ds l -> IO.dump_list ds dump_rule l) rules;
    B.contents tds

let load_session_str str = try
  let ls = IO.init_load_string (IO.uncompress str) in
  let s = new_ext_session (load_pred ls) in
    while (IO.load_bool ls) do add_ext_logic s (load_pred ls) done; Some s
  with exn when not (Signal.is_signal exn) ->
    IO.printf "ERROR: load_session_str() exn: %s\n" (Printexc.to_string exn);
    None
let load_session_str =
  make_track_1 "load_session_str" load_session_str

let setting_session_limit = register_setting "session_limit"
  "Max session size allowed" 0.

let session_limit_exceeded buf =
  let limit = setting_session_limit() *. 1048576. in
    limit <> 0. && limit < float_of_int (B.length buf)

let dump_session_str s =
  let name = get_ext_session_name s in
  let (ds,tds) = IO.init_dump_string() in try
    dump_pred ds name;
    iter_ext_logic s (fun p ->
      IO.dump_bool ds true;
      dump_pred ds p;
      if session_limit_exceeded tds then
        failwith "Maximum session size exceeded");
    IO.dump_bool ds false;
    IO.compress 5 (B.contents tds)
  with Failure msg ->
    IO.printf "ERROR: Session %s failed to dump: %s\n" 
      (string_of_pred !print_level name) msg;
    B.clear tds;
    dump_pred ds name;
    IO.dump_bool ds false;
    IO.compress 5 (B.contents tds)
let dump_session_str =
  make_track_1 "dump_session_str" dump_session_str

module OrderedPredType = struct
  type t = t_pred
  let compare = pred_compare
end
module PredSet = Set.Make(OrderedPredType)

let print_pred_set =
  PredSet.iter (fun p -> IO.printf "  %s\n" (full_string_of_pred p))

let debug_sess_changes = register_debug "sess_changes"
  "Print changes to summary sessions as they occur"

let merge_session_str sname sesso cleared preds =
  let spreds = ref PredSet.empty in
    (try match sesso with
         Some sess ->
           let ls = IO.init_load_string (IO.uncompress sess) in
           let nsname = load_pred ls in
             assert (sname = nsname);
             while (IO.load_bool ls) do
               let p = load_pred ls in
                 spreds := PredSet.add p !spreds
             done
       | None -> ();
     with exn when not (Signal.is_signal exn) ->
       IO.printf "ERROR: merge_session_str() exn: %s\n"
         (Printexc.to_string exn));
  let newpreds =
    List.fold_left (fun s e -> PredSet.add e s) PredSet.empty preds in
  let updpreds =
    if cleared then newpreds else (PredSet.union newpreds !spreds) in
  if not (PredSet.equal !spreds updpreds) then begin
    if debug_sess_changes() then begin
      IO.printf "Session %s changed:\n" (full_string_of_pred sname);
      IO.printf "Old contents:\n"; print_pred_set !spreds;
      IO.printf "New contents:\n"; print_pred_set updpreds
    end;
    let (ds,tds) = IO.init_dump_string() in try
      dump_pred ds sname;
      PredSet.iter (fun p ->
        IO.dump_bool ds true;
        dump_pred ds p;
        if session_limit_exceeded tds then
          failwith "Maximum session size exceeded") updpreds;
      IO.dump_bool ds false;
      Some (IO.compress 5 (B.contents tds))
    with Failure msg ->
      IO.printf "ERROR: Session %s failed to merge: %s\n" 
        (string_of_pred !print_level sname) msg;
      None
  end else None
let merge_session_str =
  make_track_4 "merge_session_str" merge_session_str

(* BDB integration *)

(* parse out the pred name from the string_of_pred representation *)
exception Malformed_pred_name of string
let pred_name name =
  try String.sub name 0 (String.index name '(')
  with Not_found -> raise (Malformed_pred_name name)

let bdb_trap dbname default fn =
  try fn()
  with exn when not (Signal.is_signal exn) ->
    IO.printf "ERROR: Access to database %s.db failed: %s\n"
      dbname (Printexc.to_string exn);
    default

let bdb_load_session name = bdb_trap (pred_name name) None (fun () ->
  let db = IO.get_db (pred_name name) in
    try Some (Bdb.find db name)
    with Not_found -> None)
let bdb_load_session =
  make_track_1 "bdb_load_session" bdb_load_session

let bdb_dump_session name data = bdb_trap (pred_name name) () (fun () ->
  let db = IO.get_db (pred_name name) in
    Bdb.replace db name data)
let bdb_dump_session =
  make_track_2 "bdb_dump_session" bdb_dump_session

let bdb_load_session_list keyname = bdb_trap keyname [] (fun () ->
  if IO.exists_db keyname then
    (let list = ref [] in
       Bdb.iter (fun name _ -> prepend list name) (IO.get_db keyname); !list)
  else [])

(* Processing order edge management *)

let bdb_load_process_edges f = bdb_trap "process" () (fun () ->
  if IO.exists_db "process" then
    Bdb.iter (fun _ data ->
      let ls = IO.init_load_string data in
        while (IO.load_bool ls) do
          let ps = IO.load_string ls in
          let pt = IO.load_string ls in
            f ps pt
        done) (IO.get_db "process"))
let bdb_load_process_edges =
  make_track_1 "bdb_load_process_edges" bdb_load_process_edges

let bdb_add_process_edges key newedges = bdb_trap "process" () (fun () ->
  let edges = H.create 10 in
  try let data = Bdb.find (IO.get_db "process") key in
    let ls = IO.init_load_string data in
      while (IO.load_bool ls) do
        let ps = IO.load_string ls in
        let pt = IO.load_string ls in
          H.replace edges (ps,pt) ()
      done 
  with Not_found -> () ;
  let old_edge_count = H.length edges in
  List.iter (fun edge -> H.replace edges edge () ) newedges ;
  let new_edge_count = H.length edges in
  if old_edge_count < new_edge_count then begin
    let (ds,tds) = IO.init_dump_string() in
      H.iter (fun (ps,pt) _ ->
        IO.dump_bool ds true;
        IO.dump_string ds ps;
        IO.dump_string ds pt) edges;
      IO.dump_bool ds false;
    let data = B.contents tds in
      Bdb.add (IO.get_db "process") key data
  end)

(* Worker message passing *)

let load_status ls =
  match IO.load_byte ls with
      0x50 -> Ar_success
    | 0x51 -> Ar_timeout (IO.load_float ls)
    | 0x52 -> Ar_failure (IO.load_string ls)
    | 0x53 -> Ar_ext_error (IO.load_string ls)
    | _ -> IO.loaderror "load_status"

let dump_status ds = function
    Ar_success       -> IO.dump_byte ds 0x50
  | Ar_timeout etime -> IO.dump_byte ds 0x51; IO.dump_float ds etime
  | Ar_failure str   -> IO.dump_byte ds 0x52; IO.dump_string ds str
  | Ar_ext_error str -> IO.dump_byte ds 0x53; IO.dump_string ds str

type t_wk_finished = {
  wf_status : Spec.anly_status;
  wf_time : float;
  wf_output : IO.t_output_set;
  wf_adds : (bool * t_pred_str * t_sess_str) list;
  wf_pdeps : (t_pred_str * t_pred_str) list;
}

let load_wk_finished ls =
  let status = load_status ls in
  let time = IO.load_float ls in
  let output = IO.load_output ls in
  let adds = IO.load_list ls
    (fun ls ->
       let cleared = IO.load_bool ls in
       let sname = IO.load_string ls in
       let sess = IO.load_string ls in
         (cleared,sname,sess)) in
  let pdeps = IO.load_list ls
    (fun ls ->
       let src = IO.load_string ls in
       let dst = IO.load_string ls in
         (src,dst)) in
  let res = {
    wf_status = status;
    wf_time = time;
    wf_output = output;
    wf_adds = adds;
    wf_pdeps = pdeps;
  } in res

let dump_wk_finished ds fin =
  dump_status ds fin.wf_status;
  IO.dump_float ds fin.wf_time;
  IO.dump_output ds fin.wf_output;
  IO.dump_list ds (fun ds (cleared,sname,sess) ->
    IO.dump_bool ds cleared;
    IO.dump_string ds sname;
    IO.dump_string ds sess) fin.wf_adds;
  IO.dump_list ds (fun ds (src,dst) ->
    IO.dump_string ds src;
    IO.dump_string ds dst) fin.wf_pdeps

type t_wk2sv_message =
    Ws_need_sessions of bool * t_pred_str list
  | Ws_finished of t_wk_finished
  | Ws_finished_merge of t_sess_str option

let string_of_wk2sv_message = function
    Ws_need_sessions _  -> "Ws_need_sessions"
  | Ws_finished _       -> "Ws_finished"
  | Ws_finished_merge _ -> "Ws_finished_merge"

let load_wk2sv_message str =
  let loader ls = match IO.load_string ls with
      "NSESS" ->
        let isread = IO.load_bool ls in
        let nlist = IO.load_list ls IO.load_string in
          Ws_need_sessions (isread,nlist)
    | "FIN" -> Ws_finished (load_wk_finished ls)
    | "MFIN" -> Ws_finished_merge (IO.load_option ls IO.load_string)
    | _ -> IO.loaderror "load_wk2sv_message" in
  loader (IO.init_load_string str)
let load_wk2sv_message =
  make_track_1 "load_wk2sv_message" load_wk2sv_message

let dump_wk2sv_message sock msg =
  let dumper ds = function
      Ws_need_sessions (isread,nlist) ->
        IO.dump_string ds "NSESS";
        IO.dump_bool ds isread;
        IO.dump_list ds IO.dump_string nlist
    | Ws_finished fin ->
        IO.dump_string ds "FIN";
        dump_wk_finished ds fin
    | Ws_finished_merge sesso ->
        IO.dump_string ds "MFIN";
        IO.dump_option ds IO.dump_string sesso in
  let (ds,tds) = IO.init_dump_string() in
    dumper ds msg;
    IO.socket_dump sock (B.contents tds)
let dump_wk2sv_message =
  make_track_2 "dump_wk2sv_message" dump_wk2sv_message

type t_wk_settings = {
  ws_timeout : int;
  ws_print_level : int;
  ws_debug_flags : string list;
  ws_stats_flags : string list;
  ws_settings : (string * float) list;
}

type t_sv2wk_message =
    Ws_die
  | Ws_keepalive
  | Ws_settings of t_wk_settings
  | Ws_analysis of t_analysis
  | Ws_job of t_sess_str option * string
  | Ws_merge of t_sess_str option * t_sess_str list
  | Ws_sessions of (t_pred_str * t_sess_str option) list

let string_of_sv2wk_message = function
    Ws_die         -> "Ws_die"
  | Ws_keepalive   -> "Ws_keepalive"
  | Ws_settings _  -> "Ws_settings"
  | Ws_analysis _  -> "Ws_analysis"
  | Ws_job _       -> "Ws_job"
  | Ws_merge _     -> "Ws_merge"
  | Ws_sessions _  -> "Ws_sessions"

let load_sv2wk_message str =
  let loader ls = match IO.load_string ls with
      "DIE" -> Ws_die
    | "KALV" -> Ws_keepalive
    | "SETS" ->
        let timeout = IO.load_int ls in
        let printlevel = IO.load_int ls in
        let debugs = IO.load_list ls IO.load_string in
        let stats = IO.load_list ls IO.load_string in
        let settings = IO.load_list ls (fun ls ->
                         let n = IO.load_string ls in
                         let v = IO.load_float ls in (n,v)) in
          Ws_settings {
            ws_timeout = timeout;
            ws_print_level = printlevel;
            ws_debug_flags = debugs;
            ws_stats_flags = stats;
            ws_settings = settings;
          }
    | "ANLY" -> Ws_analysis (load_analysis ls)
    | "JOB" ->
        let sess = IO.load_option ls IO.load_string in
        let anlyname = IO.load_string ls in
          Ws_job (sess,anlyname)
    | "MERGE" ->
        let sess = IO.load_option ls IO.load_string in
        let merges = IO.load_list ls IO.load_string in
          Ws_merge (sess,merges)
    | "SESS" ->
        Ws_sessions (IO.load_list ls
          (fun ls ->
             let sname = IO.load_string ls in
             let sess = IO.load_option ls IO.load_string in
               (sname,sess)))
    | _ -> IO.loaderror "load_sv2wk_message" in
  loader (IO.init_load_string str)
let load_sv2wk_message =
  make_track_1 "load_sv2wk_message" load_sv2wk_message

let dump_sv2wk_message sock msg =
  let dumper ds = function
      Ws_die ->
        IO.dump_string ds "DIE"
    | Ws_keepalive ->
        IO.dump_string ds "KALV"
    | Ws_settings sets ->
        IO.dump_string ds "SETS";
        IO.dump_int ds sets.ws_timeout;
        IO.dump_int ds sets.ws_print_level;
        IO.dump_list ds IO.dump_string sets.ws_debug_flags;
        IO.dump_list ds IO.dump_string sets.ws_stats_flags;
        IO.dump_list ds (fun ds (n,v) ->
                           IO.dump_string ds n;
                           IO.dump_float ds v) sets.ws_settings
    | Ws_analysis anly ->
        IO.dump_string ds "ANLY";
        dump_analysis ds anly
    | Ws_job (sess,anlyname) ->
        IO.dump_string ds "JOB";
        IO.dump_option ds IO.dump_string sess;
        IO.dump_string ds anlyname
    | Ws_merge (sess,merges) ->
        IO.dump_string ds "MERGE";
        IO.dump_option ds IO.dump_string sess;
        IO.dump_list ds IO.dump_string merges
    | Ws_sessions slist ->
        IO.dump_string ds "SESS";
        IO.dump_list ds
          (fun ds (sname,sess) ->
             IO.dump_string ds sname;
             IO.dump_option ds IO.dump_string sess) slist in
  let (ds,tds) = IO.init_dump_string() in
    dumper ds msg;
    IO.socket_dump sock (B.contents tds)
let dump_sv2wk_message =
  make_track_2 "dump_sv2wk_message" dump_sv2wk_message

let debug_server_fetch = register_debug "server_fetch"
  "Print names of sessions fetched by each clpa-worker"
let setting_worker_idle_timeout = register_setting "worker_idle_timeout"
  "Timeout for workers without jobs" 180.
let setting_worker_minor_heap = register_setting "worker_minor_heap"
  "Size of GC minor heap for workers" 100.
let setting_worker_hard_memory = register_setting "worker_hard_memory"
  "Hard memory limit for workers" 0.
let setting_worker_hard_cpu = register_setting "worker_hard_cpu"
  "Hard CPU limit for workers" 0.

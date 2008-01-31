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

(* Main program for distributed CLPA workers. *)

open Clpautil
open Flags
open Spec
open Specio

module A = Array
module E = Libevent
module H = Hashtbl
module S = String
module U = Unix
module IO = Streamio

let mtrack = new_track_info "main"

(* close down sock and exit *)
let exit_with sock msg =
  print_endline msg;
  print_endline "Exiting...";
  IO.socket_close sock;
  end_track mtrack;
  print_allocs(); print_times();
  exit 0

(* timeout waiting for server response *)
exception Timed_out 

let worker_timeout_event = E.create () 
let worker_timeout_cb _ _ = raise Timed_out
let _ = E.set worker_timeout_event U.stdout [E.TIMEOUT] false worker_timeout_cb
let worker_timeout_reset () =
  E.del worker_timeout_event;
  E.add worker_timeout_event (Some (setting_worker_idle_timeout()))

(* schedule a regular timer event. we need to do this since if control is
 * never returned to OCaml then we'll never receive signals like SIGINT.
 * this is a hacky but reliable way to get signal delivery. *)
let tick_event = E.create ()
let tick_event_cb _ _ = E.add tick_event (Some 1.)
let _ = 
  E.set tick_event U.stdout [E.TIMEOUT] false tick_event_cb;
  E.add tick_event (Some 1.)

(* fetch the specified session from the server listening on sock *)
exception Got_sessions of (t_pred * t_sess_str option) list
let get_server_sessions sock rd namelist : (t_pred * t_sess_str option) list =
  let bt = Unix.gettimeofday() in
  let data_cb _ msg = match load_sv2wk_message msg with
      Ws_sessions sstrlist ->
        let xlist = List.map (fun name -> (name,None)) namelist in
        if (List.length namelist <> List.length sstrlist) then begin
          IO.printf "ERROR: Corrupt server sessions: Wrong length\n";
          raise (Got_sessions xlist)
        end;
        let slist = List.map2 (fun name (xname,sstro) ->
          if (full_string_of_pred name) <> xname then begin
            IO.printf "ERROR: Corrupt server sessions: Mismatch [%s] [%s]\n"
              (full_string_of_pred name) xname;
            raise (Got_sessions xlist)
          end;
          (name,sstro)) namelist sstrlist in
        raise (Got_sessions slist)
    | Ws_die ->
        exit_with sock "Closed by server"
    | msg ->
        Printf.printf "Unexpected server session response: %s\n"
          (string_of_sv2wk_message msg) in
  let snamelist = List.map full_string_of_pred namelist in
  dump_wk2sv_message sock (Ws_need_sessions (rd,snamelist));
  worker_timeout_reset ();
  IO.socket_set_data_cb sock data_cb;
  try E.dispatch (); exit_with sock "Event dispatch failed"
  with Got_sessions slist ->
         let et = Unix.gettimeofday() in
         if debug_server_fetch() then begin
           IO.printf "Fetched server sessions [%.2f seconds]:" (et -. bt);
           List.iter (o (IO.printf " %s") full_string_of_pred) namelist;
           IO.printf "\n";
         end; slist
     | Timed_out -> exit_with sock "Timeout waiting for sessions"

let perform_server_find sock namelist =
  let sstrlist = get_server_sessions sock true namelist in
    List.map (fun (name,sstro) ->
      match sstro with
          Some sstr ->
            (match load_session_str sstr with
                 Some es -> es
               | None -> new_ext_session name)
        | None -> new_ext_session name) sstrlist
let perform_server_find =
  make_track_2 "perform_server_find" perform_server_find

let perform_server_merge sock addlist =
  let namelist = List.map (fun (_,name,_) -> name) addlist in
  let sstrlist = get_server_sessions sock false namelist in
    List.fold_left (fun res (cleared,name,preds) ->
      assert (List.exists (o ((=)name) fst) sstrlist);
      let (_,sstro) = List.find (o ((=)name) fst) sstrlist in
        match merge_session_str name sstro cleared preds with
            Some nsess -> (cleared,full_string_of_pred name,nsess)::res
          | None -> res) [] addlist
let perform_server_merge =
  make_track_2 "perform_server_merge" perform_server_merge

(* Main *)

(* keep track of all adds performed on each session *)
let server_adds : (t_pred,bool * (t_pred list)) H.t = H.create 10
let add_session_pred sname pred =
  let (cleared,oldpreds) =
    try H.find server_adds sname with Not_found -> (false,[]) in
  H.replace server_adds sname (cleared, (pred::oldpreds))
let clear_session sname =
  let preds = try snd (H.find server_adds sname) with Not_found -> [] in
  H.replace server_adds sname (true, preds)

(* keep track of all generated process dependency edges *)
let process_deps : (t_pred * t_pred) list ref = ref []
let add_process_dep sname dep = prepend process_deps (sname,dep)

(* apply all session additions, communicating with server as necessary *)
let get_adds sock =
  let addlist = H.fold (fun sname (cleared,preds) res ->
                          (cleared,sname,preds)::res) server_adds [] in
    if addlist <> [] then
      perform_server_merge sock addlist
    else []

(* get the names on each added process dependency edge *)
let get_process_deps () =
  List.map (fun (sname,dep) ->
    (full_string_of_pred sname,full_string_of_pred dep)) !process_deps

let clear_cb_state() =
  H.clear server_adds; process_deps := []

let per_timeout = ref 0
let anlymap = H.create 10

(* not really an exception, more a way to break out of a dispatch loop *)
exception Server_job of t_sess_str option * string
exception Server_merge of t_sess_str option * t_sess_str list

let process_jobs sock =
  let cbs = {
    cb_find = perform_server_find sock;
    cb_add = add_session_pred;
    cb_clear = clear_session;
    cb_process_dep = add_process_dep;
  } in

  let run_one_analysis = make_track_2 "run_one_analysis" (fun sstro aname ->
    let anly =
      try H.find anlymap aname
      with Not_found -> exit_with sock "Server did not send analysis" in
    let rules = load_rules_str anly.a_rules in
      clear_cb_state();
      IO.set_collect_output();
      let so = match sstro with 
	| None -> Some (None)
	| Some sstr -> (match load_session_str sstr with
	    | Some s -> Some (Some s)
	    | None -> None
	  ) in
      let (status,time) =
        match so with
            Some s ->
              run_analysis !per_timeout cbs
                { as_session = s;
		  as_rules = rules;
		  as_packages = anly.a_packages;
		  as_orders = anly.a_orders;
                  as_succeeds = anly.a_succeeds }
          | None ->
              (Ar_ext_error "Corrupt job session", 0.) in
      let (adds,pdeps) =
        if status = Ar_success then
          (writeout_packages anly.a_packages;
           (get_adds sock,get_process_deps()))
        else ([],[]) in
      (* collect output after doing adds to get any errors/debug messages *)
      let output = IO.get_collect_output() in
      let fin = {
        wf_status = status;
        wf_time = time;
        wf_output = output;
        wf_adds = adds;
        wf_pdeps = pdeps;
      } in
      begin
        try dump_wk2sv_message sock (Ws_finished fin)
        with Failure msg ->
          (* dump_wk2sv_message has a tendency to fail since there is a
           * 16Mb size limit on OCaml strings on 32-bit architectures. 
           * This is broken and just plain embarrassing in a modern
           * language.
           * If we fail, then send a smaller "failure" result back instead 
           *)
          IO.set_collect_output();
          let output = IO.get_collect_output() in
          let nfin = {
            wf_status = (Ar_ext_error ("Result serialization failed: " ^ msg));
            wf_time = time;
            wf_output = output;
            wf_adds = [];
            wf_pdeps = [];
          } in dump_wk2sv_message sock (Ws_finished nfin)
      end;
      reset_packages anly.a_packages;
      worker_timeout_reset ()) in

  let run_one_merge = make_track_2 "run_one_merge" (fun sstro slist ->
    let name = ref None in
    let preds = ref [] in
      List.iter (fun sstr ->
        match load_session_str sstr with
            Some sess ->
              name := Some (get_ext_session_name sess);
              iter_ext_logic sess (prepend preds)
          | None -> ()) slist;
    if !name = None then
      exit_with sock "Server sent empty/corrupt merge session list";
    let res = merge_session_str (get_some !name) sstro false !preds in
      dump_wk2sv_message sock (Ws_finished_merge res);
      worker_timeout_reset ()) in

  Sys.set_signal Sys.sigpipe Sys.Signal_ignore;
  IO.socket_set_peerclosed_cb sock
    (fun _ -> exit_with sock "Server closed connection");

  let data_cb _ msg = match load_sv2wk_message msg with
      Ws_die ->
        exit_with sock "Closed by server"
    | Ws_keepalive ->
        worker_timeout_reset ()
    | Ws_sessions _ ->
        (* we can receive these if we timed out on a previous session while
         * waiting for a session response from the server. it's harmless,
         * so we ignore it. The server will work it out eventually. *)
        ()
    | Ws_settings sets ->
        set_all_debug sets.ws_debug_flags;
        set_all_stats sets.ws_stats_flags;
        set_all_settings sets.ws_settings;
        print_level := sets.ws_print_level;
        per_timeout := sets.ws_timeout;
        let minor_bytes = setting_worker_minor_heap() *. 1048576. in
        Gc.set { (Gc.get()) with Gc.minor_heap_size =
                   int_of_float (minor_bytes /. bytes_per_word) };
        let memory_limit = setting_worker_hard_memory() *. 1048576. in
        if memory_limit <> 0. then
          Rlimit.rlimit_set Rlimit.RLIMIT_AS
            (Int64.of_float memory_limit, Int64.of_float memory_limit);
        let cpu_limit = setting_worker_hard_cpu() in
        if cpu_limit <> 0. then
          Rlimit.rlimit_set Rlimit.RLIMIT_CPU
            (Int64.of_float cpu_limit, Int64.of_float cpu_limit);
        worker_timeout_reset ()
    | Ws_analysis anly ->
        H.replace anlymap anly.a_name anly
    | Ws_job (sess,analysis) -> 
        (* break out of the dispatch loop when we receive a job *)
        raise (Server_job (sess,analysis))
    | Ws_merge (sess,merges) ->
        raise (Server_merge (sess,merges)) in

   while true do
     IO.socket_set_data_cb sock data_cb;
     worker_timeout_reset ();
     try
       try E.dispatch ()
       with Server_job (sstro,aname) -> run_one_analysis sstro aname
          | Server_merge (sstro,slist) -> run_one_merge sstro slist
          | Timed_out -> exit_with sock "Timeout waiting for job"
     with U.Unix_error(err,fn,arg) ->
            exit_with sock
              (Printf.sprintf "ERROR: Unix Error: %s, %s, %s"
                 (U.error_message err) fn arg)
        | exn ->
            exit_with sock
              (Printf.sprintf "ERROR: Unknown exception: %s"
                 (Printexc.to_string exn))
   done

let usage = "Usage: clpa-worker addr port"

let main () =
  start_track mtrack;
  if A.length Sys.argv != 3 then (IO.printf "%s\n" usage; exit 2);
  let addr = U.inet_addr_of_string Sys.argv.(1) in
  let port = int_of_string Sys.argv.(2) in
  let sock = IO.client_socket addr port in
    (* does not return ... *)
    process_jobs sock
let _ = main()

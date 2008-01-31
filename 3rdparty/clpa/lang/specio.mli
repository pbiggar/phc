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

(* serialization and message passing for session processing *)

(* string representation of preds. using 'string_of_pred(pred)' instead of
 * 'pred' for ID'ing preds drops the dependence on spec hash-cons structures,
 * with the caveat that the pred args can no longer be dissected or changed *)
type t_pred_str = string

(* get the actual pred name, 'foo(X,Y)' -> 'foo' *)
exception Malformed_pred_name of string
val pred_name : t_pred_str -> string

(* serialized rule list and session representations *)
type t_rules_str = string
type t_sess_str = string

(* a single analysis given by a .clp, with serialized rules *)
type t_analysis = {
  a_name : string;           (* unique name for this analysis *)
  a_session : string;        (* names of the sessions to analyze *)
  a_topdown : bool;          (* whether to analyze top down *)
  a_eager : bool;            (* whether to analyze eagerly *)
  a_priority : int;          (* priority to use wrt other analyses *)
  a_packages : string list;  (* packages to use *)
  a_rules : t_rules_str;     (* serialized rules to run on *)
  a_orders : (string,Spec.t_pred_order) Hashtbl.t;  (* orderings to use *)
  a_succeeds : Spec.t_pred_succeeds list;  (* pred succeeds to check *)
  a_mutable : string list;   (* names of sessions which may be written *)
}

(* Value I/O *)

val load_rules_str : t_rules_str -> Spec.t_rule list array
val dump_rules_str : Spec.t_rule list array -> t_rules_str

val load_session_str : t_sess_str -> Spec.t_ext_session option
val dump_session_str : Spec.t_ext_session -> t_sess_str

(* merge a list of preds into an existing session, flag indicates
 * cleared vs. non-cleared, return indicates
 * new contents or None if unchanged/failure *)
val merge_session_str :
  Spec.t_pred -> t_sess_str option -> bool -> Spec.t_pred list ->
  t_sess_str option

(* BDB sessions *)

val bdb_load_session : t_pred_str -> t_sess_str option
val bdb_dump_session : t_pred_str -> t_sess_str -> unit

(* get names for all known sessions with the given name key *)
val bdb_load_session_list : string -> t_pred_str list

(* BDB process edges *)

(* process edges (name,pred) mean that pred should be processed before name *)
val bdb_load_process_edges : (t_pred_str -> t_pred_str -> unit) -> unit
val bdb_add_process_edges :
  string (* unique key *) -> (t_pred_str * t_pred_str) list -> unit

(* Worker message passing *)

(* information sent from worker to server after finishing a job *)
type t_wk_finished = {
  (* result of analysis job *)
  wf_status : Spec.anly_status;

  (* time taken actually applying rules *)
  wf_time : float;

  (* plaintext stdout/file/bdb output *)
  wf_output : Streamio.t_output_set;

  (* names/contents of sessions whose contents changed.
   * flag indicates whether this was the result of a session clear *)
  wf_adds : (bool * t_pred_str * t_sess_str) list;

  (* new process dependency edges added *)
  wf_pdeps : (t_pred_str * t_pred_str) list;
}

(* messages sent from workers to the server *)
type t_wk2sv_message =
    (* read or write performed on a set of sessions, as indicated by flag
     * (true == read), need their contents *)
    Ws_need_sessions of bool * t_pred_str list
    (* finished analysis job *)
  | Ws_finished of t_wk_finished
    (* finished batch merge *)
  | Ws_finished_merge of t_sess_str option

val load_wk2sv_message : string -> t_wk2sv_message 
val dump_wk2sv_message : Streamio.t_sock -> t_wk2sv_message -> unit

(* global settings for a worker *)
type t_wk_settings = {
  ws_timeout : int;  (* per-job analysis timeout *)
  ws_print_level : int; 
  ws_debug_flags : string list;
  ws_stats_flags : string list;
  ws_settings : (string * float) list;
}

(* messages sent from the server to workers *)
type t_sv2wk_message =
    (* quit immediately *)
    Ws_die
    (* server is waiting for more work, refresh worker timeout *)
  | Ws_keepalive
    (* settings to use for all future jobs *)
  | Ws_settings of t_wk_settings
    (* contents of a particular analysis that may be used on jobs *)
  | Ws_analysis of t_analysis
    (* jobs to run, contents of session to analyze and analysis name *)
  | Ws_job of t_sess_str option * string
    (* batch merge to run, existing contents of session and one or more
     * partial sessions to merge in *)
  | Ws_merge of t_sess_str option * t_sess_str list
    (* response to Ws_need_sessions, contents of the requested sessions
     * in the order in which they were requested. None indicates empty *)
  | Ws_sessions of (t_pred_str * t_sess_str option) list

val load_sv2wk_message : string -> t_sv2wk_message
val dump_sv2wk_message : Streamio.t_sock -> t_sv2wk_message -> unit

(* Convert messages to a human readable representation *)
val string_of_sv2wk_message : t_sv2wk_message -> string
val string_of_wk2sv_message : t_wk2sv_message -> string

(* flags and settings for exclusive use for workers.
 * define this here cuz they'll be set by the command line starting the server
 * and then transmitted to each worker *)
val debug_server_fetch : unit -> bool
val setting_worker_idle_timeout : unit -> float
val setting_worker_minor_heap : unit -> float
val setting_worker_hard_memory : unit -> float
val setting_worker_hard_cpu : unit -> float

(** Server-worker communication protocol:
 *
 * 1. Worker connects to server
 * 2. Server sends Ws_settings
 * 3. Server sends Ws_analysis, goto 3 or 4 or 8
 * 4. Server sends Ws_job, goto 5 or 7
 * 5. Worker sends Ws_need_sessions
 * 6. Server sends Ws_sessions, goto 5 or 7
 * 7. Worker sends Ws_finished, goto 4 or 8
 * 8. Server sends Ws_merge, goto 9
 * 9. Worker sends Ws_finished_merge, goto 4 or 8
 *
 * Server may send Ws_keepalive or Ws_die at any time.
 **)

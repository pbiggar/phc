(***********************************************************************)
(* The OcamlEvent library                                              *)
(*                                                                     *)
(* Copyright 2002, 2003 Maas-Maarten Zeeman. All rights reserved. See  *) 
(* LICENCE for details.                                                *)
(***********************************************************************)

(* $Id: libevent.ml,v 1.1 2004/12/18 21:58:25 maas Exp $ *)
type event

type event_flags =
    TIMEOUT 
  | READ 
  | WRITE
  | SIGNAL 

let int_of_event_type = function
    TIMEOUT -> 0x01
  | READ -> 0x02
  | WRITE -> 0x04
  | SIGNAL -> 0x08

type event_callback = Unix.file_descr -> event_flags -> unit

(* Use an internal hashtable to store the ocaml callbacks with the
   event *)
let table = Hashtbl.create 0

(* Called by the c-stub, locate, and call the ocaml callback *)
let event_cb event_id fd etype =
  if Hashtbl.mem table event_id then
    (Hashtbl.find table event_id) fd etype
  else failwith "Unknown event callback"

(* Create an event *)
external ccreate : unit -> event = "oc_create_event"
let events = ref []
let create () = let e = ccreate () in events := e::!events ; e

(* Return the id of an event *)
external event_id : event -> int = "oc_event_id"

(* Return the signal associated with the event *)
external signal : event -> int = "oc_event_fd"

(* Return the fd associated with the event *)
external fd : event -> Unix.file_descr = "oc_event_fd"

(* Set an event (not exported) *)
external cset_fd : event -> Unix.file_descr -> int -> unit = "oc_event_set"
external cset_int : event -> int -> int -> unit = "oc_event_set"

(* Event set *)
let set event fd etype (persist:bool) (cb : event_callback) =
  let rec int_of_event_type_list flag = function
      h::t -> int_of_event_type_list (flag lor (int_of_event_type h)) t
    | [] -> flag
  in
  let flag = 
    let f = int_of_event_type_list 0 etype in
    if persist then
      f lor 0x10
    else
      f
  in
  Hashtbl.replace table (event_id event) cb;
  cset_fd event fd flag

let set_signal event signal persist (cb : event_callback) =
  let signal_flag = (int_of_event_type SIGNAL) in
  let flag = if persist then
    signal_flag lor 0x10
  else
    signal_flag
  in
  Hashtbl.replace table (event_id event) cb;
  cset_int event signal flag

let unset event =
  Hashtbl.remove table (event_id event)

(* Add an event *)
external add : event -> float option -> unit = "oc_event_add"

(* Del an event  *)
external del : event -> unit = "oc_event_del"

(* *)
(* Not fully implemented yet *)
external pending : event -> event_flags list -> bool = "oc_event_pending"

(* Process events *)
external dispatch : unit -> unit = "oc_event_dispatch"

type loop_flags = ONCE | NONBLOCK
external loop : loop_flags -> unit = "oc_event_loop"

(* Initialize the event library *)
external init : unit -> unit = "oc_event_init"
let _ = 
  Callback.register "event_cb" event_cb;
  init ()




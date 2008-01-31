(***********************************************************************)
(* The Ocaml Libevent library                                          *)
(*                                                                     *)
(* Copyright 2002, 2003, 2004 Maas-Maarten Zeeman. All rights          *) 
(* reserved. See LICENCE for details.                                  *)       (***********************************************************************)

(* $Id: libevent.mli,v 1.2 2004/12/21 19:15:14 maas Exp $ *)

(** The Ocaml Event library provides an interface to the event API.

    The event API provides a mechanism to execute a function when a
    specific event on a file descriptor occurs or after a given time
    has passed.

    This library is a wrapper of the libevent API made by Nils
    Provos. For more information about this library see:
    http://www.monkey.org/~provos/libevent. 

    Currently, libevent supports kqueue(2), select(2), poll(2) and
    epoll(4). Support for /dev/poll is planned.

    @author Maas-Maarten Zeeman 
*)

(** The type of events *)
type event

(** The possible event types *)
type event_flags = 
    TIMEOUT (** A timeout occurred. *)
  | READ    (** A read is possible. *)
  | WRITE   (** A write operation is possible. *)
  | SIGNAL  (** A signal occurred. *)

type event_callback = Unix.file_descr -> event_flags -> unit
(** The type of event callbacks *)

(** {5 Basic Libevent Operations} *)

val create : unit -> event
(** Create a new empty event *)

val fd : event -> Unix.file_descr
(** [fd event] returns the file descriptor associated with the event *)

val signal : event -> int
(** [signal event] returns the signal associated with the event *)

val set : event -> 
  Unix.file_descr -> event_flags list -> bool -> event_callback -> unit
(** [set event fd type persist callback] initializes the event. The
    flag [persist] makes an event persitent until {!Libevent.del} is
    called. *)

val set_signal : event ->
  int -> bool -> event_callback -> unit
(** [set_signal event signal persist callback] initializes the event. The
    flag [persist] makes an event persistent unit {!Libevent.del} is
    called. *)

val unset : event -> unit
(** [unset event] removes the callback associated with [event].
    [set] or [set_signal] must be called again before a call to [add] *)

val add : event -> float option -> unit
(** [add event timeout] adds the [event] and schedules the execution
    of the function specified with {!Libevent.set}, or in at least the
    time specified in the [timeout]. If [timeout] is [None], no
    timeout occures, and the function will only be called if a
    matching event occurs on the file descriptor. *)

val del : event -> unit
(** [del event] removes [event] if scheduled. Can be later added with [add] *)

val pending : event -> event_flags list -> bool 

(** {5 Process Events} *)

val dispatch : unit -> unit
(** In order to process events, an application needs to call dispatch. This 
 *  function only returns on error, and should replace the event core of the 
 *  application
 *)

type loop_flags =
    ONCE            
  | NONBLOCK        
val loop : loop_flags -> unit
(** Provides an interface for single pass execution of pending events *)




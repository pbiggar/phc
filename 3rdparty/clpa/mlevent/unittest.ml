(***********************************************************************)
(* The OcamlEvent library                                              *)
(*                                                                     *)
(* Copyright 2002, 2003 Maas-Maarten Zeeman. All rights reserved. See  *) 
(* LICENCE for details.                                                *)
(***********************************************************************)

(* $Id: unittest.ml,v 1.9 2004/12/21 19:15:14 maas Exp $ *)

open OUnit

let create_event = Libevent.create 

(* Tests the creation of new events *)
let test_create_event _ =
  let e1 = create_event () in
  let e2 = create_event () in 
  "Events should be different" @? (e1 <> e2)

(* Tests if pending can be called with and without the optional float *)
let test_pending _ =
  let e = create_event () in
  ignore(Libevent.pending e [])

(* Test eof on a read callback *)
let test_read_eof _ =
  let test_string = "This is a test string\n\n\n" in
  let buflen = 512 in
  let buf = String.create buflen in
  let read_count = ref 0 in 
  let evt = create_event () in
  let read_cb fd event_type = 
    (* read data from the fd *)
    let len = Unix.read fd buf 0 buflen in
    (* when 0 bytes are read this is the EOF, and we are done. *)
    if len <> 0 then
      begin
	read_count := !read_count + len;
	Libevent.add evt None
      end
  in

  (* Create a socket pair for testing *)
  let s1, s2 = Unix.socketpair Unix.PF_UNIX Unix.SOCK_STREAM 0 in
  let l = Unix.write s1 test_string 0 (String.length test_string) in

  (* A shutdown_send will cause an EOF on the reading end *)
  Unix.shutdown s1 Unix.SHUTDOWN_SEND;

  (* Setup the event *)
  Libevent.set evt s2 [Libevent.READ] false read_cb;
  Libevent.add evt None;
  Libevent.dispatch ();

  (* Now its time to check some things *)
  assert_equal (String.length test_string) !read_count

(* This is not really a test (yet) *)
let call_set _ =
  let do_nothing _ _ =
    ()
  in  
  let e1 = Libevent.create () in
  Libevent.set e1 Unix.stderr [Libevent.WRITE] false do_nothing;
  Libevent.set e1 Unix.stdout [Libevent.WRITE] false do_nothing;
  Libevent.set e1 Unix.stdin [Libevent.READ] false do_nothing;
  Libevent.add e1 (Some 0.1);
  Libevent.loop(Libevent.ONCE)
 
(* Construct the test suite *)
let suite = "event" >::: 
  ["create_event" >:: test_create_event;
   "test_pending" >:: test_pending;
   "test_read_eof" >:: test_read_eof;
   "call_set" >:: call_set;
 ] 

(* Run the tests in the test suite *)
let _ = 
  run_test_tt_main suite

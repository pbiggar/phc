(*
 * Small example program
 *)

let signal_callback event called fd event_type =
  (* Print information on the signal we received *)
  Printf.printf "Got signal: %d\n" (Libevent.signal event);
  flush stdout;
 
  called := !called - 1;

  if !called <= 0 then
    Libevent.del event

let _ =
  let sigint = 2 in  

  (* Create an event *)
  let signal_event = Libevent.create () in

  (* Set the sigint signal *)
  Libevent.set_signal signal_event sigint true
    (signal_callback signal_event (ref 2));

  (* Add the signal to the event library *)
  Libevent.add signal_event None;

  Printf.printf "SIGINT me please!\n";
  flush stdout;

  (* Start the event dispatching mainloop *)
  Libevent.dispatch ()

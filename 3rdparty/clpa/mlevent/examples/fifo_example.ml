(*
 * Small example program
 *)

let fifo_read event fd event_type =
  let buflen = 255 in
  let buf = String.create buflen in 
  match Unix.read fd buf 0 buflen with
    0 -> 
      Printf.printf "Connection closed\n";
      flush stdout
  | n -> 
      Printf.printf "Read: %s\n" (String.sub buf 0 n);
      flush stdout;

      (* Reschedule this event *)
      Libevent.add event None

let _ =
  let fifo = "event.fifo" in

  Unix.unlink fifo; 
  Unix.mkfifo fifo 0o600;

  let fifo_fd = Unix.openfile fifo [ Unix.O_RDWR; Unix.O_NONBLOCK ] 0 in
  let evfifo = Libevent.create () in

  Printf.printf "Write date to: %s\n" fifo;
  flush stdout;
  
  Libevent.set evfifo fifo_fd [Libevent.READ] false (fifo_read evfifo);
  Libevent.add evfifo None;

  Libevent.dispatch ()
    


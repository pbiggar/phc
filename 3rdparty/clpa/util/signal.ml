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

(* signal.ml - convert POSIX signals into exceptions *)

exception Signal of string
let signals = [
  (Sys.sigabrt, "SIGABRT");
  (Sys.sigalrm, "SIGALRM");
  (Sys.sigfpe,  "SIGFPE");
  (Sys.sighup,  "SIGHUP");
  (* (Sys.sigill,  "SIGILL"); *)
  (Sys.sigint,  "SIGINT");
  (* (Sys.sigkill, "SIGKILL"); *)
  (Sys.sigpipe, "SIGPIPE");
  (Sys.sigquit, "SIGQUIT");
  (* (Sys.sigsegv, "SIGSEGV"); *)
  (* (Sys.sigterm, "SIGTERM"); *)
]
let _ = List.iter (fun (sign,name) ->
  Sys.set_signal sign
    (Sys.Signal_handle (fun _ -> raise (Signal name)))) signals

let is_signal exn =
  match exn with
      Signal _ -> true
    | Out_of_memory -> true  (* treat Out_of_memory as de-facto signal *)
    | _ -> false

let set_sigalrm secs =
  let interval = {
    (* set both initial and recurring alarm in case we timeout during
     * an external procedure call *)
    Unix.it_interval = float_of_int secs;
    Unix.it_value = float_of_int secs;
  } in
  ignore (Unix.setitimer Unix.ITIMER_REAL interval)

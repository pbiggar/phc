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

(* debugging *)

val register_debug : string (* name *) -> string (* desc *) -> (unit -> bool)
val set_debug : string (* name *) -> unit

(* print descriptions of each debug flag to the screen *)
val list_all_debug : unit -> unit

(* batch get/set all names associated with active debug flags *)
val get_all_debug : unit -> string list
val set_all_debug : string list -> unit

(* statistics *)

val register_stats : string (* name *) -> string (* desc *) -> (unit -> bool)
val set_stats : string (* name *) -> unit

(* print descriptions of each stats flag to the screen *)
val list_all_stats : unit -> unit

(* batch get/set all names associated with active stats flags *)
val get_all_stats : unit -> string list
val set_all_stats : string list -> unit

(* settings *)

val register_setting :
  string (* name *) -> string (* desc *) -> float (* default *) ->
  (unit -> float)
val set_setting : string (* name=value *) -> unit

(* print descriptions of each setting to the screen *)
val list_all_settings : unit -> unit

(* batch get/set all names associated with active settings flags *)
val get_all_settings : unit -> (string * float) list
val set_all_settings : (string * float) list -> unit

(* allocation/timing statistics *)

(* generate functions which will keep track of the total amount of allocation
 * performed within them (regardless of whether it is collected later) as well
 * as the total time spent, printing out later with print_tracks() *)
val make_track_0 :
  string -> (unit -> 'a) -> (unit -> 'a)
val make_track_1 :
  string -> ('a -> 'b) -> ('a -> 'b)
val make_track_2 :
  string -> ('a -> 'b -> 'c) -> ('a -> 'b -> 'c)
val make_track_3 :
  string -> ('a -> 'b -> 'c -> 'd) -> ('a -> 'b -> 'c -> 'd)
val make_track_4 :
  string -> ('a -> 'b -> 'c -> 'd -> 'e) -> ('a -> 'b -> 'c -> 'd -> 'e)

(* finer control over beginning or ending of tracks *)
type track_info
val new_track_info : string -> track_info
val start_track : track_info -> unit
val end_track : track_info -> unit

(* whether to create tracking functions. default true, if false then each
 * make_track_* returns the identify *)
val make_tracks : bool ref

(* prints overall/deltas in allocation info for each tracking function *)
val print_allocs : unit -> unit
val print_alloc_deltas : unit -> unit

(* prints overall/deltas in timing info for each tracking function *)
val print_times : unit -> unit
val print_time_deltas : unit -> unit

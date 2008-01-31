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

open Clpautil
module H = Hashtbl
module S = String

let format_print title values tostring =
  let maxlen = List.fold_left (fun len (name,_) ->
                 max len (S.length name)) 0 values in
    Printf.printf "%s:\n" title;
    List.iter (fun (name,v) ->
      let rem = S.make (maxlen - S.length name) ' ' in
        Printf.printf "%s:%s %s\n" name rem (tostring v)) values

(* debugging *)

let debug_all : (string,string) H.t = H.create 10
let debug_active : (string,unit) H.t = H.create 10

let register_debug name desc =
  if H.mem debug_all name then
    (Printf.eprintf "Duplicate debug flag: %s\n" name; exit 1);
  H.add debug_all name desc;
  fun () -> H.mem debug_active name

let set_debug name =
  if not (H.mem debug_all name) then
    (Printf.eprintf "Unknown debug flag: %s\n" name; exit 1);
  H.replace debug_active name ()

let list_all_debug() =
  let flags = H.fold (fun name desc rem -> (name,desc)::rem) debug_all [] in
  let flags = List.sort (fun (n0,_) (n1,_) -> compare n0 n1) flags in
    format_print "Debug Flags" flags id

let set_all_debug flags =
  H.clear debug_active;
  List.iter (fun f -> H.replace debug_active f ()) flags
let get_all_debug() =
  H.fold (fun f _ list -> f::list) debug_active []

(* statistics *)

let stats_all : (string,string) H.t = H.create 10
let stats_active : (string,unit) H.t = H.create 10

let register_stats name desc =
  if H.mem stats_all name then
    (Printf.eprintf "Duplicate stats flag: %s\n" name; exit 1);
  H.add stats_all name desc;
  fun () -> H.mem stats_active name

let set_stats name =
  if not (H.mem stats_all name) then
    (Printf.eprintf "Unknown stats flag: %s\n" name; exit 1);
  H.replace stats_active name ()

let list_all_stats() =
  let flags = H.fold (fun name desc rem -> (name,desc)::rem) stats_all [] in
  let flags = List.sort (fun (n0,_) (n1,_) -> compare n0 n1) flags in
    format_print "Stats Flags" flags id

let set_all_stats flags =
  H.clear stats_active;
  List.iter (fun f -> H.replace stats_active f ()) flags
let get_all_stats() =
  H.fold (fun f _ list -> f::list) stats_active []

(* settings *)

let settings_all : (string,string*float) H.t = H.create 10
let settings_changed : (string,float) H.t = H.create 10

let register_setting name desc default =
  if H.mem stats_all name then
    (Printf.eprintf "Duplicate setting name: %s\n" name; exit 1);
  H.add settings_all name (desc,default);
  fun () -> try H.find settings_changed name with Not_found -> default

let set_setting asnstr =
  try let eqpos = S.index asnstr '=' in
    let name = S.sub asnstr 0 eqpos in
    let vs = S.sub asnstr (eqpos+1) (S.length asnstr - eqpos - 1) in
    let value = float_of_string vs in
      H.replace settings_changed name value
  with Not_found
     | Failure "float_of_string" ->
    Printf.eprintf "Setting string not in flag=n format: %s\n" asnstr; exit 1

let list_all_settings() =
  let flags = H.fold (fun name desc rem -> (name,desc)::rem) settings_all [] in
  let flags = List.sort (fun (n0,_) (n1,_) -> compare n0 n1) flags in
    format_print "Settings  [default]" flags
      (fun (desc,def) -> Printf.sprintf "%s [%.0f]" desc def);
    print_endline "  *** all times in seconds, all memory amounts in megabytes"

let set_all_settings flags =
  H.clear settings_changed;
  List.iter (fun (name,value) -> H.replace settings_changed name value) flags
let get_all_settings() =
  H.fold (fun name value list -> (name,value)::list) settings_changed []

(* allocation/timing info *)

let time() = Unix.gettimeofday()
let alloc() = (Gc.quick_stat()).Gc.minor_words

type track_info = {
  name : string;
  (* start time/allocs for current tracking *)
  mutable cur_track : int; (* # of times started, allow re-entrancy *)
  mutable cur_time : float;
  mutable cur_alloc : float;
  (* aggregate info *)
  mutable total_calls : float;
  mutable total_time : float;
  mutable total_alloc : float;
  (* aggregate info at last call to delta() *)
  mutable last_calls : float;
  mutable last_time : float;
  mutable last_alloc : float;
}
let all_tracks : track_info list ref = ref []

let last_delta_time : float ref = ref (time())
let last_delta_alloc : float ref = ref (alloc())

let new_track_info name =
  let info = {
    name = name;
    cur_track = 0;
    cur_time = 0.;
    cur_alloc = 0.;
    total_calls = 0.;
    total_time = 0.;
    total_alloc = 0.;
    last_calls = 0.;
    last_time = 0.;
    last_alloc = 0.;
  } in prepend all_tracks info; info

let start_track info =
  info.cur_track <- info.cur_track + 1;
  info.total_calls <- info.total_calls +. 1.;
  if info.cur_track = 1 then begin
    info.cur_time <- time();
    info.cur_alloc <- alloc()
  end

let end_track info =
  info.cur_track <- info.cur_track - 1;
  if info.cur_track < 0 then
    Printf.printf "WARNING: end_track() called without start_track(): %s\n"
      info.name
  else if info.cur_track = 0 then begin
    info.total_time <- info.total_time +. (time() -. info.cur_time);
    info.total_alloc <- info.total_alloc +. (alloc() -. info.cur_alloc);
    info.cur_time <- 0.;
    info.cur_alloc <- 0.
  end

let active_tracks : track_info list ref = ref []
let track info func =
  start_track info;
  try let v = func() in end_track info; v
  with exn -> end_track info; raise exn

let make_tracks = ref true
let make_track_0 name func =
  if !make_tracks then begin
    let info = new_track_info name in
      fun () -> track info (fun () -> func ())
  end else func
let make_track_1 name func =
  if !make_tracks then begin
    let info = new_track_info name in
      fun x -> track info (fun () -> func x)
  end else func
let make_track_2 name func =
  if !make_tracks then begin
    let info = new_track_info name in
      fun x y -> track info (fun () -> func x y)
  end else func
let make_track_3 name func =
  if !make_tracks then begin
    let info = new_track_info name in
      fun x y z -> track info (fun () -> func x y z)
  end else func
let make_track_4 name func =
  if !make_tracks then begin
    let info = new_track_info name in
      fun x y z w -> track info (fun () -> func x y z w)
  end else func

let print_track_info title (fvalue: track_info -> float) (thresh:float)
                     (fstring: float -> string) =
  let numlist = List.fold_right (fun info list ->
    let v = fvalue info in
      if v >= thresh then (info.name,v)::list else list) !all_tracks [] in
  let numlist = List.sort (fun (_,v0) (_,v1) -> compare v1 v0) numlist in
    format_print title numlist fstring

let print_allocs() =
  print_track_info "Allocations"
    (fun i -> i.total_alloc) 1048576. alloc_string

let print_alloc_deltas() =
  let title = Printf.sprintf "Allocation deltas: %s performed"
    (alloc_string (alloc() -. !last_delta_alloc)) in
  last_delta_alloc := alloc();
  print_track_info title
    (fun i -> i.total_alloc -. i.last_alloc) 1048576. alloc_string;
  List.iter (fun i -> i.last_alloc <- i.total_alloc) !all_tracks

let print_times() =
  print_track_info "Timers"
    (fun i -> i.total_time) 1. time_string

let print_time_deltas() =
  let title = Printf.sprintf "Timer deltas: %s elapsed" 
    (time_string (time() -. !last_delta_time)) in
  last_delta_time := time();
  print_track_info title
    (fun i -> i.total_time -. i.last_time) 1. time_string;
  List.iter (fun i -> i.last_time <- i.total_time) !all_tracks

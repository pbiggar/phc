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

(* lightweight representation of 3-byte integer sets as hashes.
 * retain average case O(1) insert/lookup while optimizing for space *)

type t = {
  (* hash table. each 4 characters is a distinct slot.
   * first byte is 0 if empty, 1 if non-empty, next 3 bytes indicate content.
   * collisions resolved by advancing to next unoccupied slot *)
  mutable hash: string;

  (* number of slots, length(hash) / 4 *)
  mutable cap: int;

  (* number of occupied slots. maintain between 50% and 75% of capacity *)
  mutable len: int;
}

let create() = {
  hash = String.make 8 (char_of_int 0);
  cap = 2;
  len = 0;
}

let is_empty str pos =
  int_of_char (String.unsafe_get str (pos*4)) = 0

let read str pos =
  assert (not (is_empty str pos));
  (int_of_char (String.unsafe_get str (pos*4+1))) lor
 ((int_of_char (String.unsafe_get str (pos*4+2))) lsl 8) lor
 ((int_of_char (String.unsafe_get str (pos*4+3))) lsl 16)

let write str pos n =
  String.unsafe_set str (pos*4) (char_of_int 1);
  String.unsafe_set str (pos*4+1) (char_of_int (n land 0xff));
  String.unsafe_set str (pos*4+2) (char_of_int ((n lsr 8) land 0xff));
  String.unsafe_set str (pos*4+3) (char_of_int ((n lsr 16) land 0xff))

let add h n =
  let chain hash cap n =
    let pos = ref (n mod cap) in
      while not (is_empty hash !pos) && read hash !pos <> n do
        pos := (!pos + 1) mod cap
      done;
      if is_empty hash !pos then (write hash !pos n; true)
      else false in
  if h.len+1 >= h.cap*3/4 then begin
    let ncap = h.cap*3/2 in
    let nhash = String.make (ncap*4) (char_of_int 0) in
      for pos = 0 to (h.cap-1) do
        if not (is_empty h.hash pos) then
          ignore (chain nhash ncap (read h.hash pos))
      done;
      h.hash <- nhash;
      h.cap <- ncap
  end;
  if chain h.hash h.cap n then h.len <- h.len + 1

let mem h n =
  let pos = ref (n mod h.cap) in
    while not (is_empty h.hash !pos) && read h.hash !pos <> n do
      pos := (!pos + 1) mod h.cap
    done;
    not (is_empty h.hash !pos)

let length h = h.len

let iter fn h =
  for pos = 0 to (h.cap-1) do
    if not (is_empty h.hash pos) then
      fn (read h.hash pos)
  done

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

(* heap array based priority queue implementation *)

exception Empty

module V = Vector

(* queue structure *)
type 'a t = {
  compare: 'a -> 'a -> int;
  tostring: 'a -> string;
  heap: ('a * int ref) V.t;
}

(* ref cell with the element's queue position *)
type qref = int ref

let create fn tostring = {
  compare = fn;
  tostring = tostring;
  heap = V.create 100;
}

let is_empty q = V.size q.heap = 0

let clear q = V.clear q.heap

let higher q pos0 pos1 =
  let (v0,_) = V.get q.heap pos0 in
  let (v1,_) = V.get q.heap pos1 in
    (q.compare v0 v1) < 0

let swap q pos0 pos1 =
  let (v0,r0) = V.get q.heap pos0 in
  let (v1,r1) = V.get q.heap pos1 in
    V.set q.heap pos0 (v1,r1);
    V.set q.heap pos1 (v0,r0);
    r0 := pos1;
    r1 := pos0

(*
let check where q cpos =
  let bad_order which fpos bpos =
    Printf.printf "ERROR: %s [%s]: bad queue ordering %s [%d] before %s [%d]\n" where which
      (q.tostring (fst (V.get q.heap fpos))) fpos
      (q.tostring (fst (V.get q.heap bpos))) bpos in
  let size = V.size q.heap in
  let rec check_par pos =
    let parpos = (pos-1)/2 in
      if pos > 0 then begin
        if higher q cpos parpos then bad_order "parent" parpos cpos;
        check_par parpos
      end in
  let rec check_child pos =
    let lpos = pos*2+1 in
    let rpos = lpos+1 in
      if rpos < size then begin
        if higher q rpos cpos then bad_order "child" cpos rpos;
        check_child rpos
      end;
      if lpos < size then begin
        if higher q lpos cpos then bad_order "child" cpos lpos;
        check_child lpos
      end in
  check_par cpos; check_child cpos
*)

let rec upheap q pos =
  let size = V.size q.heap in
  let ppos = (pos-1)/2 in
    if pos < size && pos > 0 && higher q pos ppos then
      (swap q pos ppos; upheap q ppos)
    else ()

let rec downheap q pos =
  let size = V.size q.heap in
  let lpos = pos*2+1 in
  let rpos = lpos+1 in
    if rpos < size && higher q rpos lpos then
      (if higher q rpos pos then (swap q rpos pos; downheap q rpos))
    else if lpos < size then
      (if higher q lpos pos then (swap q lpos pos; downheap q lpos))
    else ()

let percolate q pos =
  let size = V.size q.heap in
  let ppos = (pos-1)/2 in
  let lpos = pos*2+1 in
  let rpos = lpos+1 in
    if pos < size && pos > 0 && higher q pos ppos then
      (swap q pos ppos; upheap q ppos)
    else if rpos < size && higher q rpos lpos then
      (if higher q rpos pos then (swap q rpos pos; downheap q rpos))
    else if lpos < size then
      (if higher q lpos pos then (swap q lpos pos; downheap q lpos))
    else ()

let insert q v =
  (* add at end of vector and percolate, O(log n) *)
  let r = ref (V.size q.heap) in
  let npos = V.append q.heap (v,r) in
    upheap q npos; r

let reinsert q v r =
  let npos = V.append q.heap (v,r) in
    r := npos;
    upheap q npos

let remove_min q =
  (* swap with end of vector and percolate, O(log n) *)
  let last = V.size q.heap - 1 in
    if last = ~-1 then raise Empty
    else begin
      let (v,r) = V.get q.heap 0 in
        swap q 0 last;
        V.shrink q.heap last;
        downheap q 0;
        r := ~-1; v
    end

let remove q r =
  (* swap particular element with end of vector and percolate, O(log n) *)
  let last = V.size q.heap - 1 in
  let pos = !r in
    if pos <> ~-1 then begin
      let (v,_) = V.get q.heap pos in
      swap q pos last;
      V.shrink q.heap last;
      percolate q pos;
      r := ~-1; Some v
    end else None

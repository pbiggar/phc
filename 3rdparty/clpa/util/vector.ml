(*
 * Authors:
 *   Yichen Xie  <yxie@cs.stanford.edu>
 *
 * Copyright (c) 2004,
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

type 'a t = { mutable theVector : 'a option array;
	      mutable theSize : int;
	      mutable maxIndex : int }

let create n = { theVector = Array.make n None; theSize = n; maxIndex = -1 }

let grow_array vec =
  vec.theVector <-
    Array.append vec.theVector (Array.make vec.theSize None);
  vec.theSize <- vec.theSize * 2

let set vec i v =
  while (i >= vec.theSize) do
    grow_array vec
  done;
  vec.theVector.(i) <- Some v;
  vec.maxIndex <- if i > vec.maxIndex then i else vec.maxIndex

let unset vec i =
  if (i >= vec.theSize) then ()
  else vec.theVector.(i) <- None

let get vec i =
  if i > vec.maxIndex then raise Not_found;
  match vec.theVector.(i) with
      None -> raise Not_found
    | Some e -> e

let size vec = vec.maxIndex + 1

let shrink vec newsize = 
  assert (newsize <= vec.maxIndex + 1);
  for i = newsize to vec.maxIndex do
    vec.theVector.(i) <- None
  done;
  vec.maxIndex <- newsize - 1

let append vec v = 
  let idx = size vec
  in set vec idx v; idx

let fold f v b =
  let res = ref b in
    for i = 0 to v.maxIndex do
      match v.theVector.(i) with
          Some e -> res := f e !res
        | None -> ()
    done; !res

let iter f v =
  for i = 0 to v.maxIndex do
    match v.theVector.(i) with
      Some e -> f e
    | None -> ()
  done

let iteri f v =
  for i = 0 to v.maxIndex do
    match v.theVector.(i) with
      Some e -> f i e
    | None -> ()
  done

let clear vec = shrink vec 0

let mem v i =
  if i >= size v then false
  else if v.theVector.(i) = None then false
  else true

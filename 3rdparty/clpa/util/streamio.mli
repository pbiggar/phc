(*
 * Authors:
 *   Brian Hackett  <bhackett@stanford.edu>
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
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

type t_load_fn = unit -> char (* may raise End_of_file *)
type t_dump_fn = char -> unit

(* String streams *)

val init_load_string : string -> t_load_fn
val init_dump_string : unit -> (t_dump_fn * Buffer.t)

(* File streams *)

type t_load_file
val init_load_file : string -> (t_load_file * t_load_fn)
val close_load_file : t_load_file -> unit

type t_dump_file
val init_dump_file : string -> (t_dump_file * t_dump_fn)
val close_dump_file : t_dump_file -> unit

val load_file : string -> (t_load_fn -> 'a) -> 'a
val dump_file : string -> (t_dump_fn -> 'a) -> 'a

(* BDB integration *)

val bdb_init : string -> unit
val bdb_finish : unit -> unit

val bdb_checkpt_dir : string ref
val bdb_checkpt : unit -> unit
val bdb_checkpt_resume : unit -> unit

(* merge databases in a directory with the current ones *)
val bdb_merge_dir : string -> unit

(* get the named database, creating a new one if it does not exist *)
val get_db : string -> Bdb.db
val exists_db : string -> bool

(* default compress/uncompress routines, using zlib *)
val compress : int -> string -> string
val uncompress : string -> string

(* Sockets integration *)

type t_sock_desc 
type t_sock

type t_sock_connect_cb = (t_sock -> unit)
type t_sock_data_cb = (t_sock -> string -> unit)
type t_sock_peerclosed_cb = (t_sock -> unit)

(* Exception raised by socket_dump when the connection is closed by a peer.
 * The peer close callback is called before this exception is raised.
 *)
exception Socket_closed_by_peer of t_sock

val socket_set_data_cb : t_sock -> t_sock_data_cb -> unit
val socket_set_peerclosed_cb : t_sock -> t_sock_peerclosed_cb -> unit
val socket_dump : t_sock -> string -> unit
val socket_close : t_sock -> unit

(* Attempt to ensure that all data has been written to a set of sockets, 
 * timing out after a specified number of seconds *)
val ensure_writes : t_sock list -> float -> unit

(* get the number of bytes read and written to a socket *)
val socket_count_io : t_sock -> float * float

(* Create a server socket, calling the accept function when a new connection
 * is received *)
val server_socket : t_sock_connect_cb -> (t_sock_desc * Unix.inet_addr * int)

val client_socket : Unix.inet_addr -> int -> t_sock

(* Plaintext Output *)

(* type of a plaintext output stream, which can be piped to file or database,
 * or captured via set_collect_output() below *)
type t_ptstream

(* mode for combining plaintext output with earlier output *)
type t_ptmode =
    Pt_excl    (* later output is added only if no earlier output exists *)
  | Pt_trunc   (* any earlier output is truncated and overwritten *)
  | Pt_append  (* later output is appended to earlier output *)

(* create a stream for writing plaintext data to the analysis directory *)
val open_file : string (* file name *) -> t_ptmode -> t_ptstream
val open_dbentry : string (* db name *) -> string (* db key *) -> t_ptmode -> t_ptstream
val close_stream : t_ptstream -> unit

val printf : ('a,unit,string,unit) format4 -> 'a
val fprintf : t_ptstream -> ('a,unit,string,unit) format4 -> 'a

(* suppress stdout and file I/O from C libraries etc. *)
val suppress_external_output : unit -> bool

(* collect all stdout and file/database I/O performed using printf and fprintf
 * between calls to set_collect_output() and get_collect_output().
 * get_collect_output() reverts to default printf/fprintf afterwards *)
type t_output_set
val set_collect_output : unit -> unit
val get_collect_output : unit -> t_output_set

(* prints all output to console and file *)
val print_output : t_output_set -> unit

val load_output : t_load_fn -> t_output_set
val dump_output : t_dump_fn -> t_output_set -> unit

(* I/O for basic types *)

(* error reporting for malformed loads *)
exception Load_error of string
val loaderror: string -> 'a

val load_byte   : t_load_fn -> int
val load_int    : t_load_fn -> int
val load_int64  : t_load_fn -> int64
val load_bigint : t_load_fn -> Big_int.big_int
val load_string : t_load_fn -> string
val load_bool   : t_load_fn -> bool
val load_float  : t_load_fn -> float
val load_option : t_load_fn -> (t_load_fn -> 'a) -> 'a option
val load_list   : t_load_fn -> (t_load_fn -> 'a) -> 'a list
val load_array  : t_load_fn -> (t_load_fn -> 'a) -> 'a array

val dump_byte   : t_dump_fn -> int -> unit
val dump_int    : t_dump_fn -> int -> unit
val dump_int64  : t_dump_fn -> int64 -> unit
val dump_bigint : t_dump_fn -> Big_int.big_int -> unit
val dump_string : t_dump_fn -> string -> unit
val dump_bool   : t_dump_fn -> bool -> unit
val dump_float  : t_dump_fn -> float -> unit
val dump_option : t_dump_fn -> (t_dump_fn -> 'a -> unit) -> 'a option -> unit
val dump_list   : t_dump_fn -> (t_dump_fn -> 'a -> unit) -> 'a list -> unit
val dump_array  : t_dump_fn -> (t_dump_fn -> 'a -> unit) -> 'a array -> unit

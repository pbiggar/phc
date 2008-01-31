(*
 * Authors:
 *   Ted Kremenek   <kremenek@cs.stanford.edu>
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
 *
 * Copyright (c) 2004-2006,
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

(* Database environments *)
type dbenv
external dbenv_create : unit -> dbenv = "caml_dbenv_create"
external dbenv_open : dbenv -> string -> int -> unit = "caml_dbenv_open"
external dbenv_set_cachesize : dbenv -> int -> int -> unit = 
    "caml_dbenv_set_cachesize"
external dbenv_close : dbenv -> unit = "caml_dbenv_close"
external dbenv_memp_stat_print : dbenv -> unit = "caml_dbenv_memp_stat_print"

(* Databases *)
type open_flag =
  (* simulate the Dbm library *)
    Dbm_rdonly
  | Dbm_wronly
  | Dbm_rdwr
  | Dbm_create

  (* extended flags *)
  | Dbm_auto_commit
  | Dbm_dirty_read
  | Dbm_excl
  | Dbm_nommap
  | Dbm_thread
  | Dbm_truncate

exception Dbm_error of string

type db

external raw_openbdb : dbenv option -> string -> open_flag list -> int -> db
  = "caml_bdb_open"

let opendbm env file flags mode =
  try
    raw_openbdb env file flags mode
  with Dbm_error msg ->
    raise ( Dbm_error("Can't open file " ^ file ^ ": " ^ msg ))

external close : db -> unit = "caml_bdb_close"
external find : db -> string -> string = "caml_bdb_fetch"
external add : db -> string -> string -> unit = "caml_bdb_insert"
external replace : db -> string -> string -> unit = "caml_bdb_replace"
external remove : db -> string -> unit = "caml_bdb_delete"
external firstkey : db -> string = "caml_bdb_firstkey"
external nextkey : db -> string = "caml_bdb_nextkey"
external sync : db -> unit = "caml_bdb_sync"

let _ = Callback.register_exception "dbmbderror" (Dbm_error "")

let iter f t =
  let rec walk = function
      None -> ()
    | Some k ->
	f k ( find t k ) ;
	walk ( try Some( nextkey t ) with Not_found -> None )
  in
  walk ( try Some ( firstkey t ) with Not_found -> None )

(* BerKeley DB Specific extensions to DBM interface.  This
   is somewhere halfway to the full thing *)

(*
type open_bdb_flag =
    DB_AUTO_COMMIT
  | DB_CREATE
  | DB_DIRTY_READ
  | DB_EXCL
  | DB_NOMMAP
  | DB_RDONLY
  | DB_THREAD
  | DB_TRUNCATE
*)

type bdb_db_type =
    DB_BTREE
  | DB_HASH
  | DB_UNKNOWN

external raw_openbdb_advanced : 
  string -> string -> bdb_db_type -> 
  (*open_bdb_flag*) open_flag list -> int -> db
  = "caml_bdb_open_advanced"

let opendbm_advanced file dbname dbtype flags mode =
  try 
    raw_openbdb_advanced dbname file dbtype flags mode
  with Dbm_error msg ->
    raise ( Dbm_error("Can't open file " ^ file ^ ": " ^ msg ))


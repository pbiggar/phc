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

(** Interface to Berkeley DB that mimics the {!Dbm} module that is
  part of the standard Objective Caml library.  This is a primitive
  interface that hides many of the features of Berkeley DB.  It is
  designed to be a plug in replacement for the {!Dbm} module.  To
  harness more of the features of Berkeley DB, see the {!Bdb} module
  instead. *)

    (* The type of a database environment *)
type dbenv

    (* dbenv_create 
     * Create a DB environment handle
     *)
val dbenv_create : unit -> dbenv

    (* dbenv_open path mode 
     * Open a database environment. Takes a environment path and a permissions
     * bitmask to apply to new database files. *)
val dbenv_open : dbenv -> string -> int -> unit 

    (* dbenv_set_cachesize env gbytes bytes
     * Set the cache size of an environment to gbytes gigabytes + bytes bytes.
     * Must be called before dbenv_open.
     *)
val dbenv_set_cachesize : dbenv -> int -> int -> unit

    (* dbenv_close env
     * Close a database environment, freeing all associated memory. This
     * function should not be called while database handles associated with
     * this environment remain open.
     *) 
val dbenv_close : dbenv -> unit

    (* dbenv_memp_stat_print 
     * Dump statistics about cache usage to standard output
     *)
val dbenv_memp_stat_print : dbenv -> unit


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
  (** The type of file descriptors opened on Berkeley DB databases.
    This descriptor type is incompatible with the type for the {!Bdb}
    module. *)

val opendbm : dbenv option -> string -> open_flag list -> int -> db
  (** Open a descriptor on a Berkeley DB database.  Because this
    interface is limited, it defaults to using the B-Tree storage
    method for data (see Berkeley DB
    documentation). The first argument is an optional environment handle to use.
    The second argument is the name of the database.
    The third argument is a list of flags (see the [Dbm] module).
    The fourth argument is the permissions to give to the database
    file. *)

val close : db -> unit
(* external close : t -> unit = "caml_dbmbdb_close" *)
  (** Closes the Berkeley DB database associated with the descriptor.
    Make sure you do this when you are done with a database.  It will
    sync the data to secondary storage, but will also free resources
    used by the C backend.  Failure to do so will result in a memory
    leak when the database descriptor object is garbage collected.
    This may be fixed in a future implementation so that these
    resources are properly released when the object is garbage
    collected.  Even if this is done, it is a bad idea to rely on the
    garbage collector to do this, as you have no idea when the garbage
    collector will run. *)

val find : db -> string -> string
(* external find : t -> string -> string = "caml_dbmbdb_fetch" *)
   (** [find db key] returns the data assocaited with the given [key]
     in the database opened for the descriptor [db].  Raise
     [Not_found] if the [key] has no associated data. *)

val add : db -> string -> string -> unit
(* external add : t -> string -> string -> unit = "caml_dbmbdb_insert" *)
   (** [add db key data] inserts the pair ([key], [data]) in the
     database [db]. If the database already contains data associated
     with [key], raise [Dbm_error "Entry already exists"]. *)

val replace : db -> string -> string -> unit
(* external replace : t -> string -> string -> unit = "caml_dbmbdb_replace" *)

val remove : db -> string -> unit
(* external remove : t -> string -> unit = "caml_dbmbdb_delete" *)
  (** [remove db key data] removes the data associated with [key] in
    [db]. If [key] has no associated data, raise [Dbm_error
    "dbm_delete"]. *)

val firstkey : db -> string
(* external firstkey : t -> string = "caml_dbmbdb_firstkey" *)
				    (** See {!Dbmbd.nextkey}.*)

val nextkey : db -> string
(* external nextkey : t -> string = "caml_dbmbdb_nextkey" *)
  (** Enumerate all keys in the given database, in an unspecified
    order.  [firstkey db] returns the first key, and repeated calls to
    [nextkey db] return the remaining keys. [Not_found] is raised when
    all keys have been enumerated. *)

val iter : (string -> string -> 'a) -> db -> unit
  (** [iter f db] applies [f] to each ([key], [data]) pair in
    the database [db]. [f] receives [key] as first argument
    and [data] as second argument. *)

val sync : db -> unit

(** Berkeley DB specific extensions to DBM interface *)

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

val opendbm_advanced : string -> string -> bdb_db_type -> 
  open_flag list -> int -> db
  (** Open a descriptor to a Berkeley DB database.  This is an
    extension to the Dbm interface that allows you to specify the
    database name (allows multiple databases in a single file) and the
    database storage type.  This interface only allows B-Tree and hash
    representations. *)

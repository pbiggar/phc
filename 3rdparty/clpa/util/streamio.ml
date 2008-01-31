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

open Clpautil
open Flags

module B = Buffer
module H = Hashtbl
module S = String
module U = Unix
module E = Libevent
open Big_int

type t_load_fn = unit -> char
type t_dump_fn = char -> unit

(* String streams *)

let init_load_string str =
  let len = S.length str in
  let pos = ref 0 in
  fun () ->
    if !pos >= len then raise End_of_file
    else let res = String.unsafe_get str !pos in incr pos; res

let init_dump_string () =
  let dumpstr = B.create 1024 in
  let dumpfn = B.add_char dumpstr in
    (dumpfn, dumpstr)

(* File streams *)

type t_load_file = in_channel

let init_load_file file =
  let loadfile = open_in_bin file in
  let loadfn () = input_char loadfile in
    (loadfile, loadfn)

let close_load_file = close_in

type t_dump_file = out_channel

let init_dump_file file =
  let dumpfile = open_out_bin file in
  let dumpfn = output_char dumpfile in
    (dumpfile, dumpfn)

let close_dump_file = close_out

let load_file file fn =
  let (lf,ls) = init_load_file file in
  let res = fn ls in
    close_load_file lf; res

let dump_file file fn =
  let (df,ds) = init_dump_file file in
  let res = fn ds in
    close_dump_file df; res

(* BDB integration *)

let dbenv_handle = ref None
let database_dir = ref "."
let db_mode = 0o666
let databases : (string,Bdb.db) H.t = H.create 10

let stats_db_cache_usage = register_stats "db_cache"
  "Print information about database cache usage on exit"
let setting_db_cache_size = register_setting "bdb_cache_size"
  "Size of BDB cache" 50.

let dbinit = ref false
let check_init v msg =
  if !dbinit <> v then failwith msg

let bdb_init dir =
  check_init false "bdb_init called multiple times";
  dbinit := true;
  database_dir := dir;
  let dbh = Bdb.dbenv_create () in
  Bdb.dbenv_set_cachesize dbh 0
    (int_of_float (setting_db_cache_size() *. 1048576.));
  Bdb.dbenv_open dbh "." db_mode;
  dbenv_handle := Some dbh

let bdb_finish () =
  check_init true "bdb_finish called without bdb_init";
  dbinit := false;
  H.iter (fun _ db -> Bdb.close db) databases;
  H.clear databases;
  (match !dbenv_handle with
      None -> ()
    | Some dbh ->
        if stats_db_cache_usage() then Bdb.dbenv_memp_stat_print dbh;
        Bdb.dbenv_close dbh; dbenv_handle := None)

let bdb_checkpt_dir = ref "./checkpt"

let bdb_checkpt () =
  check_init true "bdb_checkpt called without bdb_init";
  let dbnames = H.fold (fun name _ list -> name::list) databases [] in
  bdb_finish();
  (* copy every database to the checkpt directory *)
  if not (Sys.file_exists !bdb_checkpt_dir) then
    Unix.mkdir !bdb_checkpt_dir 0o777;
  List.iter (fun name ->
      (* hack: ignore CIL databases which are assumed read-only *)
      if (S.length name >= 4 && S.sub name 0 4 = "cil_") then ()
      else if name = "process" then ()
      else ignore (Sys.command ("cp " ^ name ^ ".db " ^ !bdb_checkpt_dir)))
    dbnames;
  bdb_init !database_dir

let bdb_checkpt_resume () =
  check_init false "bdb_checkpt_resume called after bdb_init";
  (* copy the databases back to the current directory. TODO: dehackify *)
  ignore (Sys.command ("cp " ^ !bdb_checkpt_dir ^ "/* ."))

let exists_db name =
  check_init true "exists_db called without bdb_init";
  Sys.file_exists (!database_dir ^ "/" ^ name ^ ".db")

let get_db name =
  check_init true "get_db called without bdb_init";
  try H.find databases name
  with Not_found ->
    let file = !database_dir ^ "/" ^ name ^ ".db" in
    let db = Bdb.opendbm !dbenv_handle file [ Bdb.Dbm_rdwr; Bdb.Dbm_create ]
             db_mode in
      H.add databases name db; db

let bdb_merge_dir dir =
  check_init true "bdb_merge_dir called without bdb_init";
  Array.iter (fun file ->
    let len = String.length file in
    if len >= 3 && (String.sub file (len-3) 3 = ".db") then
      let udb = get_db (String.sub file 0 (len-3)) in
      let mdb = Bdb.opendbm !dbenv_handle (dir ^ "/" ^ file) [ Bdb.Dbm_rdonly ]
                db_mode in
        Printf.printf "Merging in %s/%s...\n" dir file;
        Bdb.iter (Bdb.replace udb) mdb;
        Bdb.close mdb) (Sys.readdir dir)

external compress : int -> string -> string = "gz_compress"
external uncompress : string -> string = "gz_uncompress"

(* Plaintext Output *)

type t_ptmode =
    Pt_excl
  | Pt_trunc
  | Pt_append

type t_ptstream = {
  pt_where : string option;  (* None for file, Some dbname for dbname.db *)
  pt_kname : string;         (* file name or database key *)
  pt_mode  : t_ptmode;
  pt_data  : B.t;
}

let open_file name mode = {
  pt_where = None;
  pt_kname = name;
  pt_mode = mode;
  pt_data = B.create 1000;
}

let open_dbentry dbname kname mode = {
  pt_where = Some dbname;
  pt_kname = kname;
  pt_mode = mode;
  pt_data = B.create 1000;
}

let collecting = ref false
let c_stdout : B.t = B.create 10
let c_streams : t_ptstream list ref = ref []

let coll_string str =
  if !collecting then B.add_string c_stdout str
  else (print_string str; flush stdout)

let print_stream s = match s.pt_where with
    Some dbname ->
      (try
         let db = get_db dbname in
         let data = B.contents s.pt_data in
           match s.pt_mode with
               Pt_excl ->
                 Bdb.add db s.pt_kname (compress 5 data)
             | Pt_trunc ->
                 Bdb.replace db s.pt_kname (compress 5 data)
             | Pt_append ->
                 let data = try (uncompress (Bdb.find db s.pt_kname)) ^ data
                            with Not_found -> data in
                   Bdb.replace db s.pt_kname (compress 5 data)
       with Bdb.Dbm_error("Entry already exists") -> ()
          | exn -> Printf.printf "Error writing to database: %s: %s: %s\n"
                     dbname s.pt_kname (Printexc.to_string exn))
  | None ->
      (* escape and remove slashes from filename *)
      let fname = string_map
        (fun c -> if c = '/' then "_" else S.make 1 c)
        (String.escaped s.pt_kname) in
      let flags =
        match s.pt_mode with
            Pt_excl -> [Open_wronly; Open_creat; Open_excl; Open_text]
          | Pt_trunc -> [Open_wronly; Open_creat; Open_trunc; Open_text]
          | Pt_append -> [Open_append; Open_creat; Open_text] in
      (try
         let out = open_out_gen flags 0o666 fname in
           output_string out (B.contents s.pt_data);
           close_out out
       with Sys_error msg when (msg = fname ^ ": File exists") -> ()
          | exn -> Printf.printf "Error writing to file: %s: %s\n"
                     fname (Printexc.to_string exn))

let close_stream s =
  if !collecting then prepend c_streams s
  else print_stream s

let printf fmt = Printf.kprintf coll_string fmt
let fprintf s fmt = Printf.kprintf (B.add_string s.pt_data) fmt

let suppress_external_output() = !collecting

type t_output_set = {
  outc_stdout : string;
  outc_streams : t_ptstream list;
}

let set_collect_output() = collecting := true
let get_collect_output() =
  let outset = {
    outc_stdout = B.contents c_stdout;
    outc_streams = !c_streams;
  } in
  B.reset c_stdout;
  c_streams := [];
  collecting := false;
  outset

let print_output out =
  print_string out.outc_stdout; flush stdout;
  List.iter print_stream out.outc_streams

(* I/O for basic types *)

(* Based in part on earlier implementation by Yichen Xie
 * <yxie@cs.stanford.edu> *)

exception Load_error of string
let loaderror msg = raise (Load_error msg)

let load_byte ls =
  int_of_char (ls())

let dump_byte ds b =
  ds (char_of_int b)

let load_bool ls =
  match load_byte ls with
      0x88 -> true
    | 0x66 -> false
    | _ -> loaderror "load_bool"

let dump_bool ds b =
  if b then dump_byte ds 0x88	(* true *)
  else dump_byte ds 0x66	(* false *)

let load_int ls =
  let x =                load_byte ls  in
  let x = (x lsl 8) lor (load_byte ls) in
  let x = (x lsl 8) lor (load_byte ls) in
  let x = (x lsl 8) lor (load_byte ls) in
    if (x land 0x40000000) <> 0 then x lor (~-1 lsl 31) else x

let dump_int ds n =
  for i = 3 downto 0 do
    let x = n lsr (i * 8) in
    let x = x land 0xff in
    dump_byte ds x
  done

let load_int64 ls =
  let x = ref 0L in
  for i = 0 to 7 do
    x := Int64.logor 
      (Int64.shift_left !x 8) 
      (Int64.of_int (load_byte ls))
  done;
  !x

let dump_int64 ds n =
  for i = 7 downto 0 do
    let x = Int64.shift_right_logical n (i * 8) in
    let x = Int64.logand x 0xffL in
    dump_byte ds (Int64.to_int x)
  done

(* For big integers we use a sign-magnitude representation. 
 * Magnitudes use a variable length tagged byte representation. Each byte 
 * contains 7-bit data nibble, with the top bit set if more nibbles are 
 * present. 
 *)
let load_bigint ls =
  let shift = ref 0 in
  let acc = ref zero_big_int in
  let morebytes = ref true in
  while !morebytes do
    let b = load_byte ls in
    morebytes := (b land 0x80) <> 0;
    acc := add_big_int !acc
      (mult_int_big_int (b land 0x7F) (power_int_positive_int 2 !shift));
    shift := !shift + 7
  done;
  let sign = load_bool ls in
  if sign then minus_big_int !acc else !acc

let dump_bigint ds n =
  let maskmod = big_int_of_int 0x80 in
  let sign = (sign_big_int n = ~-1) in
  let m = ref (if sign then minus_big_int n else n) in
  while ge_big_int !m maskmod do
    dump_byte ds ((int_of_big_int (mod_big_int !m maskmod)) lor 0x80);
    m := div_big_int !m maskmod
  done;
  dump_byte ds (int_of_big_int (mod_big_int !m maskmod));
  dump_bool ds sign

let load_string ls =
  let l = load_int ls in
  let s = String.create l in
  for i = 0 to l-1 do
    String.unsafe_set s i (ls())
  done;
  s

let dump_string ds s =
  let len = String.length s in
   dump_int ds len;
   for i = 0 to len-1 do
     ds (String.unsafe_get s i)
   done

let load_float ls = Int64.float_of_bits (load_int64 ls)

let dump_float ds v = dump_int64 ds (Int64.bits_of_float v)

let load_option ls f =
  match load_byte ls with
      0xfe -> None
    | 0xff -> Some (f ls)
    | _ -> loaderror "load_option"

let dump_option ds f = function
    None ->
      dump_byte ds 0xfe
  | Some x ->
      dump_byte ds 0xff;
      f ds x

let load_list ls f =
  let len = load_int ls in
  let res = ref [] in
  for i = 1 to len do
    res := (f ls) :: !res
  done;
  List.rev !res

let dump_list ds f l =
  dump_int ds (List.length l);
  List.iter (f ds) l

let load_array ls f =
  let len = load_int ls in
    Array.init len (fun _ -> f ls)

let dump_array ds f a =
  dump_int ds (Array.length a);
  Array.iter (f ds) a

let load_output ls =
  let stdout = uncompress (load_string ls) in
  let streams = load_list ls
    (fun ls ->
       let where = load_option ls load_string in
       let kname = load_string ls in
       let mode = match load_byte ls with
           0x01 -> Pt_excl
         | 0x02 -> Pt_trunc
         | 0x03 -> Pt_append
         | _ -> loaderror "load_output_mode" in
       let data = uncompress (load_string ls) in
       let databuf = B.create (String.length data) in
       let _ = B.add_string databuf data in
       let res = {
         pt_where = where;
         pt_kname = kname;
         pt_mode = mode;
         pt_data = databuf;
       } in res) in
  let res = {
    outc_stdout = stdout;
    outc_streams = streams;
  } in res

let dump_output ds out =
  dump_string ds (compress 5 out.outc_stdout);
  dump_list ds
    (fun ds s ->
       dump_option ds dump_string s.pt_where;
       dump_string ds s.pt_kname;
       dump_byte ds
         (match s.pt_mode with
              Pt_excl -> 0x01
            | Pt_trunc -> 0x02
            | Pt_append -> 0x03);
       dump_string ds (compress 5 (B.contents s.pt_data))) out.outc_streams

(* Socket streams *)

type t_sock_desc = U.file_descr
type t_sock = {
  ts_desc : U.file_descr;
  ts_inbuf : B.t;
  ts_outbuf : B.t;
  mutable ts_loaded : int; (* length of inbuf we've tried to load from *)
  mutable ts_read : float;
  mutable ts_write : float;
  ts_buflen : int;         (* buffer for data en route to inbuf *)
  ts_buffer : string;
  ts_read_event  : E.event;
  ts_write_event : E.event;
  mutable ts_data_cb : t_sock_data_cb option;
  mutable ts_peerclosed_cb : t_sock_peerclosed_cb;
}
and t_sock_data_cb = (t_sock -> string -> unit)
and t_sock_peerclosed_cb = (t_sock -> unit)
type t_sock_connect_cb = (t_sock -> unit)

exception Socket_closed_by_peer of t_sock

let socket_has_pending_writes sock =
  B.length sock.ts_outbuf > 0

let socket_has_unread_data sock =
  B.length sock.ts_inbuf > sock.ts_loaded

let socket_do_read sock =
  let buflen = sock.ts_buflen in
  let more_to_read = ref true in
    try
      while !more_to_read do
        let nread = U.read sock.ts_desc sock.ts_buffer 0 buflen in
          (* If we read 0 bytes then the connection has been closed by the
           * other end. We would receive EAGAIN if the connection was still
           * up. *)
          if nread = 0 then 
            raise (Socket_closed_by_peer sock) 
          else
            B.add_substring sock.ts_inbuf sock.ts_buffer 0 nread;
            (* If we didn't read a full buffer's worth of data then there's no
             * point trying again. *)
            if nread < buflen then more_to_read := false
      done
    with U.Unix_error (U.EAGAIN,_,_)
       | End_of_file -> ()

let socket_flush_writes sock =
  let len = B.length sock.ts_outbuf in
  if len > 0 then
    let bufstr = (B.contents sock.ts_outbuf) in 
    let written =
      try
        U.write sock.ts_desc bufstr 0 len
      with 
          U.Unix_error (U.EAGAIN, _, _) -> 0 (* We need to block *)
        | U.Unix_error (U.EPIPE, _, _) 
        | U.Unix_error (U.ECONNRESET, _, _)  -> 
          raise (Socket_closed_by_peer sock)
      in
    B.reset sock.ts_outbuf;
    if written < len then
      B.add_substring sock.ts_outbuf bufstr written (len - written); 
      false 
    else
      true

let socket_load sock =
  let loadfn pos =
    let opos = ref pos in
      fun () -> (incr opos; B.nth sock.ts_inbuf (!opos-1)) in
  (* grab all available data off the socket *)
  socket_do_read sock;
  sock.ts_loaded <- B.length sock.ts_inbuf;
  (* return the data only if it is all there *)
  if B.length sock.ts_inbuf >= 4 then
    let readlen = B.length sock.ts_inbuf in
    let reqlen = load_int (loadfn 0) in
      if readlen >= 4 + reqlen then begin
        let res = B.sub sock.ts_inbuf 4 reqlen in
        let rem = B.sub sock.ts_inbuf (reqlen + 4) (readlen - reqlen - 4) in
          B.reset sock.ts_inbuf; B.add_string sock.ts_inbuf rem;
          sock.ts_loaded <- 0;
          sock.ts_read <- sock.ts_read +. (float_of_int (reqlen + 4));
          Some res
      end else None
  else None

let socket_dump sock str =
  let strlen = S.length str in
  dump_int (B.add_char sock.ts_outbuf) strlen;
  B.add_string sock.ts_outbuf str;
  sock.ts_write <- sock.ts_write +. (float_of_int (strlen + 4)) ;
  let allwritten = socket_flush_writes sock in
  if not allwritten then E.add sock.ts_write_event None

let socket_close sock =
  E.del sock.ts_write_event;
  E.del sock.ts_read_event;
  E.unset sock.ts_write_event;
  E.unset sock.ts_read_event;
  B.reset sock.ts_inbuf;
  B.reset sock.ts_outbuf;
  U.close sock.ts_desc

let socket_count_io sock = (sock.ts_read,sock.ts_write)

let socket_read_event sock _ _ = match sock.ts_data_cb with 
    None -> ()
  | Some cb -> 
      (try
         let finished = ref false in
         while not !finished do
           let d = socket_load sock in
           match d with 
               Some msg -> cb sock msg 
             | None     -> finished := true
         done
       with Socket_closed_by_peer _ -> sock.ts_peerclosed_cb sock)

let socket_write_event sock _ _ =
  let allwritten = socket_flush_writes sock in
  if not allwritten then
    E.add sock.ts_write_event None

let socket_create desc =
  let re = E.create () in
  let we = E.create () in
  let sock = {
    ts_desc = desc;
    ts_inbuf = B.create 16;
    ts_outbuf = B.create 16;
    ts_loaded = 0;
    ts_read = 0.;
    ts_write = 0.;
    ts_buflen = 4096;
    ts_buffer = String.create 4096;
    ts_read_event = re;
    ts_write_event = we;
    ts_data_cb = None;
    ts_peerclosed_cb = (fun _ -> ());
  } in 
  U.set_nonblock desc;
  E.set re desc [E.READ] true (socket_read_event sock);
  E.set we desc [E.WRITE] false (socket_write_event sock);
  E.add re None;
  sock

let socket_set_data_cb sock cb =
  sock.ts_data_cb <- Some cb

let socket_set_peerclosed_cb sock cb =
  sock.ts_peerclosed_cb <- cb

let connect_event = E.create () 
let server_socket connect_cb =
  let sock = U.socket U.PF_INET U.SOCK_STREAM 0 in
  let connect_event_handler _ _ = 
    let (csock,_) = U.accept sock in
    connect_cb (socket_create csock) in
    U.bind sock (U.ADDR_INET (U.inet_addr_any, 0));
    U.setsockopt sock U.SO_REUSEADDR true;
    U.set_nonblock sock;
    U.listen sock 200;
    (* inet_addr_any is 0.0.0.0 and kind of useless for printing *)
    let addr = match (U.gethostbyname (U.gethostname())).U.h_addr_list with
        [|addr|] -> addr
      | _ -> U.inet_addr_any in
    E.set connect_event sock [E.READ] true connect_event_handler;
    E.add connect_event None;
    match U.getsockname sock with
        U.ADDR_INET (_,port) -> (sock,addr,port)
      | U.ADDR_UNIX _ -> assert false

let client_socket addr port =
  let sock = U.socket U.PF_INET U.SOCK_STREAM 0 in
    U.connect sock (U.ADDR_INET (addr, port));
    U.set_nonblock sock;
    socket_create sock

exception Writes_completed
let ensure_writes socks timeout =
  let socks_left = ref 0 in
  let writeable_cb _ _ = 
    decr socks_left;
    if !socks_left = 0 then raise Writes_completed in
  List.iter (fun s -> 
      let e = E.create () in
      E.set e s.ts_desc [E.WRITE] false writeable_cb;
      E.add e (Some timeout);
      incr socks_left
    ) socks;
  if !socks_left > 0 then try E.dispatch () with Writes_completed -> ()

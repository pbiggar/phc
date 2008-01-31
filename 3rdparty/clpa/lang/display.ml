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

(* Predicates for generating UI display XML files *)

open Builtin
open Clpautil
open Spec
open Flags

module H = Hashtbl
module V = Vector
module IO = Streamio

(* XML *)

let open_tag out tab name =
  IO.fprintf out "%s<%s>\n" tab name
let close_tag out tab name =
  IO.fprintf out "%s</%s>\n" tab name
let data_tag out tab name contents =
  IO.fprintf out "%s<%s> %s </%s>\n" tab name contents name

let inc tab = tab ^ "  "

let tag_wrap out tab name fn =
  open_tag out tab name;
  fn out (inc tab);
  close_tag out tab name

(* XML structure *)

type link = string * string (* name, text *)

let write_link out tab (name,text) =
  tag_wrap out tab "link" (fun out tab ->
    data_tag out tab "name" name;
    data_tag out tab "text" text)

type lineitem =
    LineStyle of int * string
  | LineText of int * string * string * string * link list

let write_lineitem out tab = function
    LineStyle (line,cssclass) ->
      tag_wrap out tab "linestyle" (fun out tab ->
        data_tag out tab "line" (string_of_int line);
        data_tag out tab "cssclass" cssclass)
  | LineText (line,cssclass,position,text,links) ->
      tag_wrap out tab "linetext" (fun out tab ->
        data_tag out tab "line" (string_of_int line);
        data_tag out tab "cssclass" cssclass;
        data_tag out tab "position" position;
        data_tag out tab "text" text;
        List.iter (write_link out tab) links)

type display = {
  d_name : string;
  d_category : string;
  d_title : string;
  d_function : string;
  d_file : string;
  d_minline : int;
  d_maxline : int;
  d_focusline : int;
  d_lineitems : lineitem list;
}

let debug_display_files = register_debug "display_files"
  "Write error displays as .xml files"

let write_display d replace =
  let mode = if replace then IO.Pt_trunc else IO.Pt_excl in
  let out = if debug_display_files() then
              IO.open_file (d.d_name ^ ".xml") mode
            else IO.open_dbentry "display" d.d_name mode in
  tag_wrap out "" "display" (fun out tab ->
    data_tag out tab "name" d.d_name;
    data_tag out tab "category" d.d_category;
    data_tag out tab "title" d.d_title;
    data_tag out tab "function" d.d_function;
    data_tag out tab "file" d.d_file;
    data_tag out tab "minline" (string_of_int d.d_minline);
    data_tag out tab "maxline" (string_of_int d.d_maxline);
    data_tag out tab "focusline" (string_of_int d.d_focusline);
    List.iter (write_lineitem out tab) d.d_lineitems);
  IO.close_stream out

(* Displays *)

let vt_displaylink = make_type "displaylink" [||]
let sum_displaylink = (vt_displaylink,[
  ("d_link",[|vt_str;vt_str|]);
])

let val2link v =
  let (n,args) = val2sum v in
    if n <> "d_link" then pred_unexpected "Unknown displaylink";
    let name = val2str args.(0) in
    let text = val2str args.(1) in
      (name,text)

let vt_position = make_type "displayposition" [||]
let enum_position = (vt_position,[
  ("left","d_left");
  ("right","d_right");
  ("bottom","d_bottom");
  ("top","d_top");
])

let vt_displayitem = make_type "displayitem" [||]
let sum_displayitem = (vt_displayitem,[
  ("d_line_style",[|vt_int;vt_str|]);
  ("d_line_text",[|vt_int;vt_str;vt_position;vt_str;vt_list vt_displaylink|]);
])

let val2line v =
  let (n,args) = val2sum v in
    if n = "d_line_style" then
      let line = val2sint args.(0) in
      let cssclass = val2str args.(1) in
        LineStyle (line,cssclass)
    else if n = "d_line_text" then
      let line = val2sint args.(0) in
      let cssclass = val2str args.(1) in
      let position = val2enum enum_position args.(2) in
      let text = val2str args.(3) in
      let links = List.map val2link (val2list args.(4)) in
        LineText (line,cssclass,position,text,links)
    else pred_unexpected "Bad Line"

(* displays we've generated and need to write out at exit *)
let displays : (t_val,display*bool) H.t = H.create 10

(* search terms we've generated and need to write out at exit *)
let searches : (string,string list) H.t = H.create 10

let write_info() =
  H.iter (fun _ (d,replace) -> write_display d replace) displays;
  H.iter (fun term names ->
    let out = if debug_display_files() then
                IO.open_file (term ^ ".txt") IO.Pt_append
              else IO.open_dbentry "search" term IO.Pt_append in
    List.iter (fun name -> IO.fprintf out "%s\n" name) names;
    IO.close_stream out) searches

let reset_info() =
  H.clear displays; H.clear searches

(* Display package *)

let add_handlers = ref []

let _ = prepend add_handlers
  (("display_add",[|vt_str;vt_bool;vt_str;vt_str;vt_str;vt_str;
                    vt_int;vt_int;vt_int;vt_list vt_displayitem|]),
   fun (name,args) ->
     let disp = {
       d_name = val2str args.(0);
       d_category = val2str args.(2);
       d_title = val2str args.(3);
       d_function = val2str args.(4);
       d_file = val2str args.(5);
       d_minline = max 1 (val2sint args.(6));
       d_maxline = val2sint args.(7);
       d_focusline = val2sint args.(8);
       d_lineitems = List.map val2line (val2list args.(9));
     } in
     let replace = val2bool args.(1) in
     try let (odisp,oreplace) = H.find displays args.(0) in
       if disp <> odisp || replace <> oreplace then
         pred_unexpected "Display name conflicts with previously added display"
     with Not_found ->
       H.add displays args.(0) (disp,replace))

let _ = prepend add_handlers
  (("search_add",[|vt_str;vt_str|]),
   fun (name,args) ->
     let term = val2str args.(0) in
     let name = val2str args.(1) in
     let old = try H.find searches term with Not_found -> [] in
       if not (List.exists ((=)name) old) then
         H.replace searches term (name::old))

let _ = register_package { empty_package with
  p_name = "display";
  p_writeout = write_info;
  p_reset = reset_info;
  p_add_handlers = !add_handlers;
  p_find_handlers = [];
  p_sumtypes = [sum_displayitem; sum_displaylink; make_enum_sum enum_position];
}

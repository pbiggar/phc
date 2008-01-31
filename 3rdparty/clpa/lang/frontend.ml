(* 
 * Logic program interpreter front-end
 *
 * Authors:
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
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

open Spec
open Clpautil
open Flags
open Ast

module A = Array
module H = Hashtbl
module S = String
module IO = Streamio

(* CLP parsing *)

let stats_clp_sizes = register_stats "clp_sizes"
  "Print number of rules in each .clp file"

(* List of directories that should be searched for source code *)
let source_dirs : string list ref = ref [Filename.current_dir_name]

let find_source_file filename searchdirs =
  let rec try_source_dirs dirs =
    match dirs with 
        []    -> parse_error ("File not found: " ^ filename)
      | d::ds -> let f = Filename.concat d filename in
                 if Sys.file_exists f then f else try_source_dirs ds in
  let len = String.length filename in
  let filename = if filename.[0] = '~' then 
    (Sys.getenv "HOME") ^ (String.sub filename 1 (len - 1)) else filename in
  if Filename.is_relative filename then
    try_source_dirs searchdirs 
  else if Sys.file_exists filename then filename
  else parse_error ("File not found: " ^ filename)

let parse_clp file =
  let parsed : (string,unit) H.t = H.create 10 in
  let counts = Stack.create() in
  Stack.push 0 counts;
  let rec inner_parse (file : string) (extrasearchdirs : string list) =
    let base = Filename.basename file in
    if not (H.mem parsed base) then begin
      H.add parsed base ();
      if stats_clp_sizes() then Stack.push 0 counts;
      let searchdirs = extrasearchdirs @ !source_dirs in
      let file = find_source_file file searchdirs in
      let inch = open_in file in
      let inbuf = Lexing.from_channel inch in
      let oldsfa = change_sfa (file,1) in
      let rules = Specparser.sentences Speclexer.token inbuf in
        ignore (change_sfa oldsfa);
        if stats_clp_sizes() then begin
          let count = Stack.pop counts in
          let tot = List.length rules in
          let sub = tot - count in
            IO.printf "%s: %d (%d) rules\n" file sub tot;
            Stack.push (Stack.pop counts + List.length rules) counts
        end; rules
    end else [] in
    Ast.parse_file := inner_parse;
    List.iter Ast.add_package (get_builtin_packages());
    let analysis = inner_parse file [] in
      analysis
let parse_clp =
  make_track_1 "parse" parse_clp

(* Perform static checking on rules *)
let check_ast rules =
  session_check ();
  if !analysis_session = "" then rule_warning Sfa_none
    "No 'analyze session_name(...)' directive supplied; using empty session.";
  List.map (fun r -> 
    ast_check_rule r; 
    let r' = dont_care_disambiguate_rule r in
    let r'' = scope_infer_rule r' in
    Type_check.type_check r'';
    r''
  ) rules

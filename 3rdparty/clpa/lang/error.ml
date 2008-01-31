(*
 * Authors:
 *   Isil Dillig    <isil@stanford.edu>
 *   Thomas Dillig  <tdillig@stanford.edu>
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

(* Predicates for generating error messages that can be parsed by error2html 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Currently, this supports the following predicates:
 * +error_file(FILE): changes the name of the generated file
 * +error_message(color_on_main_page, line, color_on_code_page, message,
 *    file_name, error_type, linl (or "None")).   
 *)

open Spec 
open Clpautil
open Builtin

module H = Hashtbl
module V = Vector
module IO = Streamio

(* default error file name *)
let filename_ref = ref "error.txt";;

let verbose = ref true;;


let add_handlers = ref []
let find_handlers = ref []

(*{FILE:string, LINE_BEGIN:int, LINE_END:int, BYTE_BEGIN:int, BYTE_END:int, MACRO:int}*)


(* type deref_location_type ::= deref_location{NAME:string, LINE:int} *)

let vt_deref_location = make_type "deref_location_type" [||]
let sum_deref_location = ("deref_location", [|vt_str;vt_int;vt_str|])



let verify_color c =
	match c with
		"blue" -> true;
		| "red" -> true;
		| "green" -> true;
		| "orange" -> true;
		| "violet" -> true;
		| "yellow" -> true;
		| "gray" -> true;
		| _ -> false;
;;

let print_error_msg mcolor line hcolor msg file msg_type link =
 if(not (verify_color mcolor)) || (not (verify_color hcolor))then 
 (
  IO.printf "\tmodule error: illegal color specified\n";
 )
 else
 (
 	let out_channel = open_out_gen [Open_append; Open_creat] 0o666 (!filename_ref) in
 	output_string out_channel (mcolor ^ "\n");
 	output_string out_channel (Big_int.string_of_big_int line);
 	output_string out_channel (" " ^ hcolor ^ " " ^ msg ^ "\n");
 	output_string out_channel (file ^ "\n");
 	output_string out_channel (msg_type ^ "\n");
 	output_string out_channel (link ^ "\n\n");
 	flush out_channel;

	if !verbose then
	(
	

	let a1= ("@" ^ mcolor ^ "\n") in
	IO.printf "%s" a1;
	let a2 = ("@" ^ Big_int.string_of_big_int line) in
	IO.printf "%s" a2;
	let a3 = (" " ^ hcolor ^ " " ^ msg ^ "\n") in
	IO.printf "%s" a3 ;
	let a4 = ("@" ^ file ^ "\n") in
	IO.printf "%s" a4;
	let a5 = ("@" ^ msg_type ^ "\n") in
	IO.printf "%s" a5;
	let a6 = ("@" ^ link ^ "\n@\n") in
	IO.printf "%s"  a6;
		();
	)
 );
 ();
;;

let deref_location2str v=
	let (n,args) = val2sum v in
	if n = "deref_location" then 
	(
		let name = val2str args.(0) in
       		let line = val2sint args.(1) in
		let file = val2str args.(2) in
		name^" ("^(string_of_int line)^":"^file^")";
	)
	else pred_unexpected "Unknown constructor";	
;;

let deref_location_end2str v=
	let (n,args) = val2sum v in
	if n = "deref_location" then 
	(
(*		let name = val2str args.(0) in *)
       		let line = val2sint args.(1) in
		let file = val2str args.(2) in
		" final site of dereference is: ("^(string_of_int line)^":"^file^")";
	)
	else pred_unexpected "Unknown constructor";	
;;

let rec list_to_string l =
	match l with
	[] -> "";
	| hd::tl -> if tl <> [] then  (deref_location2str hd) ^ ", " ^ (list_to_string tl) else (deref_location_end2str hd)  ^ (list_to_string tl);
;;

let rec string_list_to_string l =
	match l with
	[] -> "";
	| hd::tl -> if tl <> [] then  (val2str hd) ^ ", " ^ (string_list_to_string tl) else (val2str hd)  ^ (string_list_to_string tl);
;;

let rec int_list_to_string l =
	match l with
	[] -> "";
	| hd::tl -> if tl <> [] then  (string_of_int (val2sint hd)) ^ ", " ^ (int_list_to_string tl) else(string_of_int (val2sint hd))  ^ (int_list_to_string tl);
;;

let print_error_msg_list mcolor line hcolor msg file msg_type link callstack =
	let callstack_string = list_to_string callstack in
	let full_msg = msg ^ callstack_string  in
  print_error_msg mcolor line hcolor full_msg file msg_type link;
;;

let print_error_msg_check mcolor line hcolor msg file msg_type link check =
  let check_string = int_list_to_string check in
	let full_msg = msg ^ ". This variable is checked for Null at lines: " ^ check_string  in
  print_error_msg mcolor line hcolor full_msg file msg_type link;
;;

let print_error_msg_check_macro mcolor line hcolor msg file msg_type link check mc =
  let check_string = int_list_to_string check in
	let full_msg = msg ^ ". This variable is checked for Null at lines: " ^ check_string ^ 
		" and is dereferenced through macro chain: "^(string_list_to_string mc) in
  print_error_msg mcolor line hcolor full_msg file msg_type link;
;;


let print_error_msg_check_callstack mcolor line hcolor msg file msg_type link gls check callstack =
  let check_string = int_list_to_string check in
  let callstack_string = list_to_string callstack in
	let gls_string = string_list_to_string gls in
	let full_msg = msg ^  gls_string ^ ". This variable is checked for Null at lines: " ^ check_string ^ ", and is dereferenced through call chain: " ^ callstack_string  in
  print_error_msg mcolor line hcolor full_msg file msg_type link;
;;

let _ = prepend add_handlers
	(
	("error_message",[|vt_str;vt_int;vt_str;vt_str;vt_str;vt_str;vt_str|]),
		fun (name,args) ->
		(
			let mcolor = (val2str args.(0)) in
			let line = (val2int args.(1)) in
			let hcolor = (val2str args.(2)) in
			let msg = (val2str args.(3)) in
			let file = (val2str args.(4)) in
			let msg_type = (val2str args.(5)) in
			let link = (val2str args.(6)) in
			print_error_msg mcolor line hcolor msg file msg_type link;
		);
		
	)
;;

let _ = prepend add_handlers
	(
	("error_file",[|vt_str|]),
		fun (name,args) ->
		(
			let file = (val2str args.(0)) in
			filename_ref:=file;
		)
	)
;;



let _ = prepend add_handlers
	(
	("error_message_list",[|vt_str;vt_int;vt_str;vt_str;vt_str;vt_str;vt_str;(vt_list vt_deref_location)|]),
		fun (name,args) ->
		(
			let mcolor = (val2str args.(0)) in
			let line = (val2int args.(1)) in
			let hcolor = (val2str args.(2)) in
			let msg = (val2str args.(3)) in
			let file = (val2str args.(4)) in
			let msg_type = (val2str args.(5)) in
			let link = (val2str args.(6)) in
			let callstack = (val2list args.(7)) in
			print_error_msg_list mcolor line hcolor msg file msg_type link callstack;
		);
		
	)
;;

let _ = prepend add_handlers
	(
	("error_message_check",[|vt_str;vt_int;vt_str;vt_str;vt_str;vt_str;vt_str;(vt_list vt_int)|]),
		fun (name,args) ->
		(
			let mcolor = (val2str args.(0)) in
			let line = (val2int args.(1)) in
			let hcolor = (val2str args.(2)) in
			let msg = (val2str args.(3)) in
			let file = (val2str args.(4)) in
			let msg_type = (val2str args.(5)) in
			let link = (val2str args.(6)) in
			let check = (val2list args.(7)) in
			print_error_msg_check mcolor line hcolor msg file msg_type link check;
		);
		
	)
;;

let _ = prepend add_handlers
	(
	("error_message_check_macro",[|vt_str;vt_int;vt_str;vt_str;vt_str;vt_str;vt_str;(vt_list vt_int);(vt_list vt_str)|]),
		fun (name,args) ->
		(
			let mcolor = (val2str args.(0)) in
			let line = (val2int args.(1)) in
			let hcolor = (val2str args.(2)) in
			let msg = (val2str args.(3)) in
			let file = (val2str args.(4)) in
			let msg_type = (val2str args.(5)) in
			let link = (val2str args.(6)) in
			let check = (val2list args.(7)) in
			let mc = (val2list args.(8)) in
			print_error_msg_check_macro mcolor line hcolor msg file msg_type link check mc;
		);
		
	)
;;

let _ = prepend add_handlers
	(
	("error_message_check_callstack",[|vt_str;vt_int;vt_str;vt_str;vt_str;vt_str;vt_str;(vt_list vt_str);(vt_list vt_int);(vt_list vt_deref_location)|]),
		fun (name,args) ->
		(
			let mcolor = (val2str args.(0)) in
			let line = (val2int args.(1)) in
			let hcolor = (val2str args.(2)) in
			let msg = (val2str args.(3)) in
			let file = (val2str args.(4)) in
			let msg_type = (val2str args.(5)) in
			let link = (val2str args.(6)) in
			let gls = (val2list args.(7)) in
			let check = (val2list args.(8)) in
			let callstack = (val2list args.(9)) in
			print_error_msg_check_callstack mcolor line hcolor msg file msg_type link gls check callstack;
		);
		
	)
;;


let _ = prepend add_handlers
	(
	("get_unique_string",[||]),
		fun (name,args) ->
		(
			let mcolor = (val2str args.(0)) in
			let line = (val2int args.(1)) in
			let hcolor = (val2str args.(2)) in
			let msg = (val2str args.(3)) in
			let file = (val2str args.(4)) in
			let msg_type = (val2str args.(5)) in
			let link = (val2str args.(6)) in
			let gls = (val2list args.(7)) in
			let check = (val2list args.(8)) in
			let callstack = (val2list args.(9)) in
			print_error_msg_check_callstack mcolor line hcolor msg file msg_type link gls check callstack;
		);
		
	)
;;


let reset () = 
  filename_ref:="error.txt";
	();
;;

let _ = register_package { empty_package with
  p_name = "error";
  p_reset = reset;
  p_add_handlers = !add_handlers;
  p_find_handlers = !find_handlers;
}

open Spec
open Clpautil
open Flags
open Builtin
open String
open Char
open List
open Netencoding

let find_handlers = ref []

let encode = fun (str) ->
	let need_encoding = ref false in
	let check = fun (c) ->
		let intval = code c in
			if intval < 32 || intval > 126
				|| c == '>'
				|| c == '<'
				|| c == '&'
			then need_encoding := true in
	(* If any character can't be put straight into XML, base64 encode. *)
	let _ = String.iter check str in
	if !need_encoding then
		Base64.encode str
	else str

let _ = prepend find_handlers
  (("str_to_base64",[|vt_str;vt_str|]),[[|true;false|],[Sk_once]],
   fun (name,args) ->
     let str = val2str args.(0) in
     let result = encode str in
       [name,[|args.(0);str2val result|]])


let _ = register_package { empty_package with
  p_name = "base64";
  p_find_handlers = !find_handlers;
}

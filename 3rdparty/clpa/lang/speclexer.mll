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

(* Lexer for specification files *)

{
  open Spec
  open Specparser

  let tokenize = function
      "import"       -> IMPORT
    | "using"        -> USING
    | "predicate"    -> PREDICATE
    | "session"      -> SESSION
    | "analyze"      -> ANALYZE
    | "type"         -> TYPE
    | "in"           -> IN
    | "out"          -> OUT
    | "order"        -> ORDER
    | "containing"   -> CONTAINING 
    | "all"          -> ALL
    | "some"         -> SOME
    | "assert"       -> ASSERT
    | "implies"      -> IMPLIES
    | "operator"     -> OPERATOR
    | "succeeds"     -> SUCCEEDS
    | "zero"         -> ZERO
    | "once"         -> ONCE
    | "many"         -> MANY
    | str            -> SYMBOL(str)

  (* why does OCaml have escaped but not unescaped? this was copied from:
   * http://permalink.gmane.org/gmane.comp.lang.ocaml.lib.devel/582 *)
  let lexer = lazy (Genlex.make_lexer [])
  let unescaped squot = try
    let tok_stream = Lazy.force lexer (Stream.of_string squot) in
      match Stream.peek tok_stream with
        | Some (Genlex.String s) -> s
        | _ -> assert false
  with _ -> parse_error ("Bad string constant: " ^ squot)

  let advance_line() =
    match cur_sfa () with
      | Sfa_file (file, line) -> ignore (change_sfa (file,line+1))
      | _ -> failwith "Bad SFA"
}

let num = ['0'-'9']
let exp = ['e' 'E'] num+
let lalpha = ['a' - 'z']
let ualpha = ['A' - 'Z']
let alphanum = ['a'-'z' 'A'-'Z' '_' '0'-'9']

rule token = parse
  | [' ' '\t']                      { token lexbuf }
  | '%' [^ '{' '}' '\n'] [^ '\n']*  { token lexbuf }
  | "%{"                            { comments 0 lexbuf }
  | '%'? '\n'                       { advance_line(); token lexbuf }
  | lalpha alphanum* as str         { tokenize str }
  | '#' lalpha alphanum* as str     { HSYMBOL(str) }
  | '$' lalpha alphanum* as str     { DSYMBOL(str) }
  | ualpha alphanum* as str         { VAR(str) }
  | '_' alphanum* as str            { ANYVAR(str) }
  | '\"' ([^ '\n' '\"']|"\\\"")* '\"' as str  { STRING(unescaped str) }
  | ['-']? num+ as num
      { try INT(Big_int.big_int_of_string num)
        with Failure _ -> parse_error "Bad integer" }
  | ['-']? num* '.' num+ exp? as num
      { try FLOAT(float_of_string num)
        with Failure _ -> parse_error "Bad float" }
  | "?-"        { QUERY }
  | ":-"        { TURNSTILE }
  | ":"         { COLON }
  | ";"         { SEMICOLON }
  | ","         { COMMA }
  | "."         { PERIOD }
  | "="         { EQUAL }
  | "\\="       { NOTEQUAL }
  | "::="       { BNFDEF }
  | "|"         { VBAR }
  | "->"        { ARROW }
  | "\\/"       { VEE }
  | "~"         { TILDE }
  | "?"         { QUESTION }
  | "+"         { PLUS }
  | "("         { LPAREN }
  | ")"         { RPAREN }
  | "{"         { LBRACE }
  | "}"         { RBRACE }
  | "["         { LBRACKET }
  | "]"         { RBRACKET }
  | "&&"        { AMPAMP }
  | "||"        { BARBAR }
  | "!"         { BANG }
  | "<"         { LT }
  | "<="        { LE }
  | ">"         { GT }
  | ">="        { GE }
  | "=="        { EQEQ }
  | "!="        { BANGEQ }
  | "-"         { MINUS }
  | "*"         { TIMES }
  | "/"         { DIVIDE }
  | "^"         { CARET }
  | '`' lalpha alphanum* '`' as str     
      { BACKTICKOP(String.sub str 1 ((String.length str) - 2)) }
  | '\'' [^'\'']* '\'' as str     
      { SYMBOL(String.sub str 1 ((String.length str) - 2)) }
  | eof         { EOF }
  | "%}"        { parse_error "Missing comment opening" }
  | '#' ualpha  { parse_error "'#' can only be used with symbols" }
  | '$' ualpha  { parse_error "'$' can only be used with symbols" }
  | _ as c      { parse_error ("Bad token: " ^ (String.make 1 c)) }

and comments level = parse
  | "%{"    { comments (level + 1) lexbuf }
  | "%}"    { if level = 0 then token lexbuf
              else comments (level - 1) lexbuf }
  | '\n'    { advance_line(); comments level lexbuf }
  | eof     { parse_error "Comment not terminated" }
  | _       { comments level lexbuf }

(*
 * Authors:
 *   Brian Hackett  <bhackett@stanford.edu>
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
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

(* Add CIL constructs to the CLP corpus *)

open Printf
open Clpautil
open Spec
open Specio
open Cil
open Cabs2cil
open Builtin
module B = Buffer
module IO = Streamio
module S = String
module H = Hashtbl
open Big_int

(* Session manipulation *)

(* maintain a stack of sessions, all add_logic goes into the one at the top *)
let all_sessions : (t_pred,t_ext_session) Hashtbl.t = Hashtbl.create 10
let session_stack : t_ext_session Stack.t = Stack.create()

let pushs name =
  try Stack.push (Hashtbl.find all_sessions name) session_stack
  with Not_found ->
    let s = new_ext_session name in
      Hashtbl.add all_sessions name s;
      Stack.push s session_stack
let pops() = ignore (Stack.pop session_stack)
let tops() = Stack.top session_stack

let add_top_logic name args = 
  ignore (add_ext_logic (tops()) (rep2pred (name,args)))

(* Spec CIL types and predicates *)

let sumtypes = ref []
let abstypes = ref []
let predicates = ref []
let find_handlers = ref []

(* List of the known contents of each session *)
let sessions : (string, string list) H.t = H.create 50

let add_pred_to_sessions sesslist name = List.iter (fun s ->
    let contents = H.find sessions s in
    H.replace sessions s (name::contents) 
  ) sesslist

let new_sess name =
  let name = "cil_" ^ name in
    H.add sessions name [];
    (name, fun a -> rep2pred (name,[|str2val a|]))

let new_p1 sessions name os a0 = let name = "cil_" ^ name in
  prepend predicates ((name,[|a0|]),os);
  add_pred_to_sessions sessions name;
  fun a0 -> add_top_logic name [|a0|]

let new_p2 sessions name os a0 a1 = let name = "cil_" ^ name in
  prepend predicates ((name,[|a0;a1|]),os);
  add_pred_to_sessions sessions name;
  fun a0 a1 -> add_top_logic  name [|a0;a1|]

let new_p3 sessions name os a0 a1 a2 = let name = "cil_" ^ name in
  prepend predicates ((name,[|a0;a1;a2|]),os);
  add_pred_to_sessions sessions name;
  fun a0 a1 a2 -> add_top_logic name [|a0;a1;a2|]

let new_p4 sessions name os a0 a1 a2 a3 = let name = "cil_" ^ name in
  prepend predicates ((name,[|a0;a1;a2;a3|]),os);
  add_pred_to_sessions sessions name;
  fun a0 a1 a2 a3 -> add_top_logic name [|a0;a1;a2;a3|]

let new_p5 sessions name os a0 a1 a2 a3 a4 = let name = "cil_" ^ name in
  prepend predicates ((name,[|a0;a1;a2;a3;a4|]),os);
  add_pred_to_sessions sessions name;
  fun a0 a1 a2 a3 a4 -> add_top_logic name [|a0;a1;a2;a3;a4|]

let new_p6 sessions name os a0 a1 a2 a3 a4 a5 = let name = "cil_" ^ name in
  prepend predicates ((name,[|a0;a1;a2;a3;a4;a5|]),os);
  add_pred_to_sessions sessions name;
  fun a0 a1 a2 a3 a4 a5-> add_top_logic name [|a0;a1;a2;a3;a4;a5|]

(* make the type as well as a factory predicate handler for making new ones *)
let new_abstype name =
  let typ = make_type ("c_" ^ name) [||] in
    prepend abstypes typ;
    prepend find_handlers 
      (("cil_make_" ^ name,[|vt_any;vt_any;typ|]),
      [[|true;true;false|],[Sk_once]],
       fun (pname,args) ->
         if not (is_val_const args.(0)) || not (is_val_const args.(1)) then
           pred_unexpected "Arguments not const";
         let res = sum2val ("c_" ^ name,[|args.(0);args.(1)|]) in
           [pname,[|args.(0);args.(1);res|]]);
    typ

let new_sumtype name sum =
  let typ = make_type name [||] in
    prepend sumtypes (typ,sum);
    typ

let new_enumtype name enum =
  let typ = make_type name [||] in
    prepend sumtypes (make_enum_sum (typ,enum));
    (typ,enum2val (typ,enum))

(* Session functions *)

let (s_body, mk_s_body) = new_sess "body"
let (s_glob, mk_s_glob) = new_sess "glob"
let (s_init, mk_s_init) = new_sess "init"
let (s_comp, mk_s_comp) = new_sess "comp"
let (s_enum, mk_s_enum) = new_sess "enum"
let (s_type, mk_s_type) = new_sess "type"

(* Relation predicates *)

(* special session-wide relations *)
let mk_curfn = new_p1 [s_body] "curfn" [] vt_str

(* CIL node types *)
let vt_type = new_abstype "type"
let vt_comp = new_abstype "comp"
let vt_field = new_abstype "field"
let vt_enum = new_abstype "enum"
let vt_var = new_abstype "var"
let vt_init = new_abstype "init"
let vt_exp = new_abstype "exp"
let vt_const = new_abstype "const"
let vt_lval = new_abstype "lval"
let vt_offset = new_abstype "offset"
let vt_fundec = new_abstype "fundec"
let vt_block = new_abstype "block"
let vt_stmt = new_abstype "stmt"
let vt_instr = new_abstype "instr"
let vt_attr = new_abstype "attr"
let vt_attr_arg = new_abstype "attr_arg"
let vt_macro = new_abstype "macro"

(* CIL integer kinds *)
let (vt_ikind,ikind2val) = new_enumtype "ikind" [
  (IChar,"ichar");
  (ISChar,"ischar");
  (IUChar,"iuchar");
  (IInt,"iint");
  (IUInt,"iuint");
  (IShort,"ishort");
  (IUShort,"iushort");
  (ILong,"ilong");
  (IULong,"iulong");
  (ILongLong,"ilonglong");
  (IULongLong,"iulonglong");
]

(* CIL float kinds *)
let (vt_fkind,fkind2val) = new_enumtype "fkind" [
  (FFloat,"ffloat");
  (FDouble,"fdouble");
  (FLongDouble,"flongdouble");
]

(* CIL unops *)
let (vt_unop,unop2val) = new_enumtype "unop" [
  (Neg,"u_neg");
  (BNot,"u_bnot");
  (LNot,"u_lnot");
]

(* CIL binops *)
let (vt_binop,binop2val) = new_enumtype "binop" [
  (PlusA,"b_plusa");
  (PlusPI,"b_pluspi");
  (IndexPI,"b_indexpi");
  (MinusA,"b_minusa");
  (MinusPI,"b_minuspi");
  (MinusPP,"b_minuspp");
  (Mult,"b_mult");
  (Div,"b_div");
  (Mod,"b_mod");
  (Shiftlt,"b_shiftlt");
  (Shiftrt,"b_shiftrt");
  (Lt,"b_lt");
  (Gt,"b_gt");
  (Le,"b_le");
  (Ge,"b_ge");
  (Eq,"b_eq");
  (Ne,"b_ne");
  (BAnd,"b_band");
  (BXor,"b_bxor");
  (BOr,"b_bor");
  (LAnd,"b_land");
  (LOr,"b_lor");
]

(* most predicates can appear in any of the CIL sessions *)
let all_sess = [s_body;s_comp;s_enum;s_glob;s_init;s_type]

(* CIL types *)

let mk_type_void =
  new_p1 all_sess "type_void" [] vt_type
let mk_type_int =
  new_p2 all_sess "type_int" [] vt_type vt_ikind
let mk_type_float =
  new_p2 all_sess "type_float" [] vt_type vt_fkind
let mk_type_ptr =
  new_p2 all_sess "type_ptr" [0,1] vt_type vt_type
let mk_type_array =
  new_p3 all_sess "type_array" [0,1] vt_type vt_type vt_exp
let mk_type_func =
  new_p3 all_sess "type_func" [0,1] vt_type vt_type vt_bool
let mk_type_func_arg =
  new_p4 all_sess "type_func_arg" [0,3] vt_type vt_int vt_str vt_type
let mk_type_func_arg_attr =
  new_p3 all_sess "type_func_arg_attr" [] vt_type vt_int vt_attr
let mk_type_named =
  new_p3 all_sess "type_named" [0,2] vt_type vt_str vt_type
let mk_type_comp =
  new_p2 all_sess "type_comp" [] vt_type vt_str
let mk_type_enum =
  new_p2 all_sess "type_enum" [] vt_type vt_str
let mk_type_valist =
  new_p1 all_sess "type_valist" [] vt_type
let mk_type_x_attr =
  new_p2 all_sess "type_x_attr" [] vt_type vt_attr
let mk_type_x_bytes =
  new_p2 all_sess "type_x_bytes" [] vt_type vt_int
let mk_type_location =
  new_p3 [s_type] "type_location" [] vt_type vt_str vt_int

(* CIL structs/unions *)
let mk_comp_name =
  new_p3 [s_comp] "comp_name" [] vt_comp vt_str vt_bool
let mk_comp_field =
  new_p3 [s_comp] "comp_field" [] vt_comp vt_int vt_field
let mk_comp_attr =
  new_p2 [s_comp] "comp_attr" [] vt_comp vt_attr
let mk_comp_bytes =
  new_p2 [s_comp] "comp_bytes" [] vt_comp vt_int
let mk_comp_location =
  new_p3 [s_comp] "comp_location" [] vt_comp vt_str vt_int
let mk_comp_end_location =
  new_p3 [s_comp] "comp_end_location" [] vt_comp vt_str vt_int
let mk_field_name =
  new_p5 all_sess "field_name" [] vt_field vt_str vt_type vt_int vt_int
let mk_field_attr =
  new_p2 all_sess "field_attr" [] vt_field vt_attr

(* CIL enums *)
let mk_enum_name =
  new_p2 [s_enum] "enum_name" [] vt_enum vt_str
let mk_enum_item =
  new_p4 [s_enum] "enum_item" [] vt_enum vt_int vt_str vt_exp
let mk_enum_attr =
  new_p2 [s_enum] "enum_attr" [] vt_enum vt_attr
let mk_enum_location =
  new_p3 [s_enum] "enum_location" [] vt_enum vt_str vt_int
let mk_enum_end_location =
  new_p3 [s_enum] "enum_end_location" [] vt_enum vt_str vt_int

(* CIL variables *)
let mk_var_name =
  new_p3 all_sess "var_name" [] vt_var vt_str vt_type
let mk_var_global =
  new_p1 all_sess "var_global" [] vt_var
let mk_var_inline =
  new_p1 all_sess "var_inline" [] vt_var
let mk_var_static =
  new_p1 all_sess "var_static" [] vt_var
let mk_var_register =
  new_p1 all_sess "var_register" [] vt_var
let mk_var_init =
  new_p2 [s_init] "var_init" [] vt_var vt_init
let mk_var_attr =
  new_p2 all_sess "var_attr" [] vt_var vt_attr
let mk_var_location =
  new_p3 [s_glob] "var_location" [] vt_var vt_str vt_int

(* CIL static initializers *)
let mk_init_single =
  new_p2 [s_init] "init_single" [0,1] vt_init vt_exp
let mk_init_cmpnd_type =
  new_p2 [s_init] "init_cmpnd_type" [] vt_init vt_type
let mk_init_cmpnd_field =
  new_p3 [s_init] "init_cmpnd_field" [0,2] vt_init vt_field vt_init
let mk_init_cmpnd_index =
  new_p3 [s_init] "init_cmpnd_index" [0,1;0,2] vt_init vt_exp vt_init

(* CIL expressions *)
let mk_exp_const =
  new_p2 all_sess "exp_const" [] vt_exp vt_const
let mk_exp_lval =
  new_p2 all_sess "exp_lval" [0,1] vt_exp vt_lval
let mk_exp_sizeof =
  new_p2 all_sess "exp_sizeof" [] vt_exp vt_type
let mk_exp_sizeofe =
  new_p2 all_sess "exp_sizeofe" [] vt_exp vt_exp
let mk_exp_sizeofstr =
  new_p2 all_sess "exp_sizeofstr" [] vt_exp vt_str
let mk_exp_alignof =
  new_p2 all_sess "exp_alignof" [] vt_exp vt_type
let mk_exp_alignofe =
  new_p2 all_sess "exp_alignofe" [] vt_exp vt_exp
let mk_exp_unop =
  new_p4 all_sess "exp_unop" [0,2] vt_exp vt_unop vt_exp vt_type
let mk_exp_binop =
  new_p5 all_sess "exp_binop" [0,2;0,3] vt_exp vt_binop vt_exp vt_exp vt_type
let mk_exp_cast =
  new_p3 all_sess "exp_cast" [0,1] vt_exp vt_exp vt_type
let mk_exp_addr =
  new_p2 all_sess "exp_addr" [0,1] vt_exp vt_lval
let mk_exp_start =
  new_p2 all_sess "exp_start" [0,1] vt_exp vt_lval
let mk_exp_x_intval =
  new_p2 all_sess "exp_x_intval" [] vt_exp vt_int
let mk_exp_x_location =
  new_p6 all_sess "exp_x_location" [] vt_exp vt_str vt_int vt_int vt_int vt_int
let mk_exp_x_macro =
  new_p2 all_sess "exp_x_macro" [] vt_exp vt_macro

(* CIL constants *)
let mk_const_int =
  new_p3 all_sess "const_int" [] vt_const vt_ikind vt_int
let mk_const_str =
  new_p2 all_sess "const_str" [] vt_const vt_str
let mk_const_wstr =
  new_p2 all_sess "const_wstr" [] vt_const vt_int
let mk_const_char =
  new_p2 all_sess "const_char" [] vt_const vt_int
let mk_const_real =
  new_p3 all_sess "const_real" [] vt_const vt_fkind vt_flt

(* CIL lvalues *)
let mk_lval_var =
  new_p3 all_sess "lval_var" [0,2] vt_lval vt_var vt_offset
let mk_lval_mem =
  new_p3 all_sess "lval_mem" [0,1;0,2] vt_lval vt_exp vt_offset
let mk_off_none =
  new_p1 all_sess "off_none" [] vt_offset
let mk_off_field =
  new_p3 all_sess "off_field" [0,2] vt_offset vt_field vt_offset
let mk_off_index =
  new_p3 all_sess "off_index" [0,1;0,2] vt_offset vt_exp vt_offset

(* CIL function definitions *)
let mk_fundec_name =
  new_p3 [s_body] "fundec_name" [] vt_fundec vt_var vt_block
let mk_fundec_formal =
  new_p3 [s_body] "fundec_formal" [] vt_fundec vt_int vt_var
let mk_fundec_local =
  new_p2 [s_body] "fundec_local" [] vt_fundec vt_var
let mk_fundec_location =
  new_p3 [s_body] "fundec_location" [] vt_fundec vt_str vt_int
let mk_fundec_end_location =
  new_p3 [s_body] "fundec_end_location" [] vt_fundec vt_str vt_int

(* sumtype for CIL switch statement cases *)
let vt_cases = new_sumtype "c_cases" [
  ("case",[|vt_exp;vt_stmt|]);
  ("default",[|vt_stmt|]);
]

(* CIL blocks *)
let mk_block_stmts =
  new_p2 [s_body] "block_stmts" [] vt_block (vt_list vt_stmt)
let mk_block_attr =
  new_p2 [s_body] "block_attr" [] vt_block vt_attr

(* CIL statements *)
let mk_stmt_instrs =
  new_p2 [s_body] "stmt_instrs" [] vt_stmt (vt_list vt_instr)
let mk_stmt_return =
  new_p1 [s_body] "stmt_return" [] vt_stmt
let mk_stmt_return_exp =
  new_p2 [s_body] "stmt_return_exp" [] vt_stmt vt_exp
let mk_stmt_goto =
  new_p2 [s_body] "stmt_goto" [] vt_stmt vt_stmt
let mk_stmt_break =
  new_p1 [s_body] "stmt_break" [] vt_stmt
let mk_stmt_continue =
  new_p1 [s_body] "stmt_continue" [] vt_stmt
let mk_stmt_if =
  new_p4 [s_body] "stmt_if" [] vt_stmt vt_exp vt_block vt_block
let mk_stmt_switch =
  new_p4 [s_body] "stmt_switch" [] vt_stmt vt_exp vt_block (vt_list vt_cases)
let mk_stmt_loop =
  new_p2 [s_body] "stmt_loop" [] vt_stmt vt_block
let mk_stmt_block =
  new_p2 [s_body] "stmt_block" [] vt_stmt vt_block
let mk_stmt_tryfinally =
  new_p1 [s_body] "stmt_tryfinally" [] vt_stmt
let mk_stmt_tryexcept =
  new_p1 [s_body] "stmt_tryexcept" [] vt_stmt
let mk_stmt_x_location =
  new_p3 [s_body] "stmt_x_location" [] vt_stmt vt_str vt_int

(* CIL instructions *)
let mk_instr_set =
  new_p3 [s_body] "instr_set" [] vt_instr vt_lval vt_exp
let mk_instr_call =
  new_p2 [s_body] "instr_call" [] vt_instr vt_exp
let mk_instr_call_ret =
  new_p2 [s_body] "instr_call_ret" [] vt_instr vt_lval
let mk_instr_call_arg =
  new_p3 [s_body] "instr_call_arg" [] vt_instr vt_int vt_exp
let mk_instr_asm =
  new_p2 [s_body] "instr_asm" [] vt_instr (vt_list vt_str)
let mk_instr_asm_out =
  new_p5 [s_body] "instr_asm_out" [] vt_instr vt_int (vt_maybe vt_str) vt_str vt_lval
let mk_instr_asm_in =
  new_p5 [s_body] "instr_asm_in" [] vt_instr vt_int (vt_maybe vt_str) vt_str vt_exp
let mk_instr_asm_clobber =
  new_p2 [s_body] "instr_asm_clobber" [] vt_instr vt_str
let mk_instr_asm_attr =
  new_p2 [s_body] "instr_asm_attr" [] vt_instr vt_attr
let mk_instr_x_location =
  new_p3 [s_body] "instr_x_location" [] vt_instr vt_str vt_int

(* CIL attributes *)
let mk_attr_name =
  new_p2 all_sess "attr_name" [] vt_attr vt_str
let mk_attr_arg =
  new_p3 all_sess "attr_arg" [] vt_attr vt_int vt_attr_arg
let mk_attr_arg_int =
  new_p2 all_sess "attr_arg_int" [] vt_attr_arg vt_int
let mk_attr_arg_str =
  new_p2 all_sess "attr_arg_str" [] vt_attr_arg vt_str
let mk_attr_arg_cons =
  new_p2 all_sess "attr_arg_cons" [] vt_attr_arg vt_attr
let mk_attr_arg_sizeof =
  new_p2 all_sess "attr_arg_sizeof" [] vt_attr_arg vt_type
let mk_attr_arg_sizeofe =
  new_p2 all_sess "attr_arg_sizeofe" [] vt_attr_arg vt_attr_arg
let mk_attr_arg_alignof =
  new_p2 all_sess "attr_arg_alignof" [] vt_attr_arg vt_type
let mk_attr_arg_alignofe =
  new_p2 all_sess "attr_arg_alignofe" [] vt_attr_arg vt_attr_arg
let mk_attr_arg_unop =
  new_p3 all_sess "attr_arg_unop" [] vt_attr_arg vt_unop vt_attr_arg
let mk_attr_arg_binop =
  new_p4 all_sess "attr_arg_binop" [] vt_attr_arg vt_binop vt_attr_arg vt_attr_arg
let mk_attr_arg_dot =
  new_p3 all_sess "attr_arg_dot" [] vt_attr_arg vt_attr_arg vt_str

(* CIL macro extensions *)
let mk_macro_builtin =
  new_p1 all_sess "macro_builtin" [] vt_macro
let mk_macro_ident =
  new_p2 all_sess "macro_ident" [] vt_macro vt_str
let mk_macro_func =
  new_p2 all_sess "macro_func" [] vt_macro vt_str
let mk_macro_func_arg =
  new_p4 all_sess "macro_func_arg" [] vt_macro vt_int vt_str vt_str
let mk_macro_x_name =
  new_p2 all_sess "macro_x_name" [] vt_macro vt_str
let mk_macro_x_location =
  new_p5 all_sess "macro_x_location" [] vt_macro vt_str vt_int vt_int vt_int
let mk_macro_x_parent =
  new_p2 all_sess "macro_x_parent" [] vt_macro vt_macro

(* Predicates not created by the translation process but still added to
 * the CIL sessions, so they need to be defined here *)
let _ = new_p1 [s_body] "var_return" [] vt_var
let _ = new_p1 [s_body] "var_temporary" [] vt_var
let _ = new_p1 [s_body] "var_local" [] vt_var
let _ = new_p1 [s_body] "var_formal" [] vt_var

(* Process edge dependencies *)

let process_edges : (t_pred_str * t_pred_str) list ref = ref []
let add_process_edge ps pt = process_edges := (ps,pt)::!process_edges

(* CIL Processing *)

let get_id (base,num) = str2val (base ^ "#" ^ (string_of_int num))
let next_id (base,numref) = incr numref; get_id (base,!numref)

(* roots are used to generate unique IDs for the components of a tree. *)
let root_id name = (get_id (name,0), (name, ref 0))

(* prefix to omit from file names *)
let omit_prefix = ref ""
let setOmitPrefix = (:=) omit_prefix

let replace_prefix file =
  let flen = S.length file in
  let olen = S.length !omit_prefix in
    if flen >= olen && S.sub file 0 olen = !omit_prefix then
      S.sub file olen (flen - olen)
    else file

let mk_location mk_fn loc =
  mk_fn (str2val (replace_prefix loc.file)) (sint2val loc.line)

let cil_intconst_to_intval i k =
  let msk = Int64.sub (Int64.shift_left Int64.one 30) Int64.one in
  let high = Int64.to_int (Int64.shift_right_logical i 60) in
  let mid = Int64.to_int (Int64.logand (Int64.shift_right_logical i 30) msk) in
  let low = Int64.to_int (Int64.logand i msk) in
  let a = 
    add_big_int (add_big_int
      (mult_int_big_int high (power_int_positive_int 2 60))
      (mult_int_big_int mid (power_int_positive_int 2 30)))
      (big_int_of_int low) in
  (* Watch out for large negative integers that are actually positive due
   * to ML's Int64 type being signed *)
  if i < Int64.zero && isSigned k then
    (* Subtract from 2^64 to get the absolute value, and then negate it *)
    minus_big_int (sub_big_int (power_int_positive_int 2 64) a)
  else
    a

(* keep track of macros added to avoid wasting work with duplicate adds *)
let macros_added : (int,unit) Hashtbl.t = Hashtbl.create 10

let rec get_cil_macro id =
  let idv = get_id ("m",id) in
  if not (Hashtbl.mem macros_added id) then begin
    Hashtbl.add macros_added id ();
    let m = Inthash.find macro_table_by_id id in
      (match m.macro_type with
	   Function_macro func ->
             mk_macro_func idv (str2val func.function_macro_def);
             list_iteri (fun i (f,a) ->
                 mk_macro_func_arg idv (sint2val i) (str2val f) (str2val a))
               func.function_macro_args
         | Id_macro ident ->
             mk_macro_ident idv (str2val ident.id_macro_def)
         | Builtin_macro ->
             mk_macro_builtin idv);
      mk_macro_x_name idv (str2val m.macro_name);
      mk_macro_x_location idv
        (str2val (replace_prefix m.macro_file))
        (sint2val (Int32.to_int m.macro_line))
        (sint2val m.macro_begin) (sint2val m.macro_end);
      (match m.macro_parents with
           par::_ when par <> -1 -> mk_macro_x_parent idv (get_cil_macro par)
         | _ -> ())
  end; idv

let rec do_cil_global = function
    GType(ti,l) -> if ti.tname <> "" then ignore (get_cil_typeinfo ti l)
  | GCompTag(ci,l,el) -> ignore (get_cil_compinfo ci l el)
  | GEnumTag(ei,l,el) -> ignore (get_cil_enuminfo ei l el)
  | GVar(vi,ii,l) ->  ignore (get_cil_varinfo vi true ii.init (Some l))
  | GFun(fn,l,el) ->  ignore (get_cil_fundec fn l el)
  | _ -> ()

and get_cil_attr idr (Attr(name,params)) =
  let idv = next_id idr in
    mk_attr_name idv (str2val name);
    list_iteri (fun i a ->
      mk_attr_arg idv (sint2val i) (get_cil_attrparam idr a)) params;
    idv

and get_cil_attrparam idr param =
  let idv = next_id idr in
  let _ = match param with
      AInt n ->       mk_attr_arg_int idv (sint2val n)
    | AStr s ->       mk_attr_arg_str idv (str2val s)
    | ACons (n,a) ->  mk_attr_arg_cons idv (get_cil_attr idr (Attr(n,a)))
    | ASizeOf t ->    mk_attr_arg_sizeof idv (get_cil_typ idr t)
    | ASizeOfE p ->   mk_attr_arg_sizeofe idv (get_cil_attrparam idr p);
    | AAlignOf t ->   mk_attr_arg_alignof idv (get_cil_typ idr t)
    | AAlignOfE p ->  mk_attr_arg_alignofe idv (get_cil_attrparam idr p)
    | AUnOp (op,p) ->
        mk_attr_arg_unop idv (unop2val op) (get_cil_attrparam idr p)
    | ABinOp (op,p0,p1) ->
        mk_attr_arg_binop idv (binop2val op)
          (get_cil_attrparam idr p0) (get_cil_attrparam idr p1)
    | ADot (p,s) ->  mk_attr_arg_dot idv (get_cil_attrparam idr p) (str2val s)
    | _ -> () in
  idv

and mk_attrs idr mk_fn = List.iter (o mk_fn (get_cil_attr idr))

and get_cil_typ idr typ =
  let idv = next_id idr in
  let attrs = match typ with
      TVoid attrs ->        mk_type_void idv; attrs
    | TInt (op,attrs) ->    mk_type_int idv (ikind2val op); attrs
    | TFloat (op,attrs) ->  mk_type_float idv (fkind2val op); attrs
    | TPtr (typ,attrs) ->   mk_type_ptr idv (get_cil_typ idr typ); attrs
    | TArray (typ,eo,attrs) ->
        let lene = (match eo with
            Some e -> e
          | None -> Const (CInt64 (Int64.zero,IInt,None), unknownExpLoc )) in
        mk_type_array idv (get_cil_typ idr typ) (get_cil_exp idr lene); attrs
    | TFun (rettyp,argso,varargs,attrs) ->
        (match argso with
             Some args ->
               list_iteri (fun i (x,typ,attrs) ->
                 mk_type_func_arg idv
                   (sint2val i) (str2val x) (get_cil_typ idr typ);
                 mk_attrs idr
                   (mk_type_func_arg_attr idv (sint2val i)) attrs) args
           | None -> ());
        mk_type_func idv (get_cil_typ idr rettyp) (bool2val varargs); attrs
    | TNamed (ti, attrs) ->
        mk_type_named idv (str2val ti.tname) (get_cil_typ idr ti.ttype); attrs
    | TComp (ci, attrs) ->       mk_type_comp idv (str2val ci.cname); attrs
    | TEnum (ei, attrs) ->       mk_type_enum idv (str2val ei.ename); attrs
    | TBuiltin_va_list attrs ->  mk_type_valist idv; attrs in
  mk_attrs idr (mk_type_x_attr idv) attrs;
  (try match sizeOf typ unknownExpLoc with
       Const (CInt64 (n,_,_), _) ->
         mk_type_x_bytes idv (sint2val (Int64.to_int n))
     | _ -> ()
   with SizeOfError _ -> ());
  idv

and get_cil_typeinfo ti loc =
  let (idv,idr) = root_id ("type:" ^ ti.tname) in
    pushs (mk_s_type ti.tname);
    mk_type_named idv (str2val ti.tname) (get_cil_typ idr ti.ttype);
    mk_location (mk_type_location idv) loc;
    pops();
    idv

and get_cil_compinfo ci loc endloc =
  let (idv,idr) = root_id ("comp:" ^ ci.cname) in
    pushs (mk_s_comp ci.cname);
    mk_comp_name idv (str2val ci.cname) (bool2val ci.cstruct);
    list_iteri (fun i fld ->
      mk_comp_field idv (sint2val i) (get_cil_fieldinfo fld)) ci.cfields;
    mk_attrs idr (mk_comp_attr idv) ci.cattr;
    (try match sizeOf (TComp (ci,[])) unknownExpLoc with
         Const (CInt64 (n,_,_), _) ->
           mk_comp_bytes idv (sint2val (Int64.to_int n))
       | _ -> ()
     with SizeOfError _ -> ());
    mk_location (mk_comp_location idv) loc;
    mk_location (mk_comp_end_location idv) endloc;
    pops();
    idv

and get_cil_fieldinfo fi =
  (* use comp/field name in ID to promote reuse *)
  let (idv,idr) = root_id ("comp:" ^ fi.fcomp.cname ^ "." ^ fi.fname) in
    let (s,w) = try bitsOffset (TComp(fi.fcomp,[])) (Field(fi,NoOffset))
                with SizeOfError _ -> (0,0) in
    mk_field_name idv (str2val fi.fname) (get_cil_typ idr fi.ftype)
      (sint2val s) (sint2val w);
    mk_attrs idr (mk_field_attr idv) fi.fattr;
    idv

and get_cil_enuminfo ei loc endloc =
  let (idv,idr) = root_id ("enum:" ^ ei.ename) in
    pushs (mk_s_enum ei.ename);
    mk_enum_name idv (str2val ei.ename);
    list_iteri (fun i (x,e,_) ->
      mk_enum_item idv (str2val x) (get_cil_exp idr e)) ei.eitems;
    mk_attrs idr (mk_enum_attr idv) ei.eattr;
    mk_location (mk_enum_location idv) loc;
    mk_location (mk_enum_end_location idv) endloc;
    pops();
    idv

and get_cil_varinfo vi doglobal iio loco =
  (* use variable name in ID to promote reuse *)
  let root = if vi.vglob then "gvar" else "var" in
  let (idv,idr) = root_id (root ^ ":" ^ vi.vname) in
    (if doglobal then pushs (mk_s_glob vi.vname));
    mk_var_name idv (str2val vi.vname) (get_cil_typ idr vi.vtype);
    (if vi.vglob then mk_var_global idv);
    (if vi.vinline then mk_var_inline idv);
    (match vi.vstorage with
         Static -> mk_var_static idv
       | Register -> mk_var_register idv
       | _ -> ());
    mk_attrs idr (mk_var_attr idv) vi.vattr;
    (match loco with
         Some loc -> mk_location (mk_var_location idv) loc
       | None -> ());
    (if doglobal then pops());
    (match iio with
         Some ii ->
           pushs (mk_s_init vi.vname);
           mk_var_init idv (get_cil_initinfo idr ii);
           pops()
       | None -> ());
    idv

and get_cil_initinfo idr ii =
  let idv = next_id idr in
  let _ = match ii with
       SingleInit exp -> mk_init_single idv (get_cil_exp idr exp)
     | CompoundInit (typ,inits) ->
         mk_init_cmpnd_type idv (get_cil_typ idr typ);
         List.iter (function
             (Field(fi,NoOffset),ii) ->
               mk_init_cmpnd_field idv
                 (get_cil_fieldinfo fi) (get_cil_initinfo idr ii)
           | (Index(exp,NoOffset),ii) ->
               mk_init_cmpnd_index idv
                 (get_cil_exp idr exp) (get_cil_initinfo idr ii)
           | _ -> IO.printf "WARNING: Bad CompoundInit\n") inits in
  idv

and get_cil_exp idr exp =
  let idv = next_id idr in
  let loc = getExpLoc exp in
  let _ = match exp with
      Const (c, loc) -> 
	mk_exp_const idv (get_cil_constant idr c);
    | Lval (lv, loc) ->  
	mk_exp_lval idv (get_cil_lval idr lv)
    | SizeOf (typ, loc) ->
	mk_exp_sizeof idv (get_cil_typ idr typ)
    | SizeOfE (exp, loc) ->   
	mk_exp_sizeofe idv (get_cil_exp idr exp)
    | SizeOfStr (str, loc) ->  
	mk_exp_sizeofstr idv (str2val str)
    | AlignOf (typ, loc) ->   
	mk_exp_alignof idv (get_cil_typ idr typ)
    | AlignOfE (exp, loc) ->
	mk_exp_alignofe idv (get_cil_exp idr exp)
    | UnOp (op,exp,typ, loc) ->
        mk_exp_unop idv (unop2val op)
          (get_cil_exp idr exp) (get_cil_typ idr typ)
    | BinOp (op,exp0,exp1,typ, loc) ->
        mk_exp_binop idv (binop2val op)
          (get_cil_exp idr exp0) (get_cil_exp idr exp1) (get_cil_typ idr typ)
    | CastE (typ,exp, loc) ->
        mk_exp_cast idv (get_cil_exp idr exp) (get_cil_typ idr typ)
    | AddrOf (lv, loc) -> 
	mk_exp_addr idv (get_cil_lval idr lv)
    | StartOf (lv, loc) -> 
	mk_exp_start idv (get_cil_lval idr lv) in
  let _ = match constFold true exp with
      Const (CInt64 (n,k,_), _) ->
        mk_exp_x_intval idv (int2val (cil_intconst_to_intval n k))
    | _ -> () in
  mk_exp_x_location idv (str2val (replace_prefix loc.exp_file)) 
    (sint2val (fst loc.exp_line_range)) (sint2val (snd loc.exp_line_range))
    (sint2val (fst loc.exp_byte_range)) (sint2val (snd loc.exp_byte_range));
  if loc.exp_macro_id <> -1 then
    mk_exp_x_macro idv (get_cil_macro loc.exp_macro_id);
  idv

and get_cil_constant idr cv =
  let idv = next_id idr in
  let _ = match cv with
      CInt64 (n,k,_) -> mk_const_int idv (ikind2val k) 
                                         (int2val (cil_intconst_to_intval n k))
    | CStr str ->       mk_const_str idv (str2val str)
    | CWStr wstr ->     mk_const_wstr idv (sint2val (List.length wstr))
    | CChr c ->         mk_const_char idv (sint2val (Char.code c))
    | CReal (n,k,_) ->  mk_const_real idv (fkind2val k) (flt2val n)
    | CEnum (_,_,_) ->  failwith "Unexpected CEnum in CIL tree" in
  idv

and get_cil_lval idr (host,off) =
  let idv = next_id idr in
  let rec get_offset off =
    let idv = next_id idr in
    let _ = match off with
        NoOffset -> mk_off_none idv
      | Field (fi,noff) ->
          mk_off_field idv (get_cil_fieldinfo fi) (get_offset noff)
      | Index (exp,noff) ->
          mk_off_index idv (get_cil_exp idr exp) (get_offset noff) in
    idv in
  let _ = match host with
      Var vi ->
        mk_lval_var idv (get_cil_varinfo vi false None None) (get_offset off)
    | Mem exp ->
        mk_lval_mem idv (get_cil_exp idr exp) (get_offset off) in
  idv

and get_cil_fundec fn loc endloc =
  (* set sids for each statement cuz we don't computeCFGInfo *)
  let sid_ref = ref 0 in
  let rec set_sids stmt =
    stmt.sid <- !sid_ref; incr sid_ref;
    match stmt.skind with
        Switch(_,blk,_,_)
      | Loop(blk,_,_,_)
      | Block blk ->
          set_blk_sids blk
      | If(_,trueblk,falseblk,_) ->
          set_blk_sids trueblk; set_blk_sids falseblk
      | _ -> ()
  and set_blk_sids blk = List.iter set_sids blk.bstmts in
  let _ = set_blk_sids fn.sbody in
  (* assuming one function per session for uniqueness *)
  let (idv,idr) = root_id "" in
    pushs (mk_s_body fn.svar.vname);
    Hashtbl.clear macros_added;
    mk_curfn (str2val fn.svar.vname);
    mk_location (mk_fundec_location idv) loc;
    mk_location (mk_fundec_end_location idv) endloc;
    mk_fundec_name idv (get_cil_varinfo fn.svar false None None)
      (get_cil_block idr fn.svar.vname fn.sbody);
    list_iteri (fun i vi ->
      mk_fundec_formal idv
        (sint2val i) (get_cil_varinfo vi false None None)) fn.sformals;
    List.iter (fun vi ->
      mk_fundec_local idv (get_cil_varinfo vi false None None)) fn.slocals;
    (* also add global sessions for static locals *)
    List.iter (fun vi -> if vi.vstorage = Static then
      ignore (get_cil_varinfo vi true None None)) fn.slocals;
    pops();
    idv

and get_cil_block idr fname blk =
  let idv = next_id idr in
    mk_block_stmts idv
      (list2val None (List.map (get_cil_stmt idr fname) blk.bstmts));
    mk_attrs idr (mk_block_attr idv) blk.battrs;
    idv

and get_cil_stmt idr fname stmt =
  (* assuming one function per session for uniqueness *)
  let make_idv stmt = get_id ("s",stmt.sid) in
  let idv = make_idv stmt in
  let _ = match stmt.skind with
      Instr instrs ->
        mk_stmt_instrs idv
          (list2val None (List.map (get_cil_instr idr fname) instrs))
    | Return (eo,_) ->
        mk_stmt_return idv;
        (match eo with
             Some exp -> mk_stmt_return_exp idv (get_cil_exp idr exp)
           | None -> ())
    | Goto (sr,_) ->  mk_stmt_goto idv (make_idv !sr)
    | Break _ ->      mk_stmt_break idv
    | Continue _ ->   mk_stmt_continue idv
    | If (exp,trueblk,falseblk,l) ->
        mk_stmt_if idv (get_cil_exp idr exp)
          (get_cil_block idr fname trueblk) (get_cil_block idr fname falseblk)
    | Switch (exp,blk,_,_) ->
        let do_case e s =
          sum2val ("case",[|get_cil_exp idr e; make_idv s|]) in
        let do_default s =
          sum2val ("default",[|make_idv s|]) in
        let rec get_stmt_cases = function
            [] -> [] 
          | stmt::sxs ->
              let casexs = get_stmt_cases sxs in
              let rec get_label_cases = function
                  [] -> casexs
                | Case(exp,_)::xs  -> (do_case exp stmt)::(get_label_cases xs)
                | Default _::xs    -> (do_default stmt)::(get_label_cases xs)
                | Label(_,_,_)::xs -> get_label_cases xs in
              get_label_cases stmt.labels in
        let cases = get_stmt_cases blk.bstmts in
          mk_stmt_switch idv (get_cil_exp idr exp)
            (get_cil_block idr fname blk) (list2val None cases)
    | Loop (blk,_,_,_) ->     mk_stmt_loop idv (get_cil_block idr fname blk)
    | Block blk ->            mk_stmt_block idv (get_cil_block idr fname blk)
    | TryFinally (_,_,_) ->   mk_stmt_tryfinally idv
    | TryExcept (_,_,_,_) ->  mk_stmt_tryexcept idv in
  mk_location (mk_stmt_x_location idv) (get_stmtLoc stmt.skind);
  idv

and get_cil_instr idr fname instr =
  let idv = next_id idr in
  let loc = match instr with
      Set (lv,exp,l) ->
        mk_instr_set idv (get_cil_lval idr lv) (get_cil_exp idr exp); l
    | Call (lvo,exp,args,l) ->
        mk_instr_call idv (get_cil_exp idr exp);
        (match lvo with
             Some lv -> mk_instr_call_ret idv (get_cil_lval idr lv)
           | None -> ());
        list_iteri (fun i e ->
          mk_instr_call_arg idv (sint2val i) (get_cil_exp idr e)) args;
        (* add edge for direct calls to use later in topo-sorting *)
        (match exp with
             Lval ((Var vi,NoOffset), _) ->
               let ss_body = o full_string_of_pred mk_s_body in
                 add_process_edge (ss_body fname) (ss_body vi.vname)
           | _ -> ()); l
    | Asm (attrs,templates,outputs,inputs,clobbers,l) ->
        mk_instr_asm idv (list2val None (List.map str2val templates));
        let n = List.fold_left (fun n (idopt,output,lv) ->
          mk_instr_asm_out idv (sint2val n) (maybex2val str2val idopt) 
            (str2val output) (get_cil_lval idr lv) ; n+1) 0 outputs in
        ignore (List.fold_left (fun n (idopt,input,exp) ->
          mk_instr_asm_in idv (sint2val n) (maybex2val str2val idopt)
            (str2val input) (get_cil_exp idr exp); n+1) n inputs);
        List.iter (o (mk_instr_asm_clobber idv) str2val) clobbers;
        mk_attrs idr (mk_instr_asm_attr idv) attrs; l in
  mk_location (mk_instr_x_location idv) loc;
  idv

(* CIL naming tweaks *)

(* consistency between anonymous struct/union/comp definitions. CIL assigns
 * a unique ID to these in the order they appeared in the preprocessor,
 * which is fine for single file processing but will not be consistent when
 * the same definition is encountered when handling multiple files.
 * strip off the unique ID and replace it with the line number of the definition,
 * which will not be affected by different preprocessings *)
let consistent_symbol_name name loc =
  if string_begins name "__anonstruct_" ||
     string_begins name "__anonunion_" ||
     string_begins name "__anonenum_" then begin
    try let last = S.rindex name '_' in
        let chopped = S.sub name 0 (last + 1) in
          chopped ^ (string_of_int loc.line)
    with Not_found -> name
  end else name

(* uniquification of static functions/globals. since these can't be referenced
 * via 'extern'-type declarations, we can unique them by the file they appear
 * in of the form 'file:name'. strip prefix off the file if present *)
let check_static_symbol_name vi =
  if vi.vstorage = Static then begin
    assert (not (S.contains vi.vname ':'));  (* don't do this twice to a var *)
    vi.vname <- (replace_prefix vi.vdecl.file) ^ ":" ^ vi.vname
  end

(* global symbol name uniquification. when we are running over large systems
 * there may be non-static functions/globals with overlapping names (e.g. main)
 * as well as non-isomorphic structures with the same name (and which are
 * hopefully used in non-overlapping parts of the code base). assign new
 * names to symbols which were defined at a different file/line from another
 * symbol of the same name. note that this is not a completely correct
 * solution:
 *
 * (a) identically named but semantically different functions may be defined
 *     at the same file/line due to macro magic
 * (b) calls which could target any of the identically named functions
 *     (i.e. one was not defined in the same file, just referenced with
 *     an extern declaration) will be assumed to target just a single one.
 *)
let unique_symbol_name kind name loc =
  (* get known definitions for the kind/name. these are stored in symbol.db
   * as plaintext entries, key 'kind:name' and per-line entries 'FILE:LINE' *)
  let key = kind ^ ":" ^ name in
  let seek = (replace_prefix loc.file) ^ ":" ^ (string_of_int loc.line) in
  let entry = try IO.uncompress (Bdb.find (IO.get_db "symbol") key)
              with Not_found -> "" in
  let curpos = ref 0 in
  let curline = ref ~-1 in
  let curstr = ref "" in
  let isnew = ref false in
    (try while !curstr <> seek do
       incr curline;
       let next = String.index_from entry !curpos '\n' in
         curstr := String.sub entry !curpos (next - !curpos);
         curpos := next+1
     done with Not_found ->
       isnew := true;
       (* append new symbol location *)
       let out = IO.open_dbentry "symbol" key IO.Pt_append in
         IO.fprintf out "%s\n" seek;
         IO.close_stream out);
    if !curline = 0 then (name, !isnew)
    else (name ^ "$clone" ^ (string_of_int !curline), !isnew)

(* change the names of whatever CIL structures we need to in order to get
 * cross-file naming consistency and uniqueness. remember which globals we
 * haven't previously seen, and add them to glist for later crawling *)
class namingVisitor glist = object
  inherit nopCilVisitor 
  method vglob glob =
    let isnew =
      match glob with
        GCompTag (comp,l,_) ->
          comp.cname <- consistent_symbol_name comp.cname l;
          let (cname,isnew) = unique_symbol_name "vcomp" comp.cname l in
            comp.cname <- cname; isnew
      | GEnumTag (enum,l,_) ->
          enum.ename <- consistent_symbol_name enum.ename l;
          let (ename,isnew) = unique_symbol_name "venum" enum.ename l in
            enum.ename <- ename; isnew
      | GVar (var,_,l) ->
          check_static_symbol_name var;
          let (vname,isnew) = unique_symbol_name "vvar" var.vname l in
            var.vname <- vname; isnew
      | GFun (fdec,l,_) ->
          List.iter check_static_symbol_name fdec.slocals;
          check_static_symbol_name fdec.svar;
          let (fname,isnew) = unique_symbol_name "vfun" fdec.svar.vname l in
            fdec.svar.vname <- fname; isnew
      | GType (typ,l) ->
          if typ.tname <> "" then begin
            let (tname,isnew) = unique_symbol_name "vtype" typ.tname l in
              typ.tname <- tname; isnew
          end else false
      | _ -> false in
    if isnew then prepend glist glob;
    DoChildren
  (* needed for older versions of CIL (pre 1.3.4?)
   * change empty arrays int[] to int[0] to get the proper width *)
(*
  method vtype typ =
    match typ with
        TArray (typ,None,attrs) ->
          (* set the length to Some(0) *)
          let lene = Const(CInt64(Int64.zero,IInt,None)) in
            ChangeTo (TArray(typ,Some lene,attrs))
      | _ -> DoChildren
*)
end

(* Compilation hooks *)

let logic_dir = ref "."
let setLogicDir = (:=) logic_dir

let preprocessed_lines : (string,Clexer.pp_line_array) H.t = H.create 10
let set_preprocessed_lines = H.add preprocessed_lines

let process_preprocessed_lines fname =
  let found : (string, int ref * IO.t_ptstream) H.t = H.create 10 in
  let _ = try
    let lines = H.find preprocessed_lines fname in
    let input = open_in fname in
      GrowArray.iter (fun (f,l) ->
        let f = replace_prefix f in
        let ppline = input_line input in
          (* IO.printf "%s(%d): %s\n" f l ppline; *)
          if f <> "" && not (H.mem found f) then begin
            let out = IO.open_dbentry "ppfile" f IO.Pt_excl in
              H.add found f (ref 1,out)
          end;
          if f <> "" && (ppline = "" || ppline.[0] <> '#') then begin
            (* not a preprocessor directive *)
            let (next,out) = H.find found f in
              while l > !next do
                IO.fprintf out "\n"; incr next
              done;
              if l = !next then
                (IO.fprintf out "%s\n" ppline; incr next)
          end) lines
    with End_of_file -> ()
       | Not_found when fname = "stdout" -> () (* cil-generated file *)
       | exn ->
           IO.printf "Exception in set_processed_lines: %s\n"
             (Printexc.to_string exn) in
  H.iter (fun _ (_,out) -> IO.close_stream out) found

let feature : featureDescr =
  { fd_name = "clptrans";
    fd_enabled = ref true;
    fd_description = "CIL -> CLP conversion";
    fd_extraopt = [];
    fd_doit = (fun f ->
      IO.bdb_init !logic_dir;
      let gref = ref [] in
      let namer = new namingVisitor gref in
        uniqueVarNames f;  (* only uniques local variables to functions *)
        visitCilFileSameGlobals namer f;
        List.iter do_cil_global !gref;
        bdb_add_process_edges f.fileName !process_edges;
        Hashtbl.iter (fun n s ->
            bdb_dump_session (full_string_of_pred n) (dump_session_str s))
          all_sessions;
        process_preprocessed_lines f.fileName;
        IO.bdb_finish());
    fd_post_check = true;
  }

(* Spec integration *)
  
let psessions = H.fold (fun s cs sl -> 
    ((s,[|vt_str|]), Some cs)::sl
  ) sessions []

let _ = register_package { empty_package with
  p_name = "translatephc";
  p_find_handlers = !find_handlers;
  p_predicates = !predicates;
  p_sessions = psessions;
  p_sumtypes = !sumtypes;
  p_abstypes = !abstypes;
}

(*
(* Simplified IR for helloworld *)
PHP_script ::= Statement* ;
Statement ::= Eval_expr ;
Eval_expr ::= Expr ;
Expr ::= Assignment | Variable | Method_invocation | Literal ;
Assignment ::= Variable is_ref:"&"? Expr ;
Variable ::= Target? Variable_name array_indices:VARIABLE_NAME?* ;
Literal ::= STRING<String*> ;
Method_invocation ::= Target? Method_name Actual_parameter* ;
Actual_parameter ::= Variable_name array_indices:VARIABLE_NAME?* ;
Method_name ::= METHOD_NAME ;
Variable_name ::= VARIABLE_NAME ;
Target ::= CLASS_NAME ;


let input = ref ""

let read_phc_xml_stdin =
  try 
	while true
	do 
		input := !input ^ (input_line stdin) ^ "\n";
	done
  with End_of_file -> ();;


(*let _ = print_string !input;;*)
*)

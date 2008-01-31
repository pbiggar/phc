(*
 *
 * Copyright (c) 2001-2002, 
 *  George C. Necula    <necula@cs.berkeley.edu>
 *  Scott McPeak        <smcpeak@cs.berkeley.edu>
 *  Wes Weimer          <weimer@cs.berkeley.edu>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. The names of the contributors may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *)

(** The main entry point *)
val convFile: Cabs.file -> Cil.file

type id_macro_type = 
{
   id_macro_def:string;
  
};;

type function_macro_type = 
{
   function_macro_def:string;
   function_macro_num_args:int;
   function_macro_args: (string * string) list;
  
};;

type macro_type = Id_macro of id_macro_type 
				| Function_macro of function_macro_type
			    | Builtin_macro;;


type macro =
{
	macro_type:macro_type;
    macro_name:string;
	macro_line:Int32.t;
	macro_file:string;
	macro_begin:int; (* beginning byte pos for this macro *)
	mutable macro_end:int; (* end byte pos for this macro *)
	macro_id:int; (* unique id for this macro *)
	mutable macro_parents:(int list);
	(* list of parent macros for keeping track of nested macros *)
	(* Note that the first elem in the list will be the closest parent *)
	
};;

(* Hashtable to query macros by their unique_id *)
val macro_table_by_id: macro Inthash.t

(** Turn on tranformation that forces correct parameter evaluation order *)
val forceRLArgEval: bool ref

(** Set this integer to the index of the global to be left in CABS form. Use 
 * -1 to disable *)
val nocil: int ref

(** Indicates whether we're allowed to duplicate small chunks of code. *)
val allowDuplication: bool ref

(** If false, the destination of a Call instruction should always have the
    same type as the function's return type.  Where needed, CIL will insert
    a temporary to make this happen.

    If true, the destination type may differ from the return type, so there
    is an implicit cast.  This is useful for analyses involving [malloc],
    because the instruction "T* x = malloc(...);" won't be broken into
    two instructions, so it's easy to find the allocation type.

    This is false by default.  Set to true to replicate the behavior
    of CIL 1.3.5 and earlier.
*)
val doCollapseCallCast: bool ref

(** A hook into the code that creates temporary local vars.  By default this
  is the identity function, but you can overwrite it if you need to change the
  types of cabs2cil-introduced temp variables. *)
val typeForInsertedVar: (Cil.typ -> Cil.typ) ref

(** Like [typeForInsertedVar], but for casts.  
  * Casts in the source code are exempt from this hook. *)
val typeForInsertedCast: (Cil.typ -> Cil.typ) ref

(** A hook into the code that merges arguments in function types. *)
val typeForCombinedArg: ((string, string) Hashtbl.t -> Cil.typ -> Cil.typ) ref

(** A hook into the code that merges arguments in function attributes. *)
val attrsForCombinedArg: ((string, string) Hashtbl.t ->
                          Cil.attributes -> Cil.attributes) ref

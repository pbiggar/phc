(* Abstract Syntax Tree data structure, and symbol tables
 *
 * XXX: The interface to this file needs to be rationalized at some point.
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


type t_var = string

module SymbolSet : Set.S with type elt = string
module VarSet : Set.S with type elt = string
module VarMap : Map.S with type key = string

(* Return the set of keys of a VarMap *)
val varmap_keys : 'a VarMap.t -> VarSet.t

(* Restrict the domain of a VarMap *)
val varmap_restrict : 'a VarMap.t -> VarSet.t -> 'a VarMap.t

(* Remove a set of keys from a VarMap *)
val varmap_remove_keys : 'a VarMap.t -> VarSet.t -> 'a VarMap.t

(* Take the union of two variable mappings. If the same key is present in
 * both maps, then the value from the first map is used. *)
val varmap_union : 'a VarMap.t -> 'a VarMap.t -> 'a VarMap.t

val varset_of_list : t_var list -> VarSet.t

type t_type_renaming = Spec.t_val_type -> Spec.t_val_type

type t_dsymbol
val dsymbol_empty : t_dsymbol

type ast_term =
  | At_anyvar of string
  | At_var    of string
  | At_string of string
  | At_int    of Big_int.big_int
  | At_float  of float
  | At_sum    of string * ast_term array (* f{...} *)
  | At_call   of ast_pred
and ast_pred = {
  p_name: string;
  p_args: ast_term array;

  (* Which overloaded version of a predicate are we referring to?
   * Filled in by type-checking. *)
  mutable p_disambiguation: t_dsymbol;

  (* Mapping from the type variables in a predicate's definition to the
   * the instance of those type variables used for this particular occurrence 
   * of that predicate. Filled in by type-checking. *)
  mutable p_type_renaming : t_type_renaming;
} 

type ast_spred = {
    s_session : ast_pred option ;
    s_pred    : ast_pred
}

(* mode environment, internal to spectypes.ml *)
type mode_env = {
  used : VarSet.t;
  bound : VarSet.t;
  noreuse : VarSet.t;
}

val empty_menv : mode_env

type ast_goal = {
    sfa : Spec.sfa;
    mutable body : ast_goal_body;
    mutable vars_used : VarSet.t;
    nonlocals : VarSet.t;
    mutable menv : mode_env;
}

and ast_goal_body =
    Ag_conjunction of ast_goal list
  | Ag_disjunction of ast_goal list
  | Ag_find        of ast_spred
  | Ag_wait        of ast_pred 
  | Ag_add         of ast_spred
  | Ag_negation    of ast_goal
  | Ag_implies     of ast_goal * ast_goal
  | Ag_some        of t_var list * ast_goal
  | Ag_all         of t_var list * ast_goal
  | Ag_collection  of ast_goal * ast_pred

type ast_rule_body = 
    Ar_flat        of ast_goal
  | Ar_horn_clause of string option * ast_spred * ast_goal 
  | Ar_query       of ast_pred
  | Ar_assertion   of string option * ast_goal

type ast_rule = {
  r_body : ast_rule_body;
  rl_sfa  : Spec.sfa;

  (* Type variable -> type mapping. Filled in by type checking. *)
  mutable r_type_vmap: Spec.t_type_vmap;
}

type ast = ast_rule list

val string_of_ast_term : ast_term -> string
val string_of_ast_pred : ast_pred -> string


val analysis_session : string ref
val analysis_name: string ref
val analysis_topdown : bool option ref
val analysis_eager : bool ref
val analysis_priority : int option ref

(* Global symbol table *)
type symbol_kind =
    Sk_predicate
  | Sk_session
  | Sk_type
  | Sk_sum_value
  | Sk_analyze

type t_symbol_def = {
  s_name  : string;
  s_arity : int;
  s_variable_arity : bool; (* If true, then this symbol has variable arity
			    * with a minimum arity of s_arity *)  
  s_kind  : symbol_kind;
  s_disambiguations : t_dsymbol list;
}

(* Predicate symbol table *)

type t_predicate_kind = 
  | Pk_session
  | Pk_add_handler
  | Pk_find_handler
  | Pk_collect_handler
  | Pk_regular

type t_predicate_def = {
  pd_sfa   : Spec.sfa;
  pd_kind  : t_predicate_kind;
  pd_args  : Spec.t_val_type array; (* Argument types, if any *)
  (* All known predicate modes. Each predicate can have multiple modes *)
  pd_modes : (Spec.t_pred_mode * Spec.t_succeeds list) list;
  (* Has this predicate been used with the '?' wait operator? *)
  mutable pd_magic : bool; 
  (* Does this predicate appear in an external session? *)
  mutable pd_in_session: bool;
  mutable pd_orders: Spec.t_pred_order list;
}

type t_type_kind =
  | T_alias of Spec.t_val_type
  | T_sumtype of string list
  | T_abstract

type t_type_def = {
  td_kind : t_type_kind;
  td_args : Spec.t_val_type array;
  td_sfa  : Spec.sfa;
}

(* Opened packages *)
val packages : (string, unit) Hashtbl.t

(* Types of arguments to all known symbols *)
val symbols : (string, t_symbol_def) Hashtbl.t 

val predicates : (t_dsymbol, t_predicate_def) Hashtbl.t

val sessions : (string, SymbolSet.t) Hashtbl.t

val order_types : (Spec.t_val_type, unit) Hashtbl.t

val types : (string, t_type_def) Hashtbl.t

(* Special predicate names that must be used with an external session *)
val sess_handlers : string list

(* All sumvalue * sumtype pairs, indexed by the name of the sumtype value *)
val sumvalues : (string,Spec.t_pred_type * Spec.t_val_type) Hashtbl.t


(* Reset state after checking an entire spec file *)
val reset_type_checking : unit -> unit

(* Commit user-defined symbols *)
val add_predicate : Spec.sfa -> t_predicate_kind -> string ->
  Spec.t_val_type array -> (Spec.t_pred_mode * Spec.t_succeeds list) list 
  -> t_dsymbol
val add_operator : Spec.sfa -> string -> string -> unit
val add_session : Spec.sfa -> Spec.t_pred_type * string list option -> unit
val add_type : Spec.sfa -> Spec.t_val_type -> unit
val add_alias_type : Spec.sfa -> Spec.t_val_type * Spec.t_val_type -> unit
val add_sum_values : Spec.sfa -> 
  Spec.t_val_type * (Spec.t_pred_type * Spec.sfa) list -> unit

val get_mode : ast_pred -> (Spec.t_pred_mode * Spec.t_succeeds list)
val get_all_modes: ast_pred -> (Spec.t_pred_mode * Spec.t_succeeds list) list
val all_out_mode : ast_pred -> bool

val add_order : t_dsymbol -> Spec.t_pred_order -> unit

(* Mangle a name, adding any necessary disambiguation information *)
val mangle_name: t_dsymbol -> string

(* Check types for well-formedness *)
val check_type : Spec.t_val_type -> unit

val remove_aliases: Spec.t_val_type -> Spec.t_val_type

val pred_info: ast_pred -> string * ast_term array * string

val get_symbol: Spec.sfa -> symbol_kind -> string -> t_symbol_def

val ast_check_rule: ast_rule -> unit
val dont_care_disambiguate_rule: ast_rule -> ast_rule 
val scope_infer_rule: ast_rule -> ast_rule 
val session_check: unit -> unit

val spredicate_vars_used: ast_spred -> VarSet.t 

val get_pred_def: ast_pred -> t_predicate_def

(* Add a package or analysis directive *)
val add_package : string -> unit
val add_analyze : ast_pred -> unit

val ppAST: ast_rule list -> Pp.doc

(* Hook for spec parser *)
val parse_file : (string -> string list -> ast_rule list) ref

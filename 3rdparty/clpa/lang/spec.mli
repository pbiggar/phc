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

type t_val
type t_pred

type t_rpred_kind =
    Tp_find               (* add remainder for matching preds *)
  | Tp_add                (* add all matching preds *)
  | Tp_negated            (* add remainder if there are no matching preds *)
  | Tp_collect of t_pred  (* add remainder, collecting all matching preds *)

type t_priority =
    Rp_fix of int           (* fixed priority, smaller is higher priority *)
  | Rp_var of t_val * bool  (* variable priority, base on positions of values
                             * and direction (true == forward) *)
type sfa = 
  | Sfa_package  of string        (* In a built-in package *)
  | Sfa_file     of string * int  (* In a source file at a given line *)
  | Sfa_none                      (* Nowhere in particular. e.g. reporting
				   * the absence of something rather than
				   * the presence. *)

type t_rpred = {
  (* priority to use for evaluating this operation *)
  r_priority : t_priority list;

  (* rule stratum *)
  r_stratum : int;

  (* kind of operation to apply to predicate *)
  r_kind : t_rpred_kind;

  (* session to apply operation to. None indicates the current session *)
  r_session : t_pred option;

  (* pred to apply operation to *)
  r_pred : t_pred;

  (* location of this rpred in the source *)
  r_sfa : sfa;
}

type t_rule = t_rpred list  (* evaluated left to right *)

(* Compare two t_preds *)
val pred_compare : t_pred -> t_pred -> int

(* error reporting *)
exception Unexpected of string
val pred_unexpected : string -> 'a

type t_val_kind

type t_val_kind_info = {
  vki_tostring : int (* depth limit *) -> int -> string;
  vki_compare  : int -> int -> int;
  vki_dump     : Streamio.t_dump_fn -> int -> unit;
  vki_load     : Streamio.t_load_fn -> int;
}

val register_val_kind : t_val_kind_info -> t_val_kind
val val2cst : t_val_kind -> t_val -> int
val cst2val : t_val_kind -> int -> t_val

(* Values *)

val anyval  : t_val
val var2val : string -> t_val
val str2val : string -> t_val
val int2val : Big_int.big_int -> t_val
val flt2val : float -> t_val
val sum2val : string * t_val array -> t_val

(* raise Unexpected if values do not match *)
val val2var : t_val -> string
val val2str : t_val -> string
val val2int : t_val -> Big_int.big_int
val val2flt : t_val -> float
val val2sum : t_val -> string * t_val array

(* useful wrappers for int2val/val2int wrapper *)
val sint2val : int -> t_val
val val2sint : t_val -> int

(* map from variables to variables/constant values *)
type t_vmap
val vmap_empty : t_vmap

(* get a unifier for two values, None if not unifiable *)
val add_vmap : t_vmap -> t_val -> t_val -> t_vmap option
val make_vmap : t_val array -> t_val array -> t_vmap option

(* apply a vmap to the variables in a value. if a unifier for two values
 * given by make_vmap is applied to those values, the results are identical *)
val vmap_val : t_vmap -> t_val -> t_val

(* rename any vars in v by prepending with pfx *)
val rename_val : string (* pfx *) -> t_val -> t_val

(* non-const values are variables, the wildcard any_val,
 * or sums containing non-const values *)
val is_val_const : t_val -> bool

(* does the value contain any instance of any_val *)
val is_val_any : t_val -> bool

(* raise Unexpected if values are not const *)
val compare_vals : t_val -> t_val -> int

val load_val : Streamio.t_load_fn -> t_val
val dump_val : Streamio.t_dump_fn -> t_val -> unit

(* Value types *)

type t_val_type

(* pred name and argument types *)
type t_pred_type = string * t_val_type array

(* make a new type. the args indicate any other types this is specialized to,
 * and may be type variables for polymorphic types *)
val make_type : string -> t_val_type array -> t_val_type

(* raise Unexpected on type variables *)
val break_type : t_val_type -> string * t_val_type array

val string_of_type : t_val_type -> string

(* type analogs to t_vmap *)
type t_type_vmap
val type_vmap_empty : t_type_vmap
val add_type_vmap :
  t_type_vmap -> t_val_type -> t_val_type -> t_type_vmap option
val make_type_vmap :
  t_val_type array -> t_val_type array -> t_type_vmap option
val vmap_type : t_type_vmap -> t_val_type -> t_val_type
val rename_type : string -> t_val_type -> t_val_type

(* builtin types *)
val vt_any : t_val_type
val vt_var : string -> t_val_type
val vt_str : t_val_type
val vt_int : t_val_type
val vt_flt : t_val_type
val vt_list: t_val_type -> t_val_type

val rev_vt_var : t_val_type -> string

(* special types for varargs preds. having this as the last place type of a
 * pred indicates indicates that zero or more arguments past the previous one
 * may be added, where all must have the specified type *)
val vt_vargs : t_val_type -> t_val_type

(* return indicates any required arguments and the types of optional ones for
 * varargs preds *)
val is_pred_vargs : t_val_type array -> (t_val_type array * t_val_type) option

(* list operations *)
val sum_list : t_val_type * t_pred_type list
val list2val : t_val option (* trailing tail *) -> t_val list -> t_val
val val2list : t_val -> t_val list  (* only defined if no trailing tail *)

val list_cons_name : string
val list_nil_name : string

(* Predicate modes/ordering *)

(* mode for a predicate's arguments. true indicates 'in' args *)
type t_pred_mode = bool array

(* ordering imposed by a predicate. pair (src,tgt) means that argument src
 * precedes tgt in some acyclic structure for use in stratification *)
type t_pred_order = int * int

(* one way a predicate with 'in' arguments is allowed to succeed *)
type t_succeeds =
    Sk_zero  (* predicate fails for particular args *)
  | Sk_once  (* predicate succeeds once for particular args *)
  | Sk_many  (* predicate succeeds one or more times for particular args *)

type t_determinism = t_succeeds list

(* complete check for whether a predicate always succeeded correctly.
 * match a magic name with the regular name according to a mode *)
type t_pred_succeeds = string option * string * t_pred_mode * t_succeeds list

(* Printing *)

(* default term depth limit to use when converting values to strings.
 * terms deeper than this limit will be printed as "..." *)
val print_level : int ref

(* given the string rep for a val at a given depth either leaves it or
 * converts to '...' *)
val cvt_val_depth : int (* depth *) -> string -> string

val string_of_val : int (* depth *) -> t_val -> string
val string_of_pred : int (* depth limit *) -> t_pred -> string  
val string_of_rpred : t_rpred -> string
val string_of_rule : t_rule -> string

(* vals/preds at unlimited depth *)
val full_string_of_val : t_val -> string
val full_string_of_pred : t_pred -> string

(* Registration *)

type t_pred_rep = string * t_val array
val rep2pred : t_pred_rep -> t_pred
val pred2rep : t_pred -> t_pred_rep

type t_package = {
  (* package name, loaded via 'using name.' *)
  p_name : string;

  (* write all final stdout/file output before resetting *)
  p_writeout : unit -> unit;

  (* initialize/reset package resources *)
  p_reset : unit -> unit;

  (* predicate handlers for interfacing with package.
   * preds returned by find handlers may not unify with original pred *)
  p_add_handlers : (t_pred_type * (t_pred_rep -> unit)) list;
  p_find_handlers : (t_pred_type * ((t_pred_mode * t_succeeds list) list) *
                        (t_pred_rep -> t_pred_rep list)) list;
  p_collect_handlers : (t_pred_type *
    t_pred_mode * (t_pred_rep -> t_pred_rep list -> t_pred_rep list)) list;

  (* additional symbols defined by the package *)
  p_predicates : (t_pred_type * t_pred_order list) list;
  p_sessions : (t_pred_type * string list option) list;
  p_sumtypes : (t_val_type * t_pred_type list) list;
  p_abstypes : t_val_type list;  (* abstract types *)
  p_operators : (string * string) list;
}

(* empty package for extending with non-empty fields on creation *)
val empty_package : t_package

val register_package : t_package -> unit
val get_package : string -> t_package  (* raises Not_found if not found *)

(* built-in packages are always loaded *)
val set_package_builtin : string -> unit
val get_builtin_packages : unit -> string list

(* helpers for enums, just sumtypes which take no arguments *)
type 'a val_enum = t_val_type * ('a * string) list
val make_enum_sum : 'a val_enum -> (t_val_type * t_pred_type list)
val enum2val : 'a val_enum -> 'a -> t_val
val val2enum : 'a val_enum -> t_val -> 'a

(* exceptions raised by built-in handlers implemented in spec.ml *)
exception Handle_clear_preds
exception Handle_process_dep of t_pred
exception Handle_print_derivation of int * t_pred
exception Handle_assertion_failure of string

(* special predicate names with handlers in builtin.ml *)
val clear_pred_name : string
val process_dep_name : string
val derivation_pred_name : string
val query_pred_name : string
val equal_pred_name : string
val assertion_failure_name : string

(* Sessions *)

(* external session not being analyzed, lightweight set of predicates *)
type t_ext_session
val new_ext_session : t_pred -> t_ext_session
val get_ext_session_name : t_ext_session -> t_pred
val add_ext_logic : t_ext_session -> t_pred -> unit
val iter_ext_logic : t_ext_session -> (t_pred -> unit) -> unit

(* callbacks for applying find or add operations to external sessions *)
type ext_callbacks = {

  (* get the contents of each session in sesslist *)
  cb_find : t_pred list (* sesslist *) -> t_ext_session list;

  (* add pred to sess *)
  cb_add : t_pred (* sess *) -> t_pred (* pred *) -> unit;

  (* clear all *OLD* predicates from sess *)
  cb_clear : t_pred (* sess *) -> unit;

  (* add a process dependency edge between sess1 and sess2 *)
  cb_process_dep : t_pred (* sess1 *) -> t_pred (* sess2 *) -> unit;
}

type anly_spec = {
  as_session : t_ext_session option;
  as_rules : t_rule list array;
  as_packages : string list;
  as_orders : (string,t_pred_order) Hashtbl.t;
  as_succeeds : t_pred_succeeds list;
}

type anly_status =
    Ar_success
  | Ar_timeout of float     (* timeout, float indicates callback time spent *)
  | Ar_failure of string    (* failure internal to interpreter *)
  | Ar_ext_error of string  (* handling error external to interpreter *)

(* take a timeout in seconds and callbacks for using external sessions,
 * run a set of rules using a set of packages over a particular session.
 * return indicates status on how run finished as well as
 * how much analysis time was spent (other than in external callbacks) *)
val run_analysis : int -> ext_callbacks -> anly_spec -> (anly_status * float)

(* write all final stdout/file output for a set of packages.
 * call before reset_packages() *)
val writeout_packages : string list -> unit

(* clean out all intermediate data for a set of packages, as well as any
 * hash-consed strings, ints, etc. this invalidates all t_vals and t_preds *)
val reset_packages : string list -> unit

(* Parsing *)
val cur_sfa : unit -> sfa

(* updates the current parser SFA, returning the old one *)
val change_sfa : string * int -> string * int

val parse_error : string -> 'a  (* error at current parse position *)
val rule_error : sfa -> string -> 'a
val rule_warning : sfa -> string -> unit
val string_of_sfa : sfa -> string

(* check if there were any warnings, and if so (and set to warnings-as-errors),
 * print an error message and exit *)
val check_warnings : unit -> unit

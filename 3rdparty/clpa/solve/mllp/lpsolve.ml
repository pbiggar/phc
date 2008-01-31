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

(* OCaml interface to lp_solve *)

type lpm

type t_lpstatus =
    LP_Optimal
  | LP_Infeasible
  | LP_Unbounded
  | LP_Degenerate
  | LP_SubOptimal
  | LP_TimeOut
  | LP_NoMemory
  | LP_NumFailure
  | LP_UserAbort
  | LP_ProcFail
  | LP_ProcBreak
  | LP_Failure (* unspecified *)

let lpstt2str lpstt =
  match lpstt with
      LP_Optimal     -> "Optimal"
    | LP_Infeasible  -> "Infeasible"
    | LP_Unbounded   -> "Unbounded"
    | LP_Degenerate  -> "Degenerate"
    | LP_SubOptimal  -> "SubOptimal"
    | LP_TimeOut     -> "TimeOut"
    | LP_NoMemory    -> "NoMemory"
    | LP_NumFailure  -> "NumFailure"
    | LP_UserAbort   -> "UserAbort"
    | LP_ProcFail    -> "ProcFail"
    | LP_ProcBreak   -> "ProcBreak"
    | LP_Failure     -> "Unknown Failure"

type t_lpverbose =
    LP_Neutral
  | LP_Critical
  | LP_Severe
  | LP_Important
  | LP_Normal
  | LP_Detailed
  | LP_Full

type t_lpbranchdir =
    LP_BranchCeiling
  | LP_BranchFloor
  | LP_BranchAutomatic

type t_lpmajorrule =
    LP_FirstSelect
  | LP_GapSelect
  | LP_RangeSelect
  | LP_FractionSelect
  | LP_PseudoCostSelect
  | LP_PseudoNonIntSelect
  | LP_PseudoRatioSelect

type t_lpminorrule =
    LP_WeightReverseMode
  | LP_BranchReverseMode
  | LP_GreedyMode
  | LP_PseudoCostMode
  | LP_DepthFirstMode
  | LP_RandomizeMode
  | LP_GubMode
  | LP_DynamicMode
  | LP_RestartMode
  | LP_BreadthFirstMode
  | LP_AutoOrder
  | LP_RCostFixing
  | LP_StrongInit

type t_lprule = t_lpmajorrule * t_lpminorrule list

type t_lpcst =
    LPc_Le
  | LPc_Ge
  | LPc_Eq

type t_lparr = int * (float * int) list

external make : int -> int -> lpm = "lp_make"
external delete : lpm -> unit = "lp_delete"

external get_nrows : lpm -> int = "lp_get_nrows"
external get_ncols : lpm -> int = "lp_get_ncols"

external solve : lpm -> t_lpstatus = "lp_solve"
external get_obj : lpm -> float = "lp_get_obj"
external get_assign : lpm -> int -> float = "lp_get_assign"

external set_bb_depthlimit : lpm -> int -> unit = "lp_set_bb_depthlimit"
external set_bb_dir : lpm -> t_lpbranchdir -> unit = "lp_set_bb_dir"
external set_bb_rule : lpm -> t_lprule -> unit = "lp_set_bb_rule"

external set_verbose : lpm -> t_lpverbose -> unit = "lp_set_verbose"
external print : lpm -> unit = "lp_print"
external print_file : lpm -> string -> unit = "lp_print_file"

external set_timeout : lpm -> int -> unit = "lp_set_timeout"
external set_add_rowmode : lpm -> bool -> unit = "lp_set_add_rowmode"
external set_bnds_tighter : lpm -> bool -> unit = "lp_set_bnds_tighter"
external get_infinite : lpm -> float = "lp_get_infinite"
external set_infinite : lpm -> float -> unit = "lp_set_infinite"

external set_obj : lpm -> t_lparr -> unit = "lp_set_obj"
external maximize_obj : lpm -> unit = "lp_maximize_obj"
external minimize_obj : lpm -> unit = "lp_minimize_obj"

external add_column : lpm -> t_lparr -> unit = "lp_add_column"
external set_column : lpm -> int -> t_lparr -> unit = "lp_set_column"
external del_column : lpm -> int -> unit = "lp_del_column"

external add_row : lpm -> t_lparr -> t_lpcst -> float -> unit = "lp_add_row"
external set_row : lpm -> int -> t_lparr -> unit = "lp_set_row"
external set_row_type : lpm -> int -> t_lpcst -> unit = "lp_set_row_type"
external set_row_rhs : lpm -> int -> float -> unit = "lp_set_row_rhs"
external del_row : lpm -> int -> unit = "lp_del_row"

external set_isbinary : lpm -> int -> bool -> unit = "lp_set_isbinary"
external set_isint : lpm -> int -> bool -> unit = "lp_set_isint"
external set_issemicont : lpm -> int -> bool -> unit = "lp_set_issemicont"

external set_unbnded : lpm -> int -> unit = "lp_set_unbnded"
external set_bnds : lpm -> int -> float -> float -> unit = "lp_set_bnds"
external set_lower_bnd : lpm -> int -> float -> unit = "lp_set_lower_bnd"
external set_upper_bnd : lpm -> int -> float -> unit = "lp_set_upper_bnd"

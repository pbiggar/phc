(*
 * Authors:
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

(* sat_zchaff.ml 
 * 
 * Interface to the zChaff SAT solver.
 *)


open Clpautil
open Flags
open Spec
open Solvebit

module H = Hashtbl

open Biteval
module Z = Zchaff


(* Satisfiability *)

(* use a single Zchaff manager *)
let zchaff_mngr : Z.satm ref = ref (Z.init())
let _ = Z.set_time_limit !zchaff_mngr 5.
let num_zvars = ref 1

(* next free Zchaff variable *)
let next_zvar : int ref = ref 1

(* maintain a mapping between boolean vars and zchaff vars *)
type zvar = int
let tbl_var2zvar : (t_val,zvar) H.t = H.create 10

let reset() = 
  Z.release !zchaff_mngr;
  zchaff_mngr := Z.init();
  ignore (Z.set_time_limit !zchaff_mngr 5. );
  next_zvar := 1;
  H.clear tbl_var2zvar;
  num_zvars := 1

let get_zvar x =
  try H.find tbl_var2zvar x
  with Not_found ->
    if !next_zvar = !num_zvars then begin
      assert (Z.add_var !zchaff_mngr = !num_zvars);
      incr num_zvars
    end;
    let zx = !next_zvar in
      incr next_zvar;
      H.add tbl_var2zvar x zx; zx

let sat () = match Z.solve !zchaff_mngr with
      Z.Unsatisfiable -> false
    | Z.Satisfiable   -> true
    | Z.TimedOut      -> raise Timed_out
    | stt             -> pred_unexpected ("ZChaff error: " ^ Z.stt2str stt)
    
let sat_asn () = match Z.solve !zchaff_mngr with
      Z.Unsatisfiable -> None  
    | Z.Satisfiable   -> Some (let assign = H.create 10 in
        H.iter (fun x mx -> match Z.get_assign !zchaff_mngr mx with
            -1 -> H.add assign x false
          |  1 -> H.add assign x true
          |  n -> assert (n = 0) 
      ) tbl_var2zvar; assign) 
    | Z.TimedOut      -> raise Timed_out
    | stt             -> pred_unexpected ("ZChaff error: " ^ Z.stt2str stt)


(* SAT Solver registration *)
let _ = register_sat_solver {
  ss_name         = "zchaff";
  ss_priority     = 2; 
  ss_reset        = reset;
  ss_get_var      = get_zvar;
  ss_add_clause   = (fun gid df -> Z.add_clause_with_gid !zchaff_mngr df
                               (List.length df) gid);
  ss_sat          = sat; 
  ss_sat_asn      = sat_asn;
  ss_new_clause_group    = (fun _ -> Z.alloc_clause_gid !zchaff_mngr);
  ss_remove_clause_group = (fun gid -> Z.delete_clause_group !zchaff_mngr gid)
} 


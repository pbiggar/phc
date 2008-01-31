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

(* sat_minisat.ml 
 *
 * Interface to the MiniSAT SAT solver.
 *
 * The main point to note about this SAT solver interface is that clause groups
 * are "faked" by adding extra variables to each clause and using the
 * assumption feature of the solver, a trick apparently originally suggested
 * by Een and Sorrenson. As a consequence of this no clauses are ever
 * actually removed from the solver except through calling the reset() 
 * method, which nukes the entire solver.
 *)


open Clpautil
open Flags
open Spec
open Solvebit

module H = Hashtbl
module M = Minisat

let minisat_solver : M.satsolver ref = ref (M.new_solver ())
let solver_time_limit = 30
let _ = M.set_time_limit !minisat_solver solver_time_limit

(* maintain a mapping between boolean vars and minisat vars *)
type mvar = int
let tbl_var2mvar : (t_val,mvar) H.t = H.create 10

let reset () =
  minisat_solver := M.new_solver ();
  M.set_time_limit !minisat_solver solver_time_limit;
  H.clear tbl_var2mvar


let get_mvar x =
  try H.find tbl_var2mvar x
  with Not_found ->
    let zx = M.new_var !minisat_solver in
    H.add tbl_var2mvar x zx; zx

let sat () = match M.solve !minisat_solver with
      M.Unsatisfiable -> false
    | M.Satisfiable   -> true
    | M.TimedOut      -> raise Timed_out

let sat_asn () = match M.solve !minisat_solver with
      M.Unsatisfiable -> None 
    | M.Satisfiable   -> Some (let assign = H.create 10 in 
        H.iter (fun x mx -> match M.get_assign !minisat_solver mx with
            -1 -> H.add assign x false
          |  1 -> H.add assign x true
          |  n -> assert (n = 0)
      ) tbl_var2mvar; assign)
    | M.TimedOut      -> raise Timed_out

(* SAT Solver registration *)
let _ = register_sat_solver {
  ss_name         = "minisat";
  ss_priority     = 1;
  ss_reset        = reset;
  ss_get_var      = get_mvar;
  ss_add_clause   = (fun gid df -> M.add_clause !minisat_solver gid df 
                               (List.length df));
  ss_sat          = sat;
  ss_sat_asn      = sat_asn;
  ss_new_clause_group    = (fun _ -> M.new_clause_group !minisat_solver);
  ss_remove_clause_group = (fun gid -> 
    M.remove_clause_group !minisat_solver gid);
} 


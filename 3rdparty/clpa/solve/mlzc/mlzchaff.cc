/*
 * Authors:
 *   Yichen Xie  <yxie@cs.stanford.edu>
 *
 * Copyright (c) 2004,
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
 */

/* zchaff.c -- ocaml interface to zChaff
 *
 * Based on Andy Chou's implementation of the interface
 *     for a previous version of zChaff
 */
#include <SAT.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define M ((SAT_Manager) satm)

// init: unit -> satm
value zc_init(value unit) 
{
    CAMLparam1(unit);
    CAMLreturn((value) SAT_InitManager());
}

// version: unit -> string
value zc_version(value satm) 
{
    CAMLparam1(satm);
    CAMLreturn(copy_string(SAT_Version(M)));
}

// release: satm -> unit
value zc_release(value satm) 
{
    CAMLparam1(satm);
    SAT_ReleaseManager(M);
    CAMLreturn(Val_unit);
}

// set_nvars: satm -> int
value zc_set_nvars(value satm, value n) 
{
    CAMLparam2(satm, n);
    SAT_SetNumVariables(M, Int_val(n));
    CAMLreturn(Val_unit);
}

// add_var: satm -> int
value zc_add_var(value satm) 
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_AddVariable(M)));
}

// enable_var_branch: satm -> int -> unit
value zc_enable_var_branch(value satm, value vid)
{
    CAMLparam2(satm, vid);
    SAT_EnableVarBranch(M, Int_val(vid));
    CAMLreturn(Val_unit);
}

// disable_var_branch: satm -> int -> unit
value zc_disable_var_branch(value satm, value vid)
{
    CAMLparam2(satm, vid);
    SAT_DisableVarBranch(M, Int_val(vid));
    CAMLreturn(Val_unit);
}

// add_clause_with_gid: satm -> int list -> int -> int -> unit
value zc_add_clause(value satm, value list, value len, value gid)
{
    CAMLparam4(satm, list, len, gid);
    CAMLlocal1(p);

    {
	int n = Int_val(len);
	int *c = (int *) alloca (n * sizeof(*c));
	int i = 0;

	p = list;
	while (p != Val_int(0)) {
	    assert(i < n);
	    c[i++] = Int_val(Field(p, 0));
	    p = Field(p, 1);
	}
	assert(i == n);
	SAT_AddClause(M, c, n, Int_val(gid));
	CAMLreturn(Val_unit);
    }
}

// delete_clause_group: satm -> int -> unit
value zc_del_clause_group(value satm, value gid)
{
    CAMLparam2(satm, gid);
    SAT_DeleteClauseGroup(M, Int_val(gid));
    CAMLreturn(Val_unit);
}

// reset: satm -> unit
value zc_reset(value satm)
{
    CAMLparam1(satm);
    SAT_Reset(M);
    CAMLreturn(Val_unit);
}

// merge_clause_group: satm -> int -> int -> unit
value zc_merge_clause_group(value satm, value g1, value g2)
{
    CAMLparam3(satm, g1, g2);
    SAT_MergeClauseGroup(M, Int_val(g1), Int_val(g2));
    CAMLreturn(Val_unit);
}

// alloc_clause_gid : satm -> int
value zc_alloc_clause_gid(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_AllocClauseGroupID(M)));
}

// is_set_clause_gid : satm -> int -> int -> bool
value zc_is_set_clause_gid(value satm, value cidx, value id)
{
    CAMLparam3(satm, cidx, id);
    CAMLreturn(Val_bool(SAT_IsSetClauseGroupID(M, Int_val(cidx), Int_val(id))));
}

// set_clause_gid : satm -> int -> int -> unit
value zc_set_clause_gid(value satm, value cidx, value id)
{
    CAMLparam3(satm, cidx, id);
    SAT_SetClauseGroupID(M, Int_val(cidx), Int_val(id));
    CAMLreturn(Val_unit);
}

// clear_clause_gid: satm -> int -> int -> unit
value zc_clear_clause_gid(value satm, value cidx, value id)
{
    CAMLparam3(satm, cidx, id);
    SAT_ClearClauseGroupID(M, Int_val(cidx), Int_val(id));
    CAMLreturn(Val_unit);
}

// get_volatile_gid: satm -> int
value zc_get_volatile_gid(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_GetVolatileGroupID(M)));
}

// get_global_gid: satm -> int
value zc_get_global_gid(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_GetGlobalGroupID(M)));
}

// set_time_limit: satm -> float -> unit
value zc_set_time_limit(value satm, value f)
{
    CAMLparam2(satm, f);
    SAT_SetTimeLimit(M, Double_val(f));
    CAMLreturn(Val_unit);
}

// set_mem_limit: satm -> int -> unit
value zc_set_mem_limit(value satm, value m)
{
    CAMLparam2(satm, m);
    SAT_SetMemLimit(M, Int_val(m));
    CAMLreturn (Val_unit);
}

// solve: satm -> status
value zc_solve(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_Solve(M)));
}

// get_assign: satm -> int -> int
value zc_get_assign(value satm, value v)
{
    CAMLparam2(satm, v);
    CAMLreturn(Val_int(SAT_GetVarAsgnment(M, Int_val(v))));
}

// set_randomness: satm -> int -> unit
value zc_set_randomness(value satm, value n)
{
    CAMLparam2(satm, n);
    SAT_SetRandomness(M, Int_val(n));
    CAMLreturn(Val_unit);
}

// set_randseed: satm -> int -> unit
value zc_set_randseed(value satm, value seed)
{
    CAMLparam2(satm, seed);
    SAT_SetRandSeed(M, Int_val(seed));
    CAMLreturn(Val_unit);
}

// mem_usage: satm -> int
value zc_mem_usage(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_EstimateMemUsage(M)));
}

// cpu_time: satm -> float
value zc_cpu_time(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(copy_double(SAT_GetCPUTime(M)));
}

// num_literals: satm -> int
value zc_num_literals(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_NumLiterals(M)));
}

// num_clauses: satm -> int
value zc_num_clauses(value satm)
{
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_NumClauses(M)));
}

// num_vars: satm -> int
value zc_num_vars(value satm) {
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_NumVariables(M)));
}

// num_decisions: satm -> int
value zc_num_decisions(value satm) {
    CAMLparam1(satm);
    CAMLreturn(Val_int(SAT_NumDecisions(M)));
}

#ifdef __cplusplus
}
#endif

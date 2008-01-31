/*
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
 */

/* minisat.ml -- OCaml interface to MiniSAT */

/* Based on the OCaml zChaff interface by Yichen Xie (yxie@cs.stanford.edu)
 * Based on Andy Chou's implementation for an older version of zChaff. */

#include <Solver.h>

extern "C" {

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/signals.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum solver_result {
    SR_UNSAT = 0,
    SR_SAT = 1,
    SR_TIMEOUT = 2,
};

} // extern "C"

/* GroupSolver is a subclass of the MiniSAT Solver class, extended to handle
 * simple clause groups and timeouts.
 * Clause groups are handled by creating a literal for each group, which is 
 * appended to every SAT clause in that group. Groups are disabled by asserting
 * the group's literal to be true, which effectively disables all of the
 * clauses for that group.
 */
class GroupSolver : public Solver {
    vec<Lit> groups;
    time_t timeout;

public:
    GroupSolver() : timeout(-1) {}
    int newClauseGroup();
    void addClauseToGroup(int gid, const vec<Lit>& ps);
    void removeClauseGroup(int gid);

    void setTimeLimit(time_t t) { timeout = t; }

    solver_result solveWithTimeout(const vec<Lit>& assumps);
    solver_result solveWithTimeout();
};

int GroupSolver::newClauseGroup()
{
    Var v = newVar();
    int gid = groups.size();
    groups.push(Lit(v, false));
    return gid;
}

void GroupSolver::addClauseToGroup(int gid, const vec<Lit>& ps)
{
    vec<Lit> clause;
    ps.copyTo(clause);
    clause.push(Lit(var(groups[gid]), true));
    addClause(clause);
}

solver_result GroupSolver::solveWithTimeout()
{
    return solveWithTimeout(groups);
}

/*______________________________________________________________________________
|
|  solveWithTimeout : (assumps : const vec<Lit>&)  ->  [bool]
|
|  Description:
|    Top-level solve. If using assumptions (non-empty 'assumps' vector), you 
|    must call 'simplifyDB()' first to see that no top-level conflict is 
|    present (which would put the solver in an undefined state).
|____________________________________________________________________________@*/
solver_result GroupSolver::solveWithTimeout(const vec<Lit>& assumps)
{
    simplifyDB();
    if (!ok) return SR_UNSAT;

    SearchParams    params(default_params);
    double  nof_conflicts = 100;
    double  nof_learnts   = nClauses() / 3;
    lbool   status        = l_Undef;
    time_t  time_limit;

    time_limit = (timeout == -1) ? -1 : (time(NULL) + timeout);

    // Perform assumptions:
    root_level = assumps.size();
    for (int i = 0; i < assumps.size(); i++){
        Lit p = assumps[i];
        assert(var(p) < nVars());
        if (!assume(p)){
            GClause r = reason[var(p)];
            if (r != GClause_NULL){
                Clause* confl;
                if (r.isLit()){
                    confl = propagate_tmpbin;
                    (*confl)[1] = ~p;
                    (*confl)[0] = r.lit();
                }else
                    confl = r.clause();
                analyzeFinal(confl, true);
                conflict.push(~p);
            }else
                conflict.clear(),
                conflict.push(~p);
            cancelUntil(0);
            return SR_UNSAT; }
        Clause* confl = propagate();
        if (confl != NULL){
            analyzeFinal(confl), assert(conflict.size() > 0);
            cancelUntil(0);
            return SR_UNSAT; }
    }
    assert(root_level == decisionLevel());

    // Search:
    if (verbosity >= 1){
        reportf("==================================[MINISAT]==================="
                "================\n");
        reportf("| Conflicts |     ORIGINAL     |              LEARNT    | "
                "Progress |\n");
        reportf("|           | Clauses Literals |   Limit Clauses Literals  "
                "Lit/Cl |          |\n");
        reportf("=============================================================="
                "================\n");
    }

    while (status == l_Undef){
        if (verbosity >= 1)
            reportf("| %9d | %7d %8d | %7d %7d %8d %7.1f | %6.3f %% |\n", 
                (int)stats.conflicts, nClauses(), (int)stats.clauses_literals, 
                (int)nof_learnts, nLearnts(), (int)stats.learnts_literals, 
                (double)stats.learnts_literals/nLearnts(), 
                progress_estimate*100);
        status = search((int)nof_conflicts, (int)nof_learnts, params);
        nof_conflicts *= 1.5;
        nof_learnts   *= 1.1;
        if (time_limit != -1 && time(NULL) > time_limit) {
          cancelUntil(0);
          return SR_TIMEOUT;
        }
    }
    if (verbosity >= 1)
        reportf("=============================================================="
                "================\n");

    cancelUntil(0);
    return (status == l_True ? SR_SAT : SR_UNSAT);
}


void GroupSolver::removeClauseGroup(int gid)
{
    groups[gid] = Lit(var(groups[gid]), true);
    addUnit(groups[gid]);
}


extern "C" {

static void satsolver_finalize(value v)
{
    delete *((GroupSolver **)Data_custom_val(v));
}

// new_solver : unit -> satsolver
value ms_init(value unit) 
{
    CAMLparam1(unit);
    CAMLlocal1(v);
    v = caml_alloc_final(2, satsolver_finalize, 1, 100);
    *((GroupSolver **)Data_custom_val(v)) = new GroupSolver();
    CAMLreturn(v);
}

value ms_new_var(value satsolver) 
{
    CAMLparam1(satsolver);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 
    int nvar = s->newVar();
    CAMLreturn(Val_int(nvar));
}

// add_clause_with_gid: satsolver -> int list -> int -> int -> unit
value ms_add_clause(value satsolver, value gid, value list, value len)
{
    CAMLparam4(satsolver, gid, list, len);
    CAMLlocal1(p);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 

    {
	int n = Int_val(len);
    vec<Lit> c(n);
	int i = 0;

//        printf("new clause ,len %d\n", n);
	p = list;
	while (p != Val_int(0)) {
        int v;
	    assert(i < n);
        v = Int_val(Field(p, 0));
//        printf("got value %d\n", v);
	    c[i++] = Lit(v >> 1, v & 1);
	    p = Field(p, 1);
	}
	assert(i == n);
    s->addClauseToGroup(Int_val(gid), c);
	CAMLreturn(Val_unit);
    }
}

value ms_new_clause_group(value satsolver)
{
    CAMLparam1(satsolver);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 
    CAMLreturn(Val_int(s->newClauseGroup()));
}

value ms_remove_clause_group(value satsolver, value gid)
{
    CAMLparam1(satsolver);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 
    s->removeClauseGroup(Int_val(gid));
    CAMLreturn(Val_unit);
}


// set_time_limit: satsolver -> int -> unit
value ms_set_time_limit(value satsolver, value f)
{
    CAMLparam2(satsolver, f);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 
    s->setTimeLimit(Int_val(f));
    CAMLreturn(Val_unit);
}

// solve: satsolver -> status
value ms_solve(value satsolver)
{
    CAMLparam1(satsolver);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 
    enter_blocking_section();
    solver_result sat = s->solveWithTimeout();
    leave_blocking_section();
//    printf("problem was %d\n", sat);
    CAMLreturn(Val_int((int) sat));
}

// get_assign: satsolver -> int -> int
value ms_get_assign(value satsolver, value v)
{
    CAMLparam2(satsolver, v);
    GroupSolver *s = *((GroupSolver **)Data_custom_val(satsolver)); 
    CAMLreturn(Val_int(s->model[Int_val(v)].toInt()));
}

} // extern "C"

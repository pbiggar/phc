%%
% Authors:
%   Peter Hawkins  <hawkinsp@cs.stanford.edu>
%
% Copyright (c) 2006,
%   The Board of Trustees of The Leland Stanford Junior University
% All rights reserved.
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
% 
% 1. Redistributions of source code must retain the above copyright notice,
% this list of conditions and the following disclaimer.
% 
% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.
% 
% 3. The names of the contributors may not be used to endorse or promote
% products derived from this software without specific prior written
% permission.
% 
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
% ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
% CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
% SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
% INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
% CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE.
%%

% ----------------------------------------------------------------------------
% STP-based implementation of the symbol integer operations
% Integer operations are modelled as boolean formulae. Floats are modelled as
% uninterpreted functions.
% ----------------------------------------------------------------------------

import "scalar.clp".
using solve_stp.

% ----------------------------------------------------------------------------
% Defines


    % fixed_vectors(N)
    % If the fixed_vectors predicate is defined, the length of all bit vectors
    % will be fixed at N bits long. If not defined, then all bit vectors will
    % be given default lengths determined by their type. 
predicate fixed_vectors(int).

% ----------------------------------------------------------------------------
% Integer expressions, bit vector and bit formulae

type g_vec = t_stp_bvec[g_arep, g_vecrep].
type g_guard_sat = t_stp_bit[g_arep].
type g_guard_asn = t_stp_counterexample[g_arep, g_vecrep].

% ----------------------------------------------------------------------------
    % Solve an optimization problem, maximizing or minimizing the first argument
    % subject to the constraints given in the second argument. The endpoint
    % is included in the range.
predicate scalar_maximize_sat(in scalar, in g_guard, out int).
predicate scalar_minimize_sat(in scalar, in g_guard, out int).

    % Return the lower and upper bounds on an integer expression subject to
    % constraints. The range returned is closed.
predicate scalar_bounds_sat(in scalar, in g_guard, out int, out int).

    % Solve an optimization problem, maximizing or minimizing the first argument
    % ensuring that the guard provided is valid for every value in the
    % range. These predicates also require an initial value for which the guard
    % is valid, and which will be contained in the target range.
    % The inital value must be provided because it does not seem possible
    % to deduce such a value through a SAT query (it's a QBF problem).
    %
predicate scalar_maximize_valid(in scalar, in int, in g_guard, out int).
predicate scalar_minimize_valid(in scalar, in int, in g_guard, out int).
predicate scalar_bounds_valid(in scalar, in int, in g_guard, out int, out int).

% ----------------------------------------------------------------------------

    % scalar_bvec(S, Vec)
    % Convert a scalar S to a bitvector
predicate scalar_bvec(in scalar, out g_vec) succeeds [once].

    % scalar_cmp_bval(Cmp, Guard)
    % Convert an integer comparison to a SAT formula
predicate scalar_cmp_bval(in scalar_cmp, out g_guard_sat) succeeds [once].

    % guard_bval(Guard, GuardSAT)
    % Convert an guard to a SAT formulae, including all of its integer
    % expression components.
predicate guard_bval(in g_guard, out g_guard_sat) succeeds [once].

    % int_range(Signed, Width, Min, Max)
    % Given a integer's signedness and width, return the minimum and maximum 
    % values that fit in that integer.
predicate int_range(in bool, in int, out int, out int).

predicate stp_apply_unop(in scalar_unop, in t_stp_bvec[X, Y], t_stp_bvec[X,Y])
    succeeds [once].

predicate stp_apply_binop(in scalar_binop, in t_stp_bvec[X, Y],
    in t_stp_bvec[X, Y], out t_stp_bvec[X,Y]) succeeds [once].

predicate stp_apply_cmp(in t_scalar_cmp, in t_stp_bvec[X, Y],
    in t_stp_bvec[X, Y], out t_stp_bit[X]) succeeds [once].


% ----------------------------------------------------------------------------
% Integer widths

    % bvec_width(Bits, Width)
    % A bitvector with width Width is modelled by a bitvector Bits bits long.
    % By default Width = Bits, unless fixed_vectors is defined
    % which forces us to use a specified width for all integers.
predicate bvec_width(in int, out int) succeeds [once].
bvec_width(_,     Width) :-  fixed_vectors(Width).
bvec_width(Width, Width) :- ~fixed_vectors(_). 

% ----------------------------------------------------------------------------

    % unconstrained(P, E, V)
    % Generate an unconstrained vector for E evaluated at P
predicate unconstrained(in pp, in c_exp, out g_vec) succeeds [once].
unconstrained(P, E, id_sbv(vr_i{P, E}, S, bvec_width(Bits))) :- 
    exp_tint(E, K), 
    ikind_bits(K, S, Bits).

predicate unmodelled(in scalar, out g_vec) succeeds [once].
unmodelled(S, id_sbv(vr_u{S}, Signed, Bits)) :-
    scalar_kind(S, sk_int{Signed, Bits}).

unmodelled(S, id_sbv(vr_u{S}, false, Bits)) :-
    scalar_kind(S, sk_float{Bits}).

% ----------------------------------------------------------------------------

stp_apply_unop(su_not, A, sbv_bnot(A)) :- .
stp_apply_unop(su_neg, A, -A) :- .

stp_apply_binop(sb_plus,  A, B, A + B) :- .
stp_apply_binop(sb_minus, A, B, A - B) :- .
stp_apply_binop(sb_mul,   A, B, A * B) :- .
stp_apply_binop(sb_div,   A, B, A / B) :- .
stp_apply_binop(sb_mod,   A, B, A `mod` B) :- .
stp_apply_binop(sb_and,   A, B, A `and` B) :- .
stp_apply_binop(sb_or,    A, B, A `or` B) :- .
stp_apply_binop(sb_xor,   A, B, A `xor` B) :- .
stp_apply_binop(sb_shiftlt, A, B, A `shl` B) :- .
stp_apply_binop(sb_shiftrt, A, B, A `shr` B) :- .

stp_apply_cmp(sc_lt, A, B, A < B) :- .
stp_apply_cmp(sc_le, A, B, A <= B) :- .
stp_apply_cmp(sc_ge, A, B, A >= B) :- .
stp_apply_cmp(sc_gt, A, B, A > B) :- .
stp_apply_cmp(sc_eq, A, B, A == B) :- .
stp_apply_cmp(sc_ne, A, B, A != B) :- .

% ----------------------------------------------------------------------------
% Convert a integer expression to a bvec

    % We don't model floating point expressions, instead we treat them
    % as uninterpreted functions.
scalar_bvec(FS, unmodelled(FS)) :-
    scalar_kind(FS, sk_float{_}).

scalar_bvec(s_int_const{N, Signed, Bits},
	    int_sbv(N, Signed, bvec_width(Bits))) :- .

scalar_bvec(s_unconstrained{ID, sk_int{Signed, Bits}}, BV) :-
    BV = id_sbv(ID, Signed, bvec_width(Bits)).

scalar_bvec(s_cast{IE0, sk_int{Signed, Bits}}, BV) :-
    scalar_bvec(IE0, BV0),
    bvec_width(Bits, Width),
    Signed = true, sbv_length_cast(BV0, Width, BV).



predicate guard_collect(in list[guarded_scalar], in g_vec, out g_vec).
guard_collect([], BV, BV) :- .
guard_collect([pair{E,G}|Gs], BV0, BV) :-
    BV1 = sbv_guard(scalar_bvec(E), guard_bval(G)), 
    guard_collect(Gs, BV0 `or` BV1, BV).

scalar_bvec(s_guard{GE}, BV) :-
    % XXX: This is ugly -- we need a notation for zero.
    scalar_kind(s_guard{GE}, sk_int{_, _}),
    map_to_sorted_list(GE, [pair{E,G}|Gs]),
    guard_collect(Gs, sbv_guard(scalar_bvec(E), guard_bval(G)), BV).

scalar_bvec(S, V) :-
    S = s_unop{Op, IE},
    scalar_kind(S, sk_int{_, _}),
    stp_apply_unop(Op, scalar_bvec(IE), V).

scalar_bvec(S, V) :-
    S = s_binop{Op, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    stp_apply_binop(Op, scalar_bvec(IE0), scalar_bvec(IE1), V).

% ----------------------------------------------------------------------------
% Guard to SAT formula conversion

    % Base cases -- trivially true or false
guard_bval(G, bool_s(B)) :- #bool_g(B, G).

    % Conjunction/disjunction/negation
guard_bval(RG, guard_bval(RG0) && guard_bval(RG1)) :- #and(RG0, RG1, RG).
guard_bval(RG, guard_bval(RG0) || guard_bval(RG1)) :- #or(RG0, RG1, RG).
guard_bval(RG, !guard_bval(RG0)) :- #not(RG0, RG).

    % Integer comparisons
guard_bval(RG, scalar_cmp_bval(RC)) :- #id_g(br_cmp{RC}, RG).

    % Unconstrained extra bits
guard_bval(RG, id_s(AB)) :- #id_g(br_abit{AB}, RG).

?guard_bval(S,_), ~guard_bval(S,_), +warning("guard_bval failed", S).

% ----------------------------------------------------------------------------
% Comparison operation to SAT formula conversion
scalar_cmp_bval(sc{CmpOp, A, B}, G) :-
    stp_apply_cmp(CmpOp, scalar_bvec(A), scalar_bvec(B), G).

scalar_cmp_bval(sc_eqz{A}, sbv_eqz(scalar_bvec(A))) :- .
    
?scalar_cmp_bval(S,_), ~scalar_cmp_bval(S,_), 
    +warning("scalar_cmp_bval failed", S).
    
% ----------------------------------------------------------------------------
% Satisfiability predicates for upstream analyses

guard_valid(G) :- stp_valid(guard_bval(G), bool_s(true)).
guard_sat(G) :- ~guard_valid(!G).
    
guard_sat_asn(G, Assignment) :-
    stp_invalid(guard_bval(!G), bool_s(true), Assignment).

asn_value(Assignment, V, N) :-
    traceval_scalar_nokind(V, S),
    scalar_bvec(S, BV),
    cexample_bv(Assignment, BV, N).
    
%    #asnbv(Assignment, BV, N).

% ----------------------------------------------------------------------------


int_range(true, Width, -N, N - 1) :- N = 2 `exp` (Width - 1).
int_range(false, Width, 0, (2 `exp` Width) - 1) :- .


% ----------------------------------------------------------------------------

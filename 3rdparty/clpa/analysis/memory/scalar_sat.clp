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
% SAT-based implementation of the symbol integer operations
% Integer operations are modelled as boolean formulae. Floats are modelled as
% uninterpreted functions.
% ----------------------------------------------------------------------------

import "scalar.clp".
using solve_bitvector.

% ----------------------------------------------------------------------------
% Defines


    % fixed_vectors(N)
    % If the fixed_vectors predicate is defined, the length of all bit vectors
    % will be fixed at N bits long. If not defined, then all bit vectors will
    % be given default lengths determined by their type. 
predicate fixed_vectors(int).

    % omit_guard_sat()
    % If omit_guard_sat() is defined, then the default implementations
    % of guard_sat, guard_sat_asn, and guard_valid will be omitted
    % and these predicates will always fail
predicate omit_guard_sat().

% ----------------------------------------------------------------------------
% Integer expressions, bit vector and bit formulae

type g_vec = bvec[g_vecrep, g_arep].
type g_guard_sat = bval[bvecbit[g_vecrep, g_arep]].
type g_guard_asn = bval_asn[bvecbit[g_vecrep, g_arep]].

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

    % scalar_bvec(S, Constraints, Vec)
    % Convert a scalar S to a bitvector and a guard representing
    % any additional constraints on the bitvector. The constraints are 
    % additional information that we know about the imprecise operations
    % in the bitvector. If the constraint guard is not satisfied for a given
    % value of the bitvector then that value is an artifact of imprecise
    % modeling and does not correspond to a possible real value.
    % 
predicate scalar_bvec(in scalar, out g_guard_sat, out g_vec) succeeds [once].

    % scalar_cmp_bval(Cmp, Constraints, Guard)
    % Convert an integer comparison to a SAT formula
predicate scalar_cmp_bval(in scalar_cmp, out g_guard_sat, out g_guard_sat)
    succeeds [once].

    % guard_bval(Guard, Constraints, GuardSAT)
    % Convert an guard to a SAT formulae, including all of its integer
    % expression components.
predicate guard_bval(in g_guard, out g_guard_sat, out g_guard_sat)
    succeeds [once].

    % int_range(Signed, Width, Min, Max)
    % Given a integer's signedness and width, return the minimum and maximum 
    % values that fit in that integer.
predicate int_range(in bool, in int, out int, out int) succeeds [once].

% ----------------------------------------------------------------------------
% Integer widths

    % bvec_width(Bits, Width)
    % A bitvector with width Width is modelled by a bitvector Bits bits long.
    % By default Width = Bits, unless fixed_vectors is defined
    % which forces us to use a specified width for all integers.
predicate bvec_width(in int, out int).
bvec_width(_,     Width) :-  fixed_vectors(Width).
bvec_width(Width, Width) :- ~fixed_vectors(_). 

% ----------------------------------------------------------------------------

    % unconstrained(P, E, V)
    % Generate an unconstrained vector for E evaluated at P
predicate unconstrained(in pp, in c_exp, out g_vec).
unconstrained(P, E, V) :- 
    exp_tint(E, K), 
    ikind_bits(K, S, Bits),
    bvec_width(Bits, Width),
    #id_bv(vr_i{P,E}, S, true, Width, V).

predicate unmodelled(in scalar, out g_vec).
unmodelled(S, V) :-
    scalar_kind(S, sk_int{Signed, Bits}),
    #id_bv(vr_u{S}, Signed, false, Bits, V).

unmodelled(S, V) :-
    scalar_kind(S, sk_float{Bits}),
    #id_bv(vr_u{S}, false, false, Bits, V).

% ----------------------------------------------------------------------------
% Convert a integer expression to a bvec

    % We don't model floating point expressions, instead we treat them
    % as uninterpreted functions.
scalar_bvec(FS, G, BV) :-
    scalar_kind(FS, sk_float{_}),
    unmodelled(FS, BV),
    #bool_g(true, G).

scalar_bvec(s_int_const{N, Signed, Bits}, G, BV) :- 
    bvec_width(Bits, Width),
    #int_bv(N, Signed, Width, BV),
    #bool_g(true, G).

scalar_bvec(s_unconstrained{ID, sk_int{Sign, Bits}}, G, BV) :- 
    bvec_width(Bits, Width),
    #id_bv(ID, Sign, false, Width, BV),
    #bool_g(true, G).

scalar_bvec(s_cast{IE0, sk_int{Signed, Bits}}, G, BV) :-
    scalar_bvec(IE0, G, BV0),
    bvec_width(Bits, Width),
    #bv_cast(BV0, Signed, Width, BV).
    
    % gexpr(GEs, BV0, BV)
    % Compute a bitvector BV that is the disjunction of guarded expressions GEs
    % and BV0.
predicate gexpr_bvec(in list[guarded_scalar], in g_guard_sat, out g_guard_sat, 
    in g_vec, out g_vec).
gexpr_bvec([], CG, CG, BV, BV) :- .
gexpr_bvec([pair{I, G}|Gs], CGs0, CGs, BV0, BV) :-
    scalar_bvec(I, CV, V),
    guard_bval(G, CG, GBV),
    #bv_guard(V, GBV, VG),
    #bv_bor(BV0, VG, BV1),
    and3(CV, CG, CGs0, CGs1),
    gexpr_bvec(Gs, CGs1, CGs, BV1, BV).

scalar_bvec(s_guard{GE}, CGs, BV) :-
    % XXX: This is ugly -- we need a notation for zero.
    scalar_kind(s_guard{GE}, sk_int{_, _}),
    map_to_sorted_list(GE, [pair{E, G}|Gs]),
    guard_bval(G, CG, GBV),
    scalar_bvec(E, CV, BV0),
    #bv_guard(BV0, GBV, BV1),
    #and(CG, CV, CGs0),
    gexpr_bvec(Gs, CGs0, CGs, BV1, BV).

?scalar_bvec(s_guard{M}, _, _),
    map_to_sorted_list(M, L),
    list_length(L, Len),
    int_eq(Len, 0),
    +warning("Empty guarded expression passed to scalar_bvec").

scalar_bvec(s_unop{su_neg, IE0}, G, BV) :- 
    scalar_kind(IE0, sk_int{_, _}),
    scalar_bvec(IE0, G, BV0), 
    #bv_neg(BV0, BV).

scalar_bvec(s_unop{su_not, IE0}, G, BV) :- 
    scalar_kind(IE0, sk_int{_, _}),
    scalar_bvec(IE0, G, BV0), 
    #bv_bnot(BV0, BV).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_plus, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    #bv_add(BV0, BV1, BV),
    #and(G0, G1, G).
    
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_minus, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    #bv_sub(BV0, BV1, BV),
    #and(G0, G1, G).
    
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_and, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    #bv_band(BV0, BV1, BV),
    #and(G0, G1, G).
    
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_or, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    #bv_bor(BV0, BV1, BV),
    #and(G0, G1, G).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_xor, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    #bv_bxor(BV0, BV1, BV),
    #and(G0, G1, G).


% We model multiplication and shifts exactly when one argument
% is constant.
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_mul, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    #bv_int(BV0, N0), 
    #bv_mul(BV1, N0, BV),
    #and(G0, G1, G).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_mul, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    ~#bv_int(BV0, _),
    #bv_int(BV1, N1), 
    #bv_mul(BV0, N1, BV),
    #and(G0, G1, G).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_shiftlt, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1), 
    #bv_int(BV1, N1), 
    #bv_shl(BV0, N1, BV),
    #and(G0, G1, G).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_shiftrt, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1), 
    #bv_int(BV1, N1), 
    #bv_shr(BV0, N1, BV),
    #and(G0, G1, G).

predicate unmodelled_int_binop(in scalar, in g_vec, in g_vec, out g_vec).
unmodelled_int_binop(S, _BV0, _BV1, BV) :-
    unmodelled(S, BV).

% Otherwise we model multiplication and shifts by unconstrained values 
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_mul, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    ~#bv_int(BV0, _),
    ~#bv_int(BV1, _), 
    unmodelled_int_binop(S, BV0, BV1, BV),
    #and(G0, G1, G).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_shiftlt, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    ~#bv_int(BV1, _), 
    unmodelled_int_binop(S, BV0, BV1, BV),
    #and(G0, G1, G).

scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_shiftrt, IE0, IE1},
    scalar_kind(S, sk_int{_, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    ~#bv_int(BV1, _), 
    unmodelled_int_binop(S, BV0, BV1, BV),
    #and(G0, G1, G).


% Division and modulus are always modelled by unconstrained values

    % A divisor is treated as constant and handled specially if it is a
    % non-zero constant. -1 is also ignored since it can lead to overflow
    % and we can't deduce anything special in that case anyway.
predicate divisor_constant(in g_vec, out int).
divisor_constant(BV, Divisor) :-
    #bv_int(BV, Divisor),
    Divisor \= 0,
    int_ne(Divisor, -1).

predicate model_unsigned_division(in scalar, in g_guard_sat, in g_vec, 
    in g_guard_sat, in g_vec, out g_guard_sat, out g_vec).
predicate model_signed_division(in scalar, in int, in g_guard_sat, in g_vec, 
    in g_guard_sat, in g_vec, out g_guard_sat, out g_vec).

    % Unsigned division with a constant divisor
    % quotient <= max_int / divisor
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_div, IE0, IE1},
    scalar_kind(S, sk_int{false, Bits}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    divisor_constant(BV1, Divisor),
    model_unsigned_division(S, G0, BV0, G1, BV1, GU, BV),
    
    int_range(false, Bits, _, IntMax),
    int_div(IntMax, Divisor, DRangeMax),
    #int_bv(DRangeMax, false, Bits, BVRangeMax),

    #bv_le(BV, BVRangeMax, GR),
    #and(GU, GR, G).

    % Unsigned division with a variable divisor
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_div, IE0, IE1},
    scalar_kind(S, sk_int{false, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    ~divisor_constant(BV1, _),
    model_unsigned_division(S, G0, BV0, G1, BV1, G, BV).

    % Common part of unsigned divison 
    % Unsigned division never overflows, and quotient <= dividend
model_unsigned_division(S, G0, BV0, G1, BV1, G, BV)  :- 
    unmodelled_int_binop(S, BV0, BV1, BV),
    #bv_le(BV, BV0, G2),
    and3(G0, G1, G2, G).
    
    % Signed division with a constant divisor (divisor != -1)
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_div, IE0, IE1},
    scalar_kind(S, sk_int{true, Bits}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    divisor_constant(BV1, Divisor),
    int_range(true, Bits, IntMin, IntMax),
    int_div(IntMax, Divisor, D1),
    int_div(IntMin, Divisor, D2),
    int_max(D1, D2, DMax),
    int_min(D1, D2, DMin),
    #int_bv(DMax, true, Bits, BVMax),
    #int_bv(DMin, true, Bits, BVMin),
    model_signed_division(S, Bits, G0, BV0, G1, BV1, GM, BV),
    #bv_ge(BV, BVMin, GMin),
    #bv_le(BV, BVMax, GMax),
    and3(GM, GMin, GMax, G).


    % Signed division with a variable divisor 
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_div, IE0, IE1},
    scalar_kind(S, sk_int{true, Bits}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    ~divisor_constant(BV1, _),
    model_signed_division(S, Bits, G0, BV0, G1, BV1, G, BV).

    
    % Signed division overflows iff the divisor is -1 and the dividend is 
    % int_min (since there is one more negative number than positive numbers
    % in 2s-complement). Range limit: |quotient| <= |dividend|
model_signed_division(S, N, G0, BV0, G1, BV1, G, BV)  :- 
    int_range(true, N, IntMin, _),
    #int_bv(IntMin, true, N, Min),
    #bv_eq(BV0, Min, BV0Min),

    unmodelled(S, V),
    % Overflow bit calculation
    #bv_split(V, true, _, Bits),
    #bv_oflow(BV0, O0),
    #bv_oflow(BV1, O1),
    #int_bv(-1, true, N, M1),
    #bv_eq(BV1, M1,  OD2),
    #and(BV0Min, OD2, OD),
    or3(O0, O1, OD, O),
    #bv_split(BV, true, O, Bits),

    % Range guard calculation. No range guard is applied or needed if 
    % BV0 = IntMin, since calculating the absolute value of BV0 would overflow.
    int_sub(N, 1, SignBit),
    #bv_bit(BV0, SignBit, S0),

    #bv_neg(BV0, NBV0),
    #bv_ite(S0, NBV0, BV0, P0),
    #bv_ite(S0, BV0, NBV0, N0),
    #bv_le(N0, BV, R0),
    #bv_le(BV, P0, R1),
    #and(R0, R1, R2),
    #not(BV0Min, NBV0Min),
    #imp(NBV0Min, R2, R),
    and3(G0, G1, R, G).


    % Unsigned modulus.
    % r = a % b is modelled as an unconstrained value with the constraint:
    % (b != 0) -> (r < b)
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_mod, IE0, IE1},
    scalar_kind(S, sk_int{false, _}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    unmodelled_int_binop(S, BV0, BV1, BV),

    #bv_nez(BV1, NonZero),
    #bv_lt(BV, BV1, P),
    #imp(NonZero, P, C),

    and3(G0, G1, C, G).
    
    % Signed modulus: r = a % b
    % r is modelled as a unconstrained value subject to the constraint:
    % if (b == 0) then unconstrained else
    % if (b == INT_MIN) then a else
    % if (a >= 0) then 0 <= a < |b| else -|b| < a <= 0 
scalar_bvec(S, G, BV)  :- 
    S = s_binop{sb_mod, IE0, IE1},
    scalar_kind(S, sk_int{true, Len}),
    scalar_bvec(IE0, G0, BV0), 
    scalar_bvec(IE1, G1, BV1),
    unmodelled_int_binop(S, BV0, BV1, BV),

    int_sub(Len, 1, SignBit),

    % Modelling of r = a % b
    int_range(true, Len, IntMin, _),
    #int_bv(IntMin, true, Len, Min),

    % b = 0? If so leave the result unconstrained.
    #bv_nez(BV1, NonZeroG),

    % b = IntMin? If so, r = a.
    #bv_eq(Min, BV1, ModIntMinG),
    #bv_eq(BV0, BV, UnchangedG),
    
    % b != IntMin
    #int_bv(0, true, Len, Zero),
    #bv_bit(BV0, SignBit, S0),
    #bv_bit(BV1, SignBit, S1),

    % PD = +|b| and ND = -|b|
    % Only valid if b != IntMin since otherwise |b| is out of range
    #bv_neg(BV1, NBV1), 
    #bv_ite(S1, NBV1, BV1, PD),
    #bv_ite(S1, BV1, NBV1, ND),

    % a >= 0 -> 0 <= r < |b|
    #bv_le(Zero, BV, P0),
    #bv_lt(BV, PD, P1),
    #and(P0, P1, P),

    % a < 0 -> -|b| < r <= 0
    #bv_lt(ND, BV, N0),
    #bv_le(BV, Zero, N1),
    #and(N0, N1, N),
    #ite(S0, N, P, C0),

    #ite(ModIntMinG, UnchangedG, C0, C1),
    #imp(NonZeroG, C1, C),

    and3(G0, G1, C, G).

?scalar_bvec(S,_,_), ~scalar_bvec(S,_,_), +warning("scalar_bvec failed", S).

% ----------------------------------------------------------------------------
% Guard to SAT formula conversion

    % Base cases -- trivially true or false
guard_bval(G, C, B) :- #bool_g(true, G), #bool_g(true, B), #bool_g(true, C).
guard_bval(G, C, B) :- #bool_g(false, G), #bool_g(false, B), #bool_g(true, C).

    % Conjunction
guard_bval(RG, C, NG) :-
    #and(RG0, RG1, RG),
    guard_bval(RG0, C1, NG0),
    guard_bval(RG1, C2, NG1),
    #and(C1, C2, C),
    #and(NG0, NG1, NG).

    % Disjunction
guard_bval(RG, C, NG) :-
    #or(RG0, RG1, RG),
    guard_bval(RG0, C1, NG0),
    guard_bval(RG1, C2, NG1),
    #and(C1, C2, C),
    #or(NG0, NG1, NG).

    % Negation
guard_bval(RG, C, NG) :-
    #not(RG0, RG),
%    +print("not rg0", RG0),
    guard_bval(RG0, C, NG0),
    #not(NG0, NG).

%?guard_bval(X,_), +print("queried", X).

    % Integer comparisons
guard_bval(RG, C, NG) :-
    #id_g(br_cmp{RC}, RG),
    scalar_cmp_bval(RC, C, NG).

    % Overflow bits
guard_bval(RG, C, O) :-
    #id_g(br_ioverflow{RE}, RG),
    scalar_bvec(RE, C, V),
    #bv_oflow(V, O).

    % Unconstrained extra bits
guard_bval(RG, C, NG) :-
    #id_g(br_abit{AB}, RG),
    #id_g(b_abit{AB}, NG),
    #bool_g(true, C).

?guard_bval(S,_,_), ~guard_bval(S,_,_), +warning("guard_bval failed", S).

% ----------------------------------------------------------------------------
% Comparison operation to SAT formula conversion
scalar_cmp_bval(sc{sc_eq, A, B}, C, G) :-
    scalar_bvec(A, C1, AV),
    scalar_bvec(B, C2, BV),
    #bv_eq(AV, BV, G),
    #and(C1, C2, C).

scalar_cmp_bval(sc{sc_ne, A, B}, C, G) :-
    scalar_bvec(A, C1, AV),
    scalar_bvec(B, C2, BV),
    #bv_ne(AV, BV, G),
    #and(C1, C2, C).

scalar_cmp_bval(sc{sc_lt, A, B}, C, G) :-
    scalar_bvec(A, C1, AV),
    scalar_bvec(B, C2, BV),
    #bv_lt(AV, BV, G),
    #and(C1, C2, C).

scalar_cmp_bval(sc{sc_le, A, B}, C, G) :-
    scalar_bvec(A, C1, AV),
    scalar_bvec(B, C2, BV),
    #bv_le(AV, BV, G),
    #and(C1, C2, C).

scalar_cmp_bval(sc{sc_ge, A, B}, C, G) :-
    scalar_bvec(A, C1, AV),
    scalar_bvec(B, C2, BV),
    #bv_ge(AV, BV, G),
    #and(C1, C2, C).

scalar_cmp_bval(sc{sc_gt, A, B}, C, G) :-
    scalar_bvec(A, C1, AV),
    scalar_bvec(B, C2, BV),
    #bv_gt(AV, BV, G),
    #and(C1, C2, C).

scalar_cmp_bval(sc_eqz{A}, C, G) :-
    scalar_bvec(A, C, AV),
    #bv_eqz(AV, G).
    
?scalar_cmp_bval(S,_,_), ~scalar_cmp_bval(S,_,_), 
    +warning("scalar_cmp_bval failed", S).
    
% ----------------------------------------------------------------------------
% Satisfiability predicates for upstream analyses

guard_sat(G) :-
    ~omit_guard_sat(),
    guard_bval(G, C, B),
    #and(C, B, SG),
    #sat(SG).
    
guard_sat_asn(G, Assignment) :-
    ~omit_guard_sat(),
    guard_bval(G, C, B),
    #and(C, B, SG),
    #satasn(SG, Assignment).

guard_valid(G) :-
    ~omit_guard_sat(),
    #not(G, NG), ~guard_sat(NG).

asn_value(Assignment, V, N) :-
    traceval_scalar_nokind(V, S),
    scalar_bvec(S, _, BV),
    #asnbv(Assignment, BV, N).

% ----------------------------------------------------------------------------

    % #bv_size(BV, Signed, Width)
    % Given a bitvector BV, return its signedness and width
predicate #bv_size(in g_vec, out bool, out int).
#bv_size(BV, Signed, Width) :-
    #bv_split(BV, Signed, _OFlow, Bits),
    list_length(Bits, Width).

% ----------------------------------------------------------------------------

int_range(true, Width, Min, Max) :-
    int_sub(Width, 1, W1),
    int_exp(2, W1, NM),
    int_neg(NM, Min),
    int_sub(NM, 1, Max).

int_range(false, Width, 0, Max) :-
    int_exp(2, Width, NM),
    int_sub(NM, 1, Max).

% ----------------------------------------------------------------------------

    % bv_minimize(Guard, Bitvector, Out)
    % Find the minimum value of a bitvector subject to a guard. The guard
    % must be satisfiable.
predicate bv_minimize(in g_guard_sat, in g_vec, out int).
predicate bv_maximize(in g_guard_sat, in g_vec, out int).


    % Find the minimum value of an integer expression subject to constraints
scalar_minimize_sat(IE, G, Out) :-
    guard_bval(G, GC, BG),
    scalar_bvec(IE, VC, BV),
    and3(GC, VC, BG, B),
    #sat(B),    % Check that the problem is feasible
    bv_minimize(B, BV, Out).

    % Find the maximum value of an integer expression subject to constraints
scalar_maximize_sat(IE, G, Out) :-
    guard_bval(G, GC, BG),
    scalar_bvec(IE, VC, BV),
    and3(GC, VC, BG, B),
    #sat(B),    % Check that the problem is feasible
    bv_maximize(B, BV, Out).

    % Find the bounds of an integer expression subject to constraints
scalar_bounds_sat(IE, G, Min, Max) :-
    guard_bval(G, GC, BG),
    scalar_bvec(IE, VC, BV),
    and3(GC, VC, BG, B),
    #sat(B),    % Check that the problem is feasible
    bv_minimize(B, BV, Min),
    bv_maximize(B, BV, Max).

% ----------------------------------------------------------------------------

    
    % bv_minimize_rec(Guard, Bitvector, Signed, Width, Min, Max, Out)
    % Given a bitvector, guard, signedness and width, an infeasible lower
    % bound and a feasible upper bound, find the minimum value of the bitvector
    % in the range (Min, Max] that satisfies the guard.
predicate bv_minimize_rec(in g_guard_sat, in g_vec, in bool, in int, in int, 
    in int, out int).
predicate bv_maximize_rec(in g_guard_sat, in g_vec, in bool, in int, in int, 
    in int, out int).

    % Is a bound for minimization/maximization problem feasible?
predicate bv_minimize_feasible(in g_guard_sat, in g_vec, in bool, in int,
    in int).
predicate bv_maximize_feasible(in g_guard_sat, in g_vec, in bool, in int, 
    in int).

    % If the minimum value is feasible it is the solution
bv_minimize(G, BV, Min) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, Min, _Max),
    bv_minimize_feasible(G, BV, Signed, Width, Min).

    % If the minimum value is infeasible, we have to search.
bv_minimize(G, BV, Out) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, Min, Max),
    ~bv_minimize_feasible(G, BV, Signed, Width, Min),
    bv_minimize_rec(G, BV, Signed, Width, Min, Max, Out).

    % If the maximum value is feasible it is the solution
bv_maximize(G, BV, Max) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, _Min, Max),
    bv_maximize_feasible(G, BV, Signed, Width, Max).

    % If the maximum value is infeasible, we have to search.
bv_maximize(G, BV, Out) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, Min, Max),
    ~bv_maximize_feasible(G, BV, Signed, Width, Max),
    bv_maximize_rec(G, BV, Signed, Width, Min, Max, Out).


    % Test the satisfiability of an upper bound for a bitvector
bv_minimize_feasible(B, BV, Signed, Width, Max) :-
    #int_bv(Max, Signed, Width, BVMax),
    #bv_le(BV, BVMax, GMax),
    #and(B, GMax, S),
    #sat(S).

    % Test the satisfiability of an lower bound for a bitvector
bv_maximize_feasible(B, BV, Signed, Width, Min) :-
    #int_bv(Min, Signed, Width, BVMin),
    #bv_ge(BV, BVMin, GMin),
    #and(B, GMin, S),
    #sat(S).

    % Binary seach for the minimum value that satisfies the guard
    % We maintain the invariant that Max is feasible but Min is infeasible
bv_minimize_rec(B, BV, Signed, Width, Min, Max, Max) :-
    int_add(Min, 1, Max).

bv_minimize_rec(B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    bv_minimize_feasible(B, BV, Signed, Width, Val),
    bv_minimize_rec(B, BV, Signed, Width, Min, Val, Out).

bv_minimize_rec(B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    ~bv_minimize_feasible(B, BV, Signed, Width, Val),
    bv_minimize_rec(B, BV, Signed, Width, Val, Max, Out).

    % Binary seach for the maximum value that satisfies the guard
    % We maintain the invariant that Max is infeasible but Min is feasible
bv_maximize_rec(B, BV, Signed, Width, Min, Max, Min) :-
    int_add(Min, 1, Max).

bv_maximize_rec(B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    bv_maximize_feasible(B, BV, Signed, Width, Val),
    bv_maximize_rec(B, BV, Signed, Width, Val, Max, Out).

bv_maximize_rec(B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    ~bv_maximize_feasible(B, BV, Signed, Width, Val),
    bv_maximize_rec(B, BV, Signed, Width, Min, Val, Out).

% ----------------------------------------------------------------------------
predicate bv_maximize_valid(in g_guard_sat, in g_guard_sat, in int, in g_vec, 
    out int).
predicate bv_maximize_valid_rec(in g_guard_sat, in g_guard_sat, in g_vec, 
    in bool, in int, in int, in int, out int).
predicate bv_maximize_valid_feasible(in g_guard_sat, in g_guard_sat, in g_vec, 
    in bool, in int, in int).

predicate bv_minimize_valid(in g_guard_sat, in g_guard_sat, in int, in g_vec, 
    out int).
predicate bv_minimize_valid_rec(in g_guard_sat, in g_guard_sat, in g_vec, 
    in bool, in int, in int, in int, out int).
predicate bv_minimize_valid_feasible(in g_guard_sat, in g_guard_sat, in g_vec, 
    in bool, in int, in int).

    % Find the maximum value of an integer expression subject to constraints
scalar_maximize_valid(IE, V0, G, Out) :-
    guard_bval(G, GC, BG),
    scalar_bvec(IE, VC, BV),
    #and(GC, VC, C),
    #bv_size(BV, Signed, Width),
    #int_bv(V0, Signed, Width, BV0),

    % Check that the problem is feasible
    #bv_eq(BV, BV0, GEq),
    #imp(GEq, BG, Feasible),
    #not(Feasible, NFeasible),
    #and(NFeasible, C, FG),
    ~#sat(FG),    

    #bv_ge(BV, BV0, GGe),
    #imp(GGe, BG, CL),

    bv_maximize_valid(C, CL, V0, BV, Out).

    % Find the minimum value of an integer expression subject to constraints
scalar_minimize_valid(IE, V0, G, Out) :-
    guard_bval(G, GC, BG),
    scalar_bvec(IE, VC, BV),
    #and(GC, VC, C),
    #bv_size(BV, Signed, Width),
    #int_bv(V0, Signed, Width, BV0),

    % Check that the problem is feasible
    #bv_eq(BV, BV0, GEq),
    #imp(GEq, BG, Feasible),
    #not(Feasible, NFeasible),
    #and(NFeasible, C, FG),
    ~#sat(FG),    

    #bv_le(BV, BV0, GLe),
    #imp(GLe, BG, CL),

    bv_minimize_valid(C, CL, V0, BV, Out).

    % Find the bounds of an integer expression subject to constraints
scalar_bounds_valid(IE, V0, G, Min, Max) :-
    guard_bval(G, GC, BG),
    scalar_bvec(IE, VC, BV),
    #and(GC, VC, C),
    #bv_size(BV, Signed, Width),
    #int_bv(V0, Signed, Width, BV0),

    % Check that the problem is feasible
    #bv_eq(BV, BV0, GEq),
    #imp(GEq, BG, Feasible),
    #not(Feasible, NFeasible),
    #and(NFeasible, C, FG),
    ~#sat(FG),    

    #bv_le(BV, BV0, GLe),
    #imp(GLe, BG, CLMin),
    #bv_ge(BV, BV0, GGe),
    #imp(GGe, BG, CLMax),

    bv_minimize_valid(C, CLMin, V0, BV, Min),
    bv_maximize_valid(C, CLMax, V0, BV, Max).


    % If the minimum value is feasible it is the solution
bv_minimize_valid(C, G, V0, BV, Min) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, Min, _Max),
    bv_minimize_valid_feasible(C, G, BV, Signed, Width, Min).

    % If the minimum value is infeasible, we have to search.
bv_minimize_valid(C, G, V0, BV, Out) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, Min, _Max),
    ~bv_minimize_valid_feasible(C, G, BV, Signed, Width, Min),
    bv_minimize_valid_rec(C, G, BV, Signed, Width, Min, V0, Out).

    % If the maximum value is feasible it is the solution
bv_maximize_valid(C, G, V0, BV, Max) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, _Min, Max),
    bv_maximize_valid_feasible(C, G, BV, Signed, Width, Max).

    % If the maximum value is infeasible, we have to search.
bv_maximize_valid(C, G, V0, BV, Out) :-
    #bv_size(BV, Signed, Width),
    int_range(Signed, Width, _, Max),
    ~bv_maximize_valid_feasible(C, G, BV, Signed, Width, Max),
    bv_maximize_valid_rec(C, G, BV, Signed, Width, V0, Max, Out).

    % Test the feasibility of an lower bound for a bitvector
bv_minimize_valid_feasible(C, B, BV, Signed, Width, Min) :-
    #int_bv(Min, Signed, Width, BVMin),
    #bv_ge(BV, BVMin, GMin),
    #imp(GMin, B, S),
    #not(S, NS),
    #and(C, NS, G),
    ~#sat(G).

    % Test the feasibility of an upper bound for a bitvector
bv_maximize_valid_feasible(C, B, BV, Signed, Width, Max) :-
    #int_bv(Max, Signed, Width, BVMax),
    #bv_le(BV, BVMax, GMax),
    #imp(GMax, B, S),
    #not(S, NS),
    #and(C, NS, G),
    ~#sat(G).

    % Binary seach for the minimum value that ensures the guard is true
    % We maintain the invariant that Max is feasible but Min is infeasible
bv_minimize_valid_rec(C, B, BV, Signed, Width, Min, Max, Max) :-
    int_add(Min, 1, Max).

bv_minimize_valid_rec(C, B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    bv_minimize_valid_feasible(C, B, BV, Signed, Width, Val),
    bv_minimize_valid_rec(C, B, BV, Signed, Width, Min, Val, Out).

bv_minimize_valid_rec(C, B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    ~bv_minimize_valid_feasible(C, B, BV, Signed, Width, Val),
    bv_minimize_valid_rec(C, B, BV, Signed, Width, Val, Max, Out).

    % Binary seach for the maximum value that ensures the guard is true 
    % We maintain the invariant that Max is infeasible but Min is feasible
bv_maximize_valid_rec(C, B, BV, Signed, Width, Min, Max, Min) :-
    int_add(Min, 1, Max).

bv_maximize_valid_rec(C, B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    bv_maximize_valid_feasible(C, B, BV, Signed, Width, Val),
    bv_maximize_valid_rec(C, B, BV, Signed, Width, Val, Max, Out).

bv_maximize_valid_rec(C, B, BV, Signed, Width, Min, Max, Out) :-
    int_add(Min, 1, M1),
    int_gt(Max, M1),
    int_add(Min, Max, Sum),
    int_div(Sum, 2, Val),
    ~bv_maximize_valid_feasible(C, B, BV, Signed, Width, Val),
    bv_maximize_valid_rec(C, B, BV, Signed, Width, Min, Val, Out).

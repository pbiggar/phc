%%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
%   Thomas Dillig  <tdillig@stanford.edu>
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

%-----------------------------------------------------------------------------%
% Miscellaneous utility predicates.
%-----------------------------------------------------------------------------%

using solve_sat.
using solve_bitvector.
using strops.

%-----------------------------------------------------------------------------%
% Interface
%-----------------------------------------------------------------------------%
    % greaterthan(A, B)
    % The reverse of the builtin lessthan predicate.
predicate greaterthan(in T, in T).

    % boolean negation
predicate bool_not(in bool, out bool) succeeds [once].

    % Test a bval for validity.
predicate #valid(in bval[T]).

    % and[3-6]
    % Higher arity versions of #and
    % Deprecated -- use the && operator.
predicate and3(in G1:bval[T], in G2:bval[T], in G3:bval[T], RES:bval[T]).
predicate and4(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    RES:bval[T]).
predicate and5(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], RES:bval[T]).
predicate and6(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], in G6:bval[T], RES:bval[T]).

    % Alternate names for the above
predicate #and3(in G1:bval[T], in G2:bval[T], in G3:bval[T], RES:bval[T]).
predicate #and4(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    RES:bval[T]).
predicate #and5(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], RES:bval[T]).
predicate #and6(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], in G6:bval[T], RES:bval[T]).

    % or[3-6]
    % Higher arity versions of #or
    % Deprecated -- use the || operator
predicate or3(in G1:bval[T], in G2:bval[T], in G3:bval[T], RES:bval[T]).
predicate or4(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    RES:bval[T]).
predicate or5(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], RES:bval[T]).
predicate or6(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], in G6:bval[T], RES:bval[T]).
    
predicate #or3(in G1:bval[T], in G2:bval[T], in G3:bval[T], RES:bval[T]).
predicate #or4(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    RES:bval[T]).
predicate #or5(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], RES:bval[T]).
predicate #or6(in G1:bval[T], in G2:bval[T], in G3:bval[T], in G4:bval[T], 
    in G5:bval[T], in G6:bval[T], RES:bval[T]).

    % #imp(A, B, G)
    % G = (A -> B) = (not A) or B
predicate #imp(in bval[T], in bval[T], out bval[T]) succeeds [once].

    % #iff(A, B, G)
    % G = (A <-> B) 
predicate #iff(in bval[T], in bval[T], out bval[T]) succeeds [once].

    % #ite(I, T, E, R)
    % Guard if-then-else. R = (I and T) or (not I and E)
predicate #ite(in bval[T], in bval[T], in bval[T], out bval[T])
    succeeds [once].

    % #bv_ite(I, T, E, R)
    % Bitvector if-then-else. If the first argument is true then the result
    % is the second argument, otherwise the result is the third argument.
predicate #bv_ite(in bval[bvecbit[T,U]], in bvec[T, U], in bvec[T, U],
    bvec[T, U]).

    % Maximum of two bitvectors
predicate bv_max(in bvec[T,U], in bvec[T,U], bvec[T,U]).

    % Minimum of two bitvectors
predicate bv_min(in bvec[T,U], in bvec[T,U], bvec[T,U]).

    % Is a bitvector signed?
predicate bv_signed(in bvec[T, U]).

    % Value of the sign bit of a bitvector (always false if the vector
    % is unsigned)
predicate bv_sign(in bvec[T, U], out bval[bvecbit[T,U]]).

    % Absolute value of a possibly signed bitvector
predicate bv_abs(in bvec[T, U], bvec[T, U]).

    % str_cat[3-5]
    % Higher arity versions of str_cat
predicate str_cat3(in S1:string, in S2:string, in S3:string, RES:string).
predicate str_cat4(in S1:string, in S2:string, in S3:string, in S4:string, 
    RES:string).
predicate str_cat5(in S1:string, in S2:string, in S3:string, in S4:string, 
    in S5:string, RES:string).

    % str_cat_list(StringList, Result).
    % Make a string by concatenating all elements of a string list.
predicate str_cat_list(in STRING_LIST:list[string], out RESULT:string)
    succeeds [once].

    % str_cat_list_sep(StringList, Sep, Result).
    % Make a string by concatenating all elements of a string list,
    % inserting separator Sep between each adjacent element
predicate str_cat_list_sep(in STRING_LIST:list[string], in SEP:string,
                           out RESULT:string) succeeds [once].

%-----------------------------------------------------------------------------%
% Implementation
%-----------------------------------------------------------------------------%

greaterthan(A, B) :-
    lessthan(B, A).

bool_not(true, false) :- .
bool_not(false, true) :- .

%-----------------------------------------------------------------------------%

#valid(G) :-
    #not(G, NG),
    ~#sat(NG).

#imp(A, B, G) :-
    #not(A, NA),
    #or(NA, B, G).

#iff(A, B, G) :-
    #imp(A, B, G1),
    #imp(B, A, G2),
    #and(G1, G2, G).

and3(G1, G2, G3, Res) :- 
    #and(G1, G2, T1),
    #and(T1, G3, Res).

and4(G1, G2, G3, G4, Res) :- 
    #and(G1, G2, T1),
    #and(T1, G3, T2), 
    #and(T2, G4, Res). 

and5(G1, G2, G3, G4, G5, Res) :- 
    #and(G1, G2, T1), 
    #and(T1, G3, T2), 
    #and(T2, G4, T3), 
    #and(T3, G5, Res).

and6(G1, G2, G3, G4, G5, G6, Res) :- 
    #and(G1, G2, T1), 
    #and(T1, G3, T2), 
    #and(T2, G4, T3), 
    #and(T3, G5, T4), 
	#and(T4, G6, Res).
    
#and3(G1, G2, G3, Res) :- 
    #and(G1, G2, T1),
    #and(T1, G3, Res).

#and4(G1, G2, G3, G4, Res) :- 
    #and(G1, G2, T1),
    #and(T1, G3, T2), 
    #and(T2, G4, Res). 

#and5(G1, G2, G3, G4, G5, Res) :- 
    #and(G1, G2, T1), 
    #and(T1, G3, T2), 
    #and(T2, G4, T3), 
    #and(T3, G5, Res).

#and6(G1, G2, G3, G4, G5, G6, Res) :- 
    #and(G1, G2, T1), 
    #and(T1, G3, T2), 
    #and(T2, G4, T3), 
    #and(T3, G5, T4), 
	#and(T4, G6, Res).
    
or3(G1, G2, G3, Res) :- 
    #or(G1, G2, T1),
    #or(T1, G3, Res).

or4(G1, G2, G3, G4, Res) :- 
    #or(G1, G2, T1),
    #or(T1, G3, T2), 
    #or(T2, G4, Res). 

or5(G1, G2, G3, G4, G5, Res) :- 
    #or(G1, G2, T1), 
    #or(T1, G3, T2), 
    #or(T2, G4, T3), 
    #or(T3, G5, Res).

or6(G1, G2, G3, G4, G5, G6, Res) :- 
    #or(G1, G2, T1), 
    #or(T1, G3, T2), 
    #or(T2, G4, T3), 
    #or(T3, G5, T4), 
	#or(T4, G6, Res).

#or3(G1, G2, G3, Res) :- 
    #or(G1, G2, T1),
    #or(T1, G3, Res).

#or4(G1, G2, G3, G4, Res) :- 
    #or(G1, G2, T1),
    #or(T1, G3, T2), 
    #or(T2, G4, Res). 

#or5(G1, G2, G3, G4, G5, Res) :- 
    #or(G1, G2, T1), 
    #or(T1, G3, T2), 
    #or(T2, G4, T3), 
    #or(T3, G5, Res).

#or6(G1, G2, G3, G4, G5, G6, Res) :- 
    #or(G1, G2, T1), 
    #or(T1, G3, T2), 
    #or(T2, G4, T3), 
    #or(T3, G5, T4), 
	#or(T4, G6, Res).

%-----------------------------------------------------------------------------%

#ite(I, T, E, R) :-
    #not(I, NI),
    #and(I, T, R0),
    #and(NI, E, R1),
    #or(R0, R1, R).

#bv_ite(I, T, E, R) :-
    #not(I, NI),
    #bv_guard(T, I, RT),
    #bv_guard(E, NI, RE),
    #bv_bor(RT, RE, R).

bv_max(A, B, M) :- 
    #bv_gt(A, B, G), 
    #bv_ite(G, A, B, M).

bv_min(A, B, M) :- 
    #bv_lt(A, B, G), 
    #bv_ite(G, A, B, M).

bv_signed(BV) :-
    #bv_split(BV, true, _, _).

bv_sign(BV, False) :-
    ~bv_signed(BV),
    #bool_g(false, False).

bv_sign(BV, G) :-
    bv_signed(BV),
    #bv_bit(BV, -1, G).

bv_abs(BV, BV) :-
    ~bv_signed(BV).


%-----------------------------------------------------------------------------%

str_cat3(S1, S2, S3, Res) :-
    str_cat(S1, S2, T1), 
    str_cat(T1, S3, Res).

str_cat4(S1, S2, S3, S4, Res) :-
    str_cat(S1, S2, T1), 
    str_cat(T1, S3, T2), 
    str_cat(T2, S4, Res).

str_cat5(S1, S2, S3, S4, S5, Res) :-
    str_cat(S1, S2, T1), 
    str_cat(T1, S3, T2), 
    str_cat(T2, S4, T3), 
    str_cat(T3, S5, Res).

%-----------------------------------------------------------------------------%

str_cat_list([], "") :- .
str_cat_list([X|Xs], Out) :-
    str_cat_list(Xs, Y),
    str_cat(X, Y, Out).

str_cat_list_sep([], _, "") :- .
str_cat_list_sep([X], _, X) :- .
str_cat_list_sep([X,X2|Xs], Sep, Out) :-
    str_cat_list_sep([X2|Xs], Sep, Y),
    str_cat3(X, Sep, Y, Out).

% -------------------------------------------------------------------------

predicate str_rep(in string, in string, in string, string).

str_rep(Source, Replace, With, Target)
	:-	\/str_sub(Source, P, L, Replace):list_all(pair{P, L}, Pairs),
		list_sort(Pairs, SortedPairs),
		SortedPairs = [pair{Pos, Len}| _],
		str_len(Source, SourceLen),
		str_sub(Source, 0, Pos, First),
		int_add(Pos, Len, End),
		int_sub(SourceLen, End, SecondLen),
		str_sub(Source, End, SecondLen, Second),
		str_cat_list([First, With, Second], Source2),
		str_rep(Source2, Replace, With, Target).
		
str_rep(Source, Replace, With, Source)
	:-	~str_sub(Source, _, _, Replace).

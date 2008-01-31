%%
% Authors:
%   Brian Hackett  <bhackett@stanford.edu>
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

% Path-sensitive intraprocedural dataflow.

% Evaluate branch conditions for their boolean formula representation,
% and use these to construct guards for each program point in the
% current function

% this file leaves the type g_bit of formula leaf values abstract.
% files importing this which need to import guards must define g_bit.
% note that g_bit may contain additional semantic information (not just an
% unconstrained bit), and that #sat should not be directly used with a g_guard.
% instead use guard_sat(G) below
type g_bit.
type g_guard = bval[g_bit].

% satisfying assignment constructed from a g_guard. may not be bval_asn[g_bit]
type g_guard_asn.

import "../base/loops.clp".

using solve_sat.
using intops.
using map.

% PREDICATES

% P is reachable if G holds
predicate guard(P:pp,G:g_guard).

% refine the condition G to EG, according to the guard under which transfer
% occurs from P0 to P1. where guard(P0,G0) and guard(P1,G1), if EG&G1 holds,
% then G&G0 holds and the edge P0->P1 will be taken during function execution
predicate eguard(in P0:pp,in P1:pp,in G:g_guard,EG:g_guard) succeeds [once].

% E is an expression that is produced as a result of a logical or comparison
% operator and hence has a boolean result.
predicate exp_boolean(E:c_exp).

% E evaluates to condition BG if G holds. beval is only defined here for
% logical operations. comparisons and casts to boolean from other expressions
% must be supplied by additional programs
predicate beval(in P:pp,in E:c_exp,BG:g_guard,G:g_guard).

% get an unconstrained bit to distinguish the edge transfer from P0 to P1.
% must be provided once the type of g_bit is actually known
predicate path_bit(in P0:pp,in P1:pp,BG:g_guard) succeeds [once].

% G is satisfiable. must be defined by programs importing this file
predicate guard_sat(in G:g_guard).

% G is satisfiable, with ASN a satisfying assignment. must be defined by
% programs importing this file
predicate guard_sat_asn(in G:g_guard,ASN:g_guard_asn).

% G holds under satisfying assignment ASN. must be defined by programs
% importing this file
predicate asn_guard(in ASN:g_guard_asn,in G:g_guard).

% construct the unique PATH from the enclosing summary entry point to P that
% that is satisfied under ASN, with TAIL any trailing points after P
type pp_path = list[pp].
predicate asn_path(in P:pp,in ASN:g_guard_asn,in TAIL:list[pp],PATH:list[pp])
    succeeds [zero,once].

% G is logically valid, true under all possible conditions
predicate guard_valid(in G:g_guard).

% G0 always implies G1. under any conditions where G0 holds, G1 also holds
predicate guard_implies(in G0:g_guard,in G1:g_guard).

% G0 and G1 are semantically equivalent guards, holding under exactly the
% same conditions
predicate guard_equivalent(in G0:g_guard,in G1:g_guard).

% G0 and G1 are semantically disjoint guards. G0 and G1 may never both hold
predicate guard_disjoint(in G0:g_guard,in G1:g_guard).

% simplifies G to a semantically equivalent NG. this is more extensive than
% the basic guard simplification provided by the solve_sat package, in that
% it uses guard_sat to look at the semantics of the guard rather than
% just the syntactic structure
predicate guard_simplify(in G:g_guard,NG:g_guard) succeeds [once].

%Replaces in G0 each g_bit with its corresponding replacement in Sub
%If a g_bit appears in G0 but does not appear in Sub, then the g_bit is
%replace with itself.
predicate guard_replace(in G0:g_guard, in Sub:map[g_bit, g_guard], G1:g_guard).

% CUSTOMIZATION

% add omit_beval(P,E) to prevent beval(P,E,_,_) from being computed in the
% standard way, allowing for customization of beval(P,E,_,_)
predicate omit_beval(in P:pp,in E:c_exp).

% RULES

% boolean expression evaluation
% only evaluate logical operators LNot, LAnd, and LOr here.
% boolean evaluation of other expressions is left to client analyses.

% expressions for which exp_boolean is not defined should be lifted to booleans
% through comparison with zero by client analyses

cil_exp_unop(E,u_lnot,_,_), +exp_boolean(E).
cil_exp_binop(E,b_land,_,_,_), +exp_boolean(E).
cil_exp_binop(E,b_lor,_,_,_), +exp_boolean(E).
compare_op(OP), cil_exp_binop(E,OP,_,_,_), +exp_boolean(E).

cil_exp_unop(E,u_lnot,RE,_), ?beval(P,E,_,_), ~omit_beval(P,E),
    beval(P,RE,NG,G),
    #not(NG,BG), +beval(P,E,BG,G).

cil_exp_binop(E,b_land,LE,RE,_), ?beval(P,E,_,_), ~omit_beval(P,E),
    beval(P,LE,LBG,LG), beval(P,RE,RBG,RG),
    #and(LBG,RBG,BG), #and(LG,RG,G), +beval(P,E,BG,G).

cil_exp_binop(E,b_lor,LE,RE,_), ?beval(P,E,_,_), ~omit_beval(P,E),
    beval(P,LE,LBG,LG), beval(P,RE,RBG,RG),
    #or(LBG,RBG,BG), #and(LG,RG,G), +beval(P,E,BG,G).

% transfer

% to avoid generating multiple guards for each program point, create
% a single merge guard on each point P and merge conditions as they arrive.
% adding gmerge(P,G) will merge G into the guard at P
predicate gmerge(P:pp,G:g_guard).
gmerge(P,_), \/gmerge(P,G):#or_all(G,MG), +guard(P,MG).

% edge transfer condition: P0 transfers control to P1 if EG holds
predicate econd(P0:pp,P1:pp,EG:g_guard) order [P0,P1].

% the initial guard at entry (or each loop entry if they are split off) is true
sum_bound(_,P,_), #bool_g(true,G), +gmerge(P,G).

% non-branch CFG edges which don't affect the guard
predicate reg_take(P0:pp,P1:pp) order [P0,P1].
iset(P0,P1,_),  +reg_take(P0,P1).
icall(P0,P1,_), +reg_take(P0,P1).
iloop(P0,P1,_), +reg_take(P0,P1).
iasm(P0,P1,_),  +reg_take(P0,P1).

% compute edge conditions and guards for non-branch CFG edges. sometimes these
% indicate non-deterministic branches, and we need to introduce fresh bits to
% keep the guards along the separate paths distinct
predicate split_take(P0:pp,TGTS:list[pp],PG:g_guard).
split_take(P0,[P1],PG), reg_take(P0,P1), +econd(P0,P1,PG),
    guard(P0,GG), #and(PG,GG,PGG), +gmerge(P1,PGG).
split_take(P0,[P1|TAIL],PG), TAIL\=[], reg_take(P0,P1), path_bit(P0,P1,BG),
    #and(BG,PG,CPG), #not(BG,NBG), #and(NBG,PG,NPG),
    +split_take(P0,TAIL,NPG), +econd(P0,P1,CPG),
    guard(P0,GG), #and(CPG,GG,PGG), +gmerge(P1,PGG).
reg_take(P0,_), \/reg_take(P0,P1):list_all(P1,TGTS),
    #bool_g(true,G), +split_take(P0,TGTS,G).

% G is a condition under which P0 branches to P1. multiple conditions may
% occur for the same branch statement
predicate branch_take(P0:pp,P1:pp,G:g_guard).
branch(P,P0,P1,E), beval(P,E,TG,G), #not(TG,FG),
    #and(TG,G,TGG), +branch_take(P,P0,TGG),
    #and(FG,G,FGG), +branch_take(P,P1,FGG).

% at branches, get the disjunction over the separate branch conditions to
% compute the true/false edge conditions and point guards
branch(P,P0,P1,_),
    \/branch_take(P,P0,TG):#or_all(TG,TMG), +econd(P,P0,TMG),
    \/branch_take(P,P1,FG):#or_all(FG,FMG), +econd(P,P1,FMG),
    guard(P,GG),
    #and(TMG,GG,TGG), +gmerge(P0,TGG),
    #and(FMG,GG,FGG), +gmerge(P1,FGG).

% edge guards

% points with more than 1 incoming edge
predicate join(pp).
cfge_final(P0,P,_), cfge_final(P1,P,_), P0\=P1, +join(P).

% if P1 is a non-join then the guard at P1 implies the guard at P0 and
% the state is left unchanged along the edge
econd(P0,P1,_), ~join(P1), ?eguard(P0,P1,G,_), +eguard(P0,P1,G,G).

% if P1 is a join point then generate the edge guards from the edge conds ECG.
% the distinguishing guard EG is (G1=>G0&ECG)
econd(P0,P1,ECG), join(P1), guard(P0,G0), guard(P1,G1),
    #not(G1,NG1), #and(G0,ECG,GAND), #or(NG1,GAND,GIMP),
    ?eguard(P0,P1,G,_), #and(G,GIMP,EG), +eguard(P0,P1,G,EG).

% path construction

% construct paths through the function corresponding to satisfying assignments
?asn_path(P,ASN,TAIL,_), econd(PP,P,ECG), asn_guard(ASN,ECG),
    asn_path(PP,ASN,[P|TAIL],PATH),
    +asn_path(P,ASN,TAIL,PATH).
sum_bound(_,P,_), +asn_path(P,_,TAIL,[P|TAIL]).

% guard utility

% if ~G0|G1 is valid, then G0 always implies G1
?guard_implies(G0,G1), #not(G0,NG0), #or(NG0,G1,IMP),
    guard_valid(IMP), +guard_implies(G0,G1).

% if G0=>G1 and G1=>G0 always hold, then G0 and G1 are equivalent
?guard_equivalent(G0,G1), guard_implies(G0,G1), guard_implies(G1,G0),
    +guard_equivalent(G0,G1).

% if G0&G1 is unsatisfiable, then G0 and G1 are disjoint
?guard_disjoint(G0,G1), #and(G0,G1,BOTH),
    ~guard_sat(BOTH), +guard_disjoint(G0,G1).
    
?guard_replace(GF, SUB, _),
	#and(G1, G2, GF),
	guard_replace(G1, SUB, G1N),
	guard_replace(G2, SUB, G2N),
	#and(G1N, G2N, GN),
	+guard_replace(GF, SUB, GN).
	
?guard_replace(GF, SUB, _),	
	#or(G1, G2, GF),
	guard_replace(G1, SUB, G1N),
	guard_replace(G2, SUB, G2N),
	#or(G1N, G2N, GN),
	+guard_replace(GF, SUB, GN).
	
?guard_replace(GF, SUB, _),	
	#not(G1, GF),
	guard_replace(G1, SUB, G1N),
	#not(G1N, GN),
	+guard_replace(GF, SUB, GN).

?guard_replace(GF, SUB, _),	
	#bool_g(_, GF),
	+guard_replace(GF, SUB, GF).
			
?guard_replace(GF, SUB, _),	
	#id_g(GFID, GF),
	map_search(SUB, GFID, GFSUB),
	+guard_replace(GF, SUB, GFSUB).

?guard_replace(GF, SUB, _),	
	#id_g(GFID, GF),
	~map_search(SUB, GFID, _),
	+guard_replace(GF, SUB, GF).

% guard simplification

predicate guard_one_simplify(in G:g_guard,NG:g_guard).

guard_simplify(G,G) :- ~guard_one_simplify(G,_).
guard_simplify(G,NG) :-
    \/guard_one_simplify(G,XG):list_all(XG,[MG|_]), guard_simplify(MG,NG).

guard_one_simplify(G,NG) :-
    map_empty(EM), #g_id(G,BIT), (#bool_g(true,BG); #bool_g(false,BG)),
    map_insert(BIT,BG,EM,M), guard_replace(G,M,NG),
    guard_equivalent(G,NG).

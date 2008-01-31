%%
% Authors:
%   Brian Hackett  <bhackett@stanford.edu>
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

% Modelling integer operations using bit vectors

import "memory.clp".

% ANALYSIS REPRESENTATIONS

using solve_bitvector.

% representation for bit vectors
type g_vecrep ::=
    vr_t{t_trace}    % initial value of some trace
  | vr_i{pp,c_exp}.  % imprecise intermediate result

% representation for regular unconstrained bits, which can be the bits used
% by upstream analyses, or the extra type g_axrep for extension by downstream
% analyses
type g_xrep.
type g_arep ::=
    ar_extra{g_xrep}
  | ar_path{pp,pp}
  | ar_entry{pp,t_trace,t_trace}
  | ar_exit{sum,pp,t_trace,t_trace}.

type g_vec = bvec[g_vecrep,g_arep].
type g_bit = bvecbit[g_vecrep,g_arep].

% intermediate integer/floating-point values are just bvecs
type t_nrep = g_vec.

% PREDICATES

% fix the length of all bit vectors at N. if not supplied, the default lengths
% given by the type will be used
predicate fixed_vectors(N:int).

% at program point P, expression E evaluates to bitvector BV
predicate evalbv(in P:pp,in E:c_exp,BV:g_vec).

% at program point P, trace T has bitvector value BV
predicate valbv(in P:pp,in T:t_trace,BV:g_vec).

% as interpreted by the call/loop I at point P, guard RG maps to NG
predicate inst_guard(in I:sum,in P:pp,in RG:g_guard,NG:g_guard).

% As interpreted by the call/loop I at point P, bitvector RV maps to NV
predicate inst_bvec(in I:sum,in P:pp,in RV:g_vec,NV:g_vec).

% get a specific bit from a trace_val
predicate trace_bit(in t_trace_val,in int,g_guard).

% RULES

% implement satisfiability predicates for upstream analyses
type g_guard_asn = bval_asn[g_bit].
guard_sat(G) :- #sat(G).
guard_sat_asn(G,ASN) :- #satasn(G,ASN).
guard_valid(G) :- #not(G, NG), ~#sat(NG).
asn_guard(ASN,G) :- #asng(ASN,G).
asn_value(ASN,V,N) :- trace_nrep(V,BV), #asnbv(ASN,BV,N).

% implement unconstrained bits for upstream analyses
path_bit(P0,P1,G) :- #id_g(b_abit{ar_path{P0,P1}},G).
entry_bit(P,S,T,G) :- #id_g(b_abit{ar_entry{P,S,T}},G).
exit_bit(SUM,P,S,T,G) :- #id_g(b_abit{ar_exit{SUM,P,S,T}},G).

% integer kind K is modelled with sign S and bit length LEN. this is equal to
% ikind_bytes*8, unless fixed_vectors is supplied for some width
predicate ikind_bvec(K:ikind,S:bool,LEN:int).
fixed_vectors(LEN), ikind_bytes(K,S,_), +ikind_bvec(K,S,LEN).
~fixed_vectors(_), ikind_bits(K,S,Len), +ikind_bvec(K,S,Len).

% model pointers as bitvectors with sign S and length LEN. 
predicate ptr_bvec(S:bool,LEN:int).
fixed_vectors(LEN), +ptr_bvec(false,LEN).
~fixed_vectors(_), pointer_bits(Len), +ptr_bvec(false, Len).

% float kind K is modelled with sign S and bit length LEN
predicate fkind_bvec(K:fkind,S:bool,LEN:int).
fixed_vectors(LEN), fkind_bytes(K,_), +fkind_bvec(K,true,LEN).
~fixed_vectors(_), fkind_bits(K,LEN), +fkind_bvec(K,true,LEN).

% generate unconstrained vectors for E evaluated at P. all boolean operations
% are modelled precisely so we don't need to define unconstrained_cond
unconstrained_nrep(P,E,V) :-
    exp_tint(E,K), ikind_bvec(K,S,LEN), #id_bv(vr_i{P,E},S,false,LEN,V).
unconstrained_nrep(P,E,V) :-
    exp_tptr(E), ptr_bvec(S,LEN), #id_bv(vr_i{P,E},S,false,LEN,V).
unconstrained_nrep(P,E,V) :-
    exp_tflt(E,K), fkind_bvec(K,S,LEN), #id_bv(vr_i{P,E},S,false,LEN,V).

% convert trace values to vecs/bits

% get trace sign/length for int/float traces. assume pointer for other traces
predicate ifkind_bvec(in T:t_trace,S:bool,LEN:int).
ifkind_bvec(drf{T},S,LEN) :-
    trace_type(s_func,T,y_int{K}), ikind_bvec(K,S,LEN).
ifkind_bvec(drf{T},S,LEN) :-
    trace_type(s_func,T,y_flt{K}), fkind_bvec(K,S,LEN).

trace_nrep(trace{T},V) :-
    ifkind_bvec(T,S,LEN), #id_bv(vr_t{T},S,false,LEN,V).
trace_nrep(trace{T},V) :-
    ~ifkind_bvec(T,_,_), ptr_bvec(S,LEN), #id_bv(vr_t{T},S,false,LEN,V).
+trace_nrep(nrep{V},V).

trace_bit(trace{T},N,G) :- #id_g(b_vbit{vr_t{T},N},G).
trace_bit(nrep{V},N,G) :- #bv_bit(V,N,G).

% flatten multiple vectors together for faster operation in the memory analysis
nrep_flatten(VLIST,MV) :- \/list_mem(VLIST,pair{V,G}):#bv_all(V,G,MV).

nrep_bits(V,S,LEN) :- #bv_split(V,S,_,BITS), list_length(BITS,LEN).

% bitvector nrep operations

% constant integers
nrep_const_int(K,N,NV) :- ikind_bvec(K,S,LEN), #int_bv(N,S,LEN,NV).

% casts
nrep_cast(S,LEN,V,NV) :- ~fixed_vectors(_), #bv_cast(V,S,LEN,NV).
nrep_cast(S,_,V,NV) :- fixed_vectors(LEN), #bv_cast(V,S,LEN,NV).

% unary operations
nrep_unop(u_neg,RV,NV) :- #bv_neg(RV,NV).
nrep_unop(u_bnot,RV,NV) :- #bv_bnot(RV,NV).

% binary operations we can always do precisely
nrep_binop(b_plusa,LV,RV,NV) :- #bv_add(LV,RV,NV).
nrep_binop(b_minusa,LV,RV,NV) :-#bv_sub(LV,RV,NV).
nrep_binop(b_band,LV,RV,NV) :-  #bv_band(LV,RV,NV).
nrep_binop(b_bxor,LV,RV,NV) :-  #bv_bxor(LV,RV,NV).
nrep_binop(b_bor,LV,RV,NV) :-   #bv_bor(LV,RV,NV).

% binary operations we can do precisely when the LHS or RHS is constant
nrep_binop(b_mult,LV,RV,NV) :- #bv_int(LV,LN), #bv_mul(RV,LN,NV).
nrep_binop(b_mult,LV,RV,NV) :- ~#bv_int(LV,_), #bv_int(RV,RN), #bv_mul(LV,RN,NV).
nrep_binop(b_shiftlt,LV,RV,NV) :- #bv_int(RV,RN), #bv_shl(LV,RN,NV).
nrep_binop(b_shiftrt,LV,RV,NV) :- #bv_int(RV,RN), #bv_shr(LV,RN,NV).

% unary comparisons
nrep_nez(V,G) :- #bv_nez(V,G).

% binary comparisons
nrep_cmp(b_eq,LV,RV,G) :- #bv_eq(LV,RV,G).
nrep_cmp(b_ne,LV,RV,G) :- #bv_ne(LV,RV,G).
nrep_cmp(b_lt,LV,RV,G) :- #bv_lt(LV,RV,G).
nrep_cmp(b_gt,LV,RV,G) :- #bv_gt(LV,RV,G).
nrep_cmp(b_le,LV,RV,G) :- #bv_le(LV,RV,G).
nrep_cmp(b_ge,LV,RV,G) :- #bv_ge(LV,RV,G).

% condition re-evaluation

inst_guard(SUM,P,G,G) :- #bool_g(_,G).

% as interpreted by the call/loop SUM at point P, bit N of callee vector CV
% holds if caller guard G holds
predicate inst_gmerge(in SUM:sum,in P:pp,in CV:g_vecrep,in N:int,G:g_guard).

% revaluate bits for the initial value of callee traces. use inst_trace to get
% the corresponding value in the caller, then extract the Nth bit
inst_gmerge(SUM,P,vr_t{CT},N,G) :-
    inst_trace(SUM,P,CT,T,WG), trace_bit(T,N,NG), #and(NG,WG,G).

% just give a warning for re-evaluating the results of imprecise operations
?inst_gmerge(SUM,P,vr_i{PP,EXP},_,_),
    +warning("Can't get inst_guard for imprecise bit",SUM,P,PP,EXP).

% reval complex conditions by switching on what they could be: #and, #or, #not,
% or a #id_g {T,N}
inst_guard(SUM,P,RG,NG) :- #and_lv(RG0,RG1,LEVEL,RG),
    inst_guard(SUM,P,RG0,NG0), inst_guard(SUM,P,RG1,NG1),
    #and_lv(NG0,NG1,LEVEL,NG).
inst_guard(SUM,P,RG,NG) :- #or_lv(RG0,RG1,LEVEL,RG),
    inst_guard(SUM,P,RG0,NG0), inst_guard(SUM,P,RG1,NG1),
    #or_lv(NG0,NG1,LEVEL,NG).
inst_guard(SUM,P,RG,NG) :- #not_lv(RG0,LEVEL,RG),
    inst_guard(SUM,P,RG0,NG0),
    #not_lv(NG0,LEVEL,NG).
inst_guard(SUM,P,RG,NG) :- #id_g(b_vbit{T,N},RG),
    \/inst_gmerge(SUM,P,T,N,G):#or_all(G,NG).

?inst_guard(SUM,P,RG,_), #id_g(b_abit{BIT},RG),
    +warning("Can't get inst_guard for unknown extra bit",SUM,P,BIT).

% -----------------------------------------------------------------------------

evalbv(P,E,BV) :- \/(eval(P,E,XV,XG), trace_nrep(XV,XBV)):#bv_all(XBV,XG,BV).
valbv(P,T,BV) :- \/(val(P,T,XV,XG), trace_nrep(XV,XBV)):#bv_all(XBV,XG,BV).

% -----------------------------------------------------------------------------

% map a list of guards using inst_guard
predicate inst_bits(in sum,in pp,in list[g_guard],list[g_guard]).
+inst_bits(_,_,[],[]).
inst_bits(SUM,P,[B0|BS0],[B|BS]) :-
    inst_guard(SUM,P,B0,B), inst_bits(SUM,P,BS0,BS).

% map a bit vector out of a loop/call by splitting it up into its component
% bits which are mapped using inst_guard and then recombining it.
inst_bvec(SUM,P,RV,NV) :- #bv_split(RV,SIGN,OFLOW0,BITS0),
    inst_guard(SUM,P,OFLOW0,OFLOW), inst_bits(SUM,P,BITS0,BITS),
    #bv_split(NV,SIGN,OFLOW,BITS).

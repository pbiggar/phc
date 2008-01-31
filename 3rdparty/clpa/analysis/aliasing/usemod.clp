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

% compute per-root and/or per-trace information about reads, writes, and casts.
% imported by aliasing.clp

% PREDICATES

% reasons for omitting a piece of per-isum information
type omit_reason ::=
    omit_dropped   % handled by some baked in behavior
  | omit_poly_inv  % handled by polymorphic composite type properties
  | omit_comp_inv  % handled as a composite type invariant
  | omit_glob_inv. % handled as a global invariant

predicate omit_comp_soft(in C:string,in STR:t_trace,in T:t_trace).
predicate omit_usemod(in T:t_trace,in Y:access_type).

% get the maximum number of derefs allowed in summary usemod information
% for traces reachable from R. default behavior if not defined is 0 derefs
% for globals, 1 deref for arguments and locals (within loops)
predicate max_usemod_derefs(in SUM:sum,in R:t_root,N:int).

% get the cutoff for number of traces with global roots that
% can end up in the usemod set for a function before using anyuse.
% if not defined, the default is 50
predicate max_usemod_globals(N:int).

import "usemodui.clp".

% RULES

% don't pull in softness info for the current SUM, we compute it in this file
+omit_trace_soft_summary().

% generate read/write information

% usemod to add to the currently analyzed sum
predicate add_usemod(T:t_trace,Y:access_type).

% direct usemod info we've seen in this function, other than that pushed up
% through functions
predicate direct_usemod(P:pp,T:t_trace,Y:access_type).
direct_usemod(_,T,Y), +add_usemod(T,Y).

% get all traces directly accessed and their potential aliases.
% for reads we evaluate the lval expression to make sure the value targeted
% was actually live at sum entry, i.e. avoid "x = 0; ... y = x;"
cil_cursum(SUM), cil_exp_lval(E,_), exp_point(E,P),
    eval(P,E,trace{drf{T}},_), +direct_usemod(P,T,read),
    trace_alias(SUM,T,NT,_,_), +add_usemod(NT,read).
cil_cursum(SUM), access(P,T,write), +direct_usemod(P,T,write),
    trace_alias(SUM,T,NT,_,_), +add_usemod(NT,write).

% propagate up from callees. use rel_inst_trace to account for any
% deepread/deepwrite occurring within the callee through aliases we generated
rel_inst_trace(I,P,CT,T,_), sum_body(SUM,P), trace_type(SUM,T,_),
    inst_may_access(I,CT,Y), +direct_usemod(P,T,Y).

% push inst_usemod up through nestings
isum(P,_,I), inst_usemod(I,CT,Y),
    trace_sub(CT,CST,RT), rel_inst_trace(I,P,CST,ST,_),
    cil_cursum(SUM), trace_compose(SUM,ST,RT,T), +add_usemod(T,Y).
isum(_,_,I), inst_usemod(I,T,Y),
    (I=s_loop{_}; ~trace_root(T,arg{_})),
    +add_usemod(T,Y).

% usemod summaries

% extend max_usemod_derefs with default limits in cases where not defined
predicate any_max_usemod_derefs(in SUM:sum,in R:t_root,N:int).
?any_max_usemod_derefs(SUM,R,_), max_usemod_derefs(SUM,R,N),
    +any_max_usemod_derefs(SUM,R,N).
?any_max_usemod_derefs(SUM,R,_), ~max_usemod_derefs(SUM,R,_),
    (R=glob{_}, N=0; R\=glob{_}, N=1),
    +any_max_usemod_derefs(SUM,R,N).

% single step usemod simplification
predicate usemod_one_simplify(in T:t_trace,in Y:access_type,
                              NT:t_trace,NY:access_type).

% transitively simplify any usemod information for traces T,
% trying to compress similar entries together
predicate usemod_simplify(in T:t_trace,in Y:access_type,
                          NT:t_trace,NY:access_type) succeeds [once].
usemod_simplify(OT,OY,NT,NY) :-
    usemod_one_simplify(OT,OY,T,Y),
    ~(usemod_one_simplify(OT,OY,XT,_), XT\=T, trace_sub(T,XT,_)),
    usemod_simplify(T,Y,NT,NY).
usemod_simplify(T,Y,T,Y) :- ~usemod_one_simplify(T,Y,_,_).

% simplify traces which contain too many derefs according to
% any_max_usemod_derefs
usemod_one_simplify(T,Y,NT,NY) :- trace_root(T,R), trace_derefs(T,N),
    cil_cursum(SUM), any_max_usemod_derefs(SUM,R,MAX),
    int_gt(N,MAX), trace_sub(T,drf{NT},_), trace_derefs(NT,MAX),
    (Y=read, NY=deepread;
     Y=write, NY=deepwrite;
     Y\=read, Y\=write, NY=Y).

% simplify traces which contain accesses through void* casts
% or untyped extra fields - these generally indicate polymorphism
% which we don't want to capture in usemod info
usemod_one_simplify(T,Y,NT,NY) :-
    cil_cursum(SUM), trace_sub(T,fld{NT,_,C},_),
    ~trace_type(SUM,NT,y_comp{C}),
    ~trace_type(SUM,NT,y_array{y_comp{C},_}),
    (Y=read, NY=deepread;
     Y=write, NY=deepwrite;
     Y\=read, Y\=write, NY=Y).

% throw out all temp/retval/cstr information
?omit_usemod(T,Y), trace_root(T,temp{_,_}), +omit_usemod(T,Y).
?omit_usemod(T,Y), trace_root(T,return), +omit_usemod(T,Y).
?omit_usemod(T,Y), trace_root(T,cstr{_}), +omit_usemod(T,Y).

% throw out locally allocated traces
cil_cursum(SUM), ?omit_usemod(T,Y), 
    ~trace_alloc(SUM,T,ak_external), +omit_usemod(T,Y).

% throw out reads (hopefully not writes too!) on functions and other
% immutable global data
cil_cursum(SUM), ?omit_usemod(T,Y), trace_type(SUM,T,y_func), +omit_usemod(T,Y).
cil_cursum(SUM), ?omit_usemod(T,Y), ~trace_type(SUM,T,y_func),
    trace_fld_sub(T,root{glob{G}},_),
    ~sum_usemod_glob(G)->sgwrite(), +omit_usemod(T,Y).

% throw out redundant deep accesses
add_usemod(T,Y),
    (Y=read, DY=deepread; Y=write, DY=deepwrite; Y\=read, Y\=write, DY=Y),
    trace_sub(T,ST,_), T\=ST, +omit_usemod(ST,DY).

% throw out redundant reads on the same trace
add_usemod(T,Y), (Y=deepread; Y=deepwrite), +omit_usemod(T,read).

% throw out redundant reads given deeper accesses
add_usemod(T,_), trace_sub(T,ST,_), T\=ST, +omit_usemod(ST,read).

% get the final usemod set, filtering according to omit/simplify usemod.
predicate filt_usemod(T:t_trace,Y:access_type).
add_usemod(T,Y), ~omit_usemod(T,Y), usemod_simplify(T,Y,NT,NY),
    +filt_usemod(NT,NY).

% use anyuse for this summary, putting all global usemod information on the
% global itself and marking this function as using any such global
predicate use_anyuse().
inst_anyuse(_), +use_anyuse().
(max_usemod_globals(N); ~max_usemod_globals(_), N=50),
    \/(filt_usemod(T,_), trace_root(T,glob{_})):count_all(T,COUNT),
    int_gt(COUNT,N), +use_anyuse().

% if we are using anyuse, update this function's summary as well as any of
% the globals that were accessed by this function
cil_curfn(FN), cil_cursum(SUM), use_anyuse(), +sum_usemod(FN,SUM)->sanyuse(),
    filt_usemod(T,BY), trace_root(T,glob{G}),
    (BY=deepread, Y=read; BY=read, Y=read;
     BY=deepwrite, Y=write; BY=write, Y=write),
    +sum_usemod_glob(G)->sganyuse(Y).

% update sum_usemod, filtering out globals if we are using anyuse
cil_curfn(FN), cil_cursum(SUM), filt_usemod(T,Y),
    (~use_anyuse(); ~trace_root(T,glob{_})),
    +sum_usemod(FN,SUM)->stuse(T,Y).

% writable composite/global summaries

predicate direct_write(P:pp,T:t_trace).
direct_usemod(P,T,write), +direct_write(P,T).
direct_usemod(P,T,deepwrite), +direct_write(P,T).

predicate add_comp_write(C:string,F:string,P:pp).
add_comp_write(C,F,_), +sum_usemod_comp(C)->scwrite(F).

direct_write(P,T), trace_sub(T,drf{fld{_,F,C}},_), +add_comp_write(C,F,P).

predicate add_glob_write(G:string,P:pp,ENTRY:maybe[t_pair[t_trace,t_trace]]).
add_glob_write(G,_,_), ~trace_type(s_func,root{glob{G}},y_func),
    +sum_usemod_glob(G)->sgwrite().

direct_write(P,T), trace_fld_sub(T,root{glob{G}},_),
    +add_glob_write(G,P,no).
direct_write(P,drf{T}),
    trace_sub(T,fld{STR,_,C},_), comp_to_relative(STR,T,RT),
    sum_comp(C)->sxpoints(RT,GT),
    trace_fld_sub(GT,root{glob{G}},_), +add_glob_write(G,P,yes{pair{T,GT}}).
direct_write(P,drf{T}),
    trace_root(T,glob{TG}), sum_glob(TG)->sxpoints(T,GT),
    trace_fld_sub(GT,root{glob{G}},_), +add_glob_write(G,P,yes{pair{T,GT}}).

% allocation summaries

% SUM allocates a fresh value stored in trace T
predicate inst_alloc(SUM:sum,T:t_trace).
asn_points(SUM,fn_exit,S,T,_), trace_alloc(SUM,T,ak_heap_local),
    trace_rename(SUM,fn_exit,S,NS,_),
    +inst_alloc(SUM,NS).
isum_target(I,FN,SUM,_), sum_usemod(FN,SUM)->stalloc(T), +inst_alloc(I,T).

% bubble up allocations performed
inst_alloc(I,CT), isum(P,_,I), sum_body(SUM,P),
    trace_sub(CT,CST,RT), rel_inst_trace(I,P,CST,ST,_),
    trace_compose(SUM,ST,RT,T),
    trace_alloc(SUM,T,ak_external), +inst_alloc(SUM,T).
inst_alloc(I,T), ~trace_root(T,arg{_}), isum(P,_,I), sum_body(SUM,P),
    trace_alloc(SUM,T,ak_external), +inst_alloc(SUM,T).

% update summaries with allocations performed. for globals, add X->drf{X}
% spoints edges to indicate the new global location
cil_cursum(SUM), inst_alloc(SUM,T), glob_trace_rename(T,NT),
    trace_root(NT,glob{G}), trace_simplify(s_func,drf{NT},DNT),
    +sum_glob(G)->sxpoints(NT,DNT).
%cil_cursum(SUM), inst_alloc(SUM,T), ~trace_root(T,glob{_}),
%    cil_curfn(FN), +sum_usemod(FN,SUM)->stalloc(T).

% soft trace usage summaries

% soft traces used by this SUM
predicate add_soft(t_trace,soft_type).

% traces marked as soft at particular program points
predicate point_soft(pp,t_trace,soft_type).
point_soft(_,T,Y), +add_soft(T,Y).

% use point_soft to mark soft traces later in the function. can't apply newly
% soft traces summary wide or memory analysis won't stratify
predicate point_soft_prev(in pp,in t_trace).
?point_soft_prev(P,T), trace_sub(T,OT,_), point_soft(PP,OT,_),
    pp_reach(PP,P), +point_soft_prev(P,T).
iset(P0,P1,_), ?vmerge(P1,S,_,_), point_soft_prev(P0,S),
    val(P0,S,T,G), eguard(P0,P1,G,EG), +vmerge(P1,S,T,EG).

% get all pointers whose targets are directly used as arrays. these are buffers
% of values (which might themselves be arrays) being scanned through
pointer_op(OP), cil_exp_binop(E,OP,LE,_,_), exp_point(E,P), ~omit_eval(P,E),
    eval(P,LE,trace{drf{T}},_), +point_soft(P,drf{T},ptarray).

% get all traces which have been used recursively
predicate has_recursion(in SUM:sum,in OFF:c_offset,in T:t_trace,NT:t_trace).
cil_off_none(OFF), ?has_recursion(SUM,OFF,T,_), trace_simplify(SUM,drf{T},NT),
    drf{T}\=NT, +has_recursion(SUM,OFF,T,NT).
cil_off_field(OFF,FX,_), cil_field_name(FX,F,_,_,_),
    ?has_recursion(SUM,OFF,T,_), trace_type(SUM,T,y_comp{C}),
    trace_simplify(SUM,fld{T,F,C},FT), FT\=fld{T,F,C},
    +has_recursion(SUM,OFF,T,FT).
cil_off_field(OFF,FX,NOFF), cil_field_name(FX,F,_,_,_),
    ?has_recursion(SUM,OFF,T,_), trace_type(SUM,T,y_comp{C}),
    has_recursion(SUM,NOFF,fld{T,F,C},NT), +has_recursion(SUM,OFF,T,NT).
cil_off_index(OFF,_,NOFF), ?has_recursion(SUM,OFF,T,_),
    has_recursion(SUM,NOFF,T,NT), +has_recursion(SUM,OFF,T,NT).
cil_lval_mem(LV,ME,OFF), lval_point(LV,P), eval(P,ME,trace{RT},_),
    sum_body(SUM,P), has_recursion(SUM,OFF,RT,T), +point_soft(P,T,recurse).

% omit T from explicit summarization as a soft trace
predicate omit_soft(in T:t_trace,in soft_type,WHY:omit_reason).

% ptarray only applies to pointer targets
?omit_soft(T,ptarray,_), T\=drf{_}, +omit_soft(T,ptarray,omit_dropped).

% bubble up from inner summaries
isum(P,_,I), isum_target(I,FN,SUM,_), ~omit_exit_alias_summary(I),
    sum_usemod(FN,SUM)->stsoft(CT,Y),
    inst_trace(I,P,CT,trace{T},_), ~trace_root(T,temp{_,_}),
    +point_soft(P,T,Y).

% look for potential composite invariants on soft usage
predicate comp_soft(C:string,STR:t_trace,T:t_trace,soft_type).
add_soft(T,Y), ~omit_soft(T,Y,omit_dropped),
    trace_sub(T,fld{STR,_,C},_), ~omit_comp_soft(C,STR,T),
    +omit_soft(T,Y,omit_comp_inv), +comp_soft(C,STR,T,Y).

% throw out weaker composite invariants
predicate weak_comp_soft(C:string,STR:t_trace,T:t_trace).
comp_soft(_,STR,T,_), trace_sub(STR,SSTR,_), STR\=SSTR,
    comp_soft(SC,SSTR,T,_), +weak_comp_soft(SC,SSTR,T).
comp_soft(C,STR,T,Y), ~weak_comp_soft(C,STR,T),
    trace_sub(T,STR,RT), +sum_usemod_comp(C)->stsoft(RT,Y).

% of the remaining look for global invariants
add_soft(T,Y),
    ~omit_soft(T,Y,omit_dropped),
    ~omit_soft(T,Y,omit_comp_inv),
    trace_root(T,glob{G}), +omit_soft(T,Y,omit_glob_inv),
    +sum_usemod_glob(G)->stsoft(T,Y).

% and finally add per-summary soft info, updating inst_soft to bubble up
cil_curfn(FN), cil_cursum(SUM), add_soft(T,Y),
    ~omit_soft(T,Y,_), +sum_usemod(FN,SUM)->stsoft(T,Y).

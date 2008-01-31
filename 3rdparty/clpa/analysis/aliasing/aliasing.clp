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

% Path-sensitive interprocedural alias analysis

% the strategy of the alias analysis is to generally assume non-aliasing
% on input data and side effects of functions, and identify only those places
% where this assumption is violated. the results of the analysis are a set
% of points-to graphs for possibly aliased values on globals, composite types,
% and function entry and exit points.

import "../memory/intignore.clp".

analyze session_name("cil_sum_body").
analyze analysis_name("aliasing").
analyze bottomup().

using map.

% PREDICATES

% ignore spoints on the given traces. these are either covered by annotated
% invariants, or deal with low level system bits we aren't modelling
predicate drop_spoints(in SUM:sum,in POS:point_pos,in S:t_trace,in T:t_trace).

% spoints(S,T) should not be considered for a composite type invariant on C/STR
predicate omit_comp_spoints(in C:string,in SUM:sum,in STR:t_trace,
                            in S:t_trace,in T:t_trace).

% spoints(S,T) should not be considered for a global invariant on G
predicate omit_glob_spoints(in G:string,in S:t_trace,in T:t_trace).

% don't use entry_points() to identify aliased traces on callees
predicate no_entry_trace_alias().

% don't generate ANY composite or global invariants
predicate no_comp_glob_points().

% supporting information for each generated spoints edge
type t_points_asn ::=
    asn_exit{P:pp,ASN:g_guard_asn}
  | asn_entry{P:pp,T:t_trace,CT0:t_trace,CT1:t_trace,ASN:g_guard_asn}
  | asn_none{SUM:sum}.

% at entry/exit to SUM, S may point to T according to A
predicate asn_points(SUM:sum,POS:point_pos,S:t_trace,T:t_trace,A:t_points_asn).
predicate try_asn_points(SUM:sum,POS:point_pos,S:t_trace,T:t_trace,A:t_points_asn).

% info about aliases used to extend rel_inst_trace. CT maps to T at I due to Y
type ext_why ::=
    rel_direct
  | rel_alias{XT:t_trace,PT:t_trace,DPT:t_trace}.
predicate ext_rel_inst_trace(I:sum,P:pp,CT:t_trace,T:t_trace,G:g_guard,
                             Y:ext_why).

% RULES

% we only use the entry aliasing to get additional entry aliasing on callees
+no_entry_aliasing().

% only generate inst_trace for arguments included in prototypes (we want to
% be able to type everything). extra args to varargs will be smashed anyways
+matching_arg_inst_trace().

% ignore coercions that occur when casting between integers to preserve
% any pointer targets
+ignore_int_casts().

% also compute usemod and UI information
import "usemod.clp".
import "aliasingui.clp".

% get polymorphic type information
predicate comp_poly(in C:string,FT:t_trace,T:t_trace,AT:t_trace).
comp_poly(C,FT,T,AT) :- poly_comp(C)->spoly(FT,T,AT).

% generate exit aliasing

predicate scalar_trace(in SUM:sum,in S:t_trace).
?scalar_trace(SUM,S), trace_type(SUM,S,y_int{_}), +scalar_trace(SUM,S).
?scalar_trace(SUM,S), trace_type(SUM,S,y_flt{_}), +scalar_trace(SUM,S).
?scalar_trace(SUM,S), trace_type(SUM,S,y_enum{_}), +scalar_trace(SUM,S).

% mark any updated traces as as live at func/loop exit,
% then get their targets to construct the exit points-to graph, updating
% inst_exit_points for use by memory.clp
access(P,S,write), sum_body(SUM,P),
    ~scalar_trace(SUM,S), sum_bound(SUM,_,PE),
    val(PE,S,trace{T},VG), ~trace_alloc(SUM,T,ak_stack_local),
    guard(PE,GG), #and(GG,VG,G), #satasn(G,ASN),
    +try_asn_points(SUM,fn_exit,S,T,asn_exit{PE,ASN}).

% existing aliased traces at entry

% trace T could be aliased with NT due to entry points-to relationship PT->DPT
predicate trace_alias(in SUM:sum,in T:t_trace,AT:t_trace,
                      PT:t_trace,DPT:t_trace).
~no_entry_trace_alias(), ?trace_alias(SUM,T,_,_,_),
    trace_sub(T,drf{ST},RT), entry_points(SUM,ST,DST), ~trace_bad_cast(SUM,DST),
    trace_compose(SUM,DST,RT,AT), ~trace_bad_cast(SUM,AT),
    +trace_alias(SUM,T,AT,ST,DST).

% fill in glob_trace_rename() if we are not computing global points-to rels
no_comp_glob_points(), +glob_trace_rename(T,T).

% base rel_inst_trace to extend according to aliases
% only generate for non-global callee roots, pure global-global aliasing
% will be handled within the callee
rel_inst_trace(I,P,CT,T,G), +ext_rel_inst_trace(I,P,CT,T,G,rel_direct).

predicate inst_may_access_glob(I:sum).
rel_inst_trace(I,_,_,T,_), trace_root(T,glob{_}), +inst_may_access_glob(I).
inst_usemod(I,CT,_), trace_root(CT,glob{_}), +inst_may_access_glob(I).
inst_anyuse(I), +inst_may_access_glob(I).

% extend ext_rel_inst_trace according to any aliased traces on entry to SUM
ext_rel_inst_trace(I,P,CT,T,G,_), CT\=rfld{_,_,_},
    (~trace_root(T,glob{_}); ~inst_may_access(I,T,_), inst_may_access_glob(I)),
    sum_body(SUM,P), trace_alias(SUM,T,NT,PT,DPT),
    +ext_rel_inst_trace(I,P,CT,NT,G,rel_alias{T,PT,DPT}),
    ~trace_root(NT,arg{_}), inst_may_access(I,NT,_),
    +ext_rel_inst_trace(I,P,NT,NT,G,rel_direct).

% extend rel_inst_trace according to side effects on aliased traces on entry
% to SUM. if S is written with DS and S might alias NS, NS may also point to DS
access(AP,S,write), sum_body(SUM,AP), trace_alias(SUM,S,NS,PT,DPT),
    ext_rel_inst_trace(I,P,CT,drf{NS},G,_), val(P,S,trace{DS},_),
    +ext_rel_inst_trace(I,P,CT,DS,G,rel_alias{drf{NS},PT,DPT}).

% have to use a td_inst_trace for aliasing that is not as precise with
% guards as we'd like. due to fixpointing entry aliasing over loops
% that makes figuring out the relevant traces impossible without introducing
% cycles. can probably fix this only by analyzing cil_sum_body() instead
predicate alias_td_inst_trace(in I:sum,in P:pp,in T:t_trace,CT:t_trace,G:g_guard).
?alias_td_inst_trace(I,P,T,_,_), trace_sub(T,ST,RT),
    ext_rel_inst_trace(I,P,CST,ST,G,_),
    trace_compose(I,CST,RT,CT), +alias_td_inst_trace(I,P,T,CT,G).
?alias_td_inst_trace(I,P,T,_,_), (~trace_root(T,arg{_}); I=s_loop{_}),
    inst_may_access(I,T,_),
    inst_trace(I,P,T,trace{T},G),
    +alias_td_inst_trace(I,P,T,T,G).

% generate entry aliasing on loops and callees

% to identify aliased traces on invoked calls and loops, we need take all
% traces the callee could access, map them back to traces in the current
% function, and see if there is an intersection where a caller trace could
% be accessed through two different callee traces

% hack for dealing with function pointers where the same c_instr may
% reference multiple different targets. TODO: fixme
predicate actual_usemod(in FN:string,in T:t_trace).
?actual_usemod(FN,T), trace_sub(T,ST,_),
    sum_usemod(FN,s_func)->stuse(ST,_), +actual_usemod(FN,T).

% get aliased traces on each call/loop. filter according to possibly
% aliased traces we know will end up as side effect type invariants
% (same root) or as global invariants (same global)
ext_rel_inst_trace(I,P,drf{CPT},T,G0,_), alias_td_inst_trace(I,P,T,CT,G1),
    trace_root(CPT,R0), trace_root(CT,R1),
    R0\=R1, ~(R0=glob{_}, R1=glob{_}),
    inst_may_access(I,drf{CPT},Y0), inst_may_access(I,CT,Y1),
    (Y0=write; Y0=deepwrite; Y1=write; Y1=deepwrite),
    guard(P,GG), and3(GG,G0,G1,G), #satasn(G,ASN),
    +try_asn_points(I,fn_entry,CPT,CT,asn_entry{P,T,drf{CPT},CT,ASN}).

% fill in the second half of each alias relationship, S->*T => T->*T as well.
% need this for renaming later
try_asn_points(I,fn_entry,_,drf{T},_),
    +try_asn_points(I,fn_entry,T,drf{T},asn_none{I}).

% merging assignments together

predicate pri_points_asn(in A0:t_points_asn,in A1:t_points_asn).
+pri_points_asn(_,asn_none{_}).

predicate merge_points_asns(in A0:t_points_asn,in A1:t_points_asn,
                            A:t_points_asn).
?merge_points_asns(A0,A1,_), lessthan(A0,A1), pri_points_asn(A0,A1),
    +merge_points_asns(A0,A1,A0).
?merge_points_asns(A0,A1,_), lessthan(A0,A1), ~pri_points_asn(A0,A1),
    +merge_points_asns(A0,A1,A1).
?merge_points_asns(A0,A1,_), lessthan(A1,A0),
    merge_points_asns(A1,A0,A), +merge_points_asns(A0,A1,A).
+merge_points_asns(A,A,A).

predicate merge_points_asns_list(in BA:t_points_asn,in ALIST:list[t_points_asn],A:t_points_asn).
+merge_points_asns_list(A,[],A).
?merge_points_asns_list(BA,[NA|TAIL],_),
    merge_points_asns(BA,NA,NBA), merge_points_asns_list(NBA,TAIL,A),
    +merge_points_asns_list(BA,[NA|TAIL],A).

try_asn_points(SUM,POS,S,T,_),
    \/try_asn_points(SUM,POS,S,T,XA):list_all(XA,[BA|ALIST]),
    merge_points_asns_list(BA,ALIST,ASN),
    +asn_points(SUM,POS,S,T,ASN).

% rename traces in function/loop entry/exit aliasing

% at entry and exit to each function and loop, we want to rename traces in the
% points-to graphs in a fashion that will simplify them while still preserving
% the structure of the original graph.
%
% at entry to functions/loops, we are concerned with eliminating redundant
% points-to relationships between complex aliased structures. if S->drf{T}
% is in the entry graph, drf{S}->drf{drf{T}} will as well, but does not
% provide any new information. rename drf{T} and all subtraces to drf{S} to
% collapse the two together, giving the final relationship T->drf{S}
%
% at exit to functions/loops, we filter out fresh traces, those heap cells
% allocated during execution of the function/loop (or any callees), by renaming
% them according to how they are used in the exit graph. if T->fresh{X} in
% the exit graph, rename fresh{X} to drf{T}, allowing us to omit the edge from
% the exit graph. if another S->fresh{X} as well, S->drf{T} will be in the
% exit graph

% T may be renamed to NT in the graph for SUM/POS. generated only for the roots
% of structures (not fld{_,_,_} or rfld{_,_,_})
predicate filter_rename(SUM:sum,POS:point_pos,T:t_trace,NT:t_trace,
                        ASN:t_points_asn).

predicate fld_filter_rename(SUM:sum,POS:point_pos,T:t_trace,NT:t_trace,
                            ASN:t_points_asn).
fld_filter_rename(SUM,POS,T,NT,ASN), T\=fld{_,_,_}, T\=rfld{_,_,_},
    +filter_rename(SUM,POS,T,NT,ASN).
fld_filter_rename(SUM,POS,fld{FT,F,C},NT,ASN),
    trace_compose(SUM,NT,rfld{empty,F,C},NFT),
    +fld_filter_rename(SUM,POS,FT,NFT,ASN).
fld_filter_rename(SUM,POS,rfld{FT,F,C},NT,ASN),
    trace_compose(SUM,NT,fld{empty,F,C},NFT),
    +fld_filter_rename(SUM,POS,FT,NFT,ASN).

% in the entry graph we are renaming the target of any pointer
% aliased with another
asn_points(SUM,fn_entry,S,T,ASN),
    ~trace_root(T,glob{_}),
    trace_simplify(SUM,drf{S},DS),
    +fld_filter_rename(SUM,fn_entry,T,DS,ASN).

% in the exit graph we are renaming local heap traces reachable at exit only,
% so add filter sources for any external traces that point to them
asn_points(SUM,fn_exit,S,T,ASN),
    trace_alloc(SUM,S,ak_external), trace_alloc(SUM,T,ak_heap_local),
    ~drop_spoints(SUM,fn_exit,S,drf{S}),
    ~(trace_sub(S,fld{STR,_,C},_), comp_to_relative(STR,S,RS),
      comp_poly(C,_,RS,_)),
    trace_simplify(SUM,drf{S},DS),
    +fld_filter_rename(SUM,fn_exit,T,DS,ASN).

% we need additional fresh sources if there are multiple levels of fresh values
asn_points(SUM,fn_exit,S,T,ASN),
    trace_alloc(SUM,S,ak_heap_local), trace_alloc(SUM,T,ak_heap_local),
    ~trace_simplify(SUM,drf{S},T),
    trace_sub(S,BS,RS), filter_rename(SUM,fn_exit,BS,NBS,_),
    trace_compose(SUM,NBS,RS,NS),
    trace_simplify(SUM,drf{NS},DNS),
    +fld_filter_rename(SUM,fn_exit,T,DNS,ASN).

filter_rename(SUM,POS,T,_,ASN),
    trace_sub(T,BT,RT), T\=BT, filter_rename(SUM,POS,BT,NBT,_),
    trace_compose(SUM,NBT,RT,XNT),
    +filter_rename(SUM,POS,T,XNT,ASN).

% NT is a renaming for T but is pre-empted by another
predicate weak_filter_rename(SUM:sum,POS:point_pos,T:t_trace,NT:t_trace).

% when there are multiple renamings for the same value, pick one and mark all
% others as weak. rename to T0 over T1 with priority PRI, where the renaming
% with lower priority (higher value) is marked as weak
predicate pri_rename(in T0:t_trace,in T1:t_trace,PRI:int).
filter_rename(SUM,POS,T,T0,_), filter_rename(SUM,POS,T,T1,_), lessthan(T0,T1),
    \/pri_rename(T0,T1,P0):int_min_all(P0,PRI0),
    \/pri_rename(T1,T0,P1):int_min_all(P1,PRI1),
    (int_lt(PRI0,PRI1), WEAK=T1; int_lt(PRI1,PRI0), WEAK=T0),
    +weak_filter_rename(SUM,POS,T,WEAK).

% favor non-return renamings over return renamings
pri_rename(T0,T1,1) :-
    ~trace_root(T0,return), trace_root(T1,return).

% favor global renamings over local renamings
pri_rename(T0,T1,2) :-
    trace_root(T0,glob{_}), ~trace_root(T1,glob{_}).

% favor renamings that don't use rfld
pri_rename(T0,T1,3) :-
    ~trace_sub(T0,rfld{_,_,_},_), trace_sub(T1,rfld{_,_,_},_).

% favor shallower traces over deeper traces (in deref count)
pri_rename(T0,T1,4) :-
    trace_derefs(T0,N0), trace_derefs(T1,N1), int_lt(N0,N1).

% cases where a pointer to the struct is embedded in itself
pri_rename(T0,T1,5) :- trace_sub(T1,T0,_).

% otherwise pick canonically
pri_rename(T0,T1,6) :- ~lessthan(T0,T1).
+pri_rename(_,_,7).

% the filtered entry/exit graphs, S->T should be summarized on loop/call SUM
% or as a global or composite invariant
predicate add_filt_points(SUM:sum,POS:point_pos,S:t_trace,T:t_trace,ASN:t_points_asn).
predicate try_filt_points(SUM:sum,POS:point_pos,S:t_trace,T:t_trace,ASN:t_points_asn).

% T should be renamed to NT in the filtered graph for SUM
predicate trace_rename(in SUM:sum,in POS:point_pos,in T:t_trace,NT:t_trace,
                       ASN:t_points_asn).
?trace_rename(SUM,POS,T,_,_),
    trace_sub(T,BT,RT), filter_rename(SUM,POS,BT,NBT,ASN),
    ~weak_filter_rename(SUM,POS,BT,NBT),
    trace_compose(SUM,NBT,RT,NT), +trace_rename(SUM,POS,T,NT,ASN).
?trace_rename(SUM,POS,T,_,_),
    ~(trace_sub(T,BT,_), filter_rename(SUM,POS,BT,_,_)),
    glob_trace_rename(T,NT), +trace_rename(SUM,POS,T,NT,asn_none{SUM}).

% rename the entry/exit graphs and add each NS->NT to the filtered graphs
asn_points(SUM,POS,S,T,PASN),
    (POS=fn_entry; ~trace_simplify(SUM,drf{S},T)),
    trace_rename(SUM,POS,S,NS,_), trace_rename(SUM,POS,T,NT,RASN),
    (POS=fn_entry, ~trace_simplify(SUM,drf{NS},NT);
     POS=fn_exit, ~trace_simplify(SUM,drf{NS},T)),
    merge_points_asns(PASN,RASN,ASN), +try_filt_points(SUM,POS,NS,NT,ASN).

try_filt_points(SUM,POS,S,T,_),
    \/try_filt_points(SUM,POS,S,T,XA):list_all(XA,[BA|ALIST]),
    merge_points_asns_list(BA,ALIST,ASN),
    +add_filt_points(SUM,POS,S,T,ASN).

% add_filt_points(SUM,POS,S,T) are behaviors that should not be considered
% for per-function summarization
predicate omit_points(SUM:sum,POS:point_pos,S:t_trace,T:t_trace,omit_reason).

% check that a summary trace has been fully simplified
predicate check_simplify(SUM:sum,T:t_trace).
check_simplify(SUM,T), trace_sub(T,SUB,_), trace_simplify(SUM,SUB,NSUB),
    SUB\=NSUB, +warning("Summary trace not fully simplified:",T).

% dropping generated points-to edges

% drop edges based on baked-in analysis behavior
add_filt_points(SUM,POS,S,T,_), drop_spoints(SUM,POS,S,T),
    +omit_points(SUM,POS,S,T,omit_dropped).

% drop edges pointing to constant strings, which are immutable
add_filt_points(SUM,POS,S,T,_), trace_root(S,cstr{_}),
    +omit_points(SUM,POS,S,T,omit_dropped).
add_filt_points(SUM,POS,S,T,_), trace_root(T,cstr{_}),
    +omit_points(SUM,POS,S,T,omit_dropped).

% drop edges pointing to a direct subtrace - these are recursive or identity
add_filt_points(SUM,POS,S,T,_), trace_sub(drf{S},T,_),
    +omit_points(SUM,POS,S,T,omit_dropped).

% drop edges which are redundant given an edge between their subtraces
add_filt_points(SUM,POS,S,drf{T},_), trace_sub(S,drf{SS},R),
    (trace_alloc(SUM,SS,ak_external); POS=fn_entry),
    add_filt_points(SUM,POS,SS,TT,_), trace_compose(SUM,TT,R,T),
    +omit_points(SUM,POS,S,drf{T},omit_dropped).

% drop edges if the traces involved cannot be typed as pointers or composites
add_filt_points(SUM,POS,S,T,_), trace_type(SUM,S,SY),
    (SY=y_ptr{Y0}, trace_type(SUM,T,Y1);
     Y0=SY, T=drf{PT}, trace_type(SUM,PT,Y1)),
    Y0\=y_array{_,_}, Y1\=y_array{_,_}, ~check_cast(Y0,Y1),
    +omit_points(SUM,POS,S,T,omit_dropped).

% drop edges containing casts between incompatible types, which casting.clp
% checks cannot occur
add_filt_points(SUM,POS,S,T,_), trace_bad_cast(SUM,S),
    +omit_points(SUM,POS,S,T,omit_dropped).
add_filt_points(SUM,POS,S,T,_), trace_bad_cast(SUM,T),
    +omit_points(SUM,POS,S,T,omit_dropped).

% find polymorphic composite type invariants

% FIXME

%add_filt_points(SUM,fn_exit,T,DT,_), trace_root(DT,glob{_}),
%    trace_sub(T,STR,TR), trace_type(SUM,STR,y_comp{C}), comp_poly(C,_,TR,_),
%    ~(comp_poly(C,XFTR,TR,_), trace_compose(SUM,STR,XFTR,XFT),
%      ~add_filt_points(SUM,fn_exit,XFT,root{glob{_}},_)),
%    comp_poly(C,FTR,TR,AT), trace_compose(SUM,STR,FTR,FT),
%    add_filt_points(SUM,fn_exit,FT,root{glob{FN}},_),
%    +omit_points(SUM,fn_exit,FT,root{glob{FN}},omit_poly_inv),
%    +add_spoints(td_comp_points{C,STR},FT,root{glob{FN}}),
%    actual_usemod(FN,DT), +add_spoints(td_points{FN,s_func,fn_entry},AT,DT).

%add_filt_points(SUM,fn_exit,T,DT,_), ~trace_root(DT,glob{_}),
%    trace_sub(T,STR,TR), trace_type(SUM,STR,y_comp{C}), comp_poly(C,_,TR,_),
%    cil_curfn(FN), +add_spoints(td_points{FN,SUM,fn_exit},T,DT).
%add_filt_points(SUM,fn_exit,T,DT,_), trace_root(DT,glob{_}),
%    trace_sub(T,STR,TR), trace_type(SUM,STR,y_comp{C}),
%    comp_poly(C,XFTR,TR,_), trace_compose(SUM,STR,XFTR,XFT),
%    ~add_filt_points(SUM,fn_exit,XFT,root{glob{_}},_),
%    cil_curfn(FN), +add_spoints(td_points{FN,SUM,fn_exit},T,DT).
%add_filt_points(SUM,fn_exit,S,T,_),
%    trace_sub(S,STR,RS), trace_type(SUM,STR,y_comp{C}), comp_poly(C,RS,_,_),
%    +omit_points(SUM,fn_exit,S,T,omit_poly_inv),
%    cil_curfn(FN), +add_spoints(td_points{FN,SUM,fn_exit},S,T).

add_filt_points(SUM,POS,S,T,_),
    trace_sub(S,fld{STR,_,C},_), comp_to_relative(STR,S,RS),
    comp_poly(C,_,drf{RS},_),
    +omit_points(SUM,POS,S,T,omit_poly_inv).

% find composite type invariants

% points-to relationships between traces that have a common prefix generally
% reflect a composite type invariant rather than behavior particular to the
% function in question. identify these, add them to the composite type summary
% and prevent them from entering other summaries

% also valid are points-to relationships where the source is in a structure
% and the target is global data. these are not as clear-cut but are usually
% quite compact and sufficiently precise

% S->T *MAY* be summarized on the comp C given by STR
predicate add_filt_comp_points(C:string,STR:t_trace,S:t_trace,T:t_trace,ASN:t_points_asn).

% get the potential composite type points-to relationships
add_filt_points(SUM,POS,S,T,ASN),
    ~omit_points(SUM,POS,S,T,omit_dropped),
    ~omit_points(SUM,POS,S,T,omit_poly_inv),
    trace_sub(S,fld{STR,_,C},_), comp_to_relative(STR,T,_),
    ~omit_comp_spoints(C,SUM,STR,S,T),
    +omit_points(SUM,POS,S,T,omit_comp_inv),
    POS=fn_exit, +add_filt_comp_points(C,STR,S,T,ASN).

% omit invariants pre-empted by other invariants on internal structs
predicate weak_comp_spoints(C:string,STR:t_trace,S:t_trace,T:t_trace).
add_filt_comp_points(_,STR,S,T,_), trace_sub(STR,SSTR,_), STR\=SSTR,
    add_filt_comp_points(SC,SSTR,S,T,_),
    +weak_comp_spoints(SC,SSTR,S,T).

% add all composite type invariants, omitting the corresponding points-to
% relations for consideration in other summaries
add_filt_comp_points(C,STR,S,T,ASN), ~weak_comp_spoints(C,STR,S,T),
    +check_simplify(s_func,S), +check_simplify(s_func,T),
    +add_spoints_display(td_comp_points{C,STR},S,T,ASN).

%?omit_comp_spoints(C,SUM,STR,S,T),
%    trace_root(S,glob{_}), trace_root(T,glob{_}), ~trace_sub(T,STR,_),
%    +omit_comp_spoints(C,SUM,STR,S,T).

no_comp_glob_points(), +omit_comp_spoints(_,_,_,_,_).

% find global invariants

% points-to relationships between traces that are both global generally reflect
% a global invariant rather than behavior particular to the function in
% question. identify these, add them to the global summary and prevent them
% from entering the function entry/exit summaries
add_filt_points(SUM,POS,S,T,ASN),
    ~omit_points(SUM,POS,S,T,omit_dropped),
    ~omit_points(SUM,POS,S,T,omit_poly_inv),
    ~omit_points(SUM,POS,S,T,omit_comp_inv),
    trace_root(S,glob{G}), trace_root(T,glob{_}), ~omit_glob_spoints(G,S,T),
    +check_simplify(s_func,S), +check_simplify(s_func,T),
    +omit_points(SUM,POS,S,T,omit_glob_inv),
    POS=fn_exit, +add_spoints_display(td_glob_points{G},S,T,ASN).

no_comp_glob_points(), +omit_glob_spoints(_,_,_).

% function entry/exit summaries

% add to the entry/exit summaries any relationships not covered by the
% composite and global invariants
add_filt_points(SUM,POS,S,T,ASN), ~omit_points(SUM,POS,S,T,_),
    SUM\=s_call{_}, cil_curfn(FN),
    +check_simplify(SUM,S), +check_simplify(SUM,T),
    trace_alloc(SUM,S,ak_external), trace_alloc(SUM,T,ak_external),
    +add_spoints_display(td_points{FN,SUM,POS},S,T,ASN).
add_filt_points(s_call{I},POS,S,T,ASN), ~omit_points(s_call{I},POS,S,T,_),
    +check_simplify(s_call{I},S), +check_simplify(s_call{I},T),
    dircall(I,FN), +add_spoints_display(td_points{FN,s_func,POS},S,T,ASN).
add_filt_points(s_call{I},POS,S,T,ASN), ~omit_points(s_call{I},POS,S,T,_),
    +check_simplify(s_call{I},S), +check_simplify(s_call{I},T),
    anycall(I,FN,indirect), actual_usemod(FN,drf{S}), actual_usemod(FN,T),
    +add_spoints_display(td_points{FN,s_func,POS},S,T,ASN).

% add sunify for any accessed traces in each summary that were inside
% a malloc and renamed at exit
filter_rename(SUM,fn_exit,T,NT,_), ~weak_filter_rename(SUM,fn_exit,T,NT),
    cil_curfn(F), +sum_exit(F,SUM)->sunify(T,NT).

% baked in analysis behavior

import "aliasingbaked.clp".

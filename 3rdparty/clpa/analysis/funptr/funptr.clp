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

% top-down propagation of function pointers

import "../memory/intignore.clp".
import "funptrui.clp".

analyze session_name("cil_body").
analyze analysis_name("funptr").
analyze topdown().

% extra entry points-to edges for function pointer analysis
session sum_funptr_entry(FN:string) containing [sglob_points].

% trace T may point to global trace GT at entry
predicate sglob_points(T:t_trace,GT:t_trace).

% RULES

+no_entry_aliasing().
+ignore_int_casts().

predicate trace_alias(in T:t_trace,AT:t_trace).
?trace_alias(T,_), trace_alias(T,NT), ~trace_root(NT,glob{_}),
    trace_alias(NT,NNT), +trace_alias(T,NNT).
?trace_alias(T,_), glob_trace_rename(T,GT), +trace_alias(T,GT).

?trace_alias(T,_), ~trace_root(T,glob{_}), trace_sub(T,drf{ST},RT),
    cil_curfn(FN), sum_entry(FN,s_func)->spoints(ST,DST),
    trace_compose(s_func,DST,RT,AT), glob_trace_rename(AT,GAT),
    +trace_alias(T,GAT).
?trace_alias(T,_), ~trace_root(T,glob{_}), trace_sub(T,drf{ST},RT),
    cil_curfn(FN), sum_funptr_entry(FN)->sglob_points(ST,DST),
    trace_compose(s_func,DST,RT,AT), glob_trace_rename(AT,GAT),
    +trace_alias(T,GAT).
?trace_alias(T,_), ~trace_root(T,glob{_}), trace_sub(T,drf{ST},RT),
    trace_sub(ST,fld{STR,_,C},_), comp_to_relative(STR,ST,RST),
    sum_comp(C)->sxpoints(RST,RTT), comp_from_relative(STR,RTT,TT),
    trace_compose(s_func,TT,RT,AT), glob_trace_rename(AT,GAT),
    +trace_alias(T,GAT).

?trace_alias(root{glob{G}},_),
    sum_glob(G)->spoints(fld{root{glob{G}},"next",_},fld{root{glob{OG}},_,_}),
    +trace_alias(root{glob{G}},root{glob{OG}}).
?trace_alias(root{glob{G}},_),
    cil_var_name(_,G,TYP), cil_type_comp(TYP,CNAME),
    sum_comp(CNAME)->spoints(fld{empty,"next",_},root{glob{OG}}),
    +trace_alias(root{glob{G}},root{glob{OG}}).

% memory.clp extensions

% watch for pointers to global data passed directly into the callee
rel_inst_trace(s_call{I},P,drf{CT},T,G0), CT=root{arg{_}},
    trace_type(s_call{I},drf{CT},y_func),
    guard(P,G1), #and(G0,G1,G), #satasn(G,ASN),
    trace_alias(T,GT), trace_root(GT,glob{_}), anycall(I,FN,_),
    +add_entry_display(FN,CT,GT,asn_funptr{P,T,GT,ASN}).

% indirect calls

% get the targets of indirect calls
icall(P,_,I), ~dircall(I,_), cil_instr_call(I,E), eval(P,E,trace{drf{T}},G0),
    guard(P,G1), #and(G0,G1,G), #satasn(G,ASN),
    trace_alias(T,root{glob{FN}}),
    +add_indirect_display(I,FN,asn_funptr{P,T,root{glob{FN}},ASN}).

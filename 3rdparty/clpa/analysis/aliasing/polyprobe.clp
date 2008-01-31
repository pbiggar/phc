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

% look for structure-local polymorphism:
% a->handler(a->private)

import "../memory/intignore.clp".

analyze session_name("cil_body").
analyze analysis_name("polyprobe").
analyze bottomup().

+no_entry_aliasing().

predicate add_spoly(C:string,FT:t_trace,T:t_trace,AT:t_trace).
predicate str_spoly(C:string,FTS:string,TS:string,ATS:string).
add_spoly(C,FT,T,AT), +poly_comp(C)->spoly(FT,T,AT),
    trace_string(FT,FTS), trace_string(T,TS), trace_string(AT,ATS),
    +str_spoly(C,FTS,TS,ATS).

?- str_spoly(C,FT,T,AT).

% funptr trace FT is passed T through argument AN
predicate indir_arg(I:c_instr,FT:t_trace,T:t_trace,AN:int).
icall(P,_,I), ~dircall(I,_), cil_instr_call(I,E), eval(P,E,trace{drf{FT}},_),
    cil_instr_call_arg(I,AN,AE), eval(P,AE,trace{T},_),
    +indir_arg(I,FT,T,AN).

predicate trace_sub_assign(in T:t_trace,STR:t_trace,RT:t_trace).
trace_sub_assign(T,STR,RT) :- trace_sub(T,STR,RT).
%trace_sub_assign(T,STR,RT) :-
%    trace_sub(T,DS,RT0), sassign_write(_,S,trace{DS},_),
%    trace_sub(drf{S},STR,RT1), trace_compose(s_func,RT1,RT0,RT).

indir_arg(_,FT,drf{fld{STR,F,C}},AN),
    trace_sub_assign(FT,STR,FTR), ~trace_sub_assign(FT,fld{STR,F,C},_),
    (trace_derefs(FTR,1); trace_derefs(FTR,2)),
    +add_spoly(C,FTR,drf{fld{empty,F,C}},drf{root{arg{AN}}}).

indir_arg(_,FT,STR,AN),
    trace_sub_assign(FT,STR,FTR), trace_sub_assign(FT,fld{STR,BF,C},_),
    (trace_derefs(FTR,1); trace_derefs(FTR,2)),
    cil_comp(C)->cil_field_name(_,F,PTYP,_,_), F\=BF,
    cil_comp(C)->cil_type_ptr(PTYP,TYP), cil_comp(C)->cil_type_void(TYP),
    +add_spoly(C,FTR,drf{fld{empty,F,C}},drf{fld{drf{root{arg{AN}}},F,C}}).

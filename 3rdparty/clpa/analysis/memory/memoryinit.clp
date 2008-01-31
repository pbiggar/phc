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

% extensions to memory.clp for processing a static initializer.
% should only be used when the current analysis is running over cil_init

import "memory.clp".

% PREDICATES

predicate ilval(in I:c_init,T:t_trace).
predicate ieval(in E:c_exp,V:t_trace_val).

% RULES

+sum_body(s_func,p_abort).

% fill in traces corresponding to each initializer
cil_init(G), cil_var_init(_,INIT), +ilval(INIT,root{glob{G}}).
cil_init_cmpnd_field(INIT,FX,SINIT), cil_field_name(FX,F,_,_,_),
    cil_init_cmpnd_type(INIT,TYP), cil_type_comp(TYP,C),
    ilval(INIT,T), +ilval(SINIT,fld{T,F,C}).
cil_init_cmpnd_index(INIT,_,SINIT), ilval(INIT,T), +ilval(SINIT,T).

% initializer expression evaluation. since the initializer just contains
% address-of expressions and constants no per-pp evaluation needs to be done
ieval(E,V) :- eval(p_abort,E,V,_).

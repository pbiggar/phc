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

% per-global phase of aliasing.clp. scan global static initializers for new
% global and type invariants, and fill in sum_glob->spoints according to any
% composite type invariants discovered during per-function analysis

import "../memory/memoryinit.clp".
import "../memory/intignore.clp".
import "aliasinginitui.clp".

analyze session_name("cil_init").
analyze analysis_name("aliasinit").

predicate omit_comp_spoints(in C:string,in SR:t_trace,in TR:t_trace).
predicate drop_spoints(in S:t_trace,in T:t_trace).

?drop_spoints(S,T), trace_sub(S,STR,RS), trace_type(s_func,STR,y_comp{C}),
    poly_comp(C)->spoly(_,RS,_), +drop_spoints(S,T).

% RULES

% points-to relationships from static initializers
predicate init_spoints(S:t_trace,T:t_trace,E:c_exp).
cil_init_single(INIT,E), ilval(INIT,T), ieval(E,trace{DT}),
    ~drop_spoints(T,DT), +init_spoints(T,DT,E).

% now add the invariant, using the composite type if available

predicate use_comp_spoints(S:t_trace,T:t_trace).

init_spoints(fld{FS,F,C},T,E), ~omit_comp_spoints(C,fld{empty,F,C},T),
    +add_spoints_display(td_comp_points{C,FS},fld{FS,F,C},T,E),
    +use_comp_spoints(fld{FS,F,C},T).

cil_init(G), init_spoints(S,T,E), ~use_comp_spoints(S,T),
    +add_spoints_display(td_glob_points{G},S,T,E).

% fill in special sum_glob_init summary with just the initializer edges
cil_init(G), init_spoints(S,T,_), +sum_glob_init(G)->sxpoints(S,T).

%+omit_comp_spoints(_,_,_).

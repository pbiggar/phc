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

% generate displays for use in UI explaining generated spoints edges
% imported directly by aliasinginit.clp

import "uibase.clp".

% PREDICATES

% add the given TGT/S/T spoints edge, and make a display showing the assignment
% from E in the initializer for the current global
predicate add_spoints_display(TGT:t_points_target,S:t_trace,T:t_trace,
                              E:c_exp).
add_spoints_display(TGT,S,T,_), +add_spoints(TGT,S,T).

% RULES

% add displays for generated spoints

cil_init(G), glob_location(G,FILE,MINLINE,MAXLINE), cleanup_glob_string(G,GS),
    add_spoints_display(TGT,S,T,E), spoints_display_name(TGT,S,T,DNAME),
    \/(add_spoints_display(XTGT,XS,XT,XE), spoints_display_name(XTGT,XS,XT,DNAME)):list_all(XE,[E|_]),
    cil_exp_x_location(E,_,ELINE,_,_,_),
    spoints_display_title(TGT,S,T,TITLE),
    +display_add(DNAME,false,"alias_why",TITLE,GS,FILE,MINLINE,MAXLINE,ELINE,
        [d_line_text{ELINE,"aliasadd",d_top,TITLE,[]}]).

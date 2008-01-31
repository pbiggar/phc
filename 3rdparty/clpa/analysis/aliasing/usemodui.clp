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

% usemod UI information

import "uibase.clp".

% add displays for mutable type fields and globals

curfn_location(FS,FILE,MINLINE,MAXLINE), add_comp_write(C,F,_),
    \/add_comp_write(C,F,XP):list_all(XP,[P|_]),
    index_item(IITEM),
    point_location(P,_,LINE), scwrite_display_name(C,F,DNAME,TITLE),
    +display_add(DNAME,false,"usemod_why",TITLE,FS,FILE,MINLINE,MAXLINE,LINE,
        [IITEM,d_line_text{LINE,"usemodadd",d_top,TITLE,[]}]).

curfn_location(FS,FILE,MINLINE,MAXLINE), add_glob_write(G,_,_),
    \/add_glob_write(G,XP,XENT):list_all(pair{XP,XENT},[pair{P,ENTRY}|_]),
    index_item(IITEM), sum_body(SUM,P),
    point_location(P,_,LINE), sgwrite_display_name(G,DNAME,TITLE),
    (ENTRY=no, ITEMS=[];
     ENTRY=yes{pair{S,T}}, entry_points_item(SUM,S,T,ITEM), ITEMS=[ITEM]),
    +display_add(DNAME,false,"usemod_why",TITLE,FS,FILE,MINLINE,MAXLINE,LINE,
        [IITEM,d_line_text{LINE,"usemodadd",d_top,TITLE,[]}|ITEMS]).

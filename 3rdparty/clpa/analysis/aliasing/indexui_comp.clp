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

% construct an index display with all points-to edges for the current type

import "../memory/traces.clp".

analyze session_name("cil_comp").
analyze analysis_name("indexui_comp").

import "uibase.clp".

predicate invariant_info_item(ITEM:displayitem).
cil_comp(C), cil_comp(C)->cil_comp_location(_,_,LINE),
    sum_comp(C)->spoints(S,T),
    dstring_trace(s_func,S,SSTR), dstring_trace(s_func,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR," in ",C],TEXT),
    spoints_display_name(td_comp_points{C,empty},S,T,DNAME),
    +invariant_info_item(
        d_line_text{LINE,"pointscomp",d_top,TEXT,[d_link{DNAME,"link"}]}).

predicate write_info_item(ITEM:displayitem).
cil_comp(C), cil_comp(C)->cil_comp_location(_,_,LINE),
    sum_usemod_comp(C)->scwrite(F),
    scwrite_display_name(C,F,DNAME,TEXT),
    +write_info_item(
        d_line_text{LINE,"usemodcomp",d_top,TEXT,[d_link{DNAME,"link"}]}).

predicate extra_info_item(ITEM:displayitem).

% used types item
predicate globtype_item(ITEM:displayitem).
cil_comp(C), cil_comp(C)->cil_comp_location(_,_,LINE),
    cil_type_comp(_,XC), XC\=C,
    index_comp_display_name(XC,DNAME,TITLE),
    +globtype_item(
        d_line_text{LINE,"globtype",d_top,TITLE,[d_link{DNAME,"link"}]}).
cil_comp(C), cil_comp(C)->cil_comp_location(_,_,LINE), globtype_item(_),
    \/globtype_item(ITEM):list_all(ITEM,ITEMS),
    comp_location(C,FILE,MINLINE,MAXLINE),
    index_comp_globtypes_display_name(C,DNAME,TITLE),
    +display_add(DNAME,false,"alias_globtypes",TITLE,
                 C,FILE,MINLINE,MAXLINE,LINE,ITEMS),
    +extra_info_item(
        d_line_text{LINE,"globtypeset",d_top,TITLE,[d_link{DNAME,"link"}]}).

cil_comp(C), comp_location(C,FILE,MINLINE,MAXLINE),
    \/invariant_info_item(PITEM):list_all(PITEM,PITEMS),
    \/write_info_item(WITEM):list_all(WITEM,WITEMS),
    \/extra_info_item(EITEM):list_all(EITEM,EITEMS),
    list_append(PITEMS,WITEMS,ITEMS0), list_append(ITEMS0,EITEMS,ITEMS),
    index_comp_display_name(C,DNAME,TITLE),
    +display_add(DNAME,false,"alias_set_comp",TITLE,
                 C,FILE,MINLINE,MAXLINE,MINLINE,ITEMS),
    +search_add(C,DNAME).

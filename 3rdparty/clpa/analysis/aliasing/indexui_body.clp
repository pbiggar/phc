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

% construct an index display with all points-to edges for the current function

import "../base/loops.clp".
import "../base/sumcallers.clp".
import "../memory/traces.clp".

analyze session_name("cil_body").
analyze analysis_name("indexui_body").

import "uibase.clp".

% aliasing edge items

predicate entry_info_item(SUM:sum,ITEM:displayitem).
cil_curfn(FN), sum_bound(SUM,_,_), sum_entry(FN,SUM)->spoints(S,T),
    sum_location(SUM,_,LINE), dstring_sum(SUM,SUMSTR),
    dstring_trace(SUM,S,SSTR), dstring_trace(SUM,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR," at entry to ",SUMSTR],TEXT),
    spoints_display_name(td_points{FN,SUM,fn_entry},S,T,DNAME),
    +entry_info_item(SUM,
        d_line_text{LINE,"pointsentry",d_top,TEXT,[d_link{DNAME,"link"}]}).

predicate exit_info_item(SUM:sum,ITEM:displayitem).
cil_curfn(FN), sum_bound(SUM,_,_), sum_exit(FN,SUM)->spoints(S,T),
    sum_location(SUM,_,LINE), dstring_sum(SUM,SUMSTR),
    dstring_trace(SUM,S,SSTR), dstring_trace(SUM,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR," at exit from ",SUMSTR],TEXT),
    spoints_display_name(td_points{FN,SUM,fn_exit},S,T,DNAME),
    +exit_info_item(SUM,
        d_line_text{LINE,"pointsexit",d_top,TEXT,[d_link{DNAME,"link"}]}).

% side info items

% items for calls/loops interior to SUM
predicate sum_info_item(SUM:sum,ITEM:displayitem).
sum_body(SUM,P), isum(P,_,CSUM), CSUM\=SUM, sum_info_item(CSUM,ITEM),
    +sum_info_item(SUM,ITEM).

% loop and direct call items
sum_body(SUM,P), isum(P,_,CSUM), CSUM\=SUM,
    (CSUM=s_loop{_}, cil_curfn(FN), NCSUM=CSUM;
     CSUM=s_call{I}, dircall(I,FN), NCSUM=s_func),
    sum_location(CSUM,_,LINE), index_body_display_name(FN,NCSUM,DNAME,TITLE),
    +sum_info_item(SUM,
        d_line_text{LINE,"bodyset",d_right,TITLE,[d_link{DNAME,"link"}]}).

% indirect call items
predicate indirect_info_item(I:c_instr,ITEM:displayitem).
anycall(I,CFN,indirect), sum_location(s_call{I},_,LINE),
    cil_curfn(FN), indirect_display_name(FN,I,CFN,DNAME,TITLE),
    index_body_display_name(CFN,s_func,BDNAME,_),
    +indirect_info_item(I,
        d_line_text{LINE,"indircall",d_bottom,TITLE,
                    [d_link{DNAME,"link"},d_link{BDNAME,"body"}]}).
sum_body(SUM,P), icall(P,_,I), ~dircall(I,_),
    sum_location(s_call{I},_,LINE),
    \/indirect_info_item(I,ITEM):list_all(ITEM,ITEMS), ITEMS\=[],
    cil_curfn(FN), curfn_location(FS,FILE,MINLINE,MAXLINE),
    index_body_indircall_display_name(FN,I,CDNAME,CTITLE),
    +display_add(CDNAME,false,"alias_indirs",CTITLE,
                 FS,FILE,MINLINE,MAXLINE,LINE,ITEMS),
    +sum_info_item(SUM,
        d_line_text{LINE,"bodyset",d_right,CTITLE,[d_link{CDNAME,"link"}]}).
sum_body(SUM,P), icall(P,_,I), ~dircall(I,_),
    sum_location(s_call{I},_,LINE),
    \/indirect_info_item(I,ITEM):list_all(ITEM,[]),
    dstring_sum(s_call{I},ISTR),
    str_cat("No known indirect calls for ",ISTR,TITLE),
    +sum_info_item(SUM,
        d_line_text{LINE,"bodyset",d_right,TITLE,[]}).

% callers item
predicate caller_info_item(ITEM:displayitem).
cil_curfn(FN), cil_sum_caller(FN,s_func)->caller(CALLER,_,_,_),
    sum_location(s_func,_,LINE),
    index_body_display_name(CALLER,s_func,DNAME,TITLE),
    +caller_info_item(
        d_line_text{LINE,"caller",d_top,TITLE,[d_link{DNAME,"link"}]}).
sum_location(s_func,_,LINE),
    \/caller_info_item(ITEM):list_all(ITEM,ITEMS), ITEMS\=[],
    cil_curfn(FN), curfn_location(FS,FILE,MINLINE,MAXLINE),
    index_body_callers_display_name(FN,DNAME,TITLE),
    +display_add(DNAME,false,"alias_callers",TITLE,
                 FS,FILE,MINLINE,MAXLINE,LINE,ITEMS),
    +sum_info_item(s_func,
        d_line_text{LINE,"callerset",d_top,TITLE,[d_link{DNAME,"link"}]}).
sum_location(s_func,_,LINE),
    \/caller_info_item(ITEM):list_all(ITEM,[]),
    cil_curfn(FN), str_cat("No known callers for ",FN,TITLE),
    +sum_info_item(s_func,
        d_line_text{LINE,"callerset",d_top,TITLE,[]}).

% used vars/types item
predicate globtype_item(ITEM:displayitem).
cil_type_comp(_,C), sum_location(s_func,_,LINE),
    index_comp_display_name(C,DNAME,TITLE),
    +globtype_item(
        d_line_text{LINE,"globtype",d_top,TITLE,[d_link{DNAME,"link"}]}).
cil_var_global(X), cil_var_name(X,G,TYP),
    ~cil_type_func(TYP,_,_), sum_location(s_func,_,LINE),
    index_glob_display_name(G,DNAME,TITLE),
    +globtype_item(
        d_line_text{LINE,"globtype",d_top,TITLE,[d_link{DNAME,"link"}]}).
sum_location(s_func,_,LINE), globtype_item(_),
    \/globtype_item(ITEM):list_all(ITEM,ITEMS),
    cil_curfn(FN), curfn_location(FS,FILE,MINLINE,MAXLINE),
    index_body_globtypes_display_name(FN,DNAME,TITLE),
    +display_add(DNAME,false,"alias_globtypes",TITLE,
                 FS,FILE,MINLINE,MAXLINE,LINE,ITEMS),
    +sum_info_item(s_func,
        d_line_text{LINE,"globtypeset",d_top,TITLE,[d_link{DNAME,"link"}]}).

% final body index displays

cil_curfn(FN), curfn_location(FS,FILE,MINLINE,MAXLINE),
    sum_bound(SUM,_,_), sum_location(SUM,_,LINE),
    \/entry_info_item(SUM,IITEM):list_all(IITEM,IITEMS),
    \/exit_info_item(SUM,OITEM):list_all(OITEM,OITEMS),
    list_append(IITEMS,OITEMS,BITEMS), (~list_length(BITEMS,0); SUM=s_func),
    \/sum_info_item(SUM,SITEM):list_all(SITEM,SITEMS),
    list_append(BITEMS,SITEMS,ITEMS),
    index_body_display_name(FN,SUM,DNAME,TITLE),
    +display_add(DNAME,false,"alias_set",TITLE,
                 FS,FILE,MINLINE,MAXLINE,LINE,ITEMS),
    SUM=s_func, +search_add(FS,DNAME).

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
% imported directly by funptr.clp

import "../aliasing/uibase.clp".

% PREDICATES

type t_funptr_asn ::=
    asn_funptr{P:pp,T:t_trace,AT:t_trace,ASN:g_guard_asn}.

predicate add_indirect_display(I:c_instr,FN:string,ASN:t_funptr_asn).
add_indirect_display(I,FN,_), +add_sindirect(I,FN).

predicate add_entry_display(FN:string,T:t_trace,GT:t_trace,ASN:t_funptr_asn).
add_entry_display(FN,T,GT,_), +sum_funptr_entry(FN)->sglob_points(T,GT).

% RULES

% path and satisfying assignment items

% ITEM should be included in the display TGT with support ASN
predicate get_display_item(in ASN:t_funptr_asn,out ITEM:displayitem).

% PP is a point on the path to P corresponding to ASN. ITEM should be displayed
predicate get_path_item(in ASN:g_guard_asn,in P:pp,in PP:pp,
                        out ITEM:displayitem).
get_display_item(asn_funptr{P,_,_,RASN},ITEM) :-
    asn_path(P,RASN,nil,PATH), list_mem(PATH,PP),
    get_path_item(RASN,P,PP,ITEM).

% highlight the path given by the assignment
get_path_item(_,_,PP,ITEM) :-
    point_location(PP,_,PLINE),
    ITEM=d_line_style{PLINE,"pathline"}.
get_path_item(_,P,_,ITEM) :-
    point_location(P,_,LINE), sum_location(s_func,_,SLINE), LINE\=SLINE,
    ITEM=d_line_style{SLINE,"pathline"}.

% get a link showing why S may point to T at entry to SUM, (may fail)
predicate entry_points_link(in SUM:sum,in S:t_trace,in T:t_trace,DNAME:string).
entry_points_link(s_func,S,T,DNAME) :-
    cil_curfn(FN), sum_entry(FN,s_func)->spoints(S,T),
    spoints_display_name(td_points{FN,s_func,fn_entry},S,T,DNAME).
entry_points_link(s_func,S,T,DNAME) :-
    cil_curfn(FN), sum_funptr_entry(FN)->sglob_points(S,T),
    spoints_display_name(td_points{FN,s_func,fn_entry},S,T,DNAME).
entry_points_link(SUM,S,T,DNAME) :-
    trace_root(S,glob{G}), sum_glob(G)->sxpoints(S,T),
    spoints_display_name(td_glob_points{G},S,T,DNAME).
entry_points_link(SUM,S,T,DNAME) :-
    trace_sub(S,STR,RS), trace_type(SUM,STR,y_comp{C}),
    comp_to_relative(STR,T,RT), sum_comp(C)->sxpoints(RS,RT),
    spoints_display_name(td_comp_points{C,STR},S,T,DNAME).

% add any relevant entry aliasing
get_display_item(asn_funptr{_,drf{S},T,_},ITEM) :-
    sum_location(s_func,_,LINE),
    dstring_trace(s_func,S,SSTR), dstring_trace(s_func,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR," at entry"],TEXT),
    (entry_points_link(s_func,S,T,DNAME), LINKS=[d_link{DNAME,"link"}];
     ~entry_points_link(s_func,S,T,_), LINKS=[]),
    ITEM=d_line_text{LINE,"pathentry",d_bottom,TEXT,LINKS}.

% add displays for indirect calls and entry edges

curfn_location(FS,FILE,MINLINE,MAXLINE), add_indirect_display(I,CFN,_),
    \/add_indirect_display(I,CFN,XASN):list_all(XASN,[ASN|_]),
    \/get_display_item(ASN,AITEM):list_all(AITEM,AITEMS),
    index_item(IITEM), cil_curfn(FN), sum_location(s_func,_,LINE),
    indirect_display_name(FN,I,CFN,DNAME,TITLE),
    +display_add(DNAME,false,"funptr_why",TITLE,FS,FILE,MINLINE,MAXLINE,LINE,
        [IITEM,d_line_text{LINE,"funptradd",d_top,TITLE,[]}|AITEMS]).

curfn_location(FS,FILE,MINLINE,MAXLINE), add_entry_display(CFN,T,GT,_),
    \/add_entry_display(CFN,T,GT,XASN):list_all(XASN,[ASN|_]),
    \/get_display_item(ASN,AITEM):list_all(AITEM,AITEMS),
    index_item(IITEM), sum_location(s_func,_,LINE),
    TGT=td_points{CFN,s_func,fn_entry},
    spoints_display_title(TGT,T,GT,TITLE), spoints_display_name(TGT,T,GT,DNAME),
    +display_add(DNAME,false,"funent_why",TITLE,FS,FILE,MINLINE,MAXLINE,LINE,
        [IITEM,d_line_text{LINE,"aliasadd",d_top,TITLE,[]}|AITEMS]).

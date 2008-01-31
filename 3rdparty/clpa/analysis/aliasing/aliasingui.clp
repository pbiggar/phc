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
% imported directly by aliasing.clp

import "uibase.clp".

% PREDICATES

% add the given TGT/S/T spoints edge, and make a display showing why from ASN
predicate add_spoints_display(TGT:t_points_target,S:t_trace,T:t_trace,
                              ASN:t_points_asn).
add_spoints_display(TGT,S,T,_), +add_spoints(TGT,S,T).

% RULES

% path and satisfying assignment items

predicate asn_sum(in ASN:t_points_asn,out SUM:sum).
asn_sum(asn_exit{P,_},SUM) :- sum_body(SUM,P).
asn_sum(asn_entry{P,_,_,_,_},SUM) :- sum_body(SUM,P).
+asn_sum(asn_none{SUM},SUM).

% ITEM should be included in the display TGT with support ASN
predicate get_display_item(in TGT:t_points_target,in S:t_trace,in T:t_trace,
                           in ASN:t_points_asn,out ITEM:displayitem).

% PP is a point on the path to P corresponding to ASN. ITEM should be displayed
predicate get_path_item(in TGT:t_points_target,in S:t_trace,in T:t_trace,
                        in ASN:g_guard_asn,in P:pp,in PP:pp,
                        out ITEM:displayitem).
get_display_item(TGT,S,T,ASN,ITEM) :-
    (ASN=asn_exit{P,RASN}; ASN=asn_entry{P,_,_,_,RASN}),
    asn_path(P,RASN,nil,PATH), list_mem(PATH,PP),
    get_path_item(TGT,S,T,RASN,P,PP,ITEM).

% highlight the path given by the assignment, including both intermediate
% points as well as the summary line itself
get_path_item(_,_,_,_,_,PP,ITEM) :-
    point_location(PP,_,PLINE),
    ITEM=d_line_style{PLINE,"pathline"}.
get_path_item(_,_,_,_,P,_,ITEM) :-
    sum_body(SUM,P),
    point_location(P,_,LINE), sum_location(SUM,_,SLINE), LINE\=SLINE,
    ITEM=d_line_style{SLINE,"pathline"}.

% get a link showing why S may point to T at entry to SUM, (may fail)
predicate entry_points_link(in SUM:sum,in S:t_trace,in T:t_trace,DNAME:string).
entry_points_link(s_func,S,T,DNAME) :-
    cil_curfn(FN), sum_entry(FN,s_func)->spoints(S,T),
    spoints_display_name(td_points{FN,s_func,fn_entry},S,T,DNAME).
entry_points_link(SUM,S,T,DNAME) :-
    trace_root(S,glob{G}), sum_glob(G)->sxpoints(S,T),
    spoints_display_name(td_glob_points{G},S,T,DNAME).
entry_points_link(SUM,S,T,DNAME) :-
    trace_sub(S,STR,RS), trace_type(SUM,STR,y_comp{C}),
    comp_to_relative(STR,T,RT), sum_comp(C)->sxpoints(RS,RT),
    spoints_display_name(td_comp_points{C,STR},S,T,DNAME).
%cil_curfn(FN), inst_entry_points(SUM,S,T), (SUM=s_func; SUM=s_loop{_}),
%    trace_rename(SUM,fn_entry,S,S1), trace_rename(SUM,fn_entry,T,T1),
%    add_spoints(FN,SUM,fn_entry,S1,T1),
%    tostring(td_points{FN,SUM,fn_entry,S1,T1},DNAME),
%    +entry_points_link(SUM,S,T,DNAME).

% get an ITEM showing why S may point to T at entry to SUM
predicate entry_points_item(in SUM:sum,in S:t_trace,in T:t_trace,
                            ITEM:displayitem).
entry_points_item(SUM,S,T,ITEM) :-
    sum_location(SUM,_,LINE),
    dstring_trace(SUM,S,SSTR), dstring_trace(SUM,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR," at entry"],TEXT),
    (entry_points_link(SUM,S,T,DNAME), LINKS=[d_link{DNAME,"link"}];
     ~entry_points_link(SUM,S,T,_), LINKS=[]),
    ITEM=d_line_text{LINE,"pathentry",d_bottom,TEXT,LINKS}.

% add any relevant entry aliasing
predicate entry_points_find(in I:sum,in P:pp,in CT:t_trace,in T:t_trace,
                            PT:t_trace,DPT:t_trace).
entry_points_find(I,P,CT,T,PT,DPT) :-
    ext_rel_inst_trace(I,P,CT,T,_,rel_alias{_,PT,DPT}).
entry_points_find(I,P,CT,T,PT,DPT) :-
    ext_rel_inst_trace(I,P,CT,T,_,rel_alias{XCT,_,_}),
    entry_points_find(I,P,XCT,T,PT,DPT).
get_display_item(_,_,_,asn_entry{P,T,CT0,CT1,_},ITEM) :-
    isum(P,_,I), sum_body(SUM,P),
    (entry_points_find(I,P,CT0,T,PT,DPT);
     entry_points_find(I,P,CT1,T,PT,DPT)),
    entry_points_item(SUM,PT,DPT,ITEM).

% add any relevant per-sum side effects
predicate exit_points_link(in SUM:sum,in S:t_trace,in T:t_trace,
                           DNAME:string,LINK:string).
exit_points_link(s_loop{PH},S,T,DNAME,"link") :-
    cil_curfn(FN),
    spoints_display_name(td_points{FN,s_loop{PH},fn_exit},S,T,DNAME).
exit_points_link(s_call{I},S,T,DNAME,LINK) :-
    anycall(I,FN,_), sum_exit(FN,s_func)->spoints(S,T),
    spoints_display_name(td_points{FN,s_func,fn_exit},S,T,DNAME),
    cleanup_glob_string(FN,LINK).
get_path_item(_,_,_,ASN,P,PP,ITEM) :-
    PP\=P, isum(PP,_,I),
    (I=s_call{_}, inst_exit_points(I,CS,CT);
     I=s_loop{_}, add_spoints(td_points{_,I,fn_exit},CS,CT)),
    point_location(PP,_,LINE),
    inst_trace(I,PP,CS,trace{S},SG), asn_guard(ASN,SG),
    inst_trace(I,PP,CT,trace{T},TG), asn_guard(ASN,TG),
    dstring_sum(I,ISTR), dstring_trace(I,S,SSTR), dstring_trace(I,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR," after ",ISTR],TEXT),
    \/exit_points_link(I,CS,CT,DNAME,LINK):list_all(d_link{DNAME,LINK},LINKS),
    ITEM=d_line_text{LINE,"patheffect",d_bottom,TEXT,LINKS}.

% global spoints invariants for exit aliasing
get_path_item(_,S,T,_,P,PP,ITEM) :-
    sum_bound(SUM,_,P),
    lval_point(LV,PP), lval(PP,LV,GS,_), trace_root(GS,glob{_}),
    glob_trace_rename(drf{GS},GT), ~trace_simplify(SUM,drf{GS},GT),
    (trace_sub(S,GT,_); trace_sub(T,GT,_)),
    entry_points_item(SUM,GS,GT,ITEM).

% renaming of malloc results for exit aliasing
get_path_item(_,_,_,_,P,PP,ITEM) :-
    sum_bound(SUM,_,P), icall(PP,_,I), point_location(PP,_,LINE),
    callret(I,R), T=root{R},
    trace_type(SUM,T,y_ptr{_}), ~inst_exit_points(s_call{I},root{return},_),
    filter_rename(SUM,fn_exit,drf{T},NDT,_),
    ~weak_filter_rename(SUM,fn_exit,drf{T},NDT), ~trace_root(NDT,temp{_,_}),
    dstring_trace(SUM,drf{T},DTSTR), dstring_trace(SUM,NDT,NDTSTR),
    str_cat_list([DTSTR," is merged with ",NDTSTR," at exit"],TEXT),
    ITEM=d_line_text{LINE,"pathrename",d_bottom,TEXT,[]}.

% add the actual points-to relationship covered by the assignment
get_display_item(_,S,T,asn_exit{P,_},ITEM) :-
    point_location(P,_,LINE), sum_body(SUM,P),
    dstring_trace(SUM,S,SSTR), dstring_trace(SUM,T,TSTR),
    str_cat_list([SSTR," may point to ",TSTR],TEXT),
    ITEM=d_line_text{LINE,"pathtext",d_bottom,TEXT,[]}.
get_display_item(_,S,T,asn_entry{P,PT,_,_,_},ITEM) :-
    point_location(P,_,LINE), sum_body(SUM,P), isum(P,_,I),
    dstring_sum(I,ISTR), dstring_trace(SUM,PT,PTSTR),
    dstring_trace(I,drf{S},CT0STR), dstring_trace(I,T,CT1STR),
    str_cat_list([ISTR," may access ",PTSTR," through both ",
                  CT0STR," and ",CT1STR],TEXT),
    ITEM=d_line_text{LINE,"pathtext",d_bottom,TEXT,[]}.

% add displays for generated spoints

predicate get_asn_line(in ASN:t_points_asn,out LINE:int).
get_asn_line(asn_exit{P,_},LINE) :-
    sum_body(SUM,P), sum_location(SUM,_,LINE).
get_asn_line(asn_entry{P,_,_,_,_},LINE) :-
    sum_body(SUM,P), sum_location(SUM,_,LINE).
get_asn_line(asn_none{SUM},LINE) :-
    sum_location(SUM,_,LINE).

% only generate a single display for each points-to relationship discovered,
% even if there are many corresponding TGT/S/T/ASN
type t_sd_item ::= sd_item{t_points_target,t_trace,t_trace,t_points_asn}.
predicate base_spoints_display(TGT:t_points_target,S:t_trace,T:t_trace,
                               ASN:t_points_asn).
add_spoints_display(TGT,S,T,ASN), spoints_display_name(TGT,S,T,DNAME),
    \/(add_spoints_display(XTGT,XS,XT,XASN),
       spoints_display_name(XTGT,XS,XT,DNAME))
     :list_all(sd_item{XTGT,XS,XT,XASN},[sd_item{TGT,S,T,ASN}|_]),
    +base_spoints_display(TGT,S,T,ASN).

curfn_location(FS,FILE,MINLINE,MAXLINE),
    base_spoints_display(TGT,S,T,ASN), spoints_display_name(TGT,S,T,DNAME),
    \/get_display_item(TGT,S,T,ASN,AITEM):list_all(AITEM,AITEMS),
    index_item(IITEM),
    asn_sum(ASN,SUM), sum_location(SUM,_,LINE),
    spoints_display_title(TGT,S,T,TITLE),
    +display_add(DNAME,false,"alias_why",TITLE,FS,FILE,MINLINE,MAXLINE,LINE,
        [IITEM,d_line_text{LINE,"aliasadd",d_top,TITLE,[]}|AITEMS]).

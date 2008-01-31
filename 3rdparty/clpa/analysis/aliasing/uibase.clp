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

% common UI code for alias analysis

using display.
import "../memory/traces.clp".

% spoints displays

% get the UI display name/title for showing why add_spoints(TGT,S,T) was added
predicate spoints_display_name(in G:t_points_target,in S:t_trace,in T:t_trace,
                               DNAME:string).
predicate spoints_display_title(in G:t_points_target,in S:t_trace,in T:t_trace,
                                DTITLE:string).

% get the name for a display just by stringifying the component parts.
% watch composites to make sure we get a canonical name
spoints_display_name(td_points{FN,SUM,POS},S,T,DNAME) :-
    tostring(SUM,SUMS), tostring(POS,POSS), tostring(S,SS), tostring(T,TS),
    str_cat_list(["points_",FN,"_",SUMS,"_",POSS,"_",SS,"_",TS],DNAME).
spoints_display_name(td_comp_points{C,STR},S,T,DNAME) :-
    comp_to_relative(STR,S,RS), comp_to_relative(STR,T,RT),
    tostring(RS,RSS), tostring(RT,RTS),
    str_cat_list(["points_",C,"_",RSS,"_",RTS],DNAME).
spoints_display_name(td_glob_points{G},S,T,DNAME) :-
    tostring(S,SS), tostring(T,TS),
    str_cat_list(["points_",G,"_",SS,"_",TS],DNAME).

spoints_display_title(td_points{FN,SUM,POS},S,T,TITLE) :-
    (cil_curfn(FN), NSUM=SUM; ~cil_curfn(FN), anycall(I,FN,_), NSUM=s_call{I}),
    dstring_trace(NSUM,S,SSTR), dstring_trace(NSUM,T,TSTR),
    (cil_curfn(FN), dstring_sum(SUM,SUMSTR);
     ~cil_curfn(FN), SUM=s_func, cleanup_glob_string(FN,SUMSTR)),
    (POS=fn_entry, WHERE=" at entry to ";
     POS=fn_exit, WHERE=" at exit from "),
    str_cat_list([SSTR," may point to ",TSTR,WHERE,SUMSTR],TITLE).
spoints_display_title(td_comp_points{C,STR},S,T,TITLE) :-
    comp_to_relative(STR,S,RS), comp_to_relative(STR,T,RT),
    dstring_trace(s_func,RS,SSTR), dstring_trace(s_func,RT,TSTR),
    str_cat_list([SSTR," may generally point to ",TSTR," in ",C],TITLE).
spoints_display_title(td_glob_points{_},S,T,TITLE) :-
    dstring_trace(s_func,S,SSTR), dstring_trace(s_func,T,TSTR),
    str_cat_list([SSTR," may generally point to ",TSTR],TITLE).

% usemod displays

% get the UI display name/title for usemod information on globals and types
predicate scwrite_display_name(in C:string,in F:string,
                               DNAME:string,DTITLE:string).
predicate sgwrite_display_name(in G:string,
                               DNAME:string,DTITLE:string).

scwrite_display_name(C,F,DNAME,DTITLE) :-
    str_cat_list(["usemod_comp_",C,"_",F],DNAME),
    str_cat_list(["Field ",F," of type ",C," may be written through"],DTITLE).
sgwrite_display_name(G,DNAME,DTITLE) :-
    cleanup_glob_string(G,GS),
    str_cat_list(["usemod_glob_",G],DNAME),
    str_cat_list(["Global ",GS," may be written to"],DTITLE).

% funptr displays

predicate indirect_display_name(in FN:string,in I:c_instr,in CFN:string,
                                DNAME:string,DTITLE:string).
indirect_display_name(FN,I,CFN,DNAME,DTITLE) :-
    tostring(I,IS), dstring_sum(s_call{I},ISTR),
    cleanup_glob_string(CFN,CFNS),
    str_cat_list(["funptr_",FN,"_",IS,"_",CFN],DNAME),
    str_cat_list([ISTR," may call ",CFNS],DTITLE).

% per-function indexing displays

predicate index_body_display_name(in FN:string,in SUM:sum,
                                  DNAME:string,TITLE:string).
index_body_display_name(FN,SUM,DNAME,TITLE) :-
    tostring(SUM,SUMS),
    (SUM=s_loop{_}, dstring_sum(SUM,SUMSTR);
     SUM\=s_loop{_}, cleanup_glob_string(FN,SUMSTR)),
    str_cat_list(["alias_bodyset_",FN,"_",SUMS],DNAME),
    str_cat("Entry and exit aliasing for ",SUMSTR,TITLE).

predicate index_body_indircall_display_name(in FN:string,in I:c_instr,
                                            DNAME:string,TITLE:string).
index_body_indircall_display_name(FN,I,DNAME,TITLE) :-
    tostring(I,IS), dstring_sum(s_call{I},ISTR),
    str_cat_list(["alias_indirset_",FN,"_",IS],DNAME),
    str_cat("Indirect targets for ",ISTR,TITLE).

predicate index_body_callers_display_name(in FN:string,
                                          DNAME:string,TITLE:string).
index_body_callers_display_name(FN,DNAME,TITLE) :-
    cleanup_glob_string(FN,FS),
    str_cat_list(["alias_callerset_",FN],DNAME),
    str_cat("Callers of ",FS,TITLE).

predicate index_body_globtypes_display_name(in FN:string,
                                            DNAME:string,TITLE:string).
index_body_globtypes_display_name(FN,DNAME,TITLE) :-
    cleanup_glob_string(FN,FS),
    str_cat_list(["alias_body_globtypeset_",FN],DNAME),
    str_cat("Global types/variables used by ",FS,TITLE).

% per-global indexing displays

predicate index_glob_display_name(in G:string,
                                  DNAME:string,TITLE:string).
index_glob_display_name(G,DNAME,TITLE) :-
    cleanup_glob_string(G,GS),
    str_cat("alias_globset_",G,DNAME),
    str_cat("Global invariant aliasing for ",GS,TITLE).

predicate index_glob_globtypes_display_name(in G:string,
                                            DNAME:string,TITLE:string).
index_glob_globtypes_display_name(G,DNAME,TITLE) :-
    cleanup_glob_string(G,GS),
    str_cat_list(["alias_glob_globtypeset_",G],DNAME),
    str_cat("Global types/variables used by ",GS,TITLE).

% per-type indexing displays

predicate index_comp_display_name(in C:string,
                                  DNAME:string,TITLE:string).
index_comp_display_name(C,DNAME,TITLE) :-
    str_cat("alias_compset_",C,DNAME),
    str_cat("Type invariant aliasing for ",C,TITLE).

predicate index_comp_globtypes_display_name(in C:string,
                                            DNAME:string,TITLE:string).
index_comp_globtypes_display_name(C,DNAME,TITLE) :-
    str_cat_list(["alias_comp_globtypeset_",C],DNAME),
    str_cat("Global types/variables used by ",C,TITLE).

% items

% item to add a link to the current function's entry/exit aliasing display
predicate index_item(ITEM:displayitem).
cil_curfn(FN), sum_location(s_func,_,LINE),
    index_body_display_name(FN,s_func,DNAME,TITLE),
    +index_item(
        d_line_text{LINE,"bodyparent",d_top,TITLE,[d_link{DNAME,"link"}]}).

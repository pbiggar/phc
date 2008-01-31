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

% Generate displays for use in UI justifying various memory.clp assertions

import "memory.clp".

using display.

% PREDICATES

predicate get_val_display(in P:pp,in ASN:g_guard_asn,
                          in T:t_trace,in V:t_trace_val,
                          out DISPLAY:string).

% RULES

% stringify trace values

% get a string for the integer value of a trace_val, or '*' if none exists
% (i.e. intignore.clp is being used)
predicate asn_value_str(in ASN:g_guard_asn,in V:t_trace_val,STR:string).
asn_value_str(ASN,V,STR) :- asn_value(ASN,V,N), tostring(N,STR).
asn_value_str(ASN,V,"*") :- ~asn_value(ASN,V,_).

% convert a trace value to a UI string according to the given assignment
predicate asn_dstring_trace_val(in ASN:g_guard_asn,in V:t_trace_val,STR:string).

asn_dstring_trace_val(ASN,trace{drf{T}},STR) :-
    trace_type(s_func,T,y_int{_}),
    asn_value_str(ASN,trace{drf{T}},NSTR),
    dstring_trace(s_func,T,TSTR), str_cat4(TSTR," [",NSTR,"]",STR).

asn_dstring_trace_val(ASN,trace{drf{T}},STR) :-
    ~trace_type(s_func,T,y_int{_}), dstring_trace(s_func,T,STR).

asn_dstring_trace_val(ASN,trace{T},STR) :-
    T\=drf{_}, dstring_trace(s_func,T,TSTR), str_cat("&",TSTR,STR).

asn_dstring_trace_val(ASN,nrep{NR},STR) :- asn_value_str(ASN,nrep{NR},STR).

% program point links

predicate point_link(in P:pp,in ASN:g_guard_asn,LINK:displaylink).

point_link(P,ASN,d_link{DISP,TXT}) :-
    lval_point(LV,P), cil_lval_mem(LV,ME,_), cil_exp_lval(ME,MLV),
    lval(P,MLV,MT,MLG), asn_guard(ASN,MLG),
    val(P,MT,MV,MVG), asn_guard(ASN,MVG),
    trace_simplify(s_func,drf{MT},EXPT), MV\=trace{EXPT},
    exp_string(ME,MESTR),
    dstring_trace(s_func,MT,MTSTR), asn_dstring_trace_val(ASN,MV,MVSTR),
    str_cat_list(["\"",MESTR,"\" references ",MTSTR," with value ",MVSTR],TXT),
    get_val_display(P,ASN,MT,MV,DISP).

% program point events

type val_track = t_pair[t_trace,t_trace_val].

predicate exp_track(in P:pp,in ASN:g_guard_asn,
                    in E:c_exp,in V:t_trace_val,
                    out NTV:val_track).
exp_track(P,ASN,E,V,pair{T,V}) :-
    cil_exp_lval(E,LV), lval(P,LV,T,LG), asn_guard(ASN,LG),
    val(P,T,V,VG), asn_guard(ASN,VG).

predicate maybe_exp_track(in P:pp,in ASN:g_guard_asn,
                          in E:c_exp,in V:t_trace_val,
                          out NTV:maybe[val_track]).
maybe_exp_track(P,ASN,E,V,yes{NTV}) :- exp_track(P,ASN,E,V,NTV).
maybe_exp_track(P,ASN,E,V,no) :- ~exp_track(P,ASN,E,V,_).

predicate valid_track(in P:pp,in ASN:g_guard_asn,in TV:val_track).
valid_track(P,ASN,pair{T,V}) :- val(P,T,V,G), asn_guard(ASN,G).

predicate point_event(in P:pp,in ASN:g_guard_asn,in TV:val_track,
                      out EVENT:displayitem,out NTV:maybe[val_track]).

predicate direct_assign(in P:pp,in ASN:g_guard_asn,in TV:val_track,
                        out NTV:maybe[val_track]).
direct_assign(P,ASN,pair{T,V},NTV) :-
    iset(P,AP,I), guard(AP,AG), asn_guard(ASN,AG), cil_instr_set(I,LV,E),
    lval(P,LV,T,LG), asn_guard(ASN,LG),
    eval(P,E,V,EG), asn_guard(ASN,EG), maybe_exp_track(P,ASN,E,V,NTV).

point_event(P,ASN,pair{T,V},EVENT,NTV) :-
    direct_assign(P,ASN,pair{T,V},NTV),
    dstring_trace(s_func,T,TSTR), asn_dstring_trace_val(ASN,V,VSTR),
    str_cat_list([TSTR," is assigned value ",VSTR],TEXT),
    point_location(P,_,LINE), \/point_link(P,ASN,LINK):list_all(LINK,LINKS),
    EVENT = d_line_text{LINE,"pathevent_text",d_right,TEXT,LINKS}.

point_event(P,ASN,pair{T,V},EVENT,no) :-
    ~valid_track(P,ASN,pair{T,V}), ~direct_assign(P,ASN,pair{T,V},_),
    dstring_trace(s_func,T,TSTR), asn_dstring_trace_val(ASN,V,VSTR),
    str_cat_list(["unknown assign to ",TSTR," with value ",VSTR],TEXT),
    point_location(P,_,LINE),
    EVENT = d_line_text{LINE,"pathevent_text",d_right,TEXT,[]}.

% generate the EVENTS on RPATH leading to T pointing to V
predicate path_val_events(in RPATH:list[pp],in ASN:g_guard_asn,in TV:val_track,
                          EVENTS:list[displayitem]).

path_val_events([P|RTAIL],ASN,TV,[E|EVENTS]) :-
    point_event(P,ASN,TV,E,yes{NTV}), path_val_events(RTAIL,ASN,NTV,EVENTS).
path_val_events([P|RTAIL],ASN,TV,[E]) :-
    point_event(P,ASN,TV,E,no).
path_val_events([P|RTAIL],ASN,TV,EVENTS) :-
    ~point_event(P,ASN,TV,_,_), path_val_events(RTAIL,ASN,TV,EVENTS).
+path_val_events([],_,_,[]).

% val displays

cil_curfn(FN), ?get_val_display(P,ASN,T,V,_), tostring(P,PSTR),
    dstring_trace(s_func,T,TSTR), asn_dstring_trace_val(ASN,V,VSTR),
    str_cat_list(["memoryval_",FN,"_",PSTR,"_",TSTR,"_",VSTR],DISPLAY),
    +get_val_display(P,ASN,T,V,DISPLAY),
    asn_path(P,ASN,[],PATH), list_reverse(PATH,RPATH),
    path_val_events(RPATH,ASN,pair{T,V},EVENTS),
    \/(list_mem(PATH,PP), point_location(PP,_,PLINE)):
        list_all(d_line_style{PLINE,"pathline"},PITEMS),
    list_append(EVENTS,PITEMS,ITEMS),
    curfn_location(FS,FILE,MINLINE,MAXLINE),
    point_location(P,_,LINE), tostring(LINE,LS),
    str_cat_list([TSTR," has value ",VSTR," at line ",LS],TITLE),
    +display_add(DISPLAY,false,"memoryval",TITLE,FS,FILE,MINLINE,MAXLINE,LINE,ITEMS).

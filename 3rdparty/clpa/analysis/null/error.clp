%%
% Authors:
%   Isil Dillig    <isil@stanford.edu>
%   Thomas Dillig  <tdillig@stanford.edu>
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

% Error reporting tool using module error and lines.clp

using error.
using display.
import "./lines.clp".
import "../base/utility.clp".



type deref_location_type ::= deref_location{NAME:string, LINE:int, FILE:string}.


predicate report_error(P:pp, CSSCLASS:string, MSG:string, TYPE:string).
predicate report_error_callstack (P:pp, CSSCLASS:string, MSG:string, TYPE:string, CALLSTACK:list[deref_location_type]).
predicate report_error_check (P:pp, CSSCLASS:string, MSG:string, TYPE:string, CHECK:list[int]).
predicate report_error_check_callstack (P:pp, CSSCLASS:string, MSG:string, TYPE:string, GLS:list[string], 
	CHECK:list[int], CALLSTACK:list[deref_location_type]).

predicate report_error_check_macro (P:pp, CSSCLASS:string, MSG:string, TYPE:string, CHECK:list[int], MC:list[string]).


% note: this rule only exports a subset of the power of error2html, but
% for most reasonable cases it's a little easier and shorter to use
% then error_message directly.
report_error(P, _, MSG, TYPE), source_line(P, LINE), source_file(P, FILE),
  +error_message("red", LINE, "red", MSG, FILE, TYPE, "None").

report_error_check(P, _, MSG, TYPE,CHECK), source_line(P, LINE), source_file(P, FILE),
  +error_message_check("orange", LINE, "orange", MSG, FILE, TYPE, "None", CHECK).

report_error_callstack(P, _, MSG, TYPE, CALLSTACK), source_line(P, LINE), source_file(P, FILE),
  +error_message_list("blue", LINE, "blue", MSG, FILE, TYPE, "None", CALLSTACK).

report_error_check_callstack(P, _, MSG, TYPE, GLS, CHECK, CALLSTACK), source_line(P, LINE), source_file(P, FILE),
  +error_message_check_callstack("violet", LINE, "violet", MSG, FILE, TYPE, "None", GLS, CHECK, CALLSTACK).

report_error_check_macro(P, _, MSG, TYPE,CHECK,MC), source_line(P, LINE), source_file(P, FILE),
  +error_message_check_macro("violet", LINE, "violet", MSG, FILE, TYPE, "None", CHECK,MC).



%----------------------------------------------------------------------------------


predicate string_of_derefs(in CALLSTACK:list[deref_location_type], RES:string).
predicate deref_to_string(in DL:deref_location_type, RES:string).
predicate unify_derefs(CALLSTACK: list[deref_location_type], DL: string).

deref_to_string(deref_location{NAME, LINE, FILE}, RESULT) :-
	tostring(LINE, LINE_STR), 
	str_cat5(NAME, " (", LINE_STR, FILE, ")", RESULT).

?string_of_derefs(CALLSTACK, _), list_mem(CALLSTACK, DEREF_LOC), 
	deref_to_string(DEREF_LOC, DEREF_STR), 
	+unify_derefs(CALLSTACK, DEREF_STR).

unify_derefs(CALLSTACK, _), \/unify_derefs(CALLSTACK, DEREF):list_all(DEREF, DEREF_LIST),
	str_cat_list(DEREF_LIST, RES), +string_of_derefs(CALLSTACK, RES).

%--------------------------------------------------------------
predicate funsum_ui(F:string, D:displayitem).

% Add all summary info to a display
cil_curfn(F), deref_ui(cons{deref_location{FUNC, LINE, _}, _}, T, NC),
	equal(F, FUNC), trace_string(T, ST), guard_string(NC, SNC),
	str_cat5("[Summary] Derefereces ", ST, " under condition ", SNC, ".", MSG),
	+funsum_ui(F, d_line_style{LINE, "warning_red"}),
	+funsum_ui(F, d_line_text{LINE, "summary_text", d_top, MSG,[]}).

cil_curfn(F), deref_ui(cons{deref_location{FUNC, LINE, _}, cons{deref_location{FUNC1, _, FILE1}, _}}, T, NC),
	~equal(F, FUNC), trace_string(T, ST), guard_string(NC, SNC),
	str_cat4("[Summary] Indirectly derefereces ", ST, " under condition ", SNC,  MSG1),
	str_cat(MSG1, " through call to ", MSG),
	str_cat3(FUNC1, ":", FILE1, DISPLAY_NAME),
	+funsum_ui(F, d_line_style{LINE, "warning_red"}), 
	+funsum_ui(F, d_line_text{LINE, "id_summary_text", d_top, MSG,
		[d_link{DISPLAY_NAME, FUNC1}]}).

% collect all funsum_ui's and make a display out of them.
cil_curfn(F),  \/funsum_ui(F, DI):list_all(DI, DI_LIST),
curfn_location(FUNC,FILE,MIN,MAX), 
str_cat3(FUNC, ":", FILE, DISPLAY_NAME),
+display_add(DISPLAY_NAME,false,"Dereference Summary",DISPLAY_NAME, FUNC, FILE, MIN,MAX, MIN,
                     DI_LIST).

%---------------------------------------------------
%Actual error displays

%cil_curfn(F), deref_ui(cons{deref_location{FUNC, LINE, FILE}, _}, T, NC),
%~equal(F, FUNC),
% +print("Indirect Edge", F, T, NC, FUNC, LINE, FILE).


report_error(P, CSSCLASS, MSG, TYPE), source_line(P, LINE), source_file(P, FILE),
	counter(N), tostring(N, NS), source_loc(P, LOC), str_cat(NS, LOC, DISPLAY),
	curfn_location(FS,FILE,MIN,MAX),
	+display_add(DISPLAY,false,TYPE,"NULL error", FS, FILE, MIN,MAX, LINE,
                     [d_line_style{LINE, CSSCLASS}, d_line_text{LINE, "warning_text", d_top, MSG,[]}]).

  


report_error_check(P, CSSCLASS, MSG, TYPE, cons{HD, _}),
	counter(N), tostring(N, NS), source_loc(P, LOC), source_line(P, LINE), 
	str_cat(NS, LOC, DISPLAY),
	curfn_location(FS,FILE,MIN,MAX),
	+display_add(DISPLAY,false,TYPE,"NULL error", FS, FILE, MIN,MAX, LINE,
          [d_line_style{HD,"nullevent"}, d_line_style{LINE, CSSCLASS}, 
	  d_line_text{LINE,"warning_text", d_top, MSG,[]},
	d_line_text{HD,"warning_text", d_top, "Variable checked for NULL here",[]}]).



report_error_callstack(P, CSSCLASS, MSG, TYPE, cons{deref_location{FUNC1, _, FILE1}, _}), 
	source_line(P, LINE), source_file(P, FILE), 
	counter(N), tostring(N, NS), source_loc(P, LOC), str_cat(NS, LOC, DISPLAY), 
	curfn_location(FS,FILE,MIN,MAX),
	%string_of_derefs(CALLSTACK, CALL_STR),
	str_cat(MSG, " dereferenced through ", MSG2),
	str_cat3(FUNC1, ":", FILE1, DISPLAY_NAME),
	
	+display_add(DISPLAY,false,TYPE,"NULL error", FS, FILE, MIN,MAX, LINE,
                [d_line_style{LINE,CSSCLASS}, 
		d_line_text{LINE, "warning_text", d_top, MSG2,	[d_link{DISPLAY_NAME, FUNC1}]}]).





report_error_check_callstack(P, CSSCLASS, MSG, TYPE, cons{GLS_HD, _}, cons{HD, _},  
	cons{deref_location{FUNC1, _, FILE1}, _}),
	source_line(P, LINE), source_file(P, FILE),
	counter(N), tostring(N, NS), source_loc(P, LOC), source_line(P, LINE), 
	str_cat(NS, LOC, DISPLAY), curfn_location(FS,FILE,MIN,MAX),
	str_cat4(MSG, " with ", GLS_HD, " derferenced through ", MSG2), 
	str_cat3(FUNC1, ":", FILE1, DISPLAY_NAME),

	+display_add(DISPLAY,false,TYPE,"NULL error", FS, FILE, MIN,MAX, LINE,
                     [d_line_style{HD,"nullevent"}, d_line_style{LINE, CSSCLASS}, d_line_text{LINE, "warning_text", d_top, MSG2,
	[d_link{DISPLAY_NAME, FUNC1}]},
  d_line_text{HD,"warning_text", d_top, "Variable checked for NULL here",[]}
]).


report_error_check_macro(P, CSSCLASS, MSG, TYPE,cons{HD, _},MC), source_line(P, LINE), source_file(P, FILE),
	counter(N), tostring(N, NS), source_loc(P, LOC), source_line(P, LINE), str_cat(NS, LOC, DISPLAY),
	curfn_location(FS,FILE,MIN,MAX),
	str_cat_list(MC, MC_STR), str_cat3(MSG, " derferenced in macro(s) ", MC_STR, MSG2), 
	+display_add(DISPLAY,false,TYPE,"NULL error", FS, FILE, MIN,MAX, LINE,
                     [d_line_style{HD,"nullevent"}, d_line_style{LINE, CSSCLASS}, d_line_text{LINE, "warning_text", d_top, MSG2,[]}]).


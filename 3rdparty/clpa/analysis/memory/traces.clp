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

% canonical memory representation and interprocedural points-to information

% location traces are canonical representations of memory locations accessed by
% a function or loop, to be used when summarizing the function/loop etc.
% each trace is either a root R, typically an argument or global, or
% the offset of a trace drf{T} (initial target of the location at T)
% or fld{T,F} (field F of the location at T)

import "../base/cilbase.clp".
import "../base/utility.clp".
using intops.

% root stack/static locations
type t_root ::=
    arg{A:int}       % argument number A
  | glob{G:string}   % global variable G
  | local{L:string}  % local variable L (used intraprocedurally)
  | return           % the return value
  | call_target      % the trace for the (direct/indirect) target invoking
                     % this function
  | temp{TMP:string,WHERE:string}
                     % CIL temporary TMP with usage description WHERE.
                     % if representing a call return value then drf{temp{TMP}}
                     % represents any fresh data returned through the call
  | asm_in{A:int}    % numbered input argument to inline assembly
  | asm_out{A:int}   % numbered output argument to inline assembly
  | cstr{string}     % a constant string (treated as read-only global data)
  .

% lightweight trace type representation
type t_type ::=
    y_void
  | y_int{ikind}
  | y_flt{fkind}
  | y_ptr{t_type}
  | y_array{t_type,int}
  | y_func
  | y_comp{string}
  | y_enum{string}
  | y_valist.

% possible ways to index a soft trace. left abstract within this file
type t_trace_index.

% client-defined trace extension
type t_xtrace.

% canonical representations of locations used by the program
type t_trace ::=
    root{R:t_root}  % root trace for the stack/static location of R
  | empty           % empty trace, only for pure location offsets
  | drf{T:t_trace}  % the initial result of dereferencing T
  | fld{T:t_trace,F:string,C:string}   % field F of T
  | rfld{T:t_trace,F:string,C:string}  % reverse field F of T
  | index{T:t_trace,I:t_trace_index}   % index I of soft trace T
  | xtrace{X:t_xtrace}  % client-defined trace extension
  .

% TRACE PREDICATES

% CIL variable X has root R
predicate var_trace(X:c_var,R:t_root).

% the return value of call I is assigned to (temp{_}) root trace R
predicate callret(I:c_instr,R:t_root).

% NT is a simplified version of OT, as interpreted by loop/call SUM,
% removing any type recursion or other redundancy
predicate trace_simplify(in SUM:sum,in OT:t_trace,NT:t_trace) succeeds [once].

% trace T is rooted at R
predicate trace_root(in T:t_trace,R:t_root) succeeds [zero,once].

% trace T is relative and has no root
predicate trace_relative(in T:t_trace).

% trace T includes N dereferences
predicate trace_derefs(in T:t_trace,N:int) succeeds [once].

% kinds of ways in which traces can be allocated. each trace has one allocation
type t_alloc_kind ::=
    ak_external     % allocated externally from SUM 
  | ak_stack_local  % stack-allocated within the body of SUM
  | ak_heap_local.  % heap-allocated by a call within the body of SUM

% get the allocation kind of a trace
predicate trace_alloc(in SUM:sum,in T:t_trace,K:t_alloc_kind).

% T0 and T1 compose into trace TR. T1 must have an empty root
% SUM will be used for simplifying TR
predicate trace_compose(in SUM:sum,in T0:t_trace,in T1:t_trace,TR:t_trace)
    succeeds [once].

% get TR such that TS composes with TR into T
predicate trace_sub(in T:t_trace,TS:t_trace,TR:t_trace) succeeds [many].

% TS/TR form a trace_sub of T within the same structure (i.e. no dereferences)
predicate trace_fld_sub(in T:t_trace,TS:t_trace,TR:t_trace) succeeds [many].

% generalize a trace T containing index{} focusing to the base trace BT
predicate trace_strip_index(in T:t_trace,BT:t_trace) succeeds [once].

% strip all outer fld constructors from T
predicate trace_strip_flds(in T:t_trace,BT:t_trace) succeeds [once].

% TRACE TYPE PREDICATES

% as interpreted by function body/loop/call SUM, the memory location referred 
% to by T has type TYP
predicate trace_type(in SUM:sum,in T:t_trace,Y:t_type).

% type for each created temporary
predicate temp_type(T:string,Y:t_type).

% convert regular CIL types to the t_type representation
predicate convert_type(in TYP:c_type,Y:t_type) succeeds [once].

% convert_type operating on composite type C or global G
predicate convert_comp_type(in C:string,in TYP:c_type,Y:t_type)
    succeeds [once].
predicate convert_glob_type(in G:string,in TYP:c_type,Y:t_type)
    succeeds [once].

% get the width of a type, in bytes
predicate type_width(in Y:t_type,BS:int) succeeds [once].

% TRACE PRINTING PREDICATES

% convert traces to a more readable string representation
% NOTE: not defined in this file for index{} traces
predicate trace_string(in t_trace,string) succeeds [once].

% convert a trace to a UI string. similar to trace_string except that
% '->' operation is generated, and argument numbers are converted to names
% (except when SUM is a call).
% NOTE: not defined in this file for index{} traces
predicate dstring_trace(in SUM:sum,in T:t_trace,STR:string) succeeds [once].

% convert a summary to a UI string
predicate dstring_sum(in sum,string) succeeds [once].

% USEMOD SUMMARIES

% per-func/loop usemod information
session sum_usemod(FN:string,SUM:sum) containing [stuse,sanyuse,stalloc,stsoft].

% type usemod information
session sum_usemod_comp(C:string) containing [scwrite,stsoft].

% global usemod information
session sum_usemod_glob(G:string) containing [sgwrite,sganyuse,stsoft].

% sum_usemod: usemod summary information for a particular trace T
type access_type ::=
    read        % direct read on T
  | write       % direct write on T
  | deepread    % read on data reachable from T (but not T)
  | deepwrite.  % write on data reachable from T (but not T)
predicate stuse(T:t_trace,AT:access_type).

% sum_usemod: this function may read or write to any global as according to the
% sganyuse predicates in that global's summary
predicate sanyuse().

% sum_usemod_glob: any function with sanyuse in its usemond summary may read
% or write to the contents of this global according to Y
predicate sganyuse(Y:access_type).

% sum_usemod: per-trace allocation information. T is written with a freshly
% allocated value in this func/loop
predicate stalloc(T:t_trace).

% sum_usemod/sum_usemod_comp/sum_usemod_glob: T may represent multiple
% physical locations. note that 'array' and 'softsub' soft traces are not
% represented explicitly in the summary
type soft_type ::=
    array     % explicit array type
  | ptarray   % pointer target used as an array (pointer used in arithmetic)
  | recurse   % recursive structure that has been traversed
  | softsub.  % has a subtrace which itself is soft
predicate stsoft(T:t_trace,ST:soft_type).

% sum_usemod_comp: deepwrites may be performed through field F of the current
% composite type
predicate scwrite(F:string).

% sum_usemod_glob: the static contents of the current global may be written
% at some point in the program other than during static initialization
predicate sgwrite().

% ALIASING SUMMARIES

% per-func/loop entry aliasing
session sum_entry(FN:string,SUM:sum) containing [spoints]. 

% per-func/loop exit side effects
session sum_exit(FN:string,SUM:sum) containing [spoints,sunify].

% type invariant aliasing for C
session sum_comp(C:string) containing [spoints,sxpoints].

% global invariant aliasing for G
session sum_glob(G:string) containing [spoints,sxpoints].

% sum_entry/sum_exit/sum_comp/sum_glob: points-to summary information.
% trace S may point to trace T. for sum_comp, S and possibly T have
% empty roots, in which case they indicate offsets from the composite itself
% for sum_glob, ALL possible S->T edges are included, even S->drf{S} if added
predicate spoints(S:t_trace,T:t_trace).
predicate sxpoints(S:t_trace,T:t_trace).

% sum_exit: summary unification information for freshly allocated data.
% replace OT with NT in the exit graph
predicate sunify(OT:t_trace,NT:t_trace).

% function pointer trace FT relative to this comp may be passed
% target of trace T (also relative to this comp) through argument trace AT
session poly_comp(C:string) containing [spoly].
predicate spoly(FT:t_trace,T:t_trace,AT:t_trace).

% rename OT to NT in the exit points-to graph of SUM. if OT was not allocated
% within this function/loop, it will be renamed to itself. otherwise, it will
% be renamed according to sunify() summary preds. the renaming will not hold
% if OT is not reachable at exit from any externally visible data
predicate exit_trace_rename(in SUM:sum,in OT:t_trace,NT:t_trace).

% rename OT to NT, replacing access paths on globals with the actual global
% location. if OT is not a global trace, it will be renamed to itself.
% otherwise each dereference on a global pointer will be replaced with
% the targets of that global pointer listed by sum_glob->spoints (which may
% generate multiple actual locations)
predicate glob_trace_rename(in OT:t_trace,NT:t_trace).

% keep track of which global pointers have been dereferenced via
% glob_trace_rename, and must have targets in sum_glob. run aliasingcheck.clp
% after aliasing.clp has been computed to verify all used global pointers were
% written at some point (otherwise the program may be open).
session sum_glob_must(G:string) containing [must_spoints].
predicate must_spoints(S:t_trace).

% session containing just the points-to edges derived from static initializers
session sum_glob_init(G:string) containing [sxpoints].

% GENERAL SUMMARY INFO

% convert a trace T (non-empty root) to another trace RT relative to STR
% (with a possibly empty root), if possible
predicate comp_to_relative(in STR:t_trace,in T:t_trace,RT:t_trace).

% convert a relative trace RT (possibly-empty root) in a composite invariant
% on STR to a trace T (non-empty root)
predicate comp_from_relative(in STR:t_trace,in RT:t_trace,T:t_trace).

% per-isum summary info from usemod and aliasing
predicate inst_usemod(I:sum,T:t_trace,Y:access_type).
predicate inst_anyuse(I:sum).
predicate inst_exit_points(I:sum,S:t_trace,T:t_trace).

% trace T may be accessed by SUM as either 'read' or 'write'
predicate inst_may_access(in SUM:sum,in T:t_trace,AT:access_type).

% trace T is soft within SUM
predicate trace_soft(in SUM:sum,in T:t_trace,ST:soft_type).

% UPDATING SUMMARIES

% points within the function to generate aliasing information at
type point_pos ::= fn_entry | fn_exit.

% where a particular points-to edge may be attached
type t_points_target ::=
    td_points{FN:string,SUM:sum,POS:point_pos}
  | td_comp_points{C:string,STR:t_trace}
  | td_glob_points{G:string}.

% add a particular spoints(S,T) on TGT
predicate add_spoints(TGT:t_points_target,S:t_trace,T:t_trace).

% marginally more readable summary information, generated for add_*_spoints
predicate str_spoints(FN:string,SUM:sum,POS:point_pos,SS:string,TS:string).
predicate str_comp_spoints(C:string,SS:string,TS:string).
predicate str_glob_spoints(G:string,SS:string,TS:string).

% CUSTOMIZATION

% trace_simplify() will not simplify (apparent) recursive trace T in SUM
predicate omit_trace_recurse(in SUM:sum,in T:t_trace).

%+omit_trace_recurse(_,_).

% glob_trace_rename() will not rename T
predicate omit_glob_trace_rename(in T:t_trace).

% RULES

% trace inspection/manipulation

+trace_compose(_,T,empty,T).
trace_compose(SUM,T0,drf{PT1},TR) :-
    trace_compose(SUM,T0,PT1,PTR), trace_simplify(SUM,drf{PTR},TR).
trace_compose(SUM,T0,fld{FT1,F,C},TR) :-
    trace_compose(SUM,T0,FT1,FTR), trace_simplify(SUM,fld{FTR,F,C},TR).
trace_compose(SUM,T0,rfld{FT1,F,C},TR) :-
    trace_compose(SUM,T0,FT1,FTR), trace_simplify(SUM,rfld{FTR,F,C},TR).
trace_compose(SUM,T0,index{IT1,I},TR) :-
    trace_compose(SUM,T0,IT1,ITR), trace_simplify(SUM,index{ITR,I},TR).

+trace_sub(T,T,empty).
trace_sub(drf{T},TS,drf{TR}) :- trace_sub(T,TS,TR).
trace_sub(fld{T,F,C},TS,fld{TR,F,C}) :- trace_sub(T,TS,TR).
trace_sub(rfld{T,F,C},TS,rfld{TR,F,C}) :- trace_sub(T,TS,TR).
trace_sub(index{T,I},TS,index{TR,I}) :- trace_sub(T,TS,TR).

% get trace derefs
+trace_derefs(root{_},0), +trace_derefs(empty,0).
trace_derefs(drf{T},N) :- trace_derefs(T,SN), int_add(SN,1,N).
trace_derefs(fld{T,_,_},N) :- trace_derefs(T,N).
trace_derefs(rfld{T,_,_},N) :- trace_derefs(T,N).
trace_derefs(index{T,_},N) :- trace_derefs(T,N).

trace_fld_sub(T0,T1,TR) :- trace_sub(T0,T1,TR), trace_derefs(TR,0).

% variable traces

cil_fundec_formal(_,A,X), +var_trace(X,arg{A}).
cil_var_global(X), cil_var_name(X,G,_), +var_trace(X,glob{G}).
cil_var_static(X), cil_var_name(X,G,_), +var_trace(X,glob{G}).
cil_var_local(X),  cil_var_name(X,L,_), +var_trace(X,local{L}).
cil_var_return(X), +var_trace(X,return).

% get the terms for each temporary. if the temporary is a call return value,
% form a tuple with the callee or instruction for identifying purposes
cil_var_temporary(X), callretvar(I,X),
    cil_instr_call(I,E), exp_string(E,ES),
    cil_var_name(X,T,TYP), convert_type(TYP,Y),
    +var_trace(X,temp{T,ES}), +temp_type(T,Y).
cil_var_temporary(X), ~callretvar(_,X),
    cil_var_name(X,T,TYP), convert_type(TYP,Y),
    +var_trace(X,temp{T,"op"}), +temp_type(T,Y).

% get returned traces for calls
callretvar(I,X), var_trace(X,R), +callret(I,R).

% type conversion

cil_type_void(TYP), +convert_type(TYP,y_void).
cil_type_int(TYP,K), +convert_type(TYP,y_int{K}).
cil_type_float(TYP,K), +convert_type(TYP,y_flt{K}).
cil_type_ptr(TYP,DTYP), convert_type(DTYP,DY),
    +convert_type(TYP,y_ptr{DY}).
cil_type_array(TYP,ETYP,LEN), cil_exp_x_intval(LEN,N), convert_type(ETYP,EY),
    +convert_type(TYP,y_array{EY,N}).
cil_type_func(TYP,_,_), +convert_type(TYP,y_func).
cil_type_comp(TYP,C), +convert_type(TYP,y_comp{C}).
cil_type_enum(TYP,E), +convert_type(TYP,y_enum{E}).
cil_type_valist(TYP), +convert_type(TYP,y_valist).
cil_type_named(TYP, _, NTYP), convert_type(NTYP, Y), +convert_type(TYP, Y).

convert_comp_type(C,TYP,y_void) :- cil_comp(C)->cil_type_void(TYP).
convert_comp_type(C,TYP,y_int{K}) :- cil_comp(C)->cil_type_int(TYP,K).
convert_comp_type(C,TYP,y_flt{K}) :- cil_comp(C)->cil_type_float(TYP,K).
convert_comp_type(C,TYP,y_ptr{DY}) :- 
    cil_comp(C)->cil_type_ptr(TYP,DTYP), convert_comp_type(C,DTYP,DY).
convert_comp_type(C,TYP,y_array{EY,N}) :- 
    cil_comp(C)->cil_type_array(TYP,ETYP,LEN),
    cil_comp(C)->cil_exp_x_intval(LEN,N),
    convert_comp_type(C,ETYP,EY).
convert_comp_type(C,TYP,y_func) :- cil_comp(C)->cil_type_func(TYP,_,_).
convert_comp_type(C,TYP,y_comp{DC}) :- cil_comp(C)->cil_type_comp(TYP,DC).
convert_comp_type(C,TYP,y_enum{E}) :- cil_comp(C)->cil_type_enum(TYP,E).
convert_comp_type(C,TYP,y_valist) :- cil_comp(C)->cil_type_valist(TYP).
convert_comp_type(C,TYP,Y) :- 
    cil_comp(C)->cil_type_named(TYP,_,ATYP),
    convert_comp_type(C,ATYP,Y).

convert_glob_type(G,TYP,y_void) :- cil_glob(G)->cil_type_void(TYP).
convert_glob_type(G,TYP,y_int{K}) :- cil_glob(G)->cil_type_int(TYP,K).
convert_glob_type(G,TYP,y_flt{K}) :- cil_glob(G)->cil_type_float(TYP,K).
convert_glob_type(G,TYP,y_ptr{DY}) :- 
    cil_glob(G)->cil_type_ptr(TYP,DTYP),convert_glob_type(G,DTYP,DY).
convert_glob_type(G,TYP,y_array{EY,N}) :- 
    cil_glob(G)->cil_type_array(TYP,ETYP,LEN),
    cil_glob(G)->cil_exp_x_intval(LEN,N),
    convert_glob_type(G,ETYP,EY).
convert_glob_type(G,TYP,y_func) :- cil_glob(G)->cil_type_func(TYP,_,_).
convert_glob_type(G,TYP,y_comp{C}) :- cil_glob(G)->cil_type_comp(TYP,C).
convert_glob_type(G,TYP,y_enum{E}) :- cil_glob(G)->cil_type_enum(TYP,E).
convert_glob_type(G,TYP,y_valist) :- cil_glob(G)->cil_type_valist(TYP).
convert_glob_type(G,TYP,Y) :-
    cil_glob(G)->cil_type_named(TYP,_,ATYP),
    convert_glob_type(G,ATYP,Y).

% handy predicate to get the numbered field of a comp
predicate comp_field(in C:string,N:int,BS:int,F:string,Y:t_type).
comp_field(C,N,BS,F,Y) :-
    cil_comp(C)->cil_comp_name(COMP,C,_),
    cil_comp(C)->cil_comp_field(COMP,N,FLD),
    cil_comp(C)->cil_field_name(FLD,F,TYP,BS,_), convert_comp_type(C,TYP,Y).

% type widths

+type_width(y_void,1).
type_width(y_int{K},BS) :- ikind_bytes(K,_,BS).
type_width(y_enum{_},BS) :- ikind_bytes(iint,_,BS).
type_width(y_flt{K},BS) :- fkind_bytes(K,BS).
type_width(y_ptr{_},BS) :- pointer_bytes(BS).
type_width(y_array{Y,N},BS) :- type_width(Y,YBS), int_mul(YBS,N,BS).
type_width(y_comp{C},BS) :- cil_comp(C)->cil_comp_bytes(_,BS).

% hack for code bases that don't have cil_comp_bytes
type_width(y_comp{C},BS) :- ~cil_comp(C)->cil_comp_bytes(_,_),
    cil_type_comp(TYP,C), cil_type_x_bytes(TYP,BS).

% trace types

% argument types
trace_type(s_call{I},root{arg{AN}},Y) :-
    cil_instr_call(I,FNE), exp_type(FNE,FNT),
    cil_type_func_arg(FNT,AN,_,TYP), convert_type(TYP,Y).
trace_type(SUM,root{arg{AN}},Y) :-
    (SUM=s_func; SUM=s_loop{_}), cil_fundec_formal(_,AN,X),
    cil_var_name(X,_,TYP), convert_type(TYP,Y).
trace_type(s_asm{I},root{asm_in{AN}},Y) :-
    cil_instr_asm_in(I,AN,_,_,E), exp_type(E,TYP), convert_type(TYP,Y).
trace_type(s_asm{I},root{asm_out{AN}},Y) :-
    cil_instr_asm_out(I,AN,_,_,LV), lval_type(LV,TYP), convert_type(TYP,Y).

% return value types
trace_type(s_call{I},root{return},Y) :-
    cil_instr_call(I,FNE), exp_type(FNE,FNT),
    cil_type_func(FNT,TYP,_), convert_type(TYP,Y).
trace_type(SUM,root{return},Y) :-
    (SUM=s_func; SUM=s_loop{_}), cil_var_return(X),
    cil_var_name(X,_,TYP), convert_type(TYP,Y).

% call pointer types
+trace_type(_,root{call_target},y_func).

% global types. we need to load the global information into this session.
% if there is no global information assume this is a function (HACK)
trace_type(SUM,root{glob{G}},Y) :-
    cil_glob(G)->cil_var_name(_,G,TYP), convert_glob_type(G,TYP,Y).
trace_type(SUM,root{glob{G}},y_func) :-
    ~cil_glob(G)->cil_var_name(_,G,_).

% constant strings are character arrays
trace_type(_,root{cstr{STR}},y_array{y_int{ichar},LEN}) :-
    str_len(STR,ZPOS), int_add(ZPOS,1,LEN).

% local/temporary types, for function and loops
trace_type(SUM,root{local{L}},Y) :-
    (SUM=s_func; SUM=s_loop{_}), cil_var_name(_,L,TYP), convert_type(TYP,Y).
trace_type(SUM,root{temp{T,_}},Y) :-
    (SUM=s_func; SUM=s_loop{_}), temp_type(T,Y).

% compute drf/fld/rfld trace types, loading composite info if required
trace_type(SUM,drf{T},DY) :- trace_type(SUM,T,y_ptr{DY}).
trace_type(SUM,fld{T,F,C},FY) :-
    cil_comp(C)->cil_field_name(FLD,F,FTYP,_,_),
    cil_comp(C)->cil_comp_field(COMP,_,FLD),
    cil_comp(C)->cil_comp_name(COMP,C,_),
    convert_comp_type(C,FTYP,FY).
+trace_type(_,rfld{_,_,C},y_comp{C}).

% indexes don't change the trace type
trace_type(SUM,index{T,_},Y) :- trace_type(SUM,T,Y).

% generate both the array and elem type for arrays
trace_type(SUM,T,EY) :- trace_type(SUM,T,y_array{EY,_}).

% trace cast checking

% C has a value of type Y at offset zero, with FLIST field chain to reach Y.
% split cases based on whether C is a union type, where every field is at
% offset zero
predicate first_field(in C:string,Y:t_type,FLIST:list[t_pair[string,string]]).

first_field(C,Y,[pair{F,C}]) :- cil_comp(C)->cil_comp_name(_,_,ISSTRUCT),
    (ISSTRUCT=true, comp_field(C,0,_,F,Y);
     ISSTRUCT=false, comp_field(C,_,_,F,Y)).

first_field(C,Y,[pair{F,C}|FLIST]) :- cil_comp(C)->cil_comp_name(_,_,ISSTRUCT),
    (ISSTRUCT=true, comp_field(C,0,_,F,y_comp{NC});
     ISSTRUCT=false, comp_field(C,_,_,F,y_comp{NC})),
    first_field(NC,Y,FLIST).

predicate check_cast(in OY:t_type,in NY:t_type).
+check_cast(Y,Y).
+check_cast(y_void,_), +check_cast(_,y_void).
check_cast(y_array{Y0,_},Y1) :- check_cast(Y0,Y1).
check_cast(Y0,y_array{Y1,_}) :- check_cast(Y0,Y1).
check_cast(y_ptr{Y0},y_ptr{Y1}) :- check_cast(Y0,Y1).
check_cast(y_comp{C},Y) :- first_field(C,Y,_).
check_cast(Y,y_comp{C}) :- first_field(C,Y,_).

predicate trace_bad_cast(in SUM:sum,in T:t_trace).
trace_bad_cast(SUM,T) :- trace_sub(T,fld{ST,_,C},_),
    trace_type(SUM,ST,Y), ~check_cast(y_comp{C},Y),
    Y\=y_void, ~type_width(Y,1).  % casts for void*/char*/uchar*
trace_bad_cast(SUM,T) :- trace_sub(T,rfld{ST,F,C},_),
    cil_comp(C)->cil_field_name(_,F,TYP,_,_), convert_comp_type(C,TYP,Y),
    trace_type(SUM,ST,SY), ~check_cast(SY,Y).

% trace simplification

% RT is a recursive trace for its own subtrace T. simplify RT to NT
predicate trace_recurse(in SUM:sum,in RT:t_trace,in T:t_trace,NT:t_trace).

% look for identical types on the two traces
trace_recurse(SUM,RT,T,T) :-
    RT=drf{_}, trace_type(SUM,RT,Y), trace_type(SUM,T,Y),
    Y\=y_int{_}, Y\=y_ptr{y_int{_}}, Y\=y_void, Y\=y_ptr{y_void}.

% for traces we can't type accurately due to casts from void*
+trace_recurse(_,drf{fld{_,F,C}},drf{fld{T,F,C}},drf{fld{T,F,C}}).
+trace_recurse(_,drf{drf{drf{drf{T}}}},drf{drf{drf{T}}},drf{drf{drf{T}}}).

% for weird cases walking arrays of the same type of element
trace_recurse(_,fld{BT,F,C},fld{T,F,C},fld{T,F,C}) :- trace_fld_sub(BT,T,_).
trace_recurse(_,rfld{BT,F,C},rfld{T,F,C},rfld{T,F,C}) :- trace_fld_sub(BT,T,_).

% one simplification step simplifies OT to NT
predicate trace_one_simplify(in SUM:sum,in OT:t_trace,NT:t_trace).

% simplify recursive traces, making sure we don't remove any leading index
% or change the trace's allocation kind
trace_one_simplify(SUM,RT,NT) :-
    ~omit_trace_recurse(SUM,RT), trace_alloc(SUM,RT,K),
    trace_sub(RT,T,_), T\=RT, ~trace_sub(RT,index{T,_},_),
    trace_alloc(SUM,T,K), trace_recurse(SUM,RT,T,NT).

% simplify fld{rfld{T,F},F} and rfld{fld{T,F},F} to T
+trace_one_simplify(_,fld{rfld{T,F,C},F,C},T).
+trace_one_simplify(_,rfld{fld{T,F,C},F,C},T).

% simplify traces by (recursively) applying simplifications
trace_simplify(I,OT,NT) :-
    trace_one_simplify(I,OT,T),
    ~(trace_one_simplify(I,OT,XT), XT\=T, trace_sub(T,XT,_)),
    trace_simplify(I,T,NT).
trace_simplify(I,OT,OT) :- ~trace_one_simplify(I,OT,_).

% trace roots and kinds

% get trace roots
+trace_root(root{R},R).
trace_root(drf{T},R) :- trace_root(T,R).
trace_root(fld{T,_,_},R) :- trace_root(T,R).
trace_root(rfld{T,_,_},R) :- trace_root(T,R).
trace_root(index{T,_},R) :- trace_root(T,R).

% get relative traces
trace_relative(T) :- ~trace_root(T,_).

predicate trace_alloc_root(in SUM:sum,in R:t_root,
                          NODRF_KIND:t_alloc_kind,DRF_KIND:t_alloc_kind).
trace_alloc(SUM,T,K) :-
    SUM\=s_call{_}, trace_root(T,R), trace_derefs(T,N),
    (N=0, trace_alloc_root(SUM,R,K,_);
     N\=0, trace_alloc_root(SUM,R,_,K)).
trace_alloc(s_call{_},T,K) :- trace_alloc(s_func,T,K).

% data reachable from global variables were always allocated externally
+trace_alloc_root(_,glob{_},ak_external,ak_external).

% constant strings are always visible
+trace_alloc_root(_,cstr{_},ak_external,ak_external).

% data originating from locals and stack arguments were allocated external
% to a loop invocation
+trace_alloc_root(s_loop{_},arg{_},ak_external,ak_external).
+trace_alloc_root(s_loop{_},local{_},ak_external,ak_external).

% as arguments are passed by value, only non-root data originating from
% arguments were allocated external to the function itself
+trace_alloc_root(s_func,arg{_},ak_stack_local,ak_external).
+trace_alloc_root(s_func,local{_},ak_stack_local,ak_heap_local).

% consider the return value and call target as passed by reference
+trace_alloc_root(_,return,ak_external,ak_external).
+trace_alloc_root(_,call_target,ak_external,ak_external).

% temporaries are always stack local
+trace_alloc_root(_,temp{_,_},ak_stack_local,ak_heap_local).

% input/output arguments to assembly are always treated as visible
+trace_alloc_root(s_asm{_},asm_in{_},ak_external,ak_external).
+trace_alloc_root(s_asm{_},asm_out{_},ak_external,ak_external).

% removing indexes

+trace_strip_index(empty,empty).
+trace_strip_index(root{R},root{R}).
trace_strip_index(drf{T},drf{BT}) :- trace_strip_index(T,BT).
trace_strip_index(fld{T,F,C},fld{BT,F,C}) :- trace_strip_index(T,BT).
trace_strip_index(rfld{T,F,C},rfld{BT,F,C}) :- trace_strip_index(T,BT).
trace_strip_index(index{T,_},BT) :- trace_strip_index(T,BT).

% removing outer fields

trace_strip_flds(fld{T1,_,_},T2) :- trace_strip_flds(T1,T2).
trace_strip_flds(T,T) :- T \= fld{_,_,_}.

% stringifying

% stringify root traces
trace_string(root{arg{A}},S) :- tostring(A,AS), str_cat("__arg",AS,S).
trace_string(root{asm_in{A}},S) :- tostring(A,AS), str_cat("__asmin",AS,S).
trace_string(root{asm_out{A}},S) :- tostring(A,AS), str_cat("__asmout",AS,S).
+trace_string(root{glob{G}},G).
+trace_string(root{local{L}},L).
trace_string(root{cstr{S}},SV) :- str_cat3("\"",S,"\"",SV).
trace_string(root{temp{T,W}},S) :- str_cat("tmp.",W,S).
+trace_string(root{return},"return").
+trace_string(root{call_target},"calltgt").
+trace_string(empty,"").

% stringify offset traces
trace_string(drf{PT},S) :- trace_string(PT,PS), str_cat(PS,"*",S).
trace_string(fld{FT,F,_},S) :- trace_string(FT,FS), str_cat3(FS,".",F,S).
trace_string(rfld{FT,F,_},S) :- trace_string(FT,FS), str_cat3(FS,"^",F,S).

% user interface stringifying

dstring_trace(SUM,root{arg{A}},N) :-
    SUM\=s_call{_}, cil_fundec_formal(_,A,X), cil_var_name(X,N,_).
dstring_trace(SUM,root{arg{A}},N) :-
    SUM\=s_call{_}, ~cil_fundec_formal(_,A,_), tostring(A,AS), str_cat("__arg",AS,N).
dstring_trace(s_call{_},root{arg{A}},N) :- tostring(A,AS), str_cat("__arg",AS,N).
dstring_trace(_,root{asm_in{A}},S) :- trace_string(root{asm_in{A}},S).
dstring_trace(_,root{asm_out{A}},S) :- trace_string(root{asm_out{A}},S).
dstring_trace(_,root{glob{G}},S) :- cleanup_glob_string(G,S).
+dstring_trace(_,root{local{L}},L).
dstring_trace(_,root{cstr{S}},QS) :- str_cat3("\"",S,"\"",QS).
dstring_trace(_,root{temp{T,W}},S) :- str_cat("tmp.",W,S).
+dstring_trace(_,root{return},"return").
+dstring_trace(_,root{call_target},"calltgt").
+dstring_trace(_,empty,"this").

dstring_trace(SUM,drf{PT},S) :- dstring_trace(SUM,PT,PS), str_cat("*",PS,S).
dstring_trace(SUM,fld{drf{FT},F,_},S) :- dstring_trace(SUM,FT,FS), str_cat3(FS,"->",F,S).
dstring_trace(SUM,fld{FT,F,_},S) :-
    FT\=drf{_}, dstring_trace(SUM,FT,FS), str_cat3(FS,".",F,S).
dstring_trace(SUM,rfld{FT,F,_},S) :- dstring_trace(SUM,FT,FS), str_cat3(FS,"^",F,S).

dstring_sum(s_func,STR) :-
    cil_curfn(FN), cleanup_glob_string(FN,STR).
dstring_sum(s_loop{PH},STR) :-
    cil_stmt_x_location(PH,_,LINE), tostring(LINE,LS), str_cat("loop:",LS,STR).
dstring_sum(s_call{I},STR) :-
    cil_instr_x_location(I,_,LINE), tostring(LINE,LS),
    cil_instr_call(I,E), exp_string(E,ES),
    str_cat_list(["call:",LS,":",ES],STR).
dstring_sum(s_asm{I},STR) :-
    cil_instr_x_location(I,_,LINE), tostring(LINE,LS),
    str_cat("asm:",LS,STR).

% converting traces from/to composite-relative traces

comp_from_relative(STR,RT,T) :-
    trace_relative(RT), trace_compose(s_func,STR,RT,T).
comp_from_relative(STR,RT,RT) :- ~trace_relative(RT).
comp_to_relative(STR,T,RT) :- trace_sub(T,STR,RT).
comp_to_relative(STR,T,T) :- ~trace_sub(T,STR,_), trace_root(T,glob{_}).
comp_to_relative(rfld{STR,F,C},T,RT) :- comp_to_relative(STR,T,RXT),
    trace_relative(RXT), trace_compose(s_func,fld{empty,F,C},RXT,RT).

% soft traces

% traces with type array are soft
trace_soft(SUM,T,array) :-
    trace_type(SUM,T,y_array{_,_}), T\=index{_,_}.

% traces with soft subtraces are soft, excepting index traces
trace_soft(SUM,T,softsub) :-
    trace_type(SUM,T,_), trace_sub(T,OT,RT), T\=OT, trace_soft(SUM,OT,_),
    ~trace_sub(RT,index{_,_},_).

% soft traces from comp/glob usemod info
trace_soft(SUM,T,ST) :-
    trace_type(SUM,T,_), T\=index{_,_}, trace_strip_index(T,BT),
    trace_sub(BT,fld{STR,_,C},_), comp_to_relative(STR,BT,RT),
    sum_usemod_comp(C)->stsoft(RT,ST).
trace_soft(SUM,T,ST) :-
    trace_type(SUM,T,_), T\=index{_,_}, trace_strip_index(T,BT),
    trace_root(BT,glob{G}), sum_usemod_glob(G)->stsoft(BT,ST).

% soft traces from summary specific usemod info. need to be able to turn this
% off when generating this info to avoid dependency cycles
predicate omit_trace_soft_summary().
trace_soft(SUM,T,ST) :- ~omit_trace_soft_summary(), SUM\=s_call{_},
    trace_type(SUM,T,_), T\=index{_,_}, trace_strip_index(T,BT),
    cil_curfn(FN), sum_usemod(FN,SUM)->stsoft(BT,ST).
trace_soft(s_call{I},T,ST) :- ~omit_trace_soft_summary(),
    trace_type(s_call{I},T,_), T\=index{_,_}, trace_strip_index(T,BT),
    anycall(I,FN,_), sum_usemod(FN,s_func)->stsoft(BT,ST).

% trace renaming

% traces that were not malloc'ed in this frame do not get renamed
exit_trace_rename(SUM,T,T) :- ~trace_alloc(SUM,T,ak_heap_local).

predicate exit_unify(in SUM:sum,in T:t_trace,NT:t_trace).
exit_unify(SUM,T,NT) :- cil_curfn(FN), sum_exit(FN,SUM)->sunify(T,NT).

% for fresh traces, compose with the summarized renaming on any subtrace.
% due to aliasing along multiple levels of a structure at exit there may
% be multiple renamings. pick the one closest to the given trace
exit_trace_rename(SUM,T,NT) :- trace_alloc(SUM,T,ak_heap_local),
    trace_sub(T,ST,RT), exit_unify(SUM,ST,NST),
    ~(trace_sub(T,CST,_), ST\=CST, trace_sub(CST,ST,_), exit_unify(SUM,CST,_)),
    trace_compose(SUM,NST,RT,NT).

predicate sub_glob_trace_rename(in OT:t_trace,NT:t_trace).
+sub_glob_trace_rename(root{R},root{R}).
sub_glob_trace_rename(drf{PT},NT) :-
    trace_type(s_func,PT,y_ptr{_}),
    glob_trace_rename(PT,NPT), trace_root(NPT,glob{G}),
    +sum_glob_must(G)->must_spoints(NPT), sum_glob(G)->sxpoints(NPT,NT).
sub_glob_trace_rename(drf{PT},NT) :-
    trace_sub(PT,fld{STR,_,C},_), comp_to_relative(STR,PT,RPT),
    sum_comp(C)->sxpoints(RPT,RDPT), comp_from_relative(STR,RDPT,DPT),
    sub_glob_trace_rename(DPT,NT).
sub_glob_trace_rename(fld{FT,F,C},NT) :-
    glob_trace_rename(FT,NFT), trace_simplify(s_func,fld{NFT,F,C},NT).
sub_glob_trace_rename(rfld{FT,F,C},NT) :-
    glob_trace_rename(FT,NFT), trace_simplify(s_func,rfld{NFT,F,C},NT).
sub_glob_trace_rename(index{IT,I},NT) :-
    glob_trace_rename(IT,NIT), trace_simplify(s_func,index{NIT,I},NT).

glob_trace_rename(T,T) :- ~trace_root(T,glob{_}).
glob_trace_rename(T,NT) :- trace_root(T,glob{_}),
    ~omit_glob_trace_rename(T), sub_glob_trace_rename(T,NT).

% summary information generation

predicate use_glob_spoints(in T:t_trace).
use_glob_spoints(T) :- ~trace_fld_sub(T,root{glob{_}},_).
use_glob_spoints(T) :- trace_fld_sub(T,root{glob{G}},_),
    ~trace_type(s_func,T,y_func), sum_usemod_glob(G)->sgwrite().

add_spoints(td_points{FN,SUM,POS},S,T),
    (POS=fn_entry, +sum_entry(FN,SUM)->spoints(S,T);
     POS=fn_exit, +sum_exit(FN,SUM)->spoints(S,T)),
    trace_string(S,SS), trace_string(T,TS), +str_spoints(FN,SUM,POS,SS,TS).

add_spoints(td_comp_points{C,STR},S,T),
    comp_to_relative(STR,S,RS), comp_to_relative(STR,T,RT),
    +sum_comp(C)->sxpoints(RS,RT),
    (trace_relative(RT); use_glob_spoints(RT)), +sum_comp(C)->spoints(RS,RT),
    trace_string(RS,SS), trace_string(RT,TS), +str_comp_spoints(C,SS,TS).

add_spoints(td_glob_points{G},S,T),
    +sum_glob(G)->sxpoints(S,T),
    use_glob_spoints(T), +sum_glob(G)->spoints(S,T),
    trace_string(S,SS), trace_string(T,TS), +str_glob_spoints(G,SS,TS).

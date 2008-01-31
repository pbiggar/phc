%%
% Authors:
%   Brian Hackett  <bhackett@stanford.edu>
%   Peter Hawkins  <hawkinsp@cs.stanford.edu>
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

% Useful abstractions and short-cuts for CIL constructs

using translatecil.
using strops.
using intops.

% PREDICATES

% the type of machine we are to simulate. this affects the size and
% signedness of the various integer and floating point types. default is i386.
% if you want a different machine kind, add the declaration:
% +machine(x86_64).
type machine_kind ::=
    i386
  | x86_64.
predicate machine(machine_kind).

predicate ikind_bytes(ikind,bool,int).  % sign and byte size for an ikind
predicate ikind_bits(ikind,bool,int).   % sign and number of bits for an ikind
predicate fkind_bytes(fkind,int).       % byte size for an fkind
predicate fkind_bits(fkind,int).        % number of bits for an fkind
predicate pointer_bytes(int).           % byte size for a pointer 
predicate pointer_bits(int).            % number of bits for a pointer 

% sign/length for an int/flt/ptr type. pointers are unsigned, floats are signed
predicate type_bits(c_type,bool,int).

predicate lval_type(c_lval,c_type).     % lval -> type
predicate exp_type(c_exp,c_type).       % exp -> type
predicate off_type(c_offset,c_type).    % off -> type
predicate base_off_type(c_offset,c_type).  % get the base type for an offset

predicate exp_tptr(c_exp).        % pointer exps
predicate exp_tint(c_exp,ikind).  % integer exps
predicate exp_tflt(c_exp,fkind).  % floating point exps

% for lvalues with a trailing field, get that field and the containing COMP
predicate lval_field(c_lval,c_field,COMP:string).

% classify variables beyond the existing cil_var_global
% These predicates are declared but not inferred in the translatecil package.
% predicate cil_var_formal(X:c_var).
% predicate cil_var_local(X:c_var).
% predicate cil_var_temporary(X:c_var).
% predicate cil_var_return(X:c_var).

% get the full set of statements and instructions in the function
predicate cil_stmt(S:c_stmt).
predicate cil_instr(I:c_instr).

% I is a direct call to FN
predicate dircall(I:c_instr,FN:string).

% I is either a direct call to FN or an indirect call which *could* target FN
type calltype ::= direct | indirect.
predicate anycall(I:c_instr,FN:string,T:calltype).

% I is a call assigning to temporary X
predicate callretvar(I:c_instr,X:c_var).

% classify each operation
predicate logic_op(binop).        % boolean args, boolean result
predicate compare_op(binop).      % integer args, boolean result
predicate arith_op(binop).        % integer args, integer result
predicate pointer_op(binop).      % pointer LHS, integer RHS, pointer result
predicate pointer_int_op(binop).  % pointer args, integer result

% T0 and T1 are equivalent types
predicate type_alias(in T0:c_type,in T1:c_type).

% call instruction I implicitly casts its result to a value of type T
predicate call_cast(I:c_instr,T:c_type).

% identify loops in a function. we just identify these based on the
% corresponding CIL statement, either a native loop or the target of a goto
type loop = c_stmt.

% locations we commonly attach summary information to
type sum ::=
    s_func           % the current function
  | s_loop{loop}     % a particular loop in the current function
  | s_call{c_instr}  % a call instruction
  | s_asm{c_instr}   % an assembly instruction
  .

% loops in this function body
predicate loophead(loop).

% stringifying and output

predicate lval_string(c_lval,string).
predicate off_string(c_offset,string).
predicate exp_string(c_exp,string).
predicate type_string(c_type,string).
predicate location_string(in FILE:string,in LINE:int,string).

% clean up a global function or variable name, removing any 'static' variable
% uniquification /path/to/file.c:
predicate cleanup_glob_string(in G:string,GSTR:string).

% SUM is at FILE/LINE
predicate sum_location(in SUM:sum,FILE:string,LINE:int) succeeds [once].

% UI location information for types, globals, and the current function.
% get an appropriate MINL and MAXL for use in generating a display,
% and for the current function get the cleaned up function name FS
predicate comp_location(in C:string,FILE:string,MINL:int,MAXL:int) succeeds [once].
predicate glob_location(in G:string,FILE:string,MINL:int,MAXL:int) succeeds [once].
predicate func_location(in FN:string,FILE:string,MINL:int,MAXL:int) succeeds [once].

predicate curfn_location(FS:string,FILE:string,MINL:int,MAXL:int).
cil_curfn(FN), cleanup_glob_string(FN,FS), func_location(FN,FILE,MINL,MAXL),
    +curfn_location(FS,FILE,MINL,MAXL).

% SUMBODY SESSIONS

% session containing only the CFG for a particular loop or outer function body,
% as well as all the regular predicates in cil_body. SUM is s_func or s_loop.
% constructed by sumbody.clp
session cil_sum_body(FN:string,SUM:sum).

% the sum we are currently analyzing. this predicate is ONLY defined
% if iterating over the cil_sum_body session.
predicate cil_cursum(sum).

% shorthand for 'cil_curfn(FN), cil_cursum(SUM)', fetches both for cil_sum_body
predicate cursum(FN:string,SUM:sum).
cil_curfn(FN), cil_cursum(SUM), +cursum(FN,SUM).

% INDIRECT CALL SESSIONS

% indirect call target session
session sum_funptr(FN:string) containing [sindirect].
predicate sindirect(I:c_instr,CFN:string).  % call I to possible callee CFN

% add to update summaries
predicate add_sindirect(I:c_instr,CFN:string).

predicate omit_call_edge(in string, in c_instr, in string).

% readable version of indirect calls, generated for add_sindirect
predicate str_indirect(FN:string,CALL:string,CFN:string).
cil_curfn(FN), add_sindirect(I,CFN), +sum_funptr(FN)->sindirect(I,CFN),
    cil_instr_call(I,E), exp_string(E,CALL), +str_indirect(FN,CALL,CFN).

cil_curfn(CURFN), dircall(I,F), ~omit_call_edge(CURFN, I, F),
	+anycall(I,F,direct).
cil_curfn(CURFN), sum_funptr(CURFN)->sindirect(I,F), 
	~omit_call_edge(CURFN, I, F), +anycall(I,F,indirect).

% RULES

% cil modifications

% short circuit all TNamed type aliases. if NT is a named type equal to T,
% replace NT with T in any relations (keeping the old relation around)
predicate rep_type(NT:c_type,T:c_type).
cil_type_named(NT,_,T), +rep_type(NT,T).
rep_type(NT,T), cil_type_ptr(PT,NT), +cil_type_ptr(PT,T).
rep_type(NT,T), cil_type_array(AT,NT,E), +cil_type_array(AT,T,E).
rep_type(NT,T), cil_type_func(F,NT,VA), +cil_type_func(F,T,VA).
rep_type(NT,T), cil_type_func_arg(F,N,S,NT), +cil_type_func_arg(F,N,S,T).
rep_type(NT,T), cil_type_named(NNT,S,NT), +cil_type_named(NNT,S,T).
rep_type(NT,T), cil_field_name(F,S,NT,SN,WN), +cil_field_name(F,S,T,SN,WN).
rep_type(NT,T), cil_var_name(X,S,NT), +cil_var_name(X,S,T).
rep_type(NT,T), cil_init_cmpnd_type(I,NT), +cil_init_cmpnd_type(I,T).
rep_type(NT,T), cil_exp_sizeof(E,NT), +cil_exp_sizeof(E,T).
rep_type(NT,T), cil_exp_alignof(E,NT), +cil_exp_alignof(E,T).
rep_type(NT,T), cil_exp_unop(E,O,R,NT), +cil_exp_unop(E,O,R,T).
rep_type(NT,T), cil_exp_binop(E,O,L,R,NT), +cil_exp_binop(E,O,L,R,T).
rep_type(NT,T), cil_exp_cast(E,CE,NT), +cil_exp_cast(E,CE,T).

% each cil_exp_start(E,LV) is equivalent to cil_exp_addr(E,LV[0]),
% make the conversion painful though it is
predicate want_convert_start_addr(OFF:c_offset).
predicate convert_start_addr(OFF:c_offset,NOFF:c_offset).
want_convert_start_addr(OFF),
    cil_off_none(OFF),
    cil_make_const(OFF,"cvtcst",C), +cil_const_int(C,iint,0),
    cil_make_exp(OFF,"cvtexp",E), +cil_exp_const(E,C), +cil_exp_x_intval(E,0),
    cil_make_offset(OFF,"empoff",EOFF), +cil_off_none(EOFF),
    cil_make_offset(OFF,"cvtoff",NOFF), +cil_off_index(NOFF,E,EOFF),
    +convert_start_addr(OFF,NOFF).
want_convert_start_addr(OFF),
    cil_off_field(OFF,F,FOFF),
    +want_convert_start_addr(FOFF),
    convert_start_addr(FOFF,NFOFF),
    cil_make_offset(OFF,"cvtoff",NOFF), +cil_off_field(NOFF,F,NFOFF),
    +convert_start_addr(OFF,NOFF).
want_convert_start_addr(OFF),
    cil_off_index(OFF,E,IOFF),
    +want_convert_start_addr(IOFF), convert_start_addr(IOFF,NIOFF),
    cil_make_offset(OFF,"cvtoff",NOFF), +cil_off_index(NOFF,E,NIOFF),
    +convert_start_addr(OFF,NOFF).
cil_exp_start(E,LV), cil_lval_var(LV,X,OFF), +want_convert_start_addr(OFF),
    convert_start_addr(OFF,NOFF), cil_make_lval(LV,"cvtlv",NLV),
    +cil_lval_var(NLV,X,NOFF), +cil_exp_addr(E,NLV).
cil_exp_start(E,LV), cil_lval_mem(LV,ME,OFF), +want_convert_start_addr(OFF),
    convert_start_addr(OFF,NOFF), cil_make_lval(LV,"cvtlv",NLV),
    +cil_lval_mem(NLV,ME,NOFF), +cil_exp_addr(E,NLV).

% convert all 'index' pointer arithmetic operations into 'plus' operations,
% which are equivalent
cil_exp_binop(E,b_indexpi,L,R,T), +cil_exp_binop(E,b_pluspi,L,R,T).

% we don't replace sizeof/alignof's with const expressions. these should be
% manually handled by client analyses. check for such non-const exps though
predicate cil_exp_x_sizeof_alignof(c_exp).
cil_exp_sizeof(E,_), +cil_exp_x_sizeof_alignof(E).
cil_exp_sizeofe(E,_), +cil_exp_x_sizeof_alignof(E).
cil_exp_sizeofstr(E,_), +cil_exp_x_sizeof_alignof(E).
cil_exp_alignof(E,_), +cil_exp_x_sizeof_alignof(E).
cil_exp_alignofe(E,_), +cil_exp_x_sizeof_alignof(E).

cil_exp_x_sizeof_alignof(E), ~cil_exp_x_intval(E,_),
    +warning("non-const sizeof/alignof exp",E).

% add temporary/local opflags to non-argument non-static locals
cil_fundec_formal(_,_,X), +cil_var_formal(X).
cil_fundec_local(_,X), cil_var_name(X,NAME,_), str_cat("ciltmp",_,NAME),
    +cil_var_temporary(X).
cil_fundec_local(_,X), ~cil_var_temporary(X), ~cil_var_static(X),
    +cil_var_local(X).

% get all statements in the function
cil_stmt_instrs(S,_), +cil_stmt(S).
cil_stmt_return(S), +cil_stmt(S).
cil_stmt_goto(S,_), +cil_stmt(S).
cil_stmt_break(S), +cil_stmt(S).
cil_stmt_continue(S), +cil_stmt(S).
cil_stmt_if(S,_,_,_), +cil_stmt(S).
cil_stmt_switch(S,_,_,_), +cil_stmt(S).
cil_stmt_loop(S,_), +cil_stmt(S).
cil_stmt_block(S,_), +cil_stmt(S).
cil_stmt_tryfinally(S), +cil_stmt(S).
cil_stmt_tryexcept(S), +cil_stmt(S).

% get all instructions in the function
cil_instr_set(I,_,_), +cil_instr(I).
cil_instr_call(I,_), +cil_instr(I).
cil_instr_asm(I,_), +cil_instr(I).

% classify ikind/fkind signs and sizes
predicate machine_int(machine_kind).
machine(K), +machine_int(K).
~machine(_), +machine_int(i386).

machine_int(i386), +ikind_bytes(ischar,true,1),
    +ikind_bytes(ichar,    true,1), +ikind_bytes(iuchar,    false,1),
    +ikind_bytes(ishort,   true,2), +ikind_bytes(iushort,   false,2),
    +ikind_bytes(iint,     true,4), +ikind_bytes(iuint,     false,4),
    +ikind_bytes(ilong,    true,4), +ikind_bytes(iulong,    false,4),
    +ikind_bytes(ilonglong,true,8), +ikind_bytes(iulonglong,false,8).
machine_int(i386), +fkind_bytes(ffloat,4), +fkind_bytes(fdouble,8), 
    +fkind_bytes(flongdouble,12).
machine_int(i386), +pointer_bytes(4).

machine_int(x86_64), +ikind_bytes(ischar,true,1),
    +ikind_bytes(ichar,    true,1), +ikind_bytes(iuchar,    false,1),
    +ikind_bytes(ishort,   true,2), +ikind_bytes(iushort,   false,2),
    +ikind_bytes(iint,     true,4), +ikind_bytes(iuint,     false,4),
    +ikind_bytes(ilong,    true,8), +ikind_bytes(iulong,    false,8),
    +ikind_bytes(ilonglong,true,8), +ikind_bytes(iulonglong,false,8).
machine_int(x86_64), +fkind_bytes(ffloat,4), +fkind_bytes(fdouble,8), 
    +fkind_bytes(flongdouble,16).
machine_int(x86_64), +pointer_bytes(8).

ikind_bits(Kind, Signed, Bytes * 8) :- ikind_bytes(Kind, Signed, Bytes).
fkind_bits(Kind, Bytes * 8) :- fkind_bytes(Kind, Bytes).
pointer_bits(Bytes * 8) :- pointer_bytes(Bytes).

ikind_bits(K,S,LEN), cil_type_int(T,K), +type_bits(T,S,LEN).
ikind_bits(iint,S,LEN), cil_type_enum(T,_), +type_bits(T,S,LEN).
fkind_bits(K,LEN), cil_type_float(T,K), +type_bits(T,true,LEN).
pointer_bits(LEN), cil_type_ptr(T,_), +type_bits(T,false,LEN).

% lval/offset types

cil_lval_var(LV,X,OFF), cil_var_name(X,_,XT),
    +base_off_type(OFF,XT), off_type(OFF,T), +lval_type(LV,T).
cil_lval_mem(LV,ME,OFF), exp_type(ME,MT), cil_type_ptr(MT,DT),
    +base_off_type(OFF,DT), off_type(OFF,T), +lval_type(LV,T).

cil_off_none(OFF), base_off_type(OFF,T), +off_type(OFF,T).
cil_off_field(OFF,F,NOFF), cil_field_name(F,_,FT,_,_),
    +base_off_type(NOFF,FT), off_type(NOFF,T), +off_type(OFF,T).
cil_off_index(OFF,_,NOFF), base_off_type(OFF,AT), cil_type_array(AT,ET,_),
    +base_off_type(NOFF,ET), off_type(NOFF,T), +off_type(OFF,T).

% exp types

% fabricate types for constant exps. TODO: type widths
cil_const_int(C,K,_), cil_exp_const(E,C), cil_make_type(E,"type",T),
    +cil_type_int(T,K), ikind_bytes(K,_,N), +cil_type_x_bytes(T,N),
    +exp_type(E,T).
cil_const_char(C,_), cil_exp_const(E,C), cil_make_type(E,"type",T),
    +cil_type_int(T,iint), +cil_type_x_bytes(T,1),
    +exp_type(E,T).
cil_const_str(C,_), cil_exp_const(E,C),
    cil_make_type(E,"type",T), cil_make_type(C,"etype",DT),
    +cil_type_int(DT,ichar), +cil_type_x_bytes(T,1),
    +cil_type_ptr(T,DT), +cil_type_x_bytes(T,4),
    +exp_type(E,T).
cil_const_wstr(C,_), cil_exp_const(E,C),
    cil_make_type(E,"type",T), cil_make_type(C,"etype",DT),
    +cil_type_int(DT,iushort), +cil_type_x_bytes(T,2),
    +cil_type_ptr(T,DT), +cil_type_x_bytes(T,4),
    +exp_type(E,T).
cil_const_real(C,K,_), cil_exp_const(E,C), cil_make_type(E,"type",T),
    +cil_type_float(T,K), fkind_bytes(K,N), +cil_type_x_bytes(T,N),
    +exp_type(E,T).

% fabricate types for sizeof/alignof exps.
cil_exp_x_sizeof_alignof(E), cil_make_type(E,"type",T),
    +cil_type_int(T,iuint), +cil_type_x_bytes(T,4), +exp_type(E,T).

% lval exps have same type as the lval
cil_exp_lval(E,LV), lval_type(LV,T), +exp_type(E,T).

% fabricate pointer types for address exps
cil_exp_addr(E,LV), lval_type(LV,DT), cil_make_type(E,"type",T),
    +cil_type_ptr(T,DT), +exp_type(E,T).

% types for cast/unop/binop come straight off the exp
cil_exp_cast(E,_,T), +exp_type(E,T).
cil_exp_unop(E,_,_,T), +exp_type(E,T).
cil_exp_binop(E,_,_,_,T), +exp_type(E,T).

% get pointer/integer/float exps
cil_type_ptr(T,_), exp_type(E,T), +exp_tptr(E).
cil_type_int(T,K), exp_type(E,T), +exp_tint(E,K).
cil_type_enum(T,_), exp_type(E,T), +exp_tint(E,iint).
cil_type_float(T,K), exp_type(E,T), +exp_tflt(E,K).

% trailing lval fields

predicate last_field(in OFF:c_offset,in TYP:c_type,FLD:c_field,COMP:string).
last_field(O,T,FLD,COMP) :- cil_off_field(O,FLD,NO), cil_off_none(NO),
    cil_type_comp(T,COMP).
last_field(O,T,FLD,COMP) :- cil_off_field(O,F,NO),
    cil_field_name(F,_,FT,_,_), last_field(NO,FT,FLD,COMP).
last_field(O,T,FLD,COMP) :- cil_off_index(O,_,NO),
    cil_type_array(T,ET,_), last_field(NO,ET,FLD,COMP).

lval_field(LV,FLD,COMP) :- cil_lval_var(LV,X,O), cil_var_name(X,_,T),
    last_field(O,T,FLD,COMP).
lval_field(LV,FLD,COMP) :- cil_lval_mem(LV,E,O), exp_type(E,PT),
    cil_type_ptr(PT,T), last_field(O,T,FLD,COMP).

% classify ops

+logic_op(b_land), +logic_op(b_lor).
+compare_op(b_eq), +compare_op(b_ne), +compare_op(b_lt), +compare_op(b_gt),
    +compare_op(b_le), +compare_op(b_ge).
+arith_op(b_plusa), +arith_op(b_minusa),
    +arith_op(b_band), +arith_op(b_bxor), +arith_op(b_bor),
    +arith_op(b_mult), +arith_op(b_div), +arith_op(b_mod),
    +arith_op(b_shiftlt), +arith_op(b_shiftrt).
+pointer_op(b_pluspi), +pointer_op(b_minuspi).
+pointer_int_op(b_minuspp).

% function call predicates

% identify direct calls
cil_instr_call(I,FEXP), cil_exp_lval(FEXP,LV),
    cil_lval_var(LV,X,OFF), cil_off_none(OFF), cil_var_name(X,FN,_),
    +dircall(I,FN).

% identify call return values
cil_instr_call_ret(I,RLV), cil_lval_var(RLV,X,ROFF), cil_off_none(ROFF),
    cil_var_temporary(X), +callretvar(I,X).

% type aliasing

type_alias(T0,T1) :- cil_type_void(T0), cil_type_void(T1).
type_alias(T0,T1) :- cil_type_int(T0,K), cil_type_int(T1,K).
type_alias(T0,T1) :- cil_type_float(T0,K), cil_type_float(T1,K).
type_alias(T0,T1) :- cil_type_comp(T0,C), cil_type_comp(T1,C).
type_alias(T0,T1) :- cil_type_enum(T0,E), cil_type_enum(T1,E).
type_alias(T0,T1) :- cil_type_valist(T0), cil_type_valist(T1).
type_alias(T0,T1) :-
    cil_type_ptr(T0,DT0), cil_type_ptr(T1,DT1), type_alias(DT0,DT1).

% call casts

cil_instr_call(I,E), cil_instr_call_ret(I,RLV), lval_type(RLV,LVTYP),
    exp_type(E,FNTYP), cil_type_func(FNTYP,RTYP,_), ~type_alias(LVTYP,RTYP),
    +call_cast(I,LVTYP).

% stringifying

% convert an exp to a string using exp_string, wrapping binops with '()'
predicate b_exp_string(in c_exp,string).
b_exp_string(E,S) :- exp_string(E,S), ~cil_exp_binop(E,_,_,_,_).
b_exp_string(E,S) :- exp_string(E,SS), cil_exp_binop(E,_,_,_,_),
    S = "(" ^ SS ^ ")".

% stringify lvalues
cil_lval_var(LV,X,OFF), cil_var_name(X,XS,_), cleanup_glob_string(XS,NXS),
    off_string(OFF,OS), +lval_string(LV,NXS ^ OS).
cil_lval_mem(LV,ME,OFF), cil_off_none(OFF), b_exp_string(ME,MS),
    +lval_string(LV, "*" ^ MS).
cil_lval_mem(LV,ME,OFF), cil_off_field(OFF,F,NOFF), b_exp_string(ME,MS),
    cil_field_name(F,FS,_,_,_), off_string(NOFF,OS),
    S = MS ^ "->" ^ FS ^ OS, +lval_string(LV,S).
cil_lval_mem(LV,ME,OFF), cil_off_index(OFF,_,_), b_exp_string(ME,MS),
    off_string(OFF,OS), +lval_string(LV, MS ^ OS).

% stringify offsets
cil_off_none(OFF), +off_string(OFF,"").
cil_off_field(OFF,F,NOFF), cil_field_name(F,FS,_,_,_), off_string(NOFF,OS),
    S = "." ^ FS ^ OS, +off_string(OFF,S).
cil_off_index(OFF,E,NOFF), exp_string(E,IS), off_string(NOFF,OS),
    S = "[" ^ IS ^ "]" ^ OS, +off_string(OFF,S).

% stringify constants
predicate const_string(c_const,string).
cil_const_int(C,_,N), tostring(N,S), +const_string(C,S).
cil_const_char(C,N), tostring(N,S), +const_string(C,S).
cil_const_str(C,S), R = "\"" ^ S ^ "\"", +const_string(C,R).
cil_const_wstr(C,_), +const_string(C,"wchar_t[]").
cil_const_real(C,_,N), tostring(N,S), +const_string(C,S).

% stringify unops
predicate unop_str(unop,string).
+unop_str(u_neg,"-"), +unop_str(u_bnot,"~"), +unop_str(u_lnot,"!").

% stringify binops
predicate binop_str(binop,string).
+binop_str(b_plusa,"+"), +binop_str(b_minusa,"-"),
    +binop_str(b_pluspi,"+"),
    +binop_str(b_minuspi,"-"), +binop_str(b_minuspp,"-"),
    +binop_str(b_mult,"*"), +binop_str(b_div,"/"), +binop_str(b_mod,"%"),
    +binop_str(b_shiftlt,"<<"), +binop_str(b_shiftrt,">>"),
    +binop_str(b_lt,"<"), +binop_str(b_gt,">"),
    +binop_str(b_le,"<="), +binop_str(b_ge,">="),
    +binop_str(b_eq,"=="), +binop_str(b_ne,"!="),
    +binop_str(b_band,"&"), +binop_str(b_bxor,"^"), +binop_str(b_bor,"|"),
    +binop_str(b_land,"&&"), +binop_str(b_lor,"||").

% stringify expressions
cil_exp_const(E,C), const_string(C,S), +exp_string(E,S).
cil_exp_lval(E,LV), lval_string(LV,S), +exp_string(E,S).
cil_exp_sizeof(E,_), cil_exp_x_intval(E,N), tostring(N,S), +exp_string(E,S).
cil_exp_sizeofe(E,_), cil_exp_x_intval(E,N), tostring(N,S), +exp_string(E,S).
cil_exp_sizeofstr(E,_), cil_exp_x_intval(E,N), tostring(N,S), +exp_string(E,S).
cil_exp_alignof(E,_), cil_exp_x_intval(E,N), tostring(N,S), +exp_string(E,S).
cil_exp_alignofe(E,_), cil_exp_x_intval(E,N), tostring(N,S), +exp_string(E,S).
cil_exp_addr(E,LV), lval_string(LV,LS), +exp_string(E,"&" ^ LS).
cil_exp_cast(E,CE,T), type_string(T,TS), b_exp_string(CE,CS),
    +exp_string(E, "(" ^ TS ^ ")" ^ CS).
cil_exp_unop(E,OP,RE,_), unop_str(OP,US), b_exp_string(RE,RS),
    +exp_string(E,US ^ RS).
cil_exp_binop(E,OP,LE,RE,_), binop_str(OP,US),
    b_exp_string(LE,LS), b_exp_string(RE,RS), +exp_string(E,LS ^ US ^ RS).

% stringify integer kinds
predicate ikind_str(ikind,string).
+ikind_str(ichar,"char"),
    +ikind_str(ischar,"char"), +ikind_str(iuchar,"u_char"),
    +ikind_str(iint,"int"), +ikind_str(iuint,"u_int"),
    +ikind_str(ishort,"short"), +ikind_str(iushort,"u_short"),
    +ikind_str(ilong,"long"), +ikind_str(iulong,"u_long"),
    +ikind_str(ilonglong,"longlong"),
    +ikind_str(iulonglong,"u_longlong").

% stringify float kinds
predicate fkind_str(fkind,string).
+fkind_str(ffloat,"float"), +fkind_str(fdouble,"double"),
    +fkind_str(flongdouble,"longdouble").

% stringify types

cil_type_void(T), +type_string(T,"void").
cil_type_int(T,K), ikind_str(K,S), +type_string(T,S).
cil_type_float(T,K), fkind_str(K,S), +type_string(T,S).
cil_type_ptr(T,DT), type_string(DT,DS), +type_string(T,DS ^ "*").
cil_type_array(T,ET,_), type_string(ET,ES), +type_string(T,ES ^ "[]").
cil_type_func(T,_,_), +type_string(T,"function").
cil_type_comp(T,NAME), +type_string(T,"struct " ^ NAME).
cil_type_enum(T,NAME), +type_string(T,"enum " ^ NAME).
cil_type_named(T,_,NT), type_string(NT,S), +type_string(T,S).
cil_type_valist(T), +type_string(T,"builtin_va_list").

% other stringification and output

location_string(FILE,LINE, FILE ^ ":" ^ tostring(LINE)) :- .

% clean functions by stripping everything before the ':' if present.
% ':' can't appear in a regular function name
cleanup_glob_string(G,GSTR) :-
    str_sub(G,POS,1,":"), str_sub(G,0,POS + 1,STATIC),
    str_cat(STATIC,GSTR,G).
cleanup_glob_string(G,G) :- ~str_sub(G,_,1,":").

sum_location(s_func,FILE,LINE) :- cil_fundec_location(_,FILE,LINE).
sum_location(s_loop{PH},FILE,LINE) :- cil_stmt_x_location(PH,FILE,LINE).
sum_location(s_call{I},FILE,LINE) :- cil_instr_x_location(I,FILE,LINE).
sum_location(s_asm{I},FILE,LINE) :- cil_instr_x_location(I,FILE,LINE).

% get composite type locations
comp_location(C,FILE,MINLINE - 5,MAXLINE + 5) :-
    cil_comp(C)->cil_comp_location(_,FILE,MINLINE),
    cil_comp(C)->cil_comp_end_location(_,_,MAXLINE).

% get global variable locations. for variables with static initializers look at the
% initializer expressions to find a suitable end location
glob_location(G,FILE,MINLINE - 5,MAXLINE + 5) :-
    cil_glob(G)->cil_var_name(_,_,_),
    cil_glob(G)->cil_var_location(_,FILE,MINLINE),
    (~cil_init(G)->cil_exp_x_location(_,_,_,_,_,_), MAXLINE=MINLINE;
     \/cil_init(G)->cil_exp_x_location(_,_,L,_,_,_):int_max_all(L,MAXLINE)).

% get function locations
func_location(FN,FILE,MINLINE - 5,MAXLINE + 5) :-
    cil_body(FN)->cil_fundec_location(_,FILE,MINLINE),
    cil_body(FN)->cil_fundec_end_location(_,_,MAXLINE).

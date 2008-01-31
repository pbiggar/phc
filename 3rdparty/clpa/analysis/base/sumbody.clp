%%
% Authors:
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

%-----------------------------------------------------------------------------%
% sumbody.clp
%
% Create a new session cil_sum_body(FN,SUM) that contains a single loop-free
% CFG for either a function's outer body or one of its inner loops.
%
% Since all intermediate predicates are deleted when fixpointing over separate
% sessions, analyses that handle cil_sum_body rather than cil_body do not need
% to worry about invalidated data when propagating both top-down and bottom-up,
% or when handling tail recursive loop invocations.
%
% cil_sum_body() contains the CFG for a particular loop or outer function
% body, as well as all the predicates in the function's body itself.
% A special predicate cil_cursum(Sum) is defined to indicate which
% summary is currently being analyzed.
%
% The CFG construction code understands when it is being run over a 
% cil_sum_body session and modifies its behaviour accordingly.
%
%-----------------------------------------------------------------------------%

import "loops.clp".

analyze session_name("cil_body").

+split_loops().

    % Copy the CFG into each session, together with summary bounds for
    % just one summary.
cil_curfn(FN), sum_bound(SUM,PIN,POUT),
    +cil_sum_body(FN,SUM)->cil_curfn(FN),
    +cil_sum_body(FN,SUM)->cil_cursum(SUM),
    +cil_sum_body(FN,SUM)->sum_bound(SUM,PIN,POUT).
cil_curfn(FN), sum_body(SUM,P), cfgn_final(P,N),
    +cil_sum_body(FN,SUM)->cfgn_final(P,N).
cil_curfn(FN), sum_body(SUM,P0), cfge_final(P0,P1,E),
    +cil_sum_body(FN,SUM)->cfge_final(P0,P1,E).

    % branch_loc and loophead are needed to produce program point location
    % information.
cil_curfn(FN), sum_body(SUM,P), branch(P,_,_,E), branch_loc(E,File,Line),
    +cil_sum_body(FN,SUM)->branch_loc(E,File,Line).
cil_curfn(FN), sum_bound(SUM,_,_), loophead(PH),
    +cil_sum_body(FN,SUM)->loophead(PH).

%-----------------------------------------------------------------------------%

    % Add process ordering dependencies from the current function to the
    % set of calls and loops that are performed.
icall(P0,_,I), cil_curfn(Fn), sum_body(Sum, P0), anycall(I, Callee, _),
    +cil_sum_body(Fn, Sum)->process_dependency("cil_sum_body", Callee, s_func).
iloop(P0,_,PH), cil_curfn(Fn), sum_body(Sum, P0),
    +cil_sum_body(Fn, Sum)->process_dependency("cil_sum_body", Fn, s_loop{PH}).

%-----------------------------------------------------------------------------%

% We need to merge every predicate in cil_body into each new cil_sum_body.
% Do not attempt to distinguish which predicates are relevant to which sums
predicate merge(FN:string,SUM:sum).
cil_curfn(FN), sum_bound(SUM,_,_), +merge(FN,SUM).

% This should be updated should any new predicates get into cil_body via
% the original CIL construction.

merge(FN,SUM), cil_type_void(T),               +cil_sum_body(FN,SUM)->cil_type_void(T).
merge(FN,SUM), cil_type_int(T,K),              +cil_sum_body(FN,SUM)->cil_type_int(T,K).
merge(FN,SUM), cil_type_float(T,K),            +cil_sum_body(FN,SUM)->cil_type_float(T,K).
merge(FN,SUM), cil_type_ptr(T,DT),             +cil_sum_body(FN,SUM)->cil_type_ptr(T,DT).
merge(FN,SUM), cil_type_array(T,E,ET),         +cil_sum_body(FN,SUM)->cil_type_array(T,E,ET).
merge(FN,SUM), cil_type_func(T,RT,VA),         +cil_sum_body(FN,SUM)->cil_type_func(T,RT,VA).
merge(FN,SUM), cil_type_func_arg(T,N,S,AT),    +cil_sum_body(FN,SUM)->cil_type_func_arg(T,N,S,AT).
merge(FN,SUM), cil_type_func_arg_attr(T,N,A),  +cil_sum_body(FN,SUM)->cil_type_func_arg_attr(T,N,A).
merge(FN,SUM), cil_type_named(T,NT,S),         +cil_sum_body(FN,SUM)->cil_type_named(T,NT,S).
merge(FN,SUM), cil_type_comp(T,C),             +cil_sum_body(FN,SUM)->cil_type_comp(T,C).
merge(FN,SUM), cil_type_enum(T,E),             +cil_sum_body(FN,SUM)->cil_type_enum(T,E).
merge(FN,SUM), cil_type_valist(T),             +cil_sum_body(FN,SUM)->cil_type_valist(T).
merge(FN,SUM), cil_type_x_attr(T,A),           +cil_sum_body(FN,SUM)->cil_type_x_attr(T,A).
merge(FN,SUM), cil_type_x_bytes(T,BS),         +cil_sum_body(FN,SUM)->cil_type_x_bytes(T,BS).

merge(FN,SUM), cil_field_name(F,S,T,BS,BE),  +cil_sum_body(FN,SUM)->cil_field_name(F,S,T,BS,BE).
merge(FN,SUM), cil_field_attr(F,A),          +cil_sum_body(FN,SUM)->cil_field_attr(F,A).

merge(FN,SUM), cil_var_name(X,S,T),  +cil_sum_body(FN,SUM)->cil_var_name(X,S,T).
merge(FN,SUM), cil_var_global(X),    +cil_sum_body(FN,SUM)->cil_var_global(X).
merge(FN,SUM), cil_var_inline(X),    +cil_sum_body(FN,SUM)->cil_var_inline(X).
merge(FN,SUM), cil_var_static(X),    +cil_sum_body(FN,SUM)->cil_var_static(X).
merge(FN,SUM), cil_var_register(X),  +cil_sum_body(FN,SUM)->cil_var_register(X).
merge(FN,SUM), cil_var_init(X,I),    +cil_sum_body(FN,SUM)->cil_var_init(X,I).
merge(FN,SUM), cil_var_attr(X,A),    +cil_sum_body(FN,SUM)->cil_var_attr(X,A).

merge(FN,SUM), cil_exp_const(E,C),                   +cil_sum_body(FN,SUM)->cil_exp_const(E,C).
merge(FN,SUM), cil_exp_lval(E,LV),                   +cil_sum_body(FN,SUM)->cil_exp_lval(E,LV).
merge(FN,SUM), cil_exp_sizeof(E,T),                  +cil_sum_body(FN,SUM)->cil_exp_sizeof(E,T).
merge(FN,SUM), cil_exp_sizeofe(E,ES),                +cil_sum_body(FN,SUM)->cil_exp_sizeofe(E,ES).
merge(FN,SUM), cil_exp_sizeofstr(E,S),               +cil_sum_body(FN,SUM)->cil_exp_sizeofstr(E,S).
merge(FN,SUM), cil_exp_alignof(E,T),                 +cil_sum_body(FN,SUM)->cil_exp_alignof(E,T).
merge(FN,SUM), cil_exp_alignofe(E,EA),               +cil_sum_body(FN,SUM)->cil_exp_alignofe(E,EA).
merge(FN,SUM), cil_exp_unop(E,U,RE,T),               +cil_sum_body(FN,SUM)->cil_exp_unop(E,U,RE,T).
merge(FN,SUM), cil_exp_binop(E,B,LE,RE,T),           +cil_sum_body(FN,SUM)->cil_exp_binop(E,B,LE,RE,T).
merge(FN,SUM), cil_exp_cast(E,CE,T),                 +cil_sum_body(FN,SUM)->cil_exp_cast(E,CE,T).
merge(FN,SUM), cil_exp_addr(E,LV),                   +cil_sum_body(FN,SUM)->cil_exp_addr(E,LV).
merge(FN,SUM), cil_exp_start(E,LV),                  +cil_sum_body(FN,SUM)->cil_exp_start(E,LV).
merge(FN,SUM), cil_exp_x_intval(E,N),                +cil_sum_body(FN,SUM)->cil_exp_x_intval(E,N).
merge(FN,SUM), cil_exp_x_location(E,S,BL,EL,BB,EB),  +cil_sum_body(FN,SUM)->cil_exp_x_location(E,S,BL,EL,BB,EB).
merge(FN,SUM), cil_exp_x_macro(E,M),                 +cil_sum_body(FN,SUM)->cil_exp_x_macro(E,M).

merge(FN,SUM), cil_const_int(C,K,N),   +cil_sum_body(FN,SUM)->cil_const_int(C,K,N).
merge(FN,SUM), cil_const_str(C,S),     +cil_sum_body(FN,SUM)->cil_const_str(C,S).
merge(FN,SUM), cil_const_wstr(C,WS),   +cil_sum_body(FN,SUM)->cil_const_wstr(C,WS).
merge(FN,SUM), cil_const_char(C,N),    +cil_sum_body(FN,SUM)->cil_const_char(C,N).
merge(FN,SUM), cil_const_real(C,K,F),  +cil_sum_body(FN,SUM)->cil_const_real(C,K,F).

merge(FN,SUM), cil_lval_var(LV,X,O),   +cil_sum_body(FN,SUM)->cil_lval_var(LV,X,O).
merge(FN,SUM), cil_lval_mem(LV,E,O),   +cil_sum_body(FN,SUM)->cil_lval_mem(LV,E,O).
merge(FN,SUM), cil_off_none(O),        +cil_sum_body(FN,SUM)->cil_off_none(O).
merge(FN,SUM), cil_off_field(O,F,NO),  +cil_sum_body(FN,SUM)->cil_off_field(O,F,NO).
merge(FN,SUM), cil_off_index(O,E,NO),  +cil_sum_body(FN,SUM)->cil_off_index(O,E,NO).

merge(FN,SUM), cil_fundec_name(FD,X,B),          +cil_sum_body(FN,SUM)->cil_fundec_name(FD,X,B).
merge(FN,SUM), cil_fundec_formal(FD,N,X),        +cil_sum_body(FN,SUM)->cil_fundec_formal(FD,N,X).
merge(FN,SUM), cil_fundec_local(FD,X),           +cil_sum_body(FN,SUM)->cil_fundec_local(FD,X).
merge(FN,SUM), cil_fundec_location(FD,F,L),      +cil_sum_body(FN,SUM)->cil_fundec_location(FD,F,L).
merge(FN,SUM), cil_fundec_end_location(FD,F,L),  +cil_sum_body(FN,SUM)->cil_fundec_end_location(FD,F,L).

merge(FN,SUM), cil_block_stmts(B,SLIST),  +cil_sum_body(FN,SUM)->cil_block_stmts(B,SLIST).
merge(FN,SUM), cil_block_attr(B,A),       +cil_sum_body(FN,SUM)->cil_block_attr(B,A).

merge(FN,SUM), cil_stmt_instrs(S,ILIST),      +cil_sum_body(FN,SUM)->cil_stmt_instrs(S,ILIST).
merge(FN,SUM), cil_stmt_return(S),            +cil_sum_body(FN,SUM)->cil_stmt_return(S).
merge(FN,SUM), cil_stmt_return_exp(S,E),      +cil_sum_body(FN,SUM)->cil_stmt_return_exp(S,E).
merge(FN,SUM), cil_stmt_goto(S,ST),           +cil_sum_body(FN,SUM)->cil_stmt_goto(S,ST).
merge(FN,SUM), cil_stmt_break(S),             +cil_sum_body(FN,SUM)->cil_stmt_break(S).
merge(FN,SUM), cil_stmt_continue(S),          +cil_sum_body(FN,SUM)->cil_stmt_continue(S).
merge(FN,SUM), cil_stmt_if(S,E,TB,FB),        +cil_sum_body(FN,SUM)->cil_stmt_if(S,E,TB,FB).
merge(FN,SUM), cil_stmt_switch(S,E,B,CASES),  +cil_sum_body(FN,SUM)->cil_stmt_switch(S,E,B,CASES).
merge(FN,SUM), cil_stmt_loop(S,B),            +cil_sum_body(FN,SUM)->cil_stmt_loop(S,B).
merge(FN,SUM), cil_stmt_block(S,B),           +cil_sum_body(FN,SUM)->cil_stmt_block(S,B).
merge(FN,SUM), cil_stmt_tryfinally(S),        +cil_sum_body(FN,SUM)->cil_stmt_tryfinally(S).
merge(FN,SUM), cil_stmt_tryexcept(S),         +cil_sum_body(FN,SUM)->cil_stmt_tryexcept(S).
merge(FN,SUM), cil_stmt_x_location(S,F,L),    +cil_sum_body(FN,SUM)->cil_stmt_x_location(S,F,L).

merge(FN,SUM), cil_instr_set(I,LV,E),          +cil_sum_body(FN,SUM)->cil_instr_set(I,LV,E).
merge(FN,SUM), cil_instr_call(I,E),            +cil_sum_body(FN,SUM)->cil_instr_call(I,E).
merge(FN,SUM), cil_instr_call_ret(I,LV),       +cil_sum_body(FN,SUM)->cil_instr_call_ret(I,LV).
merge(FN,SUM), cil_instr_call_arg(I,A,E),      +cil_sum_body(FN,SUM)->cil_instr_call_arg(I,A,E).
merge(FN,SUM), cil_instr_asm(I,TEMPLATE),      +cil_sum_body(FN,SUM)->cil_instr_asm(I,TEMPLATE).
merge(FN,SUM), cil_instr_asm_out(I,A,N,S,LV),  +cil_sum_body(FN,SUM)->cil_instr_asm_out(I,A,N,S,LV).
merge(FN,SUM), cil_instr_asm_in(I,A,N,S,E),    +cil_sum_body(FN,SUM)->cil_instr_asm_in(I,A,N,S,E).
merge(FN,SUM), cil_instr_asm_clobber(I,S),     +cil_sum_body(FN,SUM)->cil_instr_asm_clobber(I,S).
merge(FN,SUM), cil_instr_asm_attr(I,A),        +cil_sum_body(FN,SUM)->cil_instr_asm_attr(I,A).
merge(FN,SUM), cil_instr_x_location(I,F,L),    +cil_sum_body(FN,SUM)->cil_instr_x_location(I,F,L).

merge(FN,SUM), cil_attr_name(A,S),             +cil_sum_body(FN,SUM)->cil_attr_name(A,S).
merge(FN,SUM), cil_attr_arg(A,N,NA),           +cil_sum_body(FN,SUM)->cil_attr_arg(A,N,NA).
merge(FN,SUM), cil_attr_arg_int(A,N),          +cil_sum_body(FN,SUM)->cil_attr_arg_int(A,N).
merge(FN,SUM), cil_attr_arg_str(A,S),          +cil_sum_body(FN,SUM)->cil_attr_arg_str(A,S).
merge(FN,SUM), cil_attr_arg_cons(A,NA),        +cil_sum_body(FN,SUM)->cil_attr_arg_cons(A,NA).
merge(FN,SUM), cil_attr_arg_sizeof(A,T),       +cil_sum_body(FN,SUM)->cil_attr_arg_sizeof(A,T).
merge(FN,SUM), cil_attr_arg_sizeofe(A,NA),     +cil_sum_body(FN,SUM)->cil_attr_arg_sizeofe(A,NA).
merge(FN,SUM), cil_attr_arg_alignof(A,T),      +cil_sum_body(FN,SUM)->cil_attr_arg_alignof(A,T).
merge(FN,SUM), cil_attr_arg_alignofe(A,NA),    +cil_sum_body(FN,SUM)->cil_attr_arg_alignofe(A,NA).
merge(FN,SUM), cil_attr_arg_unop(A,U,RA),      +cil_sum_body(FN,SUM)->cil_attr_arg_unop(A,U,RA).
merge(FN,SUM), cil_attr_arg_binop(A,B,LA,RA),  +cil_sum_body(FN,SUM)->cil_attr_arg_binop(A,B,LA,RA).
merge(FN,SUM), cil_attr_arg_dot(A,NA,S),       +cil_sum_body(FN,SUM)->cil_attr_arg_dot(A,NA,S).

merge(FN,SUM), cil_macro_builtin(M),               +cil_sum_body(FN,SUM)->cil_macro_builtin(M).
merge(FN,SUM), cil_macro_ident(M,S),               +cil_sum_body(FN,SUM)->cil_macro_ident(M,S).
merge(FN,SUM), cil_macro_func(M,S),                +cil_sum_body(FN,SUM)->cil_macro_func(M,S).
merge(FN,SUM), cil_macro_func_arg(M,A,AS,FS),      +cil_sum_body(FN,SUM)->cil_macro_func_arg(M,A,AS,FS).
merge(FN,SUM), cil_macro_x_name(M,N),              +cil_sum_body(FN,SUM)->cil_macro_x_name(M,N).
merge(FN,SUM), cil_macro_x_location(M,F,L,BB,EB),  +cil_sum_body(FN,SUM)->cil_macro_x_location(M,F,L,BB,EB).
merge(FN,SUM), cil_macro_x_parent(M,PM),           +cil_sum_body(FN,SUM)->cil_macro_x_parent(M,PM).

merge(FN,SUM), cil_var_return(X),     +cil_sum_body(FN,SUM)->cil_var_return(X).
merge(FN,SUM), cil_var_temporary(X),  +cil_sum_body(FN,SUM)->cil_var_temporary(X).
merge(FN,SUM), cil_var_local(X),      +cil_sum_body(FN,SUM)->cil_var_local(X).
merge(FN,SUM), cil_var_formal(X),     +cil_sum_body(FN,SUM)->cil_var_formal(X).

%-----------------------------------------------------------------------------%

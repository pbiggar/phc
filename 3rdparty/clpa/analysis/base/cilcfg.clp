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

% Generate a CFG for each CIL function composed of branches and instructions.

import "cilbase.clp".

% PREDICATES

% disable construction of the full function CFG
predicate disable_cfg().

% program point in a function CFG
type pp ::=
    p_so{c_stmt}        % output point of statement
  | p_io{c_instr}       % output point of instruction
  | p_bi{c_block}       % input point of block
  | p_cs{c_stmt,c_exp}  % test point for a case statement
  | p_rp{c_instr}       % return point introduced for temp assign after call
  | p_abort             % program termination point after exit call
  | p_bad               % dummy unreachable program point
    % extra points from loops.clp
  | p_lnext{loop}       % start of the next loop iteration
  | p_lnexti{loop,pp}   % p_lnext for entry P of an irreducible loop
  | p_lsum{loop}        % the summary point of a loop after splitting
  | p_lsumi{loop,pp}    % p_lsum for irreducible loops starting at P
  | p_lterm{loop,pp}    % the loop term point within a split PH, exiting to P
  | p_ltrec{loop}.      % the loop term point within a split PH, after the
                        % tail-recursive loop invocation. can exit to any P

% P is the entry point of the current function
predicate entry(P:pp).

% P is the exit point of the current function
predicate exit(P:pp).

% Branch from P to P0 if A holds, P1 otherwise
predicate branch(P:pp,P0:pp,P1:pp,E:c_exp) order [P,P0] [P,P1].

% P0 and P1 are connected by a set/asm/call instruction I
predicate iset(P0:pp,P1:pp,I:c_instr) order [P0,P1].
predicate iasm(P0:pp,P1:pp,I:c_instr) order [P0,P1].
predicate icall(P0:pp,P1:pp,I:c_instr) order [P0,P1].

% P0 and P1 are connected by a split loop PH
predicate iloop(P0:pp,P1:pp,PH:loop) order [P0,P1].

% P0 and P1 are connected by a summary edge for either a call or loop
predicate isum(P0:pp,P1:pp,SUM:sum) order [P0,P1].

% SUM/P may call into CSUM within CFN. T is 'direct' for direct calls
% and loops, 'indirect' for indirect calls
predicate isum_target(SUM:sum,CFN:string,CSUM:sum,T:calltype).

% as with isum, except that tail recursive loop edges are omitted
predicate isum_norecurse(P0:pp,P1:pp,SUM:sum) order [P0,P1] [SUM,P0].

% E/LV/OFF are used at point P
predicate exp_point(E:c_exp,P:pp).
predicate lval_point(LV:c_lval,P:pp).
predicate off_point(OFF:c_offset,P:pp).

% pp corresponds to line LINE in source file FILE
predicate point_location(in pp,FILE:string,LINE:int) succeeds [once].

% CFG CONSTRUCTION

% add to translate the "if" statement IF into a nondeterministic branch
predicate cfg_ignore_if(in IF:c_stmt).

% add to translate the "switch" statement SWITCH into a nondeterministic branch
predicate cfg_ignore_switch(in SWITCH:c_stmt).

% calls to CFG will exit the program or otherwise fail to return
predicate exit_call(CFN:string).

% each call to an exit_call() function will be replaced with a call edge to
% p_abort, symbolizing termination of the program. A default set of must-exit
% functions from libc and linux is provided; additional ones may be added
% by updating exit_call() or by running exit.clp
predicate prune_exit_calls().

% CONSTRUCTION PREDICATES

% types of CFG nodes
type cfg_node ::=
    nentry         % function entry
  | nexit          % function exit
  | nlooph{loop}.  % (potential) entry point of inner loop PH
predicate cfgn_base(pp,cfg_node).  % CFG including nops

% types of CFG edges
type cfg_edge ::=
    easm{c_instr}    % asm edge
  | eset{c_instr}    % set instruction
  | ecall{c_instr}   % call instruction
  | eloop{loop}      % loop summary
  | ebtrue{c_exp}    % true branch on E
  | ebfalse{c_exp}.  % false branch on E
predicate cfge_base(pp,pp,cfg_edge).  % CFG including nops
predicate cfge_nop(pp,pp).            % nops in cfge_base

% nodes and edges after removing nops
predicate cfgn(pp,cfg_node).
predicate cfge(pp,pp,cfg_edge).

% final nodes and edges, after handling by loops.clp
predicate cfgn_final(pp,cfg_node).
predicate cfge_final(pp,pp,cfg_edge).

% CONSTRUCTION SESSIONS

% exit function session and predicates
session exit_sum(FN:string) containing [exit_fn].
predicate exit_fn().    % A function is an exit function.

% RULES

% don't build the entire function's CFG if we are iterating over cil_sum_body
cil_cursum(_), +disable_cfg().

% cfg edge nesting

% I/E is nested inside the given source statement.
% each E as used in a generated branch edge must be instantiated with
% its parent if/switch, to get nesting as well as source location info
predicate instr_nest(c_instr,c_stmt).
predicate branch_nest(c_exp,c_stmt).

% compute base nesting information for instructions
cil_stmt_instrs(S,INSTRS), list_mem(INSTRS,I), +instr_nest(I,S).

% compute nesting information for statements
predicate stmt_nest_block(c_stmt,c_block).
predicate stmt_nest_stmt(c_stmt,c_stmt).

% push nesting up from statements nested within blocks
cil_block_stmts(B,STMTS), list_mem(STMTS,S),
    +stmt_nest_block(S,B), stmt_nest_stmt(XS,S), +stmt_nest_block(XS,B).

% push nesting up from blocks nested within statements
cil_stmt_if(S,_,TB,_), stmt_nest_block(XS,TB), +stmt_nest_stmt(XS,S).
cil_stmt_if(S,_,_,FB), stmt_nest_block(XS,FB), +stmt_nest_stmt(XS,S).
cil_stmt_switch(S,_,B,_), stmt_nest_block(XS,B), +stmt_nest_stmt(XS,S).
cil_stmt_loop(S,B), stmt_nest_block(XS,B), +stmt_nest_stmt(XS,S).
cil_stmt_block(S,B), stmt_nest_block(XS,B), +stmt_nest_stmt(XS,S).

% source file locations for expressions used in branches
predicate branch_loc(E:c_exp,FILE:string,LINE:int).
branch_nest(E,S), cil_stmt_x_location(S,FILE,LINE), +branch_loc(E,FILE,LINE).

% statement uniqueness

% check that each source CIL statement is unique, if this is violated
% within the original trees then the CFG will be broken
predicate duplicate_statements().
assert ~duplicate_statements().

% statement appearing twice in a block
cil_block_stmts(_,STMTS), ~list_nodup(STMTS),
    +duplicate_statements().

predicate stmt_parent_block(c_stmt,c_block).
cil_block_stmts(B,STMTS), list_mem(STMTS,S), +stmt_parent_block(S,B).

% statement appearing twice in different blocks
stmt_parent_block(S,B0), stmt_parent_block(S,B1), B0\=B1,
    +duplicate_statements().

% block/statement input/output points

% get IDs for all possible program points in the function's execution.
% entry/exit points are generated for every block and statement, and
% will be connected by nops later on

% blocks/statements with PIN and POUT points
predicate bld_block(c_block,PIN:pp,POUT:pp).
predicate bld_stmt(c_stmt,PIN:pp,POUT:pp).

% add function entry/exit points based on input/output points for body
cil_fundec_name(_,_,B), bld_block(B,PIN,POUT),
    +cfgn_base(PIN,nentry), +cfgn_base(POUT,nexit).

% get PIN/POUT for blocks and their lists of statements. start with the entry
% point of the block and walk down and generate intermediate points between
% each statement before finally getting POUT

predicate stmt_list_pp_exit(in list[c_stmt], in pp, out pp).
stmt_list_pp_exit([], P, P) :- .
stmt_list_pp_exit(Stmts, _, p_so{P}) :-
     Stmts \= [], list_reverse(Stmts, [P|_]).

predicate bld_stmt_list(list[c_stmt],PIN:pp).
bld_stmt_list([S|TAIL],PIN), +bld_stmt(S,PIN,p_so{S}),
    +bld_stmt_list(TAIL,p_so{S}).
~disable_cfg(), cil_block_stmts(B,STMTS), +bld_stmt_list(STMTS,p_bi{B}),
    stmt_list_pp_exit(STMTS, p_bi{B}, POUT),
    +bld_block(B,p_bi{B},POUT).

% block/statement break/continue points

% blocks/statements enclosed by BRK and CONT break/continue points.
% constructed and passed top down from the function definition
predicate bld_block_brkcnt(c_block,BRK:pp,CONT:pp).
predicate bld_stmt_brkcnt(c_stmt,BRK:pp,CONT:pp).

% pass the targets of break/continue points down from the function definition
~disable_cfg(), cil_fundec_name(_,_,B), +bld_block_brkcnt(B,p_bad,p_bad).

% pass break/continue from blocks to nested statements
cil_block_stmts(B,STMTS), bld_block_brkcnt(B,BRK,CNT),
    list_mem(STMTS,S), +bld_stmt_brkcnt(S,BRK,CNT).

% statements with child blocks. pass down the break/continue points
cil_stmt_if(S,_,TB,FB), bld_stmt_brkcnt(S,BRK,CNT),
    +bld_block_brkcnt(TB,BRK,CNT), +bld_block_brkcnt(FB,BRK,CNT).
cil_stmt_switch(S,_,B,_), bld_stmt_brkcnt(S,_,CNT), bld_stmt(S,_,POUT),
    +bld_block_brkcnt(B,POUT,CNT).
cil_stmt_loop(S,B), bld_stmt(S,PIN,POUT),
    +bld_block_brkcnt(B,POUT,PIN).
cil_stmt_block(S,B), bld_stmt_brkcnt(S,BRK,CNT),
    +bld_block_brkcnt(B,BRK,CNT).

% connect program points for each statement

% instruction list statements

% instructions with input/output points
predicate bld_instr(c_instr,PIN:pp,POUT:pp).

% get PIN/POUT for instructions inside statements. since we already have the
% entry/exit points of the statement, just generate the intermediate ones and
% put a nop from the last instruction output to the statement output
predicate bld_instr_list(list[c_instr],PIN:pp,POUT:pp).
bld_instr_list([],PIN,POUT), +cfge_nop(PIN,POUT).
bld_instr_list([I|TAIL],PIN,POUT), +bld_instr(I,PIN,p_io{I}),
    +bld_instr_list(TAIL,p_io{I},POUT).
cil_stmt_instrs(S,INSTRS), bld_stmt(S,PIN,POUT),
    +bld_instr_list(INSTRS,PIN,POUT).

% return statements

% if the function has a return type, make a new return variable
cil_fundec_name(_,X,_), cil_var_name(X,_,FNTYP), cil_type_func(FNTYP,RTYP,_),
    ~cil_type_void(RTYP), cil_make_var("ret","var",RVAR),
    +cil_var_name(RVAR,"$ret",RTYP), +cil_var_return(RVAR).

% returns without a returned value are just nops
cil_stmt_return(S), ~cil_stmt_return_exp(S,_),
    bld_stmt(S,PIN,_), cfgn_base(PEXIT,nexit), +cfge_nop(PIN,PEXIT).

% returns with a returned exp assign it to the return variable
cil_stmt_return(S), cil_stmt_return_exp(S,REXP),
    cil_make_lval(S,"retlv",RLV), cil_make_offset(S,"retoff",ROFF),
    cil_var_return(RVAR), +cil_lval_var(RLV,RVAR,ROFF), +cil_off_none(ROFF),
    cil_make_instr(S,"retset",RSET),
    +cil_instr_set(RSET,RLV,REXP), +instr_nest(RSET,S),
    cil_stmt_x_location(S,FILE,LINE), +cil_instr_x_location(RSET,FILE,LINE),
    bld_stmt(S,PIN,_), cfgn_base(PEXIT,nexit),
    +cfge_base(PIN,PEXIT,eset{RSET}).

% goto statements

% targets of Gotos are potential loop heads. if they do not actually loop,
% they will be filtered out by loops.clp
cil_stmt_goto(S,ST), bld_stmt(S,PIN,_), bld_stmt(ST,TPIN,_),
    +cfge_nop(PIN,TPIN), +cfgn_base(TPIN,nlooph{ST}).

% break/continue statements

cil_stmt_break(S), bld_stmt(S,PIN,_), bld_stmt_brkcnt(S,BRK,_),
    +cfge_nop(PIN,BRK).
cil_stmt_continue(S), bld_stmt(S,PIN,_), bld_stmt_brkcnt(S,_,CNT),
    +cfge_nop(PIN,CNT).

% if statements

% get a dummy set DSET unique to S from CEXP to a new int variable
predicate make_dummy_set(S:c_stmt, CEXP:c_exp).
predicate dummy_set(in S:c_stmt,in CEXP:c_exp,DSET:c_instr).
make_dummy_set(S,CEXP),
    cil_make_type(S,"dumtyp",DTYP),
    +cil_type_int(DTYP,iint), +cil_type_x_bytes(DTYP,4),
    cil_make_var(S,"dumvar",DVAR), tostring(S,SSTR), str_cat("__$",SSTR,DNAME),
    +cil_var_name(DVAR,DNAME,DTYP), +cil_var_temporary(DVAR),
    cil_make_lval(S,"dumlv",DLV), cil_make_offset(S,"dumoff",DOFF),
    +cil_lval_var(DLV,DVAR,DOFF), +cil_off_none(DOFF),
    cil_make_instr(S,"dumset",DSET),
    +cil_instr_set(DSET,DLV,CEXP), +instr_nest(DSET,S),
    cil_stmt_x_location(S,FILE,LINE), +cil_instr_x_location(DSET,FILE,LINE),
    +dummy_set(S,CEXP,DSET).

% construct the branching logic for an 'if' statement according to whether
% it is ignored or not
predicate bld_if(S:c_stmt,COND:c_exp,PIN:pp,TIN:pp,FIN:pp).
bld_if(S,COND,PIN,TIN,FIN), cfg_ignore_if(S), +make_dummy_set(S, COND),
    dummy_set(S,COND,DSET),
    +cfge_base(PIN,TIN,eset{DSET}), +cfge_base(PIN,FIN,eset{DSET}).
bld_if(S,COND,PIN,TIN,FIN), ~cfg_ignore_if(S),
    +branch_nest(COND,S),
    +cfge_base(PIN,TIN,ebtrue{COND}), +cfge_base(PIN,FIN,ebfalse{COND}).
cil_stmt_if(S,COND,TBLK,FBLK), bld_stmt(S,PIN,POUT),
    bld_block(TBLK,TIN,TOUT), bld_block(FBLK,FIN,FOUT),
    +cfge_nop(TOUT,POUT), +cfge_nop(FOUT,POUT),
    +bld_if(S,COND,PIN,TIN,FIN).

% case statements

% C is a list of cases for switch S testing COND with PIN the point
% where C is tested and POUT the switch exit point.
predicate bld_cases(S:c_stmt,C:list[c_cases],COND:c_exp,PDEF:maybe[pp],PIN:pp,
                    POUT:pp).
cil_stmt_switch(S,COND,BLK,CASES), bld_stmt(S,PIN,POUT),
    bld_block(BLK,_,BOUT), +cfge_nop(BOUT,POUT),
    +bld_cases(S,CASES,COND,no,PIN,POUT).

% handle ignored switches, then go through each case in the switch creating
% a dummy iset from the same PIN
bld_cases(S,[],COND,no,PIN,POUT), cfg_ignore_switch(S),
    +make_dummy_set(S, COND),
    dummy_set(S,COND,DSET), +cfge_base(PIN,POUT,eset{DSET}).
bld_cases(S,[],COND,yes{PDEF},PIN,_), cfg_ignore_switch(S),
    +make_dummy_set(S, COND),
    dummy_set(S,COND,DSET), +cfge_base(PIN,PDEF,eset{DSET}).
bld_cases(S,[default{ST}|TAIL],COND,_,PIN,POUT), cfg_ignore_switch(S),
    bld_stmt(ST,PT,_), +bld_cases(S,TAIL,COND,yes{PT},PIN,POUT).
bld_cases(S,[case{_,ST}|TAIL],COND,PDEF,PIN,POUT), cfg_ignore_switch(S),
    bld_stmt(ST,PT,_), +make_dummy_set(S, COND),    
    dummy_set(S,COND,DSET), +cfge_base(PIN,PT,eset{DSET}),
    +bld_cases(S,TAIL,COND,PDEF,PIN,POUT).

% handle regular switches, just create a cascading series of branches
bld_cases(S,[],_,no,PIN,POUT), ~cfg_ignore_switch(S),
    +cfge_nop(PIN,POUT).
bld_cases(S,[],_,yes{PDEF},PIN,_), ~cfg_ignore_switch(S),
    +cfge_nop(PIN,PDEF).
bld_cases(S,[default{ST}|TAIL],COND,_,PIN,POUT), ~cfg_ignore_switch(S),
    bld_stmt(ST,PT,_), +bld_cases(S,TAIL,COND,yes{PT},PIN,POUT).
bld_cases(S,[case{CMP,ST}|TAIL],COND,PDEF,PIN,POUT), ~cfg_ignore_switch(S),
    bld_stmt(ST,PT,_),
    cil_make_exp(CMP,"ctest",CTEST), cil_make_type(CMP,"ctyp",CTYP),
    +cil_type_int(CTYP,iint), +cil_type_x_bytes(CTYP,4),
    +cil_exp_binop(CTEST,b_eq,COND,CMP,CTYP),
    +branch_nest(CTEST,S),
    +cfge_base(PIN,PT,ebtrue{CTEST}),
    +cfge_base(PIN,p_cs{S,CMP},ebfalse{CTEST}),
    +bld_cases(S,TAIL,COND,PDEF,p_cs{S,CMP},POUT).

% loop statements

% connect the loop block output BOUT to its own input BIN,
% marking BIN as a loop head
cil_stmt_loop(S,BLK), bld_stmt(S,PIN,_), bld_block(BLK,BIN,BOUT),
    +cfge_nop(PIN,BIN), +cfge_nop(BOUT,BIN), +cfgn_base(BIN,nlooph{S}).

% block statements

cil_stmt_block(S,BLK), bld_stmt(S,PIN,POUT), bld_block(BLK,BIN,BOUT),
    +cfge_nop(PIN,BIN), +cfge_nop(BOUT,POUT).

% construct isets/iasms

cil_instr_set(I,_,_), bld_instr(I,P0,P1), +cfge_base(P0,P1,eset{I}).
cil_instr_asm(I,_),   bld_instr(I,P0,P1), +cfge_base(P0,P1,easm{I}).

% construct icalls

% keep track of how we handle each call to make sure we don't generate multiple
% edges on the same call
type ci_handler ::=
    ci_exit     % call terminates the program
  | ci_noret    % call does not return a value
  | ci_temp     % call assigns its return value to a temporary
  | ci_assign.  % call assigns its return value to a non-temporary lvalue
predicate call_handler(c_instr,ci_handler).

% calls to exit functions

% baked in exit_calls()
import "exitbaked.clp".

% augment with exit summaries from the database
prune_exit_calls(), dircall(_,F), exit_sum(F)->exit_fn(), +exit_call(F).

% direct calls to exit functions, point the call target to p_abort
prune_exit_calls(), dircall(I,F), exit_call(F),
    bld_instr(I,P0,_), +cfge_base(P0,p_abort,ecall{I}),
    +call_handler(I,ci_exit).

% calls to non-exit functions

% if there is no return value, just make the icall
cil_instr_call(I,_), ~call_handler(I,ci_exit), ~cil_instr_call_ret(I,_),
    bld_instr(I,P0,P1), +cfge_base(P0,P1,ecall{I}), +call_handler(I,ci_noret).

% if there is a temporary variable return value, just make the icall
cil_instr_call(I,_), ~call_handler(I,ci_exit), cil_instr_call_ret(I,RLV),
    cil_lval_var(RLV,RX,ROFF), cil_off_none(ROFF), cil_var_temporary(RX),
    bld_instr(I,P0,P1), +cfge_base(P0,P1,ecall{I}), +call_handler(I,ci_temp).

% if a call assigns into a non-temporary, then fabricate a new temporary,
% a call returning that temporary, and an assignment from the temporary to the
% 'real' return value
cil_instr_call(I,FNEXP), cil_instr_call_ret(I,CLV), lval_type(CLV,RTYP),
    cil_make_var(I,"rtmp",RTMP),
    tostring(I,IS), str_cat("__$",IS,RNAME), +cil_var_name(RTMP,RNAME,RTYP),
    cil_make_lval(I,"rlv",RLV), cil_make_offset(I,"roff",ROFF),
    +cil_lval_var(RLV,RTMP,ROFF), +cil_off_none(ROFF),
    cil_make_exp(I,"rexp",REXP), +cil_exp_lval(REXP,RLV),
    cil_make_instr(I,"rset",RSET), cil_make_instr(I,"rcall",RCALL),
    instr_nest(I,S), +instr_nest(RSET,S), +instr_nest(RCALL,S),
    +cil_instr_call_ret(RCALL,RLV),
    +call_handler(RCALL,ci_temp), bld_instr(I,P0,P1),
    +cil_instr_call(RCALL,FNEXP), +cil_instr_set(RSET,CLV,REXP),
    cil_instr_x_location(I,FILE,LINE),
    +cil_instr_x_location(RCALL,FILE,LINE),
    +cil_instr_x_location(RSET,FILE,LINE),
    +call_handler(I,ci_assign), +cil_var_temporary(RTMP),
    % now that everything's added, be sure there are no other handlers
    ~call_handler(I,ci_exit), ~call_handler(I,ci_temp),
    +cfge_base(P0,p_rp{I},ecall{RCALL}), +cfge_base(p_rp{I},P1,eset{RSET}),
    % move over all the arguments
    cil_instr_call_arg(I,N,AEXP), +cil_instr_call_arg(RCALL,N,AEXP).

% short circuiting nops

% for any nop PS->PT, replace PS with PT in any other nodes/edges
predicate omit_cfgn_nop(P:pp,N:cfg_node).
predicate omit_cfge_nop(P0:pp,P1:pp,E:cfg_edge).
cfge_nop(PS,PT), PS\=PT, cfgn_base(PS,N),
    +omit_cfgn_nop(PS,N), +cfgn_base(PT,N).
cfge_nop(PS,PT), PS\=PT, cfge_base(P,PS,E),
    +omit_cfge_nop(P,PS,E), +cfge_base(P,PT,E).

% find the set of reachable CFG nodes, in order to prune away unreachable
% code before loop splitting
predicate cfgn_reachable(pp).
cfgn_base(P, nentry), +cfgn_reachable(P).
cfgn_reachable(P0), cfge_base(P0,P1,_), +cfgn_reachable(P1).
% XXX: Do we really want the exit point if it's unreachable?
cfgn_base(P, nexit), +cfgn_reachable(P).

% compute the simplified CFG, removing nops and unreachable parts.
cfgn_base(P,N), ~omit_cfgn_nop(P,N), cfgn_reachable(P), +cfgn(P,N).
cfge_base(P0,P1,E), ~omit_cfge_nop(P0,P1,E), cfgn_reachable(P0), +cfge(P0,P1,E).

% identify degenerate infinite loops which don't contain any edges.
% TODO: not quite complete
predicate degenerate_infinite_loop(pp).
cfge_nop(P,P), +degenerate_infinite_loop(P).

% CFG finalization

% get client nodes from finalized nodes
cfgn_final(P,nentry), +entry(P).
cfgn_final(P,nexit), +exit(P).

% get client edges from finalized edges
cfge_final(P0,P1,easm{I}), +iasm(P0,P1,I).
cfge_final(P0,P1,eset{I}), +iset(P0,P1,I).
cfge_final(P0,P1,ecall{I}), +icall(P0,P1,I).
cfge_final(P0,P1,eloop{PH}), +iloop(P0,P1,PH).
cfge_final(P,P0,ebtrue{E}), cfge_final(P,P1,ebfalse{E}), +branch(P,P0,P1,E).

% isums

iloop(P0,P1,PH), +isum(P0,P1,s_loop{PH}).
icall(P0,P1,I), +isum(P0,P1,s_call{I}).
iasm(P0,P1,I), +isum(P0,P1,s_asm{I}).

icall(_,_,I), anycall(I,CFN,T), +isum_target(s_call{I},CFN,s_func,T).
iloop(_,_,I), cil_curfn(FN), +isum_target(s_loop{I},FN,s_loop{I},direct).

% exp/lval/offset usage points

% add usage points for iset LHS/RHS, branch conditions, icall args
iset(P,_,I), cil_instr_set(I,LV,E), +lval_point(LV,P), +exp_point(E,P).
branch(P,_,_,E), +exp_point(E,P).
icall(P,_,I), cil_instr_call(I,FNE), +exp_point(FNE,P).
icall(P,_,I), cil_instr_call_ret(I,LV), +lval_point(LV,P).
icall(P,_,I), cil_instr_call_arg(I,_,E), +exp_point(E,P).
iasm(P,_,I), cil_instr_asm_in(I,_,_,_,E), +exp_point(E,P).
iasm(P,_,I), cil_instr_asm_out(I,_,_,_,LV), +lval_point(LV,P).

% walk down and add usage points for nested expressions, lvalues and offsets
cil_exp_lval(E,LV), exp_point(E,P), +lval_point(LV,P).
cil_exp_addr(E,LV), exp_point(E,P), +lval_point(LV,P).
cil_exp_cast(E,CE,_), exp_point(E,P), +exp_point(CE,P).
cil_exp_unop(E,_,RE,_), exp_point(E,P), +exp_point(RE,P).
cil_exp_binop(E,_,LE,RE,_), exp_point(E,P), +exp_point(LE,P), +exp_point(RE,P).
cil_lval_var(LV,_,OF), lval_point(LV,P), +off_point(OF,P).
cil_lval_mem(LV,ME,OF), lval_point(LV,P), +exp_point(ME,P), +off_point(OF,P).
cil_off_field(OF,_,NOF), off_point(OF,P), +off_point(NOF,P).
cil_off_index(OF,E,NOF), off_point(OF,P), +exp_point(E,P), +off_point(NOF,P).

% point source locations

% get locations for all points which precede some operation. these follow
% from the source location directly pinned to the operation itself
iasm(P,_,I), cil_instr_x_location(I,FILE,LINE), +point_location(P,FILE,LINE).
iset(P,_,I), cil_instr_x_location(I,FILE,LINE), +point_location(P,FILE,LINE).
icall(P,_,I), cil_instr_x_location(I,FILE,LINE), +point_location(P,FILE,LINE).
iloop(P,_,PH), cil_stmt_x_location(PH,FILE,LINE), +point_location(P,FILE,LINE).
branch(P,_,_,E), branch_loc(E,FILE,LINE), +point_location(P,FILE,LINE).

% get endpoint locations, which have no outgoing edges.
cil_fundec_end_location(_,FILE,LINE), +point_location(p_abort,FILE,LINE),
    exit(P), +point_location(P,FILE,LINE).
degenerate_infinite_loop(P), cfgn_final(P,nlooph{PH}),
    cil_stmt_x_location(PH,FILE,LINE), +point_location(P,FILE,LINE).

point_location(p_lnext{PH},FILE,LINE) :- cil_stmt_x_location(PH,FILE,LINE).
point_location(p_lnexti{PH,P},FILE,LINE) :- cil_stmt_x_location(PH,FILE,LINE).
point_location(p_ltrec{PH},FILE,LINE) :- cil_stmt_x_location(PH,FILE,LINE).
point_location(p_lterm{PH,P},FILE,LINE) :- cil_stmt_x_location(PH,FILE,LINE).

% guess the function's end point if there is no cil_fundec_end_location.
% TODO: kludge, remove
cil_fundec_location(F,FILE,_), ~cil_fundec_end_location(F,_,_),
    \/cil_instr_x_location(_,_,LINE):int_max_all(LINE,MLINE),
    +point_location(p_abort,FILE,MLINE),
    exit(P), +point_location(P,FILE,MLINE).

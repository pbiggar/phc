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

% baked-in code-base specific information to use during memory analysis.
% imported directly by memory.clp

% linux

% special case 'reverse field' pointer arithmetic from container_of:
% (ptr - (int)&((type*)0)->field)
cil_exp_binop(E,b_minuspi,LE,RE,_),
    cil_exp_cast(LE,LCE,_),
    cil_exp_cast(RE,RCE,_), cil_exp_addr(RCE,LV), cil_lval_mem(LV,ME,OFF),
    cil_exp_cast(ME,CME,_), cil_exp_x_intval(CME,0),
    +omit_eval(_,E), ?eval(P,E,_,_), eval(P,LCE,trace{T},G0),
    trace_rev_offset(P,T,OFF,FT,G1), #and(G0,G1,G), +eval(P,E,trace{FT},G).

% get names for untyped hidden fields $comp__N
predicate str_hidden_field(in COMP:string,in N:int,FLD:string).
?str_hidden_field(COMP,N,_),
    (int_ge(N,0), tostring(N,NS);
     int_lt(N,0), int_neg(N,NN), tostring(NN,NNS), str_cat("neg",NNS,NS)),
    str_cat("$",COMP,S0), str_cat(S0,"$",S1), str_cat(S1,NS,FLD),
    +str_hidden_field(COMP,N,FLD).

% special case 'hidden field' pointer arithmetic: adding a fixed offset N
% to a structure pointer where N is negative or is larger than the size of
% the structure yields a hidden field for the comp type and offset
exp_psum(E,LE,RE),
    cil_exp_cast(LE,LCE,NTYP), exp_type(LCE,OTYP),
    ~(cil_exp_unop(RE,u_neg,RNE,_),
      cil_exp_cast(RNE,RCE,_), cil_exp_addr(RCE,_)),
    cil_type_ptr(NTYP,DNTYP), cil_type_ptr(OTYP,DOTYP),
    cil_type_x_bytes(DOTYP,WIDTH), cil_type_x_bytes(DNTYP,1),
    cil_exp_x_intval(RE,N), (int_lt(N,0); int_ge(N,WIDTH)),
    (cil_type_comp(DOTYP,C); ~cil_type_comp(DOTYP,_), C="void"),
    str_hidden_field(C,N,F),
    +omit_eval(_,E), ?eval(P,E,_,_), sum_body(SUM,P), eval(P,LE,trace{T},G),
    (generate_index_traces(), trace_simplify_index(SUM,fld{T,F,C},FT);
     ~generate_index_traces(), trace_simplify(SUM,fld{T,F,C},FT)),
    +eval(P,E,trace{FT},G).
exp_psum(E,LE,RE), cil_exp_cast(_,E,_),
    exp_type(LE,TYP), cil_type_ptr(TYP,DTYP), cil_type_comp(DTYP,C),
    cil_type_x_bytes(DTYP,N), cil_exp_x_intval(RE,RN),
    (RN=1; RN=2), int_mul(RN,N,NN), str_hidden_field(C,NN,F),
    +omit_eval(_,E), ?eval(P,E,_,_), sum_body(SUM,P), eval(P,LE,trace{T},G),
    (generate_index_traces(), trace_simplify_index(SUM,fld{T,F,C},FT);
     ~generate_index_traces(), trace_simplify(SUM,fld{T,F,C},FT)),
    +eval(P,E,trace{FT},G).

% linux and other systems occasionally cast pointers into integers to
% apply bitmasks and various other twiddling to them, typically to hide data
% in the lower bits or to force the pointer to a particular alignment.
% rather than understand exactly what's going on we just strip away the integer
% operations and evaluate to the core pointer/integer value within the exp
predicate arith_operator_cast(E:c_exp,BE:c_exp) order [E,BE].
arith_op(B), cil_exp_binop(CE,B,LE,RE,_),
    (cil_exp_cast(E,CE,TYP), cil_type_ptr(TYP,_); arith_operator_cast(E,CE)),
    (cil_exp_x_intval(LE,_), NE=RE;
     cil_exp_x_intval(RE,_), NE=LE;
     cil_exp_lval(RE,LV), cil_lval_var(LV,X,_), cil_var_name(X,"__per_cpu_offset",_), NE=LE),
    ~cil_exp_x_intval(NE,_), +arith_operator_cast(E,NE).
cil_exp_unop(CE,u_bnot,LE,_),
    (cil_exp_cast(E,CE,TYP), cil_type_ptr(TYP,_); arith_operator_cast(E,CE)),
    ~cil_exp_x_intval(LE,_),
    +arith_operator_cast(E,LE).
arith_operator_cast(E,CE), cil_exp_cast(CE,XCE,_), +arith_operator_cast(E,XCE).

arith_operator_cast(E,BE),
    ~cil_exp_cast(BE,_,_), ~cil_exp_binop(BE,_,_,_,_), ~cil_exp_unop(BE,_,_,_),
    +omit_eval(_,E), ?eval(P,E,_,_), eval(P,BE,V,G), +eval(P,E,V,G).

% understand __builtin_expect, which just returns its first argument
dircall(I,"__builtin_expect"), icall(P0,P1,I),
    cil_instr_call_arg(I,0,E), callret(I,S),
    #bool_g(false,FG), +inst_transfer_necessary(s_call{I},P0,root{S},FG),
    ?vmerge(P1,root{S},_,_), eval(P0,E,T,G), +vmerge(P1,root{S},T,G).

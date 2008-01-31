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

%import "./cilbase.clp".

predicate simplify(ORIG:c_exp, E:c_exp).
predicate non_simplified(E:c_exp).
predicate atomic_exp(in ORIG:c_exp, E:c_exp).
predicate pointer_exp(in ORIG:c_exp, E:c_exp).

cil_exp_cast(E, _, _), +non_simplified(E).
cil_exp_unop(E, _, _, _), +non_simplified(E).
cil_exp_binop(E,b_ne,_,_,_), +non_simplified(E).
cil_exp_binop(E,b_eq,_,_,_), +non_simplified(E).
cil_exp_binop(E, OP, _, _,_), logic_op(OP), +non_simplified(E).

%exp_binop(_, OP, _, _), op_string(OP, STR), +print("Op: ", STR).

cil_exp_cast(E,CE,_), +simplify(E, CE).
cil_exp_cast(_,CE,_), +simplify(CE, CE).
cil_exp_unop(E,_,RE,_), +simplify(E, RE).
cil_exp_binop(E,b_eq,LE,RE,_), +simplify(E, LE), +simplify(E, RE).
cil_exp_binop(E,b_ne,LE,RE,_), +simplify(E, LE), +simplify(E, RE).
cil_exp_binop(E, OP, LE, RE,_), logic_op(OP),  +simplify(E, LE), +simplify(E, RE).

simplify(OR, E), cil_exp_cast(E, CE,_), +simplify(OR, CE).
simplify(OR, E), cil_exp_unop(E, _, RE,_), +simplify(OR, RE).
simplify(OR, E), cil_exp_binop(E,b_eq,LE,RE,_), +simplify(OR, LE), +simplify(OR, RE).
simplify(OR, E), cil_exp_binop(E,b_ne,LE,RE,_), +simplify(OR, LE), +simplify(OR, RE).
simplify(OR, E), cil_exp_binop(E, OP, LE, RE,_), logic_op(OP),  +simplify(OR, LE), +simplify(OR, RE).

atomic_exp(OR, OR) :- ~simplify(OR, _).
atomic_exp(OR, E) :- simplify(OR, E), ~non_simplified(E).
pointer_exp(OR, E) :- atomic_exp(OR, E), exp_tptr(E).

%pointer_exp(EE, E), exp_string(EE, EE_STR), exp_string(E, STR), +print("ATOMIC EXP: ",  EE, EE_STR, E, STR).

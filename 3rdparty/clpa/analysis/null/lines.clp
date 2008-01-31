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

% ********************************
% Include this file if you want to map program points to line numbers
% in the actual source code. The source_line(P, LINE) predicate can be
% used to find the mapping between line numbers and program points 
% and to generate meaningful error messages.

% Program point P corresponds to line number LINE in the source code.
predicate source_line(P:pp, LINE:int).

% Program point P is in file FILE.
predicate source_file(P:pp, FILE:string).

% Program point P is in source code location LOC which identifies 
% the source location as line:file name (e.g "15:test.c").
predicate source_loc(P:pp, LOC:string).


iasm(P,_,I), cil_instr_x_location(I,FILE,LINE), +source_line(P, LINE), +source_file(P, FILE).
iset(P,_,I), cil_instr_x_location(I,FILE,LINE), +source_line(P, LINE), +source_file(P, FILE).
icall(P,_,I), cil_instr_x_location(I,FILE,LINE), +source_line(P, LINE), +source_file(P, FILE).
iloop(P,_,PH), cil_stmt_x_location(PH,FILE,LINE), +source_line(P, LINE), +source_file(P, FILE).
branch(P,_,_,E), branch_loc(E,FILE,LINE), +source_line(P, LINE), +source_file(P, FILE).
%point_location(P, FILE, LINE), +source_line(P, LINE), +source_file(P, FILE).


% add source locations
source_line(P, LINE), source_file(P, FILE), tostring(LINE, STR_LINE), str_cat(STR_LINE, ":", TEMP), str_cat(TEMP, FILE, LOC), 
+source_loc(P, LOC).

% for testing
%source_line(P, LINE), +print("Line number: ", P, LINE).
%source_file(P, FILE), +print("FILE: ", P, FILE).
%source_loc(P,LOC), +print("LOC: ", P, LOC).

%cil_stmt_x_location(S:c stmt,FILE:string,LINE:int)

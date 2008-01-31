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
% mustmod.clp 
%
% A simple must-mod analysis that attempts to determine when a trace
% was definitely modified by a summary.
%
% This file contains the glue between the mustmod data and the memory analysis.
%
%-----------------------------------------------------------------------------%

    % sum_mustmod(Fn, Sum)
session sum_mustmod(string, sum) containing [stmustmod].

    % stmustmod(T)
    % Trace T is necessarily modified by a summary. This is necessarily
    % a subset of the may-mod summaries.
predicate stmustmod(t_trace).

    % inst_mustmod(ISum, T)
    % Summary ISum must modify trace T
predicate inst_mustmod(sum, t_trace).

% -----------------------------------------------------------------------------

    % Values that are necessarily modified do not have their targets preserved
inst_transfer_necessary(ISum, P0, T, False) :-
    isum(P0, _, ISum),
    inst_mustmod(ISum, T),
    #bool_g(false, False).

% -----------------------------------------------------------------------------

    % Fetch mustmod data from the appropriate session
inst_mustmod(ISum, T) :-
    isum_target(ISum, Fn, FnSum, _), ~omit_exit_alias_summary(ISum),
    sum_mustmod(Fn, FnSum)->stmustmod(T).



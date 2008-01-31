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
%
% Live function inference analysis. Attempts to determine which functions
% in a program can be called which cannot.
%
% This file contains the externally visible session and predicate definitions. 
%
%-----------------------------------------------------------------------------%

    % sum_livecode(Function)
session sum_livecode(string) containing [live_fn, dead_fn].
    
type t_live_reason ::=
    l_root       % This is a callgraph root (from a baked-in list)
  | l_called     % This function is called from another live function
  | l_escaped    % This function's address is passed to a function we know 
                 % nothing about.
  | l_sighandler % This function is installed as a signal handler
  .
    
    % This function is live.
predicate live_fn(t_live_reason).

    % This function is dead.
predicate dead_fn().

%-----------------------------------------------------------------------------%

    % Is a function a root function?
predicate root_fn(in string).

%-----------------------------------------------------------------------------%


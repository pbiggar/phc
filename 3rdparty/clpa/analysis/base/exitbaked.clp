%%
% Authors:
%   Kenny Lau  <klau@cs.stanford.edu>
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

% baked in exit functions

% Add to exit_call() a list of functions that may not terminate the program
% but are generally expected to. prune_exit_calls() must still be added to
% actually generate the calls to p_abort
predicate use_may_exit_calls().

% While longjmp does not terminate the program, it will still never return
% to the invoking call site.
predicate use_longjmp_exit().

% Libc exit functions

+exit_call("exit").
+exit_call("_exit").
+exit_call("abort").
+exit_call("__assert_fail").

% The exec() family of functions only return if the command they invoked
% failed to execute
use_may_exit_calls(), +exit_call("execl"), +exit_call("execlp"),
    +exit_call("execle"), +exit_call("execv"), +exit_call("execvp").

use_longjmp_exit(), +exit_call("longjmp").

% Histar exit functions
+exit_call("panic").
+exit_call("thread_halt").
+exit_call("process_exit").
+exit_call("utrap_ret").
use_longjmp_exit(), +exit_call("jos_longjmp"), +exit_call("stack_switch").



% linux exit functions

% exit functions used by the NULL analysis
predicate use_null_exit().

use_null_exit(), +exit_call("fatal"), +exit_call("packet_disconnect"), 
+exit_call("yy_fatal_eror"), +exit_call("smb_panic"),
+exit_call("exit_server"), +exit_call("cgi_setup_error"),
+exit_call("db_return"), +exit_call("db_longjmp"), +exit_call("msg_panic"),
+exit_call("msg_fatal"), +exit_call("msg_fatal_status"), +exit_call("error"),
+exit_call("yy_fatal_error"), +exit_call("_bfd_abort"), +exit_call("panic").

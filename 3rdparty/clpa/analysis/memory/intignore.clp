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

% Dumb as dirt modelling of integer operations

% Operations defined here and in other int modelling programs are:
% exp_const
% exp_unop and exp_binop where the op is not logic_op or pointer_op
% exp_cast with int result
% boolean evaluation of integer expressions

import "traces.clp".
import "../base/cilcfg.clp".

% ANALYSIS REPRESENTATIONS

import "memory.clp".

% int representation, result of evaluating some exp E at P
type t_nrep ::= unint{P:pp,E:c_exp}.

% guards are either uninterpreted ints or are unconstrained bits from upstream
% analyses
type g_bit ::=
    ar_int{t_nrep}
  | ar_path{pp,pp}
  | ar_entry{pp,t_trace,t_trace}
  | ar_exit{sum,pp,t_trace,t_trace}.

% RULES

% implement satisfiability predicates for upstream analyses
% note that asn_value will always fail if this file is used
type g_guard_asn = bval_asn[g_bit].
guard_sat(G) :- #sat(G).
guard_sat_asn(G,ASN) :- #satasn(G,ASN).
guard_valid(G) :- #not(G, NG), ~#sat(NG).
asn_guard(ASN,G) :- #asng(ASN,G).

% implement unconstrained bits for upstream analyses
path_bit(P0,P1,G) :- #id_g(ar_path{P0,P1},G).
entry_bit(P,S,T,G) :- #id_g(ar_entry{P,S,T},G).
exit_bit(SUM,P,S,T,G) :- #id_g(ar_exit{SUM,P,S,T},G).

% implement unconstrained values for upstream analyses
+unconstrained_nrep(P,E,unint{P,E}).
unconstrained_cond(P,E,G) :- #id_g(ar_int{unint{P,E}},G).

% nrep sign/length
nrep_bits(unint{_,E},S,LEN) :- exp_type(E,TYP), type_bits(TYP,S,LEN).

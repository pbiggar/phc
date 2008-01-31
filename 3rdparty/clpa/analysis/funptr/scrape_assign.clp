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

% scrape information off functions that more sophisticated analyses choke on

import "../memory/traces.clp".
analyze session_name("cil_body").
analyze analysis_name("scrape_assign").

% scrape assignments of global addresses to particular fields,
% adding composite type invariants
cil_instr_set(_,LV,E),
    lval_field(LV,F,CNAME), cil_field_name(F,FNAME,PTYP,_,_),
    cil_type_ptr(PTYP,FTYP), cil_type_func(FTYP,_,_),
    cil_exp_addr(E,RLV), cil_lval_var(RLV,X,OFF), cil_off_none(OFF),
    cil_var_global(X), cil_var_name(X,GNAME,_),
    RS=fld{empty,FNAME,CNAME}, RT=root{glob{GNAME}},
    +sum_comp(CNAME)->sxpoints(RS,RT),
    trace_string(RS,RSS), trace_string(RT,RTS),
    +str_comp_spoints(CNAME,RSS,RTS).

% scrape assignments between function pointer fields of different structures,
% adding composite type invariants based on any source sxpoints
cil_instr_set(_,LV,E),
    lval_field(LV,F,CNAME), cil_field_name(F,FNAME,PTYP,_,_),
    cil_type_ptr(PTYP,FTYP), cil_type_func(FTYP,_,_),
    cil_exp_lval(E,ELV), lval_field(ELV,EF,ECNAME), cil_field_name(EF,EFNAME,_,_,_),
    sum_comp(ECNAME)->sxpoints(fld{empty,EFNAME,ECNAME},root{glob{GNAME}}),
    RS=fld{empty,FNAME,CNAME}, RT=root{glob{GNAME}},
    +sum_comp(CNAME)->sxpoints(RS,RT),
    trace_string(RS,RSS), trace_string(RT,RTS),
    +str_comp_spoints(CNAME,RSS,RTS).

?- str_comp_spoints(C,S,T).

import "../intbvec.clp".
analyze session_name("cil_body").

predicate failure(P:pp,I:c_instr,ASN:bval_asn[g_bit]).

predicate failed_assert(LINE:int).
predicate cexample(LINE:int,T:t_root,N:int).
predicate correct(LINE:int).

icall(P,_,I), dircall(I,"assert"), cil_instr_call_arg(I,0,E),
        beval(P,E,BG,WG), guard(P,GG), #not(BG,FG), #and(FG,WG,TG0), #and(TG0,GG,TG), #satasn(TG,ASN), +failure(P,I,ASN).

failure(_,I,_), cil_instr_x_location(I,_,LINE), +failed_assert(LINE).
failure(P,I,ASN), ?val(P,root{S},_,_), val(P,root{S},T,_), trace_nrep(T,BV), #asnbv(ASN,BV,N), cil_instr_x_location(I,_,LINE), +cexample(LINE,S,N).

using intops.

% specific rules for test.c
cexample(204,arg{0},NA), cexample(204,arg{1},NB), int_gt(NA,NB), +correct(204).
cexample(205,arg{0},NA), cexample(205,arg{1},NB), int_eq(NA,NB), +correct(205).
cexample(206,arg{0},NA), cexample(206,arg{1},NB), int_ge(NA,NB), int_add(NB,10,NP), int_le(NA,NP), +correct(206).

cexample(304,arg{0},NA), cexample(304,local{"x"},NX), cexample(304,local{"y"},NY), int_ne(NA,NX), int_eq(NA,NY), +correct(304).

?- failed_assert(LINE).
?- cexample(LINE,T,_).
?- correct(LINE).

import "../scalar_sat.clp".
analyze session_name("cil_body").

+ignore_int_casts().

predicate failed(LINE:int).
?- failed(LINE).

icall(P,_,I), dircall(I,"assert"), cil_instr_call_arg(I,0,E),
    beval(P,E,BG,WG), guard(P,GG), #not(BG,FG), #and(FG,WG,TG0), 
    #and(TG0,GG,TG), guard_sat(TG),
    point_location(P,_,LINE), +failed(LINE).

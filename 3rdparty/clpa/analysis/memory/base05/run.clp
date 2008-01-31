import "../intbvec.clp".

analyze session_name("cil_body").

+split_loops().
+ignore_int_casts().

predicate escaped(string,string,t_trace,t_trace,Y:access_type).
?- escaped(CALLER,CALLEE,T,CT,Y).

predicate check_escaped(string,string,t_trace).
cil_curfn(FN), check_escaped(FN,CALLEE,T), dircall(I,CALLEE),
    icall(P,_,I), td_inst_trace(s_call{I},P,T,CT,_),
    inst_may_access(s_call{I},CT,Y),
    +escaped(FN,CALLEE,T,CT,Y).

+check_escaped("escape_fn","escape_call",drf{root{arg{0}}}).
+check_escaped("sideeffect_fn","sideeffect_call",root{local{"la"}}).
+check_escaped("sideeffect_fn","sideeffect_call",root{local{"lb"}}).
+check_escaped("multi_fn","multi_call",root{local{"local"}}).
+check_escaped("castint_fn","castint_call",drf{root{arg{0}}}).
+check_escaped("cast2_fn","cast2_call",drf{root{arg{0}}}).
+check_escaped("cast3_fn","cast3_call",drf{root{arg{0}}}).
+check_escaped("uninit_fn","uninit_call",drf{root{local{"p"}}}).
+check_escaped("struct_fn","struct_call",drf{fld{drf{root{arg{0}}},"x","foo"}}).
+check_escaped("struct_fn","struct_call",fld{drf{root{arg{0}}},"x","foo"}).
+check_escaped("struct_fn","struct_call",fld{root{local{"local"}},"x","foo"}).
+check_escaped("xstruct_fn","struct_call",drf{fld{drf{root{arg{0}}},"x","foo"}}).
+check_escaped("xstruct_fn","struct_call",fld{drf{root{arg{0}}},"x","foo"}).
+check_escaped("xstruct_fn","struct_call",fld{root{local{"local"}},"x","foo"}).
+check_escaped("inter_fn","inter_call2",drf{drf{root{arg{0}}}}).
+check_escaped("inter_fn","inter_call2",drf{drf{root{arg{1}}}}).

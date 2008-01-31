import "../aliasing_traceusemod.clp".

?omit_comp_spoints(C,SUM,STR,S,T), ~trace_sub(T,STR,_),
    ~add_filt_points(_,fn_entry,S,T,_), +omit_comp_spoints(C,SUM,STR,S,T).

%?drop_spoints(SUM,POS,S,T), trace_type(SUM,T,y_func),
%    +drop_spoints(SUM,POS,S,T).

?drop_spoints(SUM,POS,S,T), trace_type(SUM,S,Y),
    ~equal(Y,y_ptr{_}), ~equal(Y,y_array{y_ptr{_},_}),
    +drop_spoints(SUM,POS,S,T).

?drop_spoints(SUM,POS,S,T),
    trace_fld_sub(S,STR,_), trace_fld_sub(T,STR,_),
    +drop_spoints(SUM,POS,S,T).

?- str_spoints(FN,PH,POS,S,T).
?- str_comp_spoints(C,S,T).
?- str_glob_spoints(G,S,T).

import "loops.clp".
analyze session_name("cil_sum_body").

predicate pp_paths(in P:pp,N:int) succeeds [once].

predicate pp_paths_list(in PLIST:list[pp],N:int).
+pp_paths_list([],0).
pp_paths_list([P|TAIL],N) :-
    pp_paths(P,PN), pp_paths_list(TAIL,TN), int_add(PN,TN,N).

pp_paths(P,1) :- sum_bound(_,P,_).
pp_paths(P,N) :- ~sum_bound(_,P,_),
    \/cfge_final(XP,P,_):list_all(XP,PLIST), pp_paths_list(PLIST,N).

predicate counts(FN:string,SUM:sum,BRANCHES:int,PATHS:int).
?- counts(FN,SUM,BRANCHES,PATHS).

cil_curfn(FN), cil_cursum(SUM),
    \/branch(P,_,_,_):count_all(P,BRANCHES),
    \/sum_bound(SUM,_,XP):list_all(XP,PLIST), pp_paths_list(PLIST,PATHS),
    +counts(FN,SUM,BRANCHES,PATHS).

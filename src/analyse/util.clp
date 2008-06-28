% The repository for general functions which dont otherwise have a home.

import "3rdparty/clpa/analysis/base/utility.clp".

predicate get_method_name (in METHOD:t_Method, out NAME:string) succeeds [once].
get_method_name (METHOD, METHOD_NAME) :- 
	METHOD = method{_, signature{_, _, _, mETHOD_NAME{_, METHOD_NAME}, _}, _}.


% Flatten a list of lists into a single list
predicate flatten (in list[list[A]], out list[A]) succeeds [once].
flatten ([], []) :- .
flatten ([H|T], OUT) :- flatten (T, TS), list_append (H, TS, OUT).

% Concatenate STR to itself COUNT times.
predicate str_times (in COUNT:int, in STR:string, out OUT:string) succeeds [once].
str_times (COUNT, STR, "") :- int_le (COUNT, 0).
str_times (COUNT, STR, OUT) :- 
	int_gt (COUNT, 0), 
	str_cat (str_times (COUNT - 1, STR), STR, OUT).

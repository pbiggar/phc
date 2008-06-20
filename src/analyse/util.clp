import "3rdparty/clpa/analysis/base/utility.clp".

predicate get_method_name (in METHOD:t_Method, out NAME:string) succeeds [once].
get_method_name (METHOD, METHOD_NAME) :- 
	METHOD = method{_, signature{_, _, _, mETHOD_NAME{_, METHOD_NAME}, _}, _}.

import "cfg.clp".
import "util.clp".

session optimized ().

% After optimization, the program is split into methods. (The name 'method'
% is used).
predicate method_out (METHOD_NAME:string, METHOD:t_Method).


type var_info ::= var_name{string}
					 | var_bottom.

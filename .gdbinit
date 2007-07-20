b phc_internal_error(char const*, ...)
b phc_internal_error(char const*, String*, int, ...)
b phc_internal_error(char const*, AST_node*, ...)
b phc_error(char const*, ...)
b phc_error(char const*, String*, int, ...)
b phc_error(char const*, AST_node*, ...)
define ast
	print debug_hash (EG(active_symbol_table))
end
b sighandler

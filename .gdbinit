b phc_internal_error(char const*, ...)
b phc_internal_error(char const*, String*, int, ...)
b phc_internal_error(char const*, AST_node*, ...)
b phc_error(char const*, ...)
b phc_error(char const*, String*, int, ...)
b phc_error(char const*, AST_node*, ...)
define ast
	print ht_debug (EG(active_symbol_table))
end
define gst
	print ht_debug (&EG(symbol_table))
end

b sighandler

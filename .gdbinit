set breakpoint pending on

b phc_internal_error(char const*, ...)
b phc_internal_error(char const*, AST::Node*, ...)
b phc_internal_error(char const*, HIR::Node*, ...)
b phc_internal_error(char const*, LIR::Node*, ...)
b phc_internal_error(char const*, MICG::Node*, ...)
b phc_internal_error(char const*, MIR::Node*, ...)
b phc_internal_error(char const*, String*, int, int, ...)
b phc_internal_error(char const*, __va_list_tag*, String*, int, int)
b phc_error(char const*, ...)
b phc_error(char const*, AST::Node*, ...)
b phc_error(char const*, HIR::Node*, ...)
b phc_error(char const*, LIR::Node*, ...)
b phc_error(char const*, MICG::Node*, ...)
b phc_error(char const*, MIR::Node*, ...)
b phc_error(char const*, String*, int, int, ...)
b phc_error(char const*, __va_list_tag*, String*, int, int)


define ast
	print ht_debug (EG(active_symbol_table))
end
define gst
	print ht_debug (&EG(symbol_table))
end

#b sighandler
set print object

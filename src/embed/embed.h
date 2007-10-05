#include "AST.h"

class PHP
{
	private:
		static bool is_started;
		
	public:
		static void startup_php ();
		static void shutdown_php ();
		static AST::AST_literal* convert_token (AST::AST_literal* token);
		static unsigned long get_hash (String* string);
};

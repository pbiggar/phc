#include "AST.h"

class PHP
{
	private:
		static bool is_started;
		
	public:
		static void startup_php ();
		static void shutdown_php ();
		static AST_literal* convert_token (AST_literal* token);
};

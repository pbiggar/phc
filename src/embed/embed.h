#include "AST.h"

class PHP
{
	private:
		static bool is_started;
		
	public:
		static bool is_available ();
		static void startup_php ();
		static void shutdown_php ();
		static AST::Literal* convert_token (AST::Literal* token);
		static unsigned long get_hash (String* string);
};

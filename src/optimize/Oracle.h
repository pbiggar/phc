/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Optimization oracle acts as a go-between for the Optimization passes and
 * Embed.
 */
 

#ifndef PHC_ORACLE
#define PHC_ORACLE

#include "MIR.h"
#include "embed/embed.h"
#include "Method_info.h"
#include "Class_info.h"

// The optimization oracle. This is a layer between the PHP:: embed functions
// and the optimizer, in order to allow the optimizer update the information.
class Oracle : virtual public GC_obj
{
private:
	Oracle ();
	static Map<string, Method_info*> methods;
	static Map<string, Class_info*> classes;
public:

	static void initialize (MIR::PHP_script*);

	/*
	 * Methods
	 */

	static void add_method_info (Method_info* info);
	static void add_method_alias (String* original, String* alias);
	static Method_info_list* get_all_methods ();

	// Returns NULL if the method_info is not found.
	static Method_info* get_method_info (String* name);

	// Returns NULL if the method_info is not found, or is not a uer_method_info
	static User_method_info* get_user_method_info (String* name);

	static bool is_pure_function (MIR::METHOD_NAME* method_name);

	/*
	 * Classes
	 */

	static void add_class_info (Class_info* info);
	static void add_class_alias (String* original, String* alias);
	static Class_info* get_class_info (String* name);
	static Class_info_list* get_all_classes ();
	static User_class_info* get_user_class_info (String* name);
};

#endif // PHC_ORACLE

/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replaces an include statement with the parsed contents of the included file.
 * 
 */

#include <libgen.h> // for dirname
#include <iostream>
#include <fstream>
#include "Process_includes.h"
#include "AST_visitor.h"
#include "AST.h"
#include "lib/error.h"
#include "src/codegen/fresh.h"
#include "parsing/parse.h"
#include "process_ast/PHP_unparser.h"

/*
 * The include functionality is described in http://php.net/include/. 
 *
 * We support:
 * - include statements whose parameter must be a literal string
 * - the included file being in the current directory or the directory
 *	  containing the file being parsed
 * 
 * 
 * We don't support:
 * - return statements in the included file
 * - the '$val = include('my_file.php');' construct
 * - get_included_files()
 * - proper error messages. If it fails, we leave in the include statement
 * - using include_path to get the correct include path
 *
 * TODO
 * - return statements and the complications they entail
 *
 * We intend to support in the future (but probably in the IR):
 * - include statements whose parameter can be derived using constant
 *   propegation or other dataflow analysis
 * - Run-time inclusion
 * - Remote compile-time or run-time inclusion
 */

/* These statements are culled from the manuals.
 *
 * Any variables available at that line in the calling file will be
 * available within the called file, from that point forward.
 *
 * However, all functions and classes defined in the included file have
 * the global scope.
 *
 * If the include occurs inside a function within the calling file, then all of
 * the code contained in the called file will behave as though it had been
 * defined inside that function. So, it will follow the variable scope of that
 * function.
 *
 * - We put the code directly inside the calling function, which handles all these cases.
 *
 * Because include() and require()  are special language constructs, you
 * must enclose them within a statement block if it's inside a conditional
 * block.
 *  - This is handled automatically by the parser
 *
 * $bar is the value 1 because the include was successful. Notice the
 * difference between the above examples. The first uses return() within the
 * included file while the other does not. If the file can't be included, FALSE
 * is returned and E_WARNING is issued.
 * - We dont support this. The warning is left to the run-time.
 *
 * Handling Returns: It is possible to execute a return()  statement
 * inside an included file in order to terminate processing in that file and
 * return to the script which called it. Also, it's possible to return values
 * from included files. You can take the value of the include call as you would
 * a normal function. This is not, however, possible when including remote
 * files unless the output of the remote file has valid PHP start and end tags
 * (as with any local file). You can declare the needed variables within those
 * tags and they will be introduced at whichever point the file was included.
 *  - TODO We'll handle returns in the IR, since the IR has goto, which these
 *         really need. Also, contructs like '$a =
 *         do_something(do_something_else(include('myfile.php')))' are easy to
 *         support in the IR and nasty to support in the AST.
 *
 * If there are functions defined in the included file, they can be used in the
 * main file independent if they are before return() or after. If the file is
 * included twice, PHP 5 issues fatal error because functions were already
 * declared, while PHP 4 doesn't complain about functions defined after
 * return(). It is recommended to use include_once() instead of checking if the
 * file was already included and conditionally return inside the included file.
 *  - Redefined functions and classes lead to an error. However, there may be
 *    some bugs in this, which cant really be resolved without data flow.
 *    Include_once at your peril.
 */ 

// TODO add tests for each warning and error
// - include_once fails incorrectly
// - include_once fails correctly

class Return_check : public AST_visitor
{
public:
	bool found;

	Return_check()
	{
		found = false;
	}

	// Avoid looking in any defined functions
	void children_method (AST_method* in)
	{
		// deliberately empty
	}

	void pre_return(AST_return* in)
	{
		found = true;
	}
};

/* Transform
 *   $x = include "a"; // where "a.php" has the line "return 7";
 * into
 *	  ... // included file lines
 *   $x = 7;
 *	  goto TIG1;
 *   ...; // ore included lines
 *   TIG1:
 */
class Return_transform : public AST_transform
{
public:

	// The label to jump to
	AST_label* label;

	// The variable to be set before jumping
	AST_variable* variable;

	Return_transform (AST_label* label, AST_variable* variable = NULL)
	: label (label),
	  variable (variable)
	{
	}

	// Avoid looking in any defined functions
	void children_method (AST_method* in)
	{
		// deliberately empty
	}

   void pre_return (AST_return* in, List<AST_statement*>* out)
	{
		// return 7; => $x = 7;
		if (variable and in->expr)
			out->push_back (new AST_eval_expr (
						new AST_assignment (
							variable->clone(), 
							false, // we only work on the outer function,
									 // so return cant be by reference
							in->expr)));

		// goto TIG;
		out->push_back (new AST_goto (label->label_name->clone ()));
	}
};

Process_includes::Process_includes (bool definitive, String* pass_name, Pass_manager* pm)
: definitive (definitive),
  pass_name (pass_name),
  pm (pm)
{
}

// look for include statements
void Process_includes::pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	Wildcard<Token_method_name>* method_name = new Wildcard<Token_method_name>;
	Wildcard<AST_expr>* expr_filename = new Wildcard<AST_expr>;

	// the filename is the only parameter of the include statement
	AST_method_invocation* pattern = new AST_method_invocation(
			NULL,
			method_name,
			new List<AST_actual_parameter*> (new AST_actual_parameter (false, expr_filename))
			);

	AST_assignment* agn_pattern = new AST_assignment (
		new Wildcard<AST_variable>, false, pattern);

	// TODO there is obviously a difference between these forms. In
	// particular, the once_ versions actually do something
	// different. Make tests to demonstrate, then fix.
	if ((in->expr->match (pattern) or in->expr->match (agn_pattern))
		and (*(method_name->value->value) == "include" 
			or *(method_name->value->value) == "include_once"
			or *(method_name->value->value) == "require"
			or *(method_name->value->value) == "require_once"))
	{
		Token_string* token_filename = dynamic_cast<Token_string*> (expr_filename->value);
		if (token_filename == NULL)
		{
			if (definitive)
				phc_warning("File with variable filename could not be included, and will be included at run-time", in);

			out->push_back(in);
			return;
		}

		String* filename = token_filename->value;

		// Set up search directory
		List<String*>* dirs = new List<String*>();

		// If the included file starts with "./" or "../", use empty search path
		// Otherwise, pass in dirname(filename) as the search path
		if(filename->substr(0, 2) != "./" && filename->substr(0, 3) != "../")
		{
			char* directory_name = strdup(in->get_filename()->c_str());
			directory_name = dirname(directory_name);
			dirs->push_back(new String(directory_name));
		}

		// Try to parse the file
		AST_php_script* php_script = parse(filename, dirs, false);
		if(php_script == NULL)
		{
			// Script could not be found or not be parsed; leave the include in
			if (definitive)
				phc_warning("File %s could not be included, and will be included at run-time", in, filename->c_str());

			out->push_back(in);
			return;
		}

		// We don't support returning values from included scripts; 
		// issue a warning and leave the include as-is
		Return_check rc;
		rc.visit_statement_list (php_script->statements);
		if(rc.found)
		{
			if (definitive)
			{
				AST_label* label = fresh_label ();
				php_script->transform_children (new Return_transform (label));
				out->push_back (label);
			}
			else
			{
				// Dont issue a warning, as it will be included next time
				out->push_back(in);
				return;
			}
		}

		// bring the statements to the expected level of the IR
		pm->run_until (pass_name, php_script);

		// copy the statements
		out->push_back_all(php_script->statements);
	}
	else
		out->push_back(in);
}

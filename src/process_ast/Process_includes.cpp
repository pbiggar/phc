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
#include "process_ir/General.h"
#include "process_ir/fresh.h"
#include "parsing/parse.h"

using namespace AST;

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

class Return_check : public Visitor
{
public:
	bool found;

	Return_check()
	{
		found = false;
	}

	// Avoid looking in any defined functions
	void children_method (Method* in)
	{
		// deliberately empty
	}

	void pre_return(Return* in)
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
class Return_transform : public Transform
{
public:

	// The label to jump to
	Label* label;

	// The variable to be set before jumping
	Variable* variable;

	Return_transform (Label* label, Variable* variable = NULL)
	: label (label),
	  variable (variable)
	{
	}

	// Avoid looking in any defined functions
	void children_method (Method* in)
	{
		// deliberately empty
	}

   void pre_return (Return* in, List<Statement*>* out)
	{
		// return 7; => $x = 7;
		if (variable and in->expr)
			out->push_back (new Eval_expr (
						new Assignment (
							variable->clone(), 
							false, // we only work on the outer function,
									 // so return cant be by reference
							in->expr)));

		// goto TIG;
		out->push_back (new Goto (label->label_name->clone ()));
	}
};

Process_includes::Process_includes (bool hir, String* pass_name, Pass_manager* pm, String* name)
: hir (hir),
  pass_name (pass_name),
  pm (pm)
{
	this->name = name;
	this->description = new String ("Insert included and required files into the AST");
}

bool Process_includes::pass_is_enabled (Pass_manager* pm)
{
	// We need to use the pass to tidy up the include for the HIR, even if we
	// dont have --include set.
	return true;
}


void Process_includes::do_not_include (const char* warning, Eval_expr* in, List<Statement*>* out, Actual_parameter* param)
{
	// TODO bring this back
#if 0
	if (hir && warning)
		phc_warning("File %s could not be included, and will be included at run-time", warning, in);

	/* Convert
	 *			include ("myfile.php"); 
	 *		or include (t());
	 *	into
	 *			$T1 = "myfile.php";
	 *			include $T1;
	 *		or	$T2 = t() ;
	 *			include $2;
	 *
	 * for future HIR.
	 */
	if (hir && param->expr->classid () != Variable::ID)
	{
		// This was set in Annotate.
		param->expr->attrs->erase ("phc.ast_lower_expr.no_temp");
		param->expr = eval (param->expr);
		pieces->push_back (in); // only works after control flow is lowered
	}
	else
#endif
	out->push_back (in);
}



/* If it matches, return the filename, else return NULL. If warn is passed,
 * warn if an include statement is found, but using an expression, not a
 * string. */
Actual_parameter* matching_param (Eval_expr* in, List<Statement*>* out) 
{ 

	// the filename is the only parameter of the include statement
	Wildcard<Actual_parameter>* param = new Wildcard<Actual_parameter>;
	Wildcard<METHOD_NAME>* method_name = new Wildcard<METHOD_NAME>;
	Method_invocation* pattern = new Method_invocation(
			NULL,
			method_name,
			new List<Actual_parameter*> (param)
			);

	Assignment* agn_pattern = new Assignment (
		new Wildcard<Variable>, false, pattern);

	// TODO there is obviously a difference between these forms. In
	// particular, the _once versions actually do something
	// different. Make tests to demonstrate, then fix.
	if ((in->expr->match (pattern) or in->expr->match (agn_pattern))
		and (*(method_name->value->value) == "include" 
			or *(method_name->value->value) == "include_once"
			or *(method_name->value->value) == "require"
			or *(method_name->value->value) == "require_once"))
	{
		return param->value;
	}

	return NULL;
}

String* get_filename_from_param (Actual_parameter* param)
{
	STRING* token_filename = dynamic_cast<STRING*> (param->expr);
	if (token_filename != NULL)
		return token_filename->value;
	return NULL;
}

List<String*>* get_search_directories (String* filename, Node* in)
{
	List<String*>* dirs = new List<String*>();
	// TODO get include path from PHP and allow path to be provided at compile time

	// If the included file starts with "./" or "../", use empty search path.
	// Otherwise, pass in the current working directory as the search path
	if(filename->substr(0, 2) != "./" && filename->substr(0, 3) != "../")
	{
		char* cwd = strdup(in->get_filename()->c_str());
		cwd = dirname (cwd);
		dirs->push_back (new String (cwd));
	}

	return dirs;
}

// look for include statements
void Process_includes::pre_eval_expr(Eval_expr* in, List<Statement*>* out)
{
	// check if its an include function
	Actual_parameter* param = matching_param (in, out);
	if (param == NULL)
	{
		out->push_back (in);
		return;
	}

	if (not pm->args_info->include_given)
	{
		do_not_include (NULL, in, out, param);
		return;
	}

	// check the parameter is a string
	String* filename = get_filename_from_param (param);
	if (filename == NULL)
	{
		do_not_include ("with unknown filename", in, out, param);
		return;
	}

	// Set up search directory
	List<String*>* dirs = get_search_directories (filename, in);

	// Try to parse the file
	PHP_script* ast = parse(filename, dirs);

	// Script could not be found or not be parsed; leave the include in
	if (ast == NULL)
	{
		// warn even if this isnt the hir, since the file wont magically appear later.
		do_not_include (filename->c_str (), in, out, param);
		return;
	}

	// We don't support returning values from included scripts; 
	// issue a warning and leave the include as-is
	Return_check rc;
	rc.visit_statement_list (ast->statements);
	if(rc.found)
	{
		if (hir)
		{
			assert (0); // TODO re-enable
//			Label* label = fresh_label ();
//			ast->transform_children (new Return_transform (label));
//			out->push_back (label);
		}
		else
		{
			// no warning; we'll get it next time.
			do_not_include (NULL, in, out, param);
			return;
		}
	}

	// bring the statements to the expected level of the IR
	pm->run_until (pass_name, ast);

	// copy the statements
	out->push_back_all(ast->statements);
}

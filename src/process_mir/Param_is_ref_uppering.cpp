/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 *  Replace param_is_ref with calls to ReflectionFunction.
 */

#include "Param_is_ref_uppering.h"
#include "MIR_to_AST.h"
#include "process_ir/General.h"

using namespace MIR;

/* Convert
 *	
 *		$T = param_is_ref ($target, $method_name, $index);
 *
 *	into
 *
 *		// NULL target
 *		$T1 = new ReflectionFunction ($method_name);
 *		$T2 = $T1->getParameters ();
 *		$T3 = $T2[$index];
 *		$t = $T3->isPassedByReference ();
 *
 *	or
 *
 *		// Class name target
 *		$T1 = new ReflectionClass ($class_name);
 *		$T2 = $T1->getMethod ($method_name);
 *		$T3 = $T2->getParameters ();
 *		$T4 = $T3[$index];
 *		$t = $T4->isPassedByReference ();
 *
 *	or
 *
 *		// Variable target
 *		$T1 = new ReflectionObject ($target);
 *		$T2 = $T1->getMethod ($method_name);
 *		$T3 = $T2->getParameters ();
 *		$T4 = $T3[$index];
 *		$t = $T4->isPassedByReference ();
 */
void
Param_is_ref_uppering::pre_assign_var (MIR::Assign_var* in, MIR::Statement_list* out)
{
	Wildcard<VARIABLE_NAME>* lhs = new Wildcard<VARIABLE_NAME>;
	Wildcard<Param_is_ref>* param_is_ref = new Wildcard<Param_is_ref>;

	if (in->match (
		new Assign_var (
			lhs,
			false, /* dont-care */
			param_is_ref)))
	{
		if (param_is_ref->value->target == NULL)
		{
			VARIABLE_NAME* function_temp = fresh_var_name ("Tpuf");
			VARIABLE_NAME* parameter_temp = fresh_var_name ("Tpup");
			VARIABLE_NAME* index_temp = fresh_var_name ("Tpui");

			(*out
			 << "$" << function_temp << " = new ReflectionFunction (\"" << param_is_ref->value->method_name << "\");"
			 << "$" << parameter_temp << " = $" << function_temp << "->getParameters ();"
			 << "$" << index_temp << " = $" << parameter_temp << "[" << param_is_ref->value->param_index->value << "];"
			 << "$" << lhs->value << " = $" << index_temp << "->isPassedByReference ();").finish (in);
		}
		else if (VARIABLE_NAME* target = dynamic_cast<VARIABLE_NAME*> (param_is_ref->value->target))
		{
			VARIABLE_NAME* object_temp = fresh_var_name ("Tpuo");
			VARIABLE_NAME* method_temp = fresh_var_name ("Tpum");
			VARIABLE_NAME* parameter_temp = fresh_var_name ("Tpup");
			VARIABLE_NAME* index_temp = fresh_var_name ("Tpui");

			(*out
			 << "$" << object_temp << " = new ReflectionObject ($" << target << ");"
			 << "$" << method_temp << " = $" << object_temp << "->getMethod (\"" << param_is_ref->value->method_name << "\");"
			 << "$" << parameter_temp << " = $" << method_temp << "->getParameters ();"
			 << "$" << index_temp << " = $" << parameter_temp << "[" << param_is_ref->value->param_index->value << "];"
			 << "$" << lhs->value << " = $" << index_temp << "->isPassedByReference ();").finish (in);
		}
		else
			// TODO: class target
			assert (0);
	}
	else
		out->push_back (in);
}

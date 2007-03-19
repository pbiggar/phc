/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "AST.h"

extern "C" void process_ast(AST_php_script* php_script)
{
	List<AST_class_def*>::const_iterator ci;
	List<AST_member*>::const_iterator mi;
	List<AST_statement*>::const_iterator si;
	
	AST_method* method;
	AST_eval_expr* eval_expr;
	AST_method_invocation* invoc;
	
	int num_function_calls = 0;
	
	// Inspect all classes
	for(
	   ci = php_script->class_defs->begin(); 
	   ci != php_script->class_defs->end(); 
	   ci++)
	{
	   // Inspect all members in the class
	   for(
	      mi = (*ci)->members->begin(); 
	      mi != (*ci)->members->end(); 
	      mi++)
	   {
	      // Check whether this member is a method or an attribute
	      method = dynamic_cast<AST_method*>(*mi);
	      if(method == NULL) continue;
	      
	      // Check all statements in the method
	      for(
	         si = method->statements->begin(); 
	         si != method->statements->end(); 
	         si++)
	      {
	         // Check if the statement is of type "eval_expr"
	         eval_expr = dynamic_cast<AST_eval_expr*>(*si);
	         if(eval_expr == NULL) continue;
	
	         // Finally, check if the expression is a function call
	         invoc = dynamic_cast<AST_method_invocation*>(eval_expr->expr);
	         if(invoc == NULL) continue;
	
	         // Yeah! We found a function call
	         num_function_calls++;
	      }
	   }
	}
	
	printf("%d function calls found\n", num_function_calls);
}

/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Add a TODO comment in empty if statement bodies.
 */

#include "AST_visitor.h"

class Comment_ifs : public AST_visitor
{
private:
   bool comment;

public:
   Comment_ifs()
   {
      comment = false; 
   }

   void children_if(AST_if* in)
   {
      visit_expr(in->expr);
      comment = true;
      visit_statement_list(in->iftrue);
      comment = true;
      visit_statement_list(in->iffalse);
      comment = false;
   }

   void post_statement(AST_statement* in)
   {
      if(comment && in->get_comments()->empty())
         in->get_comments()->push_back(new String("/* TODO: Insert comment */"));

      comment = false;
   }
};

extern "C" void process_ast(AST_php_script* php_script)
{
	Comment_ifs cifs;
	php_script->visit(&cifs);
}

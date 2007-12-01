/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Add a TODO comment in empty if statement bodies.
 */

#include "pass_manager/Plugin_pass.h"

using namespace AST;

class Comment_ifs : public Visitor
{
private:
   bool comment;

public:
   Comment_ifs()
   {
      comment = false; 
   }

   void children_if(If* in)
   {
      visit_expr(in->expr);
      comment = true;
      visit_statement_list(in->iftrue);
      comment = true;
      visit_statement_list(in->iffalse);
      comment = false;
   }

   void post_statement(Statement* in)
   {
      if(comment && in->get_comments()->empty())
         in->get_comments()->push_back(new String("/* TODO: Insert comment */"));

      comment = false;
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (PHP_script* in, Pass_manager* pm)
{
	in->visit (new Comment_ifs ());
}

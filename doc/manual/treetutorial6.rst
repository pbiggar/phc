.. _treetutorial6:

Returning Lists
===============


In this tutorial we will develop step-by-step a transform that expands
``include`` statements. For example, if :file:`b.php` is 

.. sourcecode:: php

   <?php
      echo "Hello world";
   ?>

			
and :file:`a.php` is

.. sourcecode:: php

   <?php
      include "b.php";
      echo "Goodbye!";
   ?>


Then running the transform on :file:`a.php` yields 

.. sourcecode:: php

   <?php
      echo "Hello world\n";
      echo "Goodbye\n";
   ?>


The transform we will develop in this tutorial is only a simple
implementation of ``include``\s, and we won't take every feature of
``include`` into account. However, it can serve as a basis for more
full-featured version. The transform we will develop here is available as
:file:`plugins/tutorials/Expand_includes.la`.


Deleting Nodes
--------------

Our transform should process ``include`` statements.  In the AST, ``include``\s
are represented as method invocations. Thus, we might start like this: 

.. sourcecode:: c++

   class Expand_includes : public Transform
   {
   public:
      Expr* pre_method_invocation(Method_invocation* in)
      {
         // Process includes
      }
   };


However, this will not get us very far. The return type of
:func:`pre_method_invocation` is an :class:`Expr`.  That means that we can
replace the method invocation (the ``include`` statement) only by another,
single, expression. But we want to replace it by the contents of the specified
file! 

Recall from :ref:`treetutorial1` that to turn an expression into a
statement, |phc| inserts an :class:`Eval_expr` in the abstract syntax tree.
Thus, if we want to process ``include`` statements, we could also look at all
:class:`Eval_expr` nodes. Assuming for the moment we can make that work, does
it get us any further? As a matter of fact, it does! If you check
:file:`AST_transform.h`, you will see that the signature for
:func:`pre_eval_expr` is 

.. sourcecode:: c++

   void pre_eval_expr(Eval_expr* in, Statement_list* out)


This is different from the signatures we have seen so far. For nodes that can
be replaced by a number of new nodes, the pre transform and post transform
methods will not have a return value in their signature, but have an extra
``xxx_List`` argument.  This list is initialised to be empty before
:func:`pre_eval_expr` is invoked, and when :func:`pre_eval_expr` returns, the
nodes in this list will replace ``*in``. If the list is empty, the node is
simply deleted from the tree. 

So, we will use the following p lugin as our starting point. Executing this
plugin deletes all :class:`Eval_expr` nodes from the tree (try it!). 

.. sourcecode:: c++

   #include "AST_transform.h"

   class Expand_includes : public Transform
   {
   public:
      void pre_eval_expr(Eval_expr* in, Statement_list* out)
      {
      }
   };

   extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
   {
      pm->add_after_named_pass (pass, new String ("ast"));
   }

   extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
   {
      Expand_includes einc;
      in->transform_children(&einc);
   }



Using the XML unparser
----------------------

So, we now want to do something more useful than deleting all
:class:`Eval_expr` nodes from the tree. The first thing we need to be able to
do is distinguish ``include`` statements from other :class:`Eval_expr` nodes.
We can use pattern matching (see :ref:`treetutorial3` and :ref:`treetutorial4`) to do that - but what should we match against? If you
are unsure about the structure of the tree, it can be quite useful to use the
XML unparser to find out what the tree looks like. We modify the plugin as
follows: 

.. sourcecode:: c++

   #include "AST_transform.h"
   #include "process_ir/XML_unparser.h"

   class Expand_includes : public Transform
   {
   private:
      XML_unparser* xml_unparser;

   public:
      Expand_includes()
      {
         // Send output to cout, do not print attributes
         xml_unparser = new XML_unparser(cout, false);
      }

   public:
      void pre_eval_expr(Eval_expr* in, Statement_list* out)
      {
         in->visit(xml_unparser);
      }
   };


The XML unparser is implemented using the :class:`Visitor` API, so it can be
invoked just like you run any other visitor. There is a similar visitor called
:class:`AST_unparser` (in :file:`<process_ast/AST_unparser.h>`) that you can
use to print (parts of the) AST to PHP syntax. 

When you run this transform on :file:`a.php`, it will print two
:class:`Eval_expr` nodes (shown in XML syntax), one for the
``include`` and one for the ``echo`` . We are interested in the first, the
``include``: 

.. sourcecode:: xml

   <AST:Eval_expr>
      <AST:Method_invocation>
         <AST:Target xsi:nil="true" />
         <AST:METHOD_NAME>
            <value>include</value>
         </AST:METHOD_NAME>
         <AST:Actual_parameter_list>
            <AST:Actual_parameter>
               <bool><!-- is_ref -->false</bool>
               <AST:STRING>
                  <value>b.php</value>
               </AST:STRING>
            </AST:Actual_parameter>
         </AST:Actual_parameter_list>
      </AST:Method_invocation>
   </AST:Eval_expr>


This tells us that the ``include`` statement is an :class:`Eval_expr` node
(that was obvious from the fact that we implemented :func:`pre_eval_expr`). The
:class:`Eval_expr` contains a :class:`Method_invocation` (we knew that too,
although of course a node of type :class:`Eval_expr` can contain any type of
expression). The method invocation has target ``NULL`` (it is not invoked on an
object or a class), method name "``include``", and a single parameter in the
parameter list that contains the name of the file we are interested in. We can
construct a pattern that matches this tree exactly: 

.. sourcecode:: c++

   class Expand_includes : public Transform
   {
   private:
      Wildcard<STRING>* filename;
      Method_invocation* pattern;

   public:
      Expand_includes()
      {
         filename = new Wildcard<STRING>;
         pattern = 
            new Method_invocation(
               NULL,
               new METHOD_NAME(new String("include")),
               new List<Actual_parameter*>(
                  new Actual_parameter(false, filename)
               )
            );
      }

   public:
      void pre_eval_expr(Eval_expr* in, List<Statement*>* out)
      {
         // Check for calls to include
         if(in->expr->match(pattern))
         {
            // Matched! Try to parse the file
         }
         else
         {
            // No match; leave untouched
            out->push_back(in);
         }
      }
   };

	
Note how the construction of the pattern follows the structure of the tree as
output by the XML unparser exactly. The only difference is that we leave the
actual filename a wildcard; obviously, we want to be able to match against any
``include``, not just ``include("a.php")``.  Running this transform should
remove the ``include`` from the file, but leave the other statements untouched
(note that we need to :func:`push_back in` to ``out`` to make sure a statement
does not get deleted). 


The Full Transform
------------------

We are nearly done! All that's left is to parse the file (we can use the
"``filename``" wildcard to find out which file we need to include) and insert
all statements into the parsed file at the point of the include. Parsing PHP is
hard, but of course |phc| comes with a PHP parser. To use this parser, include
the :file:`<parsing/parse.h>` header and call "``parse``".  Here then is the
full transform: 

.. sourcecode:: c++

   #include "AST_transform.h"
   #include "parsing/parse.h"
   #include "process_ir/XML_unparser.h"

   class Expand_includes : public Transform
   {
   private:
      XML_unparser* xml_unparser;
      Wildcard<STRING>* filename;
      Method_invocation* pattern;

   public:
      Expand_includes()
      {
         xml_unparser = new XML_unparser(cout, false);

         filename = new Wildcard<STRING>;
         pattern = 
            new Method_invocation(
               NULL,
               new METHOD_NAME(new String("include")),
               new List<Actual_parameter*>(
                  new Actual_parameter(false, filename)
               )
            );
      }

   public:
      void pre_eval_expr(Eval_expr* in, List<Statement*>* out)
      {
         // in->visit(xml_unparser);

         // Check for calls to include
         if(in->expr->match(pattern))
         {
            // Matched! Try to parse the file
            PHP_script* php_script = parse(filename->value->value, NULL, false);
            if(php_script == NULL)
            {
               cerr 
               << "Could not parse file " << *filename->value->value
               << " on line " << in->get_line_number() << endl;
               exit(-1);
            }

            // Replace the include by the statements in the parsed file
            out->push_back_all(php_script->statements);
         }
         else
         {
            // No match; leave untouched
            out->push_back(in);
         }
      }
   };

   extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
   {
      pm->add_after_named_pass (pass, new String ("ast"));
   }

   extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
   {
      Expand_includes einc;
      in->transform_children(&einc);
   }


**Exercise.** One problem with the plugin we have developed is that if the file
we are including in turn has ``include`` statements, they will not be
processed. Modify the plugin to invoke the transform on the list of statements
from the parsed file, taking care to deal with infinite loops (if the first
file includes the second, and the second the first). 


What's Next?
------------

This is the last tutorial in this series on using the :class:`AST::Visitor` and
:class:`AST::Transform` classes. Of course, the only way to really learn this
stuff is to try it out for yourself.  Hopefully, the tutorials will help you do
so.  The following sources should also be useful: 

*  The :ref:`grammar` (and the :ref:`maketeatheory`)

*  The explanation of how PHP gets represented in the abstract syntax as
   detailed in :ref:`representingphp`

*  The definition of the C++ classes for the AST nodes in
   :file:`src/generated/AST.h`

*	The definition of the ``AST::Visitor`` and ``AST::Transform`` classes in
        :file:`src/generated/AST_visitor.h` and
        :file:`src/generated/AST_transform.h` respectively

.. The previous lines are weird because reST gives an error if they arent
   indented enough.




And of course, we are more than happy to answer any other questions you might
still have. Just send an email to the `mailing list <http://www.phpcompiler.org/mailinglist.html>`_ and
we'll do our best to answer you as quickly as possible! Happy coding! 

.. _treetutorial5:

Modifying the Traversal Order
=============================

As explained in the previous tutorials (in particular, :ref:`treetutorial1`), when a
:class:`AST::Visitor` traverses a tree, it first calls ``pre_xxx`` for a node
of type *xxx*, it then visits all the children of the node, and finally it
calls ``post_xxx`` on the node.  For many transforms, this is sufficient
-- but not for all. Consider the following transform. Suppose we want to
add comments to the ``true`` and ``false`` branches of an ``if``-statement, so
that the following example 

.. sourcecode:: php

   <?php
      if($expr)
      {
         echo "Do something";
      }
      else
      {
         echo "Do something else";
      }
   ?>

	
is translated to
		
.. sourcecode:: php

   <?php
      if($expr)
      {
         // TODO: Insert comment
         echo "Do something";
      }
      else
      {
         // TODO: Insert comment
         echo "Do something else";
      }
   ?>


This appears to be a simple transform. One way to do implement it would be
to introduce a flag ``comment`` that is set to ``true`` when we encounter an
:class:`If` (i.e., in :func:`pre_if`). Then in :func:`post_statement` we could
check for this flag, and if it is set, we could add the required comment to the
statement, and reset the flag to ``false``.  

However, this will only add a comment to the first statement in the ``true``
branch (try it!). To add a comment to the first statement in the ``false``
branch too, we should set the flag to ``true`` in between visiting the children
of the **true** branch and visiting the children of the **false** branch. To be
able to do this, we need to modify :func:`children_if`, as explained in the
next section. 


The Solution
------------

For every AST node type *xxx*, the AST Transform API
defines a method called ``children_xxx``. This method is responsible for
visiting all the children of the node. The default implementation for
:class:`If` is: 

.. sourcecode:: c++

   void Visitor::children_if(If* in)
   {  
       visit_expr(in->expr);
       visit_statement_list(in->iftrue);
       visit_statement_list(in->iffalse);
   }


(you can find this definition in :file:`AST_visitor.cpp`). If you want to
change the order in which the children of a node are visited, entirely avoid
visiting some children, or simply execute a piece of code in between two
children, this is the method you will need to modify. 

Here is the transform that does what we need (available as
:file:`plugins/tutorials/Comment_ifs.la`):

.. sourcecode:: c++

   #include "AST_visitor.h"

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
            in->get_comments()->push_back(new String("// TODO: Insert comment"));

         comment = false;
      }
   };



What's Next?
------------

:ref:`treetutorial6` explains how to deal with transforms that can
replace a single node by multiple new nodes, and shows how to call the |phc|
parser and unparser from your plugins.

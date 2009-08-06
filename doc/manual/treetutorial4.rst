.. _treetutorial4:

Using State
===========

This tutorial explains an advanced feature of pattern matching, and shows an
important technique in writing tree transforms: the use of state. Suppose we
are continuing the refactoring tool that we began in :ref:`treetutorial2`, and
suppose that we have replaced all calls to database specific functions by calls
to the generic DBX functions. To finish the refactoring, we want to rename any
function ``foo`` in the script to ``foo_DB``, if it makes use of the database
--- this clearly sets functions that use the database apart, which may make the
structure of the script clearer.  

So, we want to write a transform that renames all functions ``foo``
to ``foo_DB``, if there is one or more call within that function to any
``dbx_something`` function.  Here is a simple example:

.. sourcecode:: php

   <?php
      function first()
      {
         global $link;
         $error = dbx_error($link);
      }

      function second()
      {
         echo "Do something else";
      }
   ?>

	
After the transform, we should get 
	
.. sourcecode:: php

   <?php
      function first_DB ()
      {
         global $link;
         $error = dbx_error ($link);
      }

      function second()
      {
         echo "Do something else";
      }
   ?>


The Implementation
------------------

Since we have to modify method (function) names, the nodes we are interested in
are the nodes of type :func:`Method`. However, how do we know when to modify a
particular method? Should we search the method body for function calls to
``dbx_something``? As we saw in :ref:`treetutorial1`, manual searching
through the tree is cumbersome; there must be a better solution. 

The solution is in fact very easy. At the start of each method, we set a
variable ``uses_dbx`` to ``false``. When we process the method, we set
``uses_dbx`` to ``true`` when we find a function call to a DBX function.  Then
at the end of the method, we check ``uses_dbx``; if it was set to ``true``, we
modify the name of the method.  This tactic is implement by the following
transform (available as :file:`plugins/tutorials/InsertDB.la` in the |phc|
distribution). Note the use of :func:`pre_method` and :func:`post_method` to
initialise and check ``use_dbx``, respectively.  (Because we don't need to
modify the structure of the tree in this transform, we use the simpler
:class:`AST::Visitor` API instead of the :class:`AST::Transform` API.) 

.. sourcecode:: c++

   class InsertDB : public Visitor
   {
   private:
      int uses_dbx;
      
   public:
      void pre_method(Method* in)
      {
         uses_dbx = false;   
      }

      void post_method(Method* in)
      {
         if(uses_dbx)
            in->signature->method_name->value->append("_DB");
      }

      void post_method_invocation(Method_invocation* in)
      {
         Wildcard<METHOD_NAME>* pattern = new Wildcard<METHOD_NAME>;
         
         // Check for dbx_
         if(in->method_name->match(pattern) && 
            pattern->value->value->find("dbx_") == 0)
         {
            uses_dbx = true;
         }
      }
   };


In :ref:`treetutorial2`, we simply wanted to check for a
particular function name, and we used :func:`match` to do this: 
     
.. sourcecode:: c++

   if(in->match(new METHOD_NAME("mysql_connect")))


Here, we need to check for method names that start with ``dbx_``.
We use the STL method :func:`find` to do this, but we cannot call this
directly on ``in->method_name`` because ``in->method_name`` has type
:class:`Method_name` (could either be a :class:`METHOD_NAME` or a
:class:`Reflection` node).  However, calling :func:`match` on a pattern has the
side effect of setting the :attr:`value` to point to the node that was matched
by the wildcard. So, if the match succeeds, we know that the name of the method
must have been a :func:`METHOD_NAME`, and we can access this name by accessing
``pattern->value`` (``pattern->value->value`` is the value field of the
:class:`METHOD_NAME` itself, i.e., the actual string that stores the name of
the method.) 

(Of course, this transform is not complete; renaming methods is not enough, we
must also rename the corresponding method invocations. This is left as an
exercise for the reader.) 


What's Next?
------------

:ref:`treetutorial5` explains how to change the order in which the
children of a node are visited, avoid visiting some children, or how to execute
a piece of code in between visiting two children.

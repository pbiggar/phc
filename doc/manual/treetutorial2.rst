.. _treetutorial2:

Modifying Tree Nodes
====================

Now that we have seen in :ref:`treetutorial1` how to inspect the
tree, in this tutorial we will look at modifying the tree. The task we set
ourselves is: replace all calls to :func:`mysql_connect` by calls to
func:`dbx_connect` (`dbx <http://pecl.php.net/package/dbx>`_ is
a PECL extension to PHP that allows scripts interface with a database
independent of the type of the database; this conversion could be part of a
larger refactoring process that makes a script written for MySQL work with
other databases.) 

The tutorial we develop in this tutorial is available as :file:`MySQL2DBX.la`
in the |phc| distribution. To see its effect, run |phc| as follows: 
	
.. sourcecode:: bash

   phc --run plugins/tutorials/MySQL2DBX.la --pretty-print test.php


First Attempt
-------------

We are interested in all function calls to :func:`mysql_connect`.  Let us have
a look at the precise definition of a function call according to the :ref:`grammar`: 

.. sourcecode:: haskell

   Method_invocation ::= Target? Method_name Actual_parameter* ;
   Method_name ::= METHOD_NAME | Reflection ;
   Actual_parameter ::= is_ref:"&"? Expr ;
   Reflection ::= Expr ;

			
(The :attr:`target` of a method invocation is the class or object the function
gets invoked on, if any. It need not worry us here.) For now, we are only
interested in the :class:`Method_name`. The grammar tells us that a
:class:`Method_name` is either a :class:`METHOD_NAME` or a node of type
:class:`Reflection`. If a symbol is written in CAPITALS in the grammar, that
means it refers to a "token", a literal value.  In this case, to an actual
method name (such as :func:`mysql_connect`).  In PHP, it is also possible to
call a method whose name is stored in variable; in this case, the function name
will be a :class:`Reflection` node (which contains an :class:`Expr`). In this
tutorial, we are interested in "normal" method invocations only.  

All tokens have an attribute called :attr:`value` which corresponds to the
value of the token. For most tokens, the type of :attr:`value` is a
:ctype:`String*` (consider a :class:`String` to be an STL :ctype:`string`.
However, for some tokens, for example :class:`INT`, :attr:`value` has a
different type (e.g., :ctype:`int`).  If the token has a non-standard type, it
will have method called :func:`get_source_rep`, which returns a
:ctype:`String*` representing the token in the source. For example, the real
number ``5E-1`` would have :attr:`value` equal to the (:ctype:`double`) 0.5,
but :func:`get_source_rep` would return (the :ctype:`String*`) "5E-1". 

Thus, we arrive at the following first attempt. 

.. sourcecode:: c++

   #include "AST_visitor.h"
   #include <pass_manager/Plugin_pass.h>

   using namespace AST;

   class MySQL2DBX : public Visitor
   {
   public:
      void post_method_invocation(Method_invocation* in)
      {
         if(in->method_name->match(new METHOD_NAME(new String("mysql_connect"))))
         {
            // Modify name
            in->method_name = new METHOD_NAME(new String("dbx_connect"));
         }
      }
   };

   extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
   {
      pm->add_after_named_pass (pass, new String ("ast"));
   }

   extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
   {
      MySQL2DBX m2d;
      in->visit(&m2d);
   }


.. note::

	|phc| uses a garbage collector, so there is never any need to free objects
	(you never have to call ``delete``).  This makes programming much
	easier and less error-prone (smaller chance of bugs). 

:func:`match` compares two (sub)trees for deep equality.  There is also
another function called :func:`deep_equals`, which does nearly the same
thing, but there are two important differences.  :func:`match` does not take
comments, line numbers and other "additional" information into account, whereas
:func:`deep_equals` does. The second difference is that :func:`match` supports
wildcards; this will be explained in :ref:`treetutorial3`.



Modifying the Parameters
------------------------

Unfortunately, renaming :func:`mysql_connect` to :func:`dbx_connect` is not
sufficient, because the parameters to the two functions differ. According to
the `PHP manual <http://www.php.net/manual/en/index.php>`_, the
signatures for both functions are 

.. sourcecode:: php

   mysql_connect ($server, $username, $password, $new_link, int $client_flags)


and 

.. sourcecode:: php

   dbx_connect ($module, $host, $database, $username, $password, $persistent)


The :data:`module` parameter to :func:`dbx_connect` should be set to
:func:`DBX_MYSQL` to connect to a MySQL database. Then :data:`host` corresponds
to :data:`server`, and :data:`username` and :data:`password` have the same
purpose too.  So, we should insert :func:`DBX_MYSQL` at the front of the list,
and insert ``NULL`` in between :data:`host` and :data:`username` (the
:func:`mysql_connect` command does not select a database). The last two
parameters to :func:`mysql_connect` do not have an equivalent in
:func:`dbx_connect`, so if they are specified, we cannot perform the
conversion. The last parameter to :func:`dbx_connect` (:data:`persistent`) is
optional, and we will ignore it in this tutorial.  

Now, in |phc|, :const:`DBX_MYSQL` is a :class:`Constant`, which has two fields,
an optional class name (for class constants) and the name of the constant, of
type :class:`CONSTANT_NAME`. ``NULL`` is represented by :class:`NIL` (to avoid
getting confused with the C++ value ``NULL``.

We are now ready to write our conversion function: 

.. sourcecode:: c++

   #include "AST_visitor.h"
   #include <pass_manager/Plugin_pass.h>

   using namespace AST;

   class MySQL2DBX : public Visitor
   {
   public:
      void post_method_invocation(Method_invocation* in)
      {
         Actual_parameter_list*>::iterator pos;
         CONSTANT_NAME* module_name;
         Constant* module_constant;
         Actual_parameter* param;
    
         if(in->method_name->match(new METHOD_NAME(new String("mysql_connect"))))
         {
            // Check for too many parameters
            if(in->actual_parameters->size() > 3)
            {
               printf("Error: unable to translate call "
                  "to mysql_connect on line %d\n", in->get_line_number());
               return;
            }
         
            // Modify name
            in->method_name = new METHOD_NAME(new String("dbx_connect"));
         
            // Modify parameters
            module_name = new CONSTANT_NAME(new String("DBX_MYSQL"));
            module_constant = new Constant(NULL, module_name);
            
            pos = in->actual_parameters->begin();
            param = new Actual_parameter(false, module_constant);
            in->actual_parameters->insert(pos, param); pos++;
            /* Skip host */ pos++;
            param = new Actual_parameter(false, new NIL());
            in->actual_parameters->insert(pos, param); 
         }
      }
   };

   extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
   {
      pm->add_after_named_pass (pass, new String ("ast"));
   }

   extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
   {
      MySQL2DBX m2d;
      in->visit(&m2d);
   }


If we apply this transformation to 

.. sourcecode:: php

   $link = mysql_connect('host', 'user', 'pass');


We get 

.. sourcecode:: php

   $link = dbx_connect(DBX_MYSQL, "host", NULL, "user", "pass");


Refactoring
-----------

A quick note on refactoring. Refactoring is the process of modifying existing
programs (PHP scripts), usually to work in new projects or in different setups
(for example, with a different database engine). Manual refactoring is
laborious and error-prone, so tool-support is a must.  Although |phc| can be
used to refactor PHP code as shown in this tutorial, a dedicated refactoring
tool for PHP would be easier to use (though of course less flexible). Such a
tool can however be built on top of |phc|.


What's Next?
------------

:ref:`treetutorial3` explains how you can modify the *structure* of
the tree, as well as the tree nodes.

.. _gettingstarted:

Getting Started
===============

For this introductory tutorial, we assume that you have successfully
downloaded and installed |phc|, and that you know how to run it (:ref:`install`
and :ref:`runningphc`. This tutorial gets you started with using |phc| to
develop your own tools for PHP by writing plugins.

Compiling a Plugin
------------------

To get up and running, we'll first write a "hello world" plugin that does
nothing except print a string. Create a new directory, say :file:`~/myplugins`
and create a new file :file:`helloworld.cpp`:

.. sourcecode:: c++

	#include <AST.h>
	#include <pass_manager/Plugin_pass.h>

	extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
	{
		pm->add_after_named_pass (pass, new String ("ast"));
	}

	extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
	{
		cout << "Hello world (I'm a phc plugin!)" << endl;
	}


This is an example of an (almost) minimal plugin. Every plugin you write must
contain these functions, with these exact signatures [#signature_note]_.
:func:`load` is run when |phc| starts, giving your plugin the opportunity to
add itself to the list of passes |phc| runs. In this example, it is added after
the "ast" pass. When |phc| processes a PHP script, it runs all of the passes on
it in turn. When it's your plugin's turn, it calls your version of
:func:`run_ast()`.

To compile the plugin, run

.. sourcecode:: bash

	~/myplugins$ phc_compile_plugin helloworld.cpp
			
(:program:`phc_compile_plugin` is a small shellscript that makes the task of
compiling plugins easier; it calls :program:`g++` in a platform independent
way; if you're curious, you can open it in any text editor.) Finally, run the
plugin using

.. sourcecode:: bash

	~/myplugins$ phc --run helloworld.la sometest.php

(You need to pass in an input script to |phc| even though our plugin does not
use it.) If that worked as expected, congratulations: you've just written
your first |phc| plugin! :-)


About ``extern "C"``
------------------------

You may have been wondering what the ``extern "C"`` in the definition of
:func:`load()` and :func:`run_ast()` is for; the reason is that |phc| uses the
:program:`libtool`'s :program:`libltdl` interface to load your plugin; if the
functions are not declared as ``extern "C"``, |phc| will not be able to
find them in your plugin because the name of that function will have been
mangled by the C++ compiler. It does not mean that you cannot write C++ code
inside these functions.

If you don't understand any of that, don't worry about it: just remember that
you need to declare :func:`load()`, :func:`run_ast()`, and a small number of
other functions which we'll name later, as ``extern "C"`` and everything will
be fine. (You don't need ``extern "C"`` for any functions you might
define).


Abstract Syntax
---------------

To be able to do anything useful in your plugins, you need to know how |phc|
represents PHP code internally. |phc|'s view of PHP scripts is described by an
*abstract grammar*. An abstract grammar describes how the contents of a PHP
script are structured. A grammar consists of a number of rules. For example,
there is a rule in the grammar that describes how ``if`` statements work:

.. sourcecode:: haskell

	If ::= Expr iftrue:Statement* iffalse:Statement* ; 

This rules reads: "*an if-statement consists of an expression (the
condition of the if-statement), *a list of statements called 'iftrue'* (the
instructions that get executed when the condition holds), *and another list of
statements called 'iffalse'* (the instructions that get executed when the
condition does not hold)".  The asterisk (``*``) in the rule means "list of".
			
As a second example, consider the rule that describes arrays in PHP.  This rule
should cover things such as ``array()``, ``array("a", "b")`` and ``array(1 =>
"a", 2 => "g")``. Arrays are described by the following two rules [#array_note]_.

.. sourcecode:: haskell

	Array ::= Array_elem* ;
	Array_elem ::= key:Expr? val:Expr ;

These two rules say that "*an array consists of a list of array elements*", and
an "*array element has an optional expression called 'key', and a second
expression called 'val'*". The question mark (``?``) means "optional". Note
that the grammar does not record the need for the keyword ``array``, or for the
parentheses and commas.  We do not need to record these, because we already
*know* that we are talking about an array; all we need to know is what the
array elements are.
		

The Abstract Syntax Tree
------------------------

When |phc| reads a PHP script, it builds up an internal representation of the
script. This representation is known as an *abstract syntax tree* (or *AST* for
short). The structure of the AST follows directly from the abstract grammar.
For people familiar with XML, this tree can be compared to the DOM
representation of an XML script (and in fact, |phc| can output the AST as an
XML document, see :ref:`runningphc`).
			

For example, consider ``if``-statements again. An ``if``-statement is represented by an
instance of the ``If`` class, which is (approximately) defined as follows.

.. sourcecode:: c++

	class If
	{
	public:
		Expr* expr;
		Statement_list* iftrue;
		Statement_list* iffalse;
	};

Thus, the name of the rule (``if ::= ...``) translates into a class ``If``, and
the elements on the right hand side of the rule (``Expr iftrue:Statement*
iffalse:Statement*``) correspond directly to the class members.  The class
``Statement_list`` inherits from the STL ``list`` class, and can thus be
treated as such.
		
Similarly, the class definitions for arrays and array elements look like
		
.. sourcecode:: c++

	class Array
	{
	public:
		Array_elem_list* array_elems;
	};

	class Array_elem
	{
	public:
		Expr* key;
		Expr* val;
	};

When you start developing applications with |phc| you will find it useful to
consult the full description of the grammar, which can be found in
:ref:`grammar`. A detailed explanation of the structure of this grammar, and
how it converts to the C++ class structure, can be found in
:ref:`maketeatheory`. Some notes on how |phc| converts normal PHP code into
abstract syntax can be found in :ref:`representingphp`


Working with the AST
--------------------

When you want to build tools based on |phc|, you do not have to understand how
the abstract syntax tree is built, because this is done for you.  Once the tree
has been built, you can examine or modify the tree in any way you want. When
you are finished, you can ask |phc| to output the tree to normal PHP code
again.

Let's write a very simple plugin that counts the number of statements in a
script. Create a new file :file:`~/myplugins/count_statements.cpp`. Recall the
skeleton plugin:
		
.. sourcecode:: c++

	#include <AST.h>
	#include <pass_manager/Plugin_pass.h>

	extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
	{
		pm->add_after_named_pass (pass, new String ("ast"));
	}

	extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
	{
	}

You will notice that :func:`run_ast()` gets passed an object of type :class:`PHP_script`.
This is the top-level node of the generated AST. If you look at the grammar
(:ref:`grammar`), you will find that :class:`PHP_script` corresponds to the
following rule:
	
.. sourcecode:: haskell

	PHP_script ::= Statement* ;

Thus, as far as |phc| is concerned, a PHP script consists of a number of
statements. The class :class:`PHP_script` will have therefore have one member,
called ``statements``, the list of statements. So, to count the number of
classes, all we have to do is query the number of elements in the
``statements`` list:

.. sourcecode:: c++

	#include <AST.h>
	#include <pass_manager/Plugin_pass.h>

	extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
	{
		pm->add_after_named_pass (pass, new String ("ast"));
	}

	extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
	{
		printf("%d statement(s) found\n", in->statements->size());
	}

Save this file to :file:`~/myplugins/count_statements.cpp`.  Compile:

.. sourcecode:: bash

	~/myplugins$ phc_compile_plugin count_statements.cpp

And run:

.. sourcecode:: bash

	~/myplugins$ ./phc --run count_statements.la hello.php


Actually..
----------

If you actually did try to run your plugin, you may have found that our
plugin isn't quite correct. Consider the following example:

.. sourcecode:: php

	<?php
		$x = 5;
		if ($x == 5)
			echo "yes";
		else
			echo "no";
	?>

If you run our plugin on this example, if will report two statements.
Why? Well, the first statement is the assignment, and the second is the
conditional (the ``if`` statement). The statements *inside* the ``if``
statement are not counted, because they are not part of the outer list of
statements of the script. In the next tutorial we will see how to fix this.


Writing Stand Alone Applications
--------------------------------

If you prefer not to write a plugin but want to modify |phc| itself to derive
a new, stand-alone, application, you can add your passes in
:file:`src/phc.cpp` in the |phc| source tree instead. This has
the effect of "hardcoding" your plugin into |phc| [#version_note]_. However, in the
rest of the tutorials we will assume that you are writing your extension as a
plugin.


What's Next?
------------

In theory, you now know enough to start implementing your own tools for PHP.
Write a new plugin, run the plugin using the :option:`--run` option, and
optionally pass in the :option:`--pretty-print` option also to request
that |phc| outputs the tree back to PHP syntax after having executed your
plugin.

However, you will probably find that modifying the tree, despite being
well-defined and easy to understand, is actually rather laborious.  It
requires a lot of boring boilerplate code. The good news is that |phc|
provides sophisticated support for examining and modifying this tree. This
is explained in detail in the follow-up tutorials.


.. [#signature_note] Well, not exactly. :func:`run_ast` can be replaced by :func:`run_hir()` or :func:`run_mir()`.
.. [#array_note] Actually, this is a simplification, but it will do for the moment.
.. [#version_note] In versions before *0.1.7*, this was the only way to write extensions.

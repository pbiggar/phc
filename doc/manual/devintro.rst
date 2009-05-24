.. include:: include.rst

Introduction
============


From the start, one of the design goals of |phc| has been to provide a useful
framework for writing applications that process PHP scripts. |phc| parses PHP
code into an internal representation known as an *abstract syntax tree* or
*AST*.  Applications can process PHP code by analysing and modifying this
abstract representation in one of two ways:


*  |phc| supports *plugins*. Plugins are modules that can be loaded into |phc|,
   which get access to the AST. |phc| provides sophisticated support for writing
   operations over the AST through the *Tree Transformation API*.

*  Alternatively, you can export the AST to *XML*. You
   can then process the XML (for example, using the PHP *SimpleXML* extension)
   in any way you like, and then use |phc| to convert the XML back to PHP.


The :ref:`treetutorials` explain how to
write plugins for |phc|, and provide numerous examples. You will find :ref:`reference` very useful when writing serious
applications using |phc|.

Although we have tried to document |phc| as well as we can, if anything is
still unclear, please let us know by sending an email to the `mailing list <http://www.phpcompiler.org/mailinglist.html>`_.


System Requirements
-------------------

If you want to modify the internals of |phc| in other ways than through the
explicit API we provide for doing so, you will following tools listed below, in
addition to those detailed in the user manual (:ref:`install`).
However, most people should not need these tools (even if you are implementing
tools based on |phc|).

*  :program:`flex` if you need to modify the lexical analyser.
*  :program:`bison` if you need to modify the parser.
*  `maketea <http://www.maketea.org>`_ if you want to modify
   the |phc| grammars (or the AST/HIR/MIR classes).
*  `gengetopt <http://www.gnu.org/software/gengetopt/gengetopt.html>`_ if
   you need to add additional command line arguments; you will need version 0.20 or higher.
*  `gperf <http://www.gnu.org/software/gperf/gperf.html>`_
   if you need to modify the list of keywords recognized by the lexical analyser.
*  `PHP <http://www.php.net/downloads.html>`_ if you need to
   compile or use the *dataflow* branch. See the next section for instructions
   on configuring PHP for use.


Building PHP for |phc| development
----------------------------------

When compiling PHP for use with |phc|, there are a few options:

*  Development: For developing |phc| or debugging |phc| problems, it is
   worthwhile to have debugging symbols and leak checkers enabled.

   :option:`CFLAGS="-O0 -ggdb3" ./configure --enable-debug --enable-maintainer-zts --enable-embed`

*  Deployment: For performance, optimization should be used:

   :option:`CFLAGS="-O3 -g" ./configure --enable-embed`

*  Benchmarking: In order to be fair, both |phc|-generated-code and PHP should
   both be compiled with -O3. The are also some options required to run some
   benchmarks. The prefix is supplied to correspond to benchmarking scripts we
   provide:

   :option:`CFLAGS="-O3 -DNDEBUG" ./configure --enable-embed --enable-bcmath --with-gmp --prefix=/usr/local/php-opt`



Demonstration
-------------

This section is intended as a quick introduction outlining what the current
release of |phc| can do for you. It does not explain everything in detail.

The Source Program
******************

Consider the following simple PHP script.

.. sourcecode:: php

   <?php
      function foo()
      {
         return 5;
      }

      $foo = foo();
      echo "foo is $foo<br>";
   ?>


Internally this program gets represented as an abstract syntax tree, as
shown in figure :ref:`ast`.

.. figure:: img/demo.jpg

   Abstract syntax tree for the demo example



The Transform
*************

Suppose we want to rename function :func:`foo()` to
:func:`bar()`. This is done by the following plugin:

.. sourcecode:: c++

   #include "AST_visitor.h"
   #include "pass_manager/Plugin_pass.h"

   class Rename_foo_to_bar : public Visitor
   {
      void pre_method_name(METHOD_NAME* in)
      {
         if(*in->value == "foo")
            in->value = new String("bar");
      }
   };

   extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
   {
       Rename_foo_to_bar f2b;
       php_script->visit(&amp;f2b);
   }

   extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
   {
      pm->add_after_named_pass (pass, new String("ast"));
   }
					


The Result
**********

Running |phc| gives

.. sourcecode:: php

   <?php
      function bar()
      {
         return 5;
      }

      $foo = bar();
      echo "foo is " . $foo . "<br>";
   ?>


where the name of the function has been changed, while the name of the variable
remained unaltered, as has the text ``"foo"`` inside the string. It's that
simple! Of course, in this example, it would have been quicker to do it by
hand, but that's not the point; the example shows how easy it is to operate on
PHP scripts within the |phc| framework.


Writing Plugins
---------------

:ref:`gettingstarted` introduces
writing plugins for |phc|. It then explains how |phc| represents PHP scripts
internally, and shows how to write a first (but ultimately wrong) attempt at
simple plugin that counts the number of statements in a PHP script.

:ref:`treetutorial1` introduces the
support that |phc| offers for traversing (and transforming) scripts. It shows
how to write a plugin that correctly counts the number of statements in a
script.

:ref:`treetutorial2` shows how you can
modify nodes in the tree (without modifying the structure of the tree).  It
shows how to replace calls to :func:`mysql_connect()` by calls to
:func:`dbx_connect()`.

:ref:`treetutorial3` shows how you can
modify the structure of the tree. It works through an example that removes
unnecessary string concatenations (for example, ``$a .  ""`` is replaced by
just ``$a``).

:ref:`treetutorial4` explains an
advanced features of pattern matching, and shows an important technique: the
use of state in transformations (where one transformation depends on a previous
transformation). It shows how to write a program that renames all functions
:func:`foo()` in a script to :func:`db_foo()`, if there are calls to a database
engine within :func:`foo()`.

:ref:`treetutorial5` explains how
to change the order in which the children of a node are visited, avoid visiting
some children, or how to execute a piece of code in between visiting two
children.

:ref:`treetutorial6` shows how to
define transformations that replace nodes in the tree by multiple other nodes,
and how to delete nodes from the tree. It also shows to call the |phc| parser
and unparsers from plugins.


Reference
---------

|phc| represents PHP scripts internally as an abstract syntax tree. The
structure of this tree is dictated by the :ref:`grammar`. The grammar definition is a very important part of
|phc|.

|phc|'s view on the world (as dictated by the grammar) does not completely
agree with the PHP standard view.  :ref:`representingphp` describes how the various PHP constructs get
translated into the abstract syntax.

:ref:`apioverview` gives an
overview of the AST classes, the tree visitor API and the tree transformation
API from a programmer's perspective.

:program:`Maketea` is a tool created for |phc| which, based on a grammar
definition of a language, generates a C++ hierarchy for the corresponding
abstract syntax tree, a tree transformation and visitor API, and deep cloning,
deep equality and pattern matching on the AST. :ref:`maketeatheory` explains some of the theory behind
:program:`maketea`; in particular, the grammar formalism, the mapping from the
grammar to the AST classes, and the derivation of the tree transformation API.


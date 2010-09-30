.. _devintro:

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
*  `maketea <http://maketea.googlecode.com>`_ if you want to modify
   the |phc| grammars (or the AST/HIR/MIR classes).
*  `gengetopt <http://www.gnu.org/software/gengetopt/gengetopt.html>`_ if
   you need to add additional command line arguments; you will need version 0.20 or higher.
*  `gperf <http://www.gnu.org/software/gperf/gperf.html>`_
   if you need to modify the list of keywords recognized by the lexical analyser.
*  `PHP <http://www.php.net/downloads.html>`_ if you need to
   compile PHP code, or use the *dataflow* branch. See the next section for
   instructions on configuring PHP for use.
*  `automake <http://www.gnu.org/software/automake/>`_,
   `autoconf <http://www.gnu.org/software/autoconf/>`_ and
   `autoconf-archive <http://www.gnu.org/software/autoconf-archive/>_` if you
   want to add files to be compiled as part of |phc|.

.. _dev.phpbuild:

Building PHP for phc development
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






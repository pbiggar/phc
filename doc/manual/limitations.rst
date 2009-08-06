.. _limitations:

Limitations
===========

This document describes the known limitations of the current |phc|
implementation. These limitations are things that we are aware of but that are
not high on our priority list of things to deal with at the moment.  However,
if any of them are bothering you, let us `know <http://www.phpcompiler.org/mailinglist.html>`_ and we might
look into it.

Comments
--------

:ref:`representingphp` explains how
we deal with comments. Most comments in a PHP script should get attached to the
right token in the tree, and no comments should ever be lost. If that is not
true, please send us a sample program that demonstrates where it breaks. There
are a few problems that we are aware of, and there are probably others too. 

Dealing with comments in a completely satisfactory way is a difficult task! The
first problem with our method of dealing with comments is how we deal with
whitespace in multi-line comments.
Consider the following example.

.. sourcecode:: php

   <?php
      /*
       * Some comment with
       * multiple lines
       */
      foo();
   ?>


The problem is that the whitespace at the start of each line is included in the
comment. This means that when the unparser outputs the comment, it outputs
something like 

.. sourcecode:: php

   <?php
      /*
       * Some comment with
          * multiple lines
          */
      foo();
   ?>

It is unclear how to solve this problem nicely. Suggestions are
welcome :-) 

Second, it is not currently possible to associate a comment with
the ``else``-clause of an ``if``-statement. Thus, in

.. sourcecode:: php

   <?php
      // Comment 1
      if($c)
      {
         foo();
      }
      // Comment 2
      else
      {
         bar();
      }
   ?>


Comment 2 will be associated with the call to ``bar``
(but Comment 1 will be associated with the ``if``-statement
itself). A similar problem occurs with comments for
``elseif`` statements.

Finally, if a scope ends on a comment, that comment will be associated with the wrong node. For example, in

.. sourcecode:: php

   <?php
      if($c)
      {
         echo "Hi";
      }
      else
      {
         // Do nothing
      }

      echo "World";
   ?>


the comment will be associated with the ``echo "World"``
statement. A similar problem occurs when a script ends on a comment;
that comment will not be lost, but will be associated with the last
node in the script. 


Numbers
-------

PHP accepts invalid octal numbers such as ``01090`` the
"incorrect tail" is silently ignored (so, this number should
evaluate to 8 decimal). The |phc| lexical analyser will generate an
"invalid token" instead which will result in a syntax error.


Scopes
------

We incorrectly represent

.. sourcecode:: php

   <?php
      {
         function x () {}
      }
   ?>


as

.. sourcecode:: php

   <?php
      function x () {}
   ?>


In the former, ``x`` is only declared when its declaration is executed. In the
latter, it is declared as soon as the program starts.

Other issues
------------

There are quite a number of minor bugs and issues with |phc|, that we are aware
of. Our bug tracker is available at `our project site <http://code.google.com/p/phc/issues/list>`_. We are
looking for contributors to help us fix many of these bugs. Please see `our contributors page  <http://phpcompiler.org/contribute.html>`_, if
you're interested in helping out.



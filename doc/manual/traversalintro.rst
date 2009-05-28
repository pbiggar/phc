.. _traversalintro:

Introduction
============

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




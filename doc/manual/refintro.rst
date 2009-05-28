
.. _refintro:

Introduction
============

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


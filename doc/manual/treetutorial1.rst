<chapter id="treetutorial1">
<title id="treetutorial1.title">Traversing the Tree</title>

<section>

<title></title>

<para>
	In <xref linkend="gettingstarted">, we explained that |phc| represents PHP
	scripts internally as an abstract syntax tree, and that the structure of
	this tree is determined by the <xref linkend="grammar"
	endterm="grammar.title">. We then showed how to make use of this tree to
	count the number of statements. However, the plugin we wrote only counted
	the &ldquo;top-level&rdquo; statements. Statements nested inside other
	statements (for example, statements inside the true or false branch of an
	``if`` statement) were ignored. In this tutorial, we will rectify
	this problem and write a plugin that counts <emphasis>all</emphasis>
	statements in a script. So, for
</para>
		
.. sourcecode::

<?php
   $x = 5;
   if($x == 5)
      echo "yes";
   else
      echo "no";
?>


<para>
	we should report four statements.
</para>

<para>
	Note that all the plugins that we will develop in these tutorials are
	included in the |phc| distribution. For example, in this tutorial we will be
	developing two plugins: a difficult solution to the problem and an easy
	solution to the problem. You can run these plugins by running
</para>

.. sourcecode::

phc --run plugins/tutorials/count_statements_difficult.la test.php

			
<para>
	or 
</para>

.. sourcecode::

phc --run plugins/tutorials/count_statements_easy.la test.php


</section>

<section>

<title>The Grammar (Revisited)</title>

<para>
	How do we go about counting all statements in a script?  Remember that, as
	far as |phc| is concerned, a PHP script consists of a number of statements,
	but some of those statements may have other statements nested inside them.
	Here is part of the |phc| grammar: 
</para>

.. sourcecode::

PHP_script ::= Statement* ;
Statement ::= Eval_expr | If | While | ...
If ::= Expr iftrue:Statement* iffalse:Statement* ;
While ::= Expr Statement* ;


<para>
	The vertical bar (``|``) means &ldquo;or&rdquo;. So, a statement is
	either an evaluation of an expression (``eval_expr``), an
	``if`` statement, or a ``while`` statement, or..  Thus,
	our running example is represented by the tree in <xref linkend="ifx5tree">.
	The four statements that we are interested in have been highlighted.
</para>

<figure id="ifx5tree">
<title>Abstract syntax tree for the running example</title>
<mediaobject>
<imageobject>
<imagedata fileref="img/ifx5.jpg">
</imageobject>
</mediaobject>
</figure>


</section>

<section>

<title>Statements and Expressions</title>

<para>
	The ``Eval_expr`` nodes in the tree probably need some explanation.
	There are many different types of statements in PHP:
	``if``-statements, ``while``-statements,
	``for``-loops, etc. You can find the full list in the <xref
	linkend="grammar" endterm="grammar.title">. If you do look at the grammar,
	you will notice in particular that a function call is not actually a
	statement!  Instead, a function call is an <emphasis>expression</emphasis>.
</para> 

<para>
	The difference between statements and expressions is that a statement
	<emphasis>does</emphasis> something (for example, a ``for``-loop
	repeats a bunch of other statements), but an expression has a
	<emphasis>value</emphasis>. For example, &ldquo;5&rdquo; is an expression
	(with value 5), &ldquo;1+1&rdquo; is an expression (with value 2), etc. A
	function call is also considered an expression. The value of a function call
is the value that the function returns. </para>

<para>
	Now, an ``eval_expr`` makes a statement from an expression.  So, if
	you want to use an expression where |phc| expects a statement, you have to
	use the grammar rule
</para>

.. sourcecode::

Statement ::= ... | Eval_expr ;
Eval_expr ::= Expr ;


</section>

<section>

<title>The Difficult Solution</title>

<para>
	The following plugin is a partial solution to counting the number of
	statements in a tree. If you do not understand the code, do not worry! We
	will look at a much easier solution in a second. If you understand the
	comments, that is enough.
</para>
			
.. sourcecode::

#include <AST.h>
#include <pass_manager/Plugin_pass.h>

int count(AST::Statement_list* in)
{
   <emphasis>// Every item in "in" is a statement</emphasis>
   int num_statements = in->size();

   <emphasis>// But there can also be statements nested inside any</emphasis>
   <emphasis>// of the statements in "in". We consider each one in turn.</emphasis>
   Statement_list::const_iterator i;
   for(i = in->begin(); i != in->end(); i++)
   {
      <emphasis>// Check if the statement is an if-statement</emphasis>
      if(If* if_stmt = dynamic_cast<If*>(*i))
      {
         num_statements += count(if_stmt->iftrue);
         num_statements += count(if_stmt->iffalse);
      }
   }

   return num_statements;
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
   int num_statements = count(in->statements);
   cout << num_statements << " statements found" << endl;
}


<para>
	The overall structure of this plugin should be fairly clear. We count all
	the statements in the outermost list of statements, and then consider each
	statement in turn to check if there are any statements nested inside them.
	This plugin will now report the correct number of statements for our example
	with the ``if`` statement. However, if will report an invalid
	number of statements for examples with other types of statements. For
	example, it will report only two statements for
</para>

.. sourcecode::

<?php
   $x = 5;
   while($x--)
   {
      echo $x;
   }
?>


<para>
	Of course, we can fix the plugin by testing for ``while``
	statements. And for ``do`` statements. And for
	``foreach``, ``switch``, ``try``, etc. As
	mentioned, manually dealing with the syntax tree is a laborious process!
	Even something as simple as counting the number of statements in a script
	becomes a large program. Fortunately, there is a much easier solution.
</para> 

</section>

<section>

<title>The Easy Solution</title>

<para>
	Fortunately, |phc| will do all this for you automatically! There is a
	standard &ldquo;do-nothing&rdquo; tree traversal predefined in |phc| in the
	form of a class called ``AST::Visitor`` (defined in
	:file:`AST_visitor.h`). ``AST::Visitor``
	contains methods for each type of node in the tree. |phc| will automatically
	traverse the abstract syntax tree for you, and call the appropriate method
	at each node.
</para>

<para>
	In fact, there are <emphasis>two</emphasis> methods defined for each type of
	node. The first method, called ``pre_something``, gets called on a
	node <emphasis>before</emphasis> |phc| visits the children of the node. The
	second method, called ``post_something``, gets called on a node
	<emphasis>after</emphasis> |phc| has visited the children of the node.  For
	example, ``pre_if`` gets called on an ``If``,
	before visiting the statements in the ``iftrue`` and
	``iffalse`` clauses of the ``If``. After all the
	statements, have been visited, ``post_if`` gets called.
</para>

<para>
	So, here is an alternative and much easier solution for our problem. This
	plugin will actually count <emphasis>all</emphasis> statements in a script,
	without having to worry about all the different ways statements can be
	embedded in other statements. Moreover, even if the internal representation
	of |phc| changes (for example, if another type of statement gets added),
	this plugin will still work as-is.
</para>

.. sourcecode::

#include "AST_visitor.h"
#include <pass_manager/Plugin_pass.h>

class Count_statements : public AST::Visitor
{
private:
   int num_statements;

public:
   <emphasis>// Set num_statements to zero before we begin</emphasis>
   void pre_php_script(AST::PHP_script* in)
   {
      num_statements = 0;
   }

   <emphasis>// Print the number of function calls when we are done</emphasis>
   void post_php_script(AST::PHP_script* in)
   {
      cout << num_statements << " statements found" << endl;
   }
   
   <emphasis>// Count the number of function calls</emphasis>
   void post_statement(AST::Statement* in)
   {
      num_statements++;
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	Count_statements cfc;
	in->visit(&amp;cfc);
}


<para> We override a number of methods of the ``Visitor`` class to
implement the functionality we need; the traversal is then taken care of by
|phc|. </para>

</section>

<section>

<title>Pre and Post Methods</title> 

<para> We need to be precise about the order in which |phc| calls all these
methods. Suppose we have a node ``Foo`` (say, an if-statement), which
<emphasis>is-a</emphasis> ``Bar`` (say, statement), which itself
<emphasis>is-a</emphasis> ``Baz`` (say, commented node).  Then |phc|
calls the visitor methods in the following order: </para>

<orderedlist>
<listitem><para>``pre_baz``</para></listitem>
<listitem><para>``pre_bar``</para></listitem>
<listitem><para>``pre_foo``</para></listitem>
<listitem><para>``children_foo`` (visit the children of ``foo``)</para></listitem>
<listitem><para>``post_foo``</para></listitem>
<listitem><para>``post_bar``</para></listitem>
<listitem><para>``post_baz``</para></listitem>
</orderedlist>

<para> Just to emphasise, if all of the visitor methods listed above are
implemented, they will <emphasis>all</emphasis> be invoked, in the order listed
above. So, implementing a more specific visitor (``pre_foo``) does not
inhibit the more general method (``pre_bar``) from being invoked. You
can run the :file:`plugins/tutorials/show_traversal_order.la` from
the |phc| distribution to see this in action. </para>

<note>
<para>(Advanced users) As mentioned above, if you implement ``pre_if``
(say), the more general methods such as ``pre_statement`` or
``pre_node`` will still be invoked. It is possible to override
``pre_if_chain`` instead; if you override ``pre_if_chain``,
you are responsible for calling the more general methods manually. If you
don't, they will not be called at all. </para>
</note>

</section>

</chapter>

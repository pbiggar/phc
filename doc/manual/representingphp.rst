<chapter id="representingphp">
<title id="representingphp.title">Representing PHP</title>

<section>
<title></title>

<para>
	Most PHP constructs can immediately be represented in terms of the |phc|
	grammar (<xref linkend="grammar">). There are a few constructs that present
	some difficulties. This document describes how these difficulties are
	resolved, and it explains some of the more difficult rules in the
	grammar.
</para>

</section>
<section>

<title>Variables</title>

<para>The grammar rule for variables reads</para>

.. sourcecode::

variable ::= target? variable_name <emphasis>array_indices:</emphasis>(expr?)* <emphasis>string_index:</emphasis>expr?
variable_name ::= VARIABLE_NAME | reflection 


<para> This is probably one of the more difficult rules in the grammar, so it
is worth explaining in a bit more detail. The following table describe each
element of the first rule in detail. </para>

<variablelist>

<varlistentry>
	<term>``Target?``</term>
	<listitem><para>
		Just like function calls, variables can have a target, and just as for
		function calls, this target can be an expression (for an object, e.g.,
		``$x->y``) or a class name (for a static class attribute,
		e.g. ``FOO::$y``). As in function calls, in variables the target
		is optional (indicated by the question mark). If no target is specified,
		the variable refers to a <emphasis>local</emphasis> variable in a method.
	</para></listitem>
</varlistentry>

<varlistentry>
	<term>``Variable_name``</term>
	<listitem><para>
		Again, as for function calls, the name of the variable may be a literal
		``VARIABLE_NAME`` (``$x``), or be given by an
		expression (which is wrapped up in an ``Reflection`` node).  The
		latter possibility is referred to as &ldquo;variable-variables&rdquo; in
		the PHP manual.  For example, ``$$x`` is the variable whose name
		is currently stored in (another) variable called
		``$x``.
	</para></listitem>
</varlistentry>

<varlistentry>
	<term>``array_indices:(Expr?)*``</term>
	<listitem><para>
		A variable may have one or more array indices, for example
		``$x[3][5]``. The strange construct ``(Expr?)*`` means:
		a list of (``*``) optional (``?``) expressions. For
		example, ``$x[4][]`` is a list of two expressions, but the
		second expression is not given. In PHP, this means &ldquo;use the next
		available index&rdquo;. String- and array-indexing (``$x{3}``)
		are equivalent in PHP, so string-indexing is also represented by
		``array_indices``.
	</para></listitem>
</varlistentry>
</variablelist>

<para>We illustrate the various possibilities using diagrams.</para> 
<warning>
<para>
	These diagrams use old names for AST nodes. Where you see
	``AST_variable``, it is now called ``Variable`` (it uses
	the AST namespace). ``Token_variable_name`` is called
	``VARIABLE_NAME`` and ``Token_int`` is called
	``INT``.
</para>
<para>
	It is possible the structure of some nodes have changed slightly since this
	was written.
</para>
</warning>

<variablelist>
<!-- TODO: these images need to be regenerated -->

<varlistentry>
	<term>The simple case: ``$x``</term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/variable.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>The name of the variable is ``x``, not
	``$x``.</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Using array indices: ``$x[1][][2]``</term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/array_indices.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>(The empty array index means &ldquo;next available&rdquo; in
	PHP).</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Class constants: ``X::$y``</term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/static_var.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>Again, the variable name is ``y``, not ``$y``. The
	fact that you must write ``$x->y`` but ``X::$y`` in
	PHP disappears in the abstract syntax.</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Variable variables: ``$$x``</term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/var_var.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>Note how the name of the variable (second component) is now given by
	another variable.</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Object attributes: ``$x->y``</term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/attribute.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>The target is now given by a variable.</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Variable object attributes: ``$x->$y``</term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/var_attr.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>Both the target and the variable name are given by (other)
	variables.</para>
	</listitem>
</varlistentry>

</variablelist>

</section>
<section>

<title>Comments</title>

<para>
	A number of nodes in the AST are dedicated &ldquo;commented nodes&rdquo;.
	Their corresponding C++ classes inherit from ``Commented_node``,
	which introduces a ``String_list*`` attribute called
	``comments``.  The commented nodes are class members
	(``Member``), statements (``Statement``), interface and
	class definitions (``Interface_def``, ``Class_def``),
	switch cases (``Switch_case``) and catches (``Catch``).
</para>

<para>
	When the parser encounters a comment in the input, it attaches it either to
	the previous node in the AST, or to the next, according to a variable
	``attach_to_previous``. This variable is set as follows: 
</para>

<itemizedlist>
	<listitem><para>
		It is reset to ``false`` at the start of each
		line
	</para></listitem>
	<listitem><para>
		It is set to ``true`` after seeing a semicolon, or either of the
		keywords ``class`` or ``function``
	</para></listitem>
</itemizedlist>

<para> Thus, in </para>

.. sourcecode::

foo();
<emphasis>// Comment</emphasis>
bar();


<para> the comment gets attached to ``bar();`` (to be precise, to the
corresponding ``Eval_expr`` node; the function call itself is an
expression and |phc| does not associate comments with expressions), but in
</para>

.. sourcecode::

foo(); <emphasis>// Comment</emphasis>
bar();


<para> the comment gets attached to ``foo();`` instead. The same
applies to multiple comments:	 </para>

.. sourcecode::

foo(); <emphasis>/* A */</emphasis> <emphasis>/* B */</emphasis>
<emphasis>// C</emphasis>
<emphasis>// D</emphasis>
bar();


<para> In this snippet, ``A`` and ``B`` get attached to
``foo();``, but ``C`` and ``D`` get attached to
``bar();``. Also, in the following snippet, </para>
			
.. sourcecode::

<emphasis>// Comment</emphasis>
echo <emphasis>/* one */</emphasis> 1 + <emphasis>/* two */</emphasis> 2;

			
<para> all comments get attached to the same node.  This should work most of
the time, if not all the time. In particular, it should never loose any
comments. If something goes wrong with comments, please <ulink
url="http://www.phpcompiler.org/contact.html">send</ulink> us a sample program
that shows where it goes wrong. Note that whitespace in multi-line comments
gets dealt with in a less than satisfactory way; see <xref
linkend="limitations" endterm="limitations.title"> for details for details. </para> 

</section>
<section>

<title>String parsing</title>

<para>Double quoted strings and those written using the HEREDOC syntax are
treated specially by PHP: it parses variables used inside these strings and
automatically expands them with their value. |phc| handles both the simple and
complex syntax defined by PHP for variables in strings. We transform a string
like</para>
			
.. sourcecode::

"Total cost is: $total (includes shipping of $shipping)"

			
<para>into:</para>

.. sourcecode::

"Total cost is: " . $total . " (includes shipping of " . $shipping . ")"

			
<para>
	which is represented in the |phc| abstract syntax tree by a number of strings
	and expressions concatenated together. Thus, as a programmer you don't need
	to do anything special to process variables inside strings. Any code you
	write for processing variables will also appropriately handle variables
	inside strings. (Note that as of version 0.2.0, interpolated strings are
	correctly unparsed by |phc|.)
</para>

</section>
<section>

<title>``elseif``</title>

<para>The abstract grammar does not have a construct for ``elseif``.
The following PHP code</para>

.. sourcecode::

<?php
   if($x)
      c1();
   elseif($y)
      c2();
   else
      c3();
?>


<para>gets interpreted as</para>

.. sourcecode::

<?php
   if($x)
      c1();
   else
   {
      if($y)
         c2();
      else
         c3();
   }
?>


<para>The higher the number of ``elseif``s, the greater the level of
nesting. This transformation is &ldquo;hidden&rdquo; by the unparser.</para>

</section>
<section>

<title>Miscellaneous Other Changes</title>

<itemizedlist>

	<listitem><para>
		Fragments of inline HTML become arguments to a function call to
		``echo``.
	</para></listitem>

	<listitem><para>
		The keywords ``use``, ``require``,
		``require_once``, ``include``,
		``include_once``, ``isset`` and ``empty`` all
		get translated into a function call to a function with the same name as
		the keyword.
	</para></listitem>

	<listitem><para>
		``exit`` also becomes a call to the function ``exit``;
		``exit;`` and ``exit();`` are interpreted as
		``exit(0)``
	</para></listitem>

</itemizedlist>

</section>
<section id="comparison">

<title>Comparison to the PHP grammar</title>

<para>
	Finally, the |phc| grammar is much simpler than the official grammar, and as
	a consequence more general. The class of programs that are valid according
	to the abstract grammar is larger than the class of programs actually
	accepted by the PHP parser. In other words, it is possible to represent a
	program in the abstract syntax that does not have a valid PHP equivalent.
	The advantage of our grammar is that is much, <emphasis>much</emphasis>
	easier to work with. 
</para>

<para>
	To compare, consider the tree for 
</para>

.. sourcecode::

$g->greet("TACS");


<para>
	Using the |phc| abstract syntax, this looks like the tree shown in figure
	<xref linkend="abstracttree">. 
</para>
	
<figure id="abstracttree">
<title>Function call in the AST</title>
<mediaobject>
<imageobject>
<imagedata fileref="img/abstract-tree.jpg">
</imageobject>
</mediaobject>
</figure>

<para>
	However, in the official PHP grammar, the tree would look like the tree
	shown in figure <xref linkend="concretetree">. 
</para>

<figure id="concretetree">
<title>Function call as represented by PHP</title>
<mediaobject>
<imageobject>
<imagedata fileref="img/concrete-tree.jpg">
</imageobject>
</mediaobject>
</figure>

<para>
	Not only is the number of concepts used in the tree much larger
	(``base_variable_with_function_calls``,
	``reference_variable``, ``variable_property``, etc. etc.),
	the concepts used in the |phc| tree map directly to constructs in the PHP
	language; that does not hold true for the PHP tree. Moreover, the fact that
	this expression is a method invocation (function call) is immediately
	obvious from the root of the expression in the |phc| tree; the root of the
	PHP tree says that the expression is a variable, and only deeper down the
	tree does it become apparent that the expression is in fact a function call.
</para>

</section>
</chapter>

<chapter id="representingphp">
<title id="representingphp.title">Representing PHP</title>

<section>
<title></title>

<para>
	Most PHP constructs can immediately be represented in terms of the &phc
	grammar (<xref linkend="grammar">). There are a few constructs that present
	some difficulties. This document describes how these difficulties are
	resolved, and it explains some of the more difficult rules in the
	grammar.
</para>

</section>
<section>

<title>Variables</title>

<para>The grammar rule for variables reads</para>

<programlisting>
variable ::= target? variable_name <emphasis>array_indices:</emphasis>(expr?)* <emphasis>string_index:</emphasis>expr?
variable_name ::= VARIABLE_NAME | reflection 
</programlisting>

<para> This is probably one of the more difficult rules in the grammar, so it
is worth explaining in a bit more detail. The following table describe each
element of the first rule in detail. </para>

<variablelist>

<varlistentry>
	<term><code>Target?</code></term>
	<listitem><para>
		Just like function calls, variables can have a target, and just as for
		function calls, this target can be an expression (for an object, e.g.,
		<code>$x-&gt;y</code>) or a class name (for a static class attribute,
		e.g. <code>FOO::$y</code>). As in function calls, in variables the target
		is optional (indicated by the question mark). If no target is specified,
		the variable refers to a <emphasis>local</emphasis> variable in a method.
	</para></listitem>
</varlistentry>

<varlistentry>
	<term><code>Variable_name</code></term>
	<listitem><para>
		Again, as for function calls, the name of the variable may be a literal
		<code>VARIABLE_NAME</code> (<code>$x</code>), or be given by an
		expression (which is wrapped up in an <code>Reflection</code> node).  The
		latter possibility is referred to as &ldquo;variable-variables&rdquo; in
		the PHP manual.  For example, <code>$$x</code> is the variable whose name
		is currently stored in (another) variable called
		<code>$x</code>.
	</para></listitem>
</varlistentry>

<varlistentry>
	<term><code>array_indices:(Expr?)*</code></term>
	<listitem><para>
		A variable may have one or more array indices, for example
		<code>$x[3][5]</code>. The strange construct <code>(Expr?)*</code> means:
		a list of (<code>*</code>) optional (<code>?</code>) expressions. For
		example, <code>$x[4][]</code> is a list of two expressions, but the
		second expression is not given. In PHP, this means &ldquo;use the next
		available index&rdquo;. String- and array-indexing (<code>$x{3}</code>)
		are equivalent in PHP, so string-indexing is also represented by
		<code>array_indices</code>.
	</para></listitem>
</varlistentry>
</variablelist>

<para>We illustrate the various possibilities using diagrams.</para> 
<warning>
<para>
	These diagrams use old names for AST nodes. Where you see
	<code>AST_variable</code>, it is now called <code>Variable</code> (it uses
	the AST namespace). <code>Token_variable_name</code> is called
	<code>VARIABLE_NAME</code> and <code>Token_int</code> is called
	<code>INT</code>.
</para>
<para>
	It is possible the structure of some nodes have changed slightly since this
	was written.
</para>
</warning>

<variablelist>
<!-- TODO: these images need to be regenerated -->

<varlistentry>
	<term>The simple case: <code>$x</code></term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/variable.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>The name of the variable is <code>x</code>, not
	<code>$x</code>.</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Using array indices: <code>$x[1][][2]</code></term>
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
	<term>Class constants: <code>X::$y</code></term>
	<listitem>
	<informalfigure>
	<mediaobject>
	<imageobject>
	<imagedata fileref="img/static_var.jpg">
	</imageobject>
	</mediaobject>
	</informalfigure>
	<para>Again, the variable name is <code>y</code>, not <code>$y</code>. The
	fact that you must write <code>$x-&gt;y</code> but <code>X::$y</code> in
	PHP disappears in the abstract syntax.</para>
	</listitem>
</varlistentry>

<varlistentry>
	<term>Variable variables: <code>$$x</code></term>
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
	<term>Object attributes: <code>$x-&gt;y</code></term>
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
	<term>Variable object attributes: <code>$x-&gt;$y</code></term>
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
	Their corresponding C++ classes inherit from <code>Commented_node</code>,
	which introduces a <code>String_list*</code> attribute called
	<code>comments</code>.  The commented nodes are class members
	(<code>Member</code>), statements (<code>Statement</code>), interface and
	class definitions (<code>Interface_def</code>, <code>Class_def</code>),
	switch cases (<code>Switch_case</code>) and catches (<code>Catch</code>).
</para>

<para>
	When the parser encounters a comment in the input, it attaches it either to
	the previous node in the AST, or to the next, according to a variable
	<code>attach_to_previous</code>. This variable is set as follows: 
</para>

<itemizedlist>
	<listitem><para>
		It is reset to <code>false</code> at the start of each
		line
	</para></listitem>
	<listitem><para>
		It is set to <code>true</code> after seeing a semicolon, or either of the
		keywords <code>class</code> or <code>function</code>
	</para></listitem>
</itemizedlist>

<para> Thus, in </para>

<programlisting>
foo();
<emphasis>// Comment</emphasis>
bar();
</programlisting>

<para> the comment gets attached to <code>bar();</code> (to be precise, to the
corresponding <code>Eval_expr</code> node; the function call itself is an
expression and &phc does not associate comments with expressions), but in
</para>

<programlisting>
foo(); <emphasis>// Comment</emphasis>
bar();
</programlisting>

<para> the comment gets attached to <code>foo();</code> instead. The same
applies to multiple comments:	 </para>

<programlisting>
foo(); <emphasis>/* A */</emphasis> <emphasis>/* B */</emphasis>
<emphasis>// C</emphasis>
<emphasis>// D</emphasis>
bar();
</programlisting>

<para> In this snippet, <code>A</code> and <code>B</code> get attached to
<code>foo();</code>, but <code>C</code> and <code>D</code> get attached to
<code>bar();</code>. Also, in the following snippet, </para>
			
<programlisting>
<emphasis>// Comment</emphasis>
echo <emphasis>/* one */</emphasis> 1 + <emphasis>/* two */</emphasis> 2;
</programlisting>
			
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
automatically expands them with their value. &phc handles both the simple and
complex syntax defined by PHP for variables in strings. We transform a string
like</para>
			
<programlisting>
"Total cost is: $total (includes shipping of $shipping)"
</programlisting>
			
<para>into:</para>

<programlisting>
"Total cost is: " . $total . " (includes shipping of " . $shipping . ")"
</programlisting>
			
<para>
	which is represented in the &phc abstract syntax tree by a number of strings
	and expressions concatenated together. Thus, as a programmer you don't need
	to do anything special to process variables inside strings. Any code you
	write for processing variables will also appropriately handle variables
	inside strings. (Note that as of version 0.2.0, interpolated strings are
	correctly unparsed by &phc;.)
</para>

</section>
<section>

<title><code>elseif</code></title>

<para>The abstract grammar does not have a construct for <code>elseif</code>.
The following PHP code</para>

<programlisting>
&lt;?<reserved>php</reserved>
   <reserved>if</reserved>($x)
      c1();
   <reserved>elseif</reserved>($y)
      c2();
   <reserved>else</reserved>
      c3();
?&gt;
</programlisting>

<para>gets interpreted as</para>

<programlisting>
&lt;?<reserved>php</reserved>
   <reserved>if</reserved>($x)
      c1();
   <reserved>else</reserved>
   {
      <reserved>if</reserved>($y)
         c2();
      <reserved>else</reserved>
         c3();
   }
?&gt;
</programlisting>

<para>The higher the number of <code>elseif</code>s, the greater the level of
nesting. This transformation is &ldquo;hidden&rdquo; by the unparser.</para>

</section>
<section>

<title>Miscellaneous Other Changes</title>

<itemizedlist>

	<listitem><para>
		Fragments of inline HTML become arguments to a function call to
		<code>echo</code>.
	</para></listitem>

	<listitem><para>
		The keywords <code>use</code>, <code>require</code>,
		<code>require_once</code>, <code>include</code>,
		<code>include_once</code>, <code>isset</code> and <code>empty</code> all
		get translated into a function call to a function with the same name as
		the keyword.
	</para></listitem>

	<listitem><para>
		<code>exit</code> also becomes a call to the function <code>exit</code>;
		<code>exit;</code> and <code>exit();</code> are interpreted as
		<code>exit(0)</code>
	</para></listitem>

</itemizedlist>

</section>
<section id="comparison">

<title>Comparison to the PHP grammar</title>

<para>
	Finally, the &phc grammar is much simpler than the official grammar, and as
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

<programlisting>
$g->greet("TACS");
</programlisting>

<para>
	Using the &phc abstract syntax, this looks like the tree shown in figure
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
	(<code>base_variable_with_function_calls</code>,
	<code>reference_variable</code>, <code>variable_property</code>, etc. etc.),
	the concepts used in the &phc tree map directly to constructs in the PHP
	language; that does not hold true for the PHP tree. Moreover, the fact that
	this expression is a method invocation (function call) is immediately
	obvious from the root of the expression in the &phc tree; the root of the
	PHP tree says that the expression is a variable, and only deeper down the
	tree does it become apparent that the expression is in fact a function call.
</para>

</section>
</chapter>

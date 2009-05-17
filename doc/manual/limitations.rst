<chapter id="limitations">
<title id="limitations.title">Limitations</title>

<section>
<title></title>

<para>
	This document describes the known limitations of the current |phc|
	implementation. These limitations are things that we are aware of but that
	are not high on our priority list of things to deal with at the moment.
	However, if any of them are bothering you, let us <ulink
	url="http://www.phpcompiler.org/mailinglist.html">know</ulink> and we might
	look into it.
</para>

</section>
<section>

<title> Comments </title>
<para>
	<xref linkend="representingphp" endterm="representingphp.title"> explains
	how we deal with comments. Most comments in a PHP script should get attached
	to the right token in the tree, and no comments should ever be lost. If that
	is not true, please send us a sample program that demonstrates where it
	breaks. There are a few problems that we are aware of, and there are
	probably others too. 
</para>

<para> Dealing with comments in a completely satisfactory way is a
difficult task! The first problem with our method of dealing with
comments is how we deal with whitespace in multi-line comments.
Consider the following example. </para>

<programlisting>
<?<reserved>php</reserved>
   <emphasis>/*
    * Some comment with
    * multiple lines
    */</emphasis>
   foo();
?>
</programlisting>

<para> The problem is that the whitespace at the start of each line is
included in the comment. This means that when the unparser outputs the
comment, it outputs something like </para>

<programlisting>
<?<reserved>php</reserved>
   <emphasis>/*
    * Some comment with
       * multiple lines
       */</emphasis>
   foo();
?>
</programlisting>

<para>It is unclear how to solve this problem nicely. Suggestions are
welcome :-) </para>

<para> Second, it is not currently possible to associate a comment with
the ``else``-clause of an ``if``-statement. Thus, in
</para>

<programlisting>
<?<reserved>php</reserved>
   <emphasis>// Comment 1</emphasis>
   <reserved>if</reserved>($c)
   {
      foo();
   }
   <emphasis>// Comment 2</emphasis>
   <reserved>else</reserved>
   {
      bar();
   }
?>
</programlisting>

<para> Comment 2 will be associated with the call to ``bar``
(but Comment 1 will be associated with the ``if``-statement
itself). A similar problem occurs with comments for
``elseif`` statements. </para>

<para> Finally, if a scope ends on a comment, that comment will be associated with the wrong node. For example, in </para>

<programlisting>
<?<reserved>php</reserved>
   <reserved>if</reserved>($c)
   {
      <reserved>echo</reserved> "Hi";
   }
   <reserved>else</reserved>
   {
      <emphasis>// Do nothing</emphasis>
   }

   <reserved>echo</reserved> "World";
?>
</programlisting>

<para>the comment will be associated with the ``echo "World"``
statement. A similar problem occurs when a script ends on a comment;
that comment will not be lost, but will be associated with the last
node in the script. </para>

</section>
<section>

<title> Numbers </title>

<para>
	PHP accepts invalid octal numbers such as ``01090``; the
	&ldquo;incorrect tail&rdquo; is silently ignored (so, this number should
	evaluate to 8 decimal). The |phc| lexical analyser will generate an
	&ldquo;invalid token&rdquo; instead which will result in a syntax error.
</para>

</section>

<section>

<title> Scopes </title>

<para>
	We incorrectly represent
</para>

.. sourcecode::

<?php
	{
		function x () {}
	}
?>


<para>
	as
</para>

.. sourcecode::

<?php
	function x () {}
?>


<para>
	In the former, ``x`` is only declared when its declaration is
	executed. In the latter, it is declared as soon as the program starts.
</para>

</section>
<section>

<title> Other issues </title>

<para>
	There are quite a number of minor bugs and issues with |phc|, that we are
	aware of. Our bug tracker is available at <ulink
	url="http://code.google.com/p/phc/issues/list">our project site</ulink>. We
	are looking for contributors to help us fix many of these bugs. Please see
	<ulink url="http://phpcompiler.org/contribute.html">our contributors page
	</ulink>, if you're interested in helping out.
</para>

</section>



</chapter>

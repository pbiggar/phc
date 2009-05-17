<chapter id="devintro">
<title id="devintro.title">Introduction</title>

<section>
<title></title>

<para>
	From the start, one of the design goals of |phc| has been to provide a
	useful framework for writing applications that process PHP scripts. |phc|
	parses PHP code into an internal representation known as an
	<emphasis>abstract syntax tree</emphasis> or <emphasis>AST</emphasis>.
	Applications can process PHP code by analysing and modifying this abstract
	representation in one of two ways:
</para>  

<itemizedlist>

	<listitem><para>
		|phc| supports <emphasis>plugins</emphasis>. Plugins are modules that can
		be loaded into |phc|, which get access to the AST. |phc| provides
		sophisticated support for writing operations over the AST through the
		<emphasis>Tree Transformation API</emphasis>.
	</para></listitem> 

	<listitem><para>
		Alternatively, you can export the AST to <emphasis>XML</emphasis>. You
		can then process the XML in any way you like, and then use |phc| to
		convert the XML back to PHP.
	</para></listitem>

</itemizedlist>

<para>
	The <xref linkend="treetutorials" endterm="treetutorials.title"> explain how
	to write plugins for |phc|, and provide numerous examples. You will find
	<xref linkend="reference" endterm="reference.title"> very useful when
	writing serious applications using |phc|.
</para>

<para>
	Although we have tried to document |phc| as well as we can, if
	anything is still unclear, please let us know by sending an email to the
	<ulink url="http://www.phpcompiler.org/mailinglist.html">mailing list</ulink>.
</para>

</section>

<section>
<title>System Requirements</title>

<para>
	If you want to modify the internals of |phc| in other ways than through the
	explicit API we provide for doing so, you will following tools listed below,
	in addition to those detailed in the user manual (<xref linkend="install">).
	However, most people should not need these tools (even if you are
	implementing tools based on |phc|).
</para>

<itemizedlist>
	<listitem><para>
		``flex`` if you need to modify the lexical
		analyser
	</para></listitem>
	<listitem><para>
		``bison`` if you need to modify the parser
	</para></listitem>
	<listitem><para>
		<ulink url="http://www.maketea.org">maketea</ulink> if you want to modify
		the |phc| grammars (or the AST/HIR/MIR classes)
	</para></listitem>
	<listitem><para>
		<ulink
		url="http://www.gnu.org/software/gengetopt/gengetopt.html">gengetopt</ulink>
		if you need to add additional command line arguments; you will need
		version 0.20 or higher
	</para></listitem>
	<listitem><para>
		<ulink url="http://www.gnu.org/software/gperf/gperf.html">gperf</ulink>
		if you need to modify the list of keywords recognized by the lexical
		analyser
	</para></listitem>
</itemizedlist>

</section>

<section id=dev.phpbuild>
<title id=dev.phpbuild.title>Building PHP for |phc| development</title>

<para>
	When compiling PHP for use with |phc|, there are a few options:
</para>

<itemizedlist>

	<listitem>
		<para>Development: For developing |phc| or debugging |phc| problems, it is
		worthwhile to have debugging symbols and leak checkers enabled.</para>
		<para>``CFLAGS="-O0 -ggdb3" ./configure --enable-debug --enable-maintainer-zts --enable-embed``</para>
	</listitem>

	<listitem>
		<para>Deployment: For performance, optimization should be used:</para>
		<para>``CFLAGS="-O3 -g" ./configure --enable-embed``</para>
	</listitem>

	<listitem>
		<para>Benchmarking: In order to be fair, both |phc|-generated-code and PHP
		should be compiled with -O3. The are also some options required to run
		some benchmarks. The prefix is supplied to correspond to benchmarking
		scripts we provide:</para>
		<para>``CFLAGS="-O3 -DNDEBUG" ./configure --enable-embed --enable-bcmath --with-gmp --prefix=/usr/local/php-opt``</para>
	</listitem>

</itemizedlist>
</section>

<section>

<title>Demonstration</title>

<para>
	This section is intended as a quick introduction outlining what the current
	release of |phc| can do for you. It does not explain everything in detail.
</para>

<section>
<title>The Source Program</title>

<para>
	Consider the following simple PHP script.
</para>

.. sourcecode::

<?php
   function foo()
   {
      return 5;
   }

   $foo = foo();
   echo "foo is $foo<br>";
?>


<para>
	Internally this program gets represented as an abstract syntax tree, as
	shown in figure <xref linkend="ast">.
</para>

<figure id="ast">
<title>Abstract syntax tree for the demo example</title>
<mediaobject>
<imageobject>
<imagedata fileref="img/demo.jpg">
</imageobject>
</mediaobject>
</figure>

</section>
<section>

<title>The Transform</title>

<para> Suppose we want to rename function ``foo`` to
``bar``. This is done by the following plugin: </para>

.. sourcecode::

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
					

</section>
<section>

<title>The Result</title>

<para> Running |phc| gives </para>

.. sourcecode::

<?php
   function bar()
   {
      return 5;
   }

   $foo = bar();
   echo "foo is " . $foo . "<br>";
?>


<para> where the name of the function has been changed, while the name of the
variable remained unaltered, as has the text ``"foo"`` inside
the string. It's that simple! Of course, in this example, it would
have been quicker to do it by hand, but that's not the point; the
example shows how easy it is to operate on PHP scripts within the
|phc| framework. </para>

</section>
</section>

<section>

<title>Writing Plugins</title>

<para><xref linkend="gettingstarted" endterm="gettingstarted.title"> introduces
writing plugins for |phc|. It then explains how |phc| represents PHP scripts
internally, and shows how to write a first (but ultimately wrong) attempt at
simple plugin that counts the number of statements in a PHP script.</para>

<para><xref linkend="treetutorial1" endterm="treetutorial1.title"> introduces
the support that |phc| offers for traversing (and transforming) scripts. It
shows how to write a plugin that correctly counts the number of statements in a
script.</para>

<para><xref linkend="treetutorial2" endterm="treetutorial2.title"> shows how
you can modify nodes in the tree (without modifying the structure of the tree).
It shows how to replace calls to ``mysql_connect`` by calls to
``dbx_connect``.</para>

<para><xref linkend="treetutorial3" endterm="treetutorial3.title"> shows how
you can modify the structure of the tree. It works through an example that
removes unnecessary string concatenations (for example, ``$a .  ""``
is replaced by just ``$a``).</para>	

<para><xref linkend="treetutorial4" endterm="treetutorial4.title"> explains an
advanced features of pattern matching, and shows an important technique: the
use of state in transformations (where one transformation depends on a previous
transformation). It shows how to write a program that renames all functions
``foo`` in a script to ``db_foo``, if there are calls to a
database engine within ``foo``.</para>

<para><xref linkend="treetutorial5" endterm="treetutorial5.title"> explains how
to change the order in which the children of a node are visited, avoid visiting
some children, or how to execute a piece of code in between visiting two
children.</para>

<para><xref linkend="treetutorial6" endterm="treetutorial6.title"> shows how to
define transformations that replace nodes in the tree by multiple other nodes,
and how to delete nodes from the tree. It also shows to call the |phc| parser
and unparsers from plugins.</para>

</section>
<section>

<title>Reference</title>

<para>|phc| represents PHP scripts internally as an abstract syntax tree. The
structure of this tree is dictated by the <xref linkend="grammar"
endterm="grammar.title">. The grammar definition is a very important part of
|phc|.

<para>|phc|'s view on the world (as dictated by the grammar) does not completely
agree with the PHP standard view.  <xref linkend="representingphp"
endterm="representingphp.title"> describes how the various PHP constructs get
translated into the abstract syntax.</para>

<para><xref linkend="apioverview" endterm="apioverview.title"> gives an
overview of the AST classes, the tree visitor API and the tree transformation
API from a programmer's perspective.</para>

<para><application>Maketea</application> is a tool bundled with |phc| which,
based on a grammar definition of a language, generates a C++ hierarchy for the
corresponding abstract syntax tree, a tree transformation and visitor API, and
deep cloning, deep equality and pattern matching on the AST. <xref
linkend="maketeatheory" endterm="maketeatheory.title">  explains some of the
theory behind <application>maketea</application>; in particular, the grammar
formalism, the mapping from the grammar to the AST classes, and the derivation
of the tree transformation API.</para>
	
</section>


</chapter>

<chapter id="gettingstarted">
<title id="gettingstarted.title">Getting Started</title>

<section>

<title></title>

<para>
	For this introductory tutorial, we assume that you have successfully
	downloaded and installed &phc, and that you know how to run it (<xref
	linkend="install"> and <xref linkend="runningphc">). This tutorial gets you
	started with using &phc to develop your own tools for PHP by writing
	plugins.
</para>

</section>

<section>
<title>Compiling a Plugin</title>

<para>
	To get up and running, we'll first write a &ldquo;hello world&rdquo; plugin
	that does nothing except print a string. Create a new directory, say
	<filename>~/myplugins</filename> and create a new file
	<filename>helloworld.cpp</filename>:
</para>

<programlisting>
<reserved>#include</reserved> &lt;AST.h&gt;
<reserved>#include</reserved> &lt;pass_manager/Plugin_pass.h&gt;

<reserved>extern</reserved> "C" <reserved>void</reserved> load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

<reserved>extern</reserved> "C" <reserved>void</reserved> run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
   cout &lt;&lt; "Hello world (I'm a phc plugin!)" &lt;&lt; endl;
}

</programlisting>

<para>
	This is an example of an (almost) minimal plugin. Every plugin you write
	must contain these functions, with these exact signatures. <code>load</code>
	is run when &phc starts, giving your plugin the opportunity to add itself to
	the list of passes &phc; runs. In this example, it is added after the "ast"
	pass. When &phc processes a PHP script, it runs all of the passes on it in
	turn. When it's your plugin's turn, it calls your version of
	<code>run_ast</code>.
</para>
<para>
	To compile the plugin, run
</para>

<screen>
~/myplugins$ phc_compile_plugin helloworld.cpp
</screen>
			
<para>
	(<application>phc_compile_plugin</application> is a small shellscript that
	makes the task of compiling plugins easier; it calls
	<application>g++</application> in a platform independent way; if you're
	curious, you can open it in any text editor.) Finally, run the plugin using
</para>

<screen>
~/myplugins$ phc --run helloworld.la sometest.php
</screen>

<para>
	(You need to pass in an input script to &phc even though our plugin does not
	use it.) If that worked as expected, congratulations: you've just written
	your first &phc plugin! :-)
</para>

</section>

<section>
<title>About <code>extern "C"</code></title>

<para>
	You may have been wondering what the <code>extern "C"</code> in the
	definition of <code>load</code> and <code>run_ast</code> is for; the reason
	is that &phc uses the <code>libtool</code>'s <code>libltdl</code> interface
	to load your plugin; if the functions are not declared as <code>extern
	"C"</code>, &phc will not be able to find them in your plugin because the
	name of that function will have been mangled by the C++ compiler. It does
	not mean that you cannot write C++ code inside these functions.
</para>

<para>
	If you don't understand any of that, don't worry about it: just remember
	that you need to declare <code>load</code>, <code>run_ast</code>, and a
	small number of other functions which we'll name later, as <code>extern
	"C"</code> and everything will be fine. (You don't need <code>extern
	"C"</code> for any functions you might define).
</para>

</section>

<section>
<title>Abstract Syntax</title>

<para>
	To be able to do anything useful in your plugins, you need to know how &phc
	represents PHP code internally. &phc's view of PHP scripts is described by
	an <emphasis>abstract grammar</emphasis>. An abstract grammar describes how
	the contents of a PHP script are structured. A grammar consists of a number
	of rules. For example, there is a rule in the grammar that describes how
	<code>if</code> statements work:
</para>

<programlisting>
If ::= Expr <emphasis>iftrue:</emphasis>Statement* <emphasis>iffalse:</emphasis>Statement* ; 
</programlisting>

<para>
	This rules reads: &ldquo;<emphasis>An <code>if</code> statement consists of
	an expression</emphasis> (the condition of the if-statement), <emphasis>a
	list of statements called `iftrue'</emphasis> (the instructions that get
	executed when the condition holds), <emphasis>and another list of statements
	called `iffalse'</emphasis> (the instructions that get executed when the
	condition does not hold)&rdquo;. The asterisk (<code>*</code>) in the rule
	means &ldquo;list of&rdquo;.
</para>
			
<para>
	As a second example, consider the rule that describes arrays in PHP.  This
	rule should cover things such as <code>array()</code>, <code>array("a",
	"b")</code> and <code>array(1 =&gt; "a", 2 =&gt; "g")</code>. Arrays are
	described by the following two rules.
</para>

<programlisting>
Array ::= Array_elem* ;
Array_elem ::= <emphasis>key:</emphasis>Expr? <emphasis>val:</emphasis>Expr ;
</programlisting>

<para>
	(Actually, this is a simplification, but it will do for the moment.) These
	two rules say that &ldquo;<emphasis>an array consists of a list of array
	elements</emphasis>&rdquo;, and an &ldquo;<emphasis>array element has an
	optional expression called `key', and a second expression called
	`val'</emphasis>&rdquo;. The question mark (<code>?</code>) means
	&ldquo;optional&rdquo;. Note that the grammar does not record the need for
	the keyword <code>array</code>, or for the parentheses and commas.  We do
	not need to record these, because we already <emphasis>know</emphasis> that
	we are talking about an array; all we need to know is what the array
	elements are.
</para>
		
</section>

<section>
<title>The Abstract Syntax Tree</title>

<para>
	When &phc reads a PHP script, it builds up an internal representation of the
	script. This representation is known as an <emphasis>abstract syntax
	tree</emphasis> (or AST for short). The structure of the AST follows
	directly from the abstract grammar. For people familiar with XML, this tree
	can be compared to the DOM representation of an XML script (and in fact,
	&phc can output the AST as an XML document, see <xref
	linkend="runningphc">).
</para>
			
<para>
	For example, consider <code>if</code>-statements again. An
	<code>if</code>-statement is represented by an instance of the
	<code>If</code> class, which is (approximately) defined as follows.
</para>

<programlisting>
<reserved>class</reserved> If
{
<reserved>public</reserved>:
   Expr* expr;
   Statement_list* iftrue;
   Statement_list* iffalse;
};
</programlisting>

<para>
	Thus, the name of the rule (<code>if ::= ...</code>) translates into a class
	<code>If</code>, and the elements on the right hand side of the rule
	(<code>Expr iftrue:Statement* iffalse:Statement*</code>) correspond directly
	to the class members.  The class <code>Statement_list</code> inherits from
	the STL <code>list</code> class, and can thus be treated as such.
</para>
		
<para>
	Similarly, the class definitions for arrays and array elements look like
</para> 
		
<programlisting>
<reserved>class</reserved> Array
{
<reserved>public</reserved>:
   Array_elem_list* array_elems;
};

<reserved>class</reserved> Array_elem
{
<reserved>public</reserved>:
   Expr* key;
   Expr* val;
};
</programlisting>

<para>
	When you start developing applications with &phc you will find it useful to
	consult the full description of the grammar, which can be found in <xref
	linkend="grammar">. A detailed explanation of the structure of this grammar,
	and how it converts to the C++ class structure, can be found in <xref
	linkend="maketeatheory">. Some notes on how &phc converts normal PHP code
	into abstract syntax can be found in <xref linkend="representingphp">.
</para>

</section>

<section>
<title>Working with the AST</title>

<para>
	When you want to build tools based on &phc, you do not have to understand
	how the abstract syntax tree is built, because this is done for you.  Once
	the tree has been built, you can examine or modify the tree in any way you
	want. When you are finished, you can ask &phc to output the tree to normal
	PHP code again.
</para> 

<para>
	Let's write a very simple plugin that counts the number of statements in a
	script. Create a new file
	<filename>~/myplugins/count_statements.cpp</filename>. Recall the skeleton
	plugin:
</para>
		
<programlisting>
<reserved>#include</reserved> &lt;AST.h&gt;
<reserved>#include</reserved> &lt;pass_manager/Plugin_pass.h&gt;

<reserved>extern</reserved> "C" <reserved>void</reserved> load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

<reserved>extern</reserved> "C" <reserved>void</reserved> run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
}
</programlisting>

<para>
	You will notice that <code>run_ast</code> gets passed an object of type
	<code>PHP_script</code>. This is the top-level node of the generated
	AST. If you look at the grammar (<xref linkend="grammar">), you will find
	that <code>PHP_script</code> corresponds to the following rule:
</para>
	
<programlisting>
PHP_script ::= Statement* ;
</programlisting>

<para>
	Thus, as far as &phc is concerned, a PHP script consists of a number of
	statements. The class <code>PHP_script</code> will have therefore have
	one member, called <code>statements</code>, the list of statements. So, to
	count the number of classes, all we have to do is query the number of
	elements in the <code>statements</code> list:
</para>

<programlisting>
<reserved>#include</reserved> &lt;AST.h&gt;
<reserved>#include</reserved> &lt;pass_manager/Plugin_pass.h&gt;

<reserved>extern</reserved> "C" <reserved>void</reserved> load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

<reserved>extern</reserved> "C" <reserved>void</reserved> run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
   printf("%d statement(s) found\n", in->statements->size());
}
</programlisting>

<para>
	Save this file to <filename>~/myplugins/count_statements.cpp</filename>.
	Compile:
</para>

<programlisting>
~/myplugins$ phc_compile_plugin count_statements.cpp
</programlisting>

<para>
	And run:
</para>

<programlisting>
./phc --run count_statements.la hello.php
</programlisting>

</section>

<section>
<title>Actually..</title>

<para>
	If you actually did try to run your plugin, you may have found that our
	plugin isn't quite correct. Consider the following example:
</para>

<programlisting>
&lt;?<reserved>php</reserved>
   $x = 5;
   <reserved>if</reserved>($x == 5)
      <reserved>echo</reserved> "yes";
   <reserved>else</reserved>
      <reserved>echo</reserved> "no";
?&gt;
</programlisting>

<para> If you run our plugin on this example, if will report two statements.
Why? Well, the first statement is the assignment, and the second is the
conditional (the <code>if</code> statement). The statements
<emphasis>inside</emphasis> the <code>if</code> statement are not counted,
because they are not part of the outer list of statements of the script. In the
next tutorial we will see how to fix this. </para>

</section>

<section>
<title>Writing Stand Alone Applications</title>

<para>
	If you prefer not to write a plugin but want to modify &phc itself to derive
	a new, stand-alone, application, you can add your passes in
	<filename>src/phc.cpp</filename> in the &phc source tree instead. This has
	the effect of &ldquo;hardcoding&rdquo; your plugin into &phc; (in versions
	before 0.1.7, this was the only way to write extensions).  However, in the
	rest of the tutorials we will assume that you are writing your extension as
	a plugin.
</para>

</section>

<section>
<title>What's Next?</title>

<para>
	In theory, you now know enough to start implementing your own tools for PHP.
	Write a new plugin, run the plugin using the <code>--run</code> option, and
	optionally pass in the <code>--pretty-print</code> option also to request
	that &phc outputs the tree back to PHP syntax after having executed your
	plugin.
</para>

<para>
	However, you will probably find that modifying the tree, despite being
	well-defined and easy to understand, is actually rather laborious.  It
	requires a lot of boring boilerplate code. The good news is that &phc
	provides sophisticated support for examining and modifying this tree. This
	is explained in detail in the follow-up tutorials.
</para>

</section>

</chapter>

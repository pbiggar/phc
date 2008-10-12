<chapter id="treetutorial6">
<title id="treetutorial6.title">Returning Lists</title>

<section>
<title></title>

<para>
	In this tutorial we will develop step-by-step a transform that expands
	<code>include</code> statements. For example, if <filename>b.php</filename>
	is 
</para>

<programlisting>
&lt;?<reserved>php</reserved>
   echo "Hello world";
?&gt;
</programlisting>
			
<para>and <filename>a.php</filename> is</para> 

<programlisting>
&lt;?<reserved>php</reserved>
   include "b.php";
   echo "Goodbye!";
?&gt;
</programlisting>

<para>
	Then running the transform on <filename>a.php</filename> yields 
</para>

<programlisting>
&lt;?<reserved>php</reserved>
   echo "Hello world\n";
   echo "Goodbye\n";
?&gt;
</programlisting>

<para> The transform we will develop in this tutorial is only a simple
implementation of <code>include</code>s, and we won't take every feature of
<code>include</code> into account. However, it can serve as a basis for more
full-featured version. The transform we will develop here is available as
<filename>plugins/tutorials/Expand_includes.la</filename>. </para>

</section>
<section>

<title> Deleting Nodes </title>

<para>
	Our transform should process <code>include</code> statements.  In the AST,
	<code>include</code>s are represented as method invocations. Thus, we might
	start like this: 
</para>

<programlisting>
<reserved>class</reserved> Expand_includes : <reserved>public</reserved> Transform
{
<reserved>public</reserved>:
   Expr* pre_method_invocation(Method_invocation* in)
   {
      <emphasis>// Process includes</emphasis>
   }
};
</programlisting>

<para>
	However, this will not get us very far. The return type of
	<code>pre_method_invocation</code> is an <code>Expr</code>.  That means that
	we can replace the method invocation (the <code>include</code> statement)
	only by another, single, expression. But we want to replace it by the
	contents of the specified file! 
</para>

<para>
	Recall from <xref linkend="treetutorial1"> that to turn an expression into a
	statement, &phc inserts an <code>Eval_expr</code> in the abstract syntax
	tree.  Thus, if we want to process <code>include</code> statements, we could
	also look at all <code>eval_expr</code> nodes. Assuming for the moment we
	can make that work, does it get us any further? As a matter of fact, it
	does! If you check <filename>AST_transform.h</filename>, you will see that
	the signature for <code>pre_eval_expr</code> is 
</para>

<programlisting>
<reserved>void</reserved> pre_eval_expr(Eval_expr* in, Statement_list* out)
</programlisting>

<para>
	This is different from the signatures we have seen so far. For nodes that
	can be replaced by a number of new nodes, the pre transform and post
	transform methods will not have a return value in their signature, but have
	an extra <code>xxx_List</code> argument.  This list is initialised to
	be empty before <code>pre_eval_expr</code> is invoked, and when
	<code>pre_eval_expr</code> returns, the nodes in this list will replace
	<code>*in</code>. If the list is empty, the node is simply deleted from the
	tree. 
</para>

<para>
	So, we will use the following p lugin as our starting point. Executing this
	plugin deletes all <code>Eval_expr</code> nodes from the tree (try it!). 
</para>

<programlisting>
<reserved>#include</reserved> "AST_transform.h"

<reserved>class</reserved> Expand_includes : <reserved>public</reserved> Transform
{
<reserved>public</reserved>:
   <reserved>void</reserved> pre_eval_expr(Eval_expr* in, Statement_list* out)
   {
   }
};

<reserved>extern</reserved> "C" <reserved>void</reserved> load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

<reserved>extern</reserved> "C" <reserved>void</reserved> run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
   Expand_includes einc;
   in->transform_children(&amp;einc);
}
</programlisting>

</section>
<section>

<title> Using the XML unparser </title>

<para>
	So, we now want to do something more useful than deleting all
	<code>eval_expr</code> nodes from the tree. The first thing we need to be
	able to do is distinguish <code>include</code> statements from other
	<code>eval_expr</code> nodes. We can use pattern matching (see <xref
	linkend="treetutorial3"> and <xref linkend="treetutorial4"> ) to do that -
	but what should we match against? If you are unsure about the structure of
	the tree, it can be quite useful to use the XML unparser to find out what
	the tree looks like. We modify the plugin as follows: 
</para>

<programlisting>
<reserved>#include</reserved> "AST_transform.h"
<reserved>#include</reserved> "process_ir/XML_unparser.h"

<reserved>class</reserved> Expand_includes : <reserved>public</reserved> Transform
{
<reserved>private</reserved>:
   XML_unparser* xml_unparser;

<reserved>public</reserved>:
   Expand_includes()
   {
      <emphasis>// Send output to cout, do not print attributes</emphasis>
      xml_unparser = <reserved>new</reserved> XML_unparser(cout, false);
   }

<reserved>public</reserved>:
   <reserved>void</reserved> pre_eval_expr(Eval_expr* in, Statement_list* out)
   {
      in->visit(xml_unparser);
   }
};
</programlisting>

<para>
	The XML unparser is implemented using the <code>Visitor</code> API, so it
	can be invoked just like you run any other visitor. There is a similar
	visitor called <code>AST_unparser</code> (in
	<filename>&lt;process_ast/AST_unparser.h&gt;</filename>) that you can use to
	print (parts of the) AST to PHP syntax. 
</para>

<para>
	When you run this transform on <filename>a.php</filename>, it will print two
	<code>eval_expr</code> nodes (shown in XML syntax), one for the
	<code>include</code> and one for the <code>echo</code> . We are interested
	in the first, the <code>include</code>: 
</para>

<programlisting>
&lt;AST:Eval_expr&gt;
   &lt;AST:Method_invocation&gt;
      &lt;AST:Target xsi:nil="true" /&gt;
      &lt;AST:METHOD_NAME&gt;
         &lt;value&gt;include&lt;/value&gt;
      &lt;/AST:METHOD_NAME&gt;
      &lt;AST:Actual_parameter_list&gt;
         &lt;AST:Actual_parameter&gt;
            &lt;bool&gt;&lt;!-- is_ref --&gt;false&lt;/bool&gt;
            &lt;AST:STRING&gt;
               &lt;value&gt;b.php&lt;/value&gt;
            &lt;/AST:STRING&gt;
         &lt;/AST:Actual_parameter&gt;
      &lt;/AST:Actual_parameter_list&gt;
   &lt;/AST:Method_invocation&gt;
&lt;/AST:Eval_expr&gt;
</programlisting>

<para>
	This tells us that the <code>include</code> statement is an
	<code>Eval_expr</code> node (that was obvious from the fact that we
	implemented <code>pre_eval_expr</code>). The <code>Eval_expr</code> contains
	a <code>Method_invocation</code> (we knew that too, although of course a
	node of type <code>Eval_expr</code> can contain any type of expression). The
	method invocation has target <code>NULL</code> (it is not invoked on an
	object or a class), method name &ldquo;<code>include</code>&rdquo;, and a
	single parameter in the parameter list that contains the name of the file we
	are interested in. We can construct a pattern that matches this tree
	exactly: 
</para>

<programlisting>
<reserved>class</reserved> Expand_includes : <reserved>public</reserved> Transform
{
<reserved>private</reserved>:
   Wildcard&lt;STRING&gt;* filename;
   Method_invocation* pattern;

<reserved>public</reserved>:
   Expand_includes()
   {
      filename = <reserved>new</reserved> Wildcard&lt;STRING&gt;;
      pattern = 
         <reserved>new</reserved> Method_invocation(
            NULL,
            <reserved>new</reserved> METHOD_NAME(<reserved>new</reserved> String("include")),
            <reserved>new</reserved> List&lt;Actual_parameter*&gt;(
               <reserved>new</reserved> Actual_parameter(false, filename)
            )
         );
   }

<reserved>public</reserved>:
   <reserved>void</reserved> pre_eval_expr(Eval_expr* in, List&lt;Statement*&gt;* out)
   {
      <emphasis>// Check for calls to include</emphasis>
      <reserved>if</reserved>(in-&gt;expr-&gt;match(pattern))
      {
         <emphasis>// Matched! Try to parse the file</emphasis>
      }
      <reserved>else</reserved>
      {
         <emphasis>// No match; leave untouched</emphasis>
         out-&gt;push_back(in);
      }
   }
};
</programlisting>
	
<para>
	Note how the construction of the pattern follows the structure of the tree
	as output by the XML unparser exactly. The only difference is that we leave
	the actual filename a wildcard; obviously, we want to be able to match
	against any <code>include</code>, not just <code>include("a.php")</code>.
	Running this transform should remove the <code>include</code> from the file,
	but leave the other statements untouched (note that we need to
	<code>push_back in</code> to <code>out</code> to make sure a statement does
	not get deleted). 
</para>

</section>
<section>

<title> The Full Transform </title>

<para>
	We are nearly done! All that's left is to parse the file (we can use the
	&ldquo;<code>filename</code>&rdquo; wildcard to find out which file we need
	to include) and insert all statements into the parsed file at the point of
	the include. Parsing PHP is hard, but of course &phc; comes with a PHP
	parser. To use this parser, include the
	<filename>&lt;parsing/parse.h&gt;</filename> header and call
	&ldquo;<code>parse</code>&rdquo;.  Here then is the full transform: 
</para>  

<programlisting>
<reserved>#include</reserved> "AST_transform.h"
<reserved>#include</reserved> "parsing/parse.h"
<reserved>#include</reserved> "process_ir/XML_unparser.h"

<reserved>class</reserved> Expand_includes : <reserved>public</reserved> Transform
{
<reserved>private</reserved>:
   XML_unparser* xml_unparser;
   Wildcard&lt;STRING&gt;* filename;
   Method_invocation* pattern;

<reserved>public</reserved>:
   Expand_includes()
   {
      xml_unparser = <reserved>new</reserved> XML_unparser(cout, false);

      filename = <reserved>new</reserved> Wildcard&lt;STRING&gt;;
      pattern = 
         <reserved>new</reserved> Method_invocation(
            NULL,
            <reserved>new</reserved> METHOD_NAME(<reserved>new</reserved> String("include")),
            <reserved>new</reserved> List&lt;Actual_parameter*&gt;(
               <reserved>new</reserved> Actual_parameter(false, filename)
            )
         );
   }

<reserved>public</reserved>:
   <reserved>void</reserved> pre_eval_expr(Eval_expr* in, List&lt;Statement*&gt;* out)
   {
      // in-&gt;visit(xml_unparser);

      <emphasis>// Check for calls to include</emphasis>
      <reserved>if</reserved>(in-&gt;expr-&gt;match(pattern))
      {
         <emphasis>// Matched! Try to parse the file</emphasis>
         PHP_script* php_script = parse(filename-&gt;value-&gt;value, NULL, false);
         <reserved>if</reserved>(php_script == NULL)
         {
            cerr 
            &lt;&lt; "Could not parse file " &lt;&lt; *filename-&gt;value-&gt;value
            &lt;&lt; " on line " &lt;&lt; in-&gt;get_line_number() &lt;&lt; endl;
            exit(-1);
         }

         <emphasis>// Replace the include by the statements in the parsed file</emphasis>
         out-&gt;push_back_all(php_script-&gt;statements);
      }
      <reserved>else</reserved>
      {
         <emphasis>// No match; leave untouched</emphasis>
         out-&gt;push_back(in);
      }
   }
};

<reserved>extern</reserved> "C" <reserved>void</reserved> load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

<reserved>extern</reserved> "C" <reserved>void</reserved> run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
   Expand_includes einc;
   in->transform_children(&amp;einc);
}
</programlisting>

<para>
	<emphasis>Exercise.</emphasis> One problem with the plugin we have developed
	is that if the file we are including in turn has <code>include</code>
	statements, they will not be processed. Modify the plugin to invoke the
	transform on the list of statements from the parsed file, taking care to
	deal with infinite loops (if the first file includes the second, and the
	second the first). 
</para>

</section>
<section>

<title> What's Next? </title>

<para>
	This is the last tutorial in this series on using the
	<code>AST_visitor</code> and <code>AST_transform</code> classes. Of
	course, the only way to really learn this stuff is to try it out for
	yourself.  Hopefully, the tutorials will help you do so.  The following
	sources should also be useful: 
</para>

<itemizedlist>
	<listitem><para>
		The <xref linkend="grammar" endterm="grammar.title"> (and the <xref
		linkend="maketeatheory" endterm="maketeatheory.title">)
	</para></listitem>
	<listitem><para>
		The explanation of how PHP gets represented in the abstract syntax as
		detailed in <xref linkend="representingphp"
		endterm="representingphp.title">
	</para></listitem>
	<listitem><para>
		The definition of the C++ classes for the AST nodes in
		<filename>src/generated/AST.h</filename>
	</para></listitem>
	<listitem><para>
		The definition of the <code>AST_visitor</code> and
		<code>AST_transform</code> classes in
		<filename>src/generated/AST_visitor.h</filename> and
		<filename>src/generated/AST_transform.h&gt;</filename>
		respectively
	</para></listitem>
	</itemizedlist>

<para>
	And of course, we are more than happy to answer any other questions you
	might still have. Just send an email to the <ulink
	url="http://www.phpcompiler.org/mailinglist.html">mailing list</ulink> and
	we'll do our best to answer you as quickly as possible! Happy coding! 
</para>

</section>
</chapter>

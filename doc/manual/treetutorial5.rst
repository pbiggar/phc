<chapter id="treetutorial5">
<title id="treetutorial5.title">Modifying the Traversal Order</title>

<section>
<title></title>

<para>
	As explained in the previous tutorials (in particular, <xref
	linkend="treetutorial1" endterm="treetutorial1.title">), when a
	<code>AST_visitor</code> traverses a tree, it first calls
	<code>pre_xxx</code> for a node of type <emphasis>xxx</emphasis>, it then
	visits all the children of the node, and finally it calls
	<code>post_xxx</code> on the node.  For many transforms, this is sufficient
	&mdash; but not for all. Consider the following transform. Suppose we want
	to add comments to the <emphasis>true</emphasis> and
	<emphasis>false</emphasis> branches of an <emphasis>if</emphasis>-statement,
	so that the following example 
</para>

<programlisting>
&lt;?<reserved>php</reserved>
   <reserved>if</reserved>($expr)
   {
      <reserved>echo</reserved> "Do something";
   }
   <reserved>else</reserved>
   {
      <reserved>echo</reserved> "Do something else";
   }
?&gt;
</programlisting>
	
<para> is translated to </para>
		
<programlisting>
&lt;?<reserved>php</reserved>
   <reserved>if</reserved>($expr)
   {
      <emphasis>/* TODO: Insert comment */</emphasis>
      <reserved>echo</reserved> "Do something";
   }
   <reserved>else</reserved>
   {
      <emphasis>/* TODO: Insert comment */</emphasis>
      <reserved>echo</reserved> "Do something else";
   }
?&gt;
</programlisting>

<para>
	This appears to be a simple transform. One way to do implement it would be
	to introduce a flag <code>comment</code> that is set to <code>true</code>
	when we encounter an <code>If</code> (i.e., in <code>pre_if</code>). Then in
	<code>post_statement</code> we could check for this flag, and if it is set,
	we could add the required comment to the statement, and reset the flag to
	<code>false</code>.  
</para>

<para>
	However, this will only add a comment to the first statement in the
	<emphasis>true</emphasis> branch (try it!). To add a comment to the first
	statement in the <emphasis>false</emphasis> branch too, we should set the
	flag to <code>true</code> in between visiting the children of the
	<emphasis>true</emphasis> branch and visiting the children of the
	<emphasis>false</emphasis> branch. To be able to do this, we need to modify
	<code>children_if</code>, as explained in the next section. 
</para>

</section>
<section>

<title> The Solution </title>

<para>
	For every AST node type <emphasis>xxx</emphasis>, the AST Transform API
	defines a method called <code>children_xxx</code>. This method is
	responsible for visiting all the children of the node. The default
	implementation for <code>If</code> is: 
</para>

<programlisting>
<reserved>void </reserved>Visitor::children_if(If* in)
{  
    visit_expr(in->expr);
    visit_statement_list(in->iftrue);
    visit_statement_list(in->iffalse);
}
</programlisting>

<para>
	(you can find this definition in <filename>AST_visitor.cpp</filename>). If
	you want to change the order in which the children of a node are visited,
	entirely avoid visiting some children, or simply execute a piece of code in
	between two children, this is the method you will need to modify. 
</para>

<para> Here is the transform that does what we need (available as
<filename>plugins/tutorials/Comment_ifs.la</filename>): </para>

<programlisting>
<reserved>#include</reserved> "AST_visitor.h"

<reserved>class</reserved> Comment_ifs : <reserved>public</reserved> Visitor
{
<reserved>private</reserved>:
   bool comment;

<reserved>public</reserved>:
   Comment_ifs()
   {
      comment = <reserved>false</reserved>; 
   }

   <reserved>void</reserved> children_if(If* in)
   {
      visit_expr(in-&gt;expr);
      comment = <reserved>true</reserved>;
      visit_statement_list(in-&gt;iftrue);
      comment = <reserved>true</reserved>;
      visit_statement_list(in-&gt;iffalse);
      comment = <reserved>false</reserved>;
   }

   <reserved>void</reserved> post_statement(Statement* in)
   {
      <reserved>if</reserved>(comment && in-&gt;get_comments()-&gt;empty())
         in-&gt;get_comments()-&gt;push_back(new String("/* TODO: Insert comment */"));

      comment = <reserved>false</reserved>;
   }
};
</programlisting>

</section>

<section>

<title> What's Next? </title>

<para> <xref linkend="treetutorial6"> explains how to deal with transforms that
can replace a single node by multiple new nodes, and shows how to call the
&phc; parser and unparser from your plugins. </para>

</section>

</chapter>

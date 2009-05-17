<chapter id="treetutorial4">
<title id="treetutorial4.title">Using State</title>

<section>
<title></title>

<para>
	This tutorial explains an advanced feature of pattern matching, and shows an
	important technique in writing tree transforms: the use of state.  Suppose
	we are continuing the refactoring tool that we began in <xref
	linkend="treetutorial2">, and suppose that we have replaced all calls to
	database specific functions by calls to the generic DBX functions. To finish
	the refactoring, we want to rename any function ``foo`` in the
	script to ``foo_DB``, if it makes use of the database &mdash; this
	clearly sets functions that use the database apart, which may make the
	structure of the script clearer.  
</para>

<para>
	So, we want to write a transform that renames all functions ``foo``
	to ``foo_DB``, if there is one or more call within that function to
	any ``dbx_``<emphasis>something</emphasis> function.  Here is a
	simple example: 
</para>

<programlisting>
<?<reserved>php</reserved>
   <reserved>function</reserved> first()
   {
      <reserved>global</reserved> $link;
      $error = dbx_error($link);
   }

   <reserved>function</reserved> second()
   {
      <reserved>echo</reserved> "Do something else";
   }
?>
</programlisting>
	
<para>
	After the transform, we should get 
</para>
	
<programlisting>
<?<reserved>php</reserved>
   <reserved>function</reserved> first<boxed>_DB</boxed>()
   {
      <reserved>global</reserved> $link;
      $error = dbx_error($link);
   }

   <reserved>function</reserved> second()
   {
      <reserved>echo</reserved> "Do something else";
   }
?>
</programlisting>

</section>
<section>

<title>The Implementation</title>

<para>
	Since we have to modify method (function) names, the nodes we are interested
	in are the nodes of type ``Method``. However, how do we know when
	to modify a particular method? Should we search the method body for function
	calls to ``dbx_``<emphasis>xxx</emphasis>? As we saw in <xref
	linkend="treetutorial1">, manual searching through the tree is cumbersome;
	there must be a better solution. 
</para> 

<para>
	The solution is in fact very easy. At the start of each method, we set a
	variable ``uses_dbx`` to ``false``. When we process the
	method, we set ``uses_dbx`` to ``true`` when we find a
	function call to a DBX function.  Then at the end of the method, we check
	``uses_dbx``; if it was set to ``true``, we modify the
	name of the method.  This tactic is implement by the following transform
	(available as <filename>plugins/tutorials/InsertDB.la</filename> in the
	|phc| distribution). Note the use of ``pre_method`` and
	``post_method`` to initialise and check ``use_dbx``,
	respectively. (Because we don't need to modify the structure of the tree in
	this transform, we use the simpler ``AST_visitor`` API instead of
	the ``AST_transform`` API.) 
</para>

<programlisting>
<reserved>class</reserved> InsertDB : <reserved>public</reserved> Visitor
{
<reserved>private</reserved>:
   <reserved>int</reserved> uses_dbx;
   
<reserved>public</reserved>:
   <reserved>void</reserved> pre_method(Method* in)
   {
      uses_dbx = <reserved>false</reserved>;   
   }

   <reserved>void</reserved> post_method(Method* in)
   {
      <reserved>if</reserved>(uses_dbx)
         in->signature->method_name->value->append("_DB");
   }

   <reserved>void</reserved> post_method_invocation(Method_invocation* in)
   {
      Wildcard<METHOD_NAME>* pattern = <reserved>new</reserved> Wildcard<METHOD_NAME>;
      
      <emphasis>// Check for dbx_</emphasis>
      <reserved>if</reserved>(in->method_name->match(pattern) && 
         pattern->value->value->find("dbx_") == 0)
      {
         uses_dbx = <reserved>true</reserved>;
      }
   }
};
</programlisting>

<para>
	In <xref linkend="treetutorial2">, we simply wanted to check for a
	particular function name, and we used ``match`` to do this: 
</para>
     
<programlisting>
<reserved>if</reserved>(in->match(<reserved>new</reserved> METHOD_NAME("mysql_connect")))
</programlisting>

<para>
	Here, we need to check for method names that start with ``dbx_``.
	We use the STL method ``find`` to do this, but we cannot call this
	directly on ``in->method_name`` because
	``in->method_name`` has type ``Method_name`` (could
	either be a ``METHOD_NAME`` or a ``Reflection`` node).
	However, calling ``match`` on a pattern has the side effect of
	setting the ``value`` to point to the node that was matched by the
	wildcard. So, if the match succeeds, we know that the name of the method
	must have been a ``METHOD_NAME``, and we can access this name by
	accessing ``pattern->value``
	(``pattern->value->value`` is the value field of the
	``METHOD_NAME`` itself, i.e., the actual string that stores the
	name of the method.) 
</para>

<para>
	(Of course, this transform is not complete; renaming methods is not enough,
	we must also rename the corresponding method invocations. This is left as an
	exercise for the reader.) 
</para> 

</section>
<section>

<title> What's Next? </title>

<para>
	<xref linkend="treetutorial5"> explains how to change the order in which the
	children of a node are visited, avoid visiting some children, or how to
	execute a piece of code in between visiting two children.
</para>

</section>

</chapter>

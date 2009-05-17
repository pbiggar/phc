<chapter id="treetutorial6">
<title id="treetutorial6.title">Returning Lists</title>

<section>
<title></title>

<para>
	In this tutorial we will develop step-by-step a transform that expands
	``include`` statements. For example, if :file:`b.php`
	is 
</para>

.. sourcecode::

<?php
   echo "Hello world";
?>

			
<para>and :file:`a.php` is</para> 

.. sourcecode::

<?php
   include "b.php";
   echo "Goodbye!";
?>


<para>
	Then running the transform on :file:`a.php` yields 
</para>

.. sourcecode::

<?php
   echo "Hello world\n";
   echo "Goodbye\n";
?>


<para> The transform we will develop in this tutorial is only a simple
implementation of ``include``s, and we won't take every feature of
``include`` into account. However, it can serve as a basis for more
full-featured version. The transform we will develop here is available as
:file:`plugins/tutorials/Expand_includes.la`. </para>

</section>
<section>

<title> Deleting Nodes </title>

<para>
	Our transform should process ``include`` statements.  In the AST,
	``include``s are represented as method invocations. Thus, we might
	start like this: 
</para>

.. sourcecode::

class Expand_includes : public Transform
{
public:
   Expr* pre_method_invocation(Method_invocation* in)
   {
      <emphasis>// Process includes</emphasis>
   }
};


<para>
	However, this will not get us very far. The return type of
	``pre_method_invocation`` is an ``Expr``.  That means that
	we can replace the method invocation (the ``include`` statement)
	only by another, single, expression. But we want to replace it by the
	contents of the specified file! 
</para>

<para>
	Recall from <xref linkend="treetutorial1"> that to turn an expression into a
	statement, |phc| inserts an ``Eval_expr`` in the abstract syntax
	tree.  Thus, if we want to process ``include`` statements, we could
	also look at all ``eval_expr`` nodes. Assuming for the moment we
	can make that work, does it get us any further? As a matter of fact, it
	does! If you check :file:`AST_transform.h`, you will see that
	the signature for ``pre_eval_expr`` is 
</para>

.. sourcecode::

void pre_eval_expr(Eval_expr* in, Statement_list* out)


<para>
	This is different from the signatures we have seen so far. For nodes that
	can be replaced by a number of new nodes, the pre transform and post
	transform methods will not have a return value in their signature, but have
	an extra ``xxx_List`` argument.  This list is initialised to
	be empty before ``pre_eval_expr`` is invoked, and when
	``pre_eval_expr`` returns, the nodes in this list will replace
	``*in``. If the list is empty, the node is simply deleted from the
	tree. 
</para>

<para>
	So, we will use the following p lugin as our starting point. Executing this
	plugin deletes all ``Eval_expr`` nodes from the tree (try it!). 
</para>

.. sourcecode::

#include "AST_transform.h"

class Expand_includes : public Transform
{
public:
   void pre_eval_expr(Eval_expr* in, Statement_list* out)
   {
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
   Expand_includes einc;
   in->transform_children(&amp;einc);
}


</section>
<section>

<title> Using the XML unparser </title>

<para>
	So, we now want to do something more useful than deleting all
	``eval_expr`` nodes from the tree. The first thing we need to be
	able to do is distinguish ``include`` statements from other
	``eval_expr`` nodes. We can use pattern matching (see <xref
	linkend="treetutorial3"> and <xref linkend="treetutorial4"> ) to do that -
	but what should we match against? If you are unsure about the structure of
	the tree, it can be quite useful to use the XML unparser to find out what
	the tree looks like. We modify the plugin as follows: 
</para>

.. sourcecode::

#include "AST_transform.h"
#include "process_ir/XML_unparser.h"

class Expand_includes : public Transform
{
private:
   XML_unparser* xml_unparser;

public:
   Expand_includes()
   {
      <emphasis>// Send output to cout, do not print attributes</emphasis>
      xml_unparser = new XML_unparser(cout, false);
   }

public:
   void pre_eval_expr(Eval_expr* in, Statement_list* out)
   {
      in->visit(xml_unparser);
   }
};


<para>
	The XML unparser is implemented using the ``Visitor`` API, so it
	can be invoked just like you run any other visitor. There is a similar
	visitor called ``AST_unparser`` (in
	:file:`<process_ast/AST_unparser.h>`) that you can use to
	print (parts of the) AST to PHP syntax. 
</para>

<para>
	When you run this transform on :file:`a.php`, it will print two
	``eval_expr`` nodes (shown in XML syntax), one for the
	``include`` and one for the ``echo`` . We are interested
	in the first, the ``include``: 
</para>

.. sourcecode::

<AST:Eval_expr>
   <AST:Method_invocation>
      <AST:Target xsi:nil="true" />
      <AST:METHOD_NAME>
         <value>include</value>
      </AST:METHOD_NAME>
      <AST:Actual_parameter_list>
         <AST:Actual_parameter>
            <bool><!-- is_ref -->false</bool>
            <AST:STRING>
               <value>b.php</value>
            </AST:STRING>
         </AST:Actual_parameter>
      </AST:Actual_parameter_list>
   </AST:Method_invocation>
</AST:Eval_expr>


<para>
	This tells us that the ``include`` statement is an
	``Eval_expr`` node (that was obvious from the fact that we
	implemented ``pre_eval_expr``). The ``Eval_expr`` contains
	a ``Method_invocation`` (we knew that too, although of course a
	node of type ``Eval_expr`` can contain any type of expression). The
	method invocation has target ``NULL`` (it is not invoked on an
	object or a class), method name "``include``", and a
	single parameter in the parameter list that contains the name of the file we
	are interested in. We can construct a pattern that matches this tree
	exactly: 
</para>

.. sourcecode::

class Expand_includes : public Transform
{
private:
   Wildcard<STRING>* filename;
   Method_invocation* pattern;

public:
   Expand_includes()
   {
      filename = new Wildcard<STRING>;
      pattern = 
         new Method_invocation(
            NULL,
            new METHOD_NAME(new String("include")),
            new List<Actual_parameter*>(
               new Actual_parameter(false, filename)
            )
         );
   }

public:
   void pre_eval_expr(Eval_expr* in, List<Statement*>* out)
   {
      <emphasis>// Check for calls to include</emphasis>
      if(in->expr->match(pattern))
      {
         <emphasis>// Matched! Try to parse the file</emphasis>
      }
      else
      {
         <emphasis>// No match; leave untouched</emphasis>
         out->push_back(in);
      }
   }
};

	
<para>
	Note how the construction of the pattern follows the structure of the tree
	as output by the XML unparser exactly. The only difference is that we leave
	the actual filename a wildcard; obviously, we want to be able to match
	against any ``include``, not just ``include("a.php")``.
	Running this transform should remove the ``include`` from the file,
	but leave the other statements untouched (note that we need to
	``push_back in`` to ``out`` to make sure a statement does
	not get deleted). 
</para>

</section>
<section>

<title> The Full Transform </title>

<para>
	We are nearly done! All that's left is to parse the file (we can use the
	"``filename``" wildcard to find out which file we need
	to include) and insert all statements into the parsed file at the point of
	the include. Parsing PHP is hard, but of course |phc| comes with a PHP
	parser. To use this parser, include the
	:file:`<parsing/parse.h>` header and call
	"``parse``".  Here then is the full transform: 
</para>  

.. sourcecode::

#include "AST_transform.h"
#include "parsing/parse.h"
#include "process_ir/XML_unparser.h"

class Expand_includes : public Transform
{
private:
   XML_unparser* xml_unparser;
   Wildcard<STRING>* filename;
   Method_invocation* pattern;

public:
   Expand_includes()
   {
      xml_unparser = new XML_unparser(cout, false);

      filename = new Wildcard<STRING>;
      pattern = 
         new Method_invocation(
            NULL,
            new METHOD_NAME(new String("include")),
            new List<Actual_parameter*>(
               new Actual_parameter(false, filename)
            )
         );
   }

public:
   void pre_eval_expr(Eval_expr* in, List<Statement*>* out)
   {
      // in->visit(xml_unparser);

      <emphasis>// Check for calls to include</emphasis>
      if(in->expr->match(pattern))
      {
         <emphasis>// Matched! Try to parse the file</emphasis>
         PHP_script* php_script = parse(filename->value->value, NULL, false);
         if(php_script == NULL)
         {
            cerr 
            << "Could not parse file " << *filename->value->value
            << " on line " << in->get_line_number() << endl;
            exit(-1);
         }

         <emphasis>// Replace the include by the statements in the parsed file</emphasis>
         out->push_back_all(php_script->statements);
      }
      else
      {
         <emphasis>// No match; leave untouched</emphasis>
         out->push_back(in);
      }
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
   pm->add_after_named_pass (pass, new String ("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
   Expand_includes einc;
   in->transform_children(&amp;einc);
}


<para>
	<emphasis>Exercise.</emphasis> One problem with the plugin we have developed
	is that if the file we are including in turn has ``include``
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
	``AST_visitor`` and ``AST_transform`` classes. Of
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
		:file:`src/generated/AST.h`
	</para></listitem>
	<listitem><para>
		The definition of the ``AST_visitor`` and
		``AST_transform`` classes in
		:file:`src/generated/AST_visitor.h` and
		:file:`src/generated/AST_transform.h>`
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

<chapter id="treetutorial5">
<title id="treetutorial5.title">Modifying the Traversal Order</title>

<section>
<title></title>

<para>
	As explained in the previous tutorials (in particular, <xref
	linkend="treetutorial1" endterm="treetutorial1.title">), when a
	``AST_visitor`` traverses a tree, it first calls
	``pre_xxx`` for a node of type <emphasis>xxx</emphasis>, it then
	visits all the children of the node, and finally it calls
	``post_xxx`` on the node.  For many transforms, this is sufficient
	&mdash; but not for all. Consider the following transform. Suppose we want
	to add comments to the <emphasis>true</emphasis> and
	<emphasis>false</emphasis> branches of an <emphasis>if</emphasis>-statement,
	so that the following example 
</para>

.. sourcecode::

<?php
   if($expr)
   {
      echo "Do something";
   }
   else
   {
      echo "Do something else";
   }
?>

	
<para> is translated to </para>
		
.. sourcecode::

<?php
   if($expr)
   {
      <emphasis>/* TODO: Insert comment */</emphasis>
      echo "Do something";
   }
   else
   {
      <emphasis>/* TODO: Insert comment */</emphasis>
      echo "Do something else";
   }
?>


<para>
	This appears to be a simple transform. One way to do implement it would be
	to introduce a flag ``comment`` that is set to ``true``
	when we encounter an ``If`` (i.e., in ``pre_if``). Then in
	``post_statement`` we could check for this flag, and if it is set,
	we could add the required comment to the statement, and reset the flag to
	``false``.  
</para>

<para>
	However, this will only add a comment to the first statement in the
	<emphasis>true</emphasis> branch (try it!). To add a comment to the first
	statement in the <emphasis>false</emphasis> branch too, we should set the
	flag to ``true`` in between visiting the children of the
	<emphasis>true</emphasis> branch and visiting the children of the
	<emphasis>false</emphasis> branch. To be able to do this, we need to modify
	``children_if``, as explained in the next section. 
</para>

</section>
<section>

<title> The Solution </title>

<para>
	For every AST node type <emphasis>xxx</emphasis>, the AST Transform API
	defines a method called ``children_xxx``. This method is
	responsible for visiting all the children of the node. The default
	implementation for ``If`` is: 
</para>

.. sourcecode::

void Visitor::children_if(If* in)
{  
    visit_expr(in->expr);
    visit_statement_list(in->iftrue);
    visit_statement_list(in->iffalse);
}


<para>
	(you can find this definition in :file:`AST_visitor.cpp`). If
	you want to change the order in which the children of a node are visited,
	entirely avoid visiting some children, or simply execute a piece of code in
	between two children, this is the method you will need to modify. 
</para>

<para> Here is the transform that does what we need (available as
:file:`plugins/tutorials/Comment_ifs.la`): </para>

.. sourcecode::

#include "AST_visitor.h"

class Comment_ifs : public Visitor
{
private:
   bool comment;

public:
   Comment_ifs()
   {
      comment = false; 
   }

   void children_if(If* in)
   {
      visit_expr(in->expr);
      comment = true;
      visit_statement_list(in->iftrue);
      comment = true;
      visit_statement_list(in->iffalse);
      comment = false;
   }

   void post_statement(Statement* in)
   {
      if(comment && in->get_comments()->empty())
         in->get_comments()->push_back(new String("/* TODO: Insert comment */"));

      comment = false;
   }
};


</section>

<section>

<title> What's Next? </title>

<para> <xref linkend="treetutorial6"> explains how to deal with transforms that
can replace a single node by multiple new nodes, and shows how to call the
|phc| parser and unparser from your plugins. </para>

</section>

</chapter>

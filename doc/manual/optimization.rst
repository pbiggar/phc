.. _optimization:

Optimization
============

|phc| now incorporates full dataflow analysis and a number of useful optimizations as a result.  
Users can take advantage of these built in optimizations by passing the :option:`-O` flag to |phc|.  
This is equivilant to the gcc :option:`-O` flag and thus a number or 's' must follow it (:option:`-O1`, 
:option:`-Os` etc.).  It is also passed to gcc if applicible.  It is also possible to dump information about 
optimizations, such as debug information and CFGs.  Developers also have the option of writing their own 
optimizations or modifying included optimisations.

The Pass Manager
----------------

The pass manager is central to |phc|'s operation.  It controls the execution of the different compiler passes 
which |phc| uses to parse, analyse, optimize, and ultimately, compile php code.

Its source can be viewed in src/pass_manager/Pass_manager.cpp, and how it is used can be seen in src/phc.cpp.
As you will see, each pass is added to a queue before all are run.

Listing Passes
--------------

A full list of passes and whether they are enabled or disabled by default can be obtained by simply 
running phc with the :option:`--list-passes` flag:

.. sourcecode:: bash
   
  phc --list-passes

Optimization passes are denoted by 'OPT' or 'IPA' (Interprocedural Optimizations).  The source code 
for these optimizations can be found easily in the src/optimize directory.

Writing an Optimization
-----------------------

An optimization is simply a class which follows both of the following rules:
	
   1. It must inherit from CFG_Visitor.
   2. It must define a run () method.

The Visit_once subclass of CFG_Visitor defines a simple run () method where visit_block () and transform_block () 
are called on every block.  It can be useful for many optimization classes to simply inherit from this.

visit_block () will analyse each block in the program and call visit_basic_block () and one of visit_branch_block (),
visit_statement_block () etc. depending on the type of block.  You should define these methods according to what
behaviour you wish your optimization to follow.  A list of other visitor methods can be seen in src/optimizr/CFG_visitor.cpp.

You can run your optimization as a plugin (See 'Getting Started' for details).

Dumping a Control Flow Graph
----------------------------

Control flow graphs can be dumped easily using the :option:`cfg-dump` flag.  The flag takes passname arguments 
(which can be obtained from the list of passes (see above) ) and causes a CFG for the specified pass(es) to be
dumped to stdout in the dot language.

.. sourcecode:: bash

   phc helloworld.php -O2 --cfg-dump=dce,rlb

Generally, it is advised to pipe stdout to dot and use the :option:`-Tps` flag, and to redirect dot's output to 
a .ps file, which can be viewed in graphviz:

.. sourcecode:: bash

  phc helloworld.php -O2 --cfg-dump=dce,rlb | dot -Tps >a.ps
  gv a.ps

Writing and Dumping Debug Information
-------------------------------------

To dump debug information about a pass to stderr, you can use |phc|'s :option:`debug` flag in a similar fashion
to the :option:`--cfg-dump` flag, e.g.

.. sourcecode:: bash
   
   phc helloworld.php -O2 --debug=build-ssa

|phc| supports DEBUG() and CHECK_DEBUG() macros.  When writing your own optimization passes, you can use DEBUG() to
print out debug information about your pass at runtime when the :option:`--debug=yourpass` flag is passed.  If you place 
CHECK_DEBUG() at the start of a function, it will return if the debug flag for your pass is not set.

.. sourcecode:: c++

  DEBUG("This is an debug message");
 
  ...

  void my_debug_function ()
  {
     CHECK_DEBUG()
   
     ....

  }
   


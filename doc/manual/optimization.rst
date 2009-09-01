.. _optimization:

Optimization
============

|phc| now incorporates full dataflow analysis and a number of useful optimizations as a result.  
Users can take advantage of these built in optimizations by passing the :option:`-O#` flag (where # 
is a number from 1-3) to |phc|.  It is also possible to dump information about optimizations, such 
as debug information and CFGs.  Developers also have the option of writing their own optimizations
or modifying included optimisations.

The Pass Manager
----------------

The pass manager is central to |phc|'s operation.  It controls the execution of the different compiler passes 
which |phc| uses to analyse, optimize, and ultimately, compile php code.

***TODO

Listing Passes
--------------

A full list of passes and whether they are enabled or disabled by default can be obtained by simply 
running phc with the :option:`list-passes` flag:

.. sourcecode:: bash
   
  phc --list-passes

Optimization passes are denoted by 'OPT'.  The source code for these optimizations can be found easily in the src/optimize directory.

Writing an Optimization
-----------------------

An optimization is simply a class which follows both of the following rules:
	
   1. It must inherit from CFG_Visitor.
   2. It must define a run () method.

The Visit_once subclass of CFG_Visitor defines a simple run () method where each visit_block () and transform_block () are called on every
block and therefore it can be useful for many optimization classes to simply inherit from this.


***TODO: Stuff about the CFG_Visitor etc.

Once you have written your optimization and wish to try it out, you should save its header and implementation in src/optimize/ and include it at
the top of src/phc.cpp:

.. sourcecode:: c++

   ...
   #include "optimize/mynewpass.h"
   ...

You then need to add a line to src/phc.cpp so that the pass manager will add your pass to the queue.  Do this in the "Optimization Passes" section alongside
other optimizations:

.. sourcecode:: c++

   pm->add_local_optimization (new My_pass (), s("mypass"), s("A description of My Pass"), true);

Note that s() is simply a constructor for phc's own String class.  The second parameter is your pass's passname in the Pass manager, and the last one
indicates whether your pass is enabled by default (In this case, true indicates that it is).

Ordering can be important, so you may have to be careful where you insert this line.

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
   


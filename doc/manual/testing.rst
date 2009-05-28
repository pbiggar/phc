.. _testing:

Test-suite
==========


After `./configure`-ing |phc|, you may test it using:

.. sourcecode:: bash

   make test

or

.. sourcecode:: bash

   php test/framework/driver.php



The output of the test suite is similar to:

.. sourcecode:: text

   Annotated_test               Failure:     638 P,   3 F,   0 T,  21 S
   BasicParseTest               Success:     592 P,   0 F,   0 T,  70 S
   NoWhitespace                 Failure:     551 P,  41 F,   0 T,  70 S
   cb_ast                       Failure:     578 P,   4 F,   0 T,  49 S
   cb_sua                       Success:     578 P,   0 F,   0 T,  53 S
   cb_AST-to-HIR                Failure:     571 P,   3 F,   0 T,  57 S
   cb_hir                       Success:     571 P,   0 F,   0 T,  60 S
   cb_mir                       Failure:     568 P,   3 F,   0 T,  60 S
   HIR-to-MIR_dump              Success:     581 P,   0 F,   0 T,  81 S
   mir_dump                     Success:     578 P,   0 F,   0 T,  84 S
   InterpretOptimized           Success:     568 P,   0 F,   0 T,  63 S
   InterpretCanonicalUnparsed   Failure:     578 P,   4 F,   0 T,  49 S
   InterpretStrippedIncludes    Failure:     573 P,   3 F,   0 T,  55 S
   InterpretObfuscated          Success:     568 P,   0 F,   0 T,  63 S
   Generate_C                   Failure:     540 P,  30 F,   0 T,  61 S
   CompiledVsInterpreted        Failure:     507 P,  33 F,   0 T,  91 S
   CompileOptimized             Failure:     506 P,   1 F,   0 T, 124 S
   Refcounts                    Failure:     288 P, 190 F,   4 T, 149 S
   Demi_eval_true               Failure:     489 P,  18 F,   0 T, 124 S
   Demi_eval_false              Failure:     495 P,  12 F,   0 T, 124 S
   plugin_inconsistent_st_attr  Success:     592 P,   0 F,   0 T,  70 S
   plugin_linear                Success:     592 P,   0 F,   0 T,  70 S
   plugin_cloning               Success:     591 P,   0 F,   1 T,  70 S
   plugin_pre_vs_post_count     Success:     592 P,   0 F,   0 T,  70 S
   ReparseUnparsed              Failure:     582 P,  10 F,   0 T,  70 S
   plugin_source_vs_semantic_values  Success:     592 P,   0 F,   0 T,  70 S

The columns indicate:

:P: Number of passes

:F: Number of failures

:T: Number of time-outs. We stop any test which runs for longer than 5 seconds.

:S: Number of skipped tests. In some cases, test subjects [#test_subjects]_
   which fail one test will also fail subsequent tests. We skip these instead.

As you can see, some failures are expected. Howver, if a test fails completely
(i.e. it has no passed tests), there may be a platform-dependent issue, which should
be `reported to the mailing-list <http://phpcompiler.org/mailinglist.html>`_.


Parallelizing
-------------

The tests can take a long time to run. If you have multiple processors on your machine, you may prefer to run tests in parallel. The test-suite looks for the environmental variable **PHC_NUM_PROCS**, which can be set for a session:

.. sourcecode:: bash

   export PHC_NUM_PROCS=4

or for one test iteration:

.. sourcecode:: bash

   PHC_NUM_PROCS=4 php test/framework/driver.php

A good argument for **PHC_NUM_PROCS** seems to be one-and-a-half time the number of cores in your available.




Options
-------

If you are developing |phc|, there are a lot of options to make it simpler. To
see them, run.

.. sourcecode:: bash

   php test/framework/driver.php -h


3rd-party tests
---------------

You can also add your own code to :file:`test/subjects/3rdparty/`, and test it by running:

.. sourcecode:: bash

   make long-test

to run the entire suite.


.. [#test_subjects] That is, the PHP files we keep in the `test/subjects/ directory <http://code.google.com/p/phc/source/browse/#svn/trunk/test/subjects/>`_.

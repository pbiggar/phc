/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a number of whole-program analyses simulteneously.
 */

/*
 * This is the basis for simulatenous optimizations. It seems that we need
 * alias analysis to do type-inference, and type-inference for alias analysis.
 * On top of this, we would get more precise results if we did the analysis
 * conditionally (or symbolically - aka evaluating constants and branches).
 * Additionally, we can use this to model global state, including include_path,
 * the error_reporting level, defined functions, classes and constants, etc.
 *
 * The analysis starts in main, and each statement is symbolically executed
 * (referred heretofore as evaluated) by each analyser before the next
 * statement is evaluated. When another function is called, it propagates the
 * current results (or global results for global state) into the callee, and
 * the callee is the evaluated, before returning to the caller. Once the entire
 * program is evaluated in this manner, we will have complete results,
 * including a callgraph and types. Then other analyses who merely consume this
 * information can run, and annotated things for the code generator.
 *
 * The analysis will proceed conditionally, in the sense of CCP, which means
 * that it will evaluate a conditional, and only proceed down 1 path if we are
 * able to evaluate it. Passes will be passed a clone of the statement, and so
 * can update it if they wish. The statement will be passed to each analysis
 * until it fix-points.
 *
 * The analyses will have to each other, so that we can get a type if required
 * for callgraph resolution, etc. 
 */

#ifndef PHC_WHOLE_PROGRAM
#define PHC_WHOLE_PROGRAM

#include "WPA.h"
#include "lib/Map.h"

class Whole_program
{
	Map<string, WPA*> analyses;

	// TODO: these should probably be put elsewhere
	Map<string, MIR::Method*> functions;
	Map<string, MIR::Class_def*> classes;
	// TODO: interfaces

public:
	Whole_program();
	void run (MIR::PHP_script* in);


	void evaluate_function (CFG* in);

	Edge_list* get_branch_successors (Branch_block* bb);

	void register_analysis (string name, WPA* analysis);
};


#endif // PHC_WHOLE_PROGRAM

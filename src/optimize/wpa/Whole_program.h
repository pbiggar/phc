/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a number of whole-program analyses simulteneously.
 */

/*
 * This is the basis for simulatenous optimizations. It seems that we need
 * alias analysis to do type-inference, and type-inference for alias
 * analysis.  On top of this, we would get more precise results if we did the
 * analysis conditionally (or symbolically - aka evaluating constants and
 * branches).  Additionally, we can use this to model global state, including
 * include_path, the error_reporting level, defined functions, classes and
 * constants, etc.
 *
 * The analysis starts in main, and each statement is symbolically executed
 * (referred heretofore as evaluated) by each analyser before the next
 * statement is evaluated. When another function is called, it propagates the
 * current results (or global results for global state) into the callee, and
 * the callee is the evaluated, before returning to the caller. Once the
 * entire program is evaluated in this manner, we will have complete results,
 * including a callgraph and types. Then other analyses who merely consume
 * this information can run, and annotated things for the code generator.
 *
 * The analysis will proceed conditionally, in the sense of CCP, which means
 * that it will evaluate a conditional, and only proceed down 1 path if we
 * are able to evaluate it. Passes will be passed a clone of the statement,
 * and so can update it if they wish. The statement will be passed to each
 * analysis until it fix-points.
 *
 * The analyses will have to each other, so that we can get a type if
 * required for callgraph resolution, etc.
 *
 */

#ifndef PHC_WHOLE_PROGRAM
#define PHC_WHOLE_PROGRAM

#include "WPA.h"
#include "lib/Map.h"
#include "optimize/Oracle.h"

class Aliasing;
class Callgraph;
class CCP;
class Constant_state;
class Include_analysis;
class Type_inference;
class VRP;
class WPA;

class Whole_program
{

	// Analyses should be able to reach in here to get other analyses'
	// results.

public:
	Map<string, WPA*> analyses;
	Aliasing* aliasing;
	CCP* ccp;


public:
	Whole_program();
	void register_analysis (string name, WPA* analysis);

	/*
	 * Analysis
	 */
	// My current plan is the each analysis can annotate the MIR nodes as they
	// go. Then, before each block is analysed, all of its annotations are
	// cleared.
	//
	// This way, each analysis does not have to store results at each program
	// point, and can update them as it proceeds through the program.
	// TODO: do we have to clone for join points then?

	void run (MIR::PHP_script* in);

	void invoke_method (MIR::Method_invocation* in, Basic_block* context, MIR::VARIABLE_NAME* lhs);
	Edge_list* get_branch_successors (Branch_block* bb);
	Method_info_list* get_possible_receivers (MIR::Method_invocation* in);

	// TODO: move these elsewhere
	void apply_results (CFG* cfg);

private:
	// The CFG parameterss arent in an intuitive order, but thats so that when
	// there are 2 CFGs, they go in the order Caller,callee. The other problems
	// can at least be spotted by the type-checker.
	void analyse_method_info (Method_info* info, Basic_block* context, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs);
	void analyse_function (Basic_block* context, CFG* cfg, 
								  MIR::Actual_parameter_list*, MIR::VARIABLE_NAME* lhs);
	void analyse_summary (Method_info* info, Basic_block* context,
							    MIR::Actual_parameter_list*, MIR::VARIABLE_NAME* lhs);
};


#endif // PHC_WHOLE_PROGRAM

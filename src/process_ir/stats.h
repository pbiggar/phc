/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience statistics functions.
 */

#include "lib/Set.h"
#include "lib/Map.h"

using namespace std;
//using namespace boost;

#ifndef PHC_STATS
#define PHC_STATS

/*
 * Design:
 *
 *		- We want to print compile-time statistics for a pass. The only interface
 *		in the pass should be the macro CTS (NAME).
 *		- CTS stands for 'Compile-Time-Statistic'
 *		- It simply adds one to a counter, which is specific to NAME.
 *		- After each pass, if --stats is enabled, all live counters are printed.
 *		- The is (currently) no need to save the stats after a pass ends.
 */

#define LCTS(NAME)do {inc_stat (NAME, __FILE__, __LINE__); } while (0)
#define CTS(NAME)do {inc_stat (NAME); } while (0)


/* XCTS allows you wrap a statement, and use its code as the counter. For example:
 *
 *		XCTS (out->push_back (in));
 *
 *	would create increment a counter called "out->push_back (in)", and also call
 *	out->push_back (in);
 */
//#define XCTS(NAME) do { increment_stat (#NAME, __FILE__, __LINE__); NAME; } while (0)

typedef Set<string> Stringset_stats;

static Map<string, int> stats;
static Map<string, Stringset_stats*> stringset_stats;

void inc_stat (string name, string filename, int line_number);
void inc_stat (string name);
void set_stat (string name, int num);
int get_stat (string name);
Stringset_stats* get_stringset_stat (string name);
void add_to_stringset_stat (string name, string s);

void dump_types_per_opmeth ();
void dump_stats ();
void dump_stringset_stats ();
void reset_stats ();
void reset_stringset_stats ();
int stringset_stats_size ();
#endif // STATS

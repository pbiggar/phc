/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience statistics functions.
 */

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

#define CTS(NAME) do { increment_stat (#NAME, __FILE__, __LINE__); } while (0)

void increment_stat (string name, string filename, int line_number);
void dump_stats ();
void reset_stats ();

#endif // STATS

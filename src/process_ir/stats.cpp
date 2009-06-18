/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience statistics functions.
 */

#include <iostream>
#include <sstream>

#include "lib/Map.h"

using namespace std;
using namespace boost;

static Map<string, int> stats;

void reset_stats ()
{
	stats.clear ();
}

int increment_stat (string name, string filename, int line_number)
{
	stringstream ss;
	ss << name << " (" << filename << ":"/* << line_number*/ << ")";
	return stats[ss.str ()]++ > 0;
}

void dump_stats ()
{
	string name;
	int count;
	foreach (tie (name, count), stats)
	{
		cerr << name << " - " << count << endl;
	}
}

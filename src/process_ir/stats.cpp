/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience statistics functions.
 */

#include <iostream>
#include <sstream>

#include "stats.h"

using namespace std;
using namespace boost;

void reset_stats ()
{
	stats.clear ();
}

void add_to_stringset_stat (string name, string s)
{
	stringset_stats[name]->insert (s);
}

Stringset_stats* get_stringset_stat (string name)
{
	return stringset_stats[name];
}

void increment_stat (string name, string filename, int line_number)
{
	stringstream ss;
	ss << name/* << " (" << filename << ":" << line_number << ")"*/;
}


int get_stat (string name) 
{
	return stats[name];
}

void set_stat (string name, int num)
{
	stats[name]=num;
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

void dump_types_per_var_name () 
{
	string s;
	int n;
	foreach (tie (s, n), stats)
	{
		if ( (s.substr(0,28) == "Number of types assigned to "))
		{
			cerr << "\'" << s.substr(28) << "\'" << ',' << n << endl;
		}
	}	
}

void dump_types_per_opmeth ()
{
	string s;
	Stringset_stats * ssl;
	
	foreach (tie (s,ssl), stringset_stats)
	{
		int count=0;
		if (s.substr (0,5) == "types")
		{
			cerr << "\'" << s.substr (5) << "\',\'";
			foreach (string str, *ssl)
			{
				cerr << str << "," ;
				count++;
			}
			cerr << "\'," << count << endl;
		}		

	}

}

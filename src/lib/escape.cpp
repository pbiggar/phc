/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Various routines for escaping strings.
 */

#include <sstream>
#include <iomanip> 

#include "lib/String.h"

using namespace std;

// TODO: All of these functions could be substantially refactored, as they
// all duplicate functionality, but are all slightly different. No point
// fixing them now, as they work, but if they need to be bug-fixed, it might
// be easier to refactor them at the same time.

String* escape_C_dq (String* s)
{
	stringstream ss;

	foreach (char c, *s)
	{
		if(c == '"' || c == '\\')
		{
			ss << "\\" << c;
		}
		else if(c >= 32 && c < 127)
		{
			ss << c;
		}
		else
		{
			ss << "\\" << setw(3) << setfill('0') << oct << uppercase << (unsigned long int)(unsigned char) c;
			ss << resetiosflags(ss.flags ());
		}
	}

	return new String (ss.str());
}

String* escape_C_comment (String* s)
{
	// TODO: this really just needs to remove \ns
	stringstream ss;

	foreach (char c, *s)
	{
		if(c == '\n')
		{
			ss << "\\" << c;
		}
		else if((c >= 32 && c < 127) || c == '\t')
		{
			ss << c;
		}
		else
		{
			ss << "\\" << setw(3) << setfill('0') << oct << uppercase << (unsigned long int)(unsigned char) c;
			ss << resetiosflags(ss.flags ());
		}
	}

	return new String (ss.str());
}

String* escape_PHP_dq (String* s)
{
	stringstream os;

	string::iterator i;
	for(i = s->begin(); i != s->end(); i++)
	{
		switch(*i)
		{
			case '\n':
				os << "\\n";
				break;
			case '\r':
				os << "\\r";
				break;
			case '\t':
				os << "\\t";
				break;
			case '\\':
			case '$':
			case '"':
				os << "\\" << *i;
				break;
			default:
				if(*i < 32 || *i == 127)
				{
						os << "\\x" << setw(2) <<
							setfill('0') << hex << uppercase << (unsigned long int)(unsigned char)*i;
						os << resetiosflags(os.flags());
				}
				else
					os << *i;
				break;
		}
	}
	
	return new String(os.str());	
}

String* escape_PHP_sq (String* s)
{
	stringstream os;

	string::iterator i;
	for(i = s->begin(); i != s->end(); i++)
	{
		switch (*i)
		{
			case '\'': // single quote
			case '\\': // backslash
				os << '\\' << *i;
				break;
			default:
				os << *i;
				break;
		}
	}
	
	return new String(os.str());	
}


String* escape_DOT (String* in, int max_length)
{
	unsigned ml = max_length;

	if (max_length == -1)
		ml = in->size();

	stringstream escaped;
	unsigned i;

	for(i = 0; i < ml && i < in->size(); i++)
	{
		switch((*in)[i])
		{
			case '\\':
			case '"':
			case '|':
			case '{':
			case '}':
				escaped << "\\" << (*in)[i];
				break;
			default:
				if((*in)[i] >= 32 && (*in)[i] != 127) escaped << (*in)[i];
				break;
		}
	}	

	if(i < in->size())
		escaped << "..";

	return s(escaped.str());
}

String* escape_DOT_record (String* in, int max_length)
{
	unsigned ml = max_length;

	if (max_length == -1)
		ml = in->size();

	stringstream escaped;
	unsigned i;

	for(i = 0; i < ml && i < in->size(); i++)
	{
		switch((*in)[i])
		{
			case '\\':
			case '>': // must be escaped within the label of a record
			case '<': // must be escaped within the label of a record
			case '"':
				escaped << "\\" << (*in)[i];
				break;
			default:
				if((*in)[i] >= 32 && (*in)[i] != 127) escaped << (*in)[i];
				break;
		}
	}	

	if(i < in->size())
		escaped << "..";

	return s(escaped.str());
}

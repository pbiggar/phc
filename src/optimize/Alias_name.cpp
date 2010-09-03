/*
 * phc -- the open source PHP compiler
 * 
 * Representation of a variable_name/object.
 */

#include "MIR.h"
#include "process_ir/General.h"

#include "Basic_block.h"

#include "Alias_name.h"
#include "wpa/Aliasing.h"
#include "wpa/Points_to.h"

#include <boost/algorithm/string/replace.hpp>

using namespace std;
using namespace MIR;

Alias_name::Alias_name ()
{
}


bool
Alias_name::operator== (const Alias_name& other) const
{
	return this->str () == other.str ();
}

bool
Alias_name::operator!= (const Alias_name& other) const
{
	return not (operator== (other));
}

size_t
Alias_name::hash () const
{
	return std::tr1::hash<string>() (this->str ());
}


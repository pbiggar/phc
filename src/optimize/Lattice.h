#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


#include "lib/Map.h"
#include "Var_map.h"

#include "MIR.h"
#include "process_ir/debug.h"
#include <boost/tuple/tuple.hpp> // for tie

class Lattice_cell : virtual public GC_obj
{
public:
	virtual void dump () = 0;

	// Assume THIS and OTHER are not TOP or BOTTOM, and they are all of the same type.
	virtual bool equals (Lattice_cell* other) = 0;

	// Assuming that THIS and OTHER are not TOP or BOTTOM. This models a 3-level
	// lattice. A subclass may wish to model a deeper lattice.
	virtual Lattice_cell* meet (Lattice_cell* other);
};

extern Lattice_cell* TOP;
extern Lattice_cell* BOTTOM;

Lattice_cell* meet (Lattice_cell* l1, Lattice_cell* l2);


class Lattice_map
: public Map<string, Lattice_cell*>
{
public:
	Lattice_map (Lattice_cell* default_value = TOP)
	: Map<string, Lattice_cell*> ()
	, default_value (default_value)
	{
	}

	Lattice_cell* default_value;

	void dump ()
	{
		CHECK_DEBUG ();

		string index;
		Lattice_cell* cell;
		foreach (boost::tie (index, cell), *this)
		{
			cdebug << index << " => ";
			if (cell == TOP)
				cdebug << "TOP";
			else if (cell == BOTTOM)
				cdebug << "BOTTOM";
			else
			{
				cdebug << "(";
				cell->dump ();
				cdebug << ")";
			}
			cdebug << "\n";
		}
	}

	// We want to offer the option of the default value not being TOP.
	Lattice_cell*& operator[](string var)
	{
		if (has (var))
		{
			return Map<string, Lattice_cell*>::operator[](var);
		}
		else
		{
			Map<string, Lattice_cell*>::operator[](var) = default_value;
			return Map<string, Lattice_cell*>::operator[](var);
		}
	}

	// Not a deep copy.
	Lattice_map* clone ()
	{
		Lattice_map* result = new Lattice_map (default_value);

		string var;
		Lattice_cell* cell;
		foreach (boost::tie (var, cell), *this)
			(*result)[var] = cell;

		return result;
	}

	bool equals (Lattice_map* other)
	{
		bool result = true;
		string var;
		Lattice_cell* cell;
		foreach (boost::tie (var, cell), *other)
		{
			if (cell == TOP || cell == BOTTOM)
			{
				if (cell != (*this)[var])
					return false;
			}
			else if (!(cell->equals ((*this)[var])))
				return false;
		}
		return true;
	}

	void merge (Lattice_map* other)
	{
		string key;
		Lattice_cell* val;
		foreach (boost::tie (key, val), *other)
		{
			(*this)[key] = meet ((*this)[key], val);
		}
	}

	// Rather than merging with current results, overwrite them
	void overwrite (Lattice_map* other)
	{
		string key;
		Lattice_cell* val;
		foreach (boost::tie (key, val), *other)
		{
			(*this)[key] = val;
		}
	}
};

class SSA_map
: public Var_map<Lattice_cell*>
{
public:
	SSA_map (Lattice_cell* default_value = TOP)
	: Var_map<Lattice_cell*> ()
	, default_value (default_value)
	{
	}

	Lattice_cell* default_value;

	void dump ()
	{
		CHECK_DEBUG ();

		MIR::VARIABLE_NAME* var;
		Lattice_cell* cell;
		foreach (boost::tie (var, cell), *this)
		{
			cdebug << *var->get_ssa_var_name () << " => ";
			if (cell == TOP)
				cdebug << "TOP";
			else if (cell == BOTTOM)
				cdebug << "BOTTOM";
			else
			{
				cdebug << "(";
				cell->dump ();
				cdebug << ")";
			}
			cdebug << "\n";
		}
	}

	// We want to offer the option of the default value not being TOP.
	Lattice_cell*& operator[](MIR::VARIABLE_NAME* var)
	{
		if (has (var))
		{
			return Var_map<Lattice_cell*>::operator[](var);
		}
		else
		{
			Var_map<Lattice_cell*>::operator[](var) = default_value;
			return Var_map<Lattice_cell*>::operator[](var);
		}
	}

	// Not a deep copy.
	SSA_map* clone ()
	{
		SSA_map* result = new SSA_map (default_value);

		MIR::VARIABLE_NAME* var;
		Lattice_cell* cell;
		foreach (boost::tie (var, cell), *this)
			(*result)[var] = cell;

		return result;
	}

	bool equals (SSA_map* other)
	{
		bool result = true;
		MIR::VARIABLE_NAME* var;
		Lattice_cell* cell;
		foreach (boost::tie (var, cell), *other)
		{
			if (cell == TOP || cell == BOTTOM)
			{
				if (cell != (*this)[var])
					return false;
			}
			else if (!(cell->equals ((*this)[var])))
				return false;
		}
		return true;
	}
};

#endif // PHC_LATTICE_H

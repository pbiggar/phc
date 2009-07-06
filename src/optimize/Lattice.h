#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


#include "lib/Map.h"

#include "MIR.h"
#include "process_ir/General.h"
#include <boost/tuple/tuple.hpp> // for tie


template <class Key_type, class Cell_type>
class Lattice_map
: public Map<Key_type, Cell_type*>
{
	typedef Map<Key_type, Cell_type*> parent;
	typedef Lattice_map <Key_type, Cell_type> this_type;

public:
	Lattice_map ()
	: Map<Key_type, Cell_type*> ()
	{
	}

	void dump (std::ostream& os = cdebug) const
	{
		CHECK_DEBUG ();

		Key_type index;
		Cell_type* cell;
		foreach (tie (index, cell), *this)
		{
			os << index << " => ";
			cell->dump (os);
			os << "\n";
		}
	}

	Cell_type* operator[](Key_type var) const // const version
	{
		if (parent::has (var))
			return parent::operator[](var);
		else
		return Cell_type::get_default ();
	}


	// We want to offer the option of the default value not being TOP.
	Cell_type*& operator[](Key_type var)
	{
		if (parent::has (var))
		{
			return parent::operator[](var);
		}
		else
		{
			parent::operator[](var) = Cell_type::get_default ();
			return parent::operator[](var);
		}
	}

	// Not a deep copy.
	this_type* clone ()
	{
		this_type* result = new this_type;

		Key_type var;
		Cell_type* cell;
		foreach (tie (var, cell), *this)
			(*result)[var] = cell;

		return result;
	}

	bool equals (this_type* other)
	{
		if (this->size () != other->size ())
			return false;

		Key_type var;
		Cell_type* cell;
		foreach (tie (var, cell), *other)
			if (!cell->equals ((*this)[var]))
				return false;

		return true;

	}

	void merge (this_type* other)
	{
		Key_type key;
		Cell_type* val;
		foreach (tie (key, val), *other)
		{
			(*this)[key] = (*this)[key]->meet (val);
		}
	}
};

#endif // PHC_LATTICE_H

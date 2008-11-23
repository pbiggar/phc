#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


#include "lib/Map.h"
#include "Var_map.h"

#include "MIR.h"
#include "Set.h"
#include "process_ir/debug.h"


template <typename T>
class Lattice_cell : virtual public GC_obj
{
public:
	Lattice_cell (T* value) : value(value) {}

	T* get_value ()
	{
		assert (value != NULL);
		return value;
	}

	static Lattice_cell<T>* TOP;
	static Lattice_cell<T>* BOTTOM;

private:
	T* value;
};

// Each client must call this to provide them memory for TOP and BOTTOM (this
// must be called from a .cpp file).
#define INITIALIZE_LATTICE(TYPE)																			\
	template<> Lattice_cell<TYPE>* Lattice_cell<TYPE>::TOP = NULL;								\
	template<> Lattice_cell<TYPE>* Lattice_cell<TYPE>::BOTTOM = new Lattice_cell<TYPE> (NULL);

template <typename T>
class Lattice_map
: public Var_map<Lattice_cell<T>*>
{
public:
	Lattice_map () : Var_map<Lattice_cell<T>*> () { }

	void dump ()
	{
		std::pair<MIR::VARIABLE_NAME*, Lattice_cell<T>*> pair;
		foreach (pair, *this)
		{
			cdebug << *pair.first->get_ssa_var_name () << " => ";
			if (pair.second == Lattice_cell<T>::TOP)
				cdebug << "TOP";
			else if (pair.second == Lattice_cell<T>::BOTTOM)
				cdebug << "BOTTOM";
			else
				cdebug << "(" << *pair.second->get_value()->get_value_as_string () << ")";
			cdebug << "\n";
		}
	}
};

template <typename T>
Lattice_cell<T>* meet (Lattice_cell<T>* l1, T* l2)
{
	if (l1 == Lattice_cell<T>::BOTTOM)
		return Lattice_cell<T>::BOTTOM;

	if (l1 == Lattice_cell<T>::TOP)
		return new Lattice_cell<T> (l2);
	
	// l1 == CONST && l2 == CONST
	if (l1->get_value()->equals (l2))
		return l1;
	else
		return Lattice_cell<T>::BOTTOM;
}

template <typename T>
Lattice_cell<T>* meet (Lattice_cell<T>* l1, Lattice_cell<T>* l2)
{
	if (l1 == Lattice_cell<T>::BOTTOM || l2 == Lattice_cell<T>::BOTTOM)
		return Lattice_cell<T>::BOTTOM;

	if (l1 == Lattice_cell<T>::TOP)
		return l2;
	
	if (l2 == Lattice_cell<T>::TOP)
		return l1;

	// l1 == CONST && l2 == CONST
	return meet (l1, l2->get_value ());
}


#endif // PHC_LATTICE_H

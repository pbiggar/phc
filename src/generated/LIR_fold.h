#include <iostream>
#include <sstream>
#include <iomanip>
#include "boost/lexical_cast.hpp"
#include "lib/error.h"
#include "lib/Object.h"
#include "lib/List.h"
#include "lib/String.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/AttrMap.h"
#include "process_ir/IR.h"
#include "process_lir/LIR_PHP_script_hack.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "LIR.h"
namespace LIR{
template
<class _CODE,
 class _C_file,
 class _Node,
 template <typename _Tp, typename _Alloc = typename List<_Tp>::allocator_type> class _List = List
>
class Fold
{
// Access this class from subclasses without copying out the template instantiation
public:
   typedef Fold<_CODE, _C_file, _Node, _List> parent;
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _C_file fold_c_file(C_file* in)
	{
		_List<_CODE>* codes = 0;
	
		{
			codes = new _List<_CODE>;
			typename _List<CODE*>::const_iterator i;
			for(i = in->codes->begin(); i != in->codes->end(); i++)
				if(*i != NULL) codes->push_back(fold_code(*i));
				else codes->push_back(0);
		}
		return fold_impl_c_file(in, codes);
	}



// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _C_file fold_impl_c_file(C_file* orig, _List<_CODE>* codes) { assert(0); };

	virtual _CODE fold_code(CODE* orig) { assert(0); };


// Manual dispatching for abstract classes
// Override only if you know what you are doing!
	virtual _Node fold_node(Node* in)
	{
		switch(in->classid())
		{
			case C_file::ID:
				return fold_c_file(dynamic_cast<C_file*>(in));
			case CODE::ID:
				return fold_code(dynamic_cast<CODE*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T, template <class _Tp, class _Alloc = typename List<_Tp>::allocator_type> class _List>
class Uniform_fold : public Fold<T, T, T, _List> {};
}


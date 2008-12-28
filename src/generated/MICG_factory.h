#ifndef _MICG_FACTORY_H_
#define _MICG_FACTORY_H_

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
#include "process_ir/IR.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "MICG.h"

namespace MICG{
class Node_factory
{
public:
    /* If type_id corresponds to an AST node, the elements in args must */
    /* correspond to the children of the node. */
    /*  */
    /* If type_id corresponds to a list (of the form "..._list"), */
    /* the elements of arg must be of the same type as the elements */
    /* in the list, and all elements in args are added to the list. */
    /*  */
    /* If type_id corresponds to a token (terminal symbol), args must */
    /* contain a single node of type String. Terminal symbols */
    /* with non-default values are not supported. */
    /*  */
    /* If the node type is not recognized, NULL is returned. */
    static Object* create(char const* type_id, List<Object*>* args);
};
}


#endif

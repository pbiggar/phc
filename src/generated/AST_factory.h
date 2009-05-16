#ifndef _AST_FACTORY_H_
#define _AST_FACTORY_H_

#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/error.h"
#include "lib/Object.h"
#include "lib/List.h"
#include "lib/String.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/AttrMap.h"
#include "process_ir/IR.h"
#include "process_ir/Foreach.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "AST.h"

namespace AST{
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

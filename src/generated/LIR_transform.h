#ifndef _LIR_TRANSFORM_H_
#define _LIR_TRANSFORM_H_

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
class Transform
{
public:
    virtual ~Transform();
/* Invoked before the children are transformed */
public:
    virtual C_file* pre_c_file(C_file* in);
    virtual void pre_code(CODE* in, CODE_list* out);
/* Invoked after the children have been transformed */
public:
    virtual C_file* post_c_file(C_file* in);
    virtual void post_code(CODE* in, CODE_list* out);
/* Transform the children of the node */
public:
    virtual void children_c_file(C_file* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_code(CODE* in);
/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
public:
    virtual CODE_list* transform_code_list(CODE_list* in);
    virtual CODE_list* transform_code(CODE* in);
    virtual C_file* transform_c_file(C_file* in);
};
}


#endif

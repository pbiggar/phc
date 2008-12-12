#ifndef _LIR_VISITOR_H_
#define _LIR_VISITOR_H_

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
class Visitor
{
public:
    virtual ~Visitor();
/* Invoked before the children are visited */
public:
    virtual void pre_node(Node* in);
    virtual void pre_c_file(C_file* in);
    virtual void pre_code(CODE* in);
/* Invoked after the children have been visited */
public:
    virtual void post_node(Node* in);
    virtual void post_c_file(C_file* in);
    virtual void post_code(CODE* in);
/* Visit the children of a node */
public:
    virtual void children_c_file(C_file* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_code(CODE* in);
/* Unparser support */
public:
    virtual void visit_marker(char const* name, bool value);
    virtual void visit_null(char const* name_space, char const* type_id);
    virtual void visit_null_list(char const* name_space, char const* type_id);
    virtual void pre_list(char const* name_space, char const* type_id, int size);
    virtual void post_list(char const* name_space, char const* type_id, int size);
/* Invoke the chain of pre-visit methods along the inheritance hierachy */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_c_file_chain(C_file* in);
    virtual void pre_code_chain(CODE* in);
/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_c_file_chain(C_file* in);
    virtual void post_code_chain(CODE* in);
/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
public:
    virtual void visit_code_list(CODE_list* in);
    virtual void visit_code(CODE* in);
    virtual void visit_c_file(C_file* in);
};
}


#endif

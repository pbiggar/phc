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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


#include "AST.h"

class AST_factory
{
public:
    static Object* create(char const* type_id, List<Object*>* args);
};


#endif

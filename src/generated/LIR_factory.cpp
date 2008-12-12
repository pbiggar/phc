#include "LIR_factory.h"

namespace LIR{
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
Object* Node_factory::create(char const* type_id, List<Object*>* args)
{
    List<Object*>::const_iterator i = args->begin();
    if(!strcmp(type_id, "C_file"))
    {
    	CODE_list* codes = dynamic_cast<CODE_list*>(*i++);
    	assert(i == args->end());
    	return new C_file(codes);
    }
    if(!strcmp(type_id, "CODE_list"))
    {
    	CODE_list* list = new CODE_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<CODE*>(*i++));
    	return list;
    }
    return NULL;
}
}


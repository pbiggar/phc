#include "LIR_factory.h"

namespace LIR{
// If type_id corresponds to an AST node, the elements in args must
// correspond to the children of the node.
// 
// If type_id corresponds to a list (of the form "..._list"),
// the elements of arg must be of the same type as the elements
// in the list, and all elements in args are added to the list.
// 
// If type_id corresponds to a token (terminal symbol), args must
// contain a single node of type String. Terminal symbols
// with non-default values are not supported.
// 
// If the node type is not recognized, NULL is returned.
Object* Node_factory::create(char const* type_id, List<Object*>* args)
{
    List<Object*>::const_iterator i = args->begin();
    if(!strcmp(type_id, "C_file"))
    {
    	Piece_list* pieces = dynamic_cast<Piece_list*>(*i++);
    	assert(i == args->end());
    	return new C_file(pieces);
    }
    if(!strcmp(type_id, "Method"))
    {
    	COMMENT* comment = dynamic_cast<COMMENT*>(*i++);
    	UNINTERPRETED* entry = dynamic_cast<UNINTERPRETED*>(*i++);
    	Piece_list* pieces = dynamic_cast<Piece_list*>(*i++);
    	UNINTERPRETED* exit = dynamic_cast<UNINTERPRETED*>(*i++);
    	assert(i == args->end());
    	return new Method(comment, entry, pieces, exit);
    }
    if(!strcmp(type_id, "Block"))
    {
    	COMMENT* comment = dynamic_cast<COMMENT*>(*i++);
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new Block(comment, statements);
    }
    if(!strcmp(type_id, "If"))
    {
    	Cond* cond = dynamic_cast<Cond*>(*i++);
    	Statement_list* iftrue = dynamic_cast<Statement_list*>(*i++);
    	Statement_list* iffalse = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new If(cond, iftrue, iffalse);
    }
    if(!strcmp(type_id, "Assign_zvp"))
    {
    	Zvp* lhs = dynamic_cast<Zvp*>(*i++);
    	Zvp* rhs = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Assign_zvp(lhs, rhs);
    }
    if(!strcmp(type_id, "Assign_zvpp"))
    {
    	Zvpp* lhs = dynamic_cast<Zvpp*>(*i++);
    	Zvpp* rhs = dynamic_cast<Zvpp*>(*i++);
    	assert(i == args->end());
    	return new Assign_zvpp(lhs, rhs);
    }
    if(!strcmp(type_id, "Inc_ref"))
    {
    	Zvp* zvp = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Inc_ref(zvp);
    }
    if(!strcmp(type_id, "Allocate"))
    {
    	Zvp* zvp = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Allocate(zvp);
    }
    if(!strcmp(type_id, "Clone"))
    {
    	Zvp* lhs = dynamic_cast<Zvp*>(*i++);
    	Zvp* rhs = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Clone(lhs, rhs);
    }
    if(!strcmp(type_id, "Separate"))
    {
    	Zvpp* zvpp = dynamic_cast<Zvpp*>(*i++);
    	assert(i == args->end());
    	return new Separate(zvpp);
    }
    if(!strcmp(type_id, "Dec_ref"))
    {
    	Zvp* zvp = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Dec_ref(zvp);
    }
    if(!strcmp(type_id, "Destruct"))
    {
    	Zvpp* zvpp = dynamic_cast<Zvpp*>(*i++);
    	assert(i == args->end());
    	return new Destruct(zvpp);
    }
    if(!strcmp(type_id, "Is_ref"))
    {
    	Zvp* zvp = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Is_ref(zvp);
    }
    if(!strcmp(type_id, "Equals"))
    {
    	Zvp* lhs = dynamic_cast<Zvp*>(*i++);
    	Zvp* rhs = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Equals(lhs, rhs);
    }
    if(!strcmp(type_id, "Not_equals"))
    {
    	Zvp* lhs = dynamic_cast<Zvp*>(*i++);
    	Zvp* rhs = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Not_equals(lhs, rhs);
    }
    if(!strcmp(type_id, "Uninitialized"))
    {
    	assert(i == args->end());
    	return new Uninitialized();
    }
    if(!strcmp(type_id, "Null"))
    {
    	assert(i == args->end());
    	return new Null();
    }
    if(!strcmp(type_id, "Deref"))
    {
    	Zvpp* zvpp = dynamic_cast<Zvpp*>(*i++);
    	assert(i == args->end());
    	return new Deref(zvpp);
    }
    if(!strcmp(type_id, "Ref"))
    {
    	Zvp* zvp = dynamic_cast<Zvp*>(*i++);
    	assert(i == args->end());
    	return new Ref(zvp);
    }
    if(!strcmp(type_id, "COMMENT"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new COMMENT(value);
    }
    if(!strcmp(type_id, "UNINTERPRETED"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new UNINTERPRETED(value);
    }
    if(!strcmp(type_id, "INTRINSIC"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new INTRINSIC(value);
    }
    if(!strcmp(type_id, "API_CALL"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new API_CALL(value);
    }
    if(!strcmp(type_id, "CODE"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new CODE(value);
    }
    if(!strcmp(type_id, "ZVP"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new ZVP(value);
    }
    if(!strcmp(type_id, "LITERAL"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new LITERAL(value);
    }
    if(!strcmp(type_id, "ZVPP"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new ZVPP(value);
    }
    if(!strcmp(type_id, "Piece_list"))
    {
    	Piece_list* list = new Piece_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Piece*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Statement_list"))
    {
    	Statement_list* list = new Statement_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Statement*>(*i++));
    	return list;
    }
    return NULL;
}
}


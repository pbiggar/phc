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
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "MICG.h"
namespace MICG{
template
<class _ATTR_NAME,
 class _Actual_parameter,
 class _Body,
 class _Body_part,
 class _C_CODE,
 class _Equals,
 class _Expr,
 class _Formal_parameter,
 class _Interpolation,
 class _Lookup,
 class _Macro_call,
 class _Node,
 class _PARAM_NAME,
 class _PATTERN_NAME,
 class _Rule,
 class _STRING,
 class _Signature,
 class _TYPE,
 class _Template,
 template <typename _Tp, typename _Alloc = typename List<_Tp>::allocator_type> class _List = List
>
class Fold
{
// Access this class from subclasses without copying out the template instantiation
public:
   typedef Fold<_ATTR_NAME, _Actual_parameter, _Body, _Body_part, _C_CODE, _Equals, _Expr, _Formal_parameter, _Interpolation, _Lookup, _Macro_call, _Node, _PARAM_NAME, _PATTERN_NAME, _Rule, _STRING, _Signature, _TYPE, _Template, _List> parent;
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _Template fold_template(Template* in)
	{
		_Signature signature = 0;
		if(in->signature != NULL) signature = fold_signature(in->signature);
		_List<_Rule>* rules = 0;
	
		{
			rules = new _List<_Rule>;
			typename _List<Rule*>::const_iterator i;
			for(i = in->rules->begin(); i != in->rules->end(); i++)
				if(*i != NULL) rules->push_back(fold_rule(*i));
				else rules->push_back(0);
		}
		_Body body = 0;
		if(in->body != NULL) body = fold_body(in->body);
		return fold_impl_template(in, signature, rules, body);
	}

	virtual _Signature fold_signature(Signature* in)
	{
		_PATTERN_NAME pattern_name = 0;
		if(in->pattern_name != NULL) pattern_name = fold_pattern_name(in->pattern_name);
		_List<_Formal_parameter>* formal_parameters = 0;
	
		{
			formal_parameters = new _List<_Formal_parameter>;
			typename _List<Formal_parameter*>::const_iterator i;
			for(i = in->formal_parameters->begin(); i != in->formal_parameters->end(); i++)
				if(*i != NULL) formal_parameters->push_back(fold_formal_parameter(*i));
				else formal_parameters->push_back(0);
		}
		return fold_impl_signature(in, pattern_name, formal_parameters);
	}

	virtual _Formal_parameter fold_formal_parameter(Formal_parameter* in)
	{
		_TYPE type = 0;
		if(in->type != NULL) type = fold_type(in->type);
		_PARAM_NAME param_name = 0;
		if(in->param_name != NULL) param_name = fold_param_name(in->param_name);
		return fold_impl_formal_parameter(in, type, param_name);
	}

	virtual _Rule fold_rule(Rule* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_rule(in, expr);
	}

	virtual _Lookup fold_lookup(Lookup* in)
	{
		_PARAM_NAME param_name = 0;
		if(in->param_name != NULL) param_name = fold_param_name(in->param_name);
		_ATTR_NAME attr_name = 0;
		if(in->attr_name != NULL) attr_name = fold_attr_name(in->attr_name);
		return fold_impl_lookup(in, param_name, attr_name);
	}

	virtual _Equals fold_equals(Equals* in)
	{
		_Expr left = 0;
		if(in->left != NULL) left = fold_expr(in->left);
		_Expr right = 0;
		if(in->right != NULL) right = fold_expr(in->right);
		return fold_impl_equals(in, left, right);
	}

	virtual _Body fold_body(Body* in)
	{
		_List<_Body_part>* body_parts = 0;
	
		{
			body_parts = new _List<_Body_part>;
			typename _List<Body_part*>::const_iterator i;
			for(i = in->body_parts->begin(); i != in->body_parts->end(); i++)
				if(*i != NULL) body_parts->push_back(fold_body_part(*i));
				else body_parts->push_back(0);
		}
		return fold_impl_body(in, body_parts);
	}

	virtual _Macro_call fold_macro_call(Macro_call* in)
	{
		_PATTERN_NAME pattern_name = 0;
		if(in->pattern_name != NULL) pattern_name = fold_pattern_name(in->pattern_name);
		_List<_Actual_parameter>* actual_parameters = 0;
	
		{
			actual_parameters = new _List<_Actual_parameter>;
			typename _List<Actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_macro_call(in, pattern_name, actual_parameters);
	}



// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _Template fold_impl_template(Template* orig, _Signature signature, _List<_Rule>* rules, _Body body) { assert(0); };
	virtual _Signature fold_impl_signature(Signature* orig, _PATTERN_NAME pattern_name, _List<_Formal_parameter>* formal_parameters) { assert(0); };
	virtual _Formal_parameter fold_impl_formal_parameter(Formal_parameter* orig, _TYPE type, _PARAM_NAME param_name) { assert(0); };
	virtual _Rule fold_impl_rule(Rule* orig, _Expr expr) { assert(0); };
	virtual _Lookup fold_impl_lookup(Lookup* orig, _PARAM_NAME param_name, _ATTR_NAME attr_name) { assert(0); };
	virtual _Equals fold_impl_equals(Equals* orig, _Expr left, _Expr right) { assert(0); };
	virtual _Body fold_impl_body(Body* orig, _List<_Body_part>* body_parts) { assert(0); };
	virtual _Macro_call fold_impl_macro_call(Macro_call* orig, _PATTERN_NAME pattern_name, _List<_Actual_parameter>* actual_parameters) { assert(0); };

	virtual _PATTERN_NAME fold_pattern_name(PATTERN_NAME* orig) { assert(0); };
	virtual _TYPE fold_type(TYPE* orig) { assert(0); };
	virtual _ATTR_NAME fold_attr_name(ATTR_NAME* orig) { assert(0); };
	virtual _PARAM_NAME fold_param_name(PARAM_NAME* orig) { assert(0); };
	virtual _STRING fold_string(STRING* orig) { assert(0); };
	virtual _C_CODE fold_c_code(C_CODE* orig) { assert(0); };


// Manual dispatching for abstract classes
// Override only if you know what you are doing!
	virtual _Node fold_node(Node* in)
	{
		switch(in->classid())
		{
			case Template::ID:
				return fold_template(dynamic_cast<Template*>(in));
			case Signature::ID:
				return fold_signature(dynamic_cast<Signature*>(in));
			case Formal_parameter::ID:
				return fold_formal_parameter(dynamic_cast<Formal_parameter*>(in));
			case Rule::ID:
				return fold_rule(dynamic_cast<Rule*>(in));
			case Equals::ID:
				return fold_equals(dynamic_cast<Equals*>(in));
			case Lookup::ID:
				return fold_lookup(dynamic_cast<Lookup*>(in));
			case PARAM_NAME::ID:
				return fold_param_name(dynamic_cast<PARAM_NAME*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case Body::ID:
				return fold_body(dynamic_cast<Body*>(in));
			case C_CODE::ID:
				return fold_c_code(dynamic_cast<C_CODE*>(in));
			case Macro_call::ID:
				return fold_macro_call(dynamic_cast<Macro_call*>(in));
			case PATTERN_NAME::ID:
				return fold_pattern_name(dynamic_cast<PATTERN_NAME*>(in));
			case TYPE::ID:
				return fold_type(dynamic_cast<TYPE*>(in));
			case ATTR_NAME::ID:
				return fold_attr_name(dynamic_cast<ATTR_NAME*>(in));
		}
		assert(0);
	}

	virtual _Expr fold_expr(Expr* in)
	{
		switch(in->classid())
		{
			case Equals::ID:
				return fold_equals(dynamic_cast<Equals*>(in));
			case Lookup::ID:
				return fold_lookup(dynamic_cast<Lookup*>(in));
			case PARAM_NAME::ID:
				return fold_param_name(dynamic_cast<PARAM_NAME*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
		}
		assert(0);
	}

	virtual _Body_part fold_body_part(Body_part* in)
	{
		switch(in->classid())
		{
			case C_CODE::ID:
				return fold_c_code(dynamic_cast<C_CODE*>(in));
			case Macro_call::ID:
				return fold_macro_call(dynamic_cast<Macro_call*>(in));
			case Lookup::ID:
				return fold_lookup(dynamic_cast<Lookup*>(in));
			case PARAM_NAME::ID:
				return fold_param_name(dynamic_cast<PARAM_NAME*>(in));
		}
		assert(0);
	}

	virtual _Actual_parameter fold_actual_parameter(Actual_parameter* in)
	{
		switch(in->classid())
		{
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case PARAM_NAME::ID:
				return fold_param_name(dynamic_cast<PARAM_NAME*>(in));
		}
		assert(0);
	}

	virtual _Interpolation fold_interpolation(Interpolation* in)
	{
		switch(in->classid())
		{
			case Lookup::ID:
				return fold_lookup(dynamic_cast<Lookup*>(in));
			case PARAM_NAME::ID:
				return fold_param_name(dynamic_cast<PARAM_NAME*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T, template <class _Tp, class _Alloc = typename List<_Tp>::allocator_type> class _List>
class Uniform_fold : public Fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, _List> {};
}


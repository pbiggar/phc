/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Error handling 
 */

#ifndef PHC_ERROR_H
#define PHC_ERROR_H

#include <stdarg.h>
#include <iostream>

using namespace std;

class String;

namespace AST { class Node; }
namespace HIR { class Node; }
namespace MIR { class Node; }
namespace MICG { class Node; }

void phc_internal_error (const char* message, ...);
void phc_internal_error (const char* message, va_list args, String* filename, int line, int column);
void phc_internal_error (const char* message, String* filename, int line, int column, ...);
void phc_internal_error (const char* message, AST::Node*, ...);
void phc_internal_error (const char* message, HIR::Node*, ...);
void phc_internal_error (const char* message, MIR::Node*, ...);
void phc_internal_error (const char* message, MICG::Node*, ...);



void phc_error (const char* message, ...);
void phc_error (const char* message, va_list args, String* filename, int line, int column);
void phc_error (const char* message, String* filename, int line, int column, ...);
void phc_error (const char* message, AST::Node*, ...);
void phc_error (const char* message, HIR::Node*, ...);
void phc_error (const char* message, MIR::Node*, ...);
void phc_error (const char* message, MICG::Node*, ...);



void phc_warning (const char* message, ...);
void phc_warning (const char* message, va_list args, String* filename, int line, int column); 
void phc_warning (const char* message, String* filename, int line, int column, ...);
void phc_warning (const char* message, AST::Node*, ...);
void phc_warning (const char* message, HIR::Node*, ...);
void phc_warning (const char* message, MIR::Node*, ...);
void phc_warning (const char* message, MICG::Node*, ...);

#define phc_unreachable() assert(0 && "Should be unreachable")
#define phc_TODO() assert(0 && "TODO")

void _phc_optimization_exception (string message, string filename, int line);

#define phc_optimization_exception(MSG) _phc_optimization_exception(MSG,__FILE__,__LINE__)

#define phc_optimization_assertion(COND)	\
do {												\
	if (!(COND))										\
		phc_optimization_exception("Assertion Failure (" #COND ").  This means there is a bug in phc which should be reported.");			\
} while(0)									

#endif // PHC_ERROR_H

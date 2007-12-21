/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Error handling 
 */

#ifndef PHC_ERROR
#define PHC_ERROR

#include "lib/String.h"

namespace AST { class Node; }
namespace HIR { class Node; }
namespace MIR { class Node; }

void phc_internal_error (const char* message, ...);
void phc_internal_error (const char* message, String* filename, int line, ...);
void phc_internal_error (const char* message, AST::Node*, ...);
void phc_internal_error (const char* message, HIR::Node*, ...);
void phc_internal_error (const char* message, MIR::Node*, ...);



void phc_error (const char* message, ...);
void phc_error (const char* message, String* filename, int line, ...);
void phc_error (const char* message, AST::Node*, ...);
void phc_error (const char* message, HIR::Node*, ...);
void phc_error (const char* message, MIR::Node*, ...);



void phc_warning (const char* message, ...);
void phc_warning (const char* message, String* filename, int line, ...);
void phc_warning (const char* message, AST::Node*, ...);
void phc_warning (const char* message, HIR::Node*, ...);
void phc_warning (const char* message, MIR::Node*, ...);

#endif // PHC_ERROR

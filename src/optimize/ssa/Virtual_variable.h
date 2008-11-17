#ifndef PHC_VIRTUAL_VARIABLE
#define PHC_VIRTUAL_VARIABLE

#include "MIR.h" 

class Basic_block;
MIR::VARIABLE_NAME*
get_virtual (Basic_block* bb, MIR::Node* in);

#endif // PHC_VIRTUAL_VARIABLE

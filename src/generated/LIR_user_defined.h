#ifndef _LIR_USER_DEFINED_H_
#define _LIR_USER_DEFINED_H_

#ifndef MAKETEA_USER_DEFINED
#error "MAKETEA_USER_DEFINED macro undefined"
#endif

namespace LIR{
class Node;
class C_file;
class CODE;
class None;

}

MAKETEA_USER_DEFINED(LIR::Node)
MAKETEA_USER_DEFINED(LIR::C_file)
MAKETEA_USER_DEFINED(LIR::CODE)
MAKETEA_USER_DEFINED(LIR::None)


#endif

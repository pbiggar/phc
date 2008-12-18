#ifndef _LIR_USER_DEFINED_H_
#define _LIR_USER_DEFINED_H_

#ifndef MAKETEA_USER_DEFINED
#error "MAKETEA_USER_DEFINED macro undefined"
#endif

namespace LIR{
class Node;
class C_file;
class Piece;
class Statement;
class Cond;
class Zvp;
class Zvpp;
class Identifier;
class Opt_param;
class INT;
class Method;
class Block;
class Action;
class If;
class Is_ref;
class Equals;
class Equals_p;
class Not;
class Is_change_on_write;
class Is_copy_on_write;
class Uninit;
class Null;
class Deref;
class Ref;
class Clone;
class Opt;
class UNINTERPRETED;
class COMMENT;
class INTRINSIC;
class API_CALL;
class CODE;
class ZVP;
class ZVPP;
class LITERAL;
class SYMTABLE;
class STRING;
class Assign_zvp;
class Assign_zvpp;
class Declare;
class Declare_p;
class Inc_ref;
class Allocate;
class Separate;
class Set_is_ref;
class Dec_ref;
class Destruct;
class Overwrite;
class Symtable_fetch;
class Symtable_insert;
class None;

}

MAKETEA_USER_DEFINED(LIR::Node)
MAKETEA_USER_DEFINED(LIR::C_file)
MAKETEA_USER_DEFINED(LIR::Piece)
MAKETEA_USER_DEFINED(LIR::Statement)
MAKETEA_USER_DEFINED(LIR::Cond)
MAKETEA_USER_DEFINED(LIR::Zvp)
MAKETEA_USER_DEFINED(LIR::Zvpp)
MAKETEA_USER_DEFINED(LIR::Identifier)
MAKETEA_USER_DEFINED(LIR::Opt_param)
MAKETEA_USER_DEFINED(LIR::INT)
MAKETEA_USER_DEFINED(LIR::Method)
MAKETEA_USER_DEFINED(LIR::Block)
MAKETEA_USER_DEFINED(LIR::Action)
MAKETEA_USER_DEFINED(LIR::If)
MAKETEA_USER_DEFINED(LIR::Is_ref)
MAKETEA_USER_DEFINED(LIR::Equals)
MAKETEA_USER_DEFINED(LIR::Equals_p)
MAKETEA_USER_DEFINED(LIR::Not)
MAKETEA_USER_DEFINED(LIR::Is_change_on_write)
MAKETEA_USER_DEFINED(LIR::Is_copy_on_write)
MAKETEA_USER_DEFINED(LIR::Uninit)
MAKETEA_USER_DEFINED(LIR::Null)
MAKETEA_USER_DEFINED(LIR::Deref)
MAKETEA_USER_DEFINED(LIR::Ref)
MAKETEA_USER_DEFINED(LIR::Clone)
MAKETEA_USER_DEFINED(LIR::Opt)
MAKETEA_USER_DEFINED(LIR::UNINTERPRETED)
MAKETEA_USER_DEFINED(LIR::COMMENT)
MAKETEA_USER_DEFINED(LIR::INTRINSIC)
MAKETEA_USER_DEFINED(LIR::API_CALL)
MAKETEA_USER_DEFINED(LIR::CODE)
MAKETEA_USER_DEFINED(LIR::ZVP)
MAKETEA_USER_DEFINED(LIR::ZVPP)
MAKETEA_USER_DEFINED(LIR::LITERAL)
MAKETEA_USER_DEFINED(LIR::SYMTABLE)
MAKETEA_USER_DEFINED(LIR::STRING)
MAKETEA_USER_DEFINED(LIR::Assign_zvp)
MAKETEA_USER_DEFINED(LIR::Assign_zvpp)
MAKETEA_USER_DEFINED(LIR::Declare)
MAKETEA_USER_DEFINED(LIR::Declare_p)
MAKETEA_USER_DEFINED(LIR::Inc_ref)
MAKETEA_USER_DEFINED(LIR::Allocate)
MAKETEA_USER_DEFINED(LIR::Separate)
MAKETEA_USER_DEFINED(LIR::Set_is_ref)
MAKETEA_USER_DEFINED(LIR::Dec_ref)
MAKETEA_USER_DEFINED(LIR::Destruct)
MAKETEA_USER_DEFINED(LIR::Overwrite)
MAKETEA_USER_DEFINED(LIR::Symtable_fetch)
MAKETEA_USER_DEFINED(LIR::Symtable_insert)
MAKETEA_USER_DEFINED(LIR::None)


#endif

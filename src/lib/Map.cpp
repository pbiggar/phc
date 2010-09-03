/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Map static members
 */

#include <iostream>
#include "Map.h"


long long __map_private_construct_count = 0;
long long __map_private_op_eq_count = 0;
long long __map_private_detach_count = 0;
long long __map_private_copy_construct_count = 0;

long long __set_private_construct_count = 0;
long long __set_private_op_eq_count = 0;
long long __set_private_detach_count = 0;
long long __set_private_copy_construct_count = 0;



void print_cow_memory_stats ()
{
	std::cerr << "New: " << __map_private_construct_count << std::endl;
	std::cerr << "operator=: " << __map_private_op_eq_count << std::endl;
	std::cerr << "detach: " << __map_private_detach_count << std::endl;
	std::cerr << "Copy constructor : " << __map_private_copy_construct_count << std::endl;

	std::cerr << "New: " << __set_private_construct_count << std::endl;
	std::cerr << "operator=: " << __set_private_op_eq_count << std::endl;
	std::cerr << "detach: " << __set_private_detach_count << std::endl;
	std::cerr << "Copy constructor : " << __set_private_copy_construct_count << std::endl;
}


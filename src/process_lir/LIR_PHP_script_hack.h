
// It seems we're sort of married to the idea that each IR has a PHP_script.
// Hack it. This allows me to have a C_file in the grammar definition, without
// things breaking in other places.
namespace LIR
{
	class C_file;
	typedef C_file PHP_script;
}

/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser wrapper. 
 */

#include <fstream>
#include <istream>
#include "config.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> // for search dirs.
#include <libgen.h> // for basename.
#include <boost/regex.hpp> // for regular expression.
#include "parse.h"
#include "cmdline.h"
#include "php_parser.tab.hpp"
#include "parsing/PHP_context.h"
#include "process_ast/Remove_parser_temporaries.h"
#include "process_ast/Token_conversion.h"

extern struct gengetopt_args_info args_info;

using namespace AST;
using namespace std;

void run_standard_transforms(PHP_script* php_script);

PHP_script* parse_code (String* code, String* filename, int line_number)
{
	// TODO: It is important to have this, but this also substancially slows
	// down my work. Since it already doesn't work in the general case, and line
	// numbers aren't available properly a lot of the time, it is best to
	// disable this assertion for now, and fix it later.
	if (filename == NULL)
		filename = new String ("");
	assert (filename);

	assert (code);

	stringstream ss;
	ss << *code;

	PHP_script* php_script = NULL;

	// Compile
	PHP_context* context = new PHP_context(ss, filename);
	context->source_line = line_number;

	bool success = context->parse ();
	assert (success);

	php_script = context->php_script;
	php_script->attrs->set ("phc.filename", filename);
	run_standard_transforms(php_script);
	php_script->assert_valid();

	return php_script;
}


PHP_script* parse(String* filename, String_list* dirs)
{
	assert(filename);
	
	PHP_script* php_script = NULL;

	String* full_path = search_file(filename, dirs);

	if(full_path == NULL)
		return NULL;

	ifstream file_input;
	istream& input = (*full_path == "-") ? cin : file_input;

	if(*full_path != "-")
	{
		file_input.open (full_path->c_str(), ifstream::in);
		if (not file_input.is_open ()) return NULL;
	}

	// Compile
	PHP_context* context = new PHP_context (input, full_path);

	if (args_info.dump_tokens_flag)
	{
		while (context->lex ())
			;

		exit (0);
	}
	else
	{
		if (context->parse ())
		{
			php_script = context->php_script;
			php_script->attrs->set ("phc.filename", filename);
			run_standard_transforms(php_script);
			php_script->assert_valid();
		}
	}

	if (file_input.is_open ()) file_input.close ();

	return php_script;
}


void
dump_parse_tree (String* filename, String_list* dirs)
{
	assert(filename);
	
	String* full_path = search_file (filename, dirs);

	if(full_path == NULL)
		phc_error ("Search path not found");

	ifstream file_input;
	istream& input = (*full_path == "-") ? cin : file_input;

	if(*full_path != "-")
	{
		file_input.open (full_path->c_str(), ifstream::in);
		if (not file_input.is_open ())
			phc_error ("Couldnt open file");
	}

	PHP_context* context = new PHP_context (input, full_path);

	context->dump_parse_tree ();

	if (file_input.is_open ()) file_input.close ();
}

bool is_directory(String *dir) {
	// Simple checking. We can't process directory if it is unknown.
	if (dir == NULL or dir->empty())
		return false;

	// Let us test whenever doc root points to a valid directory.
	struct stat st;
	if (stat(dir->c_str(), &st) < 0)
		return false;

	// Test if it is a directory.
	return (st.st_mode & S_IFDIR);
}

String *get_basename(String* filename) {
	// I believe this is OK, memory wise. The cloned memory is overwritten by
	// dirname, but that is then copied into the result, and then never touched
	// again.
	String *base = NULL;
	char* copy = strdup (filename->c_str());
	if (copy != NULL) {
		base = s(basename (copy));
		free(copy);
	}

	return base;
}

String* search_file_from_dirs(String* filename, String_list* dirs)
{
	struct stat buf;

	if(*filename == "-")
		return filename;
	
	if(dirs == NULL)
		return filename;

	// Check if contains a regular expression.
	if (filename->find("(.*)") != string::npos)
		return NULL;

	// Check whether filename can be opened without searching dirs
	if(!stat(filename->c_str(), &buf))
	{
		return filename;
	}

	// Otherwise, search dirs
	foreach (String* s, *dirs)
	{
		String* full_path = s->clone ();
		full_path->append("/");
		full_path->append(*filename);
	
		if(!stat(full_path->c_str(), &buf))
		{
			return full_path;
		}
	}

	// Otherwise, search dirs (with backslashes instead of forward slashes)
	foreach (String* s, *dirs)
	{
		String* full_path = s->clone ();
		full_path->append("/");
		full_path->append(*filename);

		String::iterator j;
		foreach (char & c, *full_path)
			if(c == '/') c = '\\';

		if(!stat(full_path->c_str(), &buf))
		{
			return full_path;
		}
	}
	
	// If file could not be found, return NULL
	return NULL;
}

/*
 * Search for the basename of the filename beginning from the
 * root directory passed by --include-searchdir argument. If
 * no root directory is provided, attempt to use the current
 * working directory.
 *
 * The search will continue until the whole root directory
 * tree is covered and only a SINGLE file match happened.
 * This is the only way to ensure that we are including the
 * supposed correct file.
 */
String *search_file_with_regexp(String *filename, bool basename = false) {
	if (filename == NULL)
		return NULL;

	// Get the root directory to be the base of the search.
	String *root = NULL;

	if (args_info.include_searchdir_arg) {
		root = s(args_info.include_searchdir_arg);
		if (not is_directory(root))
			root = NULL;
	}

	if (root == NULL) {
		// Get current working directory.
		char cwd[PATH_MAX];
		if (!getcwd(cwd, PATH_MAX))
			return NULL;

		// Make the initial root directory as the current directory.
		root = s(cwd);
	}

	String *expression = filename;
	/*
	 * We shall search extracting any directory information
	 * from the filename, leaving only its base name.
	 */
	if (basename)
		expression = get_basename(filename);

	// Regular expressions to match file names.
	boost::regex exp(*expression, boost::regex::perl);

	// Search for the filename recursively starting at the document root.
	String_list *dirlist = new String_list;
	dirlist->push_back(root);

	// Matched file names with regular expression.
	String *matched = NULL;

	// Search the tree.
	while (!dirlist->empty()) {
		// Get the top directory to test.
		String *dir = dirlist->front();
		dirlist->pop_front();

		// Open the directory.
		DIR *dirp = opendir(dir->c_str());
		if (!dirp)
			continue;

		// Get all the directory contents.
		struct dirent *dptr;
		while ((dptr = readdir(dirp))) {
			if (dptr->d_type == DT_REG) { // The path is a file.
				// Build the full path file name.
				String *uri = dir->clone();
				uri->append("/");
				uri->append(dptr->d_name);

						 // Try to match only the base name.
				bool reg_match = basename ? regex_match(dptr->d_name, exp) :
						 // Try to match the original filename.
						 regex_match(*uri, exp);

				// Check if regular expressions matches.
				if (reg_match) {
					// We can only be sure if we have the correct
					// include file if it is the only one matched.
					// More than one match means an error.
					if (matched)
						return NULL;

					// Saved it to matched.
					matched = uri;
				}
			} else if (dptr->d_type == DT_DIR) { // The path is another directory.
				// Do not process current dir and one level down dir.
				if (strcmp(dptr->d_name, ".") and
				    strcmp(dptr->d_name, "..")) {
					// Build the path.
					String *uri = dir->clone();
					uri->append("/");
					uri->append(dptr->d_name);

					// Add the newly discovered directory path to be tested.
					dirlist->push_back(uri);
				}
			}
		}

		// Close the directory.
		closedir(dirp);
	}

	return matched;
}

String* search_file(String* filename, String_list* dirs) {
	String *file = search_file_from_dirs(filename, dirs);
	if (!file && args_info.include_regexp_flag)
		file = search_file_with_regexp(filename);

	if (!file && args_info.include_name_flag)
		file = search_file_with_regexp(filename, true);

	// If file could not be found, return NULL
	return file;
}

void run_standard_transforms(PHP_script* php_script)
{
	// Remove temporaries generated by the parser for the purpose
	// of building the AST. It doesn't really matter when this 
	// transform runs, as long as it runs before XML serialisation
	Remove_parser_temporaries rpt;
	php_script->visit(&rpt);


	// There are a number of strange rules based on the value of an
	// integer/real, which must be applied. The parser cannot do this,
	// since we have to determine whether there are 1 or more - signs
	// before the number, and this is unknown at compile time. This
	// should be run early.
	Token_conversion tc;
	php_script->transform_children(&tc);
}

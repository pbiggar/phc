/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser context for the PHP parser 
 */

#ifndef PHC_PHP_CONTEXT
#define PHC_PHP_CONTEXT

#include "AST.h"
#include "lib/String.h"
#include "lib/List.h"
#include "php_parser.tab.hpp"

class PHP_context : public virtual GC_obj
{
/*
 * Constructor and destructor
 */
public:
	PHP_context (std::istream& input, String* filename);
	virtual ~PHP_context();

	std::istream& stream;

/*
 * Public interface
 */
public:
	// Wrap PHP_lex
	bool lex ();

	// Wrap PHP_parse
	bool parse ();

	bool dump_parse_tree ();

/*
 * State used by the parser
 */
public:
	AST::PHP_script* php_script;
	String* current_method;
	String* current_class;
	String* filename;

/*
 * State used by the lexical analyser
 */

// Flex internal state
public:
	void* scanner;

// Interfacing with bison
public:
	long source_line;
	List<String*> last_comments;
	AST::Commented_node* last_commented_node;
	String* hash_bang;

// Processing comments, HEREDOC strings and keywords
public: 
	bool attach_to_previous; // Attach comment to previous token?
	bool after_arrow; // was the last token we generated "->"?
	bool starts_line; // does the next token start a new line? 

	char *heredoc_id, *heredoc_id_ptr;
	long heredoc_id_len;
	String* heredoc_attr; // used to set phc.unparser.heredoc_id

// Buffers
public:
	string value_buffer;
	string source_rep_buffer;

// Returning multiple tokens from a single production
public:
	#define MAX_MT 10

	long mt_type[MAX_MT];
	YYSTYPE mt_lval[MAX_MT];
	long mt_index;
	long mt_count;
	long mt_final_state;

	// Schedule the return of a token of type "type", with semantic value
	// "lval". If "lval" is nonnull, "length" must be the length of "lval",
	// or -1 to return the entire string. lval must be zero-terminated. 

	void schedule_return(long type, const char* lval = 0, long length = -1);
	void schedule_return(long type, string& s);
	void schedule_return_string();
	void schedule_return_op(const char* op, const char* attr = NULL);

// Dealing with in-string syntax
public:
	void return_to_complex_syntax(); 
	void attach_comment(String *s);

// Initialise and destroy the scanner (bodies defined in php_scanner.lex)
public:
	void init_scanner(FILE* input);
	void destroy_scanner();
};

#endif // PHC_PHP_CONTEXT

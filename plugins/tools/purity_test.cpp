/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Printout any impure function calls in a given script
 */


#include "AST_visitor.h"
#include "process_ast/AST_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "lib/List.h"
#include "process_ir/General.h"

using namespace AST;
using namespace std;

// search for scripts that are "pure"; ie have no side effects
class Purity_test : public Visitor
{
public:
	bool pure;
	Method_invocation* impurity;
	List<Method_invocation*> recheck;

	Purity_test()
	{
		pure = true;
	}

	// the things that we worry about:
	// backticks: - translated to shell_exec function call
	void post_method_invocation(Method_invocation *in)
	{
		if (pure == false) return; // we already know its not pure

		// A side effect is something that affects the machine, or file system,
		// or something like that. Setting a global, printing out, over-writing a
		// variable, throwing an exception etc, are all not side-effects in this
		// case.
		List<String*> allowed;

		//sections

		// .NET
		// dotnet_load - not allowed 

		// Apache
		allowed.push_back(new String(""));
		// apache_child_terminate - not allowed
		allowed.push_back(new String("apache_get_modules"));
		allowed.push_back(new String("apache_get_version"));
		allowed.push_back(new String("apache_getenv"));
		allowed.push_back(new String("apache_lookup_uri")); // looks OK
		// apache_note - can set an apache thing
		allowed.push_back(new String("apache_request_headers"));
		// apache_reset_timeout - resets an apache timer
		allowed.push_back(new String("apache_response_headers"));
		// apache_setenv - sets something in apache
		allowed.push_back(new String("ascii2ebcdic"));
		allowed.push_back(new String("ebcdic2ascii"));
		allowed.push_back(new String("getallheaders"));
		// virtual - does something in apache

		// APC
		// APD
		// Arrays
		allowed.push_back(new String("array_change_key_case"));
		allowed.push_back(new String("array_chunk"));
		allowed.push_back(new String("array_combine"));
		allowed.push_back(new String("array_count_values"));
		allowed.push_back(new String("array_diff_assoc"));
		allowed.push_back(new String("array_diff_key"));
		// array_diff_uassoc - callback
		// array_diff_ukey - callback
		allowed.push_back(new String("array_diff"));
		allowed.push_back(new String("array_fill"));
		// array_filter - callback
		allowed.push_back(new String("array_flip"));
		allowed.push_back(new String("array_intersect_assoc"));
		allowed.push_back(new String("array_intersect_key"));
		allowed.push_back(new String("array_intersect_uassoc"));
		allowed.push_back(new String("array_intersect_ukey"));
		allowed.push_back(new String("array_intersect"));
		allowed.push_back(new String("array_key_exists"));
		allowed.push_back(new String("array_keys"));
		// array_map - callback
		allowed.push_back(new String("array_merge_recursive"));
		allowed.push_back(new String("array_merge"));
		allowed.push_back(new String("array_multisort"));
		allowed.push_back(new String("array_pad"));
		allowed.push_back(new String("array_pop"));
		allowed.push_back(new String("array_product"));
		allowed.push_back(new String("array_push"));
		allowed.push_back(new String("array_rand"));
		//  array_reduce - callback
		allowed.push_back(new String("array_reverse"));
		allowed.push_back(new String("array_search"));
		allowed.push_back(new String("array_shift"));
		allowed.push_back(new String("array_slice"));
		allowed.push_back(new String("array_splice"));
		allowed.push_back(new String("array_sum"));
		// array_udiff_assoc - callback
		// array_udiff_uassoc - callback
		// array_udiff - callback
		// array_uintersect_assoc - callback
		// array_uintersect_uassoc - callback
		// array_uintersect - callback
		allowed.push_back(new String("array_unique"));
		allowed.push_back(new String("array_unshift"));
		allowed.push_back(new String("array_values"));
		// array_walk_recursive - callback
		// array_walk - callback
		allowed.push_back(new String("array"));
		allowed.push_back(new String("arsort"));
		allowed.push_back(new String("asort"));
		allowed.push_back(new String("compact"));
		allowed.push_back(new String("count"));
		allowed.push_back(new String("current"));
		allowed.push_back(new String("each"));
		allowed.push_back(new String("end"));
		// extract - plays with the symbol table
		allowed.push_back(new String("in_array"));
		allowed.push_back(new String("key"));
		allowed.push_back(new String("krsort"));
		allowed.push_back(new String("ksort"));
		allowed.push_back(new String("list"));
		allowed.push_back(new String("natcasesort"));
		allowed.push_back(new String("natsort"));
		allowed.push_back(new String("next"));
		allowed.push_back(new String("pos"));
		allowed.push_back(new String("prev"));
		allowed.push_back(new String("range"));
		allowed.push_back(new String("reset"));
		allowed.push_back(new String("rsort"));
		allowed.push_back(new String("shuffle"));
		allowed.push_back(new String("sizeof"));
		allowed.push_back(new String("sort"));
		// uasort - callback
		// uksort - callback
		// usort - callback

		// Aspell
		// BC math
		// bcompiler
		// Bzip2
		// Calendar
		// CCVS

		// Classes/Objects
		// call_user_method_array - callback
		// call_user_method - not allowed
		allowed.push_back(new String("class_exists"));
		allowed.push_back(new String("get_class_methods"));
		allowed.push_back(new String("get_class_vars"));
		allowed.push_back(new String("get_class"));
		allowed.push_back(new String("get_declared_classes"));
		allowed.push_back(new String("get_declared_interfaces"));
		allowed.push_back(new String("get_object_vars"));
		allowed.push_back(new String("get_parent_class"));
		allowed.push_back(new String("interface_exists"));
		allowed.push_back(new String("is_a"));
		allowed.push_back(new String("is_subclass_of"));
		allowed.push_back(new String("method_exists"));
		allowed.push_back(new String("property_exists"));

		// Classkit
		// ClibPDF
		// COM
		// Crack
		// ctype
		// CURL
		// Cybercash
		// CyberMUT
		// Cyrus IMAP

		// Date/Time
		allowed.push_back(new String("checkdate"));
		allowed.push_back(new String("date_default_timezone_get"));
		// only sets in the script, not the system
		allowed.push_back(new String("date_default_timezone_set")); 
		allowed.push_back(new String("date_sunrise"));
		allowed.push_back(new String("date_sunset"));
		allowed.push_back(new String("date"));
		allowed.push_back(new String("getdate"));
		allowed.push_back(new String("gettimeofday"));
		allowed.push_back(new String("gmdate"));
		allowed.push_back(new String("gmmktime"));
		allowed.push_back(new String("gmstrftime"));
		allowed.push_back(new String("idate"));
		allowed.push_back(new String("localtime"));
		allowed.push_back(new String("microtime"));
		allowed.push_back(new String("mktime"));
		allowed.push_back(new String("strftime"));
		allowed.push_back(new String("strptime"));
		allowed.push_back(new String("strtotime"));
		allowed.push_back(new String("time"));

		// DB++
		// dba
		// dBase
		// DBM
		// dbx
		// Direct IO
		// Directories
		// DOM
		// DOM XML
		// enchant

		// Errors and Logging
		allowed.push_back(new String("debug_backtrace"));
		allowed.push_back(new String("debug_print_backtrace"));
		// error_log - can print to anything, according to parameter
		allowed.push_back(new String("error_reporting"));
		allowed.push_back(new String("restore_error_handler"));
		allowed.push_back(new String("restore_exception_handler"));
		// set_error_handler - callback
		// set_exception_handler - callback
		allowed.push_back(new String("trigger_error"));
		allowed.push_back(new String("user_error"));

		// Exif
		// exif_imagetype - allows file reading
		// exif_read_data - allows file reading
		// exif_tagname - not documented
		// exif_thumbnail - allows file reading
		// read_exif_data - alias for exif_read_data

		// Expect
		// fam
		// FDF
		// Fileinfo
		// filePro
		// Filesystem
		allowed.push_back(new String("basename"));
		// chgrp - not allowed
		// chmod - not allowed
		// chown - not allowed
		allowed.push_back(new String("clearstatcache")); // affects PHP
		// copy - not allowed
		// delete - not allowed
		allowed.push_back(new String("dirname"));
		allowed.push_back(new String("disk_free_space"));
		allowed.push_back(new String("disk_total_space"));
		allowed.push_back(new String("diskfreespace"));

		// opening, reading, or stating files etc isnt allowed because they might
		// be wrapped, ie www.a.com/p?kill_my_server=true

		// fclose - likewise
		// feof - likewise
		// fflush - likewise
		// fgetc - likewise
		// fgetcsv - likewise
		// fgets - likewise
		// fgetss - likewise
		// file_exists - not allowed
		// file_get_contents - not allowed
		// file_put_contents - not allowed
		// file - not allowed
		// fileatime - not allowed
		// filectime - not allowed
		// filegroup - not allowed
		// fileinode - not allowed
		// filemtime - not allowed
		// fileowner - not allowed
		// fileperms - not allowed
		// filesize - not allowed
		// filetype - not allowed
		// flock - locking
		allowed.push_back(new String("fnmatch"));
		// fopen - not allowed
		// fpassthru - not allowed
		// fputcsv - not allowed
		// fputs - not allowed
		// fread - not allowed
		// fscanf - not allowed
		// fseek - not allowed
		// fstat - not allowed
		// ftell - not allowed
		// ftruncate - not allowed
		// fwrite - not allowed
		allowed.push_back(new String("glob")); // cant be wrapped
		// is_dir - not allowed
		// is_executable - not allowed
		// is_file - not allowed
		// is_link - not allowed
		// is_readable - not allowed
		allowed.push_back(new String("is_uploaded_file")); // cant be wrapped
		// is_writable - not allowed
		// is_writeable - not allowed
		// lchgrp - not allowed
		// lchown - not allowed
		// link - not allowed
		allowed.push_back(new String("linkinfo")); // doesnt appear to be wrappable
		// lstat - not allowed
		// mkdir - not allowed
		// move_uploaded_file - not allowed
		// parse_ini_file - looks OK, but I'm sceptical
		allowed.push_back(new String("pathinfo"));
		// pclose - not allowed
		// popen - not allowed
		// readfile - not allowed
		allowed.push_back(new String("readlink")); // not wrappable
		allowed.push_back(new String("realpath"));
		// rename - not allowed
		// rewind - not allowed
		// rmdir - not allowed
		// set_file_buffer - not allowed
		// stat - not allowed
		// symlink - not allowed
		// tempnam - not allowed
		// tmpfile - not allowed
		// touch - not allowed

		// I should rethink this. No good can come of this
		allowed.push_back(new String("umask")); 
		// unlink - not allowed


		// Filter
		// Firebird/InterBase
		// Firebird/Interbase (PDO)
		// FriBiDi
		// FrontBase
		// FTP
		// Function handling
		// GeoIP

		// gettext
		allowed.push_back(new String("bind_textdomain_codeset"));
		allowed.push_back(new String("bindtextdomain"));
		allowed.push_back(new String("dcgettext"));
		allowed.push_back(new String("dcngettext"));
		allowed.push_back(new String("dgettext"));
		allowed.push_back(new String("dngettext"));
		allowed.push_back(new String("gettext"));
		allowed.push_back(new String("_")); // alias for gettext
		allowed.push_back(new String("ngettext"));
		allowed.push_back(new String("textdomain"));

		// GMP
		// gnupg
		// gopher
		// hash
		// http
		// Hyperwave
		// Hyperwave API
		// ibm_ db2
		// ICAP
		// iconv
		// id3
		// IIS Functions
		// Image
		// IMAP
		// Informix
		// Informix (PDO)
		// Ingres II
		// IRC Gateway
		// Java
		// JSON
		// kadm5
		// LDAP
		// libxml
		// Lotus Notes
		// LZF
		// Mail
		// mailparse

		// Math
		allowed.push_back(new String("abs"));
		allowed.push_back(new String("acos"));
		allowed.push_back(new String("acosh"));
		allowed.push_back(new String("asin"));
		allowed.push_back(new String("asinh"));
		allowed.push_back(new String("atan2"));
		allowed.push_back(new String("atan"));
		allowed.push_back(new String("atanh"));
		allowed.push_back(new String("base_convert"));
		allowed.push_back(new String("bindec"));
		allowed.push_back(new String("ceil"));
		allowed.push_back(new String("cos"));
		allowed.push_back(new String("cosh"));
		allowed.push_back(new String("decbin"));
		allowed.push_back(new String("dechex"));
		allowed.push_back(new String("decoct"));
		allowed.push_back(new String("deg2rad"));
		allowed.push_back(new String("exp"));
		allowed.push_back(new String("expm1"));
		allowed.push_back(new String("floor"));
		allowed.push_back(new String("fmod"));
		allowed.push_back(new String("getrandmax"));
		allowed.push_back(new String("hexdec"));
		allowed.push_back(new String("hypot"));
		allowed.push_back(new String("is_finite"));
		allowed.push_back(new String("is_infinite"));
		allowed.push_back(new String("is_nan"));
		allowed.push_back(new String("lcg_value"));
		allowed.push_back(new String("log10"));
		allowed.push_back(new String("log1p"));
		allowed.push_back(new String("log"));
		allowed.push_back(new String("max"));
		allowed.push_back(new String("min"));
		allowed.push_back(new String("mt_getrandmax"));
		allowed.push_back(new String("mt_rand")); // could affect system RNG, but OK
		allowed.push_back(new String("mt_srand")); // could affect system RNG, but OK
		allowed.push_back(new String("octdec"));
		allowed.push_back(new String("pi"));
		allowed.push_back(new String("pow"));
		allowed.push_back(new String("rad2deg"));
		allowed.push_back(new String("rand"));
		allowed.push_back(new String("round"));
		allowed.push_back(new String("sin"));
		allowed.push_back(new String("sinh"));
		allowed.push_back(new String("sqrt"));
		allowed.push_back(new String("srand")); // could affect system RNG, but OK
		allowed.push_back(new String("tan"));
		allowed.push_back(new String("tanh"));

		// MaxDB
		// MCAL
		// mcrypt
		// MCVE
		// Memcache
		// mhash
		// Mimetype
		// Ming (flash)
		// Misc.
		allowed.push_back(new String("connection_aborted"));
		allowed.push_back(new String("connection_status"));
		allowed.push_back(new String("connection_timeout"));
		allowed.push_back(new String("constant"));
		allowed.push_back(new String("define"));
		allowed.push_back(new String("defined"));
		allowed.push_back(new String("die"));
		// eval - obvious
		allowed.push_back(new String("exit"));
		allowed.push_back(new String("get_browser"));
		// __halt_compiler - a bit odd, not sure how it works
		// highlight_file - whether affected by wrapping isnt specified in docs
		allowed.push_back(new String("highlight_string"));
		allowed.push_back(new String("ignore_user_abort"));
		allowed.push_back(new String("pack"));
		allowed.push_back(new String("php_check_syntax"));
		allowed.push_back(new String("php_strip_whitespace"));
		// show_source - alias of highlight_file
		allowed.push_back(new String("sleep"));
		allowed.push_back(new String("sys_getloadavg"));
		allowed.push_back(new String("time_nanosleep"));
		// time_sleep_until - this will make our scripts run forever, potentially
		allowed.push_back(new String("uniqid"));
		allowed.push_back(new String("unpack"));
		allowed.push_back(new String("usleep"));

		// mnoGoSearch
		// MS SQL Server
		// MS SQL Server (PDO)
		// Msession
		// mSQL
		// Multibyte String
		// muscat
		// MySQL
		// MySQL (PDO)
		// mysqli
		// Ncurses
		// Network
		// Newt
		// NSAPI
		// Object Aggregation
		// Object overloading
		// OCI8
		// ODBC
		// ODBC and DB2 (PDO)
		// OGG/Vorbis
		// openal
		// OpenSSL
		// Oracle
		// Oracle (PDO)


		// Output Control
		// these affect the output buffer, so playing with them is fine
		allowed.push_back(new String("flush"));
		allowed.push_back(new String("ob_clean"));
		allowed.push_back(new String("ob_end_clean"));
		allowed.push_back(new String("ob_end_flush"));
		allowed.push_back(new String("ob_flush"));
		allowed.push_back(new String("ob_get_clean"));
		allowed.push_back(new String("ob_get_contents"));
		allowed.push_back(new String("ob_get_flush"));
		allowed.push_back(new String("ob_get_length"));
		allowed.push_back(new String("ob_get_level"));
		allowed.push_back(new String("ob_get_status"));
		// ob_gzhandler - involves callbacks. Uh oh
		allowed.push_back(new String("ob_implicit_flush"));
		// ob_list_handlers - involves callbacks. Uh oh
		// ob_start - callback
		allowed.push_back(new String("output_add_rewrite_var"));
		allowed.push_back(new String("output_reset_rewrite_vars"));

		// OvrimosSQL
		// Paradox
		// Parsekit
		// PCNTL
		// PCRE
		allowed.push_back(new String("preg_grep"));
		allowed.push_back(new String("preg_last_error"));
		allowed.push_back(new String("preg_match_all"));
		allowed.push_back(new String("preg_match"));
		allowed.push_back(new String("preg_quote"));
		// preg_replace_callback - callback
		allowed.push_back(new String("preg_replace"));
		allowed.push_back(new String("preg_split"));

		// PDF
		// PDO
		// PHP Options/Info
		// assert_options - allows a callback
		allowed.push_back(new String("assert"));
		// dl - loads an extension - might have an init function?
		allowed.push_back(new String("extension_loaded"));
		allowed.push_back(new String("get_cfg_var"));
		allowed.push_back(new String("get_current_user"));
		allowed.push_back(new String("get_defined_constants"));
		allowed.push_back(new String("get_extension_funcs"));
		allowed.push_back(new String("get_include_path"));
		allowed.push_back(new String("get_included_files"));
		allowed.push_back(new String("get_loaded_extensions"));
		allowed.push_back(new String("get_magic_quotes_gpc"));
		allowed.push_back(new String("get_magic_quotes_runtime"));
		allowed.push_back(new String("get_required_files"));
		allowed.push_back(new String("getenv"));
		allowed.push_back(new String("getlastmod"));
		allowed.push_back(new String("getmygid"));
		allowed.push_back(new String("getmyinode"));
		allowed.push_back(new String("getmypid"));
		allowed.push_back(new String("getmyuid"));
		allowed.push_back(new String("getopt"));
		allowed.push_back(new String("getrusage"));
		// ini_alter - allows setting of callbacks
		allowed.push_back(new String("ini_get_all"));
		allowed.push_back(new String("ini_get"));
		// ini_restore - allows setting of callbacks
		// ini_set - allows setting of callbacks
		// main - not a real function
		allowed.push_back(new String("memory_get_peak_usage"));
		allowed.push_back(new String("memory_get_usage"));
		allowed.push_back(new String("php_ini_scanned_files"));
		allowed.push_back(new String("php_logo_guid"));
		allowed.push_back(new String("php_sapi_name"));
		allowed.push_back(new String("php_uname"));
		allowed.push_back(new String("phpcredits"));
		allowed.push_back(new String("phpinfo"));
		allowed.push_back(new String("phpversion"));
		// putenv - setting some env vars can be bad
		allowed.push_back(new String("restore_include_path"));
		allowed.push_back(new String("set_include_path"));
		allowed.push_back(new String("set_magic_quotes_runtime"));
		allowed.push_back(new String("set_time_limit"));
		allowed.push_back(new String("sys_get_temp_dir"));
		allowed.push_back(new String("version_compare"));
		allowed.push_back(new String("zend_logo_guid"));
		allowed.push_back(new String("zend_version"));

		// POSIX
		// POSIX Regex
		allowed.push_back(new String("ereg_replace"));
		allowed.push_back(new String("ereg"));
		allowed.push_back(new String("eregi_replace"));
		allowed.push_back(new String("eregi"));
		allowed.push_back(new String("split"));
		allowed.push_back(new String("spliti"));
		allowed.push_back(new String("sql_regcase"));

		// PostgreSQL
		// PostgreSQL (PDO)
		// Printer
		// Program Execution
		// PS
		// Pspell
		// qtdom
		// radius
		// Rar
		// Readline
		// Recode
		// RPMReader
		// runkit
		// Satellite
		// SDO
		// SDO DAS XML
		// SDO-DAS-Relational
		// Semaphore
		// SESAM
		// Session PgSQL
		// Sessions
		// shmop
		// SimpleXML
		// SNMP
		// SOAP
		// Sockets
		// spl
		// SQLite
		// SQLite (PDO)
		// ssh2
		// Statistics
		// Streams
		// Strings
		allowed.push_back(new String("addcslashes"));
		allowed.push_back(new String("addslashes"));
		allowed.push_back(new String("bin2hex"));
		allowed.push_back(new String("chop"));
		allowed.push_back(new String("chr"));
		allowed.push_back(new String("chunk_split"));
		allowed.push_back(new String("convert_cyr_string"));
		allowed.push_back(new String("convert_uudecode"));
		allowed.push_back(new String("convert_uuencode"));
		allowed.push_back(new String("count_chars"));
		allowed.push_back(new String("crc32"));
		allowed.push_back(new String("crypt"));
		allowed.push_back(new String("echo"));
		allowed.push_back(new String("explode"));
		// fprintf - not allowed
		allowed.push_back(new String("get_html_translation_table"));
		allowed.push_back(new String("hebrev"));
		allowed.push_back(new String("hebrevc"));
		allowed.push_back(new String("html_entity_decode"));
		allowed.push_back(new String("htmlentities"));
		allowed.push_back(new String("htmlspecialchars_decode"));
		allowed.push_back(new String("htmlspecialchars"));
		allowed.push_back(new String("implode"));
		allowed.push_back(new String("join"));
		allowed.push_back(new String("levenshtein"));
		allowed.push_back(new String("localeconv"));
		allowed.push_back(new String("ltrim"));
		allowed.push_back(new String("md5_file"));
		allowed.push_back(new String("md5"));
		allowed.push_back(new String("metaphone"));
		allowed.push_back(new String("money_format"));
		allowed.push_back(new String("nl_langinfo"));
		allowed.push_back(new String("nl2br"));
		allowed.push_back(new String("number_format"));
		allowed.push_back(new String("ord"));
		allowed.push_back(new String("parse_str"));
		allowed.push_back(new String("print"));
		allowed.push_back(new String("printf"));
		allowed.push_back(new String("quoted_printable_decode"));
		allowed.push_back(new String("quotemeta"));
		allowed.push_back(new String("rtrim"));
		// setlocale - per process, so can affect other threads
		allowed.push_back(new String("sha1_file"));
		allowed.push_back(new String("sha1"));
		allowed.push_back(new String("similar_text"));
		allowed.push_back(new String("soundex"));
		allowed.push_back(new String("sprintf"));
		allowed.push_back(new String("sscanf"));
		allowed.push_back(new String("str_ireplace"));
		allowed.push_back(new String("str_pad"));
		allowed.push_back(new String("str_repeat"));
		allowed.push_back(new String("str_replace"));
		allowed.push_back(new String("str_rot13"));
		allowed.push_back(new String("str_shuffle"));
		allowed.push_back(new String("str_split"));
		allowed.push_back(new String("str_word_count"));
		allowed.push_back(new String("strcasecmp"));
		allowed.push_back(new String("strchr"));
		allowed.push_back(new String("strcmp"));
		allowed.push_back(new String("strcoll"));
		allowed.push_back(new String("strcspn"));
		allowed.push_back(new String("strip_tags"));
		allowed.push_back(new String("stripcslashes"));
		allowed.push_back(new String("stripos"));
		allowed.push_back(new String("stripslashes"));
		allowed.push_back(new String("stristr"));
		allowed.push_back(new String("strlen"));
		allowed.push_back(new String("strnatcasecmp"));
		allowed.push_back(new String("strnatcmp"));
		allowed.push_back(new String("strncasecmp"));
		allowed.push_back(new String("strncmp"));
		allowed.push_back(new String("strpbrk"));
		allowed.push_back(new String("strpos"));
		allowed.push_back(new String("strrchr"));
		allowed.push_back(new String("strrev"));
		allowed.push_back(new String("strripos"));
		allowed.push_back(new String("strrpos"));
		allowed.push_back(new String("strspn"));
		allowed.push_back(new String("strstr"));
		allowed.push_back(new String("strtok"));
		allowed.push_back(new String("strtolower"));
		allowed.push_back(new String("strtoupper"));
		allowed.push_back(new String("strtr"));
		allowed.push_back(new String("substr_compare"));
		allowed.push_back(new String("substr_count"));
		allowed.push_back(new String("substr_replace"));
		allowed.push_back(new String("substr"));
		allowed.push_back(new String("trim"));
		allowed.push_back(new String("ucfirst"));
		allowed.push_back(new String("ucwords"));
		// vfprintf - prints to a file
		allowed.push_back(new String("vprintf"));
		allowed.push_back(new String("vsprintf"));
		allowed.push_back(new String("wordwrap"));

		// SWF
		// Sybase
		// TCP Wrappers
		// tidy
		// Tokenizer
		// Unicode
		// URLs
		allowed.push_back(new String("base64_decode"));
		allowed.push_back(new String("base64_encode"));
		allowed.push_back(new String("get_headers"));
		allowed.push_back(new String("get_meta_tags"));
		allowed.push_back(new String("http_build_query"));
		allowed.push_back(new String("parse_url"));
		allowed.push_back(new String("rawurldecode"));
		allowed.push_back(new String("rawurlencode"));
		allowed.push_back(new String("urldecode"));
		allowed.push_back(new String("urlencode"));


		// Variables handling
		allowed.push_back(new String("debug_zval_dump"));
		allowed.push_back(new String("doubleval"));
		allowed.push_back(new String("empty"));
		allowed.push_back(new String("floatval"));
		allowed.push_back(new String("get_defined_vars"));
		allowed.push_back(new String("get_resource_type"));
		allowed.push_back(new String("gettype"));
		allowed.push_back(new String("import_request_variables"));
		allowed.push_back(new String("intval"));
		allowed.push_back(new String("is_array"));
		allowed.push_back(new String("is_bool"));
		allowed.push_back(new String("is_callable"));
		allowed.push_back(new String("is_double"));
		allowed.push_back(new String("is_float"));
		allowed.push_back(new String("is_int"));
		allowed.push_back(new String("is_integer"));
		allowed.push_back(new String("is_long"));
		allowed.push_back(new String("is_null"));
		allowed.push_back(new String("is_numeric"));
		allowed.push_back(new String("is_object"));
		allowed.push_back(new String("is_real"));
		allowed.push_back(new String("is_resource"));
		allowed.push_back(new String("is_scalar"));
		allowed.push_back(new String("is_string"));
		allowed.push_back(new String("isset"));
		allowed.push_back(new String("print_r"));
		allowed.push_back(new String("serialize"));
		allowed.push_back(new String("settype"));
		allowed.push_back(new String("strval"));
		// unserialize - allows callbacks via php.ini settings
		allowed.push_back(new String("unset"));
		allowed.push_back(new String("var_dump"));
		allowed.push_back(new String("var_export"));

		// Verisign Payflow Pro
		// vpopmail
		// W32api
		// WDDX
		// win32ps
		// win32service
		// xattr
		// xdiff
		// XML
		// XML-RPC
		// XMLReader
		// xmlwriter
		// XSL
		// XSLT
		// YAZ
		// YP/NIS
		// Zip
		// Zlib

		// if overwriting functions is allowed, have to watch for that

		Wildcard<METHOD_NAME>* method_name = new Wildcard<METHOD_NAME>;
		Method_invocation* method = new Method_invocation (
			new Wildcard<CLASS_NAME> (),
			method_name, NULL);

		bool found = false;
		if (in->match (method))
		{
			// check against all allowed methods 
			// TODO theres a multitude of better ways to do this - hashtable
			List<String*>::const_iterator ci;
			for(ci = allowed.begin(); ci != allowed.end(); ci++)
			{
				if (*(method_name->value->value) == **ci)
				{
					found = true;
					break;
				}
			}
		}

		if (not found)
		{
			pure = false;
			impurity = in;
		}

	}

	void post_php_script(PHP_script* in)
	{
		if (not pure)
		{
			AST_unparser unparser (cout, true);
			cout << "Impure: ";
			unparser.unparse (impurity);
			cout << endl;
		}
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Purity_test ());
}

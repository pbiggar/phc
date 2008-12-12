/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Various routines for escaping strings.
 */

#ifndef PHC_ESCAPE_H
#define PHC_ESCAPE_H

class String;

/* 
 * C
 */

// For double-quoted strings
String* escape_C_dq (String* s);

// For comments
String* escape_C_comment (String* s);


/* 
 * PHP
 */

// For double-quoted strings
String* escape_PHP_dq (String* s);

// For single-quoted strings
String* escape_PHP_sq(String* s);

/*
 * Dotty
 */

String* escape_DOT (String* in, int max_length = -1);
String* escape_DOT_record (String* in, int max_length = -1);

#endif // PHC_ESCAPE_H

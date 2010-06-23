/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: /usr/bin/gperf --language=ANSI-C --includes --readonly-tables --struct-type --ignore-case --output-file=src/generated/keywords.h src/generated_src/php.gperf  */
/* Computed positions: -k'1,3-4' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "src/generated_src/php.gperf"

	/*
	 * phc -- the open source PHP compiler
	 * See doc/license/README.license for licensing information
	 *
	 * List of reserved keywords 
	 */

	// Suppress warnings in the gperf generated code 
	#pragma GCC system_header
#line 12 "src/generated_src/php.gperf"
struct keyword { char* name; int token; };
#include <string.h>

#define TOTAL_KEYWORDS 69
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 12
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 146
/* maximum key range = 144, duplicates = 0 */

#ifndef GPERF_DOWNCASE
#define GPERF_DOWNCASE 1
static unsigned char gperf_downcase[256] =
  {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
     45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
    195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
    225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
    255
  };
#endif

#ifndef GPERF_CASE_STRCMP
#define GPERF_CASE_STRCMP 1
static int
gperf_case_strcmp (register const char *s1, register const char *s2)
{
  for (;;)
    {
      unsigned char c1 = gperf_downcase[(unsigned char)*s1++];
      unsigned char c2 = gperf_downcase[(unsigned char)*s2++];
      if (c1 != 0 && c1 == c2)
        continue;
      return (int)c1 - (int)c2;
    }
}
#endif

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147,  15,  85,   5,  10,   0,
       30,   0,   0,  30, 147, 147,  25,  65,  45,  55,
        5,   0,  40,   0,   0,  60,   0,  20,   5,   0,
      147, 147, 147, 147, 147,  15, 147,  15,  85,   5,
       10,   0,  30,   0,   0,  30, 147, 147,  25,  65,
       45,  55,   5,   0,  40,   0,   0,  60,   0,  20,
        5,   0, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
      147, 147, 147, 147, 147, 147
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct keyword *
in_word_set (register const char *str, register unsigned int len)
{
  static const struct keyword wordlist[] =
    {
      {""}, {""}, {""},
#line 75 "src/generated_src/php.gperf"
      {"try",					K_TRY},
#line 30 "src/generated_src/php.gperf"
      {"else",					K_ELSE},
      {""},
#line 31 "src/generated_src/php.gperf"
      {"elseif",				K_ELSEIF},
#line 42 "src/generated_src/php.gperf"
      {"extends",				K_EXTENDS},
      {""},
#line 22 "src/generated_src/php.gperf"
      {"case",					K_CASE},
#line 32 "src/generated_src/php.gperf"
      {"empty",				K_EMPTY},
      {""},
#line 28 "src/generated_src/php.gperf"
      {"do",					K_DO},
#line 41 "src/generated_src/php.gperf"
      {"die",					K_DIE},
      {""},
#line 76 "src/generated_src/php.gperf"
      {"catch",				K_CATCH},
      {""},
#line 20 "src/generated_src/php.gperf"
      {"as",					K_AS},
      {""},
#line 37 "src/generated_src/php.gperf"
      {"endswitch",			K_ENDSWITCH},
      {""},
#line 58 "src/generated_src/php.gperf"
      {"static",				K_STATIC},
      {""},
#line 73 "src/generated_src/php.gperf"
      {"abstract",			K_ABSTRACT},
      {""},
#line 23 "src/generated_src/php.gperf"
      {"class",				K_CLASS},
      {""}, {""},
#line 14 "src/generated_src/php.gperf"
      {"and",					K_AND},
#line 52 "src/generated_src/php.gperf"
      {"list",					K_LIST},
#line 33 "src/generated_src/php.gperf"
      {"enddeclare",			K_ENDDECLARE},
      {""},
#line 47 "src/generated_src/php.gperf"
      {"if",					K_IF},
      {""},
#line 40 "src/generated_src/php.gperf"
      {"exit",					K_EXIT},
#line 51 "src/generated_src/php.gperf"
      {"isset",				K_ISSET},
#line 59 "src/generated_src/php.gperf"
      {"switch",				K_SWITCH},
      {""},
#line 38 "src/generated_src/php.gperf"
      {"endwhile",			K_ENDWHILE},
#line 68 "src/generated_src/php.gperf"
      {"interface",			K_INTERFACE},
#line 50 "src/generated_src/php.gperf"
      {"instanceof",			K_INSTANCEOF},
      {""},
#line 71 "src/generated_src/php.gperf"
      {"private",				K_PRIVATE},
#line 62 "src/generated_src/php.gperf"
      {"var",					K_VAR},
#line 39 "src/generated_src/php.gperf"
      {"eval",					K_EVAL},
#line 36 "src/generated_src/php.gperf"
      {"endif",				K_ENDIF},
#line 34 "src/generated_src/php.gperf"
      {"endfor",				K_ENDFOR},
#line 26 "src/generated_src/php.gperf"
      {"declare",				K_DECLARE},
#line 16 "src/generated_src/php.gperf"
      {"xor",					K_XOR},
      {""},
#line 35 "src/generated_src/php.gperf"
      {"endforeach",			K_ENDFOREACH},
      {""}, {""}, {""},
#line 65 "src/generated_src/php.gperf"
      {"__CLASS__",			K___CLASS__},
#line 24 "src/generated_src/php.gperf"
      {"const",				K_CONST},
      {""},
#line 15 "src/generated_src/php.gperf"
      {"or",					K_OR},
#line 25 "src/generated_src/php.gperf"
      {"continue",			K_CONTINUE},
#line 29 "src/generated_src/php.gperf"
      {"echo",					K_ECHO},
#line 81 "src/generated_src/php.gperf"
      {"false",				C_FALSE},
      {""},
#line 27 "src/generated_src/php.gperf"
      {"default",				K_DEFAULT},
#line 61 "src/generated_src/php.gperf"
      {"use",					K_USE},
#line 80 "src/generated_src/php.gperf"
      {"true",					C_TRUE},
#line 60 "src/generated_src/php.gperf"
      {"unset",				K_UNSET},
      {""},
#line 48 "src/generated_src/php.gperf"
      {"include",				K_INCLUDE},
#line 53 "src/generated_src/php.gperf"
      {"new",					K_NEW},
#line 72 "src/generated_src/php.gperf"
      {"protected",			K_PROTECTED},
#line 69 "src/generated_src/php.gperf"
      {"implements",			K_IMPLEMENTS},
      {""},
#line 49 "src/generated_src/php.gperf"
      {"include_once",		K_INCLUDE_ONCE},
#line 43 "src/generated_src/php.gperf"
      {"for",					K_FOR},
      {""},
#line 19 "src/generated_src/php.gperf"
      {"array",				K_ARRAY},
      {""},
#line 44 "src/generated_src/php.gperf"
      {"foreach",				K_FOREACH},
#line 18 "src/generated_src/php.gperf"
      {"__LINE__",			K___LINE__},
      {""},
#line 63 "src/generated_src/php.gperf"
      {"while",				K_WHILE},
      {""}, {""},
#line 17 "src/generated_src/php.gperf"
      {"__FILE__",			K___FILE__},
      {""},
#line 54 "src/generated_src/php.gperf"
      {"print",				K_PRINT},
      {""}, {""},
#line 45 "src/generated_src/php.gperf"
      {"function",			K_FUNCTION},
      {""},
#line 66 "src/generated_src/php.gperf"
      {"__METHOD__",			K___METHOD__},
      {""},
#line 79 "src/generated_src/php.gperf"
      {"old_function",		K_OLD_FUNCTION},
      {""}, {""},
#line 67 "src/generated_src/php.gperf"
      {"final",				K_FINAL},
      {""}, {""}, {""},
#line 82 "src/generated_src/php.gperf"
      {"null",					C_NULL},
#line 77 "src/generated_src/php.gperf"
      {"throw",				K_THROW},
      {""}, {""}, {""}, {""},
#line 21 "src/generated_src/php.gperf"
      {"break",				K_BREAK},
#line 57 "src/generated_src/php.gperf"
      {"return",				K_RETURN},
#line 55 "src/generated_src/php.gperf"
      {"require",				K_REQUIRE},
      {""}, {""},
#line 74 "src/generated_src/php.gperf"
      {"clone",				K_CLONE},
      {""},
#line 56 "src/generated_src/php.gperf"
      {"require_once",		K_REQUIRE_ONCE},
      {""}, {""}, {""}, {""},
#line 64 "src/generated_src/php.gperf"
      {"__FUNCTION__",		K___FUNCTION__},
      {""},
#line 78 "src/generated_src/php.gperf"
      {"cfunction",			K_CFUNCTION},
      {""},
#line 70 "src/generated_src/php.gperf"
      {"public",				K_PUBLIC},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 46 "src/generated_src/php.gperf"
      {"global",				K_GLOBAL}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if ((((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strcmp (str, s))
            return &wordlist[key];
        }
    }
  return 0;
}

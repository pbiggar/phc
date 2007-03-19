/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base64 encoder/decoder. See RFC2045.
 */

#include "lib/String.h"
#include <iostream>
#include <sstream>

using namespace std;

static char enc_table[] = 
	"ABCDEFGHIJKLMNOPQ"
	"RSTUVWXYZabcdefgh"
	"ijklmnopqrstuvwxy"
	"z0123456789+/";

// Reverse of the enc_table
// Return 0xFF for padding bytes
unsigned char decode(unsigned char c)
{
	if(c >= 'A' && c <= 'Z') 
		return c - 'A';

	if(c >= 'a' && c <= 'z')
		return c - 'a' + 26;

	if(c >= '0' && c <= '9')
		return c - '0' + 26 + 26;

	if(c == '+')
		return 26 + 26 + 10;
	
	if(c == '/')
		return 26 + 26 + 10 + 1;

	if(c == '=')
		return 0xFF;

	assert(false);
	return 0;
}

#define TRIPLE_TO_QUAD \
	a = (x & 0xFC) >> 2; \
	b = ((x & 0x03) << 4) | ((y & 0xF0) >> 4); \
	c = ((y & 0x0F) << 2) | ((z & 0xC0) >> 6); \
	d = z & 0x3F;

#define QUAD_TO_TRIPLE \
	x = (a << 2) | ((b & 0x30) >> 4); \
	y = ((b & 0x0F) << 4) | ((c & 0x3C) >> 2); \
	z = ((c & 0x03) << 6) | d;

String* base64_encode(String* str)
{
	String::const_iterator i = str->begin();
	ostringstream os;
	unsigned char x, y, z;
	unsigned char a, b, c, d;

	while(i != str->end())
	{
		x = *i++;
		if(i == str->end())
		{
			// Two padding bytes
			y = 0;
			z = 0;
			TRIPLE_TO_QUAD;
			os << enc_table[a];
			os << enc_table[b];
			os << '=';
			os << '=';
			break;
		}

		y = *i++;
		if(i == str->end())
		{
			// One padding byte
			z = 0;
			TRIPLE_TO_QUAD;
			os << enc_table[a];
			os << enc_table[b];
			os << enc_table[c];
			os << '=';
			break;
		}

		z = *i++;
		TRIPLE_TO_QUAD;

		os << enc_table[a];
		os << enc_table[b];
		os << enc_table[c];
		os << enc_table[d];
	}

	return new String(os.str());
}

String* base64_decode(String* str)
{
	String::const_iterator i = str->begin();
	ostringstream os;
	unsigned char x, y, z;
	unsigned char a, b, c, d;

	while(i != str->end())
	{
		a = decode(*i++);
		b = decode(*i++);
		c = decode(*i++);
		d = decode(*i++);

		if(c == 0xFF)
		{
			// Two padding bytes
			QUAD_TO_TRIPLE;
			os << x;
			break;
		}
		
		if(d == 0xFF)
		{
			// One padding byte
			QUAD_TO_TRIPLE;
			os << x << y;
			break;
		}

		QUAD_TO_TRIPLE;
		os << x << y << z;
	}

	return new String(os.str());
}

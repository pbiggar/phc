#include <stdlib.h>
#include <stdio.h>


struct nest
{
  int nested_int;
};

struct state
{
  struct state* next;
  int num;
  int** ptr;
  struct nest nested;
};



/*

void test111(int* p, int count)
{
  for(int i=0; i<count; i++)
  	 p[count] = 9;

}

void test112(int* p, int count)
{
  if(count < 0) p = 0;
  test111(p, count);
}

void foo(int* p, int size, int* q)
{
  if(size <= 0) return;
  p = 0;
  for(int i=0; i<size; i++)
  {
     // p = &((char*) q)[i];
	p = malloc(10);
	*p = 8;
  }

  *p = 8;
}

*/



#define CVAL(buf,pos) ((unsigned)(((const unsigned char *)(buf))[pos]))
#define CVAL_NC(buf,pos) (((unsigned char *)(buf))[pos]) 
#define PVAL(buf,pos) (CVAL(buf,pos))
#define SCVAL(buf,pos,val) (CVAL_NC(buf,pos) = (val))



#define SVAL(buf,pos) (PVAL(buf,pos)|PVAL(buf,(pos)+1)<<8)
#define IVAL(buf,pos) (SVAL(buf,pos)|SVAL(buf,(pos)+2)<<16)
#define SSVALX(buf,pos,val) (CVAL_NC(buf,pos)=(unsigned char)((val)&0xFF),CVAL_NC(buf,pos+1)=(unsigned char)((val)>>8))
#define SIVALX(buf,pos,val) (SSVALX(buf,pos,val&0xFFFF),SSVALX(buf,pos+2,val>>16))
#define SVALS(buf,pos) ((int16)SVAL(buf,pos))
#define IVALS(buf,pos) ((int32)IVAL(buf,pos))
#define SSVAL(buf,pos,val) SSVALX((buf),(pos),((uint16)(val)))
#define SIVAL(buf,pos,val) SIVALX((buf),(pos),((uint32)(val)))
#define SSVALS(buf,pos,val) SSVALX((buf),(pos),((int16)(val)))
#define SIVALS(buf,pos,val) SIVALX((buf),(pos),((int32)(val)))

int* pull_string(int* in_buffer)
{
   *in_buffer = 8;
   if(*in_buffer) return *in_buffer;
   return 0;
}

int decode_pw_buffer(int in_buffer[516], char *new_pwrd,
		      int new_pwrd_size, int *new_pw_len,
		      int string_flags, int* buf)
{

	int byte_len=0;



	byte_len = IVAL(in_buffer, 512);


	if ( (byte_len < 0) || (byte_len > 512)) {
		return 0;
	}

 	*new_pw_len = pull_string(&in_buffer[512 - byte_len]);


	
	return 1;
}


char *test4 (const char *string)

{
  return string ? strcpy ((char *) fs_get (1 + strlen (string)),string) : 0;
}

void test5(char *p)
{
   char* ret = test4(p ? p : "");
   if(*ret) {}; 
}

void test6(int* p, int* q)
{
   int a = p ? (q ? *q : *p): 0;
   return a;
}

void test7(int* p, int* q)
{
  test6(p, q);
  if(p) *p = 8;
}


struct variable
{
   struct state* main_user_val;
   struct state* post_user_val;
   int num;
};

typedef enum {Main, Post, None} EditWhich;

#define PVAL(v,w) ((v) ? (((w) == Main) ? (v)->main_user_val->num :	\
	                                  (v)->post_user_val->num) : NULL)
int *
sampleexc_color(ps, v)
    struct pine     *ps;
    struct variable *v;
{
    int *cp = NULL;
    char *pvalfg, *pvalbg;

    pvalfg = PVAL(v, Post);
  //  pvalbg = PVAL(v+1, Post);
    if(v && color_holding_var(ps, v) &&
       srchstr(*v, "-foreground-color") &&
       pvalfg && pvalfg[0] && pvalbg && pvalbg[0])
	cp = new_color_pair(pvalfg, pvalbg);

    return(cp);
}

int test8(int* buf)
{
  buf[0] = 8;
  while(foo () && bar())
  {
	buf = malloc_wrapper(10);
  }
  if(buf && *buf) return *buf;
  return 0;
}

int
check_for_move_mbox(mbox, sourcebuf, sbuflen, targetptr)
    char  *mbox;
    char  *sourcebuf;
    size_t sbuflen;
    char **targetptr;
{
    char delim, *s;
    int  i;

    if(mbox && (mbox[0] == '#')
       && ((mbox[1] == 'M') || (mbox[1] == 'm'))
       && ((mbox[2] == 'O') || (mbox[2] == 'o'))
       && ((mbox[3] == 'V') || (mbox[3] == 'v'))
       && ((mbox[4] == 'E') || (mbox[4] == 'e'))
       && (delim = mbox[5])
       && (s = strchr(mbox+6, delim))
       && (i = s++ - (mbox + 6))
       && (!sourcebuf || i < sbuflen)){

	if(sourcebuf){
	    strncpy(sourcebuf, mbox+6, i);	/* copy source mailbox name */
	    sourcebuf[i] = '\0';
	}

	if(targetptr)
	  *targetptr = s;
	
	return 1;
    }

    return 0;
}

   long openflags;
char* debugfile;

long
pine_mail_create(stream, mailbox)
    char *stream;
    char       *mailbox;
{
   char *ourstream = NULL;
    long        return_val;
 
    char        source[3], *target = NULL;
    char    *d;

    dprint(7, (debugfile, "pine_mail_create: creating \"%s\"%s\n", 
	       mailbox ? mailbox : "(NULL)",
	       stream ? "" : " (stream was NULL)"));

    if(check_for_move_mbox(mailbox, source, sizeof(source), &target)){
	mailbox = target;
	dprint(7, (debugfile,
		   "pine_mail_create: #move special case, creating \"%s\"\n", 
		   mailbox ? mailbox : "(NULL)"));
    }


    if(!stream)
      stream = sp_stream_get(mailbox, 1);
    if(!stream)
      stream = sp_stream_get(mailbox, 2);

    if(!stream){
	/*
	 * It is only useful to open a stream in the imap case.
	 */
	if((d = mail_valid (0, mailbox, (char *) 0))
	   && !strcmp(d, "imap")){

	    stream = pine_mail_open(NULL, mailbox, openflags, NULL);
	    ourstream = stream;
	}
    }

    return_val = mail_create(stream, mailbox);

    if(ourstream)
      pine_mail_close(ourstream);

    return(return_val);
}

void test10(int *p)
{
  *p = 9;
}

void test9(int** p)
{
   int local;
   if(!*p)
   {
	*p = malloc(10);
	if(!*p) *p = 0;
	if(*p)  
		test10(*p); // STATEMENT GUARD: *arg0 == NULL && malloc != NULL

   }
}

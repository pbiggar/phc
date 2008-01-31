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

/*The simplest case: Error */
void test1(int* p)
{
  p= 0;
  *p=9;
  
}

/*No error */
void test2(int* p, int i)
{
 int q;
 p = &i;
 q = *p;
 
}

/* Simple alias test: error*/
void test3(int* p, int* q, int i)
{
  p=0;
  q = p;
  i = *q; 
}

/*Struct test: error */
void test4(struct state* s, struct state* sp)
{
  int* cursor;
  s->ptr = 0;
  sp->next->ptr = s->ptr;
  cursor = *sp->next->ptr;
}

/*Logical mistake test: Error*/
void test5(int* p)
{
  if(!p) *p = 8;
  
}

/* Error */
void test6(int* p, int flag)
{
  if(!p || flag) *p = 8;
  
}

/*Inconsistency: error*/
void test7(int*p)
{
 int q;
 if(p) *p=9;
 q=*p;
}

/*Inconsistency with aliasing: Error */
void test8(int*p, int* z)
{
 int q;
 if(p) *p=9;
 z = p;
 q=*z;
}

/*No inconsistency error: different gls's*/
void test9(int*p, int* z, int flag)
{
 int q;
  if(p) *p = 9;
  if(flag) z=p;
  q = *z;
}


/*error*/
void test10(int* p, int flag)
{
 if(flag) p =0;
 *p = 8;
}

/* INTERPROCEDURAL */

/*********Interprocedural 1************/
//no error
void test11(int* p)
{
 
  int q = *p;
}
//error
void test12(int* p)
{
 p = 0;
 test11(p);
 
}

/*********Interprocedural 2************/
//no error
void test13(int* p, int flag)
{
 if(flag) *p = 8;
 else *p = 0;
}
//error
void test14(int* p, int flag)
{
 p = 0;
 test13(p, flag);
 
}
/*********Side effect************/
//no error
void test15(struct state** s)
{
 *s = malloc(sizeof(struct state));
 (*s)->next = 0;
 (*s)->ptr = 0;
}

/* This should report *two* null dereference errors. */
void test16(struct state* s)
{
  int* q;
  int* p;
  p = malloc(sizeof(int));
  s = malloc(sizeof(struct state));
  struct state *ss;
  test15(&s);
  q = *s->ptr;
  ss = s->next;
  p = s->next->ptr;
  
}

/**************************/
//no error
void test17(struct state** s)
{
 *s = malloc(sizeof(struct state));
 (*s)->next = 0;
 (*s)->ptr = 0;
 *s = malloc(sizeof(struct state));
}

/* This should not report any null dereference errors. */
void test18(struct state* s)
{
  int* q;
  int* p;
  p = malloc(sizeof(int));
  s = malloc(sizeof(struct state));
  struct state *ss;
  test17(&s);
  q = *s->ptr;
  ss = s->next;
  p = s->next->ptr;
  
}

/*******************************/
/* Test interprocedural inconsistency*/
//no error
void test19(int* p, int* q)
{
  q = p;
  *q = 8;
}
//error
void test20(int* p, int* q)
{
  if(p) *p = 8;
  test19(p, q);
}

/*This should not report an error*/
void test21(struct state* s)
{
  *s->ptr = 0;
}
//no error
void test22(struct state* s)
{
  if(!s->ptr)
  {
    return;
  }
  test21(s);
}
//no error
void test23(int *a, int*b)
{
	*b= 7;
	if(a==b) *b = 5;
}

//We currently do not report an error for this; but this is an inconsistency
void test24(int** p, int size)
{
  if(p)
  {
   *p = malloc(10);
   **p=8; 
  }

  
  if(p && *p) **p=9;
  

}

//this is an inconsistency
void test25(int** p, int size)
{
	int i;
	for(i=0; i < size; i++)
	{
  	if(p)
  	{
  	 *p = malloc(10);
   	**p=8; 
  	}
  }

  
  if(p && *p) **p=9;
  

}

//no error,we use bitshit comps
void test26(int *p, int*q)
{
	if((int)p & 3) *p = 5;
	else *p = 7;

	if((int)q & 2) *p=5;

*p=*q;

}


//error: inconsistency in stores
void test27(int *a)
{
	if(a) *a = 5;
	*a = 7;

}

//error: inconsistency in load
void test28(int *a, int b)
{
	if(a) b = *a;
	b = *a+5;
}

//no error
void test29(struct state* s, struct state* ss, int flag)
{
   int* a = s->ptr;
  ss =s;
 
  while(ss!=0)
  {
    if(flag) s->ptr=malloc(2);
    ss = ss->next;
  }
}

//no error
void test30(int* p, int flag)
{
  int i;
 *p = 9;
 for(; p ; ++p)  *p=8;
}

//inconsistency error
void test31(int* p, int flag)
{
  int i;
 *p = 9;
 for(; flag ; ++p)  if(p) *p=8;
}

//error
void test32(int* p, int flag)
{
  int i;
 *p = 9;
 for(; flag || p  ; ++p)  *p=8;
}

//no error
void test33(int* p)
{
  if((int)p & 3) *p = 6;
  *p = 8;
}

//************LOOP TESTS******************/
//no error
void test34(int* p, int flag)
{
  p = 0;
  while(p)
  {
    *p = 8;
  }
} 


//error
void test35(int* p, int flag)
{
  p = 0;
  while(flag)
  {
    *p = 8;
  }
} 


//error
void test36(int* p, int flag, int b)
{
  p = 0;
  while(flag)
  {
    if(b) *p = 8;
  }
}

//no error
void test37(int* p, int flag, int b)
{
  if(!b) p = 0;
  while(flag)
  {
    if(b) *p = 8;
  }
} 

//error
void test38(int* p, int flag, int b)
{
  int i;
  if(b) p = 0;
  while(flag)
  {
    i++;
    if(i<3) *p = 8;
  }
} 

/*************NESTED LOOPS*************/
//error
void test39(int* p, int* q, int flag1, int flag2)
{
    while(1)
    {
  
    if(flag2 && flag1) 
     p=0;
     while(1)
     {
      
       if(flag2) *p = 8;
       if(q) break;
     }
     
     if(flag1) break;
  }
 
}

//no error
void test40(int* p, int* q, int flag1, int flag2)
{
    while(1)
    {
    if(!flag2) p=0;
     while(1)
     {
      
       if(flag2) *p = 8;
       if(q) break;
     }
     
     if(flag1) break;
  } 
}

//error
void test41(int* p, int* q, int flag1, int flag2)
{
     p=0;
    while(1)
    {
    
     while(1)
     {
      
       if(flag2) *p = 8;
       if(q) break;
     }
     
     if(flag1) break;
  } 
}

//no error
void test42(int* p, int* q, int flag1, int flag2)
{
    if(!flag2)  p=0;
    while(1)
    {
    
     while(1)
     {
      
       if(flag2) *p = 8;
       if(q) break;
     }
     
     if(flag1) break;
  } 
}

//error
void test43(int* p, int* q, int flag1, int flag2)
{
 int* z;
 p=q;
 while(flag1)
 {
   z=p;
   while(flag2)
   { 
      *z = 8;
   }
 
 }
  if(q) *q=8;
}
//no error
void test44(int* p, int* q, int flag1, int flag2)
{
 int* z;
 p=q;
 while(flag1)
 {
   z=p;
   while(flag2)
   { 
      *z = 8;
   }
 
 }
  *q=8;
}

//no error
void test45(int* p, int* q, int flag1, int flag2)
{
 int* z;
 p=q;
 while(p)
 {
   z=p;
   while(flag2)
   { 
      *z = 8;
   }
 
 }
  if(q) *q=8;
}

//error
void test46(int* p, int* q, int flag1, int flag2)
{
 int* z;
 p=q;
 while(flag2)
 {
 while(flag1)
 {
   z=p;
   while(flag2)
   { 
      *z = 8;
   }
 }
 }
  if(q) *q=8;
}

/***************************************Interprocedural **********************/
//no error
void test47(int* p)
{
 
  int q = *p;
}

//no error
void test48(int* z, int* q)
{
  z = q;
  test47(z);
}

//error
void test49(int* p, int* q)
{
 q = 0;
 test48(p, q);
 
}

/*******************************************************************************/
/*Interprocedural inconsistency**/

//no error
void test50(int* p, int* q)
{
  p=q;
  *p = 5;

}

//no error
void test51(int* p, int* q, int* z)
{ 
  z=q;
  test50(p, z);
}

//error: interprocedural inconsistency
void test52(int* p, int*q, int* z)
{
  test51(p, q, z);
 if(q) *q=8; 
 
}

/*************************************************************************************/

//no error
void test53(int* p, int* q, int flag)
{
  if(flag) p=q;
  *p = 8;
}
//error: interprocedural inconsistency
void test54(int* p, int* q, int flag)
{
 test53(p, q, flag);
 if(flag) p=q;
 if(p) *p=7;
}

/******************************************************************************/
//no error
void test55(int* p)
{ 
  *p = 0;
}

//error
void test56(int* p)
{
  if(!p) test55(p);
}

/**********TEST LOOP SIDE EFFECTS*****************************************************/

/*error*/
void test57(int* p, int* q, int flag1, int flag2)
{
  while(1)
  {
  while(1)
  {
    p=0;
    if(flag1) break;
  }
  if(flag2) break;
  }
  *p=0;
}



/*Two null dereference errors*/
void test58(int* p, int* q, int flag1, int flag2)
{
    while(1)
    {
     p=0;
     while(1)
     {
       q=0;
	if(flag2) break;
     }
     if(flag1) break;
     *q = 8;
  }
  *p = 9;
}
/*******************Interprocedural error********************************/
//no error
void test59(int* p, int* q, int flag)
{
  p=q;
  *p=4;
 
}
//no error
void test60(int* p, int* q, int flag)
{
  test59(p, q, flag);
}

//error
void test61(int* p, int* q, int flag)
{
  q=0;
  test60(p, q, flag);
}

/**********************TEST INVALIDATED NEGATION/COLLECTION*********************************/

//no error
// We got an invalidated collection on inst_transfer on this; make sure it doesn't show up.
int test62(int** p, int flag, int size)
{
  int i;
  if(flag)
     for(i=0; i<size; i++)
       *p = 0;
 return 1;
}

//no error (test mapping unknown guards out of loops)
int test63(const char *string, const char *pattern)
{
	int i;
        char a;
	for (; i < 5; i++){
		if(isupper(a))
			a =  pattern[i]; 
                else a= 'a';
                 }

	return 0;
}

//no error
int test64(char *pat, char *patend, int flag)
{
	char c, k;
	switch (c & 1) {
	case 1:
		if (pat == patend)
			return(1);		
		else return(0);
	case 2:
		while (flag)
			if ((*pat) == 1) { printf("HELLO");}
			return 2; 	
		break;
	}
	return 1;
}

/******TEST LOOP CHECKED LOCATIONS*********/
//no error
void test65(int* p, int flag)
{
  while(flag)
  {
     while(p)
      *p = 8;
  }
 *p=7;
}

/*************SOFT TRACES************/
//no error
//new fix: don't report error for soft traces
void test66(int** channels, int* c)
{
         channels[0] = 0;
	 channels[0] = c;
	 *channels[0] = 0;
}

/*****************INTERPROCEDURAL: TEST INST_TRACE ********/
//no error
int test67(const char *s, int flag)
{
  int n = 0;
  while (flag) {s++; n++; *s='a';}
  return n;
}
//error
void test68()
{
  char* c;
  test67(c,1);
  if(c) *c = 'a';
}

/******************TEST MAPPING FUNCTION DEREFS OUT OF LOOPS**********/
//error:inconsistency
void test69(char* p, int flag, int flag2)
{
  if(flag)
    while(flag2)
       test67(p, 1);

 if(p) *p=8;

}
//no error
void test70(char* p, int flag, int flag2)
{
  if(p)
    while(flag2)
       test67(p, 1);

 if(p) *p=8;

}

//error:inconsistency
void test71(char* p, int flag, int flag2)
{
  while(flag)
    while(flag2)
       test67(p, 1);

 if(p) *p=8;

}
//no error
void test72(char* p, int flag, int flag2)
{
  p=0;
  if(p)
    while(flag2)
       test67(p, 1);

 if(p) *p=8;

}

//blue error
void test73(char* p, int flag, int flag2)
{
  p=0;
  
    while(flag2)
       test67(p, 1);

 if(p) *p=8;

}

//blue error
void test74(char* p, int flag, int flag2)
{
  p=0;
  while(flag)
    while(flag2)
       test67(p, 1);

 if(p) *p=8;

}

//no error
int test75(char *t)
{
	*t ='i';
	return 5;
}

//no eror -tests an intricate statement guard & trace guard dead combination (look at unsigned)
const char *
test76(unsigned int utmp_len, int use_dns)
{
	static const char *remote = "";
	if (utmp_len > 0)
		remote = get_canonical_hostname(use_dns);
	if (utmp_len == 0 || test75(remote) > utmp_len)
		remote = get_remote_ipaddr();
	return remote;
}

int** channels;
int channels_alloc;

//no error
void test77(int* c)
{
   *c = 8;
}

//no error - tests strange trace_soft issues with (1)
void
test78(char *ctype, int type, int rfd, int wfd, int efd,
   int extusage, char *remote_name, int nonblock)
{
	int found;
	int i;
	int *c;

	/* Do initial allocation if this is the first call. */
	if (channels_alloc == 0) {
		//channels_alloc = 10;
		//channels = xmalloc(channels_alloc * sizeof(int *));
		for (i = 0; i < channels_alloc; i++)
			channels[i] = 0;
	}

	/* Initialize and return new channel. */
	c = channels[found] = xmalloc(sizeof(int));
	
	test77(c); //(1)
	
}

/**********************************************/
//error
int test79(int** p, int*q, int flag, int size)
{
  int i;
  p = 0;
  if(flag)
     for(i=0; i<size; i++)
       *p = 0;
 return 1;
}

//no error
void test80(int *a)
{
	*a=5;
}

//no error
void test81(int **a)
{
 *a = 0;
}

//2 errors
void test82(int* p, int* q, int flag1, int flag2)
{
    while(1)
    {
     test81(&p);
     while(1)
     {
       test81(&q);
	if(flag2) break;
     }
     if(flag1) break;
     test80(q);
  }
  test80(p);
}

//no error
void test83(int* p)
{
  int q;
  while(p==0){q=8;}
  *p=8;
}

//no error - test checked locations with return statements inside loops
int test84(int flag)
{
	int i;
	int *c;

	for (i = 0; i <10; i++) {
		if (c != 0) {

			if (flag) { 
				*c = 8;
				return 0;
			}
		}
	}
	return 1;
}

/********* signed pointer tests *******************/
//no error
void test85(int *p, int *q)
{
	if(p>q) 
	{
	   *p = 8;

	}
	*p = 7;
}

//error
void test86(int *p, int *q)
{
	if(p>0) 
	{
	   *p = 8;

	}
	*p = 7;
}
//no error
void test87(int *p, int *q, int flag)
{	
	while(flag)
	{
		if(p>q) 
		{
	   		*p = 8;
		}
		*p = 7;
	}
	*p=4;
}

//no error
void test88(int *p, int *q, int flag)
{	
	while(p>q)
	{
		
        	*p = 7;
	}
	*p=4;
}

/*************************************/
//no error
void test89(int** p)
{
  int* q= malloc(10);
  *p = q;
}

//no error
void test90(int* p)
{
  p=0;
  test89(&p);
  *p = 8;
}

//*ONE* error
void test91(int* p)
{
  if(p) *p= 8;
  if(p) *p = 7;
  *p = 7;
}

/****************************************/
//one error
void test92(int** p)
{
  if(p && !*p)
  {
    *p = malloc(10);
    return;
   }
   **p = 8;
}

//no error
void test93(int* p)
{
  p = 0;
  test92(&p);
}

/*******************************************/
struct sk_buff
{
  struct sk_buff* frag_list;
  struct sk_buff* next;
};


//no error
static void test94(struct sk_buff *skb, int flag)
{
      //  skb = 0;
	struct sk_buff *list = skb; 

	skb=0; 

	while(flag)
       {
		struct sk_buff *this = list;
		list = list->next;
	}
}

//error
static void test95(struct sk_buff *skb, int flag)
{
         skb = 0;
	struct sk_buff *list = skb; 

	while(flag)
       {
		struct sk_buff *this = list;
		list = list->next;
	}
}

/****************************************/
//error
void test96(int* p, int flag)
{
  if(p) flag = 1;
  *p = 9;
}

/************Test recursive trace collapse******/
/* no error */
void test97(struct state* s)
{
  if(s->next == 0)
    s->num = 8;
}

/***********Test casts**********/

// error
void test98(int* p, char* q)
{
   p = (int*) q;
   if(p) *p = 9;
   *q = 8;
}

/**********************/

// no error
void test99(int* p)
{
  int* q;
  if (foo()) return;
  if(p) q=p;
  else q = malloc(10);
  *q =8;
}

// no error: test tg_implies
void test100(void)
{
  test99(0);
}
/**********************/

/******TEST RETURNS********/
// no error
int* test101(int* p, int flag)
{
  if(flag) return 0;
  return malloc(10);
}

// no error
void test102(int* p)
{
    p = test101(p, 0);
    *p = 8;
}

// no error
int* test103(int* p, int flag)
{
  if(flag || !malloc(10)) return 0;
  return malloc(10);
}

// error
void test104(int* p)
{
    p = test103(p, 0);
    *p = 8;
}

// error
void test105(int* p)
{
    p = test101(p, 1);
    *p = 8;
}

// error
void test106(int* p)
{
    p = test103(p, 1);
    *p = 8;
}

// no error
int* test107(void)
{
  if(foo()) return 0;
  else return malloc();
}

// error
void test108(int* p)
{
   p = test107();
   *p = 8;
}

// -------------

// no error
void test109(int* p, int* q)
{
  if( !( ((char*) q) = bar())) return;
  if(p == q)
 	*p = 9;
  *p = 8;
}

// no error
void test110(int* p, int* q)
{
  if( !( ((char*) q) = bar())) return;
  if(p != q)
 	*p = 9;
  *p = 8;
}

// no error
/*
void test111(int** p)
{
   int local;
   if(!*p)
   {
	*p = malloc(10);
	if(!*p) *p = 0;
	if(*p)  
		test10(*p); 

   }
}
*/

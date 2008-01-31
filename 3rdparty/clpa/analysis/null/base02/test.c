/**************************************
* Regressions for testing correlations between 
* null parameters and flags.

***********************************/

// no error
void test1(int *p, int flag)
{
   if(flag) *p = 8;
}

// no error
void test2(void)
{
  test1(0, 0);
}

// error
void test3(void)
{
  test1(0, 1);
}

// no error
void test4(int *p, int flag)
{
   if(flag && bar()) *p = 8;
   if(flag && foo()) *p = 3;

}

// no error
void test5(void)
{
  test1(0, 0);
}


// error
void test6(void)
{
  test1(0, 1);
}


// no error
void test7(int*p , int flag1, int flag2)
{
   if(flag1 || flag2) *p = 0;
   if(flag1) *p = 8;
}

// error
void test8(int* p, int flag)
{
  p = 0;
  test7(p, 0, flag);
}

// no error
void test9(int* p, int flag)
{
  test1(p, flag);
}

// no error
void test10(void)
{
  test9(0, 0);
} 

// error
void test11(void)
{
  test9(0, 1);
} 

//no error
void test12(int* p, int* q, int flag1, int flag2)
{
  if(flag1 && flag2) *p = 0;
  if(flag1) *p = 9;
}


//error
void test13(int* p, int* q)
{
  if(p) *p = 8;
   test12(p, q, 1, 0);
}

// no error
void test14(int* p, int* q)
{
  if(p) *p = 8;
   test12(p, q, 0, 0);
}

// no error
void test15(int* p, int* q, int flag1, int flag2)
{
  p=q;
  if(flag1 && flag2) *p = 0;
  if(flag1) *p = 9;
}

//error
void test16(int* p, int *q)
{
  if(q) *q = 9;
  test15(p, q, 1, 0);
}


//no error
void test17(int* p, int *q)
{
  if(q) *q = 9;
  test15(p, q, 0, 1);
}

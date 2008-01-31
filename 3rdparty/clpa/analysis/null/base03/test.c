/*****************************************
* Regressions for testing error reporting on
* soft traces.
* Since reporting errors on soft traces
* causes a lot of false positives,
* the null analysis should currently suppress 
* any error that involves soft traces.
******************************************/

// no error: soft trace
void test1(int** p)
{
  p[0] = 0;
  *p[1] = 5;
}

// error: no soft trace
void test2(int** p)
{
  *p = 0;
  **p = 8;
}

// error (but we wouldn't want it to have an error)
void test3(int** p)
{
  *p = 0;
  **(p+1) = 8;
}

// no error
void test4(int** p)
{
  if(p[0]) *p[0] = 5;
  *(p[1]) = 6;
}

// no error
void test5(int** p)
{
  if(p[1]) *p[0] = 8;
  *p[2] = 9;
}

// no error (but we would want it to have an error)
void test6(int** p)
{
  if(p[1]) *p[1] = 8;
  *p[1] = 9;
}

// no error
void test7(int** p, int flag)
{
  if(p[0]) *p[0] = 9;
  for(int i=1; i<10; i++) *p[i] = 0;
}

// no error (BUT WE *REALLY* WOULD WANT THIS TO BE AN ERROR).
void test8(int* p, int** q)
{
   p = q[2];
   if(p) *p = 9;
   *p = 8;
}


// no error
void test9(int** p)
{
  *p[0] = 8;
}

// no error
void test10(int** p)
{
  if(p[1]) *p[1] = 8;
  test9(p);
}


// no error
void test11(int* p)
{
  *p = 8;
}

// error
void test12(int* p)
{
   if(p) *p = 9;
   test11(p);
}



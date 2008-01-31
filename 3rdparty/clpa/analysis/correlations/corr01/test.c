

// necessary and sufficient cond both: flag1 || flag2

void foo1(int* p, int flag1, int flag2)
{
  if(flag1 || flag2) 
    *p = 8;
}

void bar1(void)
{
 int* p = 0;
 int flag1, flag2;
 flag1 = flag2 = 0;
 foo1(p, flag1, flag2);
  
}
//--------------------------------------------

void foo2(int* p, int flag1, int flag2, int flag3)
{
  if(flag1 || flag2 || flag3) 
    *p = 8;
}

void bar2(int* p, int flag3)
{
 
 int flag1, flag2;
 flag1 = flag2 = 0;
 foo2(p, flag1, flag2, flag3);
  
}

void baz2(void)
{
  int* p =0;
  int flag3 = 0;
  bar2(p, flag3);
}

//------------------------------------------------

// sufficient cond: flag1
// necessary cond: flag1 || flag2

void foo3(int* p, int flag1, int flag2)
{
  if(flag1 || (flag2 && rand())) 
    *p = 8;
}

void bar3(void)
{
 
 int* p = 0;
 int flag1, flag2;
 flag1 = flag2 = 0;
 foo3(p, flag1, flag2);
  
}



// --------------------------------------------------

// sufficient cond: flag1 && flag2
// necessary cond: flag1
void foo4(int* p, int flag1, int flag2)
{
  if(flag1 && (flag2 || rand())) 
    *p = 8;
}


void bar4(void)
{
 
 int* p = 0;
 int flag1, flag2;
 flag1 = flag2 = 0;
 foo4(p, flag1, flag2);
  
}

//-------------------------------------------------

// sufficient cond: (flag1 || flag3) && flag2
// necessary cond: (flag1 || flag3)
void foo5(int* p, int flag1, int flag2, int flag3)
{
  if((flag1 || flag3)  && (flag2 || rand())) 
    *p = 8;
}


void bar5(int* q)
{
 
 int* p = 0;
 int flag1, flag2, flag3;
 flag1 = flag2 = 0;
 flag3 = (q!=0);
 foo5(p, flag1, flag2, flag3);
  
}

//  -------------------------------------------------

// sufficient cond: flag2
// Note: A more precise sufficient condition is (flag1 && flag3) || flag2
// but currently we don't look at 2-level conditions if we find a 1-level
// condition for performance. This can be changed it is a problem in practice.
// necessary cond: none
void foo6(int* p, int flag1, int flag2, int flag3)
{
  if((flag1 && flag3)  || (flag2 || rand())) 
    *p = 8;
}


void bar6(int* q)
{
 
 int* p = 0;
 int flag1, flag2, flag3;
 flag1 = flag2 = 0;
 flag3 = (q!=0);
 foo6(p, flag1, flag2, flag3);
  
}
// -------------------------------------------------

// sufficient and necessary: q!=0
void foo7(int* p, int* q)
{
  if(q)
    *p = 8;
}

void bar7(void)
{
  foo7(0, 0);
}

// --------------------------------------------

// necessary & sufficient: q
void foo8(int* p, int q)
{
  if(q) *p=9;
}

void bar9(int size)
{
  int* p =0;
  foo8(p, sizeof(int)*size);
}

void baz9(void)
{
  bar9(0);
}



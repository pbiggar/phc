// Test globals

typedef struct _str { int *a; int *b; } str;

str g;
void init() { g.a = malloc(4); g.b = malloc(4); }

void foo1(int *n)
{
  g.a = n;
}

void foo2(int *n)
{
  *n = g.a;
}

void bar1(int *n)
{
  g.b = n;
  foo2(n);
  foo1(n);
}

void bar2(int *n)
{
  foo2(n);
  foo1(n);
}

int h;

void oddacc(int *b)
{
  int *a = &h;
  if (*a)
    *a = *b;
}

void oddacc_wrap()
{
  oddacc(&h);
}

// deeper entry interaction

int **dg, *dh;
void set() { dg = &dh; }
void set_malloc() { dh = malloc(4); }

void alias1(int *x, int *y) { *x=*y; }
void alias2(int *x, int *y) { *x=*y; }
void usegh(int *val)
{
  *dg = val;
  alias1(*dg,dh);
  alias2(dh,val);
}

int *mg;
void alias3(int *x, int *y) { *x=*y; }
void more1(int *x) { *mg = *x; fiddly(); }
void more2(int *x, int *y) { more1(x); alias3(x,y); }
void more3() { mg = malloc(4); more2(mg,mg); }

int *ng;
void alias4(int *x, int *y) { *x=*y; }
void nest1(int *x) { alias4(x,ng); }
void nest2(int *x, int a) { while (a) { nest1(x); } }
void nest3() { ng = malloc(4); nest2(ng); }

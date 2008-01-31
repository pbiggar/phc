// bitvector/guard revaluation

void foo(int *x, int y, int z)
{
  if (y < z)
    *x = 0;
}

void bar(int *x, int *y, int *z, int m, int n)
{
  foo(x,m,n);
  foo(y,0,1);
  if (m >= 10)
    foo(y,m,10);
}

void baz(int *x, int *y, int m)
{
  foo(x,1,0);
  if (m < 10)
    foo(y,m,10);
}

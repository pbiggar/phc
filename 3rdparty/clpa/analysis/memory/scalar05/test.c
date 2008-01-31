void assert(int x);

void test1(void *p1, long long zed)
{
  short c = (short)p1;
  short d = zed;
  short e = -c;
  int f = c+d;
  short g = d+e;
  short h = f-g;
  assert(h == 0);
  assert(h == 2*c);
}

void test2(void *p1, long long zed)
{
  long long c = -zed;
  int d = (int)p1;
  int e = c;
  int f = d+e;
  assert(f == 0);
}

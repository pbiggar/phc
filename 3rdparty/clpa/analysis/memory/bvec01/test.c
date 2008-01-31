void assert(int x);

#line 100
void stupid()
{
  assert(0);
  assert(1);
  assert(0 == 1);
  assert(1 == 1);
}

#line 200
void foo(int a, int b)
{
  if (a >= b) {
    assert(a >= b);
    assert(a == b);
    assert(a > b);
    assert(a > b + 10);
  }
  if (a == b) {
    assert(a == b);
    assert(a != b);
  }
}

#line 300
void bar(int a, int b)
{
  int x = a ^ b;
  int y = x ^ b;
  assert(a == x);
  assert(a == y);
}

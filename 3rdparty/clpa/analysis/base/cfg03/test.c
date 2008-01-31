// Switch statement splitting

int foo(int n)
{
  int res;
  switch (n) {
  case 1: res = 1; break;
  case 2: res = 2; break;
  case 3: res = 3; break;
  case 4: res = 4; break;
  case 5: res = 5; break;
  case 6: res = 6; break;
  default: res = 0;
  }
  return res;
}

int nondet_foo(int n)
{
  int res;
  switch (n) {
  case 1: res = 1; break;
  case 2: res = 2; break;
  case 3: res = 3; break;
  case 4: res = 4; break;
  case 5: res = 5; break;
  case 6: res = 6; break;
  default: res = 0;
  }
  return res;
}

int nodefault(int n)
{
  switch (n) {
  case 0: return 0;
  case 1: return 1;
  }
  return n - 1;
}

// test handling of static variables and functions

void static_var1(int **a, int *b)
{
  static int *stc = 0;
  *a = stc;
  stc = b;
}

void static_var2(int **a, int *b)
{
  static int *stc = 0;
  *a = stc;
  stc = b;
}

void call_var(int **a, int **b)
{
  static_var1(a,*b);
  static_var2(b,*a);
}

void call_call_var()
{
  int *a = malloc(4);
  int *b = malloc(4);
  call_var(&a,&b);
}

static int** static_fn(int ***a)
{
  return *a;
}

int** call_static1(int ***a)
{
  return static_fn(a);
}

int* inter_var1()
{
  static int *stc2 = 0;
  if (stc2 == 0)
    stc2 = malloc(4);
  return stc2;
}

int* inter(int b)
{
  if (b) return inter_var1();
  else return inter_var2();
}

static int* static_fn(int ***a)
{
  return **a;
}

int* call_static2(int ***a)
{
  return static_fn(a);
}

int* inter_var2()
{
  static int *stc2 = 0;
  if (stc2 == 0)
    stc2 = malloc(4);
  return stc2;
}

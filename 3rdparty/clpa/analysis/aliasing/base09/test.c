// test call site handling of trace unification

int* foo(int **ptr)
{
  *ptr = malloc(10);
  return *ptr;
}

int* wrap_foo(int **ptr)
{
  *ptr = 0;
  return foo(ptr);
}

int* wrap_wrap_foo(int **ptr)
{
  *ptr = 0;
  return wrap_foo(ptr);
}

int** other_foo(int ***ptr)
{
  *ptr = malloc(10);
  return *ptr;
}

void deeper(int ***ptr,int *val)
{
  *ptr = 0;
  other_foo(ptr);
  **ptr = val;
}

void other_deeper(int ***ptr, int *val)
{
  int **tmp;
  other_foo(&tmp);
  *ptr = tmp;
  **ptr = val;
}

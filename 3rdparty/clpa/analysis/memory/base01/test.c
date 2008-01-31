// Basic pointer stuff

void swap(int *x, int *y)
{
  int a = *x;
  *x = *y;
  *y = a;
}

void store(int **x, int a)
{
  **x = a;
}

void maybe(int x, int *a, int *b, int **m, int test)
{
  if (test)
    *m = a;
  else
    *m = b;
  **m = x;
}

void maybeswap(int *x, int *y, int test)
{
  int a;
  if (test) {
    a = *x;
    *x = *y;
    *y = a;
  }
}

int g;
void addrtaken(int **x, int *y)
{
  *x = &g;
  **x = *y;
}

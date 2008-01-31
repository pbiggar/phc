// Test malloc and return values

void* malloc(int);

void complex(void ***x, void ***y)
{
  void *tmp = **y;
  *x = malloc(4);
  **x = tmp;
  *y = malloc(4);
  **y = malloc(4);
}

void foo(void **a, void **b)
{
  *a = malloc(4);
  *b = *a;
}

void bar(void **a, void **b)
{
  *b = *a;
}

void* baz(void **a)
{
  return *a;
}

void* baz_wrap1(void **a)
{
  return baz(a);
}

void* baz_wrap2(void **a, int b)
{
  if (b)
    return baz(a);
  else
    return malloc(4);
}

// Don't copy integer values

int* intcpy(int *a, int *b)
{
  *a = *b;
  b = a;
  return a;
}

void intcpy_wrap(int *a, int *b, int **c)
{
  *c = intcpy(a, b);
}

// Offsets within a structure

typedef struct _str { int *a; int b; } str;

int* offset(str *s)
{
  return &(s->b);
}

int* offset_wrap(str *s)
{
  return offset(s);
}

// Mallocs through offsets of a structure

void multiple_one(str ***parent, int **parentb)
{
  str* tmp = malloc(sizeof(str));
  **parent = tmp;
  *parentb = &tmp->b;
}

void multiple_two(int ***parenta, int **parentb)
{
  str* tmp = malloc(sizeof(str));
  *parenta = &tmp->a;
  *parentb = &tmp->b;
}

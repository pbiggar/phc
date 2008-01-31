// test alias analysis treatment of static initializers

int *f;
int **g = &f;

void init()
{
  f = malloc(4);
}

void foo(int *myf)
{
  *f = *myf;
}

void bar()
{
  foo(*g);
}

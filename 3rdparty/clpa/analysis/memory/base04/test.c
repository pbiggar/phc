// test guard disjointness

void basic(int a, int b)
{
  a = b;
}

void loop_test(int a, int b)
{
  while (b++) { if (b == 10) goto L; if (b == 20) goto L2; }
  a = 0;
 L: a++;
 L2: a++;
}

void use_alias(int **a, int **b)
{
  *b = *a;
}

void make_alias()
{
  int *x; use_alias(&x,&x);
}

void use_side_effect(int **a, int **b)
{
  use_alias(a,b);
}

// TODO: fixme
void arrays()
{
  int buf[10];
  buf[0] = 0;
  buf[1] = 1;
}

void fresh(int **x)
{
  *x = malloc(4);
}

// TODO: fixme
void call_fresh()
{
  int *x = 0;
  fresh(&x);
}

// Test loops

void basic(char **a, char **b, int c)
{
  while (c) {
    *a = *b;
  }
}

void basic2(char **a, char **b, int c)
{
  while (c) {
    // coerce aliased accesses this time
    **a = **b;
    *a = *b;
  }
}

void inter(char **a, char **b, char *c, int d)
{
  while (d) {
    a = b;
  }
  *a = c;
}

void multi(char **a, char **b, char *c, int d)
{
  while (d) {
    a = b;
  }
  while (d) {
    *a = *b;
  }
}

// Loop alias propagation

void whata(int*x,int*y) { *x = *y; }
void whatb(int*x,int*y) { *x = *y; }

void down(int *x, int b)
{
  int *t = x;
  whata(t,x);
  while (b) {
    whatb(t,x);
  }
}

void temporary(int *x, int b)
{
  while (b) {
    int *tmp = x;
    tmp++;
  }
}

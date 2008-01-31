// Structures etc.

struct foo {
  int f;
  int g;
};

void copy(struct foo *a, struct foo *b)
{
  b->f = a->f;
  b->g = a->g;
}

int* malloc(int);

void fresh(int **a, int **b)
{
  *a = malloc(4);
  *b = *a;
}

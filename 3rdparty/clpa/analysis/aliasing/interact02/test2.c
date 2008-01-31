# 1 "test.h"

typedef struct {
  int *ptr;
} anonymous;

typedef union {
  int *a;
  int b;
} anonu;

struct cross;

int* use_1(struct cross *c);
int* use_2(struct cross *c);

# 1 "test2.c"

int g2;
void fill_2(anonymous *a)
{
  g2 = 0;
  a->ptr = &g2;
}

int g6;
void fill_6(anonu *a)
{
  g6 = 0;
  a->a = &g6;
}

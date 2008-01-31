// test anonymous structs/unions and multiple structs with same name

# 1 "test_other.h"

// I'm a comment. I'm here to fill up space and make line numbers not align
typedef struct {
  struct {
    int *argh;
  } anonymous;
} anonymous_other;

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

# 1 "test1.c"

int g1;
void fill_1(anonymous *a)
{
  g1 = 0;
  a->ptr = &g1;
}

int g3;
void fill_3(anonymous_other *a)
{
  g3 = 0;
  a->anonymous.argh = &g3;
}

int g4;
void fill_4()
{
  g4 = 0;
  struct {
  } anonymous;
}

int g5;
void fill_5(anonu *a)
{
  g5 = 0;
  a->a = &g5;
}

enum {
  A, B
} myenum;

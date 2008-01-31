// structure assignments, passed on stack and through return value

int *g;
typedef struct str {
  int **a;
  int *b;
} str;

void init() { g = malloc(4); }

void assign(str s, int *na)
{
  *(s.a) = na;
}

void stack_struct(int **a, int *na)
{
  str s = { a, 0 };
  assign(s,na);
}

void stack_indir(str a, int *na)
{
  str b = a;
  assign(b,na);
}

void more_assign(str *s0, str s1)
{
  *s0 = s1;
}

void stack_effect(str a, int *na)
{
  str b;
  more_assign(&b,a);
  assign(b,na);
}

void more_effect(str *s0)
{
  str s1;
  s1.b = g;
  more_assign(s0,s1);
}

void flatcopy(void *v0, void *v1)
{
  *v0 = *v1;
}

void more_flatcopy(str *s0, str *s1)
{
  flatcopy(s0,s1);
}

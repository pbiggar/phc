// Test aliasing detection.

typedef struct _str {int *a; int *b;} str;

void with_body(int*a,int*b) { *a = *b; }
void call_with_body(int *x)
{
  with_body(x,x);
}

void without_body(int*,int*);
void call_without_body(int *x)
{
  without_body(x,x);
}

void same_field(str *s0, str *s1)
{
  s0->a = 0;
  s1->a = 0;
}
void call_same_field(str *s)
{
  same_field(s,s);
}

void diff_field(str *s0, str *s1)
{
  s0->a = 0;
  s1->b = 0;
}
void call_diff_field(str *s)
{
  diff_field(s,s);
}

int *g, *og;
void init() { g = malloc(4); }
void glob(int *x)
{
  *g = 0;
  *x = 0;
  g = og;
}
void wrap_glob(int *x)
{
  glob(x);
}
void call_glob()
{
  wrap_glob(g);
}

void getused();
void (*usefn)();
void fill_fn()
{
  usefn = getused;
}

typedef struct _internal {int *myptr;} internal;

internal* make_internal(int n)
{
  internal *i = malloc(sizeof(internal) + n);
  i->myptr = ((char*)i) + n*sizeof(int);
  return i;
}

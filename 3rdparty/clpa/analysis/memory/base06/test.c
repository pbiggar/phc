// memory analysis result cacheing

struct str {
  struct {
    struct {
      int **h;
    } g;
  } f;
};

void escape_call(struct str *s) { **(s->f.g.h) = 0; }
void escape_fn(int *escape)
{
  int **x = &escape;
  struct str s;
  s.f.g.h = x;
  escape_call(&s);
}

void sideeffect_call(int*v) { *v = 0; }
void sideeffect_fn(int b)
{
  int la, lb;
  int *x = 0;
  if (b) x = &la;
  else x = &lb;
  sideeffect_call(x);
}

void multi_call(int*x,int**y) { *x = 0; **y = 0; }
void multi_fn()
{
  int local;
  int *x = &local;
  int **y = &x;
  multi_call(x,y);
}

void castint_call(int u) { *((int*)u) = 0; }
void castint_fn(int u)
{
  castint_call(u);
}

void cast2_call(int *x) { *x = 0; }
void cast2_fn(int *x) { cast2_call(x); }

void cast3_call(int *v) { *v = 0; }
void cast3_fn(unsigned int x) { int *y = (int*)x; cast3_call(y); }

void uninit_call(int **x) { **x = 0; }
void uninit_fn()
{
  int* p;
  uninit_call(&p);
  int a = *p;
}

struct foo {
  int *x;
};

void struct_call(struct foo *f) { if (*(f->x)) f->x = 0; }
void struct_fn(struct foo *f)
{
  struct foo local = *f;
  struct_call(&local);
}
void xstruct_fn(struct foo *f)
{
  struct foo local = *f;
  local.x = 0;
  struct_call(&local);
}

void inter_call1(int **x, int **y) { *x = *y; }
void inter_call2(int **x, int **y) { **x = 0; **y = 0; }
void inter_fn(int **x, int **y)
{
  inter_call1(x,y);
  inter_call2(x,y);
}

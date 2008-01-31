// Test global and type invariants

int h;
int h_nomod;
int *g;

typedef struct _str {
  int *a;
  int *b;
} str;

typedef struct _str3 {int *a; int *b;} str3;

int *p;
int *q;

int *p4;
typedef struct _str4 {int **pp;} str4;

int *p5;
typedef struct _str5 {int *ap;} str5;

typedef struct _fake_str3 {} fake_str3;
typedef struct _ofake_str3 {int a;} ofake_str3;

int *p6;
typedef struct _str6 {int *ap;} str6;

int *p7, **p7a, **p7b;
typedef struct _str7 {int **ap; int **bp;} str7;

void init()
{
  g = malloc(4);
  p = malloc(4);
  q = malloc(4);
  p4 = malloc(4);
  p5 = malloc(4);
  p6 = malloc(4);
  p7 = malloc(4);
}

// basic invariants

void set_default(int b)
{
  h = 0;
  if (b)
    g = &h;
  else
    g = &h_nomod;
}

void foo(str *x)
{
  x->a = x->b;
}

// cross-global propagation

void pqargs(int*x,int*y) { *x=*y; }
void get() { pqargs(p,q); }
void set() { p = q; }

// cross-struct propagation

void twoargs3(int*x,int*y) { *x=*y; }
void str3a(void *v) { str3 *s = v; twoargs3(s->a, s->b); }
void str3b(str3 *s) { s->a = s->b; }

// cross-struct/glob propagation

void twoargs4(int*x,int*y) { *x=*y; }
void str4a(str4 *s) { s->pp = &p4; }
void str4b(str4 *s) { twoargs4(*s->pp,p4); }

void twoargs5(int*x,int*y) { *x=*y; }
void str5a(str5 *s) { s->ap = p5; }
void str5b(str5 *s) { twoargs5(s->ap,p5); }

void twoargs6(int*x,int*y) { *x=*y; }
void useptr6(int**x,int*y) { **x = *y; }
void usestr6(int*x,str6*s) { *(s->ap) = *x; }
void useglob6(int*a) { *p6 = *a; }
void str6a(str6 *s) { s->ap = p6; }
void str6b(str6 *s0,str6 *s1) { twoargs6(s0->ap,s1->ap); }
void str6c(str6 *s0,str6 *s1) { useptr6(&s0->ap,s1->ap); }
void str6d(str6 *s0,str6 *s1) { usestr6(s0->ap,s1); }
void str6e(str6 *s) { useglob6(s->ap); }

void twoargs7(int**x,int**y) { **x = **y; }
void str7a() { p7a = &p7; p7b = &p7; }
void str7b(str7 *s) { s->ap = p7a; s->bp = p7b; }
void str7c(str7 *s) { twoargs7(s->ap,s->bp); }

// screwy casts

//// casting.clp should handle this cast
//void fake(fake_str3 *fs)
//{
//  str3 *s = (str3*)(ofake_str3*)fs;
//  s->a = s->b;
//}

void more(void **fs)
{
  *fs = (str3*)*fs;
}

typedef struct _cstr3 { str3 s; int a; } cstr3;
typedef struct _ccstr3 { cstr3 cs; int b; } ccstr3;
cstr3* upcast1(ccstr3 *ccs) { return (cstr3*)ccs; }
str3* upcast2(ccstr3 *ccs) { return (str3*)ccs; }
ccstr3* updowncast(ccstr3 *ccs)
{
  ccstr3 *s = (ccstr3*)upcast2(ccs);
  return s;
}

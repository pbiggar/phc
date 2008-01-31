// Test aliasing detection.

typedef struct _str1 {int *a; int *b; int c; int d;} str1;
typedef struct _str2 {int *a; int *b; int c; int d;} str2;

void alias1_1(int*x,int*y) { *x=*y; }

void simple1(int *x)
{
  alias1_1(x,x);
}

void alias2_1(int*x,int*y) { *x=*y; }
void alias2_2(int*x,int*y) { *x=*y; }
void alias2_3(int*x,int*y) { *x=*y; }

void simple2(str1 *s)
{
  alias2_1(s->a, s->a);
  alias2_2(s->b, s->b);
  alias2_3(s->a, s->b);
}

void alias3_1(int*x,int*y) { *x=*y; }
void alias3_2(int*x,int*y) { *x=*y; }
void alias3_3(int*x,int*y) { *x=*y; }

void simple3()
{
  int a, b;
  alias3_1(&a, &a);
  alias3_2(&b, &b);
  alias3_3(&a, &b);
}

void alias4_1(int*x,int*y) { *x=*y; }
void alias4_2(int*x,int*y) { *x=*y; }
void alias4_3(int*x,int*y) { *x=*y; }

void simple4(str2 *s)
{
  alias4_1(&(s->c), &(s->c));
  alias4_2(&(s->d), &(s->d));
  alias4_3(&(s->c), &(s->d));
}

void alias5(int**x,int**y) { **x=**y; }

void deeper_call(int *a)
{
  int *x = a, *y = a;
  alias5(&x,&y);
}

void alias_str(str2 *s) { s->a=s->b; }
void deeper_str(str2 *s)
{
  s->a = s->b;
  simple4(s);
  alias_str(s);
}

// from openssh/channels.c

typedef struct _Channel {
  int self;
} Channel;

Channel **channels;
int channels_alloc;

void channel_new()
{
  channels = malloc(4);
  channels[0] = malloc(4);
}

void channel_free(Channel *c)
{
  channels[c->self] = 0;
}

void channel_free_all()
{
  int i;
  for (i = 0; i < channels_alloc; i++)
    if (channels[i] != 0)
      channel_free(channels[i]);
}

// paths

void cswappya(int *x, int *y) { *x=*y; }
void cswappyb(int *x, int *y) { *x=*y; }

void swappy(int *x, int *y, int b)
{
  int *t;
  if (b) {
    t = x;
    x = y;
    y = t;
  }
  cswappya(x,y); // we currently detect x and y as not aliased
  cswappyb(t,y);
}

// top-down propagation

void calla(int *x, int *y) { *x=*y; }
void callb(int *x, int *y) { calla(x,y); }
void callc(int *x) { callb(x,x); }

// deeper modifications

int **g;
void deepset() { g = malloc(4); *g = malloc(4); }

void deepa(int *x, int *y) { *x=*y; }
void deepb(int **v, int *val)
{
  *v = val;
  deepa(*g,*v);
}
void deepc(int *val)
{
  deepb(g,val);
}

// types

void mixed_alias(int *x,void *y) { *x = *((int*)y); }
void call_mixed(int *x)
{
  mixed_alias(x,(void*)x);
}

// fubar

str1 globstr;
void twoargs_fubar(str1 *s) { if (!(globstr.a+1)) globstr = *s; }
void fubar_set() { globstr.a = malloc(); globstr.b = malloc(); }
void fubar_call() { globstr.a++; globstr.b++; twoargs_fubar(&globstr); }

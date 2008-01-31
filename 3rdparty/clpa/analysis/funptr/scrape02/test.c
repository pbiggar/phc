// assignment scraping

void fn();

struct str {
  void (*fld)();
  void (*fld2)();
  void (*fld3)();
};

struct bigger {
  struct str s[10];
};

void foo(struct str *s)
{
  s->fld = fn;
}

void bar()
{
  struct bigger b;
  b.s[0].fld2 = fn;
}

void baz(struct str *s1, struct str *s2)
{
  s1->fld3 = s2->fld;
}

void callme(struct bigger b)
{
  b.s[0].fld();
  struct str s;
  s.fld2();
  s.fld3();
}

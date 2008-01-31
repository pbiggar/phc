// test trace types

struct list_head {
  struct list_head *next, *prev;
};

typedef struct cntr {
  struct list_head member;
  int *etc;
} cntr;

typedef struct bigger {
  void *fld;
} bigger;

void explicit(struct list_head *head, int *val)
{
  cntr *c = (cntr*)head;
  c->etc = val;
}

void call_explicit(struct list_head *head, int *val)
{
  explicit(head,val);
}

void implicit(bigger *b, int *val)
{
  struct list_head *p = malloc(sizeof(cntr));
  explicit(p,val);
  b->fld = p;
}

void call_implicit(bigger *b, int *val)
{
  implicit(b,val);
}

void addtl(bigger *b, int *val)
{
  cntr *c = malloc(sizeof(cntr));
  c->etc = val;
  b->fld = c;
}

void call_addtl(bigger *b, int *val)
{
  addtl(b,val);
}

// Test handling of recursive and unbounded structures

typedef struct _list {
  int *data;
  struct _list *next;
} list;

void* malloc(int);

void extend(list *l)
{
  l->next = malloc(sizeof(list));
  l->next->data = 0;
}

void append(list *l0, list *l1) {
  list *end = l0;
  while (end->next) {
    end = end->next;
  }
  end->next = l1;
}

void update_all(list *l, int *a) {
  (*(l->next->data))++;
  l->next->data = a;
  update_all(l->next, a);
}

void wrap_update(list *l, int *a) {
  update_all(l,a);
  *(l->next->next->data) = 0; // need to handle softness here
}

typedef struct _dns_rr {
  int *rdata;
  char *name;
  struct _dns_rr *next;
} dns_rr;

void free(void*);

void free_dns_rr(dns_rr *p)
{
  if (p == 0)
    return;
  
  if (p->name)
    free(p->name);
  if (p->rdata)
    free(p->rdata);

  free_dns_rr(p->next);
  free(p);
}

dns_rr *base;
void register_dns_rr(dns_rr *regp)
{
  dns_rr *r, **rp;
  for (rp = &base; (r = *rp) != 0; rp = &r->next);

  regp->next = 0;
  *rp = regp;
}

// untyped self-referencing pointers
void parsePGArray(int b)
{
  int curitem = 0;
  char **items = malloc(10);
  char *strings = (char*) (items + b);
  while (b) {
    items[curitem] = strings;
    curitem++;
    strings++;
  }
}

struct weird {
  int a;
  int b;
  int next[];
};

// untyped advancing pointers
void weirdAdvance(struct weird *w)
{
  while (1) {
    w->a = w->b;
    w = (struct weird*)(&w->next);
  }
}

void weirdReverse(struct weird *w)
{
  while (1) {
    w->a = w->b;
    w = (struct weird*)((char*)w - __builtin_offsetof(struct weird,next));
  }
}

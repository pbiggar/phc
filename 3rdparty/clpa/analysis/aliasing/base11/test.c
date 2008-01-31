// test handling of linux list_* macros and container_of

struct list_head {
  struct list_head *next, *prev;
};

typedef struct cntr {
  struct list_head member;
  int *etc;
} cntr;

cntr* simple(struct list_head *head)
{
  cntr *par = ({ struct list_head *__mptr = head->next;
                 (cntr*)((char*)__mptr - __builtin_offsetof(cntr,member));});
  return par;
}

void iterate(struct list_head *head, int *val)
{
  cntr *pos, *n;
  for (pos = ({ struct list_head *__mptr = head->next;
                (cntr*)((char*)__mptr - __builtin_offsetof(cntr,member));}),
         n = ({ struct list_head *__mptr = pos->member.next;
                (cntr*)((char*)__mptr - __builtin_offsetof(cntr,member));});
       &pos->member != head;
       pos = n,
         n = ({ struct list_head *__mptr = n->member.next;
                (cntr*)((char*)__mptr - __builtin_offsetof(cntr,member));}))
  {
    pos->etc = val;
  }
}

void allocate(struct list_head *head, int *val)
{
  cntr *item = malloc(sizeof(cntr));
  item->etc = val;
  head->next = &item->member;
}

struct list_head glob1;
struct list_head glob2;

typedef struct contain_cntr {
  cntr *c;
} contain_cntr;

void set_glob2()
{
  glob2.next = malloc(4);
}

void set_glob1()
{
  glob1.prev = glob2.next;
  glob1.next = glob2.prev;
}

void fill_glob(contain_cntr *cntr, int b)
{
  if (b)
    cntr->c = simple(glob1.next);
  else
    cntr->c = simple(glob2.next);
}

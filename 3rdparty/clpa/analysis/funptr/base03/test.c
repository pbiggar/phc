// lists of pointers

struct funptr_list {
  struct funptr_list *next, *prev;
  void (*func)(int);
};

void foo(int);
struct funptr_list foo_item = {
  .func = foo
};

void bar(int);
struct funptr_list bar_item = {
  .func = bar
};

struct funptr_list funptrs;

void initialize()
{
  funptrs.next->next = &bar_item;
  funptrs.next = &foo_item;
}

void use()
{
  struct funptr_list *cur = &funptrs;
  while (cur) {
    cur->func(0);
    cur = cur->next;
  }
}

void wrap1(void (*func)(int),int n)
{
  (*func)(n);
}

void wrap2(struct funptr_list *list)
{
  wrap1(list->func);
}

void use_wrap()
{
  struct funptr_list *cur = &funptrs;
  while (cur) {
    wrap2(cur);
    cur = cur->next;
  }
}

struct funptr_list* get()
{
  return &funptrs;
}

void use2()
{
  get()->func(0);
}

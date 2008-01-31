typedef int spinlock;

void lock(spinlock *);
void unlock(spinlock *a);

void foo(spinlock *a)
{
  spinlock *b;
  b = a;
  lock(a);
  unlock(b);
}

void bar(spinlock *a, spinlock *b, char test)
{
  spinlock *c = a;
  if (test)
    c = b;
  lock(c);
  unlock(c);
}

void baz(spinlock *a, spinlock *b, int test0, int test1)
{
  spinlock *c = a;
  if (test0)
    c = b;
  lock(c);
  if (test1)
    c = a;
  unlock(c);
}

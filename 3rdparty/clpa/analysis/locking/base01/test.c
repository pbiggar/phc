typedef int spinlock;

void lock(spinlock *);
void unlock(spinlock *a);

void baz(spinlock *a)
{
  lock(a);
}

void foo(spinlock *a)
{
  lock(a);
  unlock(a);
}

void bar(spinlock *a, int b)
{
  if (__builtin_expect(b,0))
    lock(a);
  if (__builtin_expect(!!(b),0))
    unlock(a);
}

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
  if (b)
    lock(a);
  if (b)
    unlock(a);
}

int g;
  
int sip(spinlock *a) {
  if (g) {
    lock(a);
    return 1;
  } else {
    return 0;
  }
}
    
void sap(spinlock *a)
{
  int i;
  i = sip(a);
  if (i) {
    unlock(a);
  }
}

void wrong(spinlock *a, int b)
{
  while (b) {
    lock(a);
  }
}

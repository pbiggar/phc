typedef int spinlock;

void lock(spinlock*);
void unlock(spinlock*);
int trylock(spinlock*); // true indicates success

int trylock_wrap(spinlock *a)
{
  return trylock(a);
}

int maybe_lock(spinlock *a, int b)
{
  if (b) {
    lock(a);
    return 1;
  }
  return 0;
}

int forgot(spinlock *a, int b, int c)
{
  lock(a);
  if (b) {
    unlock(a);
    return 1;
  }
  if (c) {
    return -1;
  }
  unlock(a);
  return 0;
}

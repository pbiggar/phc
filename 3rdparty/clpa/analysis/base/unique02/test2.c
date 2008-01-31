typedef struct overlap {
  int these_are_not_the_same_structures;
  int x; int y;
} overlap;

extern void reader(overlap *l);
void writer(overlap *l)
{
  l->x = 0;
  l->y = 1;
}

void main2(overlap *l)
{
  writer(l);
  reader(l);
}

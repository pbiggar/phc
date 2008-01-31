typedef struct overlap {
  int x; int y;
} overlap;

extern void writer(overlap *l);
void reader(overlap *l)
{
  int a = l->x + l->y;
}

void main1(overlap *l)
{
  writer(l);
  reader(l);
}

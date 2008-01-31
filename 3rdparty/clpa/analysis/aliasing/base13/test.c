// Canonical naming of global locations

void* malloc(int);

int g1, *pg1, **ppg1;
void address1_seta() { ppg1 = &pg1; }
void address1_setb() { *ppg1 = &g1; }
void address1_main()
{
  address1_seta();
  address1_setb();
  g1 = 0;
}

int g2, **ppg2;
void malloc2_seta() { ppg2 = malloc(4); }
void malloc2_setb() { *ppg2 = &g2; }
void malloc2_main()
{
  malloc2_seta();
  malloc2_setb();
  g2 = 0;
}

int *pg3;
void twoargs3(int*x,int*y) { *x=*y; }
void local_seta(int *a) { pg3 = a; }
void local_main()
{
  int a;
  local_seta(&a);
  twoargs3(&a,pg3);
}

int g4, **ppg4;
void twoargs4(int*x,int*y) { *x=*y; }
void missing_set() { *ppg4 = &g4; }
void missing() { twoargs4(*ppg4,&g4); }

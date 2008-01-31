// More complex global invariants following global aliasing transitively

void* malloc(int);

int *p1, **pp1;
typedef struct _str1a {int **pp;} str1a;
typedef struct _str1b {int *p;} str1b;
void twoargs1(int*x,int*y) { *x=*y; }
void str1_seta() { pp1 = &p1; }
void str1_setb(str1a *sa,str1b *sb) { sa->pp = pp1; sb->p = p1; }
void str1_use(str1a *sa,str1b *sb) { twoargs1(*sa->pp,sb->p); }
void str1_main(str1a *sa,str1b *sb)
{
  p1 = malloc(4);
  str1_seta();
  str1_setb(sa,sb);
  str1_use(sa,sb);
}

int g2, *pg2, **ppg2;
void twoargs2a(int*x,int*y) { *x=*y; }
void twoargs2b(int*x,int*y) { *x=*y; }
void twoargs2c(int*x,int*y) { *x=*y; }
void use2_seta() { *ppg2 = &g2; }
void use2_setb() { ppg2 = &pg2; }
void use2_main()
{
  use2_setb();
  use2_seta();
  twoargs2a(&g2,pg2);
  twoargs2b(&g2,*ppg2);
  twoargs2c(pg2,*ppg2);
}

typedef struct _str3 {int *pg;} str3;
int g3, **ppg3a, **ppg3b;
str3 gstr;
void twoargs3a(int*x,int*y) { *x=*y; }
void twoargs3b(int*x,int*y) { *x=*y; }
void str3_seta(str3 *s) { s->pg = &g3; }
void str3_setb(str3 *s) { ppg3a = &s->pg; }
void str3_setc() { ppg3b = &gstr.pg; }
void str3_main(str3 *s)
{
  str3_seta(&gstr);
  str3_setb(s);
  str3_setc();
  twoargs3a(&g3,*ppg3a);
  twoargs3b(&g3,*ppg3b);
}

int g4, *pg4, **ppg4, ***pppg4;
void twoargs4(int*x,int*y) { *x=*y; }
void chain4_seta() { pg4 = &g4; }
void chain4_setb() { ppg4 = &pg4; }
void chain4_setc() { pppg4 = &ppg4; }
void chain4_main()
{
  chain4_seta();
  chain4_setb();
  chain4_setc();
  twoargs4(&g4,**pppg4);
}

// note: this is currently broken
int g5, *pg5a, *pg5b, **ppg5a, **ppg5b, ***pppg5a, ***pppg5b;
void deeperargs5(int***,int***);
void deep5_seta() { pg5a = pg5b = &g5; }
void deep5_setb() { ppg5a = &pg5a; ppg5b = &pg5b; }
void deep5_setc() { pppg5a = &ppg5a; pppg5b = &ppg5b; }
void deep5_main()
{
  deep5_seta();
  deep5_setb();
  deeperargs5(pppg5a,pppg5b);
  *pg5a = 0;
}

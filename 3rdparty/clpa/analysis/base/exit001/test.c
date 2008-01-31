// exit function regressions

int g = 4;

int foo( int i )
{
  if( i )
  {
    exit(2);
  }
  else
  {
    longjmp();
  }
  return i * 2;
}

void init( int * p )
{
   *p = 0;
   abort();
}

int uninit(int c)
{
  int x ;
  int y ;
  int z;
  int *p_int; //
  int a[2];

  x = z;
 
  while( c ){ 
    if(z)
      init( &y );
  }
  foo(x);
  x = y;
  return 0;
}

static int bar()
{
  init(1);
  return 3;

}

void infinite(int x, int y)
{
  while (1) {
    x++;
    y--;
  }
}

void breakout(int x, int y, int z)
{
  while (1) {
    x++;
    if (z)
      break;
    y--;
  }
}

void breakout_bar(int x,
                  int y,
                  int z)
{
  while (1) {
    x++;
    if (z)
      break;
    y--;
  }
  bar();
  x++;
}

/*struct XFILE
{
  int flag;
  int open_flags;
  int bufused;
  char* buf;
  int* flags;
  int fd;
  
};

int errno;
int dbf;

int x_fflush(struct XFILE *f)
{
	int ret;

	if (f->flags) return -1;

	if ((f->open_flags) != -1) {
		errno = 0;
		return -1;
	}

	if (f->bufused == 0 || !f->buf) return 0;

	ret = write(f->fd, f->buf, f->bufused);
	if (ret == -1) return -1;
	
	f->bufused -= ret;
	if (f->bufused > 0) {
		memmove(f->buf, ret + (char *)f->buf, f->bufused);
		return -1;
	}

	return 0;
}

void dbgflush( void )
{
	bufr_print();
	if(dbf)
		(void)x_fflush( dbf );
}


int foo(int a)
{
  if(a == 9)
    return 1;

  return 0;
}

void bar(int a)
{
  int b;
  int ret = foo(a);
  if(ret > 0)
    b=a;
    
}

struct textint 
{
  int value;
  int digits;
};

static int
to_year (struct textint textyear)
{
  int year = textyear.value;

  if (year < 0)
    year = -year;

  if (textyear.digits == 2)
    year += year < 69 ? 2000 : 1900;

  return year;
}

void test_year(struct textint year)
{
  int newyear = to_year(year);
  if(newyear-1900 <= 70)
  //if(newyear == 2000)
    printf("Hello world");

}

*/

void foo (int* a, int flag)
{
  if(flag) *a = 8;
}


void bar(int * b, int c)
{
  *b = 3;
  foo(b,c);
}


void bar2(int * b, int c)
{
  *b = 3;
  bar2(b,c);
}

// Regressions for testing summary generation and application 
// of the correlation analysis.
// The summary encodes the correlation between the return value 
// of a function and its arguments.



int foo1(int flag, int flag2)
{
  if(flag || flag2) return 0;
  else return -1;
}

// necessary: flag1 || flag2 || flag3
// sufficient: flag1 || flag2 || flag3
void bar1(int* p, int flag1, int flag2, int flag3)
{
  if(foo1(flag1, flag3)>=0 || flag2)
    *p = 8;
}

void baz1(void)
{
  int*p = 0;
  int flag1, flag2, flag3;
  flag1 = flag2 = flag3 = 0;
  bar1(p, flag1, flag2, flag3);
}


//----------------------------------------


int foo2(int* p)
{
  if(p==0) return -1;
  return 0;
}

// necessary & sufficient: p!=0
void bar2(int* p, int flag1, int flag2)
{
  if(foo2(p)>=0)
    *p = 8;
}

void baz2(void)
{
  int*p = 0;
  int flag1, flag2;
  flag1 = flag2 = 0;
  bar2(p, flag1, flag2);
}

// ----------------------------------------

int foo3(int* p)
{
  if(p==0) return 0;
  return 1;
}


// necessary & sufficient: p!=0
void bar3(int* p)
{
  if(foo3(p)==1) *p=8;
}

void baz3(int* p)
{
  p =0;
  bar3(p);
}


//---------------------------------------------

// necessary & sufficient(arg1) = ret==0
// necessary & sufficient(arg0) = ret!= 0 
unsigned long
foo4(void *to, const void *from, unsigned long n)
{
        unsigned long flag;
	int a;
	//	  asm("": "=&r" flag);
        if (flag == 0) {
	  a=*(int*)from;
	  return 0;
	}
        else   
	{
	  a=*(int*)to;
	   return 1;
	}
 }


void bar4 (int *u, int cmd) {      
        int buf[100];
        if (foo4(buf, u, 0))
                return;       
        *u = 0;
} 


// ------------------------------------


int fun1(int c)
{
  if(c>3) return 0;
  return 1;
}

// necessary & sufficient: arg1 > 3
void foo5( int (*fn)(int), int a)
{
  int* ptr;
  int res = fn(a);
  if(res == 0) 
    *ptr = 6;
}


void bar5(int a, int b)
{
  foo5(fun1, a);
}


void baz5()
{
 bar5(1,1);
}


//---------------------------------------------


unsigned long
foo6(void *to, const void *from, unsigned long flag)
{
     
        if (flag == 0) {
	  return 0;
	}
        else   
	{
	   return 1;
	}
 }

// necessary & sufficient(arg0) = True
void bar6 (int *u, int cmd) {      
        int buf[100];
        if (foo6(buf, u, 0))
                return;       
        *u = 0;
} 


// necessary & sufficient(arg0) = False
void baz6 (int *u, int cmd) {      
        int buf[100];
        if (foo6(buf, u, 1))
                return;       
        *u = 0;
} 

//---------------------------------------

// Necessary cond(p) = retval >= 0
// Sufficient cond(p) = retval>=0
int foo7(int *u, int cmd) {
    int err = -1, flag;
    int* p;
    flag = random1();
    if (flag != 0)
        goto out;


       
    err = random2();
    if (err < 0)
        goto out;


    if(flag == 0)
      *p=0;


out:
    return err;
}

void bar7(int *u, int cmd) {
   
    int retval = foo7(u, cmd);
   int a;
    if (retval <  0) {a=1; }
    else
        *u=0;   
}

//------------------------

//NC:True
//SC: retval>=0
int foo8(int *u, int cmd) {
        int err = -1;
        int flag;

        flag = random1();
        if (flag != 0) {
                goto out;
        }
	if(flag==0)
	 *u=9;

        err = random2();
        if (err < 0) {
                goto out;
        }



out:
        return err;

}

void bar8(int *u, int cmd) {

        int retval = foo8(u, cmd);

        if (retval >=  0)
	  deref(u);

}
//----------------------

//NC: true
//SC: ret(foo9) >= 0) & cmd >10 
int foo9(int *u, int cmd) {
       int err = -1;
       int flag;

       if (cmd > 10) {
               flag = random1();
	     
               if (flag != 0) {
                       goto out;
               }
       }

         if(flag==0)
		 *u=9;

       err = random2();
       if (err < 0) {
               goto out;
       }
   

out:
       return err;

}

void bar9(int *u, int cmd) {

       int retval = foo9(u, cmd);

       if (retval >=  0)
               if (cmd > 10)
                       deref(u);
}

//-------------------------------

struct msghdr {
        unsigned char *control;
        int controllen;
};

// NC & SC: msg->controllen >=5
void foo10(struct msghdr *msg) {
        if (msg->controllen >= 5) {
                *msg->control = 0;
        }
}

void bar10(struct msghdr *msg) {
        struct msghdr msg_sys;
        unsigned char ctl_buf[100];
	int* a;

        msg_sys = *msg;
        if (msg_sys.controllen) {
                msg_sys.control = ctl_buf;
		  
		
        }

	  foo10(&msg_sys);
}

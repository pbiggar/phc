// Basic pointer stuff

void fnptr(int x) {}
typedef void (*function)(int);

function addr_fnptr = fnptr;
function *addr_1, *addr_2 = &addr_fnptr;

void foo()
{
  addr_1 = &addr_fnptr;
}

void bar()
{
  (**addr_1)(0);
  (**addr_2)(0);
}

typedef struct _str { function addr; } str;

void what(str *s)
{
  s->addr = fnptr;
}

void who(str *s)
{
  s->addr(0);
}

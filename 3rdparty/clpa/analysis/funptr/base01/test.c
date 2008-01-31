// Basic pointer stuff

void fnptr(int x) {}
void xfnptr(int x) {}
void yfnptr(int x) {}
void fnptr2(int x, int y) {}

struct str {
  void (*ptr)(int);
  void (*ptr2)(int,int);
};

struct str my_static_ptr = {
  xfnptr, fnptr2
};

struct str my_other_static_ptr = {
  .ptr = fnptr
};

// yes, C's function pointer syntax is horrible
void (*get_me_fnptr())(int)
{
  return fnptr;
}

void foo()
{
  (get_me_fnptr())(3);
}

void update_ptr(struct str *s)
{
  s->ptr = fnptr;
}

void baz(void (*fn)(int))
{
  fn(3);
}

void call_baz()
{
  baz(&yfnptr);
}

void bar()
{
  my_static_ptr.ptr2(3,4);
  my_other_static_ptr.ptr(3); // should be both fnptr and xfnptr
  baz(my_static_ptr.ptr);
}

void yafunptr(int x) {}

void (*funcs[2])(int) = { fnptr, yafunptr };

void callarr(int x, int i)
{
  funcs[i](x);
}

void static_local(int x)
{
  static void (*ptr)(int) = fnptr;
  ptr(x);
}

// initializer and function body addr-scraping

void fn1() {}
void fn2() {}
void fn3() {}
void fn4() {}

void direct()
{
  fn1();
}

void indirect()
{
  void (*pfn)() = fn2;
  (*pfn)();
}

void (*pfn)() = fn3;

# 1 "common.c"
void common() {}

# 1 "test2.c"
void use2() {}

void checkargs() {}
void main()
{
  checkargs();
  common();
  use2();
}

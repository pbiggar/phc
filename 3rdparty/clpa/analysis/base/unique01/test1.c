# 1 "common.c"
void common() {}

# 1 "test1.c"
void use1() {}

void checkargs() {}
void main()
{
  checkargs();
  common();
  use1();
}

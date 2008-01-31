# 1 "common.c"
// comment-whoops
void common() {}

# 1 "test3.c"
void use3() {}

void checkargs() {}
void main()
{
  checkargs();
  common();
  use3();
}

int foo(int x) { return x; }
void bar() { foo(1); }
void baz() { bar(); foo(2); }
int main(int argc, char **argv) { baz(); return 0; }

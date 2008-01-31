// Test side effects.

void bar1(int **a, int *b) {
  *a = b;
}

void bar2(int **a, int *b, int f) {
  if (f)
    *a = b;
}

void foo1(int **a, int *b) {
  bar1(a, b);
}

void foo2(int **a, int *b, int f) {
  bar2(a, b, f);
}

const char* getname() { return "myname"; }

// from openssh/compress.c

typedef struct _Buffer {
  char *buf;
} Buffer;

char* buffer_ptr(Buffer *buffer) { return buffer->buf; }

struct {
  char *next_in;
} outgoing_stream;

void buffer_compress(Buffer * input_buffer)
{
	outgoing_stream.next_in = buffer_ptr(input_buffer);
}

char* buffer_read()
{
  if (outgoing_stream.next_in[0] != '\0')
    return &outgoing_stream.next_in[1];
  return 0;
}

char* call_buffer_read()
{
  buffer_compress(0);
  return buffer_read();
}

void main() {}

void deref(int *x) { *x = 0; }
void loop_deref(int *p, int c) {
  int *x;
  while (c) {
    deref(x);
    x = p;
  }
}

struct list {
  void *v;
  struct list *next;
};

void advance(struct list **pl)
{
  struct list *l = *pl;
  *pl = l->next;
}

// assembly

void* memcpy(void *to, void *from, int n)
{
  int d0, d1, d2;
  __asm__ __volatile__(
      "rep ; movsl\n\t"
      "movl %4,%%ecx\n\t"
      "andl $3,%%ecx\n\t"
      "jz 1f\n\t"
      "rep ; movsb\n\t"
      "1:"
      : "=&c" (d0), "=&D" (d1), "=&S" (d2)
      : "0" (n/4), "g" (n), "1" ((long) to), "2" ((long) from)
      : "memory");
  return to;
}

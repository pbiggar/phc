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

void main() {}

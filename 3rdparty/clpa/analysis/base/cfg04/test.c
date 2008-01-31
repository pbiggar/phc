// cil_sum_body() separation

int foo(int n)
{
  int res;
  switch (n) {
  case 1: res = 1; break;
  case 2: res = 2; break;
  case 3: res = 3; break;
  case 4: res = 4; break;
  case 5: res = 5; break;
  case 6: res = 6; break;
  default: res = 0;
  }
  return res;
}

void irreducible(char *a, int b)
{
  if (b) {
    goto L;
  }

  while (*a) {
    a++;
    L:
    a++;
  }
}

void deeper_nested(char *a)
{
  while (*a) {
    while (*a) {
      while (*a) {
      }
    }
    while (*a) {
    }
  }
}

typedef struct Buffer {
 unsigned char *buf;
 unsigned int alloc;
 unsigned int offset;
 unsigned int end;
} Buffer;

// openssh/buffer.c
void *buffer_append_space(Buffer *buffer, unsigned int len)
{
	unsigned int newlen;
	void *p;

	if (len > 0x100000)
		fatal("buffer_append_space: len %u not supported", len);

	if (buffer->offset == buffer->end) {
		buffer->offset = 0;
		buffer->end = 0;
	}
restart:
	if (buffer->end + len < buffer->alloc) {
		p = buffer->buf + buffer->end;
		buffer->end += len;
		return p;
	}
	if (buffer->offset > buffer->alloc / 2) {
		memmove(buffer->buf, buffer->buf + buffer->offset,
			buffer->end - buffer->offset);
		buffer->end -= buffer->offset;
		buffer->offset = 0;
		goto restart;
	}
	newlen = buffer->alloc + len + 32768;
	if (newlen > 0xa00000)
		fatal("buffer_append_space: alloc %u not supported",
		    newlen);
	buffer->buf = xrealloc(buffer->buf, newlen);
	buffer->alloc = newlen;
	goto restart;
}

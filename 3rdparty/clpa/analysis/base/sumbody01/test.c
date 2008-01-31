// test intbvec.clp and memory.clp coverage

void complexops(int a, int b)
{
  int c = a * 3;
  int d = a * b;
  int e = a / 3;
  int f = a >> 3;
  int g = a % b;
  int h = (a * b) + (a / b);
}

double floats(int a, int b)
{
  float percent = ((float)a / b) * 100;
  return (double)a + (double)b / 1000000.0;
}

void strings()
{
  char *s = "foobar";
}

void pointers(char *a, char *b)
{
  int c = a - b;
  int d = a + 3 - b;
}

void mismatch(unsigned short c)
{
  switch (c & 0xffff) {
  case ((unsigned short)(('*')|0x8000)):
    break;
  }
}

typedef enum { FOOBAR } MyEnum;

void enums(MyEnum e)
{
  switch (e) {
  case FOOBAR:
    break;
  }
}

typedef unsigned int size_t;

struct cmsghdr {
  size_t cmsg_len;
  int cmsg_level;
  int cmsg_type;
  // CIL bug fixed during tweaking: __cmsg_data[] has unknown length
  __extension__ unsigned char __cmsg_data [];
};

void wacky()
{
  char tmp[((((sizeof(int)) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1)) + (((sizeof (struct cmsghdr)) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1)))];
  int x = sizeof(tmp);
  int y = sizeof(struct cmsghdr);
}

unsigned char get_me(struct cmsghdr *hdr)
{
  return hdr->__cmsg_data[0];
}

void foo(int a)
{
  while (a) {a++;}
}

typedef unsigned char u_char;
typedef unsigned int u_int, u_int32_t;
typedef unsigned long u_int64_t;
typedef struct Mac Mac;
typedef struct Comp Comp;
typedef struct Enc Enc;
typedef struct Newkeys Newkeys;

struct Enc {
 char *name;
  // Cipher *cipher;
 int enabled;
 u_int key_len;
 u_int block_size;
 u_char *key;
 u_char *iv;
};
struct Mac {
 char *name;
 int enabled;
  // const EVP_MD *md;
 int mac_len;
 u_char *key;
 int key_len;
};
struct Comp {
 int type;
 int enabled;
 char *name;
};
struct Newkeys {
 Enc enc;
 Mac mac;
 Comp comp;
};
enum kex_modes {
 MODE_IN,
 MODE_OUT,
 MODE_MAX
};
Newkeys *newkeys[MODE_MAX];

typedef struct Buffer {
 u_char *buf;
 u_int alloc;
 u_int offset;
 u_int end;
} Buffer;
static Buffer outgoing_packet;
static Buffer compression_buffer;
Buffer output;

static struct packet_state {
 u_int32_t seqnr;
 u_int32_t packets;
 u_int64_t blocks;
} p_read, p_send;

void buffer_init(Buffer *);
void buffer_clear(Buffer *);
void buffer_free(Buffer *);

u_int buffer_len(Buffer *);
void *buffer_ptr(Buffer *);

void buffer_append(Buffer *, const void *, u_int);
void *buffer_append_space(Buffer *, u_int);

void buffer_get(Buffer *, void *, u_int);

void buffer_consume(Buffer *, u_int);
void buffer_consume_end(Buffer *, u_int);

static u_char extra_pad = 0;

typedef struct CipherContext CipherContext;

struct CipherContext {
 int plaintext;
  // EVP_CIPHER_CTX evp;
  // Cipher *cipher;
};
static CipherContext send_context;

extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
u_char *mac_compute(Mac *, u_int32_t, u_char *, int);
extern int datafellows;

static void
packet_send2_wrapped(void)
{
 u_char type, *cp, *macbuf = ((void *)0);
 u_char padlen, pad;
 u_int packet_length = 0;
 u_int i, len;
 u_int32_t rnd = 0;
 Enc *enc = ((void *)0);
 Mac *mac = ((void *)0);
 Comp *comp = ((void *)0);
 int block_size;

 if (newkeys[MODE_OUT] != ((void *)0)) {
  enc = &newkeys[MODE_OUT]->enc;
  mac = &newkeys[MODE_OUT]->mac;
  comp = &newkeys[MODE_OUT]->comp;
 }
 block_size = enc ? enc->block_size : 8;

 cp = buffer_ptr(&outgoing_packet);
 type = cp[5];

 if (comp && comp->enabled) {
  len = buffer_len(&outgoing_packet);

  buffer_consume(&outgoing_packet, 5);
  buffer_clear(&compression_buffer);
  buffer_compress(&outgoing_packet, &compression_buffer);
  buffer_clear(&outgoing_packet);
  buffer_append(&outgoing_packet, "\0\0\0\0\0", 5);
  buffer_append(&outgoing_packet, buffer_ptr(&compression_buffer),
      buffer_len(&compression_buffer));
  ;

 }

 len = buffer_len(&outgoing_packet);


 padlen = block_size - (len % block_size);
 if (padlen < 4)
  padlen += block_size;
 if (extra_pad) {

  extra_pad = (__builtin_constant_p (block_size) && ((((block_size) - 1) & (block_size)) == 0) ? (((extra_pad) + (block_size) - 1) & ~((block_size) - 1)) : ((((extra_pad) + ((block_size) - 1)) / (block_size)) * (block_size)));
  //  pad = extra_pad - ((len + padlen) % extra_pad);
  debug3("packet_send2: adding %d (len %d padlen %d extra_pad %d)",
      pad, len, padlen, extra_pad);
  padlen += pad;
  extra_pad = 0;
 }

 cp = buffer_append_space(&outgoing_packet, padlen);
 if (enc && !send_context.plaintext) {

  for (i = 0; i < padlen; i++) {
   if (i % 4 == 0)
    rnd = arc4random();
   cp[i] = rnd & 0xff;
   rnd >>= 8;
  }
 } else {

  memset(cp, 0, padlen);
 }

 packet_length = buffer_len(&outgoing_packet) - 4;
 cp = buffer_ptr(&outgoing_packet);
 do { (cp)[0] = (packet_length) >> 24; (cp)[1] = (packet_length) >> 16; (cp)[2] = (packet_length) >> 8; (cp)[3] = (packet_length); } while (0);
 cp[4] = padlen;
 ;


 if (mac && mac->enabled) {
  macbuf = mac_compute(mac, p_send.seqnr,
      buffer_ptr(&outgoing_packet),
      buffer_len(&outgoing_packet));
  ;
 }

 cp = buffer_append_space(&output, buffer_len(&outgoing_packet));
 cipher_crypt(&send_context, cp, buffer_ptr(&outgoing_packet),
     buffer_len(&outgoing_packet));

 if (mac && mac->enabled)
  buffer_append(&output, (char *)macbuf, mac->mac_len);





 if (++p_send.seqnr == 0)
  logit("outgoing seqnr wraps around");
 if (++p_send.packets == 0)
  if (!(datafellows & 0x00008000))
   fatal("XXX too many packets with same key");
 p_send.blocks += (packet_length + 4) / block_size;
 buffer_clear(&outgoing_packet);

 if (type == 21)
  set_newkeys(MODE_OUT);
}

struct list_head {
  struct list_head *next, *prev;
};

struct kiocb {
  int pada;
  struct list_head ki_list;
  int padb;
};

//#define list_entry(ptr, type, member)                                 \
//    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

// linux/include/linux/aio.h
static inline struct kiocb *list_kiocb(struct list_head *h)
{
  return ({ const typeof( ((struct kiocb *)0)->ki_list )*__mptr = (h); (struct kiocb *)( (char *)__mptr - __builtin_offsetof(struct kiocb,ki_list) );});
  // return list_entry(h, struct kiocb, ki_list);
}

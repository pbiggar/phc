// casting and hidden fields

int *g;
struct str0 {
  int *eqg;
};

struct str1 {
  void *fld;
};

void init()
{
  g = malloc(4);
}

void make(struct str1 *p)
{
  struct str0 *s = malloc(4);
  s->eqg = g;
  p->fld = s;
}

struct str0* increment(struct str0 *s)
{
  return &s[1];
}

struct str1* hidden(struct str0 *s)
{
  return (struct str1*)&s[1];
}

struct fb_info {
  struct device *device;
  void *par;
} fb_info;

struct fb_info *framebuffer_alloc(int size, struct device *dev) 
{
  int fb_info_size = sizeof(struct fb_info);
  struct fb_info *info;
  char *p;

  if (size) 
    fb_info_size += ((32/8) - (sizeof(struct fb_info) % (32/8)));

  p = malloc(fb_info_size + size);
  info = (struct fb_info *) p;

  if (size) 
    info->par = p + fb_info_size;

  info->device = dev;
  return info;
}

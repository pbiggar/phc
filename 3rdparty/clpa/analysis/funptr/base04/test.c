// funny casts

struct my_data {
  void (*func)(int);
  void (**ofunc)(int);
};

struct contain_data {
  struct my_data mine;
};

struct other_data {
  void *private;
};

void foo(int);
void set_foo(struct my_data *data)
{
  data->func = foo;
}

void bar(int);
void set_bar(struct other_data *data)
{
  struct my_data *d = data->private;
  d->func = bar;
}

void use(struct other_data *data)
{
  struct my_data *d = data->private;
  d->func(3);
}

void wierd(struct my_data *data, int b)
{
  static void (*func)(int) = &foo;
  if (b) {
    data->ofunc = &func;
  } else {
    data->ofunc = malloc(4);
    *(data->ofunc) = &bar;
  }
}

void use_wierd(struct my_data *data)
{
  (*data->ofunc)(3);
}

void use_contain(void *data)
{
  struct contain_data *d = data;
  d->mine.func(3);
  (*(d->mine.ofunc))(3);
}

// test counting of branches and paths

void fanout(int a, int b, int c)
{
  int z;
  if (a) {
    if (b) {
      if (c) z = 0;
      else z = 1;
    }
    else {
      if (c) z = 2;
      else z = 3;
    }
  }
  else {
    if (b) {
      if (c) z = 4;
      else z = 5;
    }
    else {
      if (c) z = 6;
      else z = 7;
    }
  }
}

void merge(int a, int b, int c)
{
  int z = 0;
  if (a) z |= 0x01;
  if (b) z |= 0x02;
  if (c) z |= 0x03;
}

void loopy(int a, int b, int c)
{
  int z = 0;
  while (a) { while (b) { while (c) { z++; } } }
}

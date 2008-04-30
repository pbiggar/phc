#include <stdio.h>

int main(int argc, char *argv[])
{
  int size;

  if (argc != 2)
  {
    printf("Usage: flush_cache size_of_main_memory_in_KB");
    exit(0);
  }

  size = atoi(argv[1]);
  printf("Flushing %u KB of memory ... ", size);
  fflush(stdout);
  while (size)
  {
    void *p = (void *)malloc(1024);
    if (!p)
      break;
    else
      size--;
  }
  printf("Done\n");
}

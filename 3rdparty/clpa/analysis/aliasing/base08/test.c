// Test handling of softness for arrays, buffers, and recursive structures

int* glob[2];
void glob_array(int *a, int *b)
{
  glob[0] = a;
  glob[1] = b;
}

void parm_buffer(int **buf, int *a, int *b)
{
  buf[0] = a;
  buf[1] = b;
}

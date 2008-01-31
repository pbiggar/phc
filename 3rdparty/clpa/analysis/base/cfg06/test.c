// Test loop splitting for nesting_split_loops()

void basic(char *a)
{
  a++;
  while (*a) {
    a++;
  }
}

void padded(char *a)
{
  a++;
  while (*a) {
    a++;
    while (*a) {
      a++;
    }
    a++;
  }
}

void not_padded(char *a)
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

void exitearly(char *a)
{
  while (*a) {
    if (*a) return;
  }
  a++;
}

void complex(char *a)
{
  a++;
  while (*a) {
    while (*a) {
      if (*a) goto L;
      a++;
    }
  }
  a++;
 L:
  a++;
}

void empty(int a, int b)
{
  while (a) {}
}

void little_infinite()
{
  while (1) {}
}

void infinite(int a)
{
  while (1) {a = 0;}
}

int match(char *name, char *pat, char *patend)
{
  int ok, negate_range;
  char c, k;

  while (pat < patend) {
    c = *pat++;
    switch (c) {
    case '*':
      if (pat == patend)
        return(1);
      do
        if (match(name, pat, patend))
          return(1);
      while (*name++ != 0);
      return(0);
    case '?':
      if (*name++ == 0)
        return(0);
      break;
    case '[':
      ok = 0;
      if ((k = *name++) == 0)
        return(0);
      if ((negate_range = (*pat == '!')) != 0)
        ++pat;
      while ((c = *pat++) != ']')
        if (*pat == '-') {
          if (c <= k && k <= pat[1])
            ok = 1;
          pat += 2;
        } else if (c == k)
          ok = 1;
      if (ok == negate_range)
        return(0);
      break;
    default:
      if (*name++ != c)
        return(0);
      break;
    }
  }

  return (*name == 0);
}

int nest_test(char *a)
{
  while (*a) {
    if (*a == 'x')
      return 0;  // included with nesting/maximize
  }
  return 1;  // included only with maximize
}

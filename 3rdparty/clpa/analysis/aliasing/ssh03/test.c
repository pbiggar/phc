int BSDoptind;
int BSDoptreset;
int BSDoptopt;
int BSDopterr;
char* BSDoptarg;

extern char *strchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

int
BSDgetopt(nargc, nargv, ostr)
 int nargc;
 char * const *nargv;
 const char *ostr;
{
 extern char *__progname;
 static char *place = "";
 char *oli;

 if (ostr == ((void *)0))
  return (-1);

 if (BSDoptreset || !*place) {
  BSDoptreset = 0;
  if (BSDoptind >= nargc || *(place = nargv[BSDoptind]) != '-') {
   place = "";
   return (-1);
  }
  if (place[1] && *++place == '-') {
   ++BSDoptind;
   place = "";
   return (-1);
  }
 }

 if ((BSDoptopt = (int)*place++) == (int)':' ||
     !(oli = strchr(ostr, BSDoptopt))) {
   if (BSDoptopt == (int)'-')
    return (-1);
   if (!*place)
    ++BSDoptind;
   if (BSDopterr && *ostr != ':');
     //(void)fprintf(stderr,
     //     "%s: illegal option -- %c\n", __progname, BSDoptopt);
   return ((int)'?');
 }

 if (*++oli != ':') {
  BSDoptarg = ((void *)0);
  if (!*place)
   ++BSDoptind;
 }
 else {
  if (*place)
   BSDoptarg = place;
  else if (nargc <= ++BSDoptind) {
   place = "";
   if (*ostr == ':')
    return ((int)':');
   if (BSDopterr);
     //(void)fprintf(stderr,
     //        "%s: option requires an argument -- %c\n",
     //        __progname, BSDoptopt);
   return ((int)'?');
  }
   else
   BSDoptarg = nargv[BSDoptind];
  place = "";
  ++BSDoptind;
 }
 return (BSDoptopt);
}

void call()
{
  BSDgetopt(0,malloc(4),"");
}

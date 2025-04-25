/*
** fnv1a.c
** compute the fnv1a hash of a given string
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "opt.h"

static int ignore_case;
static const char *outfile;

const struct opt_s progopts [] = {
  OPT_HELP, OPT_VERSION,
  { "-i", NULL, "Ignore case when computing hashes", OPT_SET_FLAG,
    &ignore_case, NULL },
  { "-o", "--output", "[FILE]Write output to FILE", OPT_SET_VALUE,
    &outfile, NULL },
  { "-c", "--caseful", "Do not ignore case when computing hashes",
    OPT_CLR_FLAG, &ignore_case, NULL },
  {NULL}
};

static unsigned int fnv1a (const char *s) {
  unsigned int hash = 0x4b9ace2f;
  for (; *s; s++) {
    int c = *s;
    if (ignore_case) c = tolower(c);
    hash = (hash ^ c) * 0x1000193;
  }
  return hash * 0x1000193;
}

int main (int argc, const char *const *argv) {
  FILE *f;
  int i;
  opt_setversion("1.0.0");
  opt_setusage("[options] string...");
  i = opt_parse(argc, argv, progopts, NULL);
  if (i < 0)
    return i == LIBOPT_HELP ? EXIT_SUCCESS : EXIT_FAILURE;
  if (outfile == NULL)
    f = stdout;
  else
    f = fopen(outfile, "w");
  if (f == NULL) return EXIT_FAILURE;
  for (; i < argc; i++)
    fprintf(f, "%8x    %s\n", fnv1a(argv[i]), argv[i]);
  if (outfile)
    fclose(f);
  return EXIT_SUCCESS;
}

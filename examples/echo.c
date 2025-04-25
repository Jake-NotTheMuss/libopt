/*
** echo.c
** echo arguments to standard output
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "opt.h"

static int no_lf;
static const char *prefix = "";

const struct opt_s progopts [] = {
  OPT_HELP,
  { "-n", NULL, "Do not echo a line-feed", OPT_SET_FLAG, &no_lf, NULL },
  { "-p", "--prefix", "[STRING] Prepend STRING to each argument",
    OPT_SET_VALUE, &prefix, NULL },
  { NULL }
};

const char *progname = "echo";

static void fn_print (const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
}

int main (int argc, const char *const *argv) {
  int i;
  opt_setprintfn(fn_print);
  i = opt_parse(argc, argv, progopts, &progname);
  if (i < 0)
    return i == LIBOPT_HELP ? EXIT_SUCCESS : EXIT_FAILURE;
  if (i < argc) {
    printf("%s%s", prefix, argv[i]);
    while (++i < argc)
      printf(" %s%s", prefix, argv[i]);
    if (!no_lf) printf("\n");
  }
  return EXIT_SUCCESS;
}

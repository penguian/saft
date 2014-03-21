/* test_harness.c
 * Copyright (C) 2014  Paul Leopardi
 *
 * This file is part of SAFT.
 *
 * SAFT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>

#include "saftopt.h"
#include "test_harness.h"

static SaftOptDesc opt_desc[] =
{
    /* Program information */
    {"help",        no_argument,       'h', "Prints a short help"},
    /* General options */
    {"verbose",     no_argument,       'v', "Increases the program's verbosity"},

    {NULL, 0, 0, NULL}
};

TestOptions*
new_test_options ()
{
  TestOptions *options;

  options                               = malloc (sizeof (*options));
  options->verbosity                    = 0;

  return options;
}

TestOptions*
get_test_options (int    argc,
                  char **argv)
{
  struct option  *long_options = saft_opt_get_options (opt_desc);
  TestOptions    *options      = new_test_options ();
  int             cleanup      = 0;
  char           *optstring;

  optstring = saft_opt_get_optstring (opt_desc);
  while (1)
    {
      int option_index = 0;
      int c;

      c = getopt_long (argc,
                       argv,
                       optstring,
                       long_options,
                       &option_index);
      if (c == -1)
        break;

      switch (c)
        {
          case 'h':
              saft_opt_help (argv[0],
                             opt_desc,
                             "SAFT (Sequence Alignment Free Tool)");
              cleanup = 1;
              break;
          case 'v':
              options->verbosity++;
              break;
          default:
              saft_opt_usage (argv[0]);
              cleanup = 1;
        }
    }

  free (optstring);
  free (long_options);

  if (cleanup)
  {
    free_test_options (options);
    options = NULL;
  }
  return options;
}

void
free_test_options (TestOptions* options)
{
  free (options);
}

int
run_test (int (*test_function)(), char *test_name)
{
  int test_error = (*test_function)();
  printf("%s: %s\n", test_name, test_error ?  "failure" : "success");
  return test_error;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

/* saftopt.c
 * Copyright (C) 2008  Sylvain FORET
 * Copyright (C) 2014  Paul LEOPARDI
 *
 * This program is free software: you can redistribute it and/or modify
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

/**
 *
 */

#define _GNU_SOURCE
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "saftopt.h"

struct option*
saft_opt_get_options (SaftOptDesc *opt_desc)
{
  struct option *long_options;
  int            nb_options;
  int            i;

  for (nb_options = 0; opt_desc[nb_options].name; nb_options++);

  long_options = malloc ((nb_options + 1) * sizeof (*long_options));

  for (i = 0; i < nb_options; i++)
    {
      long_options[i].name    = opt_desc[i].name;
      long_options[i].has_arg = opt_desc[i].has_arg;
      long_options[i].flag    = NULL;
      long_options[i].val     = opt_desc[i].val;
    }
  long_options[i].name    = NULL;
  long_options[i].has_arg = 0;
  long_options[i].flag    = NULL;
  long_options[i].val     = 0;

  return long_options;
}

char*
saft_opt_get_optstring (SaftOptDesc *opt_desc)
{
  char *optstring;
  int   nb_options;
  int   i;
  int   j;

  for (nb_options = 0; opt_desc[nb_options].name; nb_options++);

  optstring = malloc (2 * nb_options + 1);

  for (i = 0, j = 0; i < nb_options; i++)
    {
      optstring[j] = (char)opt_desc[i].val;
      j++;
      if (opt_desc[i].has_arg == required_argument)
        {
          optstring[j] = ':';
          j++;
        }
    }
  optstring[j] = '\0';

  return optstring;
}

void
saft_opt_usage (char *argv0)
{
  char *prog = basename (argv0);
  printf ("Usage: %s OPTIONS\n", prog);
  printf ("Try %s -h for help\n", prog);
}

void
saft_opt_help (char        *argv0,
               SaftOptDesc *opt_desc,
               char        *message)
{
  char        *prog    = basename (argv0);
  size_t       longest = 0;
  unsigned int i;

  for (i = 0; opt_desc[i].name; i++)
    {
      const size_t l = strlen (opt_desc[i].name);
      if (l > longest)
        longest = l;
    }

  printf ("%s\n", message);
  printf ("Usage: %s OPTIONS\n", prog);
  printf ("Where OPTIONS are:\n");

  for (i = 0; opt_desc[i].name; i++)
    printf ("  --%-*s (-%c) : %s\n",
            (int)longest,
            opt_desc[i].name,
            opt_desc[i].val,
            opt_desc[i].description);
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

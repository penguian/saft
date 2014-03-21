/* saftfasta.c
 * Copyright (C) 2008  Sylvain FORET
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

#include <stdio.h>

#include "test_harness.h"
#include "saftfasta.h"

static TestOptions* options;

int
test_saft_fasta_read ()
{
  int error = 0;
  return error;
}

int
test_saft_fasta_append ()
{
  int error = 0;
  return error;
}

int
test_saft_fasta_iter ()
{
  int error = 0;
  return error;
}

int
run_all_tests ()
{
  int error = 0;
  error |= run_test(test_saft_fasta_read, "test_saft_fasta_read");
  error |= run_test(test_saft_fasta_append, "test_saft_fasta_append");
  error |= run_test(test_saft_fasta_iter, "test_saft_fasta_iter");
  return error;
}

int
main (int    argc,
      char **argv)
{
  int error;
  options = get_test_options(argc, argv);
  if (options != NULL)
  {
    error = run_all_tests();
    free_test_options(options);
  }
  else
  {
    error = 1;
  }
  return error;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

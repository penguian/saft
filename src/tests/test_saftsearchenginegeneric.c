/* saftsearchenginegeneric.c
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
#include "saftsearchengines.h"

/*************************/
/* Generic Search Engine */
/*************************/

int
test_saft_search_engine_generic_new ()
{
  int error = 0;
  return error;
}

int
test_search_engine_generic_search_two_sequences ()
{
  int error = 0;
  return error;
}

int
test_search_engine_generic_search_all ()
{
  int error = 0;
  return error;
}

int
main (int    argc,
      char **argv)
{
  int error = 0;
  error |= run_test(test_saft_search_engine_generic_new, "test_saft_search_engine_generic_new");
  error |= run_test(test_search_engine_generic_search_two_sequences, "test_search_engine_generic_search_two_sequences");
  error |= run_test(test_search_engine_generic_search_all, "test_search_engine_generic_search_all");
  return error;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

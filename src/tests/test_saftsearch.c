/* saftsearch.c
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
#include "saftsearch.h"

/******************/
/* Search Options */
/******************/

int
test_saft_options_new ()
{
  int error = 0;
  return error;
}

int
test_saft_options_free ()
{
  int error = 0;
  return error;
}


/**********/
/* Result */
/**********/

int
test_saft_result_new ()
{
  int error = 0;
  return error;
}

int
test_saft_result_free ()
{
  int error = 0;
  return error;
}

/**********/
/* Search */
/**********/

int
test_saft_search_new ()
{
  int error = 0;
  return error;
}

int
test_saft_search_free ()
{
  int error = 0;
  return error;
}

int
test_saft_search_free_all ()
{
  int error = 0;
  return error;
}

int
test_saft_search_reverse ()
{
  int error = 0;
  return error;
}

int
test_saft_search_add_result ()
{
  int error = 0;
  return error;
}

int
test_saft_search_adjust_pvalues ()
{
  int error = 0;
  return error;
}

int
test_results_heap_insert ()
{
  int error = 0;
  return error;
}

int
test_results_heap_heapify ()
{
  int error = 0;
  return error;
}

int
test_results_heap_sort ()
{
  int error = 0;
  return error;
}

/********************/
/* SaftSearchEngine */
/********************/

int
test_saft_search_engine_new ()
{
  int error = 0;
  return error;
}

int
test_saft_search_engine_free ()
{
  int error = 0;
  return error;
}

int
test_saft_search_two_sequences ()
{
  int error = 0;
  return error;
}

int
test_saft_search_all ()
{
  int error = 0;
  return error;
}

int
main (int    argc,
      char **argv)
{
  int error = 0;
  error |= run_test(test_saft_options_new, "test_saft_options_new");
  error |= run_test(test_saft_options_free, "test_saft_options_free");
  error |= run_test(test_saft_result_new, "test_saft_result_new");
  error |= run_test(test_saft_result_free, "test_saft_result_free");
  error |= run_test(test_saft_search_new, "test_saft_search_new");
  error |= run_test(test_saft_search_free, "test_saft_search_free");
  error |= run_test(test_saft_search_free_all, "test_saft_search_free_all");
  error |= run_test(test_saft_search_reverse, "test_saft_search_reverse");
  error |= run_test(test_saft_search_add_result, "test_saft_search_add_result");
  error |= run_test(test_saft_search_adjust_pvalues, "test_saft_search_adjust_pvalues");
  error |= run_test(test_results_heap_insert, "test_results_heap_insert");
  error |= run_test(test_results_heap_heapify, "test_results_heap_heapify");
  error |= run_test(test_results_heap_sort, "test_results_heap_sort");
  error |= run_test(test_saft_search_engine_new, "test_saft_search_engine_new");
  error |= run_test(test_saft_search_engine_free, "test_saft_search_engine_free");
  error |= run_test(test_saft_search_two_sequences, "test_saft_search_two_sequences");
  error |= run_test(test_saft_search_all, "test_saft_search_all");
  return error;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

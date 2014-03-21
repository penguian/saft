/* saftsearchenginednaarray.c
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

static TestOptions* options;

int
test_saft_search_engine_dna_array_new ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_free ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_hash_sequence ()
{
  int error = 0;
  return error;
}

int
test_sse2_dot_prod ()
{
  int error = 0;
  return error;
}

int
test_sse3_dot_prod ()
{
  int error = 0;
  return error;
}

int
test_scalar_dot_prod ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_d2 ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_two_sequences ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_all ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_all_no_cache ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_queries_iter_func ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_db_iter_func ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_cache_sequence ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_all_dcached ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_query ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_all_qcached ()
{
  int error = 0;
  return error;
}

int
test_search_engine_dna_array_search_db ()
{
  int error = 0;
  return error;
}

int
test_dna_array_db_entry_new ()
{
  int error = 0;
  return error;
}

int
test_dna_array_db_entry_free ()
{
  int error = 0;
  return error;
}

int
test_dna_array_db_entry_free_all ()
{
  int error = 0;
  return error;
}

int
run_all_tests ()
{
  int error = 0;
  error |= run_test(test_saft_search_engine_dna_array_new, "test_saft_search_engine_dna_array_new");
  error |= run_test(test_search_engine_dna_array_free, "test_search_engine_dna_array_free");
  error |= run_test(test_search_engine_dna_array_hash_sequence, "test_search_engine_dna_array_hash_sequence");
  error |= run_test(test_sse2_dot_prod, "test_sse2_dot_prod");
  error |= run_test(test_sse2_dot_prod, "test_sse2_dot_prod");
  error |= run_test(test_scalar_dot_prod, "test_scalar_dot_prod");
  error |= run_test(test_search_engine_dna_array_d2, "test_search_engine_dna_array_d2");
  error |= run_test(test_search_engine_dna_array_search_two_sequences, "test_search_engine_dna_array_search_two_sequences");
  error |= run_test(test_search_engine_dna_array_search_all, "test_search_engine_dna_array_search_all");
  error |= run_test(test_search_engine_dna_array_search_all_no_cache, "test_search_engine_dna_array_search_all_no_cache");
  error |= run_test(test_search_engine_dna_array_queries_iter_func, "test_search_engine_dna_array_queries_iter_func");
  error |= run_test(test_search_engine_dna_array_db_iter_func, "test_search_engine_dna_array_db_iter_func");
  error |= run_test(test_search_engine_dna_array_cache_sequence, "test_search_engine_dna_array_cache_sequence");
  error |= run_test(test_search_engine_dna_array_search_all_dcached, "test_search_engine_dna_array_search_all_dcached");
  error |= run_test(test_search_engine_dna_array_search_query, "test_search_engine_dna_array_search_query");
  error |= run_test(test_search_engine_dna_array_search_all_qcached, "test_search_engine_dna_array_search_all_qcached");
  error |= run_test(test_search_engine_dna_array_search_db, "test_search_engine_dna_array_search_db");
  error |= run_test(test_dna_array_db_entry_new, "test_dna_array_db_entry_new");
  error |= run_test(test_dna_array_db_entry_free, "test_dna_array_db_entry_free");
  error |= run_test(test_dna_array_db_entry_free_all, "test_dna_array_db_entry_free_all");
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

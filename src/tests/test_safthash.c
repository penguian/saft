/* safthash.c
 * Copyright (C) 2013  Sylvain FORET
 *
 * This file is part of libngs.
 *
 * libngs is free software: you can redistribute it and/or modify
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

#include <limits.h>
#include <stdio.h>

#include "test_harness.h"
#include "safthash.h"

static TestOptions* options;

int
test_saft_hash_generic ()
{
  int error = 0;
  unsigned long returned_hash_value;
  unsigned long hash_table_size;

  SaftHashKmer kmer_zero;
  kmer_zero.kmer_vall = 0UL;
  SaftHashKmer kmer_one;
  kmer_one.kmer_vall = 1UL;
  SaftHashKmer kmer_max;
  kmer_max.kmer_vall = ~0UL;

  const SaftHashKmer *kmer_array[] = {&kmer_one, &kmer_max};
  int kmer_array_len = sizeof(kmer_array)/sizeof(&kmer_zero);

  for (int exponent = 0; exponent < 64; ++exponent)
  {
    hash_table_size = 1UL << exponent;
    for (int kmer_array_index = 0; kmer_array_index != kmer_array_len; ++kmer_array_index)
    {
      returned_hash_value = saft_hash_generic(kmer_array[kmer_array_index], hash_table_size);
      if (returned_hash_value >= hash_table_size)
      {
        error = 1;
        printf("test_saft_hash_generic: Kmer %d: Hash value %10lu too large for table %2d.\n",
               kmer_array_index, returned_hash_value, exponent);
      }
    }
  }
  return error;
}

int
test_saft_equal_generic ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_long ()
{
  int error = 0;
  return error;
}

int
test_saft_equal_long ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_set_shift ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_find_closest_shift ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_set_shift_from_size ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_copy_kmer ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_lookup ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_lookup_node_for_insertion ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_resize ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_maybe_resize ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_new ()
{
  int error = 0;
  SaftHashTable* hash_table_ptr = NULL;

  /* Test for sizes that are powers of 2 that saft_hash_table_new
  *  returns a non-null ponter. Assume that saft_hash_table_destroy works.
  */
  const int max_exponent = sizeof(size_t) * CHAR_BIT;
  for (int exponent = 0; exponent < max_exponent; ++exponent)
  {
    unsigned long hash_table_size = 1UL << exponent;
    hash_table_ptr = saft_hash_table_new(hash_table_size);
    if (hash_table_ptr == NULL)
    {
      error = 1;
      printf("test_saft_hash_table_new: size %10lu failed.\n",
             hash_table_size);
    }
    else
    {
      saft_hash_table_destroy(hash_table_ptr);
      hash_table_ptr = NULL;
    }
  }
  return error;
}

int
test_saft_hash_table_new_full ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_iter_init ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_iter_next ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_destroy ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_increment ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_add_count ()
{
  int error = 0;
  return error;
}

int
test_saft_hash_table_lookup_or_create ()
{
  int error = 0;
  return error;
}

int
run_all_tests ()
{
  int error = 0;
  error |= run_test(test_saft_hash_generic, "test_saft_hash_generic");
  error |= run_test(test_saft_equal_generic, "test_saft_equal_generic");
  error |= run_test(test_saft_hash_long, "test_saft_hash_long");
  error |= run_test(test_saft_equal_long, "test_saft_equal_long");
  error |= run_test(test_saft_hash_table_set_shift, "test_saft_hash_table_set_shift");
  error |= run_test(test_saft_hash_table_find_closest_shift, "test_saft_hash_table_find_closest_shift");
  error |= run_test(test_saft_hash_table_set_shift_from_size, "test_saft_hash_table_set_shift_from_size");
  error |= run_test(test_saft_hash_table_copy_kmer, "test_saft_hash_table_copy_kmer");
  error |= run_test(test_saft_hash_table_lookup, "test_saft_hash_table_lookup");
  error |= run_test(test_saft_hash_table_lookup_node_for_insertion, "test_saft_hash_table_lookup_node_for_insertion");
  error |= run_test(test_saft_hash_table_resize, "test_saft_hash_table_resize");
  error |= run_test(test_saft_hash_table_maybe_resize, "test_saft_hash_table_maybe_resize");
  error |= run_test(test_saft_hash_table_new, "test_saft_hash_table_new");
  error |= run_test(test_saft_hash_table_new_full, "test_saft_hash_table_new_full");
  error |= run_test(test_saft_hash_table_iter_init, "test_saft_hash_table_iter_init");
  error |= run_test(test_saft_hash_table_iter_next, "test_saft_hash_table_iter_next");
  error |= run_test(test_saft_hash_table_destroy, "test_saft_hash_table_destroy");
  error |= run_test(test_saft_hash_table_increment, "test_saft_hash_table_increment");
  error |= run_test(test_saft_hash_table_add_count, "test_saft_hash_table_add_count");
  error |= run_test(test_saft_hash_table_lookup_or_create, "test_saft_hash_table_lookup_or_create");
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

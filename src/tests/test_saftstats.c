/* saftstats.c
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
#include <stdlib.h>

#include "test_harness.h"
#include "saftstats.h"

static TestOptions* options;

static void
print_context(SaftStatsContext* context,
              char*             message)
{
  printf("%s\n", message);
  printf("context pointer     ==  0x%016lx\n", (unsigned long) context);
  printf("context->word_size  ==  %u\n", context->word_size);
  printf("context->p_2_k      == %12.5e\n", context->p_2_k);
  printf("context->sum_var_Yu == %12.5e\n", context->sum_var_Yu);
  printf("context->cov_crab   == %12.5e\n", context->cov_crab);
  printf("context->cov_diag   == %12.5e\n", context->cov_diag);
  printf("context->cov_ac1    == %12.5e\n", context->cov_ac1);
  printf("context->cov_ac2    == %12.5e\n", context->cov_ac2);
  printf("context->unif       ==  %u\n", context->unif);
  printf("\n");
}

int
test_once_saft_stats_context_new (unsigned int word_size,
                                  double      *letter_frequencies,
                                  unsigned int n_letters,
                                  char*        message)
{
  int error = 0;
  SaftStatsContext* context;
  context = saft_stats_context_new (word_size, letter_frequencies, n_letters);
  /**
   * A NULL returned context pointer is an error.
   * Otherwise, just print out the context.
   */
  if (context == NULL)
  {
    error = 1;
    if (options->verbosity)
    {
      printf("saft_stats_context_new(%u, 0x%016lx, %u) returned NULL\n",
             word_size, (unsigned long) letter_frequencies, n_letters);
    }
  }
  else
  {
    if (options->verbosity)
    {
      print_context(context, message);
    }
  }
  /**
   * Free the context to avoid memory leaks.
   * Assume that saft_stats_context_free just works.
   */
  saft_stats_context_free (context);
  return error;
}

int
test_saft_stats_context_new ()
{
  int error = 0;
  char * message;
  /**
   * The unsigned int word_size is expected to be small.
   * If n_letters > 0, then the pointer letter_frequencies must not be NULL.
   * It must point to an array of doubles of length at least n_letters.
   */

  message = "Try with word_size == 0.";
  unsigned int word_size = 0;
  double       *letter_frequencies = NULL;
  unsigned int n_letters = 0;
  error |= test_once_saft_stats_context_new (word_size, letter_frequencies, n_letters, message);

  message = "Try with word_size == 1.";
  word_size = 1;
  letter_frequencies = NULL;
  n_letters = 0;
  error |= test_once_saft_stats_context_new (word_size, letter_frequencies, n_letters, message);

  message = "Try with n_letters == 4, and non-trivial frequencies 0.25.";
  double frequencies_table[] = {0.25, 0.25, 0.25, 0.25};
  word_size = 1;
  letter_frequencies = frequencies_table;
  n_letters = 4;
  error |= test_once_saft_stats_context_new (word_size, letter_frequencies, n_letters, message);

  message = "Try with word_size == 8.";
  word_size = 8;
  letter_frequencies = frequencies_table;
  n_letters = 4;
  error |= test_once_saft_stats_context_new (word_size, letter_frequencies, n_letters, message);

  message = "Try with word_size == 1 and frequencies 0.1, 0.2, 0.3, 0.4.";
  word_size = 1;
  frequencies_table[0] = 0.1;
  frequencies_table[0] = 0.2;
  frequencies_table[0] = 0.3;
  frequencies_table[0] = 0.4;
  letter_frequencies = frequencies_table;
  n_letters = 4;
  error |= test_once_saft_stats_context_new (word_size, letter_frequencies, n_letters, message);

  return error;
}

int
test_saft_stats_context_free ()
{
  int error = 0;
  return error;
}

int
test_once_saft_stats_mean (unsigned int word_size,
                           double      *letter_frequencies,
                           unsigned int n_letters,
                           char*        message)

{
  int error = 0;
  SaftStatsContext* context;
  double tolerance = 1.0e-12;

  if (options->verbosity)
  {
    printf("%s\n", message);
  }

  context = saft_stats_context_new (word_size, letter_frequencies, n_letters);
  /**
   * A NULL returned context pointer is an error.
   */
  if (context == NULL)
  {
    error = 1;
    if (options->verbosity)
    {
      printf("saft_stats_context_new(%u, 0x%016lx, %u) returned NULL\n",
             word_size, (unsigned long) letter_frequencies, n_letters);
    }
  }
  else
  {
    unsigned int query_size   = 1234;
    unsigned int subject_size = 4321;
    double mean = saft_stats_mean (context, query_size, subject_size);
    double p_2_k = context->p_2_k;
    double mean_should_be = query_size * subject_size * p_2_k;
    if (abs(p_2_k) < tolerance)
    {
      /**
       * p_2_k is small: use absolute error
       */
      error |= abs(mean - mean_should_be) > tolerance;
    }
    else
    {
      /**
       * Use relative error.
       */
      error |= abs((mean - mean_should_be) / mean_should_be) > tolerance;
    }
    if (error && options->verbosity)
    {
      printf("test_saft_stats_mean: returned mean %12.5f should be %12.5f\n",
             mean, mean_should_be);
    }
  }
  /**
   * Free the context to avoid memory leaks.
   * Assume that saft_stats_context_free just works.
   */
  saft_stats_context_free (context);
  return error;
}

int
test_saft_stats_mean ()
{
  int error = 0;
  SaftStatsContext* context;
  double tolerance = 1.0e-12;
  char * message;

  message = "Try with word_size == 0.";
  unsigned int word_size = 0;
  double       *letter_frequencies = NULL;
  unsigned int n_letters = 0;
  error |= test_once_saft_stats_mean (word_size, letter_frequencies, n_letters, message);

  message = "Try with word_size == 1.";
  word_size = 1;
  letter_frequencies = NULL;
  n_letters = 0;
  error |= test_once_saft_stats_mean (word_size, letter_frequencies, n_letters, message);

  message = "Try with n_letters == 4, and non-trivial frequencies 0.25.";
  double frequencies_table[] = {0.25, 0.25, 0.25, 0.25};
  word_size = 1;
  letter_frequencies = frequencies_table;
  n_letters = 4;
  error |= test_once_saft_stats_mean (word_size, letter_frequencies, n_letters, message);

  message = "Try with word_size == 8.";
  word_size = 8;
  letter_frequencies = frequencies_table;
  n_letters = 4;
  error |= test_once_saft_stats_mean (word_size, letter_frequencies, n_letters, message);

  message = "Try with word_size == 1 and frequencies 0.1, 0.2, 0.3, 0.4.";
  word_size = 1;
  frequencies_table[0] = 0.1;
  frequencies_table[0] = 0.2;
  frequencies_table[0] = 0.3;
  frequencies_table[0] = 0.4;
  letter_frequencies = frequencies_table;
  n_letters = 4;
  error |= test_once_saft_stats_mean (word_size, letter_frequencies, n_letters, message);
  return error;
}

int
test_saft_stats_var ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_sum_freq_pow ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_pgamma_m_v ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_pgamma ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_BH_array ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_BH_element ()
{
  int error = 0;
  return error;
}

int
run_all_tests ()
{
  int error = 0;
  error |= run_test(test_saft_stats_context_new, "test_saft_stats_context_new");
  error |= run_test(test_saft_stats_context_free, "test_saft_stats_context_free");
  error |= run_test(test_saft_stats_mean, "test_saft_stats_mean");
  error |= run_test(test_saft_stats_var, "test_saft_stats_var");
  error |= run_test(test_saft_stats_sum_freq_pow, "test_saft_stats_sum_freq_pow");
  error |= run_test(test_saft_stats_pgamma_m_v, "test_saft_stats_pgamma_m_v");
  error |= run_test(test_saft_stats_pgamma, "test_saft_stats_pgamma");
  error |= run_test(test_saft_stats_BH_array, "test_saft_stats_BH_array");
  error |= run_test(test_saft_stats_BH_element, "test_saft_stats_BH_element");
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

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

#include "test_harness.h"
#include "saftstats.h"

int
test_test_saft_stats_context_new ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_context_free ()
{
  int error = 0;
  return error;
}

int
test_saft_stats_mean ()
{
  int error = 0;
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
main (int    argc,
      char **argv)
{
  int error = 0;
  error |= run_test(test_test_saft_stats_context_new, "test_test_saft_stats_context_new");
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

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

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

#include <math.h>
#include <stdlib.h>

#include "saftstats.h"

static double saft_stats_sum_freq_pow (double      *f,
                                       unsigned int l,
                                       unsigned int freq_pow,
                                       unsigned int sum_pow);


SaftStatsContext*
saft_stats_context_new (unsigned int word_size,
                        double      *letters_frequencies,
                        unsigned int n_letters)
{
#define p(freq_pow, sum_pow) saft_stats_sum_freq_pow(letters_frequencies, n_letters, freq_pow, sum_pow)

  SaftStatsContext *context;
  int               k = word_size;
  unsigned int      i;
  unsigned int      j;

  context           = malloc (sizeof (*context));
  context->word_size = word_size;
  context->p_2_k     = p(2, k);
  context->cov_crab  = 0;
  context->cov_diag  = 0;
  context->cov_ac1   = 0;
  context->cov_ac2   = 0;
  context->unif      = 1;

  for (i = 1; i < n_letters; i++)
    if (letters_frequencies[i] != letters_frequencies[0])
      {
        context->unif = 0;
        break;
      }

  context->sum_var_Yu = p (2, k) - p (2, 2 * k);

  if (!context->unif)
    context->cov_crab = (p(3, k) +
                         2 * p(2, 2) * p(3, 1) *
                         ((p(3, k - 1) - p(2, 2 * (k - 1))) / (p(3, 1) - p(2, 2))) -
                         (2 * k - 1) * p(2, 2 * k));

  if (context->word_size == 1)
    return context;

  context->cov_diag = (p(2, k + 1) *
                      ((1 - p(2, k - 1)) / (1 - p(2, 1))) -
                      (k - 1) * p(2, 2 * k)) * 2;

  for (i = 1; i < k; i++)
    for (j = 0; j < i; j++)
      {
        unsigned int nu = (k - j) / (i - j);
        unsigned int ro = (k - j) % (i - j);

        context->cov_ac1 += (p(2, 2 * j) *
                            p(2 * nu + 3, ro) *
                            p(2 * nu + 1, i - j - ro) -
                            p(2, 2 * k));
      }
  context->cov_ac1 *= 4;

  for (i = 1; i < k; i++)
    {
      for (j = 1; j < k; j++)
        {
          unsigned int x;
          unsigned int nu    = k / (i + j);
          unsigned int ro    = k % (i + j);
          double       prod1 = 1;
          double       prod2 = 1;

          for (x = 1; x <= j; x++)
            {
              unsigned int t = 1 + 2 * nu;

              if (x <= ro)
                t++;
              if (x + i <= ro)
                t++;
              prod1 *= p(t, 1);
            }
          for (x = 1; x <= i; x++)
            {
              unsigned int t = 1 + 2 * nu;

              if (x <= ro)
                t++;
              if (x + j <= ro)
                t++;
              prod2 *= p(t, 1);
            }
          context->cov_ac2 += prod1 * prod2;
        }
    }
  context->cov_ac2 -= (k - 1) * (k - 1) * p(2, 2 * k);
  context->cov_ac2 *= 2;

  return context;

#undef p
}

void
saft_stats_context_free (SaftStatsContext *context)
{
  if (context)
    free (context);
}

double
saft_stats_mean (SaftStatsContext *context,
                 unsigned int      query_size,
                 unsigned int      subject_size)
{
  return query_size * subject_size * context->p_2_k;
}

double
saft_stats_var (SaftStatsContext *context,
                unsigned int      query_size,
                unsigned int      subject_size)
{
  double sum_var_Yu;
  double cov_crab;
  double cov_diag;
  double cov_ac1;
  double cov_ac2;
  int    m = query_size;
  int    n = subject_size;
  int    k = context->word_size;

  sum_var_Yu = m * n * context->sum_var_Yu;
  cov_crab   = m * n * (n + m - 4 * k + 2) * context->cov_crab;

  if (context->word_size == 1)
    return sum_var_Yu + cov_crab;

  cov_diag = m * n * context->cov_diag;
  cov_ac1  = m * n * context->cov_ac1;
  cov_ac2  = m * n * context->cov_ac2;

  return sum_var_Yu + cov_crab + cov_diag + cov_ac1 + cov_ac2;
}

static double
saft_stats_sum_freq_pow (double      *f,
                         unsigned int l,
                         unsigned int freq_pow,
                         unsigned int sum_pow)
{
  double       res = 0;
  unsigned int i;

  for (i = 0; i < l; i++)
    res += pow (f[i], (double)freq_pow);

  res = pow (res, (double)sum_pow);

  return res;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

/* saftsearch.h
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

#ifndef __SAFT_SEARCH_H__
#define __SAFT_SEARCH_H__


#include <safthash.h>
#include <saftstatistictype.h>


#ifdef __cplusplus
extern "C"
{
#endif

/**********/
/* Result */
/**********/

typedef struct _SaftResult SaftResult;

struct _SaftResult
{
  SaftResult  *next;
  char        *name;
  double       s_value;
  unsigned int subject_size;
  double       p_value;
  double       p_value_adj;
};

SaftResult* saft_result_new  (void);

void        saft_result_free (SaftResult *result);

/**********/
/* Search */
/**********/

typedef enum
{
  SAFT_FREQ_QUERY,
  SAFT_FREQ_SUBJECTS,
  SAFT_FREQ_QUERY_SUBJECTS,
  SAFT_FREQ_USER,
  SAFT_FREQ_UNIFORM,
  SAFT_FREQ_SPECTRUM
}
SaftFreqType;

typedef struct _SaftSearch SaftSearch;

struct _SaftSearch
{
  SaftSpectrum     *spectrum;
  SaftSequence     *query;
  SaftAlphabet     *alphabet;
  SaftHTable       *htable;
  double           *letters_frequencies;
  unsigned int     *letters_counts;
  SaftResult       *results;
  SaftResult      **sorted_results;
  SaftStatisticType statistic;
  unsigned int      word_size;
  unsigned int      n_results;
  SaftFreqType      freq_type;
};

SaftSearch* saft_search_new_spectrum    (SaftSpectrum     *spec,
                                         SaftStatisticType statistic);

SaftSearch* saft_search_new_query       (SaftSequence     *query,
                                         SaftStatisticType statistic,
                                         unsigned int      word_size,
                                         SaftFreqType      freq_type,
                                         const double     *letters_frequencies);

SaftSearch* saft_search_new             (SaftStatisticType statistic,
                                         unsigned int      word_size,
                                         SaftFreqType      freq_type);

void        saft_search_free            (SaftSearch       *search);

void        saft_search_add_subject     (SaftSearch       *search,
                                         SaftSequence     *subject);

void        saft_search_compute_pvalues (SaftSearch       *search);

#ifdef __cplusplus
}
#endif

#endif /* __SAFT_SEARCH_H__ */

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

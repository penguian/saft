/* safthash.c
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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "safthash.h"
#include "safterror.h"


#define SAFT_HTABLE_SIZE 16384

static unsigned int saft_get_high_bit (unsigned int x);


SaftHNode*
saft_hnode_new ()
{
  SaftHNode *node;

  node                = malloc (sizeof (*node));
  node->seq           = NULL;
  node->next          = NULL;
  node->count_query   = 0;
  node->count_subject = 0;

  return node;
}

void
saft_hnode_free (SaftHNode *node)
{
  if (node)
    {
      if (node->next)
        saft_hnode_free (node->next);
      free (node);
    }
}

SaftHTable*
saft_htable_new (SaftAlphabet *alphabet,
                 unsigned int  word_size)
{
  SaftHTable *table;

  table            = malloc (sizeof (*table));
  table->alphabet  = alphabet;
  table->size      = SAFT_HTABLE_SIZE; /* FIXME be more clever here */
  table->shift     = saft_get_high_bit (alphabet->size) + 1;
  table->table     = malloc (table->size * sizeof (*table->table));
  table->word_size = word_size;
  table->hmask     = ~0;

  if (table->word_size * table->shift < sizeof (table->hmask) * 8)
    table->hmask >>= sizeof (table->hmask) * 8 - table->word_size * table->shift;

  memset (table->table, 0, table->size * sizeof(*table->table));

  return table;
}

void
saft_htable_clear (SaftHTable *table)
{
  unsigned int i;

  for (i = 0; i < table->size; i++)
    saft_hnode_free (table->table[i]);
  memset (table->table, 0, table->size * sizeof(*table->table));
}

void
saft_htable_free (SaftHTable *table)
{
  unsigned int i;

  if (table)
    {
      for (i = 0; i < table->size; i++)
        saft_hnode_free (table->table[i]);
      free (table->table);
      free (table);
    }
}

void
saft_htable_add_spectrum (SaftHTable   *table,
                          SaftSpectrum *spec)
{
  SaftLetter   *word;
  unsigned int i;
  unsigned int hash = 0;
  unsigned int hash_prefix = 0;
  unsigned int idx;
  unsigned int word_size = spec->word_size;
  unsigned int alphabet_size = spec->alphabet->size;
  char        *letters = spec->alphabet->letters;
  unsigned int nrows = pow(alphabet_size, word_size - 1);
  unsigned int ncols = alphabet_size;
  
  // for now, we assume that table->word_size == spec->word_size.
  if (table->word_size != word_size)
    {
      saft_error ("Word size mismatch: table: %d, spectrum: %d", table->word_size, word_size);
      exit(1);
    }
  if (spec->frequencies->nrows != nrows)
    {
      saft_error ("Mismatch in number of rows: spectrum: %d, calculated: %d", spec->frequencies->nrows, nrows);
      exit(1);
    }
  if (spec->frequencies->ncols != ncols)
    {
      saft_error ("Mismatch in number of cols: spectrum: %d, calculated: %d", spec->frequencies->ncols, ncols);
      exit(1);
    }
   
  word = malloc(word_size * sizeof(SaftLetter));
  
  for (unsigned int row = 0; row != nrows; row++)
    {
      // Set prefix to be the sequence of letters corresponding to row.
      unsigned int value = row;
      unsigned int ch; 
      hash_prefix = 0;
      for (i = word_size - 2; i != -1; --i)
        {
          ch = value % alphabet_size + 1;
          word[i] = ch;
          value /= alphabet_size;
        }
      for (unsigned int col = 0; col != ncols; col++)
        {
          ch = col + 1;
          word[word_size - 1] = ch;
          idx = saft_htable_hash (table, word);
          SaftHNode *node;
          for (node = table->table[idx]; node; node = node->next)
            if (saft_htable_cmp (table, node, word))
              {
                saft_error ("Word found in table: %.*s", 
                            word_size, 
                            saft_sequence_letters_to_string(word, spec->alphabet, word_size));
                exit(1);
              }
          node               = saft_hnode_new ();
          node->seq          = malloc(word_size * sizeof(SaftLetter));
          for (i = 0; i != word_size; i++)
            node->seq[i] = word[i];
          node->count_query  = spec->frequencies->array[row][col];
          node->next         = table->table[idx];
          table->table[idx]  = node;
        }
    }
}

void
saft_htable_add_query (SaftHTable   *table,
                       SaftSequence *seq)
{
  SaftSegment *segment;
  SaftLetter  *start;
  unsigned int i;
  unsigned int hash = 0;
  unsigned int idx;

  for (segment = seq->segments; segment; segment = segment->next)
    {
      if (table->word_size > segment->size)
        continue;

      start = segment->seq - 1;
      for (i = 1; i < table->word_size; i++)
        hash = (hash << table->shift) ^ *++start;

      start = segment->seq;
      i     = table->word_size - 1;
      do
        {
          SaftHNode *node;

          hash <<= table->shift;
          hash  ^= segment->seq[i];
          hash  &= table->hmask;
          idx    = hash % SAFT_HTABLE_SIZE;

          for (node = table->table[idx]; node; node = node->next)
            if (saft_htable_cmp (table, node, start))
              {
                node->count_query++;
                goto found;
              }
          node               = saft_hnode_new ();
          node->seq          = start;
          node->count_query  = 1;
          node->next         = table->table[idx];
          table->table[idx]  = node;
found:
          ++i;
          ++start;
        }
      while (i < segment->size);
    }
}

void
saft_htable_add_subject (SaftHTable   *table,
                         SaftSequence *seq)
{
  SaftSegment *segment;
  SaftLetter  *start;
  unsigned int i;
  unsigned int hash = 0;
  unsigned int idx;

  for (segment = seq->segments; segment; segment = segment->next)
    {
      if (table->word_size > segment->size)
        continue;

      start = segment->seq - 1;
      for (i = 1; i < table->word_size; i++)
        hash = (hash << table->shift) ^ *++start;

      start = segment->seq;
      i     = table->word_size - 1;
      do
        {
          SaftHNode *node;

          hash <<= table->shift;
          hash  ^= segment->seq[i];
          hash  &= table->hmask;
          idx    = hash % SAFT_HTABLE_SIZE;

          bool found = false;
          for (node = table->table[idx]; node; node = node->next)
            if (saft_htable_cmp (table, node, start))
              {
                node->count_subject++;
                found = true;
                break;
              }
          if (!found)
            {
              printf("Word not found in table: %.*s, index %5d, hash %5d\n", 
                     table->word_size,
                     saft_sequence_letters_to_string(start, table->alphabet, table->word_size),
                     idx,
                     saft_htable_hash (table, start)
                    );
            }
          ++i;
          ++start;
        }
      while (i < segment->size);
    }
}

void
saft_htable_clear_subject (SaftHTable *table)
{
  unsigned int i;

  for (i = 0; i < table->size; i++)
    {
      SaftHNode *node;
      for (node = table->table[i]; node; node = node->next)
        node->count_subject = 0;
    }
}

unsigned int
saft_htable_hash (SaftHTable *table,
                   SaftLetter *start)
{
  unsigned int ret = *start;
  unsigned int i;

  for (i = 1; i < table->word_size; i++)
    ret = (ret << table->shift) ^ *++start;

  return ret % SAFT_HTABLE_SIZE;
}

int
saft_htable_cmp (SaftHTable *table,
                 SaftHNode  *node,
                 SaftLetter *start)
{
  /*
  return !memcmp (start, node->seq, table->word_size);
  */
  unsigned int i;
  SaftLetter  *tmp = node->seq - 1;

  --start;
  for (i = 0; i < table->word_size; i++)
    if (*++start != *++tmp)
      return 0;

  return 1;
}

double
saft_htable_d2 (SaftHTable *table)
{
  unsigned int i;
  double d2 = 0.0;

  for (i = 0; i < table->size; i++)
    {
      SaftHNode   *node;
      for (node = table->table[i]; node; node = node->next)
        d2 += node->count_query * node->count_subject;
    }

  return d2;
}

double       
saft_htable_d2c   (SaftHTable     *table,
                   double         *letters_frequencies,
                   double          query_size,
                   double          subject_size)
{
  unsigned int i;
  unsigned int j;
  double d2c = 0.0;

  for (i = 0; i < table->size; i++)
    {
      SaftHNode   *node;
      SaftLetter  *letter_ptr;
      double pw = 1.0;
      for (node = table->table[i]; node; node = node->next)
      {
        if (node->count_query * node->count_subject != 0)
        {
          letter_ptr = node->seq - 1;
          for (j = 0; j < table->word_size; j++)
            pw *= letters_frequencies[*++letter_ptr - 1]; 
          d2c += (node->count_query - query_size*pw) * (node->count_subject - subject_size*pw);
        }
      }
    }

  return d2c;
}

double
saft_htable_d2dag (SaftHTable *table,
                   double     *letters_frequencies)
{
  unsigned int i;
  unsigned int j;
  double d2dag = 0.0;

  for (i = 0; i < table->size; i++)
    {
      SaftHNode   *node;
      SaftLetter  *letter_ptr;
      double pw = 1.0;
      for (node = table->table[i]; node; node = node->next)
      {
        if (node->count_query * node->count_subject != 0)
        {
          letter_ptr = node->seq - 1;
          // Is this the right mapping from letters stored in seq to 
          // letter indices into letters_frequencies ?
          for (j = 0; j < table->word_size; j++)
            pw *= letters_frequencies[*++letter_ptr - 1]; 
          d2dag += node->count_query * node->count_subject / pw;
        }
      }
    }

  return d2dag;
}

SaftHNode*
saft_htable_lookup (SaftHTable *table,
                    SaftLetter *start)
{
  const unsigned int idx = saft_htable_hash (table, start);
  SaftHNode         *node;

  for (node = table->table[idx]; node; node = node->next)
    if (saft_htable_cmp (table, node, start))
      return node;

  return NULL;
}

/**
 * From JJ (Joerg Arndt) www.jjj.de
 */
static unsigned int
saft_get_high_bit (unsigned int x)
{
  unsigned int r = 0;

  if (x & 0xffff0000)
    {
      x >>= 16;
      r  += 16;
    }
  if (x & 0x0000ff00)
    {
      x >>= 8;
      r  += 8;
    }
  if (x & 0x000000f0)
    {
      x >>= 4;
      r  += 4;
    }
  if (x & 0x0000000c)
    {
      x >>= 2;
      r  += 2;
    }
  if (x & 0x00000002)
    r += 1;

  return r;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

/* saftspectrum.c
 * Copyright (C) 2013  Sylvain FORET and Paul LEOPARDI
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

#include "saftspectrum.h"

/************/
/* Spectrum */
/************/

SaftSpectrum*
saft_spectrum_new (void)
{
  SaftSpectrum *spec;

  spec               = malloc (sizeof (*spec));
  spec->alphabet     = NULL;
  spec->word_size    = 0;
  spec->frequencies  = NULL;

  return spec;
}

void
saft_spectrum_free (SaftSpectrum *spec)
{
  if (spec)
    {
      if (spec->frequencies)
        saft_matrix_free (spec->frequencies);
      free (spec);
    }
}

SaftSpectrum* 
saft_spectrum_read  (const char   *filename, 
                     SaftAlphabet *alphabet,
                     unsigned int  word_size)
{
  SaftSpectrum *spec = saft_spectrum_new ();
  spec->alphabet     = alphabet;
  spec->word_size    = word_size;
  spec->frequencies  = saft_matrix_read (filename);
  
  return spec;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

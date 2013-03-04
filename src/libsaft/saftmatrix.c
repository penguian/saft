/* saftmatrix.c
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

//#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "safterror.h"
#include "saftmatrix.h"
#include "mmio.h"

SaftMatrix*
saft_matrix_new ()
{
  SaftMatrix *result;

  result        = malloc (sizeof (*result));
  result->nrows = 0;
  result->ncols = 0;
  result->array = NULL;

  return result;
}

void
saft_matrix_free (SaftMatrix *matrix)
{
  if (matrix)
    {
      for (int row = 0; row != matrix->nrows; row++)
        free (matrix->array[row]); 
      free (matrix);
    }
}

SaftMatrix*
saft_matrix_read (const char *filename)
{
  // This function uses code from http://math.nist.gov/MatrixMarket/mmio/c/example_read.c
 
  FILE*       in       = NULL;
  MM_typecode matcode;
  int         nrows, ncols;

  SaftMatrix *result = saft_matrix_new();

  if ((in = fopen (filename, "r")) == NULL)
    {
      saft_error ("Couldn't open `%s'", filename);
      exit(1);
    }
  if (mm_read_banner(in, &matcode) != 0)
    {
      saft_error ("Could not read Matrix Market banner");
      exit(1);
    }

  // Check if Matrix Market data type is supported.
  if ( !( mm_is_matrix(matcode) && (mm_is_dense(matcode) || mm_is_array(matcode)) &&
         (mm_is_real(matcode) || mm_is_integer(matcode)) ) )
    {
      saft_error ("Market Market type [%s] is not supported", 
                  mm_typecode_to_str(matcode));
      exit(1);
    }

  // Determine the size of the matrix.
  if (mm_read_mtx_array_size(in, &nrows, &ncols) !=0)
    { 
      saft_error ("Could not read Matrix Market array size");
      exit(1);
    }
  result->nrows = nrows;
  result->ncols = ncols;
 
  // Reserve memory for the matrix.
  result->array = (double **) malloc(nrows * sizeof(double*));
  for (int row = 0; row != nrows; row++)
    result->array[row] = (double *) malloc(ncols * sizeof(double*));

  // Read in the value of the matrix.
  for (int col = 0; col != result->ncols; col++)
    for (int row = 0; row != result->nrows; row++)
      if (fscanf(in, "%lg\n", &(result->array[row][col])) != 1)
        { 
          saft_error ("Could not read Matrix Market array");
          exit(1);
        }

  if (in !=stdin) 
    fclose(in);

  return result;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

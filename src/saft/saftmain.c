/* saftmain.c
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


#define _GNU_SOURCE
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "saftstatistictype.h"
#include "safterror.h"
#include "saftfasta.h"
#include "saftsearch.h"


typedef enum
{
  SAFTN = 0,
  SAFTP,
  SAFTX,
  TSAFTN,
  TSAFTX,
  NB_SAFT_PROGRAMS,
  SAFT_UNKNOWN_PROGRAM
}
SaftProgramType;

static char *saft_program_names[NB_SAFT_PROGRAMS] =
{
  [SAFTN]  = "saftn",
  [SAFTP]  = "saftp",
  [SAFTX]  = "saftx",
  [TSAFTN] = "tsaftn",
  [TSAFTX] = "tsaftx",
};

typedef struct _SaftOptDesc SaftOptDesc;

struct _SaftOptDesc
{
  char *name;
  int   has_arg;
  int   val;
  char *description;
};

typedef struct _SaftOptions SaftOptions;

struct _SaftOptions
{
  char             *input_path;
  char             *db_path;
  char             *output_path;
  double            p_max;
  unsigned int      word_size;
  unsigned int      verbosity;
  int               show_max;
  SaftProgramType   program;
  SaftStatisticType statistic;
  int              lockstep;
  int              raw;
};

static SaftOptions* saft_options_new  (void);

static void         saft_options_free (SaftOptions *options);

static SaftOptDesc opt_desc[] =
{
    /* Program information */
    {"help",     no_argument,       'h', "Prints a short help"},
    {"version",  no_argument,       'V', "Prints the program's version"},
    /* General options */
    {"verbose",  no_argument,       'v', "Increases the program's verbosity"},
    /* FIXME multi threading options */
    /* Input / Output */
    {"input",    required_argument, 'i', "Path to the input file"},
    {"database", required_argument, 'd', "Path to the database to search"},
    {"output",   required_argument, 'o', "Path to the output file"},
    /* Search setup */
    {"program",  required_argument, 'p', "Program to use"},
    {"statistic",required_argument, 's', "Statistic to use (default d2)"},
    {"wordsize", required_argument, 'w', "Word size"},
    {"showmax",  required_argument, 'b', "Maximum number of results to show"},
    {"pmax",     required_argument, 'e', "Show results with a p-value smaller than this"},
    {"lockstep", no_argument,       'l', "Step through query and subject in lock step"},
    {"raw",      no_argument,       'r', "Show statistic results only - do not calculate p-values"},
    /* FIXME add option for the frequencies */
    /* FIXME add option to choose the strand(s) of the query */
    {NULL, 0, 0, NULL}
};

static struct option*     saft_main_get_options        (void);

static void               saft_main_usage              (char        *argv0);

static void               saft_main_help               (char        *argv0);

static void               saft_main_version            (void);

static SaftProgramType    saft_main_program_type       (char        *program);

static SaftStatisticType  saft_main_statistic_type     (char        *statistic);

static int                saft_main_search             (SaftOptions *options);

static void               saft_main_write_search       (SaftOptions *options,
                                                        SaftSearch  *search,
                                                        FILE        *stream);
static void               saft_main_write_search_raw   (SaftOptions *options,
                                                        SaftSearch  *search,
                                                        FILE        *stream);

int
main (int    argc,
      char **argv)
{
  struct option  *long_options = saft_main_get_options ();
  SaftOptions    *options      = saft_options_new ();
  int             ret          = 0;
  char           *endptr;
  options->lockstep            = 0;
  options->raw                 = 0;

  while (1)
    {
      int option_index = 0;
      int c;

      c = getopt_long (argc,
                       argv,
                       "hV" "v" "i:d:o:" "p:s:w:b:e:",
                       long_options,
                       &option_index);
      if (c == -1)
        break;

      switch (c)
        {
          case 'h':
              saft_main_help (argv[0]);
              goto cleanup;
          case 'V':
              saft_main_version ();
              goto cleanup;
          case 'v':
              options->verbosity++;
              break;
          case 'i':
              options->input_path = optarg;
              break;
          case 'd':
              options->db_path = optarg;
              break;
          case 'o':
              options->output_path = optarg;
              break;
          case 'p':
              options->program = saft_main_program_type (optarg);
              if (options->program == SAFT_UNKNOWN_PROGRAM)
                {
                  ret = 1;
                  saft_error ("Wrong `--program (-p)' argument: unknown program `%s'", optarg);
                  goto cleanup;
                }
              break;
          case 's':
              options->statistic = saft_main_statistic_type (optarg);
              if (options->statistic == SAFT_UNKNOWN_STATISTIC)
                {
                  ret = 1;
                  saft_error ("Wrong `--statistic (-s)' argument: unknown statistic `%s'", optarg);
                  goto cleanup;
                }
              break;
          case 'w':
              options->word_size = strtol (optarg, &endptr, 10);
              if (errno == ERANGE || errno == EINVAL || *endptr != '\0')
                {
                  saft_error ("Wrong `--wordsize (-w)' argument: could not convert `%s' to an integer", optarg);
                  ret = 1;
                  goto cleanup;
                }
              break;
          case 'b':
              options->show_max = strtol (optarg, &endptr, 10);
              if (errno == ERANGE || errno == EINVAL || *endptr != '\0')
                {
                  saft_error ("Wrong `--showmax (-b)' argument: could not convert `%s' to an integer", optarg);
                  ret = 1;
                  goto cleanup;
                }
              break;
          case 'e':
              options->p_max = strtod (optarg, &endptr);
              if (errno == ERANGE || *endptr != '\0')
                {
                  saft_error ("Wrong `--pmax (-e)' argument: could not convert `%s' to a double", optarg);
                  ret = 1;
                  goto cleanup;
                }
              break;
          default:
              saft_main_usage (argv[0]);
              ret = 1;
              goto cleanup;
          case 'l':
              options->lockstep = 1;
              break;
          case 'r':
              options->raw = 1;
              break;
        }
    }
  if (options->program == SAFT_UNKNOWN_PROGRAM)
    {
      saft_error ("Program type was not provided, use the `--program' or `-p' option");
      ret = 1;
      goto cleanup;
    }
  if (options->word_size == 0)
    {
      if (options->program == SAFTN)
        options->word_size = 7;
      else
        options->word_size = 3;
    }
  saft_main_search (options);

cleanup:
  free (long_options);
  saft_options_free (options);

  return ret;
}

static struct option*
saft_main_get_options ()
{
  struct option *long_options;
  int            nb_options;
  int            i;

  for (nb_options = 0; opt_desc[nb_options].name; nb_options++);

  long_options = malloc ((nb_options + 1) * sizeof (*long_options));

  for (i = 0; i < nb_options; i++)
    {
      long_options[i].name    = opt_desc[i].name;
      long_options[i].has_arg = opt_desc[i].has_arg;
      long_options[i].flag    = NULL;
      long_options[i].val     = opt_desc[i].val;
    }
  long_options[i].name    = NULL;
  long_options[i].has_arg = 0;
  long_options[i].flag    = NULL;
  long_options[i].val     = 0;

  return long_options;
}

static void
saft_main_usage (char *argv0)
{
  char *prog = basename (argv0);
  printf ("Usage: %s OPTIONS\n", prog);
  printf ("Try %s -h for help\n", prog);
}

static void
saft_main_help (char *argv0)
{
  char        *prog    = basename (argv0);
  size_t       longest = 0;
  unsigned int i;

  for (i = 0; opt_desc[i].name; i++)
    {
      const size_t l = strlen (opt_desc[i].name);
      if (l > longest)
        longest = l;
    }

  printf ("SAFT (Sequence Alignment Free Tool)\n");
  printf ("Usage: %s OPTIONS\n", prog);
  printf ("Where OPTIONS are:\n");

  for (i = 0; opt_desc[i].name; i++)
    printf ("  --%-*s (-%c) : %s\n",
            (int) longest,
            opt_desc[i].name,
            opt_desc[i].val,
            opt_desc[i].description);
}

static void
saft_main_version (void)
{
  printf ("SAFT version " SAFT_VERSION "\n");
}

static SaftProgramType
saft_main_program_type (char *program)
{
  unsigned int i;
  for (i = 0; i < NB_SAFT_PROGRAMS; i++)
    if (!strcmp (program, saft_program_names[i]))
      return i;
  return SAFT_UNKNOWN_PROGRAM;
}

static SaftStatisticType
saft_main_statistic_type (char *statistic)
{
  unsigned int i;
  for (i = 0; i < NB_SAFT_STATISTICS; i++)
    if (!strcmp (statistic, saft_statistic_names[i]))
      return i;
  return SAFT_UNKNOWN_STATISTIC;
}

static SaftOptions*
saft_options_new ()
{
  SaftOptions *options;

  options              = malloc (sizeof (*options));
  options->input_path  = NULL;
  options->db_path     = NULL;
  options->output_path = NULL;
  options->p_max       = 5e-2;
  options->word_size   = 0;
  options->verbosity   = 0;
  options->show_max    = 50;
  options->program     = SAFT_UNKNOWN_PROGRAM;
  options->statistic   = SAFT_D2;

  return options;
}

static void
saft_options_free (SaftOptions *options)
{
  if (options)
    free (options);
}

static int
saft_main_search (SaftOptions *options)
{
  SaftAlphabet *alphabet;
  SaftFasta   **fasta_queries;
  SaftFasta   **fasta_subjects;
  FILE         *out_stream;
  unsigned int  n_fasta_queries;
  unsigned int  n_fasta_subjects;
  unsigned int  i;
  unsigned int  j;

  switch (options->program)
    {
      case SAFTN:
          alphabet = &SaftAlphabetDNA;
          break;
      case SAFTP:
          alphabet = &SaftAlphabetProtein;
          break;
      default:
      saft_error ("Only `saftp' and `saftn' are (partially) implemented");
      return 1;
    }

  if (options->output_path == NULL)
    out_stream = stdout;
  else if ((out_stream = fopen (options->output_path, "w")) == NULL) 
      {
        saft_error ("Could not open output file");
        return 1;
      }
  /* FIXME This requires loading the whole stuff into memory, probably not the
   * best thing to do if there are many queries or if the database is very big
   */
  fasta_queries  = saft_fasta_read (options->input_path,
                                    &n_fasta_queries);
  fasta_subjects = saft_fasta_read (options->db_path,
                                    &n_fasta_subjects);
  for (i = 0; i < n_fasta_queries; i++)
    {
      SaftSequence *query  = saft_fasta_to_seq (fasta_queries[i],
                                                alphabet);
      SaftSearch   *search = saft_search_new (query,
                                              options->statistic,
                                              options->word_size,
                                              SAFT_FREQ_UNIFORM,
                                              NULL);
      if (options->lockstep)
        if (i == n_fasta_subjects)
          break;
        else
        {
          SaftSequence *subject = saft_fasta_to_seq (fasta_subjects[i],
                                                     alphabet);
          saft_search_add_subject (search, subject);
          saft_sequence_free (subject);
        }
      else
        for (j = 0; j < n_fasta_subjects; j++)
          {
            SaftSequence *subject = saft_fasta_to_seq (fasta_subjects[j],
                                                       alphabet);
            saft_search_add_subject (search, subject);
            saft_sequence_free (subject);
          }
      if (options->raw)
        saft_main_write_search_raw (options,
                                    search,
                                    out_stream);
      else
      {
        saft_search_compute_pvalues (search);
        saft_main_write_search (options,
                                search,
                                out_stream);
      }
      saft_search_free (search);
    }
  if (options->output_path == NULL)
    fclose (out_stream);
  return 0;
}

static void
saft_main_write_search (SaftOptions *options,
                        SaftSearch  *search,
                        FILE        *stream)
{
  unsigned int i;

  if (options->show_max <= 0 ||
      options->show_max > search->n_results)
    options->show_max = search->n_results;

  fprintf (stream, "Query: %s program: %s word size: %d\n",
           search->query->name,
           saft_program_names[options->program],
           search->word_size);
  for (i = 0;
       i < options->show_max &&
       search->sorted_results[i]->p_value_adj <= options->p_max;
       i++)
    {
      fprintf (stream, "  Hit: %s %s: %11.1f adj.p.val: %.5e p.val: %.5e\n",
               search->sorted_results[i]->name,
               saft_statistic_names[search->statistic],
               search->sorted_results[i]->s_value,
               search->sorted_results[i]->p_value_adj,
               search->sorted_results[i]->p_value);
    }
  if (i == 0)
    fprintf (stream, "No hit found\n");
}

static void
saft_main_write_search_raw (SaftOptions *options,
                            SaftSearch  *search,
                            FILE        *stream)
{
  unsigned int i;

  if (options->show_max <= 0 ||
      options->show_max > search->n_results)
    options->show_max = search->n_results;

  fprintf (stream, "Query: %s\n",
           search->query->name);
  SaftResult  *result = search->results;
  for (i = 0;
       result && (i < options->show_max);
       i++)
    {
      fprintf (stream, "  Hit: %s %s: %11.1f\n",
               result->name,
               saft_statistic_names[search->statistic],
               result->s_value);
      result = result->next;
    }
  if (i == 0)
    fprintf (stream, "No hit found\n");
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

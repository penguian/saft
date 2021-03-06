/* saftsearchenginegeneric.c
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
#include <stdio.h>
#include <string.h>

#include "saftfasta.h"
#include "saftsearchengines.h"
#include "saftstats.h"


/*************************/
/* Generic Search Engine */
/*************************/

typedef struct _SearchEngineGeneric SearchEngineGeneric;

struct _SearchEngineGeneric
{
  SaftSearchEngine search_engine;
};


static void        search_engine_generic_free                 (SaftSearchEngine *engine);

static SaftSearch* search_engine_generic_search_two_sequences (SaftSearchEngine *engine,
                                                               SaftSequence     *query,
                                                               SaftSequence     *subject);

static SaftSearch* search_engine_generic_search_all           (SaftSearchEngine *engine,
                                                               const char       *query_path,
                                                               const char       *db_path);

SaftSearchEngine*
saft_search_engine_generic_new (SaftOptions *options)
{
  SearchEngineGeneric *engine;

  engine                                     = malloc (sizeof (*engine));
  engine->search_engine.options              = options;
  engine->search_engine.search_two_sequences = search_engine_generic_search_two_sequences;
  engine->search_engine.search_all           = search_engine_generic_search_all;
  engine->search_engine.free                 = search_engine_generic_free;

  return (SaftSearchEngine*)engine;
}

static void
search_engine_generic_free (SaftSearchEngine *engine)
{
}

static SaftSearch*
search_engine_generic_search_two_sequences (SaftSearchEngine *engine,
                                            SaftSequence     *query,
                                            SaftSequence     *subject)
{
  SearchEngineGeneric *se;

  se = (SearchEngineGeneric*) engine;
  se++;

  return NULL;
}

static SaftSearch*
search_engine_generic_search_all (SaftSearchEngine *engine,
                                  const char       *query_path,
                                  const char       *db_path)
{
  SearchEngineGeneric *se;

  se = (SearchEngineGeneric*) engine;
  se++;

  return NULL;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

/* saftopt.h
 * Copyright (C) 2008  Sylvain FORET
 * Copyright (C) 2014  Paul LEOPARDI
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

#ifndef __SAFTOPT_H__
#define __SAFTOPT_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _SaftOptDesc SaftOptDesc;

struct _SaftOptDesc
{
  char *name;
  int   has_arg;
  int   val;
  char *description;
};

struct option*   saft_opt_get_options   (SaftOptDesc *opt_desc);

char*            saft_opt_get_optstring (SaftOptDesc *opt_desc);

void             saft_opt_usage         (char        *argv0);

void             saft_opt_help          (char        *argv0,
                                         SaftOptDesc *opt_desc,
                                         char        *message);

#ifdef __cplusplus
}
#endif

#endif /* __SAFTOPT_H__ */

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

/* saftstatistictype.h
 * Copyright (C) 2012  Sylvain FORET and Paul LEOPARDI
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

#ifndef __SAFT_STATISTICTYPE_H__
#define __SAFT_STATISTICTYPE_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
  SAFT_D2 = 0,
  SAFT_D2AST,
  SAFT_D2C,
  SAFT_D2DAG,
  SAFT_D2W,
  SAFT_D2WC,
  NB_SAFT_STATISTICS,
  SAFT_UNKNOWN_STATISTIC
}
SaftStatisticType;

static char *saft_statistic_names[NB_SAFT_STATISTICS] =
{
  [SAFT_D2]    = "d2",
  [SAFT_D2AST] = "d2ast",
  [SAFT_D2C]   = "d2c",
  [SAFT_D2DAG] = "d2dag",
  [SAFT_D2W]   = "d2w",
  [SAFT_D2WC]  = "d2wc",
};

#ifdef __cplusplus
}
#endif

#endif /* __SAFT_STATISTICTYPE_H__ */

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

/* saftutils.h
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

#ifndef __SAFT_ERROR_H__
#define __SAFT_ERROR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __GNUC__

#define SAFT_LIKELY(x)   __builtin_expect ((x), 1)
#define SAFT_UNLIKELY(x) __builtin_expect ((x), 0)

#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif

#endif /* __SAFT_ERROR_H__ */

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

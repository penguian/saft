/* test_harness.c
 * Copyright (C) 2014  Paul Leopardi
 *
 * This file is part of SAFT.
 *
 * SAFT is free software: you can redistribute it and/or modify
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

#include <stdio.h>

#include "test_harness.h"

int
run_test(int (*test_function)(), char *test_name)
{
  int test_error = (*test_function)();
  printf("%s: %s\n", test_name, test_error ?  "failure" : "success");
  return test_error;
}

/* vim:ft=c:expandtab:sw=4:ts=4:sts=4:cinoptions={.5s^-2n-2(0:
 */

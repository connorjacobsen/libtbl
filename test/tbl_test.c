/*-
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Connor Jacobsen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>

#include "test_unit.h"
#include "../tbl.h"

int tests_run = 0;

static char*
test_mk_pair(void)
{
  pair_t* p = mk_pair("foo", (void*) 42);
  expect("pair->key != foo", strcmp("foo", p->key) == 0);
  expect("pair->value != 42", (int) p->value == 42);

  return 0;
}

static char*
test_pair_key(void)
{
  pair_t* p = mk_pair("foo", (void*) 42);
  expect("pair_key != foo", strcmp(pair_key(p), "foo") == 0);

  return 0;
}

static char*
test_pair_value(void)
{
  pair_t* p = mk_pair("foo", (void*) 42);
  expect("pair_value != 42", (int) pair_value(p) == 42);

  return 0;
}

static char*
test_tbl(void)
{
  tbl_t* tt = mk_tbl();

  expect("tbl_size != 0", tbl_size(tt) == 0);
  tbl_put(tt, "foo", (void*) 42);
  expect("tbl_get('foo') != 42", (int) tbl_get(tt, "foo") == 42);

  return 0;
}

static char*
all_tests(void)
{
  run_test(test_mk_pair);
  run_test(test_pair_key);
  run_test(test_pair_value);
  run_test(test_tbl);

  return 0;
}

int
main(int argc, char** argv)
{
  char* result = all_tests();
  if (result != 0)
    printf("ERROR: %s\n", result);
  else
    printf("ALL TESTS PASSED!\n");

  return result != 0;
}

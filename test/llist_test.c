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
#include "test_unit.h"

#include "../llist.h"

int tests_run = 0;

static char*
test_llist_empty(void)
{
  llist_t* ll = mk_llist();
  expect("llist_empty when empty", llist_empty(ll));
  return 0;
}

static char*
test_llist_size(void)
{
  llist_t* ll = mk_llist();
  expect("llist_size when size==0", llist_size(ll) == 0);

  llist_push(ll, (void*) 5);
  expect("llist_size when size==1", llist_size(ll) == 1);

  return 0;
}

static char*
test_llist_push(void)
{
  llist_t* ll = mk_llist();
  
  int i;
  for (i = 0; i < 5; ++i)
    llist_push(ll, (void*) i);

  expect("llist_push", llist_size(ll) == 5);
  return 0;
}

static char*
test_llist_pop(void)
{
  llist_t* ll = mk_llist();

  int i;
  for (i = 0; i < 5; ++i)
    llist_push(ll, (void*) i);

  expect("llist_pop != 4", (int) llist_pop(ll) == 4);
  expect("llist_pop, size != 3", llist_size(ll) == 4);
  expect("llist_pop != 3", (int) llist_pop(ll) == 3);
  expect("llist_pop, size != 2", llist_size(ll) == 3);

  return 0;
}

static char*
test_llist_delete(void)
{
  llist_t* ll = mk_llist();

  int i;
  for (i = 0; i < 5; ++i)
    llist_push(ll, (void*) i);

  expect("llist_delete != 2", (int) llist_delete(ll, 2));
  expect("llist_delete size != 4", llist_size(ll));
  expect("llist_delete not shifted", (int) ll->data[2] == 3);

  return 0;
}

static char*
test_llist_at(void)
{
  llist_t* ll = mk_llist();

  int i;
  for (i = 0; i < 5; ++i)
    llist_push(ll, (void*) i);

  expect("llist_at(0)", (int) llist_at(ll, 0) == 0);
  expect("llist_at(1)", (int) llist_at(ll, 1) == 1);
  expect("llist_at(2)", (int) llist_at(ll, 2) == 2);
  expect("llist_at(3)", (int) llist_at(ll, 3) == 3);
  expect("llist_at(4)", (int) llist_at(ll, 4) == 4);
  expect("llist_at(5)", llist_at(ll, 5) == NULL);

  return 0;
}

static char*
all_tests(void)
{
  run_test(test_llist_empty);
  run_test(test_llist_size);
  run_test(test_llist_push);
  run_test(test_llist_pop);
  run_test(test_llist_delete);
  run_test(test_llist_at);

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


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

#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <string.h>

#define INITIAL_LLIST_CAPACITY 32

typedef struct llist {
  void**   data;        /* llist data */
  uint32_t head;        /* index of llist head */
  uint32_t tail;        /* index of llist tail */
  uint32_t size;        /* number of elements in llist */
  uint32_t nalloc;      /* number of bytes allocated */
} llist_t;

llist_t* mk_llist(void);
void free_llist(llist_t*);
void llist_realloc(llist_t*);

uint32_t llist_size(llist_t*);
bool llist_empty(llist_t*);

void* llist_push(llist_t*, void*);
void* llist_pop(llist_t*);

/* delete at index */
void* llist_delete(llist_t*, uint32_t);

void* llist_at(llist_t*, uint32_t);

#endif /* _LLIST_H_ */


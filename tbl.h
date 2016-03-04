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

#ifndef _TBL_H_
#define _TBL_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#include "llist.h"

#define BUCKET_COUNT 64

typedef struct pair {
  char* key;
  void* value;
} pair_t;

typedef struct tbl {
  uint32_t size;
  uint32_t nalloc;
  llist_t** buckets;
} tbl_t;

tbl_t* mk_tbl(void);
void free_tbl(tbl_t*);

pair_t* mk_pair(char*, void*);
void free_pair(pair_t*);

char* pair_key(pair_t*);
void* pair_value(pair_t*);

uint32_t tbl_hash(char*);

void* tbl_get(tbl_t*, char*);
void* tbl_put(tbl_t*, char*, void*);
uint32_t tbl_size(tbl_t*);
bool tbl_contains(tbl_t*, char*);

/* Murmur2 hash */
unsigned int MurmurHash2(void* key, int, unsigned int);

#endif /* _TBL_H_ */


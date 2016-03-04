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

#include "tbl.h"

pair_t*
mk_pair(char* key, void* value)
{
  pair_t* p = malloc(sizeof(pair_t));
  assert(p != NULL);
  p->key = malloc(sizeof(char) * (strlen(key) + 1));
  strcpy(p->key, key);
  p->value = value;

  return p;
}

void
free_pair(pair_t* p)
{
  free(p);
}

char*
pair_key(pair_t* p)
{
  return p->key;
}

void*
pair_value(pair_t* p)
{
  return p->value;
}

tbl_t*
mk_tbl(void)
{
  tbl_t* tt = malloc(sizeof(tbl_t));
  tt->size = 0;
  tt->nalloc = BUCKET_COUNT;
  tt->buckets = malloc(sizeof(llist_t) * tt->nalloc);

  /* init llists */
  int i;
  for (i = 0; i < tt->nalloc; ++i)
    tt->buckets[i] = mk_llist();

  return tt;
}

void
free_tbl(tbl_t* tt)
{
  int i;
  for (i = 0; i < tt->nalloc; ++i)
    free_llist(tt->buckets[i]);

  free(tt);
}

uint32_t
tbl_size(tbl_t* tt)
{
  return tt->size;
}

uint32_t
tbl_hash(char* key)
{
  return (uint32_t) MurmurHash2((void*) key, strlen(key), 42);
}

bool
tbl_contains(tbl_t* tt, char* key)
{
  uint32_t index = tbl_hash(key) % tt->nalloc;
  llist_t* ll = tt->buckets[index];

  int i;
  for (i = 0; i < llist_size(ll); ++i)
    if (strcmp(pair_key(llist_at(ll, i)), key) == 0)
      return true;

  return false;
}

void*
tbl_put(tbl_t* tt, char* key, void* value)
{
  uint32_t index = tbl_hash(key) % tt->nalloc;
  llist_t* ll = tt->buckets[index];

  bool contains = false;
  int i;
  for (i = 0; llist_size(ll); ++i) {
    if (strcmp(pair_key(llist_at(ll, i)), key) == 0) {
      contains = true;
      break;
    }
  }

  if (contains) {
    pair_t* p = ll->data[i];
    p->value = value;
  } else {
    llist_push(ll, mk_pair(key, value));
  }

  return value;
}

void*
tbl_get(tbl_t* tt, char* key)
{
  uint32_t index = tbl_hash(key) % tt->nalloc;
  llist_t* ll = tt->buckets[index];

  int i;
  for (i = 0; i < ll->size; ++i)
    if (strcmp(pair_key(llist_at(ll, i)), key) == 0)
      return pair_value(llist_at(ll, i));

  return NULL;
}

//-----------------------------------------------------------------------------
//// MurmurHash2, by Austin Appleby
//
//// Note - This code makes a few assumptions about how your machine behaves -
//
//// 1. We can read a 4-byte value from any address without crashing
//// 2. sizeof(int) == 4
//
//// And it has a few limitations -
//
//// 1. It will not work incrementally.
//// 2. It will not produce the same results on little-endian and big-endian
////    machines.
//
unsigned int
MurmurHash2(void* key, int len, unsigned int seed)
{
  // 'm' and 'r' are mixing constants generated offline.
  // They're not really 'magic', they just happen to work well.
  unsigned int m = 0x5bd1e995;
  int r = 24;

  // Initialize the hash to a 'random' value
  unsigned int h = seed ^ len;

  // Mix 4 bytes at a time into the hash
  unsigned char * data = (unsigned char *)key;

  while(len >= 4) {
    unsigned int k = *(unsigned int *)data;

    k *= m; 
    k ^= k >> r; 
    k *= m; 
                                      
    h *= m; 
    h ^= k;

    data += 4;
    len -= 4;
  }
  // Handle the last few bytes of the input array

  switch(len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
    h *= m;
  };

  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}


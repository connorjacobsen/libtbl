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

#include "llist.h"

llist_t*
mk_llist(void)
{
  llist_t* ll = malloc(sizeof(llist_t));
  assert(ll != NULL);
  ll->nalloc = 32;
  ll->head = 0;
  ll->tail = 0;
  ll->size = 0;
  ll->data = malloc(sizeof(void*) * 32);
  return ll;
}

/* Existential question: Do I destroy all data I contain? Yes. */
void
free_llist(llist_t* ll)
{
  free(ll->data);
  free(ll);
}

/* Does not provide a mechanism to prevent integer overflow. */
void
llist_realloc(llist_t* ll)
{
  uint32_t nalloc = ll->nalloc * 2;
  void** data = malloc(sizeof(void*) * nalloc);

  int i;
  if (ll->head < ll->tail) {
    /* no wrap */
    for (i = ll->head; i < ll->size; ++i)
      data[i] = ll->data[i];
  } else {
    /* wrap */
    for (i = ll->head; i < ll->nalloc; ++i)
      data[i] = ll->data[i];
    
    int j;
    for (j = 0; j < ll->tail; ++j)
      data[i + j] = ll->data[j];
  }
  free(ll->data);
  ll->nalloc = nalloc;
  ll->data = data;
}

uint32_t
llist_size(llist_t* ll)
{
  return ll->size;
}

bool
llist_empty(llist_t* ll)
{
  return ll->size == 0;
}

void*
llist_push(llist_t* ll, void* data)
{
  if (ll->size == ll->nalloc)
    llist_realloc(ll);

  /* need to wrap if tail is at end of allocate mem */
  if (ll->tail == ll->nalloc)
    ll->tail = -1;
 
  if (ll->size == 0)
    ll->data[ll->tail] = data;
  else {
    ll->tail++;
    ll->data[ll->tail] = data;
  }
  ll->size++;

  return data;
}

void*
llist_pop(llist_t* ll)
{
  if (ll->size == 0) return NULL;

  void* data = ll->data[ll->tail];
  ll->data[ll->tail--] = NULL;
  ll->size--;
  if (ll->tail == -1)
    ll->tail = ll->size;

  return data;
}

void*
llist_delete(llist_t* ll, uint32_t index)
{
  if (index >= llist_size(ll))
    return NULL;

  void* value = ll->data[index];
  int i;
  for (i = index; i < ll->size; ++i)
    ll->data[i] = ll->data[i+1];

  /* zero-out last element */
  ll->size--;
  ll->data[ll->size] = NULL;

  return value;
}

void*
llist_at(llist_t* ll, uint32_t index)
{
  if (index >= llist_size(ll))
    return NULL;

  return ll->data[index];
}


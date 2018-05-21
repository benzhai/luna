/* Generic linked bucket routine.
 * Copyright (C) 1997, 2000 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <zebra.h>
#include "memory.h"

#include "bts_bucket.h"

#define buckethead(X) ((X) ? ((X)->head) : NULL)
#define bucketnextnode(X) ((X) ? ((X)->next) : NULL)

#if 0

#define bucketgetdata(X) ((X)->data)

/* List iteration macro. 
 * Usage: for (ALL_BTS_BUCKET_ELEMENTS (...) { ... }
 * It is safe to delete the cell using this macro.
 */
#define ALL_BUCKET_ELEMENTS(bucket,node,nextnode,data) \
  (node) = buckethead(bucket), ((data) = NULL); \
  (node) != NULL && \
    ((data) = bucketgetdata(node),(nextnode) = node->next, 1); \
  (node) = (nextnode), ((data) = NULL)

/* read-only bucket iteration macro.
 * Usage: as per ALL_BTS_BUCKET_ELEMENTS, but not safe to delete the cell Only
 * use this macro when it is *immediately obvious* the cell is not
 * deleted in the body of the loop. Does not have forward-reference overhead
 * of previous macro.
 */
#define ALL_BUCKET_ELEMENTS_RO(bucket,node,data) \
  (node) = buckethead(bucket), ((data) = NULL);\
  (node) != NULL && ((data) = bucketgetdata(node), 1); \
  (node) = bucketnextnode(node), ((data) = NULL)

#endif

void bucket_lock(bucket_t *bucket)
{
    pthread_mutex_lock(&bucket->lock);
}

void bucket_unlock(bucket_t *bucket)
{
    pthread_mutex_unlock(&bucket->lock);
}

/* Allocate new cell.  Internal use only. */
static cell_t *
cell_new (void)
{
    cell_t *cell = NULL;
	cell = malloc(sizeof (cell_t));

    if (NULL == cell) {
        return cell;
    }

    memset(cell, 0, sizeof(cell_t));

    return cell;
}

/* Free cell. */
static void
cell_free (cell_t *cell)
{
	free(cell);
}

/* Delete all cell from the bucket. */
void
bucket_delete_all_cell (bucket_t *bucket)
{
  cell_t *node;
  cell_t *next;

  assert(bucket);
  for (node = bucket->head; node; node = next)
    {
      next = node->next;
      if (bucket->del)
          (*bucket->del) (node->data);
      cell_free (node);
    }
  bucket->head = bucket->tail = NULL;
  bucket->count = 0;
}

/* Add new data to the bucket. */
berr
cell_add (bucket_t *bucket, void *val)
{
	cell_t *node = NULL;

	assert (val != NULL);

	node = cell_new ();

    if (NULL == node) {
        return E_MEMORY;
    }

	node->prev = bucket->tail;
	node->data = val;

	if (bucket->head == NULL)
        bucket->head = node;
	else
        bucket->tail->next = node;
	    bucket->tail = node;

	bucket->count++;

    return E_SUCCESS;
}

/* Delete specific date pointer from the bucket. */
void
cell_delete_by_key (bucket_t *bucket, void *key)
{
    cell_t *node;

    assert(bucket);
    assert(bucket->cmp);
    for (node = bucket->head; node; node = node->next)
    {
        if (!bucket->cmp(key, node->data))
        {
            if (node->prev)
                node->prev->next = node->next;
            else
                bucket->head = node->next;

            if (node->next)
                node->next->prev = node->prev;
            else
                bucket->tail = node->prev;

            bucket->count--;
            cell_free (node);
            return;
        }
    }
}

/* Lookup the node which has given data. */
cell_t *
cell_lookup_by_key (bucket_t *bucket, void *key)
{
    cell_t *node = NULL;

    assert(bucket);

    for (node = buckethead(bucket); node; node = bucketnextnode (node)){
        if (!bucket->cmp(key, node->data))
            return node->data;
    }
    return NULL;
}

berr
bucket_cell_add(bucket_t *bucket, void *data)
{
    berr rv = E_FAIL;
    if ((NULL == bucket) || (NULL == data)) {
        return E_PARAM;
    }

    bucket_lock(bucket);
    rv = cell_add(bucket, data);
    bucket_unlock(bucket);

    return rv;
}

berr
bucket_cell_del(bucket_t *bucket, void *key)
{
    if ((NULL == bucket) || (NULL == key)) {
        return E_PARAM;
    }

    bucket_lock(bucket);
    cell_delete_by_key(bucket, key);
    bucket_unlock(bucket);

    return E_SUCCESS;
}

void*
bucket_cell_get(bucket_t *bucket, void *key)
{
    void *data = NULL;
    assert(bucket);

    bucket_lock(bucket);
    data = cell_lookup_by_key(bucket, key);
    bucket_unlock(bucket);

    return data;
}


/* Delete all cell then free bucket itself. */
void
bucket_clean (bucket_t *bucket)
{
  assert(bucket);
  bucket_lock(bucket);
  bucket_delete_all_cell (bucket);
  bucket_unlock(bucket);
}

berr 
bucket_init(bucket_t *bucket, int (*cmp)(void *, void *), void (*del)(void *))
{
    if ((NULL == bucket) || (NULL == cmp)) {
        return E_PARAM;
    }

    memset(bucket, 0, sizeof(bucket_t));

    pthread_mutex_init(&bucket->lock, NULL);

    bucket->cmp = cmp;

    bucket->del = del;

    return E_SUCCESS;
}

/* End of file */

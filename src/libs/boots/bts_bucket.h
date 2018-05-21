#ifndef __BTS_BUCKET_H__
#define __BTS_BUCKET_H__

#include <pthread.h>

#include "boots.h"

/* cells must always contain data to be valid. Adding an empty node
 * to a bucket is invalid
 */
typedef struct cell_s
{
  struct cell_s *next;
  struct cell_s *prev;    
  /* private member, use getdata() to retrieve, do not access directly */
  void *data;
} cell_t;


typedef int (*bucket_cmp_func)(void *key, void *obj); 
typedef void (*bucket_del_func)(void *val);

typedef struct bucket_s
{
  pthread_mutex_t lock;
  cell_t *head;
  cell_t *tail;

  /* invariant: count is the number of cells in the bucket */
  unsigned int count;
    
  /*
   * Returns -1 if val1 < val2, 0 if equal?, 1 if val1 > val2.
   * Used as definition of sorted for cell_add_sort
   */
  bucket_cmp_func cmp;

  /* callback to free user-owned data when cell is deleted. supplying
   * this callback is very much encouraged!
   */
  bucket_del_func del;
} bucket_t;

/* Prototypes. */
extern berr bucket_init(bucket_t *, int (*cmp)(void *, void *), void (*del)(void *));
extern void bucket_clean (bucket_t *);

extern berr bucket_cell_add (bucket_t *, void *);
extern berr bucket_cell_del (bucket_t *, void *);
extern void* bucket_cell_get(bucket_t *, void *);
#endif /* __BTS_BUCKET_H__ */

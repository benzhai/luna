#ifndef __BTS_HTAB_H__
#define __BTS_HTAB_H__

#include "bts_bucket.h"

typedef struct {
    uint32_t (*hash)(void *);
    void (*del)(void *);
    int (*cmp)(void *, void *);
    uint32_t size;
    bucket_t *buckets;
} htab_t;

void htab_free(htab_t *htab);

htab_t* htab_new(uint32_t size, uint32_t (*hash)(void *), int (*cmp)(void *, void *), void (*del)(void *));

#define ERROR_HVAL 0xFFFFFFFF

uint32_t htab_hash(htab_t* htab, void *obj);

bucket_t* htab_bucket_get(htab_t* htab, void *obj);

void* htab_cell_get(htab_t* htab, void *key);

berr htab_cell_add(htab_t* htab, void *obj, void *key);

void  htab_cell_del(htab_t* htab, void *key);
#endif /* !__BTS_HTAB_H__ */

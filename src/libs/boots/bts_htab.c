#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "boots.h"
#include "bts_htab.h"
#include "bts_bucket.h"

void htab_free(htab_t *htab)
{
    int i = 0;
    if (NULL == htab) {
        return;
    }

    if (htab->buckets) {
        for (i = 0; i < htab->size; i++) {
            bucket_clean(&htab->buckets[i]);
        }

        free(htab->buckets);
    }

    free(htab);
}

htab_t* htab_new(uint32_t size, uint32_t (*hash)(void *), int (*cmp)(void *, void *), void (*del)(void *))
{
    int i = 0;
    berr rv = E_FAIL;
    htab_t *htab = NULL;

    if (NULL == hash) {
        return NULL;
    }

    htab = malloc(sizeof(htab_t));

    if (NULL == htab) {
        return NULL;
    }

    memset(htab, 0, sizeof(htab_t));

    htab->buckets = malloc(sizeof(bucket_t) * size);

    if (NULL == htab->buckets) {
        htab_free(htab);
        return NULL;
    }

    memset(htab->buckets, 0, sizeof(bucket_t) * size);

    htab->size = 0;

    for (i = 0; i < size; i++) {
        rv = bucket_init(&htab->buckets[htab->size], cmp, del);

        if (E_SUCCESS != rv) {
            htab_free(htab);
            return NULL;
        }

        if (NULL != cmp) {
            htab->cmp = cmp;
        }

        htab->size++;
    }

    htab->hash = hash;

    return htab;
}

uint32_t htab_hash(htab_t* htab, void *key)
{
    uint32_t hval = ERROR_HVAL;

    if ((NULL == htab) || (NULL == key)) {
        return ERROR_HVAL;
    }

    if (NULL == htab->hash) {
        return ERROR_HVAL;
    }


    if (0 == htab->size) {
        return ERROR_HVAL;
    }

    hval = htab->hash(key);

    if (ERROR_HVAL == hval) {
        return ERROR_HVAL;
    }

    hval = hval % htab->size;

    return hval;
}

bucket_t* htab_bucket_get(htab_t* htab, void *key)
{
    uint32_t hval = 0;

    bucket_t *bucket = NULL;

    if ((NULL == htab) || (NULL == key)) {
        return NULL;
    }

    hval = htab_hash(htab, key);

    if (ERROR_HVAL == hval) {
        return NULL;
    }

    bucket = &htab->buckets[hval];

    return bucket;
}

void* htab_cell_get(htab_t* htab, void *key)
{
    bucket_t *bucket = NULL;

    bucket = htab_bucket_get(htab, key);

    if (NULL == bucket) {
        return NULL;
    }

    return bucket_cell_get(bucket, key);
}

berr htab_cell_add(htab_t *htab, void *obj, void *key)
{
    bucket_t *bucket = NULL;

    bucket = htab_bucket_get(htab, key);

    if (NULL == bucket) {
        return E_FAIL;
    }

    return bucket_cell_add(bucket, obj);
}

void htab_cell_del(htab_t *htab, void *key)
{
    bucket_t *bucket = NULL;

    bucket = htab_bucket_get(htab, key);

    if (NULL == bucket) {
        return;
    }

    bucket_cell_del(bucket, key);
}

/* End of file */

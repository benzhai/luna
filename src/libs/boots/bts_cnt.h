#ifndef __BTS_CNT_H__
#define __BTS_CNT_H__

#include "boots.h"
#include "bts_def.h"

#include "bts_custom.h"
 
typedef struct {
    uint32_t idx;
    bts_lock_t lock;
    char *name;
    uint64_t val;
} cnt_t;


typedef enum {
    CNT_CUSTOM
    CNT_DEMO,
    CNT_MAX
} cnte;

cnt_t bts_cnt_array[CNT_MAX] = {
    CNT_DEF_CUSTOM
    CNT_DEF(CNT_DEMO)
};

#define CNT_INC(_cnt)       cnt_inc(_cnt)
#define CNT_DEC(_cnt)       cnt_dec(_cnt)
#define CNT_ADD(_cnt, _val) cnt_add(_cnt, _val)
#define CNT_SET(_cnt, _val) cnt_set(_cnt, _val)
#define CNT_GET(_cnt)       cnt_get(_cnt)

berr cnt_add(cnte idx, uint64_t value);
berr cnt_set(cnte idx, uint64_t value);
berr cnt_inc(cnte idx);
berr cnt_dec(cnte idx);
berr cnt_get(cnte idx, uint32_t number, cnt_t *vals, uint32_t *total);
berr cnt_clear(cnte idx, uint32_t number, uint32_t *total);
berr cnt_int(void);

#endif

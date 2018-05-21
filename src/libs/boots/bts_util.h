#ifndef  __BTS_UTIL_H__
#define  __BTS_UTIL_H__

#include "boots.h"

int bts_ipaddr_cmp(void *val1, void *val2);
int bts_str_cmp(void *val1, void * val2);
void bts_ip4_string(uint32_t ip, char *str);

#define BSWT_STR_SZ 6
berr bswt_parse(char *str, bswt *val);
void bswt_string(bswt *val, char *str);

void bts_u64_inc(uint64_t *dat);
void bts_u64_dec(uint64_t *dat);
void bts_u64_set(uint64_t *dat, uint64_t val);
uint64_t bts_u64_get(uint64_t *dat);

void bts_lock_lock(bts_lock_t *lock);
void bts_lock_unlock(bts_lock_t *lock);
void bts_lock_init(bts_lock_t *lock);

uint32_t bts_hash(void *buff, uint32_t len);

#endif /* end of __BTS_UTIL_H__ */

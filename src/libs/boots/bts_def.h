#ifndef __BTS_DEF_H__
#define __BTS_DEF_H__

#include <pthread.h>

#define CNT_DEF(_cnt) {_cnt, PTHREAD_MUTEX_INITIALIZER, #_cnt, 0}
#define OPT_DEF(_opt, _msg) {_opt, OFF, #_opt, _msg} 

#endif /* !__BTS_DEF_H__ */

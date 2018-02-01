#ifndef __BTS_DEBUG_H__
#define __BTS_DEBUG_H__

#include "bts_cnt.h"
#include "bts_opt.h"
#include "bts_log.h"
#include "bts_mod.h"

#define BTS_DEBUG_DUMP(_mod, _opt, _fmt, _args...) { \
    if ((_mod < MOD_MAX) || (_opt < OPT_MAX)) { \
        if (dopt_array[_opt].enable && mod_array[_mod].debug) { \
            printf("[%s.%s] %s.%d:" _fmt, #_mod, #_opt, __func__, __LINE__, ##_args); \
        } \
    } \
}

#define DBG_INFO(_mod, _fmt, _args...)   \
    BTS_DEBUG_DUMP(_mod, OPT_INFO, _fmt, ##_args)

#define DBG_VERB(_mod, _fmt, _args...)  \
    BTS_DEBUG_DUMP(_mod, OPT_VERB, _fmt, ##_args)

#define DBG_WARN(_mod, _fmt, _args...) \
    BTS_DEBUG_DUMP(_mod, OPT_WARN, _fmt, ##_args)

#define DBG_ERR(_mod, _fmt, _args...) \
    BTS_DEBUG_DUMP(_mod, OPT_ERR, _fmt, ##_args)

#define BRET(e) \
{ \
    berr _rv = (e);\
    if ((_rv != E_SUCCESS) && dopt_array[OPT_ETRACE].enable) \
    { \
        printf("[ETRACE] %s.%d: return %s!\n", __FUNCTION__, __LINE__, berr_msg(_rv)); \
    } \
    return _rv; \
}


#endif /* __BTS_DEBUG_H__ */

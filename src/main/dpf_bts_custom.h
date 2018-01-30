#ifndef __DPF_BTS_CUSTOM_H__
#define __DPF_BTS_CUSTOM_H__

#include "bts_def.h"

#define DPF_OPT_CUSTOM \
    OPT_TAGMON, \
    OPT_FAILPKT,\
    OPT_LOG,

#define DPF_OPT_ARRAY  \
    OPT_DEF(OPT_TAGMON, "Hytag monitor"), \
    OPT_DEF(OPT_FAILPKT, "Process fail packet record"),\
    OPT_DEF(OPT_LOG, "log record"),

#define DPF_CNT_CUSTOM   \

#define DPF_CNT_DEF_CUSTOM   \

#endif

#ifndef __DBG_TAGMON_H__
#define __DBG_TAGMON_H__

#include "pid.h"
#include "bts_custom.h"
#include "bts_debug.h"


void hytag_print(hytag_t *tag);
void hytag_log(hytag_t *tag);

#define HYTAG_DUMP(_tag) \
{ \
    if (OPT_IS_SELECTED(OPT_TAGMON)) \
    { \
        hytag_print(_tag); \
    } \
}

#define HYTAG_LOG(_tag) \
{ \
    if (OPT_IS_SELECTED(OPT_LOG)) \
    { \
        hytag_log(_tag); \
    } \
}


#endif

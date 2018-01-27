#ifndef __BTS_OPT_H__
#define __BTS_OPT_H__

#include <stdio.h>

#include "boots.h"
#include "bts_mod.h"
#include "bts_custom.h"

typedef enum {
#ifdef MOD_OPTS
    MOD_OPTS
#endif
#ifdef OPT_CUSTOM
    OPT_CUSTOM
#endif
    OPT_DEMO,
    OPT_MAX
} dopte;

typedef struct {
    dopte idx;
    bswt enable;
    char *name;
    char *desc;
} dopt_t;

dopt_t dopt_array[OPT_MAX] = {
#ifdef MOD_OPT_ARRAY
    MOD_OPT_ARRAY
#endif
#ifdef OPT_ARRAY_CUSTOM
    OPT_ARRAY_CUSTOM
#endif
    OPT_DEF(OPT_DEMO, "dopt demo of luna")
} ;

int dopt_is_enable(dopte dop);
dopt_t* dopt_lookup(char *name);
berr dopt_modify(char *name, bswt enable);

#define OPT_IS_SELECTED(dop)    (dopt_is_enable(dop) == ENABLE)

#endif /* __BTS_OPT_H__ */

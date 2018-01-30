#ifndef __BTS_MOD_H__
#define __BTS_MOD_H__


#include "bts_def.h"

#define MOD_OPTS \
      OPT_INFO, \
      OPT_VERB, \
      OPT_WARN, \
      OPT_ERR, \
      OPT_ETRACE, \
      OPT_TINYSTEP, \
      OPT_TRAP, \
      OPT_CALLSTACK,

#define  MOD_OPT_ARRAY \
      OPT_DEF(OPT_INFO, "normal debug message"), \
      OPT_DEF(OPT_VERB, "verbose debug message"), \
      OPT_DEF(OPT_WARN, "warning message"), \
      OPT_DEF(OPT_ERR, "error message"), \
      OPT_DEF(OPT_ETRACE, "error return trace"), \
      OPT_DEF(OPT_TINYSTEP, "time spand of a section code"), \
      OPT_DEF(OPT_TRAP, "a trap trigger by condition"), \
      OPT_DEF(OPT_CALLSTACK, "dump call stack"),

typedef enum {
    MOD_DBG,
    MOD_CUSTOM,
    MOD_MAX
} bmod;

typedef struct {
    bmod  mod;      /* Module ID*/
    bswt  enable;      /* Turn on/off this module */
    bswt  debug;      /* Turn on/off the debug dump of this module */
    int   resv;     
    char *abbr;
    char *desc;
} mod_t;

mod_t mod_array[MOD_MAX];
mod_t* mod_lookup(char *name);
berr mod_modify(char *name, bswt enable, bswt debug);
int mod_is_enable(bmod mod);

#endif /* End of __BTS_MOD_H__ */

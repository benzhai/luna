
#include <strings.h>

#include "boots.h"
#include "bts_debug.h"

char *berr_array[E_MAX + 1] = {
    "SUCCESS",
    "FAIL",
    "NULL",
    "MATCH",    // ???
    "EFFECTIVE",
    "MEMORY",   // ???? 
    "PARAM",    // ????
    "EXCEED",   // ?? 
    "OPEN",     // ????
    "FOUND",    // ???
    "EXIST",    // ????
    "BUSY",     // ?? 
    "COMPARE",
    "INIT",
    "FORMAT",
    "UNKOWN",
};

char* berr_msg(berr e)
{
    if (e >= E_MAX)
    {
        return berr_array[E_MAX];
    }

    return berr_array[e];
}

mod_t mod_array[MOD_MAX] = {
#ifdef MOD_ARRAY_CUSTOM
    MOD_ARRAY_CUSTOM
#endif
    {MOD_DBG, BAS, OFF, OFF, "DBG", "debug module"},
} ;



mod_t*
mod_lookup(char *name)
{
    int i;
    if (NULL == name)
    {
        return NULL;
    }

    for (i = 0; i < MOD_MAX; i++)
    {
        if (!strcasecmp(name, mod_array[i].abbr))
        {
            return &mod_array[i];
        }
    }

    return 0;
}

berr
mod_modify(char *name, bswt enable, bswt debug)
{
    mod_t *module = NULL;
    module = mod_lookup(name);

    if (NULL == module)
    {
        BRET(E_FOUND);
    }

    if (BAS != module->enable)
    {
        module->enable = enable;
    }
 
    module->debug = debug;

    return E_SUCCESS;
}

int mod_is_enable(bmod mod)
{
   return (mod < MOD_MAX) ?  mod_array[mod].enable : OFF;
}


/* End of file */

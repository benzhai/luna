#include <strings.h>

#include "boots.h"
#include "bts_debug.h"


dopt_t dopt_array[OPT_MAX] = {
#ifdef MOD_OPT_ARRAY
    MOD_OPT_ARRAY
#endif
#ifdef OPT_ARRAY_CUSTOM
    OPT_ARRAY_CUSTOM
#endif
    OPT_DEF(OPT_DEMO, "dopt demo of luna")
} ;

int dopt_is_enable(dopte dop)
{
    return dop < OPT_MAX ? dopt_array[dop].enable : OFF;
}

dopt_t*
dopt_lookup(char *name)
{
    int i;
    if (NULL == name)
    {
        return NULL;
    }

    for (i = 0; i < OPT_MAX; i++)
    {
        if (!strcasecmp(name, dopt_array[i].name))
        {
            return &dopt_array[i];
        }
    }

    return 0;
}


berr
dopt_modify(char *name, bswt enable)
{
    dopt_t *dopt = NULL;

    dopt = dopt_lookup(name);

    if (NULL == dopt)
    {
        BRET(E_FOUND);
    }

    if (BAS != dopt->enable)
    {
        dopt->enable = enable;
    }

    return E_SUCCESS;
}

/* End of file */

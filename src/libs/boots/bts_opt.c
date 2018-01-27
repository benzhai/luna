#include <strings.h>

#include "boots.h"
#include "bts_debug.h"

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

    for (i = 0; i < MOD_MAX; i++)
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

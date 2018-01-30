#include "boots.h"
#include "bts_debug.h"
#include "bts_cnt.h"

#include "luna_types.h"
#include "fct.h"
#include "url.h"
#include "mask.h"

#include "vsr_dp.h"
#include "net.h"

berr luna_fct(hytag_t *hytag)
{
    berr rv = E_MAX;

    if( APP_TYPE_HTTP_GET_OR_POST != hytag->app_type)
    {
        return E_SUCCESS;
    }

    rv = luna_ori_url(hytag);

    if (E_SUCCESS == rv && (hytag->acl.actions & ACT_REDIR)) {
        return rv;
    }

    rv = luna_ref_url(hytag);

    if (E_SUCCESS == rv && (hytag->acl.actions & ACT_REDIR)) {
        return rv;
    }

    rv = luna_mask(hytag);

    if (E_SUCCESS == rv && (hytag->acl.actions & ACT_REDIR)) {
        return rv;
    }

    return E_SUCCESS;
}

void fct_init(void)
{
    vsr_dp_init();
    netseg_init();
}

/* End of file */

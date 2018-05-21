#include "boots.h"
#include "bts_debug.h"
#include "bts_cnt.h"

#include "luna_types.h"
#include "fct.h"
#include "net.h"
#include "uri.h"
#include "url.h"
#include "mask.h"
#include "acl.h"


#define LUNA_ACL_PREPRO(_aid, _acl, _func, _hytag) \
{ \
    _aid = _func(_hytag); \
    if (ACL_UNMATCHED == _aid){ \
        CNT_INC(FCT_UNMATCHED); \
    } else { \
        acl = acl_get(_aid);\
        if (NULL == _acl) { \
            CNT_INC(ACL_NULL); \
        } else { \
            if (ACL_ACT_IS_VAILD(_acl, ACT_DROP)) { \
                CNT_INC(ACL_DROP); \
                return E_SUCCESS; \
            } \
            if (ACL_ACT_IS_VAILD(_acl, ACT_SAMPLE)) { \
            } \
            if (ACL_ACT_IS_VAILD(_acl, ACT_MASK)) { \
            } \
        } \
    } \
}

berr luna_fct(hytag_t *hytag)
{
    int aid = -1;
    luna_acl_t *acl = NULL;

    CNT_INC(FCT_PKTS);

    if( APP_TYPE_HTTP_GET_OR_POST != hytag->app_type)
    {
        return E_SUCCESS;
    }

    //LUNA_ACL_PREPRO(aid, acl, snet_match, hytag);
    //LUNA_ACL_PREPRO(aid, acl, dnet_match, hytag);

    //LUNA_ACL_PREPRO(aid, acl, ori_domain_match, hytag);
    //LUNA_ACL_PREPRO(aid, acl, ref_domain_match, hytag);

    LUNA_ACL_PREPRO(aid, acl, ori_uri_match, hytag);
    LUNA_ACL_PREPRO(aid, acl, ref_uri_match, hytag);

    //LUNA_ACL_PREPRO(aid, acl, ori_url_match, hytag);
    //LUNA_ACL_PREPRO(aid, acl, ref_url_match, hytag);

    //LUNA_ACL_PREPRO(aid, acl, ua_match, hytag);

    //LUNA_ACL_PREPRO(aid, acl, mask_match, hytag);

    return E_SUCCESS;
}

void fct_init(void)
{
    uri_init();
}

luna_fct_t*
fct_new()
{
    luna_fct_t *fct = malloc(sizeof(luna_fct_t));

    if (NULL == fct) {
        return NULL;
    }

    memset(fct, 0, sizeof(luna_fct_t));


    return fct;
}


void fct_free(luna_fct_t* fct)
{
    if (NULL == fct) {
        return;
    }

    if (NULL != fct->data) {
        free(fct->data);
    }

    free(fct);
}
/* End of file */

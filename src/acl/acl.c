#include "boots.h"
#include "bts_debug.h"
#include "bts_cnt.h"

#include "luna_types.h"
#include "luna_util.h"
#include "acl.h"

#include "packet.h"
#include "packet_http.h"
#include "itf.h"

#include "nag_adp.h"

berr luna_acl_redir(hytag_t *hytag)
{

    berr rv;
    unsigned char buffer[2048]; 
    char url[2048];

    CNT_INC(ACL_REDIR_PKTS);

    if (NULL == hytag) 
    {
        return E_PARAM; 
    }
    
    /* */
    if( APP_TYPE_HTTP_GET_OR_POST != hytag->app_type)
    {
        CNT_INC(ACL_REDIR_DROP_GET_OR_POST);
        return E_SUCCESS;
    }

    if (hytag->url_len > 512)
    {
        CNT_INC(ACL_REDIR_LONG_URI_DROP);
        return E_EXCEED; 
    }
    
    CYCLE_START();

    memcpy(buffer, hytag->pbuf.ptr, hytag->l5_offset);//copy l2-l4 len

    memset(url, 0, 2048);
    strcpy(url, hytag->acl.url);
    rv = redirect_302_response_generator(buffer, hytag, url); 


    if(rv != E_SUCCESS) 
    {
        CNT_INC(ACL_REDIR_DROP_HEAD_GEN1);
        return rv;
    }


    CYCLE_END();

    CYCLE_START();
    rv = ift_raw_send_packet(buffer, hytag->data_len);
    if(rv != E_SUCCESS)
    {
        CNT_INC(ACL_REDIR_DROP_SEND_PACKET);
        return rv;
    }

    CYCLE_END();
  

   
    CNT_INC(ACL_REDIR_TX_SUCCESS);
    return E_SUCCESS;
}


berr luna_acl(hytag_t *hytag)
{
    int rv = E_MAX;

	CNT_INC(ACL_PKTS);

    if(ACT_REDIR == (hytag->acl.actions & ACT_REDIR))
    {
        rv = luna_acl_redir(hytag);

        if (rv != E_SUCCESS) {
            printf("%s.%d: rv = %s\n", __func__, __LINE__, berr_msg(rv));
        }
    }

    return E_SUCCESS;
}


void acl_init(void)
{
    berr rv;
    
    adp_dp_init();

    rv = ads_template_init();

    if (rv)
    {
        printf("%s %d ads_template_init fail, rv(%d)\n", __func__, __LINE__, rv);
    }
}
/* End of file */

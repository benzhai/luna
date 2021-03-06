/**************************************************************
* Copyright (C) 2014-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-10-15 07:06
* @Author: SamLiu - shan3275@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#include "bts_cnt.h"
#include "net.h"

extern rule_act_t netseg_default_act;
berr netseg_dp_match(uint32_t ip, net_t **rule)
{
    int i;

	netseg_t *seg = NULL;

	seg = api_get_netseg_ptr();
	if ((NULL == seg)||(NULL == rule))
	{
		return E_FAIL;
	}
	
    for ( i = 0; i < NETSEG_RULE_NUM_MAX; i++)
    {

		if(seg[i].effective == NETSEG_RULE_UNEFFECTIVE)
		{
			continue;			
		}
		if ( (ip & seg[i].net.mask) == (seg[i].net.ip & seg[i].net.mask) )
		{
			*rule = &seg[i].net;
			return E_SUCCESS;
		}
		else
		{
			continue;
		}
		
    }

    return E_NULL;
}

berr netseg_dp_process(hytag_t *hytag)
{
    int rv;
	net_t *rule = NULL;

    if ( NULL == hytag )
    {
        return E_PARAM;
    }

    /*add recv statistics */
    cnt_inc(NET_PKTS);

    /*check protocol type*/
    if ( hytag->app_type != APP_TYPE_HTTP_GET_OR_POST)
    {
        /* add statistics */
        cnt_inc(NET_UNURLPKTS);
        return E_SUCCESS;
    }

    /* add IP_UDP_GTP_IP_URL packet statistics */
    cnt_inc(NET_URLPKTS);

    /* IP_UDP_GTP_IP_URL packet process */
    rv = netseg_dp_match(hytag->outer_srcip4, &rule);
    
    if((E_SUCCESS != rv)|| (NULL == rule))
    {
        /*add not match statistics */
        cnt_inc(NET_UNMATCHPKTS);
        hytag->match &= 0xfffe;
		hytag->snet_hit_id = 255;
        HYTAG_ACT_DUP(hytag->act, netseg_default_act); 
    }
    else
    {
        /* add match statistics */
        cnt_inc(NET_MATCHPKTS);
        hytag->match |= 1;
		hytag->snet_hit_id = rule->index;

		//FCT_HIT(rule);
        
		HYTAG_ACT_DUP(hytag->act, rule->act);
    }
    return E_SUCCESS; 
}

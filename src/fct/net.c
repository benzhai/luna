/*=============================================================================
#       COPYRIGHT NOTICE
#       Copyright (c) 2015
#       All rights reserved
#
#       @author       :shan
#       @name         :Sam Liu
#       @file         :/mnt/hgfs/code/rose/src/dpdk-2.0.0/examples/zebra/vsr\vsr.c
#       @date         :2015/08/21 22:53
#       @algorithm    :
=============================================================================*/

#include <stdlib.h>

#include "net.h"
#include "boots.h"
#include "bts_util.h"
#include "bts_debug.h"

netseg_t *netseg = NULL;
rule_act_t netseg_default_act;

#define NETSEG_STAT_INC(_index)         bts_u64_inc(&(netseg[_index].net.act.cnt))
#define NETSEG_STAT_DEC(_index)         bts_u64_dec(&(netseg[_index].net.act.cnt))
#define NETSEG_STAT_SET(_index, _val)   bts_u64_set(&(netseg[_index].net.act.cnt), _val))

#define NETSEG_RULE_LOCK(_index)        bts_lock_lock(&(netseg[_index].lock))
#define NETSEG_RULE_UNLOCK(_index)      bts_lock_unlock(&(netseg[_index].lock))

berr api_net_add(net_t *net)
{
    uint32_t index;
    if (NULL == net)
    {
        return E_PARAM;
    }
    index = net->index;

    NETSEG_RULE_LOCK(index);
    memcpy(&netseg[index].net, net, sizeof(net_t));
    netseg[index].effective = NETSEG_RULE_EFFECTIVE;

    DBG_INFO(MOD_FCT, "netseg[%d].effective(%d)\n", index, netseg[index].effective);
    DBG_INFO(MOD_FCT, "netseg[%d].net.index(0x%x)\n", index, netseg[index].net.index);
    DBG_INFO(MOD_FCT, "netseg[%d].net.ip(0x%x)\n", index, netseg[index].net.ip);
    DBG_INFO(MOD_FCT, "netseg[%d].net.mask(0x%x)\n", index, netseg[index].net.mask);
    DBG_INFO(MOD_FCT, "netseg[%d].net.act.action(0x%x)\n", index, netseg[index].net.act.actions);
    NETSEG_RULE_UNLOCK(index);
    return E_SUCCESS;
}

berr api_net_del(uint32_t index)
{
    if (index >= NETSEG_RULE_NUM_MAX)
    {
        return E_PARAM;
    }

    NETSEG_RULE_LOCK(index);
    memset(&netseg[index].net, 0, sizeof(net_t));
    netseg[index].effective = NETSEG_RULE_UNEFFECTIVE;

    DBG_INFO(MOD_FCT, "netseg[%d].effective(%d)\n", index, netseg[index].effective);
    DBG_INFO(MOD_FCT, "netseg[%d].net.index(0x%x)\n", index, netseg[index].net.index);
    DBG_INFO(MOD_FCT, "netseg[%d].net.ip(0x%x)\n", index, netseg[index].net.ip);
    DBG_INFO(MOD_FCT, "netseg[%d].net.mask(0x%x)\n", index, netseg[index].net.mask);
    DBG_INFO(MOD_FCT, "netseg[%d].net.act.action(0x%x)\n", index, netseg[index].net.act.actions);
    NETSEG_RULE_UNLOCK(index);
    return E_SUCCESS;
}

berr  api_net_get(uint32_t index, net_t *net, uint8_t *effect)
{
    if (NULL == net)
    {
        return E_PARAM;
    }

    if (index >= NETSEG_RULE_NUM_MAX)
    {
        return E_PARAM;
    }

    NETSEG_RULE_LOCK(index);
    memcpy(net, &netseg[index].net, sizeof(net_t));
	*effect = netseg[index].effective;

    DBG_INFO(MOD_FCT, "netseg[%d].effective(%d)\n", index, netseg[index].effective);
    DBG_INFO(MOD_FCT, "netseg[%d].net.index(0x%x)\n", index, netseg[index].net.index);
    DBG_INFO(MOD_FCT, "netseg[%d].net.ip(0x%x)\n", index, netseg[index].net.ip);
    DBG_INFO(MOD_FCT, "netseg[%d].net.mask(0x%x)\n", index, netseg[index].net.mask);
    DBG_INFO(MOD_FCT, "netseg[%d].net.act.action(0x%x)\n", index, netseg[index].net.act.actions);
	DBG_INFO(MOD_FCT, "netseg[%d].effective(%d)\n", index, netseg[index].effective);
    NETSEG_RULE_UNLOCK(index);
	return E_SUCCESS;
}

berr api_net_clear_statistics(uint32_t index)
{
    if (index >= NETSEG_RULE_NUM_MAX)
    {
        return E_PARAM;
    }

    NETSEG_RULE_LOCK(index);
    bts_u64_set(&(netseg[index].net.act.cnt), 0); 

    DBG_INFO(MOD_FCT, "netseg[%d].effective(%d)\n", index, netseg[index].effective);
    DBG_INFO(MOD_FCT, "netseg[%d].net.index(0x%x)\n", index, netseg[index].net.index);
    DBG_INFO(MOD_FCT, "netseg[%d].net.ip(0x%x)\n", index, netseg[index].net.ip);
    DBG_INFO(MOD_FCT, "netseg[%d].net.mask(0x%x)\n", index, netseg[index].net.mask);
    DBG_INFO(MOD_FCT, "netseg[%d].net.act.action(0x%x)\n", index, netseg[index].net.act.actions);
    NETSEG_RULE_UNLOCK(index);
	return E_SUCCESS;
}


berr api_get_netseg_effect(uint32_t index, uint8_t *effect)
{
    if (index >= NETSEG_RULE_NUM_MAX)
    {
        return E_PARAM;
    }

    *effect = netseg[index].effective;

    return E_SUCCESS;
}

netseg_t *api_get_netseg_ptr(void)
{
    if (NULL == netseg)
    {
            printf("Netseg is NULL!!!!!!!!!!!!!\n");
            return NULL;
    }
    return netseg;
}





/* dp use */
berr api_net_dp_match(uint32_t index, uint32_t ip)
{
    int rv = E_SUCCESS;
    /* lock */
    NETSEG_RULE_LOCK(index);

    /* check rule effective */
    if(netseg[index].effective == NETSEG_RULE_UNEFFECTIVE)
    {
        /* unlock */
        NETSEG_RULE_UNLOCK(index);
        return rv;
    }

    /* check ip */
    if ((ip & netseg[index].net.mask) != (netseg[index].net.ip & netseg[index].net.mask) )
    {
        /* unlock */
        NETSEG_RULE_UNLOCK(index);
        return rv;
    }

    /* unlock */
    NETSEG_RULE_UNLOCK(index);

    return rv;
}



berr api_netseg_default_act_set(rule_act_t *act)
{
	memcpy(&netseg_default_act, act, sizeof(rule_act_t));
	return E_SUCCESS;
}

berr api_netseg_default_act_get(rule_act_t *act)
{
	memcpy(act, &netseg_default_act, sizeof(rule_act_t));
	return E_SUCCESS;
}



void netseg_init(void)
{
    int i;
	
    netseg = malloc(sizeof(netseg_t) * NETSEG_RULE_NUM_MAX);
    if ( NULL == netseg )
    {
        printf("%s %d setseg malloc failed\n", __func__, __LINE__);
        return;
    }

    memset(netseg, 0, sizeof(netseg_t) * NETSEG_RULE_NUM_MAX);
    for( i = 0; i < NETSEG_RULE_NUM_MAX; i++)
    {
        netseg[i].effective = NETSEG_RULE_UNEFFECTIVE;
        bts_lock_init(&netseg[i].lock);
    }

    return;

}

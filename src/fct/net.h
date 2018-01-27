/*=============================================================================
#       COPYRIGHT NOTICE
#       Copyright (c) 2015
#       All rights reserved
#
#       @author       :shan
#       @name         :Sam Liu
#       @file         :/mnt/hgfs/code/rose/src/dpdk-2.0.0/examples/zebra/vsr\vsr.h
#       @date         :2015/08/21 22:56
#       @algorithm    :
=============================================================================*/
#ifndef  __NET_H__
#define  __NET_H__

#include "stdio.h"
#include "string.h"
#include "boots.h"
#include "luna_types.h"



#define NETSEG_RULE_NUM_MAX     150
#define NETSEG_RULE_EFFECTIVE   1
#define NETSEG_RULE_UNEFFECTIVE 0


typedef struct {
    uint32_t index;
	uint32_t ip;
	uint32_t mask;
    luna_acl_t acl;
} net_t;

typedef struct {
    net_t net;
    bts_lock_t lock;
    uint8_t effective;
} netseg_t;


//#define CHECK_NET_EFFECTTIV(_i)   ()


berr api_net_add(net_t *net);
berr api_net_del(uint32_t index);
berr  api_net_get(uint32_t index, net_t *net, uint8_t *effect);
berr api_net_clear_statistics(uint32_t index);

berr api_get_netseg_effect(uint32_t index, uint8_t *effect);

berr api_netseg_default_act_set(luna_acl_t *acl);

berr api_netseg_default_act_get(luna_acl_t *acl);

/* dp use */
berr api_net_dp_match(uint32_t index, uint32_t ip);
netseg_t *api_get_netseg_ptr(void);

void netseg_init(void);

#endif /* end of __NET_H__ */

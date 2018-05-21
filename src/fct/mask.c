#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "boots.h"
#include "bts_debug.h"
#include "bts_cnt.h"

#include "luna_types.h"
#include "luna_util.h"
#include "mask.h"

//#define DEBUG
#ifdef  DEBUG   
#define debug(fmt,args...)  printf ("func(%s), line(%d)"fmt"\n" ,__FUNCTION__, __LINE__, ##args)
#else   
#define debug(fmt,args...)   
#endif  /* DEBUG */ 

mask_rule_tab_t  rule_tab;

berr mask_rule_add(uint32_t id,  uint32_t mask, rule_act_t *act)
{
    if(id >= MAX_MASK_RULE || act == NULL) 
    {
        return E_PARAM;
    }
    
    mask_rule_t *rule = &(rule_tab.rules[id]);

    rule->id = id;
    rule->mask = mask;

    memcpy(&rule->act, act, sizeof(rule_act_t));
    rule->used = 1;

    if(id >= rule_tab.inuse)
    {
        rule_tab.inuse = id +1;
    }

    return E_SUCCESS;
}

mask_rule_t * mask_rule_get(uint32_t id)
{
    if(id >= MAX_MASK_RULE) 
    {
        return NULL;
    }    

    return &(rule_tab.rules[id]);   
}


berr mask_rule_del(uint32_t id)
{
    if(id >= MAX_MASK_RULE) 
    {
        return E_PARAM;
    }
    
    memset(&rule_tab.rules[id], 0, sizeof(mask_rule_t));

    return E_SUCCESS;
}


berr luna_mask(hytag_t *hytag)
{
    int i;
    mask_rule_t *rule = NULL;

	CNT_INC(MASK_PKTS);

    if (NULL == hytag) {
        CNT_INC(MASK_PARAM);
        return E_PARAM;
    }

    if (hytag->act.mask == 0) {
        CNT_INC(MASK_ZERO);
        return E_SUCCESS;
    }

    CNT_INC(MASK_NOTZERO);

    debug("mask=0x%x", hytag->act.mask);
    debug("rule_tab.inuse:%u", rule_tab.inuse);

    for (i = 0; i < rule_tab.inuse; i++) 
    {
        /*
         *
        typedef struct {
            uint32_t id;
            uint32_t used;
            uint32_t mask;
            rule_act_t acl;
        } mask_rule_t;

        typedef struct {
            uint32_t actions;
            uint32_t mask;
            bts_atomic64_t cnt;
            bts_atomic64_t vcnt;
            bts_atomic64_t pushed_cnt;
            char url[LUNA_URL_LEN_MAX];
        } rule_act_t;
         *
         */
        rule = &rule_tab.rules[i];
        debug("rule->id             :%u", rule->id);
        debug("rule->used           :%u", rule->used);
        debug("rule->mask           :%u", rule->mask);
        debug("rule->act.actions    :0x%x", rule->act.actions);
        debug("rule->act.mask       :0x%x", rule->act.mask);
        debug("rule->act.acl        :%d", rule->act.acl);
       
        if (0 == rule->used) {
            continue;
        }
     
        if (rule->mask == (rule->mask & hytag->act.mask)) {
            debug("OPT: mask_url  ===================================================================");
            //FCT_HIT(rule);
            HYTAG_ACT_DUP(hytag->act, rule->act);
            CNT_INC(MASK_MATCHED);

            return E_SUCCESS; 
        }
    }

    CNT_INC(MASK_DISMATCH);

    return E_SUCCESS;
}

/* End of file */

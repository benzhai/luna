#ifndef __BOOTS_CUSTOM_H__
#define __BOOTS_CUSTOM_H__

#include "dpf_bts_custom.h"
#include "itf_bts_custom.h"
#include "pid_bts_custom.h"
#include "fct_bts_custom.h"
#include "acl_bts_custom.h"

#define MOD_CUSTOM \
    MOD_DPF, \
    MOD_ITF, \
    MOD_PID, \
    MOD_FCT, \
    MOD_ACL

#define MOD_ARRAY_CUSTOM \
    {MOD_DPF, BAS, OFF, OFF, "DPF", "Data process flow"}, \
    {MOD_ITF, BAS, OFF, OFF, "ITF", "Interface module"}, \
    {MOD_PID, ON,  OFF, OFF, "PID", "Packet identify module"}, \
	{MOD_FCT, ON,  OFF, OFF, "FCT", "Rule matching"},\
	{MOD_ACL, ON,  OFF, OFF, "ACL", "Polciy of rule"},

#define OPT_CUSTOM \
    DPF_OPT_CUSTOM \
    ITF_OPT_CUSTOM \
    PID_OPT_CUSTOM \
    FCT_OPT_CUSTOM \
    ACL_OPT_CUSTOM 

#define OPT_ARRAY_CUSTOM \
    DPF_OPT_ARRAY \
    ITF_OPT_ARRAY \
    PID_OPT_ARRAY \
    FCT_OPT_ARRAY \
    ACL_OPT_ARRAY
    

#define CNT_CUSTOM \
    DPF_CNT_CUSTOM \
    ITF_CNT_CUSTOM \
    PID_CNT_CUSTOM \
    FCT_CNT_CUSTOM \
    ACL_CNT_CUSTOM 

#define CNT_DEF_CUSTOM \
    DPF_CNT_DEF_CUSTOM \
    ITF_CNT_DEF_CUSTOM \
    PID_CNT_DEF_CUSTOM \
    FCT_CNT_DEF_CUSTOM \
    ACL_CNT_DEF_CUSTOM 

#endif /* ! __BOOTS_CUSTOM_H__ */

#include <string.h>

#include "bts_custom.h"
#include "dbg_tagmon.h"
#include "bts_mod.h"

#include "itf.h"
#include "dpf.h"
#include "pid.h"
#include "fct.h"
#include "acl.h"

#include "itf_stat.h"


#define MOD_IS_TURN_ON(mod)  (mod_is_enable(mod) == ON)


#define DPF_NODE(_mod, _tag, _func) { \
    if(MOD_IS_TURN_ON(_mod)) \
    { \
        berr _ec = _func(_tag); \
        if (_ec == E_SUCCESS) \
        { \
           DBG_INFO(MOD_DPF, "%s ...... PASS.\n", #_func); \
        } else { \
           DBG_ERR(MOD_DPF, "%s  ...... FAIL!(%s)\n", #_func, berr_msg(_ec)); \
        } \
        HYTAG_DUMP(_tag); \
    } else { \
		DBG_INFO(MOD_DPF, "%s is turn off!\n", #_mod); \
	} \
}


pthread_mutex_t luna_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * data plane main process flow, not include rx & tx
*/
#define CHECK_PACK_TIME 0
berr luna_data_process_module(hytag_t * hytag)
{

	if (!itf_rx_is_enable())
	{
		return E_SUCCESS;
	}

#if CHECK_PACK_TIME
	struct timeval tv0, tv1; 
	gettimeofday(&tv0, NULL);	
#endif

    DPF_NODE(MOD_PID, hytag, luna_pid);

    /* */
   if( APP_TYPE_HTTP_GET_OR_POST != hytag->app_type)
   {
       CNT_INC(DPF_DROP_NOT_GET_OR_POST);
       return E_SUCCESS;
   }


    DPF_NODE(MOD_FCT, hytag, luna_fct);
    DPF_NODE(MOD_ACL, hytag, luna_acl);
   
    pthread_mutex_lock(&luna_mutex);
    HYTAG_LOG(hytag);
    pthread_mutex_unlock(&luna_mutex);
#if CHECK_PACK_TIME	
	gettimeofday(&tv1, NULL); 

	uint64_t m_time = 0;
	uint64_t s_time = 0;
	if(hytag->ad_act == AD_SUCCESS)
	{
		m_time = tv0.tv_sec;
		m_time = m_time*1000*1000;
		m_time += tv0.tv_usec;

		s_time = tv1.tv_sec;
		s_time = s_time*1000*1000;
		s_time += tv1.tv_usec;
		
		printf("Take time = %ld us\n", s_time- m_time);	
	}
#endif	
    return E_SUCCESS;
}

/* End of file */

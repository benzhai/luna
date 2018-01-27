#include "bts_cnt.h"
#include "bts_debug.h"
#include "bts_util.h"

berr cnt_add(cnte idx, uint64_t value)
{
    cnt_t *cnt = NULL;

    if (idx >= CNT_MAX) 
    {
        BRET(E_EXCEED);
    }

    cnt = &bts_cnt_array[idx];

    bts_lock_lock(&cnt->lock);
        
    cnt->val += value;

    bts_lock_unlock(&cnt->lock);
    

    BRET(E_SUCCESS);
}

berr cnt_set(cnte idx, uint64_t value)
{
    cnt_t *cnt = NULL;

    if (idx >= CNT_MAX) 
    {
        BRET(E_EXCEED);
    }

    cnt = &bts_cnt_array[idx];

    bts_lock_lock(&cnt->lock);
        
    cnt->val = value;

    bts_lock_unlock(&cnt->lock);

    BRET(E_SUCCESS);
}

berr cnt_inc(cnte idx)
{
    cnt_t *cnt = NULL;

    if (idx >= CNT_MAX)
    {
        BRET(E_EXCEED);
    }

    cnt = &bts_cnt_array[idx];

    bts_lock_lock(&cnt->lock);
        
    cnt->val += 1;

    bts_lock_unlock(&cnt->lock);

    BRET(E_SUCCESS);
}

berr cnt_dec(cnte idx)
{
    cnt_t *cnt = NULL;

    if (idx >= CNT_MAX)
    {
        BRET(E_EXCEED);
    }

    
    cnt = &bts_cnt_array[idx];

    bts_lock_lock(&cnt->lock);
        
    cnt->val -= 1;

    bts_lock_unlock(&cnt->lock);

    BRET(E_SUCCESS);
}

berr cnt_get(cnte idx, uint32_t number, cnt_t *vals, uint32_t *total)
{
    uint32_t i  = 0, idxc = 0;

    if ((idx + number) > CNT_MAX)
    {
        BRET(E_EXCEED);
    }

    if ((NULL == vals) || (NULL == total))
    {
        BRET(E_PARAM);
    }

    *total = 0;

    for (i = 0; i < number; i++)
    {
        idxc = idx + i;
        vals[i] = bts_cnt_array[idxc];
        *total += 1;
    }

    BRET(E_SUCCESS);
}

berr cnt_clear(cnte idx, uint32_t number, uint32_t *total)
{
    cnt_t *cnt = NULL;

    uint32_t i  = 0, idxc = 0;

    if ((idx + number) > CNT_MAX)
    {
        BRET(E_EXCEED);
    }

    if (NULL == total)
    {
        BRET(E_PARAM);
    }

    *total = 0;

    for (i = 0; i < number; i++)
    {
        idxc = idx + i;
        cnt = &bts_cnt_array[idx];

        bts_lock_lock(&cnt->lock);
            
        cnt->val = 0;

        bts_lock_unlock(&cnt->lock);

        *total += 1;
    }

    BRET(E_SUCCESS);
}

berr cnt_init()
{
    cnt_t *cnt = NULL;
    uint32_t i = 0;

    for (i = 0; i < CNT_MAX; i++)
    {
        cnt = &bts_cnt_array[i];
        bts_lock_init(&cnt->lock);
        cnt->val = 0;
    }

    BRET(E_SUCCESS);
}

/* End of file */

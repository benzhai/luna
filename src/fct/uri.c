#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "boots.h"
#include "bts_debug.h"
#include "bts_cnt.h"
#include "bts_htab.h"
#include "bts_hash.h"

#include "luna_types.h"
#include "uri.h"
#include "fct.h"


htab_t *ori_tab = NULL;
htab_t *ref_tab = NULL;

berr
uri_rule_add(htab_t *tab, char *uri, int aclid)
{
    luna_fct_t *fct = NULL;
    fct = fct_new();

    if (NULL == fct) {
        return E_MEMORY;
    }

    fct->data = strdup(uri);

    if (NULL == fct->data) {
        fct_free(fct);
        return E_MEMORY;
    }

    fct->acl = aclid;

    htab_cell_add(tab, fct, fct->data);

    return E_SUCCESS;
}

luna_fct_t*
uri_rule_get(htab_t *tab, char *uri)
{
    void *data = NULL;

    data = htab_cell_get(tab, uri);

    if (NULL == data) {
        return NULL;
    }

    return (luna_fct_t*) data; 
}

berr
uri_rule_del(htab_t *tab, char *uri)
{
    htab_cell_del(tab, uri);
    return E_SUCCESS;
}

int
uri_match(htab_t *tab, hytag_t *hytag, char *uri)
{
    luna_fct_t *rule = NULL;

    CNT_INC(URL_PKTS);

    rule = htab_cell_get(tab, uri);

    if (NULL != rule) {

        CNT_INC(URL_MATCHED);
        FCT_HIT(rule); 

        return rule->acl;
    } else {
        return ACL_UNMATCHED;
    }
}

uint32_t
uri_hash(void *key)
{
    int len = 0;

    //luna_fct_t *fct = NULL;

    uint32_t hval = ERROR_HVAL;
    
    if (NULL == key) {
        return ERROR_HVAL;
    }

    //fct = (luna_fct_t *)obj;

    //char *uri = (char *) fct->data;

    char *uri = (char *) key;
    len = strlen(uri);

    hval = FNVHash(uri, len);

    return hval;
}

int 
uri_cmp(void *key, void *obj)
{
    char *uri1, *uri2;
    luna_fct_t *fct = NULL;

    if ((NULL == key) || (NULL == obj)) {
        return -1;
    }

    uri1 = (char *) key;

    fct =  (luna_fct_t *) obj;

    uri2 = (char *) fct->data;

    return strcmp(uri1, uri2);
}

void
uri_free(void *data)
{
    luna_fct_t *fct = NULL;

    if (NULL == data) {
        return;
    }

    fct = (luna_fct_t *) data;

    if (fct->data) {
        free(fct->data);
    }

    free(fct);
}

berr
uri_init()
{
    ori_tab = htab_new(URI_TAB_SIZE, uri_hash, uri_cmp, uri_free);

    if (NULL == ori_tab) {
        return E_MEMORY;
    }

    ref_tab = htab_new(URI_TAB_SIZE, uri_hash, uri_cmp, uri_free);

    if (NULL == ref_tab) {
        return E_MEMORY;
    }

    return E_SUCCESS;
}

berr
ori_uri_match(hytag_t *hytag)
{
    return uri_match(ori_tab, hytag, hytag->ori_url.uri); 
}

berr
ref_uri_match(hytag_t *hytag)
{
    return uri_match(ref_tab, hytag, hytag->ref_url.uri);
}

berr
ori_uri_rule_add(char *uri,  int aclid)
{
    return uri_rule_add(ori_tab, uri, aclid);
}

berr
ref_uri_rule_add(char *uri,  int aclid)
{
    return uri_rule_add(ref_tab, uri, aclid);
}

berr
ori_uri_rule_del(char *uri)
{
    return uri_rule_del(ori_tab, uri);
}

berr
ref_uri_rule_del(char *uri)
{
    return uri_rule_del(ref_tab, uri);
}

luna_fct_t*
ori_uri_rule_get(char *uri)
{
    return uri_rule_get(ori_tab, uri);
}

luna_fct_t*
ref_uri_rule_get(char *uri)
{
    return uri_rule_get(ref_tab, uri);
}
/* End of file */

#ifndef __URI_H__
#define __URI_H__

#define URI_TAB_SIZE    2048

berr uri_init(void);
berr ori_uri_match(hytag_t *hytag);
berr ref_uri_match(hytag_t *hytag);

berr ori_uri_rule_add(char *uri, int aclid);
berr ref_uri_rule_add(char *uri, int aclid);

berr ori_uri_rule_del(char *uri);
berr ref_uri_rule_del(char *uri);

luna_fct_t* ori_uri_rule_get(char *uri);
luna_fct_t* ref_uri_rule_get(char *uri);

#endif /* __URI_H__ */

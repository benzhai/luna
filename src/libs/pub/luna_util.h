#ifndef __LUNA_UTIL_H__
#define __LUNA_UTIL_H__

#include "boots.h"
#include "luna_types.h"

#define LUNA_ACL_STR_SZ  1500

berr luna_acl_parse(const char *argv[], int argc, luna_acl_t *acl);
void luna_acl_string(luna_acl_t *acl, char *str);

void luna_url_dump(luna_url_t *url);

#endif /* !__LUNA_UTIL_H__ */

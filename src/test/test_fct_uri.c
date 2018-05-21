#include <stdlib.h>

#include "CUnit/Basic.h"

#include "boots.h"
#include "bts_linklist.h"
#include "bts_hash.h"

#include "luna_types.h"

#include "uri.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_uri_suite(void)
{
    uri_init();

    return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_uri_suite(void)
{
    return 0;
}


char *uri1 = "sports.163.com/18/0515/06/DHR1TB5Q00058781.html";
char *uri2 = "www.toutiao.com/a6555462992677306888/";
char *uri3 = "http://v.youku.com/v_show/id_XMzU5OTkwMzQzNg==.html";

int test_ori_uri_rule_add()
{
    ori_uri_rule_add(uri1, 1);
    ori_uri_rule_add(uri2, 1);
    ori_uri_rule_add(uri3, 1);


    CU_ASSERT(NULL != ori_uri_rule_get(uri1));
    CU_ASSERT(NULL != ori_uri_rule_get(uri2));
    CU_ASSERT(NULL != ori_uri_rule_get(uri3));
}


int test_ori_uri_rule_del()
{
    ori_uri_rule_del(uri1);
    ori_uri_rule_del(uri2);
    ori_uri_rule_del(uri3);

    CU_ASSERT(NULL == ori_uri_rule_get(uri1));
    CU_ASSERT(NULL == ori_uri_rule_get(uri2));
    CU_ASSERT(NULL == ori_uri_rule_get(uri3));
}


int test_ref_uri_rule_add()
{
    ref_uri_rule_add(uri1, 1);
    ref_uri_rule_add(uri2, 1);
    ref_uri_rule_add(uri3, 1);


    CU_ASSERT(NULL != ref_uri_rule_get(uri1));
    CU_ASSERT(NULL != ref_uri_rule_get(uri2));
    CU_ASSERT(NULL != ref_uri_rule_get(uri3));
}


int test_ref_uri_rule_del()
{
    ref_uri_rule_del(uri1);
    ref_uri_rule_del(uri2);
    ref_uri_rule_del(uri3);

    CU_ASSERT(NULL == ref_uri_rule_get(uri1));
    CU_ASSERT(NULL == ref_uri_rule_get(uri2));
    CU_ASSERT(NULL == ref_uri_rule_get(uri3));
}


CU_ErrorCode uri_suite_create()
{
   CU_pSuite uriSuite = NULL;
   /* add a suite to the registry */
   uriSuite = CU_add_suite("URI", init_uri_suite, clean_uri_suite);
   if (NULL == uriSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(uriSuite, "test of ori_uri_add", test_ori_uri_rule_add))||
       (NULL == CU_add_test(uriSuite, "test of ori_uri_del", test_ori_uri_rule_del))||
       (NULL == CU_add_test(uriSuite, "test of ref_uri_add", test_ref_uri_rule_add))||
       (NULL == CU_add_test(uriSuite, "test of ref_uri_del", test_ref_uri_rule_del)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return CU_get_error(); 
}

/* End of file */
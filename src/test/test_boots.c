#include <stdlib.h>

#include "CUnit/Basic.h"

#include "boots.h"
#include "bts_linklist.h"
#include "bts_hash.h"
#include "bts_htab.h"

htab_t *test_htab = NULL;

uint32_t test_hash(void *data)
{
    char *str = (char *) data;

    uint32_t len = strlen(str);

    return FNVHash(str, len);
}

int test_cmp(void *data1, void *data2)
{
    char *str1, *str2;

    str1 = (char *) data1;

    str2 = (char *) data2;

    return strcmp(str1, str2);
}

void test_del(void *data)
{
    free(data);
}

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_htab_suite(void)
{
    test_htab = htab_new(1024, &test_hash, &test_cmp, &test_del);

    return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_htab_suite(void)
{
    htab_free(test_htab);
    return 0;
}

int test_htab_cell_add()
{
    char *ip1 = strdup("192.168.1.1");
    char *ip2 = strdup("192.168.1.2");
    char *ip3 = strdup("192.168.1.3");

    char *f1, *f2, *f3;

    htab_cell_add(test_htab, ip1, ip1);
    htab_cell_add(test_htab, ip2, ip2);
    htab_cell_add(test_htab, ip3, ip3);

    f1 = htab_cell_get(test_htab, "192.168.1.1");
    f2 = htab_cell_get(test_htab, "192.168.1.2");
    f3 = htab_cell_get(test_htab, "192.168.1.3");

    CU_ASSERT(ip1 == f1);
    CU_ASSERT(ip2 == f2);
    CU_ASSERT(ip3 == f3);

    //printf("ip1=%p, f1=%p\n", ip1, f1);

    //printf("ip2=%p, f2=%p\n", ip2, f2);

    //printf("ip3=%p, f3=%p\n", ip3, f3);
}


int test_htab_cell_del()
{
    char *key1 = "192.168.1.1";
    char *key2 = "192.168.1.2";
    char *key3 = "192.168.1.3";

    htab_cell_del(test_htab, key1);
    htab_cell_del(test_htab, key2);
    htab_cell_del(test_htab, key3);

    CU_ASSERT(NULL == htab_cell_get(test_htab, key1));
    CU_ASSERT(NULL == htab_cell_get(test_htab, key2));
    CU_ASSERT(NULL == htab_cell_get(test_htab, key3));
}

CU_ErrorCode boots_suite_create()
{
   CU_pSuite htabSuite = NULL;
   /* add a suite to the registry */
   htabSuite = CU_add_suite("HTAB", init_htab_suite, clean_htab_suite);
   if (NULL == htabSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(htabSuite, "test of htab_cell_add", test_htab_cell_add))||
       (NULL == CU_add_test(htabSuite, "test of htab_cell_del", test_htab_cell_del)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return CU_get_error(); 
}

/* End of file */
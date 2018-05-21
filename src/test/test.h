#ifndef __TEST_H__
#define __TEST_H__

#include "CUnit/Basic.h"

int test_pcre(void);

int test_pcre_init(void);

CU_ErrorCode boots_suite_create(void);
CU_ErrorCode uri_suite_create(void);

#endif /* __TEST_H__ */

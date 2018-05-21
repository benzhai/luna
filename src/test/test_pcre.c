#include <stdio.h>
#include <string.h>

#include "boots.h"

#include "pcre.h"

int
test_pcre(void)
{
    pcre *re = NULL;

    int erroffset;
    int i = 0;
    const char *error= NULL;

    const char *captured_string;

    int oveccount = 2, ovector[oveccount];

    int rc = 0, rv = 0;

    char *str= "http://m.sogou.com/web/searchList.jsp?keyword=%E8%8B%8D%E7%A9%B9%E6%88%98%E7%BA%BF%E5%AE%98%E7%BD%91&uID=BeyfidS4O-n4cwUE&dp=1&pid=sogou-apps-4ff6fa96179cdc28&v=5&lxg=1QgNCgMcDQZRVgUHVFVSBlIBBlUCUVFJWUkHCwlKBQoAFgsNAEoGFgsTFwEWSVlJU0lZSVxKVVxJWUkHEVlJWUkCBVksMSUzIS1JWUkCFlkXEAsWATsFCgAWCw0AOx4MDQwRDR0RCklZSQICFlkXEAsWATsFCgAWCw0AOx4MDQwRDR0RCklZSRYNAFlVXElZSQ8XWVJJWUkWAFlVVUlZSQ&w=1282&htpos=11&s_from=hint_last&htindex=2&htdbg=idc%3Egdylj%7CdbgID%3E01%7Cabt%3E7%7Cmth%3E6&htprequery=%E8%8B%8D%E7%A9%B9%E6%88%98%E7%BA%BF%E9%A2%84%E7%BA%A6&mcv=19&pcl=268,3098&sed=0&ml=74&sct=224";
    char *subject="\.sogou\.com(.*?)(\?|\&)keyword\=(.*?)(\&|$)";


    printf("  ***PCRE test ...... START.\n");

    re = pcre_compile(subject , 0, &error, &erroffset, NULL);
    
    if ( re == NULL ) {
        printf("compilation failed at offset%d: %s\n", erroffset, error);
        return 0;
    }

    do {
            rc = pcre_exec(re,  NULL, str, strlen(subject), 0, 0, ovector, oveccount);


            rv = pcre_get_substring(subject, ovector, rc, 1, &captured_string);
            printf("rv = %d, captured string : %s\n", rv, captured_string);
             
            // 设置偏移量
            erroffset = ovector[1];
            i++;
    } while ( rc > 0 );

    printf("  ***PCRE test ...... END.\n");
    return E_SUCCESS;
}

int
test_pcre_init(void)
{
    printf("  PCRE init ...... DONE.\n");
    return E_SUCCESS;
}

/* End of file */

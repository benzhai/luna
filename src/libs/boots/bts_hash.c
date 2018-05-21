#include "boots.h"

uint32_t FNVHash(char* str, uint32_t len)  
{  
   const uint32_t fnv_prime = 0x811C9DC5;  
   uint32_t hash  = 0;  
   unsigned int i = 0;  
  
   for(i = 0; i < len; str++, i++)  
   {  
      hash *= fnv_prime;  
      hash ^= (*str);  
   }  
  
   return hash;  
}  

/* End of file */

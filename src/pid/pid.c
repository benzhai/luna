#include "pid.h"

berr luna_pid(hytag_t *hytag)
{
	struct pbuf *p = NULL;

	p = &hytag->pbuf;
   
	return pid_ethernet(p, hytag);
}

/* End of file */


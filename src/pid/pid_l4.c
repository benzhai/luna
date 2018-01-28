#include "pid.h"



berr pid_L4(struct pbuf *p, hytag_t *hytag,  uint8_t protocol, int outer_inner)
{
	
	switch(protocol)
	{
        case IP_PROTO_UDPLITE:
		case IP_PROTO_UDP:
			return pid_udp(p,  hytag, outer_inner);
			break;

         case IP_PROTO_TCP:
            return pid_tcp(p,  hytag, outer_inner);
            break;
         case IP_PROTO_STCP:
            if(outer_inner == HEADER_OUTER)
               cnt_inc(OUTERL4_SCTP);
            else
               cnt_inc(INNERL4_SCTP);
            break;
         default:
                //count and incr
                if(outer_inner == HEADER_OUTER)
                    cnt_inc(OUTERL4_OTHER);
                else
                    cnt_inc(INNERL4_OTHER);
            break;
	}
	return E_SUCCESS;
}


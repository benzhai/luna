#ifndef __PID_BTS_CUSTOM_H__
#define __PID_BTS_CUSTOM_H__

#define PID_OPT_CUSTOM \
    OPT_DUMP_URL,

#define PID_OPT_ARRAY  \
    OPT_DEF(OPT_DUMP_URL, "dump ori & ref url in pid module"),

#define PID_CNT_CUSTOM   \
    /* Ether  */ \
    VLAN_PKTS, \
    PPPOE_PKTS, \
    OUTERL3_IPV4, \
    OUTERL3_IPV6, \
    OUTERL3_NOIP, \
    OUTERL3_HD, \
	\
    /* TCP */ \
    OUTERL4_HD, \
    OUTERL4_TCP, \
    OUTERL4_UDP, \
    OUTERL4_SCTP, \
    OUTERL4_OTHER, \
    INNERL3_HD, \
    INNERL3_IPV4, \
    INNERL3_IPV6, \
    INNERL3_NOIP, \
    INNERL4_HD, \
    INNERL4_TCP, \
    INNERL4_UDP, \
    INNERL4_SCTP, \
    INNERL4_OTHER, \
    \
    /* GTP */ \
    GTP_U_HD, \
    GTP_U, \
    GTP_U_NOPAYLOAD, \
    GTPC_HD, \
    GTPV1_C, \
    GTPV2_C, \
    \
    /* L5 */ \
    APP_HTTP_UP, \
    APP_HTTP_UP_OVER, \
    APP_HTTP_DN, \
    APP_OTHER, \
    HTTP_METHOD_EXCEED, \
    APP_HTTP_GET, \
    APP_HTTP_OTHER, \
    APP_HTTP_PARSE_ERR, \
    HTTP_URL_EXCEED, \
    ERR_PACKET, \
    HEADER_UNEXPECT, \

#define PID_CNT_DEF_CUSTOM   \
    /* Ether Module counters */ \
    CNT_DEF(VLAN_PKTS), \
    CNT_DEF(PPPOE_PKTS), \
    CNT_DEF(OUTERL3_IPV4), \
    CNT_DEF(OUTERL3_IPV6), \
    CNT_DEF(OUTERL3_NOIP), \
    CNT_DEF(OUTERL3_HD), \
	\
    /* TCP */ \
    CNT_DEF(OUTERL4_HD), \
    CNT_DEF(OUTERL4_TCP), \
    CNT_DEF(OUTERL4_UDP), \
    CNT_DEF(OUTERL4_SCTP), \
    CNT_DEF(OUTERL4_OTHER), \
    CNT_DEF(INNERL3_HD), \
    CNT_DEF(INNERL3_IPV4), \
    CNT_DEF(INNERL3_IPV6), \
    CNT_DEF(INNERL3_NOIP), \
    CNT_DEF(INNERL4_HD), \
    CNT_DEF(INNERL4_TCP), \
    CNT_DEF(INNERL4_UDP), \
    CNT_DEF(INNERL4_SCTP), \
    CNT_DEF(INNERL4_OTHER), \
    \
    /* GTP */ \
    CNT_DEF(GTP_U_HD), \
    CNT_DEF(GTP_U), \
    CNT_DEF(GTP_U_NOPAYLOAD), \
    CNT_DEF(GTPC_HD), \
    CNT_DEF(GTPV1_C), \
    CNT_DEF(GTPV2_C), \
    \
    /* L5 */ \
    CNT_DEF(APP_HTTP_UP), \
    CNT_DEF(APP_HTTP_UP_OVER), \
    CNT_DEF(APP_HTTP_DN), \
    CNT_DEF(APP_OTHER), \
    CNT_DEF(HTTP_METHOD_EXCEED), \
    CNT_DEF(APP_HTTP_GET), \
    CNT_DEF(APP_HTTP_OTHER), \
    CNT_DEF(APP_HTTP_PARSE_ERR), \
    CNT_DEF(HTTP_URL_EXCEED), \
    CNT_DEF(ERR_PACKET), \
    CNT_DEF(HEADER_UNEXPECT),

#endif

#ifndef __FCT_BTS_CUSTOM_H__
#define __FCT_BTS_CUSTOM_H__

#define FCT_OPT_CUSTOM \
    OPT_MASK_URL,

#define FCT_OPT_ARRAY  \
    OPT_DEF(OPT_MASK_URL, "dump ori & ref url when mask rule matched"),

#define FCT_CNT_CUSTOM   \
    FCT_PKTS, \
    FCT_UNMATCHED, \
    ACL_DROP, \
    ACL_NULL, \
    ACL_SAMP_HIT, \
    ACL_SAMP_UNHIT, \
    /* VSR Module counters */ \
    VSR_PKTS, /* VSR module input packets*/ \
    VSR_UNURLPKTS, /* take no url packet number */ \
    VSR_URLPKTS, /* take url packet number */ \
    VSR_UNMATCHPKTS, /* not match packets */ \
    VSR_MATCHPKTS, /* match packets */ \
    VSR_RULE_MATCHPKTS, /* rule ip, url all match */ \
    VSR_RULE_NEW_URL, \
    VSR_RULE_LEN_OVERFLOW, /* url len overflow */ \
    VSR_RULE_URL_OVERFLOW,    /* url overflow */ \
    \
    /* NET Module */ \
    NET_PKTS, /* netseg module input packets*/ \
    NET_UNURLPKTS, /* take no url packet number */ \
    NET_URLPKTS, /* take url packet number */ \
    NET_UNMATCHPKTS, /* not match packets */ \
    NET_MATCHPKTS, /* match packets */ \
    NET_RULE_MATCHPKTS, /* rule ip, url all match */ \
    DNET_PKTS, /* dnetseg module input packets*/ \
    DNET_UNURLPKTS, /* take no url packet number */ \
    DNET_URLPKTS, /* take url packet number */ \
    DNET_UNMATCHPKTS, /* not match packets */ \
    DNET_MATCHPKTS, /* match packets */ \
    DNET_RULE_MATCHPKTS, /* rule ip, url all match */ \
    \
    /* URL Module */ \
    URL_PKTS, \
    URL_PARAM, \
    URL_ZERO, \
    URL_NOTZERO, \
    URL_MATCHED, \
    URL_DISMATCH, \
    /* URI Module */ \
    URI_PKTS, \
    URI_PARAM, \
    URI_ZERO, \
    URI_NOTZERO, \
    URI_MATCHED, \
    URI_DISMATCH, \
    \
    /* MASK Module */ \
    MASK_PKTS, \
    MASK_PARAM, \
    MASK_ZERO, \
    MASK_NOTZERO, \
    MASK_MATCHED, \
    MASK_DISMATCH, 

#define FCT_CNT_DEF_CUSTOM   \
    CNT_DEF(FCT_PKTS), \
    CNT_DEF(FCT_UNMATCHED), \
    CNT_DEF(ACL_DROP), \
    CNT_DEF(ACL_NULL), \
    CNT_DEF(ACL_SAMP_HIT), \
    CNT_DEF(ACL_SAMP_UNHIT), \
    /* VSR Module counters */ \
    CNT_DEF(VSR_PKTS), /* VSR module input packets*/ \
    CNT_DEF(VSR_UNURLPKTS), /* take no url packet number */ \
    CNT_DEF(VSR_URLPKTS), /* take url packet number */ \
    CNT_DEF(VSR_UNMATCHPKTS), /* not match packets */ \
    CNT_DEF(VSR_MATCHPKTS), /* match packets */ \
    CNT_DEF(VSR_RULE_MATCHPKTS), /* rule ip, url all match */ \
    CNT_DEF(VSR_RULE_NEW_URL), \
    CNT_DEF(VSR_RULE_LEN_OVERFLOW), /* url len overflow */ \
    CNT_DEF(VSR_RULE_URL_OVERFLOW), /* url overflow */ \
    \
    /* NET Module */ \
    CNT_DEF(NET_PKTS), /* netseg module input packets*/ \
    CNT_DEF(NET_UNURLPKTS), /* take no url packet number */ \
    CNT_DEF(NET_URLPKTS), /* take url packet number */ \
    CNT_DEF(NET_UNMATCHPKTS), /* not match packets */ \
    CNT_DEF(NET_MATCHPKTS), /* match packets */ \
    CNT_DEF(NET_RULE_MATCHPKTS), /* rule ip, url all match */ \
    CNT_DEF(DNET_PKTS), /* dnetseg module input packets*/ \
    CNT_DEF(DNET_UNURLPKTS), /* take no url packet number */ \
    CNT_DEF(DNET_URLPKTS), /* take url packet number */ \
    CNT_DEF(DNET_UNMATCHPKTS), /* not match packets */ \
    CNT_DEF(DNET_MATCHPKTS), /* match packets */ \
    CNT_DEF(DNET_RULE_MATCHPKTS), /* rule ip, url all match */ \
    \
    /* URL Module */ \
    CNT_DEF(URL_PKTS), \
    CNT_DEF(URL_PARAM), \
    CNT_DEF(URL_ZERO), \
    CNT_DEF(URL_NOTZERO), \
    CNT_DEF(URL_MATCHED), \
    CNT_DEF(URL_DISMATCH), \
    \
    /* URI Module */ \
    CNT_DEF(URI_PKTS), \
    CNT_DEF(URI_PARAM), \
    CNT_DEF(URI_ZERO), \
    CNT_DEF(URI_NOTZERO), \
    CNT_DEF(URI_MATCHED), \
    CNT_DEF(URI_DISMATCH), \
    \
    /* MASK Module */ \
    CNT_DEF(MASK_PKTS), \
    CNT_DEF(MASK_PARAM), \
    CNT_DEF(MASK_ZERO), \
    CNT_DEF(MASK_NOTZERO), \
    CNT_DEF(MASK_MATCHED), \
    CNT_DEF(MASK_DISMATCH), 

#endif

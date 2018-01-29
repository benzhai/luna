#ifndef __RTE_H__
#define __RET_H__

#include <byteswap.h>

#define ETHER_ADDR_LEN  6 /**< Length of Ethernet address. */

#define PKT_TX_TCP_SEG       (1ULL << 50)

#define rte_bswap16(x) __builtin_bswap32 (x << 16)
#define rte_bswap32(x) __builtin_bswap32 (x)

#define rte_cpu_to_le_16(x) (x)
#define rte_cpu_to_le_32(x) (x)

#define rte_cpu_to_be_16(x) rte_bswap16(x)
#define rte_cpu_to_be_32(x) rte_bswap32(x)

#define rte_le_to_cpu_16(x) (x)
#define rte_le_to_cpu_32(x) (x)

#define rte_be_to_cpu_16(x) rte_bswap16(x)
#define rte_be_to_cpu_32(x) rte_bswap32(x)

struct ether_addr {
	uint8_t addr_bytes[ETHER_ADDR_LEN]; /**< Address bytes in transmission order */
} ;

/**
 * Ethernet header: Contains the destination address, source address
 * and frame type.
 */
struct ether_hdr {
	struct ether_addr d_addr; /**< Destination address. */
	struct ether_addr s_addr; /**< Source address. */
	uint16_t ether_type;      /**< Frame type. */
} ;

/**
 * IPv4 Header
 */
struct ipv4_hdr {
	uint8_t  version_ihl;		/**< version and header length */
	uint8_t  type_of_service;	/**< type of service */
	uint16_t total_length;		/**< length of packet */
	uint16_t packet_id;		/**< packet ID */
	uint16_t fragment_offset;	/**< fragmentation offset */
	uint8_t  time_to_live;		/**< time to live */
	uint8_t  next_proto_id;		/**< protocol ID */
	uint16_t hdr_checksum;		/**< header checksum */
	uint32_t src_addr;		/**< source address */
	uint32_t dst_addr;		/**< destination address */
} ;

/**
 * TCP Header
 */
struct tcp_hdr {
	uint16_t src_port;  /**< TCP source port. */
	uint16_t dst_port;  /**< TCP destination port. */
	uint32_t sent_seq;  /**< TX data sequence number. */
	uint32_t recv_ack;  /**< RX data acknowledgement sequence number. */
	uint8_t  data_off;  /**< Data offset. */
	uint8_t  tcp_flags; /**< TCP flags */
	uint16_t rx_win;    /**< RX flow control window. */
	uint16_t cksum;     /**< TCP checksum. */
	uint16_t tcp_urp;   /**< TCP urgent pointer, if any. */
} ;



#define rte_be_to_cpu_16(x) rte_bswap16(x)


/**
 * Fast copy an Ethernet address.
 *
 * @param ea_from
 *   A pointer to a ether_addr structure holding the Ethernet address to copy.
 * @param ea_to
 *   A pointer to a ether_addr structure where to copy the Ethernet address.
 */
static inline void ether_addr_copy(const struct ether_addr *ea_from,
				   struct ether_addr *ea_to)
{
#ifdef __INTEL_COMPILER
	uint16_t *from_words = (uint16_t *)(ea_from->addr_bytes);
	uint16_t *to_words   = (uint16_t *)(ea_to->addr_bytes);

	to_words[0] = from_words[0];
	to_words[1] = from_words[1];
	to_words[2] = from_words[2];
#else
	/*
	 * Use the common way, because of a strange gcc warning.
	 */
	*ea_to = *ea_from;
#endif
}

/**
 * @internal Calculate a sum of all words in the buffer.
 * Helper routine for the rte_raw_cksum().
 *
 * @param buf
 *   Pointer to the buffer.
 * @param len
 *   Length of the buffer.
 * @param sum
 *   Initial value of the sum.
 * @return
 *   sum += Sum of all words in the buffer.
 */
static inline uint32_t
__rte_raw_cksum(const void *buf, size_t len, uint32_t sum)
{
	/* workaround gcc strict-aliasing warning */
	uintptr_t ptr = (uintptr_t)buf;
	const uint16_t *u16 = (const uint16_t *)ptr;

	while (len >= (sizeof(*u16) * 4)) {
		sum += u16[0];
		sum += u16[1];
		sum += u16[2];
		sum += u16[3];
		len -= sizeof(*u16) * 4;
		u16 += 4;
	}
	while (len >= sizeof(*u16)) {
		sum += *u16;
		len -= sizeof(*u16);
		u16 += 1;
	}

	/* if length is in odd bytes */
	if (len == 1)
		sum += *((const uint8_t *)u16);

	return sum;
}

/**
 * @internal Reduce a sum to the non-complemented checksum.
 * Helper routine for the rte_raw_cksum().
 *
 * @param sum
 *   Value of the sum.
 * @return
 *   The non-complemented checksum.
 */
static inline uint16_t
__rte_raw_cksum_reduce(uint32_t sum)
{
	sum = ((sum & 0xffff0000) >> 16) + (sum & 0xffff);
	sum = ((sum & 0xffff0000) >> 16) + (sum & 0xffff);
	return (uint16_t)sum;
}

/**
 * Process the non-complemented checksum of a buffer.
 *
 * @param buf
 *   Pointer to the buffer.
 * @param len
 *   Length of the buffer.
 * @return
 *   The non-complemented checksum.
 */
static inline uint16_t
rte_raw_cksum(const void *buf, size_t len)
{
	uint32_t sum;

	sum = __rte_raw_cksum(buf, len, 0);
	return __rte_raw_cksum_reduce(sum);
}


/**
 * Process the IPv4 checksum of an IPv4 header.
 *
 * The checksum field must be set to 0 by the caller.
 *
 * @param ipv4_hdr
 *   The pointer to the contiguous IPv4 header.
 * @return
 *   The complemented checksum to set in the IP packet.
 */
static inline uint16_t
rte_ipv4_cksum(const struct ipv4_hdr *ipv4_hdr)
{
	uint16_t cksum;
	cksum = rte_raw_cksum(ipv4_hdr, sizeof(struct ipv4_hdr));
	return ((cksum == 0xffff) ? cksum : ~cksum);
}

/**
 * Process the pseudo-header checksum of an IPv4 header.
 *
 * The checksum field must be set to 0 by the caller.
 *
 * Depending on the ol_flags, the pseudo-header checksum expected by the
 * drivers is not the same. For instance, when TSO is enabled, the IP
 * payload length must not be included in the packet.
 *
 * When ol_flags is 0, it computes the standard pseudo-header checksum.
 *
 * @param ipv4_hdr
 *   The pointer to the contiguous IPv4 header.
 * @param ol_flags
 *   The ol_flags of the associated mbuf.
 * @return
 *   The non-complemented checksum to set in the L4 header.
 */
static inline uint16_t
rte_ipv4_phdr_cksum(const struct ipv4_hdr *ipv4_hdr, uint64_t ol_flags)
{
	struct ipv4_psd_header {
		uint32_t src_addr; /* IP address of source host. */
		uint32_t dst_addr; /* IP address of destination host. */
		uint8_t  zero;     /* zero. */
		uint8_t  proto;    /* L4 protocol type. */
		uint16_t len;      /* L4 length. */
	} psd_hdr;

	psd_hdr.src_addr = ipv4_hdr->src_addr;
	psd_hdr.dst_addr = ipv4_hdr->dst_addr;
	psd_hdr.zero = 0;
	psd_hdr.proto = ipv4_hdr->next_proto_id;
	if (ol_flags & PKT_TX_TCP_SEG) {
		psd_hdr.len = 0;
	} else {
		psd_hdr.len = rte_cpu_to_be_16(
			(uint16_t)(rte_be_to_cpu_16(ipv4_hdr->total_length)
				- sizeof(struct ipv4_hdr)));
	}
	return rte_raw_cksum(&psd_hdr, sizeof(psd_hdr));
}


/**
 * Process the IPv4 UDP or TCP checksum.
 *
 * The IPv4 header should not contains options. The IP and layer 4
 * checksum must be set to 0 in the packet by the caller.
 *
 * @param ipv4_hdr
 *   The pointer to the contiguous IPv4 header.
 * @param l4_hdr
 *   The pointer to the beginning of the L4 header.
 * @return
 *   The complemented checksum to set in the IP packet.
 */
static inline uint16_t
rte_ipv4_udptcp_cksum(const struct ipv4_hdr *ipv4_hdr, const void *l4_hdr)
{
	uint32_t cksum;
	uint32_t l4_len;

	l4_len = rte_be_to_cpu_16(ipv4_hdr->total_length) -
		sizeof(struct ipv4_hdr);

   
	cksum = rte_raw_cksum(l4_hdr, l4_len);

	cksum += rte_ipv4_phdr_cksum(ipv4_hdr, 0);

	cksum = ((cksum & 0xffff0000) >> 16) + (cksum & 0xffff);
	cksum = (~cksum) & 0xffff;
	if (cksum == 0)
		cksum = 0xffff;

	return cksum;
}




#endif /* __RTE_H__ */

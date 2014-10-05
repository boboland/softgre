/**
 * Copyright (C) 2014 Jorge Pereira <jpereiran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef PAYLOAD_H_
#define PAYLOAD_H_

#include "general.h"


/* default snap length (maximum bytes per packet to capture) */
#define SNAP_LEN            1518

/**
 * from rfc2784
 * The GRE packet header has the form:
 *
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |C|       Reserved0       | Ver |         Protocol Type         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      Checksum (optional)      |       Reserved1 (Optional)    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define GRE_LENGHT          4 /* bytes */

struct payload_gre {
    unsigned has_checksum :  1; // Checksum Present (bit 0)
    unsigned reserved0    : 12; // Reserved0 (bits 1-12)
    unsigned ver          :  3; // Version Number (bits 13-15)
    unsigned type         : 16; // Protocol Type (2 octets)
    unsigned checksum     : 16; // Checksum (2 octets)
    unsigned reserved1    : 16; // Reserved1 (2 octets)
};

struct payload_config {
    struct bpf_program fp;         /* compiled filter program (expression) */
    pcap_t *handle;                /* packet capture handle */
    char errbuf[PCAP_ERRBUF_SIZE]; /* error buffer */
    bpf_u_int32 mask;              /* subnet mask */
    bpf_u_int32 net;               /* ip */
};

/**
*/
struct vlan_tag {
    uint16_t vlan_tpid;      /* ETH_P_8021Q */
    uint16_t vlan_tci;       /* VLAN TCI */
};

struct payload_config *payload_config_get();

int
payload_loop_init();

int
payload_loop_run();

void
payload_loop_end();

void
payload_handler_packet(u_char *args,
                       const struct pcap_pkthdr *header,
                       const u_char *packet);

#endif /*PAYLOAD_H_*/


#pragma once

#include <libcoin-seeder/net-addr.h>

#include <libcoin-seeder/var-int.h>

typedef struct addr_payload {
    var_int_s count;
    net_addr_s *addr_list;
} addr_payload_s;

void free_addr_payload(addr_payload_s);

typedef struct parsed_addr_payload {
    int parsed_bytes;
    addr_payload_s addr_payload;
} parsed_addr_payload_s;

parsed_addr_payload_s parse_addr_payload(bytes_s);

void free_parsed_addr_payload(parsed_addr_payload_s);

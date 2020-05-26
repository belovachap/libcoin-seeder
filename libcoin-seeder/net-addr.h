#pragma once

#include <stdbool.h>

#include <stdint.h>

#include <libcoin-seeder/bytes.h>

typedef struct net_addr {
    uint32_t time; // not present in version message
    uint64_t services;
    char ip[16];
    uint16_t port; // network byte order
} net_addr_s;

bytes_s serialize_net_addr(net_addr_s, bool);

typedef struct parsed_net_addr {
    net_addr_s net_addr;
    int parsed_bytes;
} parsed_net_addr_s;

parsed_net_addr_s parse_net_addr(bytes_s, bool);

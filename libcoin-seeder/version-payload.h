#pragma once

#include <libcoin-seeder/net-addr.h>

#include <libcoin-seeder/var-str.h>

typedef struct version_payload {
    int32_t version;
    uint64_t services;
    int64_t timestamp;
    net_addr_s addr_recv;
    net_addr_s addr_from;
    uint64_t nonce;
    var_str_s user_agent;
    int32_t start_height;
    bool relay;
} version_payload_s;

void free_version_payload(version_payload_s);

bytes_s serialize_version_payload(version_payload_s);

typedef struct parsed_version_payload {
    version_payload_s version_payload;
    int parsed_bytes;
} parsed_version_payload_s;

parsed_version_payload_s parse_version_payload(bytes_s);

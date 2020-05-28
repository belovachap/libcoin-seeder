#include <libcoin-seeder/version-payload.h>

uint64_t random_nonce() {
    uint64_t out;
    byte *pout = (byte *)&out;
    for(int i = 0; i < 8; i++) {
        pout[i] = rand() % 16;
    }

    return out;
}

version_payload_s new_version_payload(net_addr_s addr_recv, net_addr_s addr_from, var_str_s user_agent) {
    return (version_payload_s) {
        .version = 70015,
        .services = 0,
        .timestamp = time(NULL),
        .addr_recv = addr_recv,
        .addr_from = addr_from,
        .nonce = random_nonce(),
        .user_agent = user_agent,
        .start_height = 0,
        .relay = false,
    };
}

void free_version_payload(version_payload_s version_payload) {
    free_var_str(version_payload.user_agent);
}

bytes_s serialize_version_payload(version_payload_s version_payload) {
    bytes_s var_str_bytes = serialize_var_str(version_payload.user_agent);
    int length = 4 + 8 + 8 + 2 * sizeof(net_addr_s) + 8 + var_str_bytes.length + 4 + 1;
    byte *buffer = malloc(length);

    return (bytes_s){.length=length, .buffer=buffer};
}

parsed_version_payload_s parse_version_payload(bytes_s bytes) {

}

void free_parsed_version_payload(parsed_version_payload_s parsed_version_payload) {
    free_var_str(parsed_version_payload.version_payload.user_agent);
}

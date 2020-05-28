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
    bytes_s addr_recv_bytes = serialize_net_addr(version_payload.addr_recv, false);
    bytes_s addr_from_bytes = serialize_net_addr(version_payload.addr_from, false);
    bytes_s user_agent_bytes = serialize_var_str(version_payload.user_agent);

    int length = 4 + 8 + 8 + 8 + 4 + 1; // version + services + timestamp + nonce + start_height + relay
    length += addr_recv_bytes.length;
    length += addr_from_bytes.length;
    length += user_agent_bytes.length;
    byte *buffer = malloc(length);

    int offset = 0;
    char *le = int32_t_to_little_endian(version_payload.version);
    memcpy(buffer+offset, le, 4);
    offset += 4;
    free(le);

    le = uint64_t_to_little_endian(version_payload.services);
    memcpy(buffer+offset, le, 8);
    offset += 8;
    free(le);

    le = int64_t_to_little_endian(version_payload.timestamp);
    memcpy(buffer+offset, le, 8);
    offset += 8;
    free(le);

    memcpy(buffer+offset, addr_recv_bytes.buffer, addr_recv_bytes.length);
    offset += addr_recv_bytes.length;
    free_bytes(addr_recv_bytes);

    memcpy(buffer+offset, addr_from_bytes.buffer, addr_from_bytes.length);
    offset += addr_from_bytes.length;
    free_bytes(addr_from_bytes);

    le = uint64_t_to_little_endian(version_payload.nonce);
    memcpy(buffer+offset, le, 8);
    offset += 8;
    free(le);

    memcpy(buffer+offset, user_agent_bytes.buffer, user_agent_bytes.length);
    offset += user_agent_bytes.length;
    free_bytes(user_agent_bytes);

    le = int32_t_to_little_endian(version_payload.start_height);
    memcpy(buffer+offset, le, 4);
    offset += 4;
    free(le);

    memcpy(buffer+offset, &version_payload.relay, 1);

    return (bytes_s){.length=length, .buffer=buffer};
}

parsed_version_payload_s parse_version_payload(bytes_s bytes) {
    version_payload_s version_payload;
    bytes_s window;
    int parsed_bytes = 0;

    version_payload.version = int32_t_from_little_endian(bytes.buffer);
    parsed_bytes += 4;

    version_payload.services = uint64_t_from_little_endian(bytes.buffer+parsed_bytes);
    parsed_bytes += 8;

    version_payload.timestamp = int64_t_from_little_endian(bytes.buffer+parsed_bytes);
    parsed_bytes += 8;

    window.length = bytes.length - parsed_bytes;
    window.buffer = bytes.buffer + parsed_bytes;
    parsed_net_addr_s parsed_addr_recv = parse_net_addr(window, false);
    version_payload.addr_recv = parsed_addr_recv.net_addr;
    parsed_bytes += parsed_addr_recv.parsed_bytes;

    window.length = bytes.length - parsed_bytes;
    window.buffer = bytes.buffer + parsed_bytes;
    parsed_net_addr_s parsed_addr_from = parse_net_addr(window, false);
    version_payload.addr_from = parsed_addr_from.net_addr;
    parsed_bytes += parsed_addr_from.parsed_bytes;

    version_payload.nonce = uint64_t_from_little_endian(bytes.buffer+parsed_bytes);
    parsed_bytes += 8;

    window.length = bytes.length - parsed_bytes;
    window.buffer = bytes.buffer + parsed_bytes;
    parsed_var_str_s parsed_user_agent = parse_var_str(window);
    version_payload.user_agent = parsed_user_agent.var_str;
    parsed_bytes += parsed_user_agent.parsed_bytes;

    version_payload.start_height = int32_t_from_little_endian(bytes.buffer+parsed_bytes);
    parsed_bytes += 4;

    version_payload.relay = bytes.buffer[parsed_bytes];
    parsed_bytes += 1;

    return (parsed_version_payload_s){.parsed_bytes=parsed_bytes, .version_payload=version_payload};
}

void free_parsed_version_payload(parsed_version_payload_s parsed_version_payload) {
    free_var_str(parsed_version_payload.version_payload.user_agent);
}

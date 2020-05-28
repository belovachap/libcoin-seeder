#include <libcoin-seeder/net-addr.h>

char *address_to_ip(char *address) {
    char *obuf = malloc(4);
    int ret_val = inet_pton(AF_INET, address, obuf);
    if (ret_val != 1) {
        free(obuf);
        return NULL;
    }

    char *ip = malloc(16);
    char prefix[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF};
    memcpy(ip, prefix, 12);
    memcpy(ip+12, obuf, 4);
    free(obuf);

    return ip;
}

net_addr_s new_net_addr(uint32_t time, uint64_t services, char *ip, uint16_t port) {
    net_addr_s net_addr = {.time=time, .services=services, .port=port};
    memcpy(net_addr.ip, ip, 16);
    return net_addr;
}

bytes_s serialize_net_addr(net_addr_s net_addr, bool include_time) {
    int length;
    char *buffer;
    int offset;
    byte *be, *le;

    if(include_time) {
        length = NET_ADDR_LENGTH;
        buffer = malloc(length);
        le = uint32_t_to_little_endian(net_addr.time);
        memcpy(buffer, le, 4);
        free(le);
        offset = 4;
    }
    else {
        length = NET_ADDR_LENGTH - 4;
        buffer = malloc(length);
        offset = 0;
    }

    le = uint64_t_to_little_endian(net_addr.services);
    memcpy(buffer+offset, le, 8);
    free(le);
    offset += 8;

    memcpy(buffer+offset, net_addr.ip, 16);
    offset += 16;

    be = uint16_t_to_big_endian(net_addr.port);
    memcpy(buffer+offset, be, 2);
    free(be);

    return (bytes_s){.length=length, .buffer=buffer};
}

parsed_net_addr_s parse_net_addr(bytes_s bytes, bool include_time) {
    net_addr_s net_addr = {.time=0};
    int parsed_bytes = 0;

    if(include_time) {
        net_addr.time = uint32_t_from_little_endian(bytes.buffer);
        parsed_bytes += 4;
    }

    net_addr.services = uint64_t_from_little_endian(bytes.buffer+parsed_bytes);
    parsed_bytes += 8;

    memcpy(net_addr.ip, bytes.buffer+parsed_bytes, 16);
    parsed_bytes += 16;

    net_addr.port = uint16_t_from_big_endian(bytes.buffer+parsed_bytes);
    parsed_bytes += 2;

    return (parsed_net_addr_s){.parsed_bytes=parsed_bytes, .net_addr=net_addr};
}

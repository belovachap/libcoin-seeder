typedef struct net_addr {
    uint32_t time; // not present in version message
    uint64_t services;
    char ip[16];
    uint16_t port; // network byte order
} net_addr_s;

typedef struct parsed_net_addr {
    net_addr_s net_addr;
    int parsed_bytes;
} parsed_net_addr_s;


parsed_net_addr_s parse_net_addr(bytes_s bytes, bool include_time) {
}

bytes_s serialize_net_addr(net_addr_s net_addr, bool include_time) {
}

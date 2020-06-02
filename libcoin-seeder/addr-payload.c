#include <libcoin-seeder/addr-payload.h>

void free_addr_payload(addr_payload_s addr_payload) {
    free(addr_payload.addr_list);
}

parsed_addr_payload_s parse_addr_payload(bytes_s bytes) {
    int parsed_bytes = 0;
    bytes_s window;

    window.length = bytes.length - parsed_bytes;
    window.buffer = bytes.buffer + parsed_bytes;
    parsed_var_int_s parsed_var_int = parse_var_int(window);
    parsed_bytes += parsed_var_int.parsed_bytes;

    net_addr_s *addr_list = malloc(parsed_var_int.var_int.value * sizeof(net_addr_s));
    for(int i = 0; i < parsed_var_int.var_int.value; i++) {
        window.length = bytes.length - parsed_bytes;
        window.buffer = bytes.buffer + parsed_bytes;
        parsed_net_addr_s parsed_net_addr = parse_net_addr(window, true);
        addr_list[i] = parsed_net_addr.net_addr;
        parsed_bytes += parsed_net_addr.parsed_bytes;
    }

    addr_payload_s addr_payload = {.count=parsed_var_int.var_int, .addr_list=addr_list};

    return (parsed_addr_payload_s){.parsed_bytes=parsed_bytes, .addr_payload=addr_payload};
}

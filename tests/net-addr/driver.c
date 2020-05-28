#include <assert.h>

#include <libcoin-seeder/net-addr.h>

int main ()
{
    char *address = "10.0.0.1";
    char address_ip[16] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xFF, 0xFF, 0x0A, 0x00, 0x00, 0x01,
    };

    // address_to_ip
    {
        char *ip = address_to_ip(address);
        assert(ip != NULL);
        assert(memcmp(ip, address_ip, 16) == 0);
        free(ip);
    }

    // net_addr without time
    {
        net_addr_s net_addr = new_net_addr(0, 1, address_ip, 8333);

        bytes_s bytes = serialize_net_addr(net_addr, false);
        assert(bytes.length == (NET_ADDR_LENGTH - 4));

        parsed_net_addr_s parsed_net_addr = parse_net_addr(bytes, false);
        assert(parsed_net_addr.net_addr.time == 0);
        assert(parsed_net_addr.net_addr.services == 1);
        assert(memcmp(parsed_net_addr.net_addr.ip, address_ip, 16) == 0);
        assert(parsed_net_addr.net_addr.port == 8333);

        free_bytes(bytes);
    }

    // net_addr with time
    {
        net_addr_s net_addr = new_net_addr(1000, 1, address_ip, 8333);

        bytes_s bytes = serialize_net_addr(net_addr, true);
        assert(bytes.length == NET_ADDR_LENGTH);

        parsed_net_addr_s parsed_net_addr = parse_net_addr(bytes, true);
        assert(parsed_net_addr.net_addr.time == 1000);
        assert(parsed_net_addr.net_addr.services == 1);
        assert(memcmp(parsed_net_addr.net_addr.ip, address_ip, 16) == 0);
        assert(parsed_net_addr.net_addr.port == 8333);

        free_bytes(bytes);
    }
}

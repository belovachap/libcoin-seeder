#include <assert.h>

#include <string.h>

#include <libcoin-seeder/version-payload.h>

int main ()
{
    // random_nonce
    {
        uint64_t one = random_nonce();
        uint64_t two = random_nonce();
        assert(one != two);
    }

    // serialize/parse_version_payload
    {
        net_addr_s to = {};
        net_addr_s from = {};
        char *string = heap_string("coin-seeder");
        var_str_s user_agent = new_var_str(string);
        version_payload_s version_payload = new_version_payload(to, from, user_agent);

        bytes_s bytes = serialize_version_payload(version_payload);
        parsed_version_payload_s parsed_version_payload = parse_version_payload(bytes);
        assert(strcmp(parsed_version_payload.version_payload.user_agent.string, "coin-seeder") == 0);

        free_parsed_version_payload(parsed_version_payload);
        free_bytes(bytes);
        free_version_payload(version_payload);
    }
}

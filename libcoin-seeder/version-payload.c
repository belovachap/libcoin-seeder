#include <libcoin-seeder/version-payload.h>

void free_version_payload(version_payload_s version_payload) {
    free_var_str(version_payload.user_agent);
}

bytes_s serialize_version_payload(version_payload_s version_payload) {
}

parsed_version_payload_s parse_version_payload(bytes_s bytes) {
}

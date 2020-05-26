#include <assert.h>

#include <libcoin-seeder/version-payload.h>

int main ()
{
    // serialize/parse_version_payload
    {
        version_payload_s version_payload = {
            .user_agent=new_var_str("User Agent")
        };
    }
}

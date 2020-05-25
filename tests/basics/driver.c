#include <assert.h>

#include <libcoin-seeder/coin-seeder.h>

int main ()
{
    // to_little_endian
    {
        bytes_s le = to_little_endian(0xAABBCCDD);
        assert(le.length == 4);
        assert(le.buffer[0] == 0xDD);
        assert(le.buffer[1] == 0xCC);
        assert(le.buffer[2] == 0xBB);
        assert(le.buffer[3] == 0xAA);
        free_bytes(le);
    }

    // from_little_endian
    {
        byte buffer[4] = {0xDD, 0xCC, 0xBB, 0xAA};
        bytes_s bytes = {.buffer=buffer, .length=4};
        uint32_t i = from_little_endian(bytes);
        assert(i == 0xAABBCCDD);
    }

    return 0;
}


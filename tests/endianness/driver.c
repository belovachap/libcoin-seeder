#include <assert.h>

#include <libcoin-seeder/endianness.h>

int main ()
{
    // to_little_endian
    {
        byte *le = to_little_endian(0xAABBCCDD);
        assert(le[0] == 0xDD);
        assert(le[1] == 0xCC);
        assert(le[2] == 0xBB);
        assert(le[3] == 0xAA);
        free(le);
    }

    // from_little_endian
    {
        byte le[4] = {0xDD, 0xCC, 0xBB, 0xAA};
        uint32_t i = from_little_endian(le);
        assert(i == 0xAABBCCDD);
    }
}


#include <assert.h>

#include <libcoin-seeder/endianness.h>

int main ()
{
    // uint16_t_to_big_endian
    {
        byte *be = uint16_t_to_big_endian(8333);
        assert(be[0] == 0x20);
        assert(be[1] == 0x8D);
        free(be);
    }

    // uint16_t_from_big_endian
    {
        byte be[2] = {0x20, 0x8D};
        uint16_t i = uint16_t_from_big_endian(be);
        assert(i == 8333);
    }

    // uint32_t_to_little_endian
    {
        byte *le = uint32_t_to_little_endian(0xAABBCCDD);
        assert(le[0] == 0xDD);
        assert(le[1] == 0xCC);
        assert(le[2] == 0xBB);
        assert(le[3] == 0xAA);
        free(le);
    }

    // uint32_t_from_little_endian
    {
        byte le[4] = {0xDD, 0xCC, 0xBB, 0xAA};
        uint32_t i = uint32_t_from_little_endian(le);
        assert(i == 0xAABBCCDD);
    }
}


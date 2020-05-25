#include <libcoin-seeder/coin-seeder.h>

#include <errno.h>

uchar *to_little_endian(const uint32_t i) {
    uchar *b = malloc(4);
    uchar *pi = (uchar *)&i;
    b[0] = pi[0];
    b[1] = pi[1];
    b[2] = pi[2];
    b[3] = pi[3];
    return b;
}

uint32_t from_little_endian(const uchar *b) {
    uint32_t i;
    uchar *pi = (uchar *)&i;
    pi[0] = b[0];
    pi[1] = b[1];
    pi[2] = b[2];
    pi[3] = b[3];
    return i;
}

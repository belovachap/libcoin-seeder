#include <libcoin-seeder/endianness.h>

byte *to_little_endian(uint32_t i) {
    byte *buffer = malloc(4);
    byte *pi = (byte *)&i;
    buffer[0] = pi[0];
    buffer[1] = pi[1];
    buffer[2] = pi[2];
    buffer[3] = pi[3];
    return buffer;
}

uint32_t from_little_endian(byte *buffer) {
    uint32_t i;
    byte *pi = (byte *)&i;
    pi[0] = buffer[0];
    pi[1] = buffer[1];
    pi[2] = buffer[2];
    pi[3] = buffer[3];
    return i;
}

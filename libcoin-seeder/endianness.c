#include <stdlib.h>

#include <libcoin-seeder/endianness.h>

bytes_s to_little_endian(uint32_t i) {
    int length = 4;
    byte *buffer = malloc(length);
    byte *pi = (byte *)&i;
    buffer[0] = pi[0];
    buffer[1] = pi[1];
    buffer[2] = pi[2];
    buffer[3] = pi[3];
    return (bytes_s){.buffer=buffer, .length=length};
}

uint32_t from_little_endian(bytes_s bytes) {
    uint32_t i;
    byte *pi = (byte *)&i;
    pi[0] = bytes.buffer[0];
    pi[1] = bytes.buffer[1];
    pi[2] = bytes.buffer[2];
    pi[3] = bytes.buffer[3];
    return i;
}

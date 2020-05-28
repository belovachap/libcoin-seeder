#include <libcoin-seeder/endianness.h>

byte *uint16_t_to_big_endian(uint16_t i) {
    byte *buffer = malloc(2);
    byte *pi = (byte *)&i;
    buffer[0] = pi[1];
    buffer[1] = pi[0];
    return buffer;
}

uint16_t uint16_t_from_big_endian(byte *buffer) {
    uint16_t i;
    byte *pi = (byte *)&i;
    pi[0] = buffer[1];
    pi[1] = buffer[0];
    return i;
}

byte *int32_t_to_little_endian(int32_t i) {
    byte *buffer = malloc(4);
    byte *pi = (byte *)&i;
    buffer[0] = pi[0];
    buffer[1] = pi[1];
    buffer[2] = pi[2];
    buffer[3] = pi[3];
    return buffer;
}

int32_t int32_t_from_little_endian(byte *buffer) {
    int32_t i;
    byte *pi = (byte *)&i;
    pi[0] = buffer[0];
    pi[1] = buffer[1];
    pi[2] = buffer[2];
    pi[3] = buffer[3];
    return i;
}

byte *uint32_t_to_little_endian(uint32_t i) {
    byte *buffer = malloc(4);
    byte *pi = (byte *)&i;
    buffer[0] = pi[0];
    buffer[1] = pi[1];
    buffer[2] = pi[2];
    buffer[3] = pi[3];
    return buffer;
}

uint32_t uint32_t_from_little_endian(byte *buffer) {
    uint32_t i;
    byte *pi = (byte *)&i;
    pi[0] = buffer[0];
    pi[1] = buffer[1];
    pi[2] = buffer[2];
    pi[3] = buffer[3];
    return i;
}

byte *int64_t_to_little_endian(int64_t i) {
    byte *buffer = malloc(8);
    byte *pi = (byte *)&i;
    buffer[0] = pi[0];
    buffer[1] = pi[1];
    buffer[2] = pi[2];
    buffer[3] = pi[3];
    buffer[4] = pi[4];
    buffer[5] = pi[5];
    buffer[6] = pi[6];
    buffer[7] = pi[7];
    return buffer;
}

int64_t int64_t_from_little_endian(byte *buffer) {
    int64_t i;
    byte *pi = (byte *)&i;
    pi[0] = buffer[0];
    pi[1] = buffer[1];
    pi[2] = buffer[2];
    pi[3] = buffer[3];
    pi[4] = buffer[4];
    pi[5] = buffer[5];
    pi[6] = buffer[6];
    pi[7] = buffer[7];
    return i;
}

byte *uint64_t_to_little_endian(uint64_t i) {
    byte *buffer = malloc(8);
    byte *pi = (byte *)&i;
    buffer[0] = pi[0];
    buffer[1] = pi[1];
    buffer[2] = pi[2];
    buffer[3] = pi[3];
    buffer[4] = pi[4];
    buffer[5] = pi[5];
    buffer[6] = pi[6];
    buffer[7] = pi[7];
    return buffer;
}

uint64_t uint64_t_from_little_endian(byte *buffer) {
    uint64_t i;
    byte *pi = (byte *)&i;
    pi[0] = buffer[0];
    pi[1] = buffer[1];
    pi[2] = buffer[2];
    pi[3] = buffer[3];
    pi[4] = buffer[4];
    pi[5] = buffer[5];
    pi[6] = buffer[6];
    pi[7] = buffer[7];
    return i;
}

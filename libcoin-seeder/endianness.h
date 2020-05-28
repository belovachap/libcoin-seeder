#pragma once

#include <stdint.h>

#include <stdlib.h>

#include <libcoin-seeder/bytes.h>

byte *uint16_t_to_big_endian(uint16_t);
uint16_t uint16_t_from_big_endian(byte *);

byte *uint32_t_to_little_endian(uint32_t);
uint32_t uint32_t_from_little_endian(byte *);

byte *uint64_t_to_little_endian(uint64_t);
uint64_t uint64_t_from_little_endian(byte *);


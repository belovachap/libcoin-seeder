#pragma once

#include <stdint.h>

#include <stdlib.h>

#include <libcoin-seeder/bytes.h>

byte *to_little_endian(uint32_t);

uint32_t from_little_endian(byte *);

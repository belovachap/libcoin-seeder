#pragma once

#include <stdint.h>

#include <libcoin-seeder/bytes.h>

bytes_s to_little_endian(uint32_t);
uint32_t from_little_endian(bytes_s);

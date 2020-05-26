#pragma once

#include <stdint.h>

#include <libcoin-seeder/bytes.h>

typedef struct var_int {
    uint64_t value;
} var_int_s;

bytes_s serialize_var_int(var_int_s);

typedef struct parsed_var_int {
    int parsed_bytes;
    var_int_s var_int;
} parsed_var_int_s;

parsed_var_int_s parse_var_int(bytes_s);


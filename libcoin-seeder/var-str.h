#pragma once

#include <libcoin-seeder/var-int.h>

typedef struct var_str {
    var_int_s length;
    char *string;
} var_str_s;

var_str_s new_var_str(char *);

void free_var_str(var_str_s);

bytes_s serialize_var_str(var_str_s);

typedef struct parsed_var_str {
    var_str_s var_str;
    int parsed_bytes;
} parsed_var_str_s;

parsed_var_str_s parse_var_str(bytes_s);

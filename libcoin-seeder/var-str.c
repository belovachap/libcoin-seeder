#include <stdlib.h>

#include <string.h>

#include <libcoin-seeder/var-str.h>

var_str_s new_var_str(char *string) {
    return (var_str_s){.length=strlen(string), .string=string};
}

void free_var_str(var_str_s var_str) {
    free(var_str.string);
}

bytes_s serialize_var_str(var_str_s var_str) {
    bytes_s var_int_bytes = serialize_var_int(var_str.length);

    int length = var_int_bytes.length + var_str.length.value;
    byte *buffer = malloc(length);
    memcpy(buffer, var_int_bytes.buffer, var_int_bytes.length);
    memcpy(buffer+var_int_bytes.length, var_str.string, var_str.length.value);

    free_bytes(var_int_bytes);

    return (bytes_s){.buffer=buffer, .length=length};
}

parsed_var_str_s parse_var_str(bytes_s bytes) {
    parsed_var_int_s parsed_var_int = parse_var_int(bytes);

    char *string = malloc(parsed_var_int.var_int.value + 1);
    memset(string, 0, parsed_var_int.var_int.value + 1);
    memcpy(string, bytes.buffer+parsed_var_int.parsed_bytes, parsed_var_int.var_int.value);

    var_str_s var_str = {.string=string, .length=parsed_var_int.var_int};

    return (parsed_var_str_s){.var_str=var_str, .parsed_bytes=parsed_var_int.parsed_bytes+parsed_var_int.var_int.value};
}

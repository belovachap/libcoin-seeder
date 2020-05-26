#include <stdlib.h>

#include <libcoin-seeder/var-int.h>

bytes_s serialize_var_int(var_int_s var_int) {
    int length;
    byte *buffer;
    byte *value = (byte *)&(var_int.value);
    if(var_int.value < 0xFD) {
        length = 1;
        buffer = malloc(length);
        buffer[0] = value[0];
    }
    else if (var_int.value <= 0xFFFF){
        length = 3;
        buffer = malloc(length);
        buffer[0] = 0xFD;
        buffer[1] = value[0];
        buffer[2] = value[1];
    }
    else if (var_int.value <= 0xFFFFFFFF) {
        length = 5;
        buffer = malloc(length);
        buffer[0] = 0xFE;
        buffer[1] = value[0];
        buffer[2] = value[1];
        buffer[3] = value[2];
        buffer[4] = value[3];
    }
    else {
        length = 9;
        buffer = malloc(length);
        buffer[0] = 0xFF;
        buffer[1] = value[0];
        buffer[2] = value[1];
        buffer[3] = value[2];
        buffer[4] = value[3];
        buffer[5] = value[4];
        buffer[6] = value[5];
        buffer[7] = value[6];
        buffer[8] = value[7];
    }

    return (bytes_s){.buffer=buffer, .length=length};
}

parsed_var_int_s parse_var_int(bytes_s bytes) {
    int parsed_bytes;
    var_int_s var_int = {.value=0};
    byte *value = (byte *)&(var_int.value);
    if (bytes.buffer[0] < 0xFD) {
        parsed_bytes = 1;
        value[0] = bytes.buffer[0];
    }
    else if (bytes.buffer[0] == 0xFD) {
        parsed_bytes = 3;
        value[0] = bytes.buffer[1];
        value[1] = bytes.buffer[2];
    }
    else if (bytes.buffer[0] == 0xFE) {
        parsed_bytes = 5;
        value[0] = bytes.buffer[1];
        value[1] = bytes.buffer[2];
        value[2] = bytes.buffer[3];
        value[3] = bytes.buffer[4];
    }
    else {
        parsed_bytes = 9;
        value[0] = bytes.buffer[1];
        value[1] = bytes.buffer[2];
        value[2] = bytes.buffer[3];
        value[3] = bytes.buffer[4];
        value[4] = bytes.buffer[5];
        value[5] = bytes.buffer[6];
        value[6] = bytes.buffer[7];
        value[7] = bytes.buffer[8];
    }

    return (parsed_var_int_s){.parsed_bytes=parsed_bytes, .var_int=var_int};
}

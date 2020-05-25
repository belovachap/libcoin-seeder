#include <stdlib.h>

#include <libcoin-seeder/var-int.h>

parsed_var_int_s parse_var_int(bytes_s bytes) {
}

bytes_s serialize_var_int(var_int_s var_int) {
    int length;
    byte *buffer;
    byte *value = (byte *)&(var_int.value);
    if(var_int.value < 0xFD) {
        length = 1;
        buffer = malloc(length);
        buffer[0] = value[7];
    }
    else if (var_int.value <= 0xFFFF){
        length = 3;
        buffer = malloc(length);
        buffer[0] = 0xFD;
        buffer[1] = value[7];
        buffer[2] = value[6];
    }
    else if (var_int.value <= 0xFFFFFFFF) {
        length = 5;
        buffer = malloc(length);
        buffer[0] = 0xFE;
        buffer[1] = value[7];
        buffer[2] = value[6];
        buffer[3] = value[5];
        buffer[4] = value[4];
    }
    else {
        length = 9;
        buffer = malloc(length);
        buffer[0] = 0xFF;
        buffer[1] = value[7];
        buffer[2] = value[6];
        buffer[3] = value[5];
        buffer[4] = value[4];
        buffer[5] = value[3];
        buffer[6] = value[2];
        buffer[7] = value[1];
        buffer[8] = value[0];
    }

    return (bytes_s){.buffer=buffer, .length=length};
}

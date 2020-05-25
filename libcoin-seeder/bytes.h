#pragma once

typedef unsigned char byte;

typedef struct bytes {
    byte *buffer;
    int length;
} bytes_s;

void free_bytes(bytes_s);


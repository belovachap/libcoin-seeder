#include <stdlib.h>

#include <libcoin-seeder/bytes.h>

void free_bytes(bytes_s bytes) {
    free(bytes.buffer);
}


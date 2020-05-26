#include <assert.h>

#include <stdbool.h>

#include <libcoin-seeder/var-int.h>

int main ()
{
    // serialize/parse_var_int - one byte var_int
    {
        var_int_s var_int = {.value=0xAA};

        bytes_s bytes = serialize_var_int(var_int);
        assert(bytes.length == 1);
        assert(bytes.buffer[0] == 0xAA);

        parsed_var_int_s parsed_var_int = parse_var_int(bytes);
        assert(parsed_var_int.parsed_bytes == 1);
        assert(parsed_var_int.var_int.value == 0xAA);

        free_bytes(bytes);
    }

    // serialize/parse_var_int - two byte var int
    {
        var_int_s var_int = {.value=0xFD};

        bytes_s bytes = serialize_var_int(var_int);
        assert(bytes.length == 3);
        assert(bytes.buffer[0] == 0xFD);
        assert(bytes.buffer[1] == 0xFD);
        assert(bytes.buffer[2] == 0x00);

        parsed_var_int_s parsed_var_int = parse_var_int(bytes);
        assert(parsed_var_int.parsed_bytes == 3);
        assert(parsed_var_int.var_int.value == 0xFD);

        free_bytes(bytes);
    }

    // serialize/parse_var_int - two byte var int
    {
        var_int_s var_int = {.value=0xFFFF};

        bytes_s bytes = serialize_var_int(var_int);
        assert(bytes.length == 3);
        assert(bytes.buffer[0] == 0xFD);
        assert(bytes.buffer[1] == 0xFF);
        assert(bytes.buffer[2] == 0xFF);

        parsed_var_int_s parsed_var_int = parse_var_int(bytes);
        assert(parsed_var_int.parsed_bytes == 3);
        assert(parsed_var_int.var_int.value == 0xFFFF);

        free_bytes(bytes);
    }

    // serialize/parse_var_int - four byte var int
    {
        var_int_s var_int = {.value=0x010000};

        bytes_s bytes = serialize_var_int(var_int);
        assert(bytes.length == 5);
        assert(bytes.buffer[0] == 0xFE);
        assert(bytes.buffer[1] == 0x00);
        assert(bytes.buffer[2] == 0x00);
        assert(bytes.buffer[3] == 0x01);
        assert(bytes.buffer[4] == 0x00);

        parsed_var_int_s parsed_var_int = parse_var_int(bytes);
        assert(parsed_var_int.parsed_bytes == 5);
        assert(parsed_var_int.var_int.value == 0x010000);

        free_bytes(bytes);
    }

    // serialize/parse_var_int - four byte var int
    {
        var_int_s var_int = {.value=0xFFFFFFFF};

        bytes_s bytes = serialize_var_int(var_int);
        assert(bytes.length == 5);
        assert(bytes.buffer[0] == 0xFE);
        assert(bytes.buffer[1] == 0xFF);
        assert(bytes.buffer[2] == 0xFF);
        assert(bytes.buffer[3] == 0xFF);
        assert(bytes.buffer[4] == 0x0FF);

        parsed_var_int_s parsed_var_int = parse_var_int(bytes);
        assert(parsed_var_int.parsed_bytes == 5);
        assert(parsed_var_int.var_int.value == 0xFFFFFFFF);

        free_bytes(bytes);
    }

    // serialize/parse_var_int - eight byte var int

    {
        var_int_s var_int = {.value=0x0100000000};

        bytes_s bytes = serialize_var_int(var_int);
        assert(bytes.length == 9);
        assert(bytes.buffer[0] == 0xFF);
        assert(bytes.buffer[1] == 0x00);
        assert(bytes.buffer[2] == 0x00);
        assert(bytes.buffer[3] == 0x00);
        assert(bytes.buffer[4] == 0x00);
        assert(bytes.buffer[5] == 0x01);
        assert(bytes.buffer[6] == 0x00);
        assert(bytes.buffer[7] == 0x00);
        assert(bytes.buffer[8] == 0x00);

        parsed_var_int_s parsed_var_int = parse_var_int(bytes);
        assert(parsed_var_int.parsed_bytes == 9);
        assert(parsed_var_int.var_int.value == 0x0100000000);

        free_bytes(bytes);
    }

    return 0;
}

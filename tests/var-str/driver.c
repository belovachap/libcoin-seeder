#include <assert.h>

#include <stdlib.h>

#include <string.h>

#include <libcoin-seeder/var-str.h>

int main ()
{
    // serialize/parse_var_str - empty string
    {
        var_str_s var_str = new_var_str("");
        assert(var_str.length.value == 0);
        assert(var_str.string == "");

        bytes_s bytes = serialize_var_str(var_str);
        assert(bytes.length == 1);
        assert(bytes.buffer[0] == 0x00);

        parsed_var_str_s parsed_var_str = parse_var_str(bytes);
        assert(parsed_var_str.parsed_bytes == 1);
        assert(parsed_var_str.var_str.length.value == 0);
        assert(strcmp(parsed_var_str.var_str.string, "") == 0);

        free_bytes(bytes);
        free_var_str(parsed_var_str.var_str);
    }

    // serialize/parse_var_str - short string
    {
        var_str_s var_str = new_var_str("Hello, world!");
        assert(var_str.length.value == 13);
        assert(strcmp(var_str.string, "Hello, world!") == 0);

        bytes_s bytes = serialize_var_str(var_str);
        assert(bytes.length == 14);
        assert(bytes.buffer[0] == 0x0D);
        assert((char)(bytes.buffer[1]) == 'H');
        assert((char)(bytes.buffer[2]) == 'e');
        assert((char)(bytes.buffer[3]) == 'l');
        assert((char)(bytes.buffer[4]) == 'l');
        assert((char)(bytes.buffer[5]) == 'o');
        assert((char)(bytes.buffer[6]) == ',');
        assert((char)(bytes.buffer[7]) == ' ');
        assert((char)(bytes.buffer[8]) == 'w');
        assert((char)(bytes.buffer[9]) == 'o');
        assert((char)(bytes.buffer[10]) == 'r');
        assert((char)(bytes.buffer[11]) == 'l');
        assert((char)(bytes.buffer[12]) == 'd');
        assert((char)(bytes.buffer[13]) == '!');

        parsed_var_str_s parsed_var_str = parse_var_str(bytes);
        assert(parsed_var_str.parsed_bytes == 14);
        assert(parsed_var_str.var_str.length.value == 13);
        assert(strcmp(parsed_var_str.var_str.string, "Hello, world!") == 0);

        free_bytes(bytes);
        free_var_str(parsed_var_str.var_str);
    }
}

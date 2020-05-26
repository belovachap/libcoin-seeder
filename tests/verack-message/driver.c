#include <assert.h>

#include <libcoin-seeder/message.h>

int main ()
{
    // verack_message
    {
        bytes_s empty = {.buffer=NULL, .length=0};
        message_s verack_message = new_message("verack", empty);

        assert(verack_message.magic == MAGIC);
        assert(verack_message.command[0] == 'v');
        assert(verack_message.command[1] == 'e');
        assert(verack_message.command[2] == 'r');
        assert(verack_message.command[3] == 'a');
        assert(verack_message.command[4] == 'c');
        assert(verack_message.command[5] == 'k');
        assert(verack_message.command[6] == '\0');
        assert(verack_message.command[7] == '\0');
        assert(verack_message.command[8] == '\0');
        assert(verack_message.command[9] == '\0');
        assert(verack_message.command[10] == '\0');
        assert(verack_message.command[11] == '\0');
        assert(verack_message.length == 0);
        assert(verack_message.checksum == 0xE2E0F65D);
        assert(verack_message.payload == NULL);

        bytes_s bytes = serialize_message(verack_message);
        assert(bytes.length == HEADER_LENGTH);

        parsed_message_s parsed_message = parse_message(bytes);
        assert(parsed_message.parsed_bytes == HEADER_LENGTH);
        assert(parsed_message.message.magic == MAGIC);
        assert(parsed_message.message.command[0] == 'v');
        assert(parsed_message.message.command[1] == 'e');
        assert(parsed_message.message.command[2] == 'r');
        assert(parsed_message.message.command[3] == 'a');
        assert(parsed_message.message.command[4] == 'c');
        assert(parsed_message.message.command[5] == 'k');
        assert(parsed_message.message.command[6] == '\0');
        assert(parsed_message.message.command[7] == '\0');
        assert(parsed_message.message.command[8] == '\0');
        assert(parsed_message.message.command[9] == '\0');
        assert(parsed_message.message.command[10] == '\0');
        assert(parsed_message.message.command[11] == '\0');
        assert(parsed_message.message.length == 0);
        assert(parsed_message.message.checksum == 0xE2E0F65D);
        assert(parsed_message.message.payload == NULL);

        free_message(parsed_message.message);
        free_bytes(bytes);
        free_message(verack_message);
    }
}

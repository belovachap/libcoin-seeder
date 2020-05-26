#include <assert.h>

#include <libcoin-seeder/message.h>



#include <stdio.h>

int main ()
{
    // serialize/parse_message - empty payload
    {
        bytes_s bytes = {.buffer=NULL, .length=0};
        message_s message = new_message("testing", bytes);

        assert(message.magic == MAGIC);
        assert(message.command[0] == 't');
        assert(message.command[1] == 'e');
        assert(message.command[2] == 's');
        assert(message.command[3] == 't');
        assert(message.command[4] == 'i');
        assert(message.command[5] == 'n');
        assert(message.command[6] == 'g');
        assert(message.command[7] == '\0');
        assert(message.command[8] == '\0');
        assert(message.command[9] == '\0');
        assert(message.command[10] == '\0');
        assert(message.command[11] == '\0');
        assert(message.length == 0);
        assert(message.checksum == 0xE2E0F65D);
        assert(message.payload == NULL);

        free_message(message);
    }

    // serialize/parse_message - with payload
    {
        byte buffer[1] = {0x01};
        bytes_s bytes = {.buffer=buffer, .length=1};
        message_s message = new_message("testing", bytes);

        assert(message.magic == MAGIC);
        assert(message.command[0] == 't');
        assert(message.command[1] == 'e');
        assert(message.command[2] == 's');
        assert(message.command[3] == 't');
        assert(message.command[4] == 'i');
        assert(message.command[5] == 'n');
        assert(message.command[6] == 'g');
        assert(message.command[7] == '\0');
        assert(message.command[8] == '\0');
        assert(message.command[9] == '\0');
        assert(message.command[10] == '\0');
        assert(message.command[11] == '\0');
        assert(message.length == 1);
        assert(message.checksum == 0xDCCF129C);
        assert(message.payload == buffer); // takes over buffer pointer
    }
}

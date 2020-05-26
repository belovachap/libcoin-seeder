#include <libcoin-seeder/verack-message.h>

message_s new_verack_message() {
    return new_message("verack", (bytes_s){.buffer=NULL, .length=0});
}

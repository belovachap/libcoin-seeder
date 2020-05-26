#include <openssl/sha.h>

#include <libcoin-seeder/message.h>

message_s new_message(char *command, bytes_s payload) {
    message_s message = {
        .magic=MAGIC,
        .length=payload.length,
        .payload=payload.buffer
    };

    memset(message.command, 0, 12); // 0 pad the command
    memcpy(message.command, command, strlen(command));

    byte obuf[SHA256_DIGEST_LENGTH];
    SHA256(payload.buffer, payload.length, obuf);
    SHA256(obuf, SHA256_DIGEST_LENGTH, obuf);
    memcpy(&message.checksum, obuf, 4);

    return message;
}

void free_message(message_s message) {
    free(message.payload);
}

bytes_s serialize_message(message_s message) {
    int length = HEADER_LENGTH + message.length;
    byte *buffer = malloc(length);

    byte *le = to_little_endian(message.magic);
    memcpy(buffer, le, 4);
    free(le);

    memcpy(buffer+4, message.command, 12);

    le = to_little_endian(message.length);
    memcpy(buffer+16, le, 4);
    free(le);

    le = to_little_endian(message.checksum);
    memcpy(buffer+20, le, 4);
    free(le);

    memcpy(buffer+HEADER_LENGTH, message.payload, message.length);

    return (bytes_s){.buffer=buffer, .length=length};
}

parsed_message_s parse_message(bytes_s bytes) {
    message_s message;
    message.magic = from_little_endian(bytes.buffer);
    memcpy(message.command, bytes.buffer+4, 12);
    message.length = from_little_endian(bytes.buffer+16);
    message.checksum = from_little_endian(bytes.buffer+20);
    if (message.length <= 0) {
        message.payload = NULL;
    }
    else {
        memcpy(message.payload, bytes.buffer+HEADER_LENGTH, message.length);
    }

    return (parsed_message_s){.message=message, .parsed_bytes=(HEADER_LENGTH + message.length)};
}

parsed_message_s read_message(socketfd s) {
}

void write_message(socketfd socket, message_s message) {
    bytes_s bytes = serialize_message(message);
    write(socket, bytes.buffer, bytes.length);
    free_bytes(bytes);
}

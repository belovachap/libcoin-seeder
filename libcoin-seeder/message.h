#pragma once

#include <stdint.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <libcoin-seeder/endianness.h>

typedef int socketfd;

uint32_t MAGIC = 0xE6E8E9E5;

int HEADER_LENGTH = 24; // magic + command + length + checksum

typedef struct message {
    uint32_t magic;
    char command[12];
    uint32_t length;
    uint32_t checksum;
    byte *payload;
} message_s;

message_s new_message(char *command, bytes_s payload) {
    message_s message = {.magic=MAGIC, .length=payload.length, .payload=payload.buffer};
    memset(message.command, 0, 12); // 0 pad the command
    memcpy(message.command, command, strlen(command));

    // Calculate and populate the checksum

    return message;
}

void free_message(message_s message) {
    free(message.payload);
}

bytes_s serialize_message(message_s message) {
    int length = HEADER_LENGTH + message.length;
    byte *buffer = malloc(length);

    bytes_s le = to_little_endian(message.magic);
    memcpy(buffer, le.buffer, le.length);
    free_bytes(le);

    memcpy(buffer+4, message.command, 12);

    le = to_little_endian(message.length);
    memcpy(buffer+16, le.buffer, le.length);
    free_bytes(le);

    le = to_little_endian(message.checksum);
    memcpy(buffer+20, le.buffer, le.length);
    free_bytes(le);

    memcpy(buffer+HEADER_LENGTH, message.payload, message.length);

    return (bytes_s){.buffer=buffer, .length=length};
}

message_s *read_message(socketfd s) {
}

void write_message(socketfd s, message_s m) {
    bytes_s b = serialize_message(m);
    write(s, b.buffer, b.length);
    free_bytes(b);
}

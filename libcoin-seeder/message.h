#pragma once

#include <stdint.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <libcoin-seeder/endianness.h>

typedef int socketfd;

static const uint32_t MAGIC = 0xE6E8E9E5;

static const int HEADER_LENGTH = 24; // magic + command + length + checksum

typedef struct message {
    uint32_t magic;
    char command[12];
    uint32_t length;
    uint32_t checksum;
    byte *payload;
} message_s;

message_s new_message(char *, bytes_s);

void free_message(message_s);

bytes_s serialize_message(message_s);

typedef struct parsed_message {
    message_s message;
    int parsed_bytes;
} parsed_message_s;

parsed_message_s parse_message(bytes_s);

parsed_message_s read_message(socketfd s);

void write_message(socketfd, message_s);



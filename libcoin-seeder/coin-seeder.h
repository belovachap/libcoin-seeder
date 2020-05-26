#pragma once

#include <liblog/log.h>

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <libcoin-seeder/bytes.h>
#include <libcoin-seeder/endianness.h>
#include <libcoin-seeder/var-int.h>

typedef int socketfd;

uint32_t MAGIC = 0xE6E8E9E5;

typedef struct message {
    uint32_t magic;
    char command[12];
    uint32_t length;
    uint32_t checksum;
    byte *payload;
} message_s;

const int HEADER_LENGTH = 24; // magic + command + length + checksum

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

typedef struct var_str {
    var_int_s length;
    char *string;
} var_str_s;

typedef struct parsed_var_str {
    var_str_s var_str;
    int parsed_bytes;
} parsed_var_str_s;

void free_var_str(var_str_s var_str) {
    free(var_str.string);
}

parsed_var_str_s parse_var_str(bytes_s bytes) {

}

bytes_s serialize_var_str(var_str_s var_str) {

}

typedef struct net_addr {
    uint32_t time; // not present in version message
    uint64_t services;
    char ip[16];
    uint16_t port; // network byte order
} net_addr_s;

typedef struct parsed_net_addr {
    net_addr_s net_addr;
    int parsed_bytes;
} parsed_net_addr_s;


parsed_net_addr_s parse_net_addr(bytes_s bytes, bool include_time) {
}

bytes_s serialize_net_addr(net_addr_s net_addr, bool include_time) {
}

typedef struct version_payload {
    int32_t version;
    uint64_t services;
    int64_t timestamp;
    net_addr_s addr_recv;
    net_addr_s addr_from;
    uint64_t nonce;
    var_str_s user_agent;
    int32_t start_height;
    bool relay;
} version_payload_s;

typedef struct parsed_version_payload {
    version_payload_s version_payload;
    int parsed_bytes;
} parsed_version_payload_s;

void free_version_payload(version_payload_s version_payload) {
    free_var_str(version_payload.user_agent);
}

parsed_version_payload_s parse_version_payload(bytes_s bytes) {
    log_error("TODO!");
    return (parsed_version_payload_s){};
}

bytes_s serialize_version_payload(version_payload_s version_payload) {
    log_error("TODO!");
    return (bytes_s){};
}

void write_version_message(socketfd s) {
/*    version_payload_s *vp = malloc(sizeof(version_payload_s));*/
/*    vp->version = ;*/
/*    vp->services = ;*/
/*    vp->addr_recv = ;*/
/*    vp->addr_from = ;*/
/*    vp->nonce = ;*/
/*    vp->user_agent = ;*/
/*    vp-> start_height = 0;*/
/*    vp->relay = ;*/

/*    message_s m = {*/
/*        .header={.magic=MAGIC, .command="version", .length=0, .checksum=0},*/
/*        .payload=serialize_version_payload(vp)*/
/*    };*/
/*    write_message(s, &m);*/
/*    free_version_payload(vp);*/
}

void read_verack_message(socketfd s) {
    message_s *m = read_message(s);
}

void read_version_message(socketfd s) {
    message_s *m = read_message(s);
}


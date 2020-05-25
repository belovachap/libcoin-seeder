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

#include <libcoin-seeder/export.h>

typedef unsigned char uchar;
typedef int socketfd;

typedef struct message_header {
    uint32_t magic;
    char command[12];
    uint32_t length;
    uint32_t checksum;
} message_header_s;

typedef struct message {
    message_header_s header;
    uchar *payload;
} message_s;

uchar *to_little_endian(const uint32_t i) {
    uchar *b = malloc(4);
    uchar *pi = (uchar *)&i;
    b[0] = pi[3];
    b[1] = pi[2];
    b[2] = pi[1];
    b[3] = pi[0];
    return b;
}

uint32_t from_little_endian(const uchar *b) {
    uint32_t i;
    uchar *pi = (uchar *)&i;
    pi[0] = b[3];
    pi[1] = b[2];
    pi[2] = b[1];
    pi[3] = b[0];
    return i;
}

uchar *serialize_message(const message_s *m) {
    size_t b_size = sizeof(message_header_s) + m->header.length;
    uchar *b = malloc(b_size);
    memset(b, 0, b_size);

    uchar *le = to_little_endian(m->header.magic);
    memcpy(b, le, 4);
    free(le);

    memcpy(b+4, m->header.command, 12);

    le = to_little_endian(m->header.length);
    memcpy(b+16, le, 4);
    free(le);

    le = to_little_endian(m->header.checksum);
    memcpy(b+20, le, 4);
    free(le);

    memcpy(b+24, m->payload, m->header.length);

    return b;
}

void write_message(const socketfd s, const message_s *m) {
    uchar *b = serialize_message(m);
    write(s, b, sizeof(message_header_s) + m->header.length);
    free(b);
}

typedef struct var_int {
    uint64_t value;
    int _bytes_parsed;
} var_int_s;

void free_var_int(var_int_s *vi) {
    free(vi);
}

var_int_s *parse_var_int(uchar *b) {

}

uchar *serialize_var_int(var_int_s *vi) {
    uchar *b;
    uchar *pv = (uchar *)&(vi->value);
    if(vi->value < 0xFD) {
        b = malloc(1);
        b[0] = pv[0];
    }
    else if (vi->value <= 0xFFFF){
        b = malloc(3);
        b[0] = 0xFD;
        b[1] = pv[7]; // value has 8 bytes
        b[2] = pv[6];
    }
    else if (vi->value <= 0xFFFFFFFF) {
        b = malloc(5);
        b[0] = 0xFE;
        b[1] = pv[7];
        b[2] = pv[6];
        b[3] = pv[5];
        b[4] = pv[4];
    }
    else {
        b = malloc(9);
        b[0] = 0xFF;
        b[1] = pv[7];
        b[2] = pv[6];
        b[3] = pv[5];
        b[4] = pv[4];
        b[5] = pv[3];
        b[6] = pv[2];
        b[7] = pv[1];
        b[8] = pv[0];
    }

    return b;
}

typedef struct var_str {
    var_int_s length;
    char *string;
} var_str_s;

void free_var_str(var_str_s *vs) {
    free(vs->string);
    free(vs);
}

var_str_s *parse_var_str(uchar *b) {

}

uchar *serialize_var_str(const var_str_s *vs) {

}

typedef struct net_addr {
    uint32_t time; // not present in version message
    uint64_t services;
    char ip[16];
    uint16_t port; // network byte order
} net_addr_s;

void free_net_addr(net_addr_s *n) {
    free(n);
}

net_addr_s *parse_net_addr(uchar *b, bool include_time) {

}

uchar *serialize_net_addr(net_addr_s *n, bool include_time) {
}


message_s *read_message(const socketfd s) {
}

typedef struct version_payload {
    int32_t version;
    uint64_t services;
    int64_t timestamp;
    net_addr_s *addr_recv;
    net_addr_s *addr_from;
    uint64_t nonce;
    var_str_s *user_agent;
    int32_t start_height;
    bool relay;
} version_payload_s;

void free_version_payload(version_payload_s *n) {
    free_net_addr(n->addr_recv);
    free_net_addr(n->addr_from);
    free_var_str(n->user_agent);
    free(n);
}

version_payload_s *parse_version_payload(uchar *b) {
    log_error("TODO!");
    return NULL;
}

uchar *serialize_version_payload(version_payload_s *n) {
    log_error("TODO!");
    return NULL;
}

uint32_t MAGIC = 0xe6e8e9e5;

void write_version_message(const socketfd s) {
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

void read_verack_message(const socketfd s) {
    message_s *m = read_message(s);
}

void read_version_message(const socketfd s) {
    message_s *m = read_message(s);
}


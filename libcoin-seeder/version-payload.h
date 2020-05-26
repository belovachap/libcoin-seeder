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

void read_version_message(socketfd s) {
    message_s *m = read_message(s);
}


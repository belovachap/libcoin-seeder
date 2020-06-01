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

    byte *le = uint32_t_to_little_endian(message.magic);
    memcpy(buffer, le, 4);
    free(le);

    memcpy(buffer+4, message.command, 12);

    le = uint32_t_to_little_endian(message.length);
    memcpy(buffer+16, le, 4);
    free(le);

    le = uint32_t_to_little_endian(message.checksum);
    memcpy(buffer+20, le, 4);
    free(le);

    memcpy(buffer+HEADER_LENGTH, message.payload, message.length);

    return (bytes_s){.buffer=buffer, .length=length};
}

parsed_message_s parse_message(bytes_s bytes) {
    message_s message;
    message.magic = uint32_t_from_little_endian(bytes.buffer);
    memcpy(message.command, bytes.buffer+4, 12);
    message.length = uint32_t_from_little_endian(bytes.buffer+16);
    message.checksum = uint32_t_from_little_endian(bytes.buffer+20);
    if (message.length <= 0) {
        message.payload = NULL;
    }
    else {
        memcpy(message.payload, bytes.buffer+HEADER_LENGTH, message.length);
    }

    return (parsed_message_s){.message=message, .parsed_bytes=(HEADER_LENGTH + message.length)};
}

parsed_message_s read_message(socketfd s) {
    message_s m;

    // First we need a header amount of bytes.
    int read_bytes = 0;
    byte header_bytes[HEADER_LENGTH];
    while(read_bytes < HEADER_LENGTH) {
        int recv_bytes = read(s, &header_bytes[read_bytes], HEADER_LENGTH - read_bytes);
        if(recv_bytes <= 0) {
            return (parsed_message_s){.parsed_bytes=-1, .message=m};
        }
        read_bytes += recv_bytes;
    }

    m.magic = uint32_t_from_little_endian(header_bytes);
    memcpy(m.command, header_bytes+4, 12);
    m.length = uint32_t_from_little_endian(header_bytes+16);
    m.checksum = uint32_t_from_little_endian(header_bytes+20);

    // Check for magic.
    if (m.magic != MAGIC) {
        return (parsed_message_s){.parsed_bytes=-1, .message=m};
    }

    // Check for reasonable payload length.
    if (m.length > MAX_PAYLOAD_LENGTH) {
        return (parsed_message_s){.parsed_bytes=-1, .message=m};
    }

    // Then we need a payload number of bytes.
    byte *payload = malloc(m.length);
    read_bytes = 0;
    while(read_bytes < m.length) {
        int recv_bytes = read(s, &payload[read_bytes], m.length - read_bytes);
        if(recv_bytes <= 0) {
            free(payload);
            return (parsed_message_s){.parsed_bytes=-1, .message=m};
        }
        read_bytes += recv_bytes;
    }

    // Check the checksum
    m.payload = payload;

    return (parsed_message_s){.parsed_bytes=HEADER_LENGTH + m.length, .message=m};
}

void write_message(socketfd socket, message_s message) {
    bytes_s bytes = serialize_message(message);
    write(socket, bytes.buffer, bytes.length);
    free_bytes(bytes);
}

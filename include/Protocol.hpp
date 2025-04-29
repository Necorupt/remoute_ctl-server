#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include <cstdint>

#define PROTO_MAGIC "RCTL"
#define PROTO_LITTLE_ENDIAN 0x1
#define PROTO_BIG_ENDIAN 0x2

#define PROTO_MSG_TYPE_HELLO 0x1
#define PROTO_MSG_TYPE_HANDSHAKE 0x2
#define PROTO_MSG_TYPE_SEND_CMD 0x3
#define PROTO_MSG_TYPE_GET_CMD_OUTPUT 0x4

typedef struct PROTO_MESSAGE
{
    uint8_t endian;
    uint8_t magic[4];
    uint8_t versionMaj;
    uint8_t versionMin;
    uint8_t msgType;
} PROTO_MESSAGE_T;

typedef struct PROTO_HANDSHAKE_PAYLOAD
{
    uint32_t clientId;
    uint8_t versionMaj;
    uint8_t versionMin;
    uint32_t reserved;
}
PROTO_HANDSHAKE_PAYLOAD_T;

#endif //! __PROTOCOL_HPP__
#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include <cstdint>

#define MAGIC_NUMBER 0xAB0EDD0C
#define LITLE_ENDIAN 0x1
#define BIG_ENDIAN 0x2

#define PACKET_TYPE_SEND_RESPONSE 0x1
#define PACKET_TYPE_START_SESSION 0x2
#define PACKET_TYPE_END_SESSION 0x3

typedef struct HELLO_MSG
{
    uint8_t endian;
    uint32_t magic;
    uint32_t version;
} HELLO_MSG_T;

typedef struct PACKET_DATA
{
    uint32_t lenght;
    uint32_t type;
    char *payload;
} PACKET_DATA_T;

#endif //! __PROTOCOL_HPP__
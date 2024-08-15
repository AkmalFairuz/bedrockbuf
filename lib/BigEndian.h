#ifndef BIGENDIAN_H
#define BIGENDIAN_H
#include <cstdint>

namespace bedrockbuf {

class BigEndian {
public:
    static uint8_t* writeLong(int64_t value);
    static uint8_t* writeUnsignedLong(uint64_t value);
    static uint8_t* writeInt(int32_t value);
    static uint8_t* writeUnsignedInt(uint32_t value);
    static uint8_t* writeTriad(int32_t value);
    static uint8_t* writeUnsignedTriad(uint32_t value);
    static uint8_t* writeShort(int16_t value);
    static uint8_t* writeUnsignedShort(uint16_t value);
};

}

#endif //BIGENDIAN_H

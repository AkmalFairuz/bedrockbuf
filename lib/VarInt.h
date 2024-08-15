#ifndef VARINT_H
#define VARINT_H

#include <cstdint>

namespace bedrockbuf {

class VarInt {
public:
    static void writeUnsignedVarInt(uint8_t* buffer, size_t& offset, uint32_t value);
    static void writeUnsignedVarLong(uint8_t* buffer, size_t& offset, uint64_t value);
    static void readUnsignedVarInt(const uint8_t* buffer, size_t& offset, uint32_t* out);
    static void readUnsignedVarLong(const uint8_t* buffer, size_t& offset, uint64_t* out);
    static void writeVarInt(uint8_t* buffer, size_t& offset, int32_t value);
    static void readVarInt(const uint8_t* buffer, size_t& offset, int32_t* out);
    static void writeVarLong(uint8_t* buffer, size_t& offset, int64_t value);
    static void readVarLong(const uint8_t* buffer, size_t& offset, int64_t* out);
};

}

#endif //VARINT_H

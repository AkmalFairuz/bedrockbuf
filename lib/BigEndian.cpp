#include "BigEndian.h"
#include "ByteFlipper.h"
#include "ByteOrder.h"

namespace bedrockbuf {

#define BIG_ENDIAN_WRITE_FUNCTION(type, name) \
    uint8_t* BigEndian::name(const type value) { \
        auto* ret = reinterpret_cast<uint8_t*>(value); \
        if constexpr (ByteOrder::NATIVE != ByteOrder::BE) { \
            ByteFlipper::flip(ret, sizeof(value)); \
        } \
        return ret; \
    }

BIG_ENDIAN_WRITE_FUNCTION(int64_t, writeLong)
BIG_ENDIAN_WRITE_FUNCTION(uint64_t, writeUnsignedLong)
BIG_ENDIAN_WRITE_FUNCTION(int32_t, writeInt)
BIG_ENDIAN_WRITE_FUNCTION(uint32_t, writeUnsignedInt)
BIG_ENDIAN_WRITE_FUNCTION(int32_t, writeTriad)
BIG_ENDIAN_WRITE_FUNCTION(uint32_t, writeUnsignedTriad)
BIG_ENDIAN_WRITE_FUNCTION(int16_t, writeShort)
BIG_ENDIAN_WRITE_FUNCTION(uint16_t, writeUnsignedShort)

}

#undef BIG_ENDIAN_WRITE_FUNCTION

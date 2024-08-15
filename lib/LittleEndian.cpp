#include "LittleEndian.h"
#include "ByteFlipper.h"
#include "ByteOrder.h"

namespace bedrockbuf {

#define LITTLE_ENDIAN_WRITE_FUNCTION(type, name) \
    uint8_t* LittleEndian::name(const type value) { \
        auto* ret = reinterpret_cast<uint8_t*>(value); \
        if constexpr (ByteOrder::NATIVE != ByteOrder::LE) { \
            ByteFlipper::flip(ret, sizeof(value)); \
        } \
        return ret; \
    }

LITTLE_ENDIAN_WRITE_FUNCTION(int64_t, writeLong)
LITTLE_ENDIAN_WRITE_FUNCTION(uint64_t, writeUnsignedLong)
LITTLE_ENDIAN_WRITE_FUNCTION(int32_t, writeInt)
LITTLE_ENDIAN_WRITE_FUNCTION(uint32_t, writeUnsignedInt)
LITTLE_ENDIAN_WRITE_FUNCTION(int32_t, writeTriad)
LITTLE_ENDIAN_WRITE_FUNCTION(uint32_t, writeUnsignedTriad)
LITTLE_ENDIAN_WRITE_FUNCTION(int16_t, writeShort)
LITTLE_ENDIAN_WRITE_FUNCTION(uint16_t, writeUnsignedShort)

}

#undef LITTLE_ENDIAN_WRITE_FUNCTION
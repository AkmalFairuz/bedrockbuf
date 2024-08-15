#include "VarInt.h"
#include "BufferException.h"

namespace bedrockbuf{

void VarInt::writeUnsignedVarInt(uint8_t* buffer, size_t& offset, uint32_t value) {
    uint8_t a[5];
    size_t i = 0;
    for (; i < 5; ++i) {
        if ((value & ~0x7f) != 0) {
            a[i] = static_cast<uint8_t>(value & 0x7f | 0x80);
        } else {
            a[i] = static_cast<uint8_t>(value & 0x7f);
            break;
        }
        value >>= 7;
    }
    memcpy(buffer + offset, a, i + 1);
    offset += i + 1;
}

void VarInt::writeUnsignedVarLong(uint8_t* buffer, size_t& offset, uint64_t value) {
    uint8_t a[10];
    size_t i = 0;
    for (; i < 10; ++i) {
        if ((value & ~0x7f) != 0) {
            a[i] = static_cast<uint8_t>(value & 0x7f | 0x80);
        } else {
            a[i] = static_cast<uint8_t>(value & 0x7f);
            break;
        }
        value >>= 7;
    }
    memcpy(buffer + offset, a, i + 1);
    offset += i + 1;
}

void VarInt::readUnsignedVarInt(const uint8_t* buffer, size_t& offset, uint32_t* out) {
    *out = 0;
    for (int i = 0; i <= 28; i += 7) {
        const uint8_t b = buffer[offset++];
        *out |= (b & 0x7f) << i;
        if ((b & 0x80) == 0) {
            return;
        }
    }
    throw BufferException("VarInt::readUnsignedVarInt: VarInt did not terminate after 5 bytes!");
}

void VarInt::readUnsignedVarLong(const uint8_t* buffer, size_t& offset, uint64_t* out) {
    *out = 0;
    for (int i = 0; i <= 63; i += 7) {
        const uint8_t b = buffer[offset++];
        *out |= (b & 0x7f) << i;
        if ((b & 0x80) == 0) {
            return;
        }
    }
    throw BufferException("VarInt::readUnsignedVarLong: VarLong did not terminate after 10 bytes!");
}

void VarInt::writeVarInt(uint8_t* buffer, size_t& offset, const int32_t value) {
    VarInt::writeUnsignedVarInt(buffer, offset, (value << 1) ^ (value >> 31));
}

void VarInt::readVarInt(const uint8_t* buffer, size_t& offset, int32_t* out) {
    uint32_t i = 0;
    VarInt::readUnsignedVarInt(buffer, offset, &i);
    *out = static_cast<int32_t>((i >> 1) ^ -(i & 1));
}

void VarInt::writeVarLong(uint8_t* buffer, size_t& offset, const int64_t value) {
    VarInt::writeUnsignedVarLong(buffer, offset, (value << 1) ^ (value >> 63));
}

void VarInt::readVarLong(const uint8_t* buffer, size_t& offset, int64_t* out) {
    uint64_t i = 0;
    VarInt::readUnsignedVarLong(buffer, offset, &i);
    *out = static_cast<int64_t>((i >> 1) ^ -(i & 1));
}

}
#include "BedrockBuffer.h"

#include <cstring>

#include "BufferException.h"
#include "VarInt.h"
#include "ByteOrder.h"
#include "ByteFlipper.h"

namespace bedrockbuf{

BedrockBuffer* BedrockBuffer::make(uint8_t* buf, const size_t len) {
    auto* ret = new BedrockBuffer();
    ret->_buffer = buf;
    ret->_offset = 0;
    ret->_capacity = len;
    ret->_usedBufferLength = len;
    ret->_maxCapacity = DEFAULT_MAX_BUFFER_CAPACITY;
    return ret;
}

BedrockBuffer* BedrockBuffer::make(const size_t capacity) {
    auto* ret = new BedrockBuffer();
    ret->_buffer = new uint8_t[capacity];
    ret->_offset = 0;
    ret->_capacity = capacity;
    ret->_usedBufferLength = 0;
    ret->_maxCapacity = DEFAULT_MAX_BUFFER_CAPACITY;
    return ret;
}

#define READ_WRITE_REINTERPRET_CAST(name, type, out, typesize) \
    void BedrockBuffer::read##name(type* out) { \
        auto* re = reinterpret_cast<uint8_t*>(out); \
        this->read(re, typesize); \
        if constexpr(ByteOrder::NATIVE != ByteOrder::BE) { \
            ByteFlipper::flip(re, typesize); \
        } \
    } \
    void BedrockBuffer::readL##name(type* out) { \
        auto* re = reinterpret_cast<uint8_t*>(out); \
        this->read(re, typesize); \
        if constexpr(ByteOrder::NATIVE != ByteOrder::LE) { \
            ByteFlipper::flip(re, typesize); \
        } \
    } \
    void BedrockBuffer::write##name(type value) { \
        auto* wr = reinterpret_cast<uint8_t*>(&value); \
        if constexpr(ByteOrder::NATIVE != ByteOrder::BE) { \
            ByteFlipper::flip(wr, typesize); \
        } \
        this->write(wr, typesize); \
    } \
    void BedrockBuffer::writeL##name(type value) { \
        auto* wr = reinterpret_cast<uint8_t*>(&value); \
        if constexpr(ByteOrder::NATIVE != ByteOrder::LE) { \
            ByteFlipper::flip(wr, typesize); \
        } \
        this->write(wr, typesize); \
    }

#define READ_WRITE_VARINT(name, type, writeFunc, readFunc) \
    void BedrockBuffer::write##name(const type value) { \
        size_t previousOffset = this->_offset; \
        VarInt::writeFunc(this->_buffer, this->_offset, value); \
        this->_usedBufferLength += this->_offset - previousOffset; \
    } \
    void BedrockBuffer::read##name(type* out) { \
        VarInt::readFunc(this->_buffer, this->_offset, out); \
    }

READ_WRITE_REINTERPRET_CAST(Long, int64_t, out, 8)
READ_WRITE_REINTERPRET_CAST(UnsignedLong, uint64_t, out, 8)
READ_WRITE_REINTERPRET_CAST(Int, int32_t, out, 4)
READ_WRITE_REINTERPRET_CAST(UnsignedInt, uint32_t, out, 4)
READ_WRITE_REINTERPRET_CAST(Triad, int32_t, out, 3)
READ_WRITE_REINTERPRET_CAST(UnsignedTriad, uint32_t, out, 3)
READ_WRITE_REINTERPRET_CAST(Short, int16_t, out, 2)
READ_WRITE_REINTERPRET_CAST(UnsignedShort, uint16_t, out, 2)

READ_WRITE_REINTERPRET_CAST(Float, float, out, 4)
READ_WRITE_REINTERPRET_CAST(Double, double, out, 8)

READ_WRITE_VARINT(UnsignedVarInt, uint32_t, writeUnsignedVarInt, readUnsignedVarInt)
READ_WRITE_VARINT(UnsignedVarLong, uint64_t, writeUnsignedVarLong, readUnsignedVarLong)
READ_WRITE_VARINT(VarInt, int32_t, writeVarInt, readVarInt)
READ_WRITE_VARINT(VarLong, int64_t, writeVarLong, readVarLong)

void BedrockBuffer::readByte(uint8_t *out) {
    this->read(*out);
}

void BedrockBuffer::writeByte(const uint8_t value) {
    this->write(value);
}

void BedrockBuffer::readBool(bool *out) {
    uint8_t value;
    this->readByte(&value);
    *out = value != 0;
}

void BedrockBuffer::writeBool(const bool value) {
    this->writeByte(value ? 1 : 0);
}

}

#undef READ_WRITE_REINTERPRET_CAST
#undef READ_WRITE_VARINT


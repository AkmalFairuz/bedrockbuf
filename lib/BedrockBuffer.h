#ifndef BEDROCKBUFFER_H
#define BEDROCKBUFFER_H
#include "Buffer.h"

namespace bedrockbuf {

class BedrockBuffer : public Buffer{
public:

    static BedrockBuffer* make(uint8_t* buf, size_t len);
    static BedrockBuffer* make(size_t initialCapacity);

    void readVarInt(int32_t* out);
    void writeVarInt(int32_t value);

    void readVarLong(int64_t* out);
    void writeVarLong(int64_t value);

    void readUnsignedVarInt(uint32_t* out);
    void writeUnsignedVarInt(uint32_t value);

    void readUnsignedVarLong(uint64_t* out);
    void writeUnsignedVarLong(uint64_t value);

    void readLong(int64_t *out);
    void writeLong(int64_t value);
    void readLLong(int64_t *out);
    void writeLLong(int64_t value);

    void readUnsignedLong(uint64_t *out);
    void writeUnsignedLong(uint64_t value);
    void readLUnsignedLong(uint64_t *out);
    void writeLUnsignedLong(uint64_t value);

    void readInt(int32_t *out);
    void writeInt(int32_t value);
    void readLInt(int32_t *out);
    void writeLInt(int32_t value);

    void readUnsignedInt(uint32_t *out);
    void writeUnsignedInt(uint32_t value);
    void readLUnsignedInt(uint32_t *out);
    void writeLUnsignedInt(uint32_t value);

    void readTriad(int32_t *out);
    void writeTriad(int32_t value);
    void readLTriad(int32_t *out);
    void writeLTriad(int32_t value);

    void readUnsignedTriad(uint32_t *out);
    void writeUnsignedTriad(uint32_t value);
    void readLUnsignedTriad(uint32_t *out);
    void writeLUnsignedTriad(uint32_t value);

    void readShort(int16_t *out);
    void writeShort(int16_t value);
    void readLShort(int16_t *out);
    void writeLShort(int16_t value);

    void readUnsignedShort(uint16_t *out);
    void writeUnsignedShort(uint16_t value);
    void readLUnsignedShort(uint16_t *out);
    void writeLUnsignedShort(uint16_t value);

    void readByte(uint8_t *out);
    void writeByte(uint8_t value);

    void readBool(bool *out);
    void writeBool(bool value);

    void readFloat(float *out);
    void writeFloat(float value);
    void readLFloat(float *out);
    void writeLFloat(float value);

    void readDouble(double *out);
    void writeDouble(double value);
    void readLDouble(double *out);
    void writeLDouble(double value);
};

}



#endif //BEDROCKBUFFER_H

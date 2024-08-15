#ifndef LITTLEENDIAN_H
#define LITTLEENDIAN_H
#include <cstdint>

namespace bedrockbuf {

class LittleEndian {

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



#endif //LITTLEENDIAN_H

#ifndef BYTEFLIPPER_H
#define BYTEFLIPPER_H
#include <cstdint>

namespace bedrockbuf {

class ByteFlipper {
public:
    static void flip(uint8_t* buf, size_t len);
};

}

#endif //BYTEFLIPPER_H

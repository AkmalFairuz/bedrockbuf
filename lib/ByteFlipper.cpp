#include "ByteFlipper.h"

#include <algorithm>

namespace bedrockbuf {

void ByteFlipper::flip(uint8_t *buf, const size_t len) {
    std::reverse(buf, buf + len);
}

}


#ifndef BYTEORDER_H
#define BYTEORDER_H

namespace bedrockbuf {

enum class ByteOrder {
    BE,
    LE,
#ifdef WORDS_BIGENDIAN
    NATIVE = BE
#else
    NATIVE = LE
#endif
};

}

#endif //BYTEORDER_H

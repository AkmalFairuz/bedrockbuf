#ifndef UNSAFEBUFFERPOOL_H
#define UNSAFEBUFFERPOOL_H

#include <stack>

#include "BedrockBuffer.h"

namespace bedrockbuf {

class UnsafeBufferPool {
public:
    size_t _defaultCapacity{};
    size_t _size{};
    size_t _maxBufferCapacity{};
    std::stack<BedrockBuffer*> _buffers{};

    static UnsafeBufferPool* make();

    BedrockBuffer* get();
    bool put(BedrockBuffer* buffer);
    void destroy();
    ~UnsafeBufferPool();
};

}

#endif //UNSAFEBUFFERPOOL_H

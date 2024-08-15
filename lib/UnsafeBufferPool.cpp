#include "UnsafeBufferPool.h"
#include <cstdlib>
#include <stack>

namespace bedrockbuf {

UnsafeBufferPool *UnsafeBufferPool::make() {
    auto* ret = new UnsafeBufferPool();
    ret->_defaultCapacity = 256;
    ret->_size = 64;
    ret->_maxBufferCapacity = 1024 * 256; // 256KB
    ret->_buffers = std::stack<BedrockBuffer*>();
    return ret;
}

bool UnsafeBufferPool::put(BedrockBuffer *buffer) {
    if(this->_buffers.size() > this->_size || buffer->_capacity >= this->_maxBufferCapacity) {
        buffer->free();
        delete buffer;
        return false;
    }
    buffer->setOffset(0);
    buffer->_usedBufferLength = 0;
    this->_buffers.push(buffer);
    return true;
}

BedrockBuffer *UnsafeBufferPool::get() {
    if (this->_buffers.empty()) {
        return BedrockBuffer::make(this->_defaultCapacity);
    }
    const auto ret = this->_buffers.top();
    this->_buffers.pop();
    return ret;
}

void UnsafeBufferPool::destroy() {
    while (!this->_buffers.empty()) {
        this->_buffers.pop();
    }
}

UnsafeBufferPool::~UnsafeBufferPool() {
    this->destroy();
}

}




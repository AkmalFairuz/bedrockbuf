#include "Buffer.h"

#include <algorithm>
#include <cstring>

#include "BufferException.h"

namespace bedrockbuf {

Buffer* Buffer::make(uint8_t* buf, size_t len) {
    auto* ret = new Buffer();
    ret->_buffer = buf;
    ret->_offset = 0;
    ret->_capacity = len;
    ret->_usedBufferLength = len;
    ret->_maxCapacity = DEFAULT_MAX_BUFFER_CAPACITY;
    return ret;
}

Buffer *Buffer::make(const size_t capacity) { // NOLINT(*-convert-member-functions-to-static)
    auto* ret = new Buffer();
    ret->_buffer = new uint8_t[capacity];
    ret->_offset = 0;
    ret->_capacity = capacity;
    ret->_usedBufferLength = 0;
    ret->_maxCapacity = DEFAULT_MAX_BUFFER_CAPACITY;
    return ret;
}

void Buffer::write(const uint8_t value) {
    if(this->_offset >= this->_capacity) {
        this->increaseCapacity();
    }
    this->_buffer[this->_offset++] = value;
    this->_usedBufferLength += 1;
}

void Buffer::write(const uint8_t* value, const size_t len) {
    const size_t nextOffset = this->_offset + len;
    if(nextOffset > this->_capacity) {
        this->increaseCapacityMin(len);
    }
    std::memcpy(this->_buffer + this->_offset, value, len);
    this->_offset = nextOffset;
    this->_usedBufferLength += len;
}

void Buffer::read(uint8_t& out) {
    if(this->_offset > this->_usedBufferLength) {
        throw BufferException("Buffer read out of bounds");
    }
    out = this->_buffer[this->_offset++];
}

void Buffer::read(uint8_t* out, const size_t len) {
    const size_t maxOffset = this->_offset + len;
    if(maxOffset > this->_usedBufferLength) {
        throw BufferException("Buffer read out of bounds");
    }
    std::memcpy(out, this->_buffer + this->_offset, len);
    this->_offset = maxOffset;
}

uint8_t *Buffer::remaining() {
    const size_t remainingLength = this->_usedBufferLength - this->_offset;
    auto* ret = new uint8_t[remainingLength];
    this->read(ret, remainingLength);
    return ret;
}


uint8_t* Buffer::toString() const {
    auto* str = new uint8_t[this->_usedBufferLength];
    std::memcpy(str, this->_buffer, this->_usedBufferLength);
    return str;
}

void Buffer::setOffset(const size_t offset) {
    this->_offset = offset;
}

size_t Buffer::getOffset() const {
    return this->_offset;
}

size_t Buffer::getCapacity() const {
    return this->_capacity;
}

void Buffer::increaseCapacity(const size_t capacity) {
    this->_capacity += capacity;
    if(this->_capacity > this->_maxCapacity) {
        throw BufferException("Exceeded max buffer capacity");
    }
    auto* newBuffer = new uint8_t[this->_capacity];
    std::memcpy(newBuffer, this->_buffer, this->_offset);
    delete[] this->_buffer;
    this->_buffer = newBuffer;
}

void Buffer::increaseCapacity() {
    this->increaseCapacity(this->_capacity * this->_capacity);
}

void Buffer::increaseCapacityMin(const size_t minimum_capacity) {
    this->increaseCapacity(std::max(this->_capacity + minimum_capacity, this->_capacity * this->_capacity));
}

void Buffer::setMaxCapacity(const size_t maxCapacity) {
    this->_maxCapacity = maxCapacity;
}

size_t Buffer::getUsedBufferLength() const {
    return this->_usedBufferLength;
}


void Buffer::free() {
    delete[] this->_buffer;
    this->_capacity = 0;
    this->_offset = 0;
}

Buffer::~Buffer() {
    this->free();
}

}

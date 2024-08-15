#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>
#include <cstdint>

#define DEFAULT_MAX_BUFFER_CAPACITY (1024 * 1024 * 16)

namespace bedrockbuf {

class Buffer {
public:
    uint8_t* _buffer{};
    size_t _capacity{};
    size_t _offset{};
    size_t _maxCapacity{};
    size_t _usedBufferLength{};

    static Buffer* make(size_t capacity);
    static Buffer* make(uint8_t* buf, size_t len);

    void write(uint8_t value);
    void write(const uint8_t* value, size_t len);
    void read(uint8_t &out);
    void read(uint8_t* out, size_t len);

    uint8_t* remaining();

    [[nodiscard]] uint8_t* toString() const;
    void setOffset(size_t offset);
    [[nodiscard]] size_t getOffset() const;

    [[nodiscard]] size_t getCapacity() const;
    void increaseCapacity(size_t capacity);
    void increaseCapacity();
    void increaseCapacityMin(size_t minimum_capacity);
    void setMaxCapacity(size_t maxCapacity);

    [[nodiscard]] size_t getUsedBufferLength() const;

    void free();

    ~Buffer();
};

}

#endif //BUFFER_H

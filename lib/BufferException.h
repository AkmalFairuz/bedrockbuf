

#ifndef BUFFEREXCEPTION_H
#define BUFFEREXCEPTION_H
#include <stdexcept>

namespace bedrockbuf {

class BufferException final : public std::runtime_error {
public:
    explicit BufferException(const std::string& message)
        : std::runtime_error(message) {}
};

}



#endif //BUFFEREXCEPTION_H

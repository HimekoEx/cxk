#pragma once
#include "Base.h"

//SDK
namespace MiHoYoSDK
{

//安全的字符串类型
class SafeChars
{
private:
    static const short _key = 0x7BFA;
    int *_data = nullptr;
    uint _length = 0;

public:
    SafeChars(const int data[], uint size)
    {
        this->_length = size / sizeof(int);
        this->_data = (int *)malloc(size);
        memcpy(this->_data, data, size);
    }

    // 获取长度
    uint length() const { return _length; }

    // 获取字符串
    std::string get() const
    {
        char buffer[_length + 1];
        memset(buffer, 0, _length + 1);
        for (int i = 0; i < _length + 1; ++i)
            buffer[i] = (_data[i] ^ _key) >> 2;
        buffer[_length] = '\0';

        return std::string(buffer, _length);
    }

    ~SafeChars() { free(_data); }
};

} // namespace MiHoYoSDK
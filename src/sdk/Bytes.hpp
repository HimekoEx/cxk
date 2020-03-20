#pragma once
#include "Base.h"

//SDK
namespace MiHoYoSDK
{

//字节封装
class Bytes
{
private:
    char *_data = nullptr;
    uint _length = 0;
    uint _size = 0;

    // 初始化
    void _init(const char *src, uint length)
    {
        if (_data)
            free(_data);
        this->_length = length;
        this->_size = length + 1;
        this->_data = (char *)malloc(_size);
        memcpy(this->_data, src, _size);
    }

    // 追加数据
    Bytes &_append(const char *src, uint length)
    {
        uint new_size = length + (_size ? _size : 1);

        _data = (char *)realloc(_data, new_size);
        memcpy(_data + _length, src, length + 1);
        this->_size = new_size;
        this->_length = _length + length;

        return *this;
    }

public:
    Bytes() {}
    Bytes(const char *src) { _init(src, strlen(src)); }
    Bytes(const char *src, uint length) { _init(src, length); }
    Bytes(const std::string &src) { _init(src.c_str(), src.length()); }
    Bytes(const Bytes &src) { _init(src._data, src._length); }
    ~Bytes() { free(_data); }

    const char *c_str() const { return _data; }
    const uint length() const { return _length; }
    std::string get() const { return std::string(_data, _length); }

    Bytes &append(const char *src, uint length) { return _append(src, length); }
    Bytes &append(const Bytes &src) { return _append(src._data, src._length); }
    Bytes &append(const std::string &src) { return _append(src.c_str(), src.length()); }
    Bytes &operator+=(const Bytes &src) { return _append(src._data, src._length); }

    // 查找子串
    const int find(const Bytes &src)
    {
        int index = -1;
        for (int i = 0; i < this->_length; ++i)
        {
            for (int j = 0; j < src._length; ++j)
            {
                index = i;
                int tmp = i + j;
                if (tmp > this->_length)
                    return -1;

                if (src._data[j] != this->_data[tmp])
                    break;

                if (j == src._length - 1)
                    return index;
            }
            index = -1;
        }
        return index;
    }

    Bytes &operator=(const Bytes &src)
    {
        if (this == &src)
            return *this;

        if (this->_data)
            free(this->_data);

        this->_length = src._length;
        this->_size = src._size;
        this->_data = (char *)malloc(_size);
        memcpy(this->_data, src._data, _size);
        return *this;
    }

    bool operator==(const Bytes &src) const
    {
        if (!this->_data || !src._data)
            return false;
        if (this->_length != src._length)
            return false;

        for (uint i = 0; i < this->_length; i++)
        {
            if (this->_data[i] != src._data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Bytes &src) const
    {
        return !this->operator==(src);
    }
};

} // namespace MiHoYoSDK
//
//  ByteSwapper.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-10-20.
//

#ifndef ByteSwapper_hpp
#define ByteSwapper_hpp

#include <arpa/inet.h>

//#include <endian.h>   // __BYTE_ORDER __LITTLE_ENDIAN
#include <algorithm>  // std::reverse()

template <typename T>
constexpr T htonT (T value) noexcept
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    char* ptr = reinterpret_cast<char*>(&value);
    std::reverse(ptr, ptr + sizeof(T));
#endif
    return value;
}

struct ByteSwapper
{
    template <typename T, size_t Width = sizeof(T)>
    struct Host2Network
    {
        T operator()(T value)
        {
            pfatal("Should never reach at here.");
        }
    };

    template <typename T>
    struct Host2Network<T, 1>
    {
        T operator()(T value)
        {
            return value;
        }
    };

    template <typename T>
    struct Host2Network<T, 2>
    {
        T operator()(T value)
        {
            return htons(value);
        }
    };

    template <typename T>
    struct Host2Network<T, 4>
    {
        T operator()(T value)
        {
            return htonl(value);
        }
    };

    template <typename T>
    struct Host2Network<T, 8>
    {
        T operator()(T value)
        {
            //return htonll(value);
#if __BYTE_ORDER == __LITTLE_ENDIAN
            char* ptr = reinterpret_cast<char*>(&value);
            std::reverse(ptr, ptr + sizeof(T));
#endif
            return value;
        }
    };

    template <typename T, size_t Width = sizeof(T)>
    struct Network2Host
    {
        T operator()(T value)
        {
            pfatal("Should never reach at here.");
        }
    };

    template <typename T>
    struct Network2Host<T, 1>
    {
        T operator()(T value)
        {
            return value;
        }
    };

    template <typename T>
    struct Network2Host<T, 2>
    {
        T operator()(T value)
        {
            return ntohs(value);
        }
    };

    template <typename T>
    struct Network2Host<T, 4>
    {
        T operator()(T value)
        {
            return ntohl(value);
        }
    };

    template <typename T>
    struct Network2Host<T, 8>
    {
        T operator()(T value)
        {
            //return ntohll(value);
// Linux Compat
#if __BYTE_ORDER == __LITTLE_ENDIAN
            char* ptr = reinterpret_cast<char*>(&value);
            std::reverse(ptr, ptr + sizeof(T));
#endif
            return value;
        }
    };
};

#endif /* ByteSwapper_hpp */

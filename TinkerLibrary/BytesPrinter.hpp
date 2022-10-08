//
//  BytesPrinter.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-11-20.
//

#ifndef BytesPrinter_hpp
#define BytesPrinter_hpp

#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <iterator>

/// Print a sequence of bytes elegantly
struct BytesPrinter
{
    void operator()(const void* bytes, size_t length)
    {
        for (size_t index = 0; index < length; index += 1)
        {
            printf("%02X ", reinterpret_cast<const uint8_t*>(bytes)[index]);
        }
    }

    template <typename Iterator, typename Element = std::iter_value_t<Iterator>>
    requires std::input_iterator<Iterator> && (std::same_as<Element, uint8_t> || std::same_as<Element, int8_t>)
    void operator()(Iterator begin, Iterator end)
    {
        for (auto current = begin; current != end; current++)
        {
            printf("%02X ", *current);
        }
    }
};

#endif /* BytesPrinter_hpp */

//
//  SignificantBit.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-9-23.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef SignificantBit_hpp
#define SignificantBit_hpp

#include <cstdint>
#include <cstddef>
#include <concepts>
#include "Debug.hpp"

static constexpr uint8_t MultiplyDeBruijnBitPosition32[32] =
        {
                0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
                31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
        };

// https://stackoverflow.com/questions/31374628/fast-way-of-finding-most-and-least-significant-bit-set-in-a-64-bit-integer
static constexpr uint8_t MultiplyDeBruijnBitPosition64[64] =
        {
                0,   1, 17,  2, 18, 50,  3, 57,
                47, 19, 22, 51, 29,  4, 33, 58,
                15, 48, 20, 27, 25, 23, 52, 41,
                54, 30, 38,  5, 43, 34, 59,  8,
                63, 16, 49, 56, 46, 21, 28, 32,
                14, 26, 24, 40, 53, 37, 42,  7,
                62, 55, 45, 31, 13, 39, 36,  6,
                61, 44, 12, 35, 60, 11, 10,  9,
        };

/// Private functor to find the LSB index of a fixed width integer
/// @note The integer value must not be 0, otherwise the functor returns 0.
template <typename T = size_t, size_t IntegerWidth = sizeof(T)>
requires std::unsigned_integral<T>
struct LSBFinder
{
    uint32_t operator()(T value)
    {
        pfatal("Unsupported Integer Width %u.", IntegerWidth);
    }
};

/// LSBFinder: Specialized for 8-bit integer
template <typename T>
struct LSBFinder<T, 1>
{
    uint32_t operator()(T value)
    {
        if (value == 0)
        {
            return 0;
        }

        // Linear Search
        uint32_t count = 0;

        while ((value & 0x1) == 0)
        {
            value >>= 1;

            count += 1;
        }

        return count;
    }
};

/// LSBFinder: Specialized for 16-bit integer
template <typename T>
struct LSBFinder<T, 2>
{
    uint32_t operator()(T value)
    {
        if (value == 0)
        {
            return 0;
        }

        // Guard: Check odd values
        if ((value & 0x1) != 0)
        {
            return 0;
        }

        // Binary Search
        uint32_t count = 1;

        // Check whether low 8 bits are all zero
        if ((value & 0xFF) == 0)
        {
            value >>= 8;

            count += 8;
        }

        // Check whether low 4 bits are all zero
        if ((value & 0x0F) == 0)
        {
            value >>= 4;

            count += 4;
        }

        // Check whether low 2 bits are all zero
        if ((value & 0x03) == 0)
        {
            value >>= 2;

            count += 2;
        }

        count -= value & 0x1;

        return count;
    }
};

/// LSBFinder: Specialized for 32-bit integer
template <typename T>
struct LSBFinder<T, 4>
{
    uint32_t operator()(T value)
    {
        return MultiplyDeBruijnBitPosition32[((value & -value) * 0x077CB531) >> 27];
    }
};

/// LSBFinder: Specialized for 64-bit integer
template <typename T>
struct LSBFinder<T, 8>
{
    uint32_t operator()(T value)
    {
        return MultiplyDeBruijnBitPosition64[((value & -value) * 0x37E84A99DAE458F) >> 58];
    }
};

/// Private functor to find the MSB index of a fixed width integer
/// @note The integer value must not be 0, otherwise the functor returns 0.
template <typename T = size_t, size_t IntegerWidth = sizeof(T)>
requires std::unsigned_integral<T>
struct MSBFinder
{
    uint32_t operator()(T value)
    {
        pfatal("Unsupported Integer Width %u.", IntegerWidth);
    }
};

/// MSBFinder: Specialized for 8-bit integer
template <typename T>
struct MSBFinder<T, 1>
{
    uint32_t operator()(T value)
    {
        // Linear Search
        uint32_t count = 0;

        while (value >>= 1)
        {
            count += 1;
        }

        return count;
    }
};

/// MSBFinder: Specialized for 16-bit integer
template <typename T>
struct MSBFinder<T, 2>
{
    uint32_t operator()(T value)
    {
        // Binary Search
        uint32_t count = 0;

        // Check high 8 bits
        if ((value & 0xFF00) != 0)
        {
            value >>= 8;

            count |= 8u;
        }

        // Check high 4 bits
        if ((value & 0xF0) != 0)
        {
            value >>= 4;

            count |= 4u;
        }

        // Check high 2 bits
        if ((value & 0xC) != 0)
        {
            value >>= 2;

            count |= 2u;
        }

        // Check high 1 bit
        if ((value & 0x2) != 0)
        {
            value >>= 1;

            count |= 1u;
        }

        return count;
    }
};

/// MSBFinder: Specialized for 32-bit integer
template <typename T>
struct MSBFinder<T, 4>
{
    uint32_t operator()(T value)
    {
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        value = (value >> 1) + 1;

        return MultiplyDeBruijnBitPosition32[(value * 0x077CB531) >> 27];
    }
};

/// MSBFinder: Specialized for 64-bit integer
template <typename T>
struct MSBFinder<T, 8>
{
    uint32_t operator()(T value)
    {
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        value |= value >> 32;
        value = (value >> 1) + 1;

        return MultiplyDeBruijnBitPosition64[(value * 0x37E84A99DAE458F) >> 58];
    }
};

/// Round a number up to the next highest power of 2
template <typename T = size_t>
requires std::unsigned_integral<T>
struct NextPowerOf2Finder
{
    T operator()(T value)
    {
        return value == 1 ? 1 : static_cast<T>(1) << (MSBFinder<T>()(value - 1) + 1);
    }
};

template <typename T = size_t>
requires std::unsigned_integral<T>
struct PowerOf2
{
    constexpr T operator()(T value)
    {
        return static_cast<T>(1) << (value);
    }
};

#endif /* SignificantBit_hpp */

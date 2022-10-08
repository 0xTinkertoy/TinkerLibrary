//
//  BitMasks.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-09-25.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef BitMasks_hpp
#define BitMasks_hpp

#include <concepts>
#include <cstddef>
#include "ClosedRange.hpp"

template <typename T>
requires std::unsigned_integral<T>
struct BitMask
{
    ///
    /// Create a bit mask with low `n` bits set
    ///
    /// @param n Specify the number of low consecutive bits set
    /// @return A bit mask with low `n` bits set.
    /// @note For example, if n is 2 then this function returns 0b00000011 for UInt8 type.
    ///
    static inline T createWithLowBitsSet(size_t n)
    {
        if (n >= sizeof(T) * 8)
        {
            return ~static_cast<T>(0);
        }
        else
        {
            return (static_cast<T>(1) << n) - 1;
        }
    }

    ///
    /// Create a bit mask with high `n` bits set
    ///
    /// @param n Specify the number of high consecutive bits set
    /// @return A bit mask with high `n` bits set.
    /// @note For example, if n is 2 then this function returns 0b11000000 for UInt8 type.
    ///
    static inline T createWithHighBitsSet(size_t n)
    {
        return ~BitMask::createWithLowBitsSet(sizeof(T) * 8 - n);
    }

    ///
    /// Create a bit mask with a range of bits set
    ///
    /// @param range Specify a range of bits to be set
    /// @return A bit mask with specified bits set.
    ///
    template <typename Bound = size_t>
    static inline T createWithRangeOfBitsSet(ClosedRange<Bound> range)
    {
        passert(range.isValid(), "The given range must be valid.");

        // Have out-of-bounds bits set
        auto ll = BitMask::createWithLowBitsSet(range.lowerBound);

        auto hu = BitMask::createWithHighBitsSet(sizeof(T) * 8 - 1 - range.upperBound);

        // NOR them
        return ~(ll | hu);
    }

    ///
    /// Create a bit mask with low `n` bits clear
    ///
    /// @param n Specify the number of low consecutive bits clear
    /// @return A bit mask with low `n` bits clear.
    /// @note For example, if n is 2 then this function returns 0b11111100 for UInt8 type.
    ///
    static inline T createWithLowBitsClear(size_t n)
    {
        return ~BitMask::createWithLowBitsSet(n);
    }

    ///
    /// Create a bit mask with high `n` bits clear
    ///
    /// @param n Specify the number of high consecutive bits clear
    /// @return A bit mask with high `n` bits clear.
    /// @note For example, if n is 2 then this function returns 0b00111111 for UInt8 type.
    ///
    static inline T createWithHighBitsClear(size_t n)
    {
        return ~BitMask::createWithHighBitsSet(n);
    }
};

#endif /* BitMasks_hpp */

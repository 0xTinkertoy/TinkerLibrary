//
//  BitMasksTest.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 9/25/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "BitMasksTest.hpp"
#include "BitMasks.hpp"
#include "Debug.hpp"

void BitMasksTest::run()
{
    pinfof("==== TEST BIT MASKS STARTED ====\n");

    // Test Low N Bits Set
    passert(BitMask<uint8_t>::createWithLowBitsSet(0) == 0b00000000, "Low 0 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(1) == 0b00000001, "Low 1 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(2) == 0b00000011, "Low 2 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(3) == 0b00000111, "Low 3 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(4) == 0b00001111, "Low 4 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(5) == 0b00011111, "Low 5 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(6) == 0b00111111, "Low 6 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(7) == 0b01111111, "Low 7 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsSet(8) == 0b11111111, "Low 8 bits.");

    passert(BitMask<uint64_t>::createWithLowBitsSet(63) == ~(static_cast<uint64_t>(1) << 63U), "Low 63 bits.");

    passert(BitMask<uint64_t>::createWithLowBitsSet(64) == ~static_cast<uint64_t>(0), "Low 64 bits.");

    pinfo("Low N Bits Set: Test Passed.");

    // Test Low N Bits Clear
    passert(BitMask<uint8_t>::createWithLowBitsClear(0) == 0b11111111, "Low 0 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(1) == 0b11111110, "Low 1 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(2) == 0b11111100, "Low 2 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(3) == 0b11111000, "Low 3 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(4) == 0b11110000, "Low 4 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(5) == 0b11100000, "Low 5 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(6) == 0b11000000, "Low 6 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(7) == 0b10000000, "Low 7 bits.");

    passert(BitMask<uint8_t>::createWithLowBitsClear(8) == 0b00000000, "Low 8 bits.");

    pinfo("Low N Bits Clear: Test Passed.");

    // Test High N Bits Set
    passert(BitMask<uint8_t>::createWithHighBitsSet(0) == 0b00000000, "High 0 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(1) == 0b10000000, "High 1 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(2) == 0b11000000, "High 2 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(3) == 0b11100000, "High 3 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(4) == 0b11110000, "High 4 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(5) == 0b11111000, "High 5 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(6) == 0b11111100, "High 6 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(7) == 0b11111110, "High 7 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsSet(8) == 0b11111111, "High 8 bits.");

    passert(BitMask<uint64_t>::createWithHighBitsSet(63) == (~static_cast<uint64_t>(0) - 1), "High 63 bits.");

    passert(BitMask<uint64_t>::createWithHighBitsSet(64) == ~static_cast<uint64_t>(0), "High 64 bits.");

    pinfo("High N Bits Set: Test Passed.");

    // Test High N Bits Clear
    passert(BitMask<uint8_t>::createWithHighBitsClear(0) == 0b11111111, "High 0 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(1) == 0b01111111, "High 1 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(2) == 0b00111111, "High 2 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(3) == 0b00011111, "High 3 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(4) == 0b00001111, "High 4 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(5) == 0b00000111, "High 5 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(6) == 0b00000011, "High 6 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(7) == 0b00000001, "High 7 bits.");

    passert(BitMask<uint8_t>::createWithHighBitsClear(8) == 0b00000000, "High 8 bits.");

    pinfo("High N Bits Clear: Test Passed.");

    // Test Ranges
    passert(BitMask<uint8_t>::createWithRangeOfBitsSet({2, 5}) == 0x3C, "Range [2, 5].");

    for (size_t index = 0; index < 8; index += 1)
    {
        passert(BitMask<uint8_t>::createWithRangeOfBitsSet({index, index}) == (1U << index), "Range [%lu, %lu].", index, index);
    }

    passert(BitMask<uint8_t>::createWithRangeOfBitsSet({0, 7}) == 0xFF, "Range [0, 7].");

    for (size_t index = 0; index < 8; index += 1)
    {
        passert(BitMask<uint8_t>::createWithRangeOfBitsSet({0, index}) == BitMask<uint8_t>::createWithLowBitsSet(index + 1), "Range [0, %lu] == Low %lu bits.", index, index + 1);

        passert(BitMask<uint8_t>::createWithRangeOfBitsSet({index, 7}) == BitMask<uint8_t>::createWithHighBitsSet(7 - index + 1), "Range [%lu, 7] == High %lu bits.", index, 7 - index + 1);
    }

    passert(BitMask<uint64_t>::createWithRangeOfBitsSet({0, 63}) == ~static_cast<uint64_t>(0), "Range [0, 63]");

    passert(BitMask<uint64_t>::createWithRangeOfBitsSet({0, 72}) == ~static_cast<uint64_t>(0), "Range [0, 72]");

    for (size_t index = 0; index < 64; index += 1)
    {
        passert(BitMask<uint64_t>::createWithRangeOfBitsSet({00, index}) == BitMask<uint64_t>::createWithLowBitsSet(index + 1), "Range [0, %lu] == Low %lu bits.", index, index + 1);

        passert(BitMask<uint64_t>::createWithRangeOfBitsSet({index, 63}) == BitMask<uint64_t>::createWithHighBitsSet(63 - index + 1), "Range [%lu, 63] == High %lu bits.", index, 63 - index + 1);
    }

    pinfo("Range of Bits: Test Passed.");

    pinfof("==== TEST BIT MASKS FINISHED ====\n");
}

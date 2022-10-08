//
//  BitOptionsTest.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 9/18/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "BitOptionsTest.hpp"
#include "BitOptions.hpp"
#include "Debug.hpp"

void BitOptionsTest::run()
{
    // Insertion
    BitOptions<uint32_t> options;

    options.mutativeInsert(1 << 5);

    passert(options.flatten() == 0x20, "Insertion");

    options = options.insert(1 << 4);

    passert(options.flatten() == 0x30, "Insertion");

    pinfo("BitOptions Insertion: Test Passed.");

    // Remove
    options.mutativeRemove(1 << 5);

    passert(options.flatten() == 0x10, "Remove");

    options = options.remove(1 << 4);

    passert(options.flatten() == 0x00, "Remove");

    pinfo("BitOptions Removal: Test Passed.");

    // Or
    options.mutativeBitwiseOr(0b0001);

    passert(options.flatten() == 0b0001, "Or");

    options = options.bitwiseOr(0b0010);

    passert(options.flatten() == 0b0011, "Or");

    options |= BitOptions<uint32_t>(0b0100);

    passert(options.flatten() == 0b0111, "Or");

    options = options | BitOptions<uint32_t>(0b1000);

    passert(options.flatten() == 0b1111, "Or");

    pinfo("BitOptions Bitwise OR: Test Passed.");

    // And
    options.mutativeBitwiseAnd(0b1110);

    passert(options.flatten() == 0b1110, "And");

    options = options.bitwiseAnd(0b1100);

    passert(options.flatten() == 0b1100, "And");

    options &= BitOptions<uint32_t>(0b1000);

    passert(options.flatten() == 0b1000, "And");

    options = options & BitOptions<uint32_t>();

    passert(options.flatten() == 0b0000, "And");

    pinfo("BitOptions Bitwise AND: Test Passed.");

    // Empty
    passert(options.isEmpty(), "Empty");

    options |= BitOptions<uint32_t>(0b1111);

    passert(!options.isEmpty(), "Empty");

    pinfo("BitOptions Empty: Test Passed.");

    // Contains
    passert(options.contains(0b1000), "Contains");

    passert(!options.contains(0b10000), "Contains");

    passert(options.containsBit(2), "Contains");

    passert(!options.containsBit(6), "Contains");

    pinfo("BitOptions Contains: Test Passed.");

    // Set All
    options.setAll();

    passert(options.flatten() == ~0U, "Set All");

    pinfo("BitOptions Set All: Test Passed.");

    // Clear All
    options.clearAll();

    passert(options.flatten() == 0, "Clear All");

    pinfo("BitOptions Clear All: Test Passed.");

    // LSB
    options.mutativeBitwiseOr(0b1110);

    passert(options.findLeastSignificantBitIndex() == 1, "LSB");

    // MSB
    passert(options.findMostSignificantBitIndex() == 3, "MSB");

    pinfo("BitOptions LSB/MSB: Test Passed.");

    // Set Bit
    options.setBit(8);

    passert(options.containsBit(8), "Set Bit");

    // Get Bit
    passert(options.getBit(8) == 1, "Get Bit");

    passert(options.getBit(9) == 0, "Get Bit");

    pinfo("BitOptions Set/Get: Test Passed.");

}

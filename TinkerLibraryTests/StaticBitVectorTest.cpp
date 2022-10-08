//
//  StaticBitVectorTest.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 9/25/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "StaticBitVectorTest.hpp"
#include "StaticBitVector.hpp"

void StaticBitVectorTest::run()
{
    pinfof("==== TEST STATIC BIT VECTOR STARTED ====\n");

    // Storage Unit = UInt8
    StaticBitVector<12, uint8_t> vector;

    // Test Index Converter
    size_t block = 0, offset = 0;

    for (size_t index = 0; index < 12; index += 1)
    {
        passert(vector.index2BlockOffset(index, block, offset), "A valid index.");

        if (index < 8)
        {
            passert(block == 0, "Index %lu: Check block number.", index);

            passert(offset == index, "Index %lu: Check block offset.", index);
        }
        else
        {
            passert(block == 1, "Index %lu: Check block number.", index);

            passert(offset == index - 8, "Index %lu: Check block offset.", index);
        }
    }

    for (size_t index = 12; index < 16; index += 1)
    {
        passert(!vector.index2BlockOffset(index, block, offset), "An invalid index.");
    }

    pinfo("Index Converter: Test Passed.");

    // Test Initializer: Zeros
    vector.initWithZeros();

    for (size_t index = 0; index < 12; index += 1)
    {
        passert(vector.getBit(index) == 0, "Get bit at index %lu.", index);

        passert(!vector.containsBit(index), "Contains bit at index %lu.", index);
    }

    passert(vector.blocks[0].flatten() == 0, "Check the raw value of block 0.");

    passert(vector.blocks[1].flatten() == 0, "Check the raw value of block 1.");

    pinfo("InitWithZeros: Test Passed.");

    // Test Initializer: Ones
    vector.initWithOnes();

    for (size_t index = 0; index < 12; index += 1)
    {
        passert(vector.getBit(index) == 1, "Get bit at index %lu.", index);

        passert(vector.containsBit(index), "Contains bit at index %lu.", index);
    }

    passert(vector.blocks[0].flatten() == 0xFF, "Check the raw value of block 0.");

    passert(vector.blocks[1].flatten() == 0x0F, "Check the raw value of block 1.");

    pinfo("InitWithOnes: Test Passed.");

    StaticBitVector<11, uint8_t> vector1;

    vector1.initWithOnes();

    for (size_t index = 0; index < 11; index += 1)
    {
        passert(vector1.getBit(index) == 1, "Get bit at index %lu.", index);

        passert(vector1.containsBit(index), "Contains bit at index %lu.", index);
    }

    for (size_t index = 11; index < 16; index += 1)
    {
        passert(vector1.getBit(index) == 0, "Get bit at index %lu.", index);

        passert(!vector1.containsBit(index), "Contains bit at index %lu.", index);
    }

    passert(vector1.blocks[0].flatten() == 0xFF, "Check the raw value of block 0.");

    passert(vector1.blocks[1].flatten() == 0x07, "Check the raw value of block 1.");

    pinfo("InitWithOnes: Test Passed.");

    // Test Set/Clear
    vector.initWithZeros();

    vector.setBit(11);

    passert(vector.getBit(11) == 1, "Get bit at index 11 after set.");

    passert(vector.containsBit(11), "Contains bit at index 11 after set.");

    passert(vector.blocks[0].flatten() == 0, "Check the raw value of block 0 after set.");

    passert(vector.blocks[1].flatten() == 8, "Check the raw value of block 1 after set.");

    vector.clearBit(11);

    passert(vector.getBit(11) == 0, "Get bit at index 11 after clear.");

    passert(!vector.containsBit(11), "Contains bit at index 11 after clear.");

    passert(vector.blocks[0].flatten() == 0, "Check the raw value of block 0 after clear.");

    passert(vector.blocks[1].flatten() == 0, "Check the raw value of block 1 after clear.");

    pinfo("Set/Clear: Test Passed.");

    // Test LSB/MSB
    vector.setBit(11);

    vector.setBit(9);

    vector.setBit(7);

    vector.setBit(6);

    vector.setBit(3);

    passert(vector.findLeastSignificantBitIndex() == 3, "Find LSB.");

    passert(vector.findMostSignificantBitIndex() == 11, "Find MSB");

    passert(vector.findLeastSignificantBitIndex() == vector.findLeastSignificantBitIndexWithRange({0, 11}), "Compatibility: Find LSB with range.");

    passert(vector.findMostSignificantBitIndex() == vector.findMostSignificantBitIndexWithRange({0, 11}), "Compatibility: Find MSB with range.");

    passert(vector.findLeastSignificantBitIndexWithRange({1, 7}) == 3, "Find LSB with range [1, 7].");

    passert(vector.findMostSignificantBitIndexWithRange({1, 7}) == 7, "Find MSB with range [1, 7].");

    passert(vector.findLeastSignificantBitIndexWithRange({5, 10}) == 6, "Find LSB with range [5, 10].");

    passert(vector.findMostSignificantBitIndexWithRange({5, 10}) == 9, "Find MSB with range [5, 10].");

    passert(vector.findLeastSignificantBitIndexWithRange({7, 11}) == 7, "Find LSB with range [7, 11].");

    passert(vector.findMostSignificantBitIndexWithRange({7, 11}) == 11, "Find MSB with range [7, 11].");

    pinfo("LSB/MSB: Test Passed.");

    pinfof("==== TEST STATIC BIT VECTOR FINISHED ====\n");
}

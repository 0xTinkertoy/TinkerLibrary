//
//  SignificantBitTest.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 9/24/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "SignificantBitTest.hpp"
#include "SignificantBit.hpp"
#include "Debug.hpp"

void SignificantBitTest::run()
{
    pinfo("==== TEST SIGNIFICANT BIT STARTED ====");

    // LSB: Test 64-bit integer
    for (uint32_t index = 0; index < 64; index += 1)
    {
        uint64_t value = 1ULL << index;

        passert(SignificantBitTest::clsb(value) == SignificantBitTest::ilsb(value), "LSB64@%u: Value = 0x%llx; LSB Index = %u.", index, value, index);

        passert(SignificantBitTest::clsb(value) == index, "LSB64@%u", index);

        passert(LSBFinder<uint64_t>()(value) == SignificantBitTest::ilsb(value), "LSB64@%u", index);

        pinfo("LSB64 @ Index %02u: Test Passed.", index);
    }

    // LSB: Test 32-bit integer
    for (uint32_t index = 0; index < 32; index += 1)
    {
        uint32_t value = 1U << index;

        passert(LSBFinder<uint32_t>()(value) == SignificantBitTest::ilsb(value), "LSB32@%d", index);

        pinfo("LSB32 @ Index %02d: Test Passed.", index);
    }

    // LSB: Test 16-bit integer
    for (uint32_t index = 0; index < 16; index += 1)
    {
        uint16_t value = 1U << index;

        passert(LSBFinder<uint16_t>()(value) == SignificantBitTest::ilsb(value), "LSB16@%d", index);

        pinfo("LSB16 @ Index %02d: Test Passed.", index);
    }

    // LSB: Test 8-bit integer
    for (uint32_t index = 0; index < 8; index += 1)
    {
        uint8_t value = 1U << index;

        passert(LSBFinder<uint8_t>()(value) == SignificantBitTest::ilsb(value), "LSB8@%d", index);

        pinfo("LSB08 @ Index %02d: Test Passed.", index);
    }

    // MSB: Test 64-bit integer
    for (uint32_t index = 0; index < 64; index += 1)
    {
        uint64_t value = 1ULL << index;

        passert(SignificantBitTest::cmsb(value) == SignificantBitTest::imsb(value), "MSB64@%u: Value = 0x%llx; MSB Index = %u.", index, value, index);

        passert(SignificantBitTest::cmsb(value) == index, "MSB64@%u", index);

        passert(MSBFinder<uint64_t>()(value) == SignificantBitTest::imsb(value), "MSB64@%d", index);

        pinfo("MSB64 @ Index %02u: Test Passed.", index);
    }

    // MSB: Test 32-bit integer
    for (uint32_t index = 0; index < 32; index += 1)
    {
        uint32_t value = 1U << index;

        passert(MSBFinder<uint32_t>()(value) == SignificantBitTest::imsb(value), "MSB32@%d", index);

        pinfo("MSB32 @ Index %02d: Test Passed.", index);
    }

    // MSB: Test 16-bit integer
    for (uint32_t index = 0; index < 16; index += 1)
    {
        uint32_t value = 1U << index;

        passert(MSBFinder<uint16_t>()(value) == SignificantBitTest::imsb(value), "MSB16@%d", index);

        pinfo("MSB16 @ Index %02d: Test Passed.", index);
    }

    // MSB: Test 8-bit integer
    for (uint32_t index = 0; index < 8; index += 1)
    {
        uint32_t value = 1U << index;

        passert(MSBFinder<uint8_t>()(value) == SignificantBitTest::imsb(value), "MSB8@%d", index);

        pinfo("MSB08 @ Index %02d: Test Passed.", index);
    }

    // LSB/MSB: Random Numbers
    uint64_t v64 = rand();

    uint32_t v32 = rand();

    uint16_t v16 = rand() & 0xFFFF;

    uint8_t v8 = rand() & 0xFF;

    passert(LSBFinder<uint64_t>()(v64) == SignificantBitTest::ilsb(v64), "LSB64 Random = 0x%llx", v64);

    passert(LSBFinder<uint32_t>()(v32) == SignificantBitTest::ilsb(v32), "LSB32 Random = 0x%x", v32);

    passert(LSBFinder<uint16_t>()(v16) == SignificantBitTest::ilsb(v16), "LSB16 Random = 0x%x", v16);

    passert(LSBFinder<uint8_t>()(v8) == SignificantBitTest::ilsb(v8), "LSB08 Random = 0x%x", v8);

    passert(MSBFinder<uint64_t>()(v64) == SignificantBitTest::imsb(v64), "MSB64 Random = 0x%llx", v64);

    passert(MSBFinder<uint32_t>()(v32) == SignificantBitTest::imsb(v32), "MSB32 Random = 0x%x", v32);

    passert(MSBFinder<uint16_t>()(v16) == SignificantBitTest::imsb(v16), "MSB16 Random = 0x%x", v16);

    passert(MSBFinder<uint8_t>()(v8) == SignificantBitTest::imsb(v8), "MSB08 Random = 0x%x", v8);

    pinfo("MSB*/LSB* Random: Test Passed.");

    // Special Cases: 0
    passert(LSBFinder<uint64_t>()(0) == 0, "LSB64 0 = 0");

    passert(LSBFinder<uint32_t>()(0) == 0, "LSB32 0 = 0");

    passert(LSBFinder<uint16_t>()(0) == 0, "LSB16 0 = 0");

    passert(LSBFinder<uint8_t>()(0) == 0, "LSB8 0 = 0");

    passert(MSBFinder<uint64_t>()(0) == 0, "MSB64 0 = 0");

    passert(MSBFinder<uint32_t>()(0) == 0, "MSB32 0 = 0");

    passert(MSBFinder<uint16_t>()(0) == 0, "MSB16 0 = 0");

    passert(MSBFinder<uint8_t>()(0) == 0, "MSB8 0 = 0");

    pinfo("MSB*/LSB* Zeroes: Test Passed.");

    // Special Cases: ~0
    passert(LSBFinder<uint64_t>()(~0ULL) == 0, "LSB64 ~0 = 0");

    passert(LSBFinder<uint32_t>()(~0U) == 0, "LSB32 ~0 = 0");

    passert(LSBFinder<uint16_t>()(0xFFFF) == 0, "LSB16 ~0 = 0");

    passert(LSBFinder<uint8_t>()(0xFF) == 0, "LSB8 ~0 = 0");

    passert(MSBFinder<uint64_t>()(~0ULL) == 63, "MSB64 ~0 = 63");

    passert(MSBFinder<uint32_t>()(~0U) == 31, "MSB32 ~0 = 31");

    passert(MSBFinder<uint16_t>()(0xFFFF) == 15, "MSB16 ~0 = 15");

    passert(MSBFinder<uint8_t>()(0xFF) == 7, "MSB8 ~0 = 7");

    pinfo("MSB*/LSB* IntMax: Test Passed.");

    // Next Power of 2 Tests
    for (uint64_t index = 0; index < 63; index += 1)
    {
        uint64_t value = (2ULL << index) - 1;

        pinfo("NP2(%llu): Portable = %llu, Compiler = %llu, Finder = %llu.", value,
              SignificantBitTest::inp2(value), SignificantBitTest::cnp2(value), NextPowerOf2Finder<uint64_t>()(value));

        passert(SignificantBitTest::inp2(value) == SignificantBitTest::cnp2(value), "NP2(%llu): Portable == Compiler", value);

        passert(SignificantBitTest::inp2(value) == NextPowerOf2Finder<uint64_t>()(value), "NP2(%llu): Portable == NP2Finder", value);
    }

    pinfo("Next Power of 2: Test Passed.");

    pinfo("==== TEST SIGNIFICANT BIT FINISHED ====");
}

size_t SignificantBitTest::imsb(uint64_t value)
{
    passert(value != 0, "Value cannot be zero.");

    for (uint64_t index = 63; index >= 0; index -= 1)
    {
        uint64_t mask = 1ULL << index;

        if ((value & mask) == mask)
        {
            return index;
        }
    }

    pfatal("Should never happen.");
}

size_t SignificantBitTest::ilsb(uint64_t value)
{
    passert(value != 0, "Value cannot be zero.");

    for (uint64_t index = 0; index < 64; index += 1)
    {
        uint64_t mask = 1ULL << index;

        if ((value & mask) == mask)
        {
            return index;
        }
    }

    pfatal("Should never happen.");
}

size_t SignificantBitTest::cmsb(uint64_t value)
{
    return 63 - __builtin_clzll(value);
}

size_t SignificantBitTest::clsb(uint64_t value)
{
    return __builtin_ctzll(value);
}

/// Compiler builtin implementation to find the next highest power of 2
uint64_t SignificantBitTest::cnp2(uint64_t value)
{
    return value == 1 ? 1 : 1ULL << (64 - __builtin_clzll(value - 1));
}

/// A portable implementation to find the next highest power of 2
uint64_t SignificantBitTest::inp2(uint64_t value)
{
    value -= 1;
    value |= value >> 1u;
    value |= value >> 2u;
    value |= value >> 4u;
    value |= value >> 8u;
    value |= value >> 16u;
    value |= value >> 32u;
    value += 1;

    return value;
}

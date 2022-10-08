//
//  SignificantBitTest.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 9/24/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef SignificantBitTest_hpp
#define SignificantBitTest_hpp

#include <cstdint>
#include <cstddef>
#include "TestSuite.hpp"

class SignificantBitTest: public TestSuite
{
public:
    void run() override;

private:
    /// Naive implementation to find the index of the MSB
    static size_t imsb(uint64_t value);

    /// Naive implementation to find the index of the LSB
    static size_t ilsb(uint64_t value);

    /// Compiler builtin implementation to find the index of the MSB
    static size_t cmsb(uint64_t value);

    /// Compiler builtin implementation to find the index of the LSB
    static size_t clsb(uint64_t value);

    /// Compiler builtin implementation to find the next highest power of 2
    static uint64_t cnp2(uint64_t value);

    /// A portable implementation to find the next highest power of 2
    static uint64_t inp2(uint64_t value);
};

#endif /* SignificantBitTest_hpp */

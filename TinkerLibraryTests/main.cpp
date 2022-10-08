//
//  main.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 1/11/21.
//

#include "TinkerLibraryTests.hpp"
#include <TestSuite.hpp>
#include <Debug.hpp>

static BitMasksTest bitMasksTest;
static BitOptionsTest bitOptionsTest;
static LinkedListTest linkedListTest;
static SignificantBitTest significantBitTest;
static StaticBitVectorTest staticBitVectorTest;

static TestSuite* tests[] =
{
    &bitMasksTest,
    &bitOptionsTest,
    &linkedListTest,
    &significantBitTest,
    &staticBitVectorTest
};

#include <functional>

int main(int argc, const char* argv[])
{
    for (auto test : tests)
    {
        test->run();
    }

    return 0;
}

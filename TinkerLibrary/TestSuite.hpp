//
//  TestSuite.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-9-16.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef TestSuite_hpp
#define TestSuite_hpp

/// The interface of a test suite run by the driver
class TestSuite
{
public:
    /// Run the test
    virtual void run() = 0;
};

#endif /* TestSuite_hpp */

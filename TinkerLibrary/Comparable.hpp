//
//  Comparable.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-6-9.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Comparable_hpp
#define Comparable_hpp

#include <concepts>

template <typename T>
concept Comparable = requires(const std::remove_reference_t<T>& a, const std::remove_reference_t<T>& b)
{
    { a <  b } -> std::convertible_to<bool>;
    { a >  b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a >= b } -> std::convertible_to<bool>;
};

#endif //SCHEDULER_COMPARABLE_HPP

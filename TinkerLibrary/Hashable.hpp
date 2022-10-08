//
//  Hashable.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-6-10.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Hashable_hpp
#define Hashable_hpp

#include <concepts>
#include <functional>

template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

#endif /* Hashable_hpp */

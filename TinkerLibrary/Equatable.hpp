//
//  Equatable.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-9-15.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Equatable_hpp
#define Equatable_hpp

#include <concepts>

template <typename T>
concept Equatable = std::equality_comparable<T>;

#endif /* Equatable_hpp */

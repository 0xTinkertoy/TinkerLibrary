//
//  Decrementable.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-6-12.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Decrementable_hpp
#define Decrementable_hpp

#include <concepts>

/// A decrementable type must have operator -- defined
template <typename T>
concept Decrementable = requires(T entity)
{
    entity--;
};

#endif /* Decrementable_hpp */

//
//  Incrementable.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-6-12.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Incrementable_hpp
#define Incrementable_hpp

#include <concepts>

/// An incrementable type must have operator ++ defined
template <typename T>
concept Incrementable = requires(T entity)
{
    entity++;
};

#endif /* Incrementable_hpp */

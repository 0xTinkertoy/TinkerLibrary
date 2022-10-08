//
//  Listable.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-9-14.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Listable_hpp
#define Listable_hpp

#include <concepts>

/// A type that can form a doubly linked list
template <typename Item>
class Listable
{
public:
    Item* prev;

    Item* next;

    Listable() : prev(nullptr), next(nullptr) {}
};

/// A concept to check whether a type is listable
template <typename Item>
concept ListableItem = std::derived_from<Item, Listable<Item>>;

#endif /* Listable_hpp */

//
//  LinkedList.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-9-14.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <concepts>
#include <functional>
#include "Listable.hpp"
//#include "Comparable.hpp"

template <typename Node>
requires std::derived_from<Node, Listable<Node>>
class LinkedList
{
    //
    // MARK: - Member Types
    //

    /// The type of various iterators
//    using iterator = Node*;
//    using const_iterator = const Node*;
//    using reverse_iterator = Node*;
//    using const_reverse_iterator = const Node*;

    //
    // MARK: - Metadata
    //

protected:
    /// The list head
    Node* head;

    /// The list tail
    Node* tail;

    /// The current number of elements
    size_t count;

    //
    // MARK: - Constructor & Destructor
    //

public:
    /// Create an empty doubly linked list
    explicit LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    //
    // MARK: Queue Operations
    //

    ///
    /// [Queue] Append the given node to the end of the list
    ///
    /// @param node A non-null node to be appended to the end of the list
    ///
    void enqueue(Node* node)
    {
        node->prev = nullptr;

        node->next = nullptr;

        // Guard: Check whether the list is empty
        if (this->isEmpty())
        {
            this->head = node;
        }
        else
        {
            this->tail->next = node;

            node->prev = this->tail;
        }

        this->tail = node;

        this->count += 1;
    }

    ///
    /// [Queue] Remove the first element from the list
    ///
    /// @return A non-null node if the list is not empty, `NULL` otherwise.
    ///
    Node* dequeue()
    {
        // Guard: Check whether the list is empty
        if (this->isEmpty())
        {
            return nullptr;
        }

        // Guard: Check whether the list has only one node
        if (this->count == 1)
        {
            this->tail = nullptr;
        }

        Node* node = this->head;

        this->head = node->next;

        if (this->head != nullptr)
        {
            this->head->prev = nullptr;
        }

        this->count -= 1;

        node->prev = nullptr;

        node->next = nullptr;

        return node;
    }

    //
    // MARK: Stack Operations
    //

    ///
    /// [Stack] Append the given node to the head of the list
    ///
    /// @param node A non-null node to be appended to the end of the list
    ///
    void push(Node* node)
    {
        node->prev = nullptr;

        node->next = nullptr;

        // Guard: Check whether the list is empty
        if (this->isEmpty())
        {
            this->head = node;

            this->tail = node;
        }
        else
        {
            node->next = this->head;

            this->head->prev = node;

            this->head = node;
        }

        this->count += 1;
    }

    ///
    /// [Stack] Remove the last element from the list
    ///
    /// @return A non-null node if the list is not empty, `NULL` otherwise.
    ///
    Node* pop()
    {
        // Guard: Check whether the list is empty
        if (this->isEmpty())
        {
            return nullptr;
        }

        // Guard: Check whether the list has only one node
        if (this->count == 1)
        {
            this->head = nullptr;
        }

        Node* node = this->tail;

        this->tail = node->prev;

        if (this->tail != nullptr)
        {
            this->tail->next = nullptr;
        }

        this->count -= 1;

        node->prev = nullptr;

        node->next = nullptr;

        return node;
    }

    //
    // MARK: List Operations
    //

    ///
    /// Insert the given node in either ascending or descending order
    ///
    /// @tparam Comparator A callable type that returns `true` if the first element is less than the second one
    /// @param node A non-null node to be inserted into the sorted list
    /// @param comparator A comparator instance to determine the order
    ///
    template <typename Comparator>
    void insert(Node* node, Comparator comparator)
    {
        // Find the spot to insert the given node
        Node* current = this->head;

        while (current != nullptr)
        {
            if (comparator(*node, *current))
            {
                break;
            }

            current = current->next;
        }

        // Found the right spot to insert the given node
        // `node` will be inserted before the current node
        // Case 1: List is empty
        if (this->isEmpty())
        {
            this->head = node;

            this->tail = node;
        }
            // Case 2: Node should be inserted front
        else if (current == this->head)
        {
            node->prev = nullptr;

            node->next = current;

            current->prev = node;

            this->head = node;
        }
            // Case 3: Node should be inserted back
        else if (current == nullptr)
        {
            node->prev = this->tail;

            node->next = nullptr;

            this->tail->next = node;

            this->tail = node;
        }
            // Case 4: Node should be inserted in the middle of the list
        else
        {
            node->prev = current->prev;

            node->next = current;

            node->prev->next = node;

            node->next->prev = node;
        }

        this->count += 1;
    }

    ///
    /// Insert the given node in either ascending or descending order
    ///
    /// @param node A non-null node to be inserted into the sorted list
    /// @param ascending Pass `true` if inserted in ascending order, `false` otherwise.
    /// @note This function is only available if the `Node` type conforms to `Comparable`.
    ///
    void insert(Node* node, bool ascending) //requires Comparable<Node>
    {
        if (ascending)
        {
            this->template insert(node, std::less{});
        }
        else
        {
            this->template insert(node, std::greater{});
        }
    }

    ///
    /// Remove the given node from the list
    ///
    /// @param node A non-null node to be removed from the list
    /// @note This function assumes that the given node is in the list.
    ///
    void remove(Node* node)
    {
        // Case 1: `node` is the only element in this list
        if (node == this->head && node == this->tail)
        {
            this->head = nullptr;

            this->tail = nullptr;
        }
        // Case 2: `node` is the list head and more than 2 elements exist
        else if (node == this->head)
        {
            this->head = node->next;

            node->next->prev = nullptr;
        }
        // Case 3: `node` is the list tail and more than 2 elements exist
        else if (node == this->tail)
        {
            this->tail = node->prev;

            node->prev->next = nullptr;
        }
        // Case 4: `node` is in the middle of the list
        else
        {
            node->prev->next = node->next;

            node->next->prev = node->prev;
        }

        this->count -= 1;

        node->prev = nullptr;

        node->next = nullptr;
    }

    //
    // MARK: Query Linked List Properties
    //

    ///
    /// Peek the head node of the list
    ///
    /// @return A constant reference to the current head node.
    ///
    [[nodiscard]]
    const Node* peekHead() const
    {
        return this->head;
    }

    ///
    /// Peek the tail node of the list
    ///
    /// @return A constant reference to the current tail node.
    ///
    [[nodiscard]]
    const Node* peekTail() const
    {
        return this->tail;
    }

    ///
    /// Get the number of nodes in the list
    ///
    /// @return The number nodes in the list.
    ///
    [[nodiscard]]
    size_t getCount() const
    {
        return this->count;
    }

    ///
    /// Check whether the list is empty
    ///
    /// @return `true` if the list is empty, `false` otherwise.
    ///
    [[nodiscard]]
    bool isEmpty() const
    {
        return this->count == 0;
    }

    ///
    /// Call the given action on each element in forward order
    ///
    /// @param action A functor that takes a constant reference to each element in the list
    ///
    template <typename Action>
    requires std::invocable<Action, const Node*> && std::same_as<std::invoke_result_t<Action, const Node*>, void>
    void forEach(Action action) const
    {
        for (Node* current = this->head; current != nullptr; current = current->next)
        {
            action(current);
        }
    }

    ///
    /// Call the give action on each element with their index in forward order
    ///
    /// @param action A functor that takes a constant reference of each node and its index in the list
    ///
    template <typename Action>
    requires std::invocable<Action, const Node*, size_t> && std::same_as<std::invoke_result_t<Action, const Node*, size_t>, void>
    void enumerate(Action action) const
    {
        size_t index = 0;

        for (Node* current = this->head; current != nullptr; current = current->next)
        {
            action(current, index);

            index += 1;
        }
    }

    ///
    /// Call the given action on each element in backward order
    ///
    /// @param action A functor that takes a constant reference to each element in the list
    ///
    template <typename Action>
    requires std::invocable<Action, const Node*> && std::same_as<std::invoke_result_t<Action, const Node*>, void>
    void reverseForEach(Action action) const
    {
        for (Node* current = this->tail; current != nullptr; current = current->prev)
        {
            action(current);
        }
    }

    ///
    /// Call the give action on each element with their index in backward order
    ///
    /// @param action A functor that takes a constant reference of each node and its index in the list
    ///
    template <typename Action>
    requires std::invocable<Action, const Node*, size_t> && std::same_as<std::invoke_result_t<Action, const Node*, size_t>, void>
    void reverseEnumerate(Action action) const
    {
        size_t index = this->count - 1;

        for (Node* current = this->tail; current != nullptr; current = current->prev)
        {
            action(current, index);

            index -= 1;
        }
    }

    ///
    /// Return the first element that satisfies the given predicate
    ///
    /// @param predicate A functor that takes a constant reference to each node and
    ///                  returns `true` if the current element satisfies the predicate
    /// @return The element that satisfies the predicate, `nullptr` if not found such element.
    /// @note The returned element is still in the list.
    ///
    template <typename Predicate>
    requires std::invocable<Predicate, const Node*> && std::same_as<std::invoke_result_t<Predicate, const Node*>, bool>
    Node* first(Predicate predicate)
    {
        for (Node* current = this->head; current != nullptr; current = current->next)
        {
            if (predicate(current))
            {
                return current;
            }
        }

        return nullptr;
    }
};

#endif /* LinkedList_hpp */

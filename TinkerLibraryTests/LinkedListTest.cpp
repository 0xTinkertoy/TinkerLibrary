//
//  LinkedListTest.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 9/15/20.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#include "LinkedListTest.hpp"
#include "LinkedList.hpp"
#include "Debug.hpp"

struct Number: Listable<Number>
{
    uint32_t value;

    explicit Number(uint32_t value) : Listable()
    {
        this->value = value;
    }

    friend bool operator<(const Number& lhs, const Number& rhs)
    {
        return lhs.value < rhs.value;
    }

    friend bool operator>(const Number& lhs, const Number& rhs)
    {
        return rhs < lhs;
    }

    friend bool operator<=(const Number& lhs, const Number& rhs)
    {
        return !(lhs > rhs);
    }

    friend bool operator>=(const Number& lhs, const Number& rhs)
    {
        return !(lhs < rhs);
    }

    friend bool operator==(const Number& lhs, const Number& rhs)
    {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const Number& lhs, const Number& rhs)
    {
        return !(lhs == rhs);
    }
};

void LinkedListTest::run()
{
    pinfof("==== TEST LINKED LIST STARTED ====\n");

    // Setup
    Number n1(1);

    Number n2(2);

    Number n3(3);

    Number n4(4);

    LinkedList<Number> numbers;

    // Append
    numbers.enqueue(&n1);

    numbers.enqueue(&n2);

    numbers.enqueue(&n3);

    passert(!numbers.isEmpty(), "List should not be empty.");

    passert(numbers.getCount() == 3, "There are three elements.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.");

    // Remove First
    passert(numbers.dequeue()->value == 1, "1st element is 1.");

    passert(numbers.getCount() == 2, "List should have 2 elements left.");

    passert(numbers.peekHead()->value == 2, "Head element is 2.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.");

    // Remove First
    passert(numbers.dequeue()->value == 2, "2nd element is 2.");

    passert(numbers.getCount() == 1, "List should have 1 element left.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.");

    // Remove First
    passert(numbers.dequeue()->value == 3, "3rd element is 3.");

    passert(numbers.dequeue() == nullptr, "List should be empty now.");

    passert(numbers.peekHead() == nullptr, "Head element is NULL.");

    passert(numbers.peekTail() == nullptr, "Tail element is NULL.");

    passert(numbers.isEmpty(), "List should be empty now.");

    passert(numbers.getCount() == 0, "List should be empty now.");

    // Append
    numbers.enqueue(&n1);

    numbers.enqueue(&n2);

    numbers.enqueue(&n3);

    // Remove Last
    passert(numbers.pop()->value == 3, "Last element is 3.");

    passert(numbers.getCount() == 2, "List should have 2 elements left.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 2, "Tail element is 2.");

    // Remove Last
    passert(numbers.pop()->value == 2, "Last element is 2.");

    passert(numbers.getCount() == 1, "List should have 1 element left.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 1, "Tail element is 1.");

    // Remove Last
    passert(numbers.pop()->value == 1, "Last element is 1.");

    passert(numbers.getCount() == 0, "List should be empty now.");

    passert(numbers.peekHead() == nullptr, "Head element is NULL.");

    passert(numbers.peekTail() == nullptr, "Tail element is NULL.");

    passert(numbers.isEmpty(), "List should be empty now.");

    passert(numbers.pop() == nullptr, "List should be empty now.");

    // Append
    numbers.enqueue(&n1);

    numbers.enqueue(&n2);

    numbers.enqueue(&n3);

    numbers.enqueue(&n4);

    // Remove (Branch Middle Element)
    numbers.remove(&n2);

    passert(numbers.getCount() == 3, "List should have 3 elements left.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 4, "Tail element is 4.");

    passert(n2.next == nullptr, "2 should have next set to NULL.");

    passert(n2.prev == nullptr, "2 should have prev set to NULL.");

    // Remove (Branch Head Element)
    numbers.remove(&n1);

    passert(numbers.getCount() == 2, "List should have 2 elements left.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 4, "Tail element is 4.");

    passert(n1.next == nullptr, "1 should have next set to NULL.");

    passert(n1.prev == nullptr, "1 should have prev set to NULL.");

    // Remove (Branch Tail Element)
    numbers.remove(&n4);

    passert(numbers.getCount() == 1, "List should have 1 element left.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 3, "Tail element is 4.");

    passert(n4.next == nullptr, "4 should have next set to NULL.");

    passert(n4.prev == nullptr, "4 should have prev set to NULL.");

    // Remove (Brand Single Element)
    numbers.remove(&n3);

    passert(numbers.getCount() == 0, "List should be empty.");

    passert(numbers.peekHead() == nullptr, "List should be empty.");

    passert(numbers.peekTail() == nullptr, "List should be empty.");

    passert(n3.next == nullptr, "3 should have next set to NULL.");

    passert(n3.prev == nullptr, "3 should have prev set to NULL.");

    // Insert in ascending order
    numbers.insert(&n3, true);

    passert(numbers.getCount() == 1, "List should have 1 element.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.");

    passert(n3.next == nullptr, "3 should have next set to NULL.");

    passert(n3.prev == nullptr, "3 should have next set to NULL.");

    // Insert in ascending order
    numbers.insert(&n1, true);

    passert(numbers.getCount() == 2, "List should have 2 elements.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.")

    passert(n1.prev == nullptr, "1 should have prev set to NULL.");

    passert(n1.next == &n3, "1 should have next set to &n3.");

    passert(n3.prev == &n1, "3 should have prev set to &n1.");

    passert(n3.next == nullptr, "3 should have next set to NULL.");

    // Insert in ascending order
    numbers.insert(&n2, true);

    passert(numbers.getCount() == 3, "List should have 3 elements.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.")

    passert(n1.prev == nullptr, "1 should have prev set to NULL.");

    passert(n1.next == &n2, "1 should have next set to &n2.");

    passert(n2.prev == &n1, "2 should have prev set to &n1.");

    passert(n2.next == &n3, "2 should have next set to &n3.");

    passert(n3.prev == &n2, "3 should have prev set to &n2.");

    passert(n3.next == nullptr, "3 should have next set to NULL.");

    // Insert in ascending order
    numbers.insert(&n4, true);

    passert(numbers.getCount() == 4, "List should have 4 elements.");

    passert(numbers.peekHead()->value == 1, "Head element is 1.");

    passert(numbers.peekTail()->value == 4, "Tail element is 4.");

    passert(n1.prev == nullptr, "1 should have prev set to NULL.");

    passert(n1.next == &n2, "1 should have next set to &n2.");

    passert(n2.prev == &n1, "2 should have prev set to &n1.");

    passert(n2.next == &n3, "2 should have next set to &n3.");

    passert(n3.prev == &n2, "3 should have prev set to &n2.");

    passert(n3.next == &n4, "3 should have next set to &n4.");

    passert(n4.prev == &n3, "4 should have prev set to &n3.");

    passert(n4.next == nullptr, "4 should have next set to NULL.");

    // Print the list
    pinfof("List (F): ");

    numbers.forEach([](const Number* number) { pinfof("%d -> ", number->value); });

    pinfof("NULL\n");

    pinfof("List (R): ");

    numbers.reverseForEach([](const Number* number) { pinfof("%d -> ", number->value); });

    pinfof("NULL\n");

    // Remove all elements
    passert(numbers.pop()->value == 4, "Remove 4.");

    passert(numbers.dequeue()->value == 1, "Remove 1.");

    passert(numbers.dequeue()->value == 2, "Remove 2.");

    passert(numbers.pop()->value == 3, "Remove 3.");

    passert(numbers.isEmpty(), "List is now empty.");

    passert(numbers.peekHead() == nullptr, "List is now empty.");

    passert(numbers.peekTail() == nullptr, "List is now empty.");

    // Insert in descending order
    numbers.insert(&n3, false);

    passert(numbers.getCount() == 1, "List should have 1 element.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 3, "Tail element is 3.");

    passert(n3.prev == nullptr, "3 should have prev set to NULL.");

    passert(n3.next == nullptr, "3 should have next set to NULL.");

    // Insert in descending order
    numbers.insert(&n1, false);

    passert(numbers.getCount() == 2, "List should have 2 elements.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 1, "Tail element is 1.");

    passert(n3.prev == nullptr, "3 should have prev set to NULL.");

    passert(n3.next == &n1, "3 should have next set to &n1.");

    passert(n1.prev == &n3, "1 should have prev set to &n3.");

    passert(n1.next == nullptr, "1 should have next set to NULL.");

    // Insert in descending order
    numbers.insert(&n2, false);

    passert(numbers.getCount() == 3, "List should have 3 elements.");

    passert(numbers.peekHead()->value == 3, "Head element is 3.");

    passert(numbers.peekTail()->value == 1, "Tail element is 1.");

    passert(n3.prev == nullptr, "3 should have prev set to NULL.");

    passert(n3.next == &n2, "3 should have next set to &n2.");

    passert(n2.prev == &n3, "2 should have prev set to &n3.");

    passert(n2.next == &n1, "2 should have next set to &n1.");

    passert(n1.prev == &n2, "1 should have prev set to &n2.");

    passert(n1.next == nullptr, "1 should have next set to NULL.");

    // Insert in descending order
    numbers.insert(&n4, false);

    passert(numbers.getCount() == 4, "List should have 4 elements.");

    passert(numbers.peekHead()->value == 4, "Head element is 4.");

    passert(numbers.peekTail()->value == 1, "Tail element is 1.");

    passert(n4.prev == nullptr, "4 should have prev set to NULL.");

    passert(n4.next == &n3, "4 should have next set to &n3.");

    passert(n3.prev == &n4, "3 should have prev set to &n4.");

    passert(n3.next == &n2, "3 should have next set to &n2.");

    passert(n2.prev == &n3, "2 should have prev set to &n3.");

    passert(n2.next == &n1, "2 should have next set to &n1.");

    passert(n1.prev == &n2, "1 should have prev set to &n2.");

    passert(n1.next == nullptr, "1 should have next set to NULL.");

    // Print the list
    pinfof("List (F): ");

    numbers.forEach([](const Number* number) { pinfof("%d -> ", number->value); });

    pinfof("NULL\n");

    pinfof("List (R): ");

    numbers.reverseForEach([](const Number* number) { pinfof("%d -> ", number->value); });

    pinfof("NULL\n");

    // Find the first element that satisfies the predicate
    auto* element1 = numbers.first([](const Number* number) { return number->value == 2; });

    auto* element2 = numbers.first([](const Number* number) { return number->value == 5; });

    passert(element1 != nullptr, "Should be able to find 2.");

    passert(element2 == nullptr, "Should not be able to find 5.");

    passert(element1->next != nullptr, "2 should still be in the list.");

    passert(element1->prev != nullptr, "2 should still be in the list.");

    passert(element1->value == 2, "Should be able to find 2.");

    pinfof("==== TEST LINKED LIST FINISHED ====\n");
}

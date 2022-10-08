//
//  C++Support.cpp
//  TinkerLibrary
//
//  Created by FireWolf on 2021-1-22.
//

#include <cstddef>

#ifdef __KERNEL__

/// This file implements necessary functions for the kernel so that C++ works without the standard library support

//
// MARK: Pure Virtual Functions
//

extern "C" void __cxa_pure_virtual()
{
    // This function should never be called,
    // because it is impossible to construct an instance of an abstract class.
}

//
// MARK: Local Static Variables
//

// Warning: Note that the kernel should never use local static variables
// We don't support this feature

//
// MARK: Dynamic Memory Allocations
//

// If the kernel enables dynamic memory allocations,
// function calls are routed to `kmalloc` and `kfree`,
// which will eventually be routed to MemoryAllocator::alloc() and free().

#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
#warning "Kernel has dynamic memory allocations enabled."
    extern "C" void* kmalloc(size_t size);
    extern "C" void kfree(void* ptr);
#endif

void* operator new(size_t size)
{
#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
    return kmalloc(size);
#else
    (void) size;
    return nullptr;
#endif
}

void* operator new[](size_t size)
{
#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
    return kmalloc(size);
#else
    (void) size;
    return nullptr;
#endif
}

void operator delete(void* ptr)
{
#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
    return kfree(ptr);
#else
    (void) ptr;
#endif
}

void operator delete[](void* ptr)
{
#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
    return kfree(ptr);
#else
    (void) ptr;
#endif
}

// C++14 specialization
void operator delete(void* ptr, size_t size)
{
#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
    (void) size;
    return kfree(ptr);
#else
    (void) ptr;
    (void) size;
#endif
}

// C++14 specialization
void operator delete[](void* ptr, size_t size)
{
#ifdef KERNEL_DYNAMIC_MALLOC_ENABLED
    (void) size;
    return kfree(ptr);
#else
    (void) ptr;
    (void) size;
#endif
}

#endif

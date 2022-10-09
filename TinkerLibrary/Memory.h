//
//  Memory.hpp
//  Kernel-x86
//
//  Created by FireWolf on 2/4/21.
//

#ifndef Memory_hpp
#define Memory_hpp

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

void memset(void *pch, int c, int len);

void* memcpy(void* dest, const void* src, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* Memory_hpp */

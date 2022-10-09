//
//  Memory.cpp
//  Kernel-x86
//
//  Created by FireWolf on 2/4/21.
//

#include "Memory.h"

void memset(void* pch, int c, int len)
{
    unsigned char* byte = (unsigned char*) pch;
    int n;

    if ((n = len) <= 0)
        return;
    do
        *(char *)byte++ = c;
    while (--n);
}

void* memcpy(void* dest, const void* src, size_t len)
{
    char* d = (char*) dest;
    const char* s = (const char*) src;
    while (len--)
        *d++ = *s++;
    return dest;
}

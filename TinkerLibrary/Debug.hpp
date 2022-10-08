//
//  Debug.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-2-11.
//  Revised by FireWolf on 2020-6-9.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef Debug_h
#define Debug_h

#include <stdarg.h>

#ifndef __cplusplus
    #define __PRETTY_FUNCTION__ __func__
#endif

#ifdef _MSC_VER
    #ifndef __PRETTY_FUNCTION__
        #ifdef __FUNCSIG__
            #define __PRETTY_FUNCTION__ __FUNCSIG__
        #elif defined(__FUNCDNAME__)
            #define __PRETTY_FUNCTION__ __FUNCDNAME__
        #else
            #define __PRETTY_FUNCTION__ __func__
        #endif
    #endif
#endif

//
// MARK: - Kernel Formatted Printing
//
#ifdef __KERNEL__
    #ifdef KERNEL_FORMATTED_PRINT_ENABLED
        #include "Print.h"
        #define kprintf     printf
        #define ksprintf    sprintf
        #define ksnprintf   snprintf
        #define kvsnprintf  vsnprintf
        #define kvprintf    vprintf
        #define PRINTF      kprintf
    #else
        #define kprintf     (void)
        #define ksprintf    (void)
        #define ksnprintf   (void)
        #define kvsnprintf  (void)
        #define kvprintf    (void)
        #define PRINTF      (void)
    #endif
#else
    #include <stdlib.h>
    #include <stdio.h>
    #define PRINTF printf
#endif

//
// MARK: - Panic routines
//
#ifdef __KERNEL__
    #ifdef KERNEL_SIMPLE_PANIC
        #define panic(format, ...) \
        {                          \
            while(true);           \
        };
    #else
        extern void panic(const char*, ...);
    #endif
#else
    static inline void panic(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        abort();
    }
#endif

#define PANIC panic

//
// MARK: - Print Macros
//
#ifdef DEBUG
#define pinfo(fmt, ...) \
{                       \
    PRINTF("%s DInfo: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
};
#else
#define pinfo(fmt, ...) {}
#endif

#ifdef DEBUG
#define pinfof(fmt, ...) \
{                        \
    PRINTF("%s DInfo: " fmt, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
};
#else
#define pinfof(fmt, ...) {}
#endif

#ifdef DEBUG
#define perr(fmt, ...) \
{                      \
    PRINTF("%s Error: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
};
#else
#define perr(fmt, ...) {}
#endif

#define pmesg(fmt, ...) \
{                       \
    PRINTF("%s PInfo: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
};

#define pwarning(fmt, ...) \
{                          \
    PRINTF("%s Warning: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
};

#define passert(cond, fmt, ...) \
{ \
    if (!(cond)) \
    { \
        PRINTF("%s Assertion Failed: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
        PANIC("Assertion triggered in file %s at line %d\n", __FILE__, __LINE__); \
    } \
};

#define psoftassert(cond, fmt, ...) \
{ \
    if (!(cond)) \
    { \
        PRINTF("%s Assertion Failed: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
        PRINTF("Assertion triggered in file %s at line %d\n", __FILE__, __LINE__); \
    } \
};

#define pfatal(fmt, ...) \
{ \
    PANIC("%s Fatal Error: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
    __builtin_unreachable();                                                \
};

#define precondition(cond, fmt, ...) \
{ \
    if (!(cond)) \
    { \
        PRINTF("%s Unsatisfied Precondition: " fmt "\n", __PRETTY_FUNCTION__, ##__VA_ARGS__); \
        PANIC("Assertion triggered in file %s at line %d\n", __FILE__, __LINE__); \
    } \
};

#endif /* Debug_h */

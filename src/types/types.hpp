#ifndef _CORE_TYPESH
#define _CORE_TYPESH

#ifndef NULL
#define NULL ((void *)0)
#endif

// try to determine target architecture if not specified
#if !(defined(CORE_64) || defined(CORE_32))

// Windows
#if _WIN32 || _WIN64

#error Sorry, but Windows is not yet supported. Keep in mind that this is a pet project developed on Linux.

#if _WIN64
#define CORE_64
#else
#define CORE_32
#endif

#endif

// GCC
#if __GNUC__

#if __x86_64__ || __ppc64__ || _LP64
#define CORE_64
#else
#define CORE_32
#endif
#endif

#endif

#ifdef CORE_64
typedef unsigned long size_t;
typedef long ssize_t;
#elif defined(CORE_32)
typedef unsigned int size_t;
typedef int ssize_t;
#else
#error Cannot determine architecture, please supply either the CORE_32 or CORE_64 macro.
#endif

typedef unsigned int filed;

#endif

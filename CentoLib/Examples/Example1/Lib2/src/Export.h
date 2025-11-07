#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef LIB2_EXPORTS
#define LIB2_API __declspec(dllexport)
#else
#define LIB2_API __declspec(dllimport)
#endif
#else
#if __GNUC__ >= 4
#define LIB2_API __attribute__ ((visibility ("default")))
#else
#define LIB2_API
#endif
#endif

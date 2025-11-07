#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef CENTO_EXPORTS
#define CENTO_API extern "C" __declspec(dllexport)
#else
#define CENTO_API extern "C" __declspec(dllimport)
#endif

#elif __GNUC__ >= 4
#ifdef CENTO_EXPORTS
#define CENTO_API extern "C" __attribute__((visibility("default")))
#else
#define CENTO_API extern "C" __attribute__((visibility("hidden")))
#endif
#define CENTO_CALL
#else
#define CENTO_API extern "C"
#define CENTO_CALL
#endif

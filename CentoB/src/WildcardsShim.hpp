#pragma once

#ifndef __clang__
#define __clang__ 1
#define CFG_FAKE_CLANG 1
#endif

#ifndef cfg_HAS_CONSTEXPR14
#define cfg_HAS_CONSTEXPR14 1
#endif

#include <wildcards.hpp>

#ifdef CFG_FAKE_CLANG
#undef __clang__
#undef CFG_FAKE_CLANG
#endif

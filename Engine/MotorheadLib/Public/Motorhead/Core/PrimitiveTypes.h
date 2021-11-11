#pragma once

#include "StdIncludes.h"

// Unsigned integers
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

// Signed integers
using s64 = int64_t;
using s32 = int32_t;
using s16 = int16_t;
using s8 = int8_t;

// Float (32 bits)
using f32 = float;

// Invalid indices
constexpr u64 u64_invalid_val{ 0xffff'ffff'ffff'ffffui64 };
constexpr u32 u32_invalid_val{ 0xffff'ffffui32 };
constexpr u16 u16_invalid_val{ 0xffffui16 };
constexpr u8 u8_invalid_val{ 0xffui8 };

// Size type
namespace motor::core {
	using sizeT = std::size_t;
}

// ANSI & Wide characters
using charA = char;
using charW = wchar_t;
#ifdef _WIN64
#ifdef UNICODE
using charT = charW;
#else
using charT = charA;
#endif
#endif

#ifdef UNICODE
#define TXT(string)	L##string
#else
#define TXT(string)	##string
#endif

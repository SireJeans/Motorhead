#pragma once

#include <zlib/zlib.h>
#include "PrimitiveTypes.h"

namespace motor::hash {

	u32 Crc32Hash(const void*, core::sizeT, u32 = 0);

	u32 GetCrc(u32, u8*, core::sizeT);

	constexpr u32 fnv_prime{ 16777619u };
	constexpr u32 fnv_offset{ 2166136261u };

	inline u32 Fnv1aHash(const void* data, core::sizeT length, u32 hash = fnv_offset)
	{
		assert(data != nullptr);
		u32 result = hash;
		u8* current = (u8*)data;
		while (length-- != 0) {
			result ^= *current++;
			result *= fnv_prime;
		}
		return result;
	}

	inline u32 Fnv1aHash(const charA* str, core::sizeT length, u32 hash = fnv_offset)
	{
		return Fnv1aHash((void*)str, length,  hash);
	}

	inline u32 Fnv1aHash(const charA* str)
	{
		assert(str != nullptr);
		core::sizeT length = 0;
		while (str[length] != '\0') {
			++length;
		}
		return Fnv1aHash(str, length * sizeof(charA));
	}

	inline u32 Fnv1aHash(const charW* str, core::sizeT length, u32 hash = fnv_offset)
	{
		return Fnv1aHash((void*)str, length, hash);
	}

	inline u32 Fnv1aHash(const charW* str)
	{
		assert(str != nullptr);
		core::sizeT length = 0;
		while (str[length] != '\0') {
			++length;
		}
		return Fnv1aHash(str, length * sizeof(charW));
	}


}

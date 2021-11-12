#pragma once

#include <zlib/zlib.h>
#include "PrimitiveTypes.h"

namespace motor::hash {

	u32 GetCrc(u32, u8*, core::sizeT);

	inline u32 Fnv1aHash(u32 hash, const charA* str, core::sizeT length)
	{
		for (core::sizeT i = 0; i < length; ++i)
		{
			const u32 value = static_cast<u32>(*str++);
			hash ^= value;
			hash *= 16777619u;
		}

		return hash;
	}

	inline u32 Fnv1aHash(const charA* str, core::sizeT length)
	{
		assert(str != nullptr);
		return Fnv1aHash(2166136261u, str, length);
	}

	inline u32 Fnv1aHash(const charA* str)
	{
		assert(str != nullptr);
		core::sizeT len = 0;
		while (str[len] != '\0') {
			++len;
		}
		return Fnv1aHash(str, len);
	}

	inline u32 Fnv1aHash(u32 hash, const charW* str, core::sizeT length)
	{
		for (core::sizeT i = 0; i < length; ++i)
		{
			const u32 value = static_cast<u32>(*str++);
			hash ^= value;
			hash *= 16777619u;
		}

		return hash;
	}

	inline u32 Fnv1aHash(const charW* str, core::sizeT length)
	{
		assert(str != nullptr);
		return Fnv1aHash(2166136261u, str, length);
	}

	inline u32 Fnv1aHash(const charW* str)
	{
		assert(str != nullptr);
		core::sizeT len = 0;
		while (str[len] != '\0') {
			++len;
		}
		return Fnv1aHash(str, len);
	}


}

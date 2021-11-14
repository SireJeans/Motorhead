#pragma once

#include "CoreMinimal.h"

namespace motor::hash {

	u32 Crc32Hash(const void*, core::sizeT, u32 = 0);

	u32 GetCrc(u32, u8*, core::sizeT);

	//-----------------------------------------------------------------
	// FNV1-a
	
	// Traits for FNV1a
	template<core::sizeT Bits>
	struct Fnv1a_traits
	{
		static constexpr bool supported = false;
	};

	// Traits for 32-bit FNV1a
	template<>
	struct Fnv1a_traits<32>
	{
		static constexpr bool supported = true;
		using Type = u32;

		static constexpr Type prime = 0x1000193;
		static constexpr Type offset = 0x811c9dc5;
	};

	// Traits for 64-bit FNV1a
	template<>
	struct Fnv1a_traits<64>
	{
		static constexpr bool supported = true;
		using Type = u64;

		static constexpr Type prime = 0x100000001b3;
		static constexpr Type offset = 0xcbf29ce484222325;
	};

	// Generic FNV1a implementation
	template<core::sizeT Bits>
	struct Fnv1a
	{
		static_assert(Fnv1a_traits<Bits>::supported);
		using Type = typename Fnv1a_traits<Bits>::Type;

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @comment stop An optional stop character
		 * @param s The string
		 * @param l The string size
		 * @return The fnv-1a hash
		 */
		template<typename T, u8 stop = 0, typename L = decltype(nullptr)>
		static constexpr Type Hash_Impl1Byte(T s,
			const core::sizeT l,
			L stopLen = nullptr,
			Type hash = Fnv1a_traits<Bits>::offset)
		{
			// See <https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function>
			core::sizeT j = 0;
			for (; j < l; j++) {
				const u8 byte = s[j];
				if constexpr (stop != 0) {
					if (byte == stop) {
						if constexpr (!std::is_same<L, decltype(nullptr)>::value) {
							*stopLen = j + 1;
						}
						break;
					}
				}
				hash ^= byte;
				hash *= Fnv1a_traits<Bits>::prime;
			}

			return hash;
		}

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @comment stop An optional stop character
		 * @param s The string
		 * @param l The string size
		 * @return The fnv-1a hash
		 */
		template<typename T, u16 stop = 0, typename L = decltype(nullptr)>
		static constexpr Type Hash_Impl2Bytes(T s,
			const core::sizeT l,
			L stopLen = nullptr,
			Type hash = Fnv1a_traits<Bits>::offset)
		{
			// See <https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function>
			core::sizeT j = 0;
			for (; j < l; j++) {
				const u16 byte = s[j];
				if constexpr (stop != 0) {
					if (byte == stop) {
						if constexpr (!std::is_same<L, decltype(nullptr)>::value) {
							*stopLen = j + 1;
						}
						break;
					}
				}
				hash ^= byte & 0x00FF;
				hash *= Fnv1a_traits<Bits>::prime;
				hash ^= (byte & 0xFF00) >> 8;
				hash *= Fnv1a_traits<Bits>::prime;
			}

			return hash;
		}

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @comment stop An optional stop character
		 * @param s The string
		 * @param l The string size
		 * @return The fnv-1a hash
		 */
		template<typename C, C stop = 0, typename L = decltype(nullptr)>
		static constexpr Type Hash(const C* s,
			const core::sizeT l,
			L stopLen = nullptr,
			Type hash = Fnv1a_traits<Bits>::offset)
		{
			// Accept [ unsigned | signed ] char
			static_assert(std::is_integral<C>::value);
			//static_assert(sizeof(C) == 1);
			if constexpr (sizeof(C) == 1)
				return Hash_Impl1Byte<const C*, stop, L>(s, l, stopLen, hash);
			else if constexpr (sizeof(C) == 2)
				return Hash_Impl2Bytes<const C*, stop, L>(s, l, stopLen, hash);
			else
				return hash;
		}

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @param s The string
		 * @return The fnv-1a hash
		 */
		template<const core::sizeT l>
		static constexpr Type Hash(const charA(&s)[l])
		{
			return Hash(&s[0], l - 1);
		}

		// Do not infer length for char arrays
		template<const core::sizeT l>
		static constexpr Type Hash(charA(&s)[l])
		{
			return Hash(&s[0]);
		}

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @param s The string
		 * @return The fnv-1a hash
		 */
		template<const core::sizeT l>
		static constexpr Type Hash(const charW(&s)[l])
		{
			return Hash(&s[0], l - 1);
		}

		// Do not infer length for char arrays
		template<const core::sizeT l>
		static constexpr Type Hash(charW(&s)[l])
		{
			return Hash(&s[0]);
		}

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @param s The string
		 * @return The fnv-1a hash
		 */
		static constexpr Type Hash(const charA* s) { return Hash(s, __builtin_strlen(s)); }

		/**
		 * Compute the Fowler–Noll–Vo hash
		 * @param s The string
		 * @return The fnv-1a hash
		 */
		static constexpr Type Hash(const charW* s) { return Hash(s, __builtin_wcslen(s)); }

	};

	using Fnv1a32 = Fnv1a<32>;
	using Fnv1a64 = Fnv1a<64>;

	constexpr Fnv1a32::Type operator"" _fnv1a32(const charA* s, const std::size_t l)
	{
		return Fnv1a32::Hash(s, l);
	}
	constexpr Fnv1a64::Type operator"" _fnv1a64(const charA* s, const std::size_t l)
	{
		return Fnv1a64::Hash(s, l);
	}

	constexpr Fnv1a32::Type operator"" _fnv1a32(const charW * s, const std::size_t l)
	{
		return Fnv1a32::Hash(s, l);
	}
	constexpr Fnv1a64::Type operator"" _fnv1a64(const charW * s, const std::size_t l)
	{
		return Fnv1a64::Hash(s, l);
	}


	// Static unit tests: <https://fnvhash.github.io/fnv-calculator-online/>
	static_assert("hello"_fnv1a32 == 0x4f9f2cab);
	static_assert("hello"_fnv1a64 == 0xa430d84680aabd0b);
	static_assert(L"hello"_fnv1a32 == 0xc3457ef7u);
	static_assert(L"hello"_fnv1a64 == 0x32964f71b2764b97ull);


	//
	// Standard functions
	//

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

} // motor::hash

// Make global
using ::motor::hash::operator""_fnv1a32;
using ::motor::hash::operator""_fnv1a64;

#define STRHASH32(str)	str ## _fnv1a32
#define STRHASH64(str)	str ## _fnv1a64
#define WSTRHASH32(str) L ## str ## _fnv1a32
#define WSTRHASH64(str)	L ## str ## _fnv1a64
#define PTRHASH32(str)	::motor::hash::Fnv1a32::Hash(ptr)
#define PTRHASH64(str)	::motor::hash::Fnv1a64::Hash(ptr)

#if USE_UTF16OR32
#define TXTHASH32(str)	WSTRHASH32(str)
#define TXTHASH64(str)	WSTRHASH64(str)
#else
#define TXTHASH32(str)	STRHASH32(str)
#define TXTHASH64(str)	STRHASH64(str)
#endif

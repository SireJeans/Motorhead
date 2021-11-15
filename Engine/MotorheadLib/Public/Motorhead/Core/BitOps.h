#pragma once

//#include "CoreMinimal.h"
#include <type_traits>
#include "PrimitiveTypes.h"

namespace motor::bits {

	template<core::sizeT Bits>
	struct Ops_traits
	{
		static constexpr bool supported = false;
	};

	template<>
	struct Ops_traits<8>
	{
		static constexpr bool supported = true;
		using Type = u8;

	};

	template<>
	struct Ops_traits<16>
	{
		static constexpr bool supported = true;
		using Type = u16;

	};

	template<>
	struct Ops_traits<32>
	{
		static constexpr bool supported = true;
		using Type = u32;

	};

	template<>
	struct Ops_traits<64>
	{
		static constexpr bool supported = true;
		using Type = u64;

	};

	template<core::sizeT Bits>
	struct Ops
	{
		static_assert(Ops_traits<Bits>::supported, "Unsupported bits size.");
		using Type = typename Ops_traits<Bits>::Type;

		static constexpr Type Get(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & ((Type)1 << bit_number);
		}

		static constexpr Type GetLower(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & ~(~(Type)0 << (bit_number + 1));
		}

		static constexpr Type GetHigher(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & ~(((Type)1 << bit_number) - (Type)1);
		}

		static constexpr Type GetLowest1(Type bits)
		{
			return bits & (~bits + (Type)1);
		}

		static constexpr Type GetLowest0(Type bits)
		{
			return GetLowest1(bits) >> 1;
		}

		static constexpr Type GetHighest1(Type bits)
		{
			u64 val = (u64)bits;

			val = ((u64)0xFFFFFFFF00000000 & val) ? ((u64)0xFFFFFFFF00000000 & val) : val;
			val = ((u64)0xFFFF0000FFFF0000 & val) ? ((u64)0xFFFF0000FFFF0000 & val) : val;
			val = ((u64)0xFF00FF00FF00FF00 & val) ? ((u64)0xFF00FF00FF00FF00 & val) : val;
			val = ((u64)0xF0F0F0F0F0F0F0F0 & val) ? ((u64)0xF0F0F0F0F0F0F0F0 & val) : val;
			val = ((u64)0xCCCCCCCCCCCCCCCC & val) ? ((u64)0xCCCCCCCCCCCCCCCC & val) : val;
			val = ((u64)0xAAAAAAAAAAAAAAAA & val) ? ((u64)0xAAAAAAAAAAAAAAAA & val) : val;

			return (Type)val;
		}

		static constexpr Type GetHighest0(Type bits)
		{
			return GetHighest1(bits) << 1;
		}

		static constexpr Type Set(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits | ((Type)1 << bit_number);
		}

		static constexpr void Set(Type* bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			*bits = *bits & ((Type)1 << bit_number);
		}

		static constexpr Type SetRange0(Type bits, core::sizeT start, core::sizeT range)
		{
			assert(start < sizeof(Type) * 8);
			assert(range + start < (sizeof(Type) * 8 + 1));

			return bits & ~(~(~(Type)0 << range) << start);
		}

		static constexpr void SetRange0(Type* bits, core::sizeT start, core::sizeT range)
		{
			assert(start < sizeof(Type) * 8);
			assert(range + start < (sizeof(Type) * 8 + 1));

			*bits = *bits & ~(~(~(Type)0 << range) << start);
		}

		static constexpr Type SetRange1(Type bits, core::sizeT start, core::sizeT range)
		{
			assert(start < sizeof(Type) * 8);
			assert(range + start < (sizeof(Type) * 8 + 1));

			return bits | (~(~(Type)0 << range) << start);
		}

		static constexpr void SetRange1(Type* bits, core::sizeT start, core::sizeT range)
		{
			assert(start < sizeof(Type) * 8);
			assert(range + start < (sizeof(Type) * 8 + 1));

			*bits = *bits | (~(~(Type)0 << range) << start);
		}

		static constexpr Type Clear(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & ~((Type)1 << bit_number);
		}

		static constexpr void Clear(Type* bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			*bits = *bits & ~((Type)1 << bit_number);
		}

		static constexpr Type ClearLower(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & (~(Type)0 << bit_number);
		}

		static constexpr Type ClearHigher(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & ~(~(Type)0 << bit_number);
		}

		static constexpr void ClearLower(Type* bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			*bits = *bits & (~(Type)0 << bit_number);
		}

		static constexpr void ClearHigher(Type* bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			*bits = *bits & ~(~(Type)0 << bit_number);
		}

		static constexpr core::sizeT Count1(Type bits)
		{
			static const u64 m1 = 0x5555555555555555;
			static const u64 m2 = 0x3333333333333333;
			static const u64 m4 = 0x0f0f0f0f0f0f0f0f;
			static const u64 m8 = 0x00ff00ff00ff00ff;
			static const u64 m16 = 0x0000ffff0000ffff;
			static const u64 m32 = 0x00000000ffffffff;
			static const u64 h01 = 0x0101010101010101;

			u64 val = (u64)bits;

			val = (val & m1) + ((val >> 1) & m1); //put count of each  2 bits into those  2 bits 
			val = (val & m2) + ((val >> 2) & m2); //put count of each  4 bits into those  4 bits 
			val = (val & m4) + ((val >> 4) & m4); //put count of each  8 bits into those  8 bits 
			val = (val & m8) + ((val >> 8) & m8); //put count of each 16 bits into those 16 bits 
			val = (val & m16) + ((val >> 16) & m16); //put count of each 32 bits into those 32 bits 
			val = (val & m32) + ((val >> 32) & m32); //put count of each 64 bits into those 64 bits 

			return (core::sizeT)val;
		}

		static constexpr core::sizeT Count0(Type bits)
		{
			return (core::sizeT)(sizeof(Type) * 8 - Count1(bits));
		}

	};

	using Ops8 = Ops<8>;
	using Ops16 = Ops<16>;
	using Ops32 = Ops<32>;
	using Ops64 = Ops<64>;


}

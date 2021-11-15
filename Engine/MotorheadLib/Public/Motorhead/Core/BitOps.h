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

		static constexpr Type Set(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits | ((Type)1 << bit_number);
		}

		static constexpr Type Clear(Type bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			return bits & ~((Type)1 << bit_number);
		}

		static constexpr void Set(Type* bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			*bits = *bits & ((Type)1 << bit_number);
		}

		static constexpr void Clear(Type* bits, core::sizeT bit_number)
		{
			assert(bit_number < sizeof(Type) * 8);

			*bits = *bits & ~((Type)1 << bit_number);
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

		static constexpr Type GetLowest1(Type bits)
		{
			return bits & (~bits + (Type)1);
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

		static constexpr core::sizeT Count1(Type bits)
		{
			u64 val = (u64)bits;

			val = (((u64)0xAAAAAAAAAAAAAAAA & val) >> 1) + ((u64)0x5555555555555555 & val);
			val = (((u64)0xCCCCCCCCCCCCCCCC & val) >> 2) + ((u64)0x3333333333333333 & val);
			val = (((u64)0xF0F0F0F0F0F0F0F0 & val) >> 4) + ((u64)0x0F0F0F0F0F0F0F0F & val);
			val = (((u64)0xFF00FF00FF00FF00 & val) >> 8) + ((u64)0x00FF00FF00FF00FF & val);
			val = (((u64)0xFFFF0000FFFF0000 & val) >> 16) + ((u64)0x0000FFFF0000FFFF & val);
			val = (((u64)0xFFFFFFFF00000000 & val) >> 32) + ((u64)0x00000000FFFFFFFF & val);

			return (core::sizeT)val;
		}
	};

	using Ops8 = Ops<8>;
	using Ops16 = Ops<16>;
	using Ops32 = Ops<32>;
	using Ops64 = Ops<64>;


}

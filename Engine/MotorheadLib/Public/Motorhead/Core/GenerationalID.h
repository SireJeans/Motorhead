#pragma once

#include "StdIncludes.h"

#include "PrimitiveTypes.h"

#ifndef GENID_TYPE
#define GENID_TYPE	u64
#endif

#ifndef GENID_GENERATION_SIZE
#define GENID_GENERATION_SIZE	32
#endif

#ifndef GENID_MIN_DELETED_ELMNT
#define GENID_MIN_DELETED_ELMNT		512
#endif

namespace motor::id {

	using id_type = GENID_TYPE;

	namespace internal {

		constexpr u32 generation_bits{ GENID_GENERATION_SIZE };
		constexpr u32 index_bits{ sizeof(id_type) * 8 - generation_bits };
		constexpr id_type index_mask{ (id_type{1} << index_bits) - 1 };
		constexpr id_type generation_mask{ (id_type{1} << index_bits) - 1 };

	} // id::internal

	constexpr id_type invalid_id{ id_type(-1) };
	constexpr u32	min_deleted_elements{ GENID_MIN_DELETED_ELMNT };

	using generation_type = std::conditional_t<internal::generation_bits <= 32, std::conditional_t<internal::generation_bits <= 16, std::conditional_t<internal::generation_bits <= 8, u8, u16>, u32>, u64>;
	using index_type = std::conditional_t<internal::index_bits <= 32, std::conditional_t<internal::index_bits <= 16, std::conditional_t<internal::index_bits <= 8, u8, u16>, u32>, u64>;
	static_assert(sizeof(generation_type) * 8 >= internal::generation_bits);
	static_assert(sizeof(index_type) * 8 >= internal::index_bits);
	static_assert(sizeof(id_type) - sizeof(generation_type) > 0);

	constexpr inline bool IsValid(id_type id) 
	{
		return id != invalid_id;
	}

	constexpr inline id_type Index(id_type id)
	{
		id_type index{ id & internal::index_mask };
		assert(index != internal::index_mask);
		return index;
	}

	constexpr inline generation_type Generation(id_type id)
	{
		return (id >> internal::index_bits) & internal::generation_mask;
	}

	constexpr inline id_type NewGeneration(id_type id)
	{
		const generation_type generation{ id::Generation(id) + 1 };
		assert(generation < internal::generation_mask);
		return Index(id & internal::index_mask) | (((u64)generation) << internal::index_bits);
	}

#define DEFINE_ID_TYPE(name)	using name = ::motor::id::id_type

} // motor::id

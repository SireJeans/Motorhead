#pragma once

#include "CoreMinimal.h"

namespace motor::platform {

	enum class MemTag : u8
	{
		Unknown = 0,
		SBP,
		MBP,
		Large,

		NumTags
	};

	// Platform allocs. Implemented by specific platform.
	void* Alloc(core::sizeT, MemTag = MemTag::Unknown);
	void Free(void*);
	void Zero(void*, core::sizeT);
	void Copy(void*, const void*, core::sizeT);
	void Set(void*, sint, core::sizeT);

	template<core::sizeT SmallPageSize, core::sizeT MediumPageSize>
	struct MemApi
	{
		static constexpr core::sizeT k_small_page_size = SmallPageSize;
		static constexpr core::sizeT k_medium_page_size = MediumPageSize;

		virtual void*	IsSmallBlock(void* ptr) const = 0;  // returns the address of the PAGE this pointer is on
		virtual void*	IsMediumBlock(void* ptr) const = 0;
		virtual bool	IsLargeBlock(void* ptr) const = 0;

		virtual void*	AllocSmallPage(void) = 0;
		virtual void    FreeSmallPage(void* ptr) = 0;
	};

}

#pragma once

#include "CoreMinimal.h"

namespace motor::mem {

	enum class Tag : u8
	{
		Unknown = 0,

		NumTags
	};

	void* Alloc(core::sizeT, Tag = Tag::Unknown);
	void Free(void*, core::sizeT, Tag);
	void Zero(void*, core::sizeT);
	void Copy(void*, const void*, core::sizeT);
	void Set(void*, sint, core::sizeT);
}

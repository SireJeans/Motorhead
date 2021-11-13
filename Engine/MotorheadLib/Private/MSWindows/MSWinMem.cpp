#include "Motorhead/MSWindows/MSWinCommon.h"

namespace motor::platform {

	void* Alloc(core::sizeT size)
	{
		return malloc(size);
	}

	void Free(void* block)
	{
		free(block);
	}

	void Zero(void* block, core::sizeT size)
	{
		ZeroMemory(block, size);
	}

	void Copy(void* dest, const void* source, core::sizeT size)
	{
		memcpy(dest, source, size);
	}

	void Set(void* block, sint value, core::sizeT size)
	{
		memset(block, value, size);
	}

}

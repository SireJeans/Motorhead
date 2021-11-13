#pragma once

#include "MSWinCommon.h"

namespace motor::platform {

	void* Alloc(core::sizeT);
	void Free(void*);
	void Zero(void*, core::sizeT);
	void Copy(void*, const void*, core::sizeT);
	void Set(void*, sint, core::sizeT);

}

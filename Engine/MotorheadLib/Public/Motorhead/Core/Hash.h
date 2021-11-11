#pragma once

#include <zlib/zlib.h>

namespace motor::hash {

	u32 GetCrc(u32, u8*, core::sizeT);

}

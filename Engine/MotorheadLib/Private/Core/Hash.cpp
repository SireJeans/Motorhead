#include <Motorhead/Core/CoreCommon.h>

namespace motor::hash {

	u32 GetCrc(u32 crc, u8* bytes, core::sizeT size) {
		return crc32(crc, bytes, (u32)size);
	}

}

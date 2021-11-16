#include "Motorhead/Core/CorePCH.h"
#include "Motorhead/Core/CoreCommon.h"

namespace motor::mem {

	struct MotorMemoryStats {
		u64	total_alloc;
		u64 tagged_alloc[(u8)MemTag::NumTags];
	};

	namespace {
		MotorMemoryStats stats;

		const charT* mem_tag_strings[(u8)MemTag::NumTags] =
		{
			TXT("UNKNOWN")
		};
	}

	void* Alloc(core::sizeT size, MemTag tag)
	{
		stats.total_alloc += size;
		stats.tagged_alloc[(u8)tag] += size;

		// TODO: Memory alignment
		void* block = platform::Alloc(size);
		platform::Zero(block, size);

		return block;
	}

	void Free(void* block, core::sizeT size, MemTag tag)
	{
		stats.total_alloc -= size;
		stats.tagged_alloc[(u8)tag] -= size;
		
		// TODO: Memory alignment
		platform::Free(block);
	}

	void Zero(void* block, core::sizeT size)
	{
		platform::Zero(block, size);
	}

	void Copy(void* dest, const void* source, core::sizeT size)
	{
		platform::Copy(dest, source, size);
	}

	void Set(void* block, sint value, core::sizeT size)
	{
		platform::Set(block, value, size);
	}

}

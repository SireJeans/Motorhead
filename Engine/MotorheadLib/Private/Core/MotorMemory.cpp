#include "Motorhead/Core/CoreCommon.h"
#include "Motorhead/Core/Platform/PlatformCommon.h"

namespace motor::mem {

	struct MemoryStats {
		u64	total_alloc;
		u64 tagged_alloc[(u8)Tag::NumTags];
	};

	namespace {
		MemoryStats stats;

		const charT* mem_tag_strings[(u8)Tag::NumTags] =
		{
			TXT("UNKNOWN")
		};
	}

	void* Alloc(core::sizeT size, Tag tag)
	{
		stats.total_alloc += size;
		stats.tagged_alloc[(u8)tag] += size;

		// TODO: Memory alignment
		void* block = platform::Alloc(size);
		platform::Zero(block, size);

		return block;
	}

	void Free(void* block, core::sizeT size, Tag tag)
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

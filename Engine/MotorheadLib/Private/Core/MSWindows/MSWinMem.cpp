#include "Motorhead/Core/CorePCH.h"
#include "MSWindows/MSWinCommon.h"

namespace motor::platform {

	struct PointerInfo
	{
		core::sizeT		size;
		MemTag			tag;
	};

	struct MemoryStats 
	{
		unint	total_allocated{ 0 };
		unint	tagged_allocated[(u8)MemTag::NumTags];
		unint	total_allocations{ 0 };
		unint	tagged_allocations[(u8)MemTag::NumTags];
		core::Map<void*, PointerInfo>	allocations;

		MemoryStats()
		{
			for (int i = 0; i < (u8)MemTag::NumTags; ++i)
			{
				tagged_allocated[i] = 0;
				tagged_allocations[i] = 0;
			}
		}
	};

	namespace {
		MemoryStats stats;

		const charT* mem_tag_strings[(u8)MemTag::NumTags] =
		{
			TXT("UNKNOWN"),
			TXT("SBP"),
			TXT("MBP"),
			TXT("Large")
		};
	}

	void* Alloc(core::sizeT size, MemTag tag)
	{
		void* ptr = malloc(size);
		
		if (ptr)
		{
			Zero(ptr, size);
			PointerInfo ptr_info;
			ptr_info.size = size;
			ptr_info.tag = tag;
			stats.allocations[ptr] = ptr_info;
			stats.total_allocated += size;
			stats.tagged_allocated[(u8)tag] += size;
			stats.total_allocations += 1;
			stats.tagged_allocations[(u8)tag] += 1;
		}

		return ptr;
	}

	void Free(void* block)
	{
		if (block)
		{
			free(block);
			PointerInfo ptr_info = stats.allocations[block];
			stats.total_allocated -= ptr_info.size;
			stats.tagged_allocated[(u8)ptr_info.tag] -= ptr_info.size;
			stats.total_allocations -= 1;
			stats.tagged_allocations[(u8)ptr_info.tag] -= 1;
			stats.allocations.erase(block);
		}
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


	void* MemApiMSWinDumb::AllocSmallPage(void)
	{
		void* page_address = platform::Alloc(k_small_page_size, MemTag::SBP);
		assert(page_address);
		m_small_pages.push_back(page_address);
		return page_address;
	}

	void MemApiMSWinDumb::FreeSmallPage(void* ptr)
	{
		platform::Free(ptr);
		unint i = 0;
		for (auto var = m_small_pages.begin(); var != m_small_pages.end(); ++var)
		{
			if (*var == ptr)
			{
				m_small_pages.erase(var);
				break;
			}
		}
	}

}

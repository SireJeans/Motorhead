#pragma once

#include "CoreMinimal.h"
#include "Platform/PlatformCommon.h"
#include "Containers.h"
#include "Platform/PlatformMemory.h"

namespace motor::mem {

	enum class MemTag : u8
	{
		Unknown = 0,

		NumTags
	};

	void* Alloc(core::sizeT, MemTag = MemTag::Unknown);
	void Free(void*, core::sizeT, MemTag = MemTag::Unknown);
	void Zero(void*, core::sizeT);
	void Copy(void*, const void*, core::sizeT);
	void Set(void*, sint, core::sizeT);

	template<core::sizeT PageSize>
	struct SmallBlockPage
	{
	protected:
		struct Tail
		{
			u32					free_count;
			u32					block_count;
			unint*				bitfield;
			u16					block_size;
		};

	public:
		void	Initialize(core::sizeT block_size);
		void*	Alloc(bool* is_full);
		bool	Free(void* ptr, bool* was_full);

		Tail* GetTail(void) const { return (Tail*)((u8*)this + s_tail_offset); }

	protected:

		static const core::sizeT s_tail_offset{ PageSize - sizeof(Tail) };

		static_assert(PageSize - sizeof(Tail) > 0);

	};

	template<core::sizeT PageSize>
	void SmallBlockPage<PageSize>::Initialize(core::sizeT block_size)
	{
		Tail* tail = GetTail();

		const unint max_block_per_page = (PageSize - sizeof(Tail)) / block_size;
		const unint bytes_required_for_tail = (max_block_per_page + sizeof(unint) * 8) / (sizeof(unint) * 8) * sizeof(unint) + sizeof(Tail);
		const unint num_blocks = (PageSize - bytes_required_for_tail) / block_size;
		const unint num_bytes_in_bitfield = (num_blocks + sizeof(unint) * 8) / (sizeof(unint) * 8) * sizeof(unint);

		tail->block_size = (u16)block_size;
		tail->block_count = num_blocks;
		tail->free_count = num_blocks;
		tail->bitfield = (u8*)tail - num_bytes_in_bitfield;

		//TODO: Finish implementation
	}

	template<core::sizeT PageSize>
	struct MediumBlockPage
	{
	public:

	protected:
		struct Tail
		{

		};
	};


	template<core::sizeT MinSmallAlloc
		, core::sizeT SmallAllocStepSize
		, core::sizeT MinMediumAlloc
		, core::sizeT MediumAllocStepSize
		, core::sizeT MinLargeAlloc
		, class Api>
	struct FastMemManager
	{
	public:

		FastMemManager(void);
		~FastMemManager(void);

		void* Alloc(core::sizeT size, MemTag tag = MemTag::Unknown);
		bool Free(void* ptr, MemTag tag = MemTag::Unknown);

	private:

		static const core::sizeT small_page_size = Api::k_small_page_size;
		static const core::sizeT medium_page_size = Api::k_medium_page_size;

		static const core::sizeT num_small_pages = (MinMediumAlloc - MinSmallAlloc + SmallAllocStepSize - 1) / SmallAllocStepSize;
		static const core::sizeT num_medium_pages = medium_page_size / MediumAllocStepSize;

		using SBPType = SmallBlockPage<small_page_size>;
		using MBPType = MediumBlockPage<medium_page_size>;

		core::List<SBPType*> m_small_pages[num_small_pages];
		core::List<SBPType*> m_small_pages_full[num_small_pages];
		core::List<MBPType*> m_medium_pages[num_medium_pages];

		// Total
		unint m_small_memory_allocated;
		unint m_medium_memory_allocated;
		unint m_large_memory_allocated;

		unint m_small_allocations;
		unint m_medium_allocations;
		unint m_large_allocations;

		Api		m_mem_api;

	};

	template<core::sizeT MinSmallAlloc
		, core::sizeT SmallAllocStepSize
		, core::sizeT MinMediumAlloc
		, core::sizeT MediumAllocStepSize
		, core::sizeT MinLargeAlloc
		, class Api>
	FastMemManager<MinSmallAlloc
		, SmallAllocStepSize
		, MinMediumAlloc
		, MediumAllocStepSize
		, MinLargeAlloc
		, Api>::FastMemManager(void)
	{
		m_small_memory_allocated = 0;
		m_medium_memory_allocated = 0;
		m_large_memory_allocated = 0;

		m_small_allocations = 0;
		m_medium_allocations = 0;
		m_large_allocations = 0;
	}

	template<core::sizeT MinSmallAlloc
		, core::sizeT SmallAllocStepSize
		, core::sizeT MinMediumAlloc
		, core::sizeT MediumAllocStepSize
		, core::sizeT MinLargeAlloc
		, class Api>
	FastMemManager<MinSmallAlloc
		, SmallAllocStepSize
		, MinMediumAlloc
		, MediumAllocStepSize
		, MinLargeAlloc
		, Api>::~FastMemManager(void)
	{
		// TODO: Display memory leaks and try freeing them before destruction. 
		for (unint i = 0; i < num_small_pages; ++i)
		{
			for (auto var : m_small_pages[i])
			{

			}
			for (auto var : m_small_pages_full[i])
			{

			}
		}		
		for (unint i = 0; i < num_medium_pages; ++i)
		{
			for (auto var : m_medium_pages[i])
			{

			}
		}
	}

	template<core::sizeT MinSmallAlloc
		, core::sizeT SmallAllocStepSize
		, core::sizeT MinMediumAlloc
		, core::sizeT MediumAllocStepSize
		, core::sizeT MinLargeAlloc
		, class Api>
	void* FastMemManager<MinSmallAlloc
		, SmallAllocStepSize
		, MinMediumAlloc
		, MediumAllocStepSize
		, MinLargeAlloc
		, Api>::Alloc(core::sizeT size, MemTag tag)
	{
		if (size < MinMediumAlloc)
		{
			// Small block allocation
		}
		else if (size < MinLargeAlloc)
		{
			// Medium block allocation
		}
		else
		{
			// Large block allocation
			m_large_memory_allocated += size;
			++m_large_allocations;
		}


	}

	template<core::sizeT MinSmallAlloc
		, core::sizeT SmallAllocStepSize
		, core::sizeT MinMediumAlloc
		, core::sizeT MediumAllocStepSize
		, core::sizeT MinLargeAlloc
		, class Api>
	bool FastMemManager<MinSmallAlloc
		, SmallAllocStepSize
		, MinMediumAlloc
		, MediumAllocStepSize
		, MinLargeAlloc
		, Api>::Free(void* ptr, MemTag tag)
	{

	}

}

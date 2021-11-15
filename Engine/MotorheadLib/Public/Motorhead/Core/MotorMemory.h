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

	template<core::sizeT PageSize>
	struct SmallBlockPage
	{
	protected:
		struct Tail
		{
			u32					free_count;
			u32					block_count;
			u8*					bitfield;
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
}

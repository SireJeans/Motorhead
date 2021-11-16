#pragma once

//#include "CoreMinimal.h"
#include "Platform/PlatformMemory.h"
//#include "MotorMemory.h"
#include "Containers.h"

namespace motor::platform {

	// 
	struct MemApiMSWinDumb : public platform::MemApi<6 * 1024, 6 * 1024>
	{
		virtual void* IsSmallBlock(void* ptr) const override
		{
			// returns the address of the PAGE this pointer is on
			void* page_start = (void*)((unint)ptr & ~(k_small_page_size - 1));  // assume all small pages are aligned to their own size addresses, or better
			for (auto var : m_small_pages)
			{
				if (var == page_start)
				{
					return page_start;
				}
			}
			return nullptr;
		}

		virtual void* IsMediumBlock(void* ptr) const override
		{
			return nullptr;
		}

		virtual bool IsLargeBlock(void* ptr) const override
		{
			return false;
		}

		virtual void* AllocSmallPage(void) override;
		virtual void FreeSmallPage(void* ptr) override;

	private:
		core::Vector<void*>				m_small_pages;
		core::Vector<void*>				m_medium_pages;
		core::Map<void*, core::sizeT>	m_large_allocs;
	};

	using DefaultMemApi = MemApiMSWinDumb;

}

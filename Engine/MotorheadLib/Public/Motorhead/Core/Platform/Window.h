#pragma once

//#include "Motorhead/Core/CoreMinimal.h"
#include "CoreCommon.h"
#include "GenerationalID.h"


namespace motor::platform {

	DEFINE_ID_TYPE(window_id);

	struct WindowInitInfo;

	class Window {
	public:
		constexpr explicit Window(window_id id) : _id{ id } {}
		constexpr Window() : _id{ id::invalid_id }  { }
		constexpr window_id GetId() { return _id; }
		constexpr bool IsValid() const { return id::IsValid(_id); }

		void SetFullscreen(bool is_fullscreen) const;
		bool IsFullscreen() const;
		void* Handle() const;
		void SetCaption(const charW* caption) const;
		const math::uvec4 Size() const;
		void Resize(u32 width, u32 height) const;
		const u32 Width() const;
		const u32 Height() const;
		bool IsClosed() const;

	private:
		window_id	_id;
	};

}

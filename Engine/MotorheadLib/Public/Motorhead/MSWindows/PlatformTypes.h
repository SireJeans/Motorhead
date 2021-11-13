#pragma once

#include "Motorhead/Core/CoreCommon.h"
#include "../Platform/PlatformCommon.h"

namespace motor::platform {

	using WindowProc = LRESULT(*)(HWND, UINT, WPARAM, LPARAM);
	using WindowHandle = HWND;

	struct WindowInitInfo {
		WindowProc		callback{ nullptr };
		WindowHandle	parent{ nullptr };
		const charW*	caption{ nullptr };
		s32				left{ 0 };
		s32				top{ 0 };
		s32				width{ 1920 };
		s32				height{ 1080 };
	};

	Window CreateWnd(const WindowInitInfo* const init_info);
	void RemoveWnd(window_id);
}

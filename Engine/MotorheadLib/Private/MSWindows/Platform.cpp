#include "Motorhead/MSWindows/MSWinCommon.h"

#include "Motorhead/Core/CoreCommon.h"
#include "Motorhead/Platform/PlatformCommon.h"

namespace motor::platform {

	namespace {
		struct WindowInfo {
			HWND	hwnd{ nullptr };
			RECT	client_area{ };
			RECT	fullscreen_area{ };
			POINT	top_left{ 0, 0 };
			DWORD	style{ WS_VISIBLE };
			bool	is_fullscreen{ false };
			bool	is_closed{ false };
		};

		core::vector<WindowInfo>	windows;
		core::vector<u32>			free_slots;
		
		u32 AddToWindows(WindowInfo info) {
			u32 id{ u32_invalid_val };

			if (free_slots.empty()) {
				id = windows.size();
				windows.emplace_back(info);
			} else {
				id = free_slots.back();
				free_slots.pop_back();
				assert(id != u32_invalid_val);
				windows[id] = info;
			}

			return id;
		}

		void RemoveFromWindows(u32 id) {
			assert(id != u32_invalid_val);
			assert(id < windows.size());
			free_slots.emplace_back(id);
		}

		WindowInfo& GetInfoFromId(u32 id) {
			assert(id != u32_invalid_val);
			assert(id < windows.size());
			assert(windows[id].hwnd);
			return windows[id];
		}

		WindowInfo& GetInfoFromHandle(WindowHandle handle) {
			const window_id id{ (id::genid_type)GetWindowLongPtr(handle, GWLP_USERDATA) };
			return GetInfoFromId(id);
		}

		void ResizeWindow(const WindowInfo& info, const RECT& area) {
			RECT window_rect{ area };
			AdjustWindowRect(&window_rect, info.style, FALSE);

			const u32 width{ (u32)window_rect.right - (u32)window_rect.left };
			const u32 height{ (u32)window_rect.bottom - (u32)window_rect.top };

			MoveWindow(info.hwnd, info.top_left.x, info.top_left.y, width, height, true);
		}

		void ResizeWindow(window_id id, u32 width, u32 height) {
			WindowInfo& info{ GetInfoFromId(id) };
			RECT area{ info.is_fullscreen ? info.fullscreen_area : info.client_area };

			area.right = area.left + width;
			area.bottom = area.top + height;

			ResizeWindow(info, area);
		}

		void SetWindowFullscreen(u32 id, bool is_fullscreen) {
			WindowInfo& info{ GetInfoFromId(id) };
			if (info.is_fullscreen != is_fullscreen) {
				info.is_fullscreen = is_fullscreen;

				if (is_fullscreen) {
					GetClientRect(info.hwnd, &info.client_area);
					RECT rect;
					GetWindowRect(info.hwnd, &rect);
					info.top_left.x = rect.left;
					info.top_left.y = rect.top;
					info.style = 0;
					SetWindowLongPtr(info.hwnd, GWL_STYLE, info.style);
					ShowWindow(info.hwnd, SW_MAXIMIZE);
				} else {
					info.style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
					SetWindowLongPtr(info.hwnd, GWL_STYLE, info.style);
					ResizeWindow(info, info.client_area);
					ShowWindow(info.hwnd, SW_SHOWNORMAL);
				}
			}
		}

		bool IsWindowFullscreen(window_id id) {
			return GetInfoFromId(id).is_fullscreen;
		}

		WindowHandle GetWindowHandle(window_id id) {
			return GetInfoFromId(id).hwnd;
		}

		void SetWindowCaption(window_id id, const charW* caption) {
			WindowInfo& info{ GetInfoFromId(id) };
			SetWindowText(info.hwnd, caption);
		}

		bool IsWindowClosed(window_id id) {
			return GetInfoFromId(id).is_closed;
		}

		math::uvec4 GetWindowSize(window_id id) {
			WindowInfo& info{ GetInfoFromId(id) };
			RECT area{ info.is_fullscreen ? info.fullscreen_area : info.client_area };
			return { (u32)area.left, (u32)area.top, (u32)area.right,(u32)area.bottom };
		}

		LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			WindowInfo* info{ nullptr };
			switch (msg)
			{
			case WM_DESTROY:
				GetInfoFromHandle(hwnd).is_closed = true;
				break;
			case WM_EXITSIZEMOVE:
				info = &GetInfoFromHandle(hwnd);
				break;
			case WM_SIZE:
				if (wparam == SIZE_MAXIMIZED) {
					info = &GetInfoFromHandle(hwnd);
				}
				break;
			case WM_SYSCOMMAND:
				if (wparam == SC_RESTORE) {
					info = &GetInfoFromHandle(hwnd);
				}
				break;
			}

			if (info) {
				assert(info->hwnd);
				GetClientRect(info->hwnd, info->is_fullscreen ? &info->fullscreen_area : &info->client_area);

			}

			LONG_PTR long_ptr{ GetWindowLongPtr(hwnd, 0) };
			return long_ptr
				? ((WindowProc)long_ptr)(hwnd, msg, wparam, lparam)
				: DefWindowProc(hwnd, msg, wparam, lparam);
		}

	} // anonymous namespace

	Window CreateWnd(const WindowInitInfo* const init_info) {
		WindowProc callback(init_info ? init_info->callback: nullptr);
		WindowHandle parent(init_info ? init_info->parent: nullptr);

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = InternalWindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = callback ? sizeof(callback) : 0;
		wc.hInstance = 0;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = CreateSolidBrush(RGB(26,48,76));
		wc.lpszMenuName = NULL;
		wc.lpszClassName = L"MotorheadWindow";
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		RegisterClassEx(&wc);

		WindowInfo info = {};
		RECT rc{ info.client_area };

		AdjustWindowRect(&rc, info.style, FALSE);

		const charW* caption{ (init_info && init_info->caption) ? init_info->caption : L"Motorhead Game" };
		const s32 left{ init_info ? init_info->left : info.client_area.left };
		const s32 top{ init_info ? init_info->top : info.client_area.top };
		const s32 width{ init_info ? init_info->width : rc.left - rc.right };
		const s32 height{ init_info ? init_info->height : rc.top - rc.bottom };
		
		info.style |= parent ? WS_CHILD : WS_OVERLAPPEDWINDOW;

		info.hwnd = CreateWindowEx(
			0,
			wc.lpszClassName,
			caption,
			info.style,
			left,
			top,
			width,
			height,
			parent,
			NULL,
			NULL,
			NULL
		);

		if (info.hwnd) {
			SetLastError(0);
			const window_id id{ AddToWindows(info) };
			SetWindowLongPtr(info.hwnd, GWLP_USERDATA, (LONG_PTR)id);

			if (callback) {
				SetWindowLongPtr(info.hwnd, 0, (LONG_PTR)callback);
				assert(GetLastError() == 0);
			}

			ShowWindow(info.hwnd, SW_SHOWNORMAL);
			UpdateWindow(info.hwnd);
			
			return Window{ id };
		}

		return { };
	}

	void RemoveWnd(window_id id) {
		WindowInfo& info{ GetInfoFromId(id) };
		DestroyWindow(info.hwnd);
		RemoveFromWindows(id);
	}

	void Window::SetFullscreen(bool is_fullscreen) const {
		assert(IsValid());
		SetWindowFullscreen(_id, is_fullscreen);
	}

	bool Window::IsFullscreen() const {
		assert(IsValid());
		return IsWindowFullscreen(_id);
	}

	void* Window::Handle() const {
		assert(IsValid());
		return GetWindowHandle(_id);
	}

	void Window::SetCaption(const charW* caption) const {
		assert(IsValid());
		SetWindowCaption(_id, caption);
	}

	const math::uvec4 Window::Size() const {
		assert(IsValid());
		return GetWindowSize(_id);
	}

	void Window::Resize(u32 width, u32 height) const {
		assert(IsValid());
		ResizeWindow(_id, width, height);
	}

	const u32 Window::Width() const {
		math::uvec4 s{ Size() };
		return s.z - s.x;
	}

	const u32 Window::Height() const {
		math::uvec4 s{ Size() };
		return s.w - s.y;
	}

	bool Window::IsClosed() const {
		assert(IsValid());
		return IsWindowClosed(_id);
	}
}

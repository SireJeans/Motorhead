#pragma once

#include "Motorhead/Common.h"
#include "Motorhead/Platform/PlatformCommon.h"
#include "Motorhead/MSWindows/MSWinCommon.h"
#include "../Test.h"

using namespace motor;

LRESULT TestWindowProc(HWND	hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class EngineTest : public Test {
public:
	bool Initialize() override {

		platform::WindowInitInfo info[]
		{
			{&TestWindowProc, nullptr, L"Test Window 1", 100, 100, 300, 300},
			{&TestWindowProc, nullptr, L"Test Window 2", 100, 100, 300, 300},
			{&TestWindowProc, nullptr, L"Test Window 3", 100, 100, 300, 300},
			{&TestWindowProc, nullptr, L"Test Window 4", 100, 100, 300, 300},
		};
		static_assert(_countof(info) == _countof(_windows));

		for (u32 i{ 0 }; i < _countof(_windows); ++i) {
			_windows[i] = platform::CreateWnd(&info[i]);
		}
		return true;
	}

	void Run() override {

		
	}

	void Shutdown() override {
		for (u32 i{ 0 }; i < _countof(_windows); ++i) {
			platform::RemoveWnd(_windows[i].GetId());
		}
	}

	static platform::Window _windows[4];

private:

};

platform::Window EngineTest::_windows[4];

LRESULT TestWindowProc(HWND	hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	bool all_closed{ true };

	switch (msg)
	{
	case WM_DESTROY:
		
		for (u32 i{ 0 }; i < _countof(EngineTest::_windows); ++i) {
			if (!EngineTest::_windows[i].IsClosed()) {
				all_closed = false;
			}
		}
		if (all_closed) {
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_SYSCHAR:
		if (wparam == VK_RETURN && (HIWORD(lparam) & KF_ALTDOWN)) {
			platform::Window win{ platform::window_id{(id::id_type)GetWindowLongPtr(hwnd, GWLP_USERDATA)} };
			win.SetFullscreen(!win.IsFullscreen());
		}
		break;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

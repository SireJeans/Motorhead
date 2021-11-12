#define TEST_ENTITY 0
#define TEST_COMPONENT 0
#define TEST_RANDOM 0
#define TEST_HASH 1
#define TEST_STRING 0
#define TEST_WINDOW 0

#if TEST_ENTITY == 1
#include "Engine/TestEntity.h"
#elif TEST_COMPONENT == 1
#include "Engine/TestComponent.h"
#elif TEST_RANDOM == 1
#include "Core/TestRandom.h"
#elif TEST_HASH == 1
#include "Core/TestHash.h"
#elif TEST_STRING == 1
#include "Core/TestString.h"
#elif TEST_WINDOW == 1
#include "Platform/TestWindow.h"
#else
#error One of the test must be enabled
#endif

#include <crtdbg.h>

#ifdef _CONSOLE
int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG


	EngineTest test{};

	if (test.Initialize()) {
		test.Run();
	}

	test.Shutdown();

	return 0;
}
#else
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR, int) 
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	EngineTest test{};

	if (test.Initialize()) {
		MSG msg{};
		bool is_running{ true };

		while (is_running) {

			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);
				is_running &= (msg.message != WM_QUIT);

			}

			test.Run();
		}

	}

	test.Shutdown();

	return 0;
}


#endif

#define TEST_ENTITY 0
#define TEST_COMPONENT 0
#define TEST_RANDOM 0
#define TEST_HASH 0
#define TEST_STRING 0
#define TEST_WINDOW 0
#define TEST_DELEGATE 0
#define TEST_MESSAGEBUS 0
#define TEST_LOGGING 0
#define TEST_PFMEM 1
#define TEST_BITOPS 0

#if TEST_ENTITY
#include "Engine/TestEntity.h"
#elif TEST_COMPONENT
#include "Engine/TestComponent.h"
#elif TEST_RANDOM
#include "Core/TestRandom.h"
#elif TEST_HASH
#include "Core/TestHash.h"
#elif TEST_STRING
#include "Core/TestString.h"
#elif TEST_WINDOW
#include "Platform/TestWindow.h"
#elif TEST_DELEGATE
#include "Core/TestDelegate.h"
#elif TEST_MESSAGEBUS
#include "Core/TestMessageBus.h"
#elif TEST_LOGGING
#include "Core/TestLogging.h"
#elif TEST_PFMEM
#include "Platform/TestPFMem.h"
#elif TEST_BITOPS
#include "Core/TestBitOps.h"
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

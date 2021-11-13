#pragma once

#include "Motorhead/Core/CoreCommon.h"
#include "Motorhead/MSWindows/MSWinCommon.h"
#include "../Test.h"

using namespace motor;

class EngineTest : public Test {
public:
	bool Initialize() override 
	{
		return true;
	}

	void Run() override 
	{
		do {
			void* blockSrc = platform::Alloc(10);
			void* blockDest = platform::Alloc(10);
			MH_GDEBUG("blockSrc={} blockDest={}\n", blockSrc, blockDest);
			platform::Zero(blockSrc, 10);
			platform::Zero(blockDest, 10);
			platform::Set(blockSrc, 'A', 10);
			platform::Copy(blockDest, blockSrc, 10);
			platform::Set(blockSrc, 'B', 10);
			platform::Free(blockSrc);
			platform::Free(blockDest);
			platform::Free(nullptr); 
			PrintResult();
		} while (getchar() != 'q');
	}

	void Shutdown() override 
	{

	}

private:

	void PrintResult() 
	{

	}

};

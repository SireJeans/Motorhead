#pragma once

#include "Motorhead/Core/CoreCommon.h"
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

			mem::SmallBlockPage<6 * 1024>();
			mem::MediumBlockPage<6 * 1024>();

			mem::FastMemManager<32, 32, 128, 256, 4096, platform::DefaultMemApi> fmm;

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

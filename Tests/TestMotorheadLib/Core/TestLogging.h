#pragma once

#include "Motorhead/Core/Logging.h"
#include "../Test.h"

using namespace motor;

MHLOG_DEFINE_STATIC(testlogging, Trace)

MHLOG_DECLARE_EXTERN(testlogging2, Debug)

MHLOG_DEFINE(testlogging2)

class EngineTest : public Test {
public:
	bool Initialize() override 
	{
		return true;
	}

	void Run() override 
	{
		MH_LOG(testlogging, Warning, "Pouet");
		MH_LOG(testlogging, Warning, "Pouet %s", "Caca");

		do {

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

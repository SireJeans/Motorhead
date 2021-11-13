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
		do {
			MH_LOG(testlogging, Warn, "Pouet\n");
			MH_LOG(testlogging, Warn, "Pouet {0}\n", "Caca");
			MH_LOG(testlogging2, Debug, "CHIOTTE\n");
			MH_FATAL(testlogging2, "popo {0}\n", "zobi");
			MH_ERROR(testlogging2, "popo {0}, {1}\n", "zobi0", "zobi1");
			MH_WARN(testlogging2, "popo\n");
			MH_INFO(testlogging2, "popo\n");
			MH_DEBUG(testlogging2, "popo\n");
			MH_TRACE(testlogging2, "popo\n");
			MH_GFATAL("popo {0}\n", "zobi");
			MH_GERROR("popo {0}, {1}\n", "zobi0", "zobi1");
			MH_GWARN("popo\n");
			MH_GINFO("popo\n");
			MH_GDEBUG("popo\n");
			MH_GTRACE("popo\n");

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

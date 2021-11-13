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

			MH_LOG(testlogging, Warn, TXT("Pouet\n"));
			MH_LOG(testlogging, Warn, TXT("Pouet {0}\n"), "Caca");
			MH_LOG(testlogging2, Debug, TXT("CHIOTTE\n"));
			MH_FATAL(testlogging2, TXT("popo {0}\n"), "zobi");
			MH_ERROR(testlogging2, TXT("popo {0}, {1}\n"), "zobi0", "zobi1");
			MH_WARN(testlogging2, TXT("popo\n"));
			MH_INFO(testlogging2, TXT("popo\n"));
			MH_DEBUG(testlogging2, TXT("popo\n"));
			MH_TRACE(testlogging2, TXT("popo\n"));
			MH_GFATAL(TXT("popo {0}\n"), "zobi");
			MH_GERROR(TXT("popo {0}, {1}\n"), "zobi0", "zobi1");
			MH_GWARN(TXT("popo\n"));
			MH_GINFO(TXT("popo\n"));
			MH_GDEBUG(TXT("popo\n"));
			MH_GTRACE(TXT("popo\n"));


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

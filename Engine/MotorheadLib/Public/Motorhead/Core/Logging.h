#pragma once

#include "CoreMinimal.h"
#include "Containers.h"
#include "MotorString.h"

#define MHLOG_LEVEL_NOLOG		0
#define MHLOG_LEVEL_FATAL		1
#define MHLOG_LEVEL_ERROR		2
#define MHLOG_LEVEL_WARNING		3
#define MHLOG_LEVEL_INFO		4
#define MHLOG_LEVEL_DEBUG		5
#define MHLOG_LEVEL_TRACE		6

#if !defined(MHLOG_ACTIVE_VERBO)
#define MHLOG_STATIC_VERBO		MHLOG_VERBO_TRACE
#endif

namespace motor::log {

	enum class Level {
		NoLog = MHLOG_LEVEL_NOLOG,
		Fatal = MHLOG_LEVEL_FATAL,
		Error = MHLOG_LEVEL_ERROR,
		Warning = MHLOG_LEVEL_WARNING,
		Info = MHLOG_LEVEL_INFO,
		Debug = MHLOG_LEVEL_DEBUG,
		Trace = MHLOG_LEVEL_TRACE,
		NumLevel
	};

	class LoggerStatic {
	public:
		LoggerStatic();
		LoggerStatic(const charA* name, Level default_level);

		core::Name& Name() 
		{
			return m_name;
		}

	private:
		core::Name	m_name;
		static core::List<LoggerStatic*> s_loggers;
	};
}

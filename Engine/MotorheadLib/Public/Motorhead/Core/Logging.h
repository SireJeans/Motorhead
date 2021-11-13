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

namespace motor::log {

	enum class Level : u8 {
		NoLog = MHLOG_LEVEL_NOLOG,
		Fatal = MHLOG_LEVEL_FATAL,
		Error = MHLOG_LEVEL_ERROR,
		Warning = MHLOG_LEVEL_WARNING,
		Info = MHLOG_LEVEL_INFO,
		Debug = MHLOG_LEVEL_DEBUG,
		Trace = MHLOG_LEVEL_TRACE,
		NumLevel
	};

	class LoggerBase{
	public:
		LoggerBase();
		LoggerBase(const charA* name, Level default_level);

		const core::Name& Name() const
		{
			return m_name;
		}

		const log::Level Level() const
		{
			return log::Level(m_current_level);
		}

		void SetLevel(log::Level new_level)
		{
			if (new_level != log::Level(m_current_level))
				m_current_level = (u8)new_level;
		}

		template<typename ...Args>
		void Log(log::Level level, const charA* format, Args... args)
		{

		}

		static LoggerBase* Get(const core::Name name);

	private:
		const core::Name				m_name;
		u8								m_current_level;
		const log::Level				m_default_level;
		const log::Level				m_compile_time_level;
		static core::vector<LoggerBase*>	s_loggers;
	};



#define MHLOG_DECLARE_EXTERN(log_name, level)	\
		extern class LoggerBase##log_name : public ::motor::log::LoggerBase							\
		{																							\
		public:																						\
			LoggerBase##log_name() : LoggerBase(#log_name, ::motor::log::Level::level) { }			\
		} log_name;


#define MHLOG_DEFINE(log_name) LoggerBase##log_name log_name;

#define MHLOG_DEFINE_STATIC(log_name, level)														\
		static class LoggerBase##log_name : public ::motor::log::LoggerBase							\
		{																							\
		public:																						\
			LoggerBase##log_name() : LoggerBase(#log_name, ::motor::log::Level::level) { }			\
		} log_name;

#define MH_LOG(log_name, level, format, ...)										\
		{																			\
			log_name.Log(::motor::log::Level::level, format, __VA_ARGS__);			\
		}
}

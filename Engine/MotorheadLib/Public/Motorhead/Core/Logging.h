#pragma once

#include "CoreMinimal.h"

#include "Containers.h"
#include "MotorString.h"
#include "Template.h"

//#include "fmt/format.h"
//#include "fmt/xchar.h"

#define MHLOG_LEVEL_NOLOG		0
#define MHLOG_LEVEL_FATAL		1
#define MHLOG_LEVEL_ERROR		2
#define MHLOG_LEVEL_WARN		3
#define MHLOG_LEVEL_INFO		4
#define MHLOG_LEVEL_DEBUG		5
#define MHLOG_LEVEL_TRACE		6

namespace motor::log {

	enum class Level : u8 {
		NoLog = MHLOG_LEVEL_NOLOG,
		Fatal = MHLOG_LEVEL_FATAL,
		Error = MHLOG_LEVEL_ERROR,
		Warn = MHLOG_LEVEL_WARN,
		Info = MHLOG_LEVEL_INFO,
		Debug = MHLOG_LEVEL_DEBUG,
		Trace = MHLOG_LEVEL_TRACE,
		NumLevel
	};

	const charT* ToString(Level);

	class LoggerBase {
	public:
		LoggerBase();
		LoggerBase(const charT* name, Level default_level);

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
		void Log(log::Level level, const charT* format, Args... args)
		{
			if (m_current_level < (u8)level)
				return;
#ifdef USE_UTF16
			core::wstring s = fmt::format(format, args...);
			std::wcout << s;
#else
			core::string s = fmt::format(format, args...);
			std::cout << s;
#endif

		}

		static LoggerBase* Get(const core::Name name);

	private:
		const core::Name					m_name;
		u8									m_current_level;
		const log::Level					m_default_level;
		const log::Level					m_compile_time_level;
		static core::vector<LoggerBase*>	s_loggers;
	};

}

#define MHLOG_DECLARE_EXTERN(log_name, level)	\
		extern class LoggerBase##log_name : public ::motor::log::LoggerBase							\
		{																							\
		public:																						\
			LoggerBase##log_name() : LoggerBase(TXT(#log_name), ::motor::log::Level::level) { }			\
		} log_name;


#define MHLOG_DEFINE(log_name) LoggerBase##log_name log_name;

#define MHLOG_DEFINE_STATIC(log_name, level)														\
		static class LoggerBase##log_name : public ::motor::log::LoggerBase							\
		{																							\
		public:																						\
			LoggerBase##log_name() : LoggerBase(TXT(#log_name), ::motor::log::Level::level) { }			\
		} log_name;


#define MH_LOG(log_name, level, format, ...)										\
		{																			\
			static_assert(IsArrayOrRefOfType<decltype(TXT(format)), charT>::value, "Formatting string must be a charT array."); \
			static_assert((u8)::motor::log::Level::NumLevel > (u8)::motor::log::Level::level && (u8)::motor::log::Level::level > 0, "Log level must be in range.");	\
			log_name.Log(::motor::log::Level::level, TXT(format), __VA_ARGS__);			\
		}

#define MH_FATAL(log_name, format, ...)		MH_LOG(log_name, Fatal, format, __VA_ARGS__)
#define MH_ERROR(log_name, format, ...)		MH_LOG(log_name, Error, format, __VA_ARGS__)
#define MH_WARN(log_name, format, ...)		MH_LOG(log_name, Warn, format, __VA_ARGS__)
#define MH_INFO(log_name, format, ...)		MH_LOG(log_name, Info, format, __VA_ARGS__)
#define MH_DEBUG(log_name, format, ...)		MH_LOG(log_name, Debug, format, __VA_ARGS__)
#define MH_TRACE(log_name, format, ...)		MH_LOG(log_name, Trace, format, __VA_ARGS__)


MHLOG_DECLARE_EXTERN(Global, Trace)

#define MH_GLOG(level, format, ...)			MH_LOG(Global, level, format, __VA_ARGS__)
#define MH_GFATAL(format, ...)				MH_GLOG(Fatal, format, __VA_ARGS__)
#define MH_GERROR(format, ...)				MH_GLOG(Error, format, __VA_ARGS__)
#define MH_GWARN(format, ...)				MH_GLOG(Warn, format, __VA_ARGS__)
#define MH_GINFO(format, ...)				MH_GLOG(Info, format, __VA_ARGS__)
#define MH_GDEBUG(format, ...)				MH_GLOG(Debug, format, __VA_ARGS__)
#define MH_GTRACE(format, ...)				MH_GLOG(Trace, format, __VA_ARGS__)

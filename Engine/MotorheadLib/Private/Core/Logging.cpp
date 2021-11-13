#include "Motorhead/Core/Logging.h"

namespace motor::log {

	LoggerBase::LoggerBase()
		: m_name("UNNAMED_LOGGER")
		, m_default_level(Level::Debug)
		, m_compile_time_level(log::Level(MHLOG_COMPILE_TIME_LEVEL))
		, m_current_level((u8)m_default_level)
	{
		LoggerBase::s_loggers.push_back(this);
	}

	LoggerBase::LoggerBase(const charA* name, log::Level default_level)
		: m_name(name)
		, m_default_level(default_level)
		, m_compile_time_level(log::Level(MHLOG_COMPILE_TIME_LEVEL))
		, m_current_level((u8)m_default_level)
	{
		LoggerBase::s_loggers.push_back(this);
	}

	LoggerBase* LoggerBase::Get(core::Name name)
	{
		LoggerBase* result = nullptr;

		for (LoggerBase* logger : s_loggers) 
		{
			if (logger->Name().Hash() == name.Hash()) 
			{
				result = logger;
			}
		}

		return result;
	}

	core::vector<LoggerBase*> LoggerBase::s_loggers{ };

	const charT* ToString(Level level)
	{
		switch (level)
		{
		case Level::NoLog:
			return TXT("NoLog");
		case Level::Fatal:
			return TXT("Fatal");
		case Level::Error:
			return TXT("Error");
		case Level::Warn:
			return TXT("Warning");
		case Level::Info:
			return TXT("Info");
		case Level::Debug:
			return TXT("Debug");
		case Level::Trace:
			return TXT("Trace");
		}
		return TXT("UnknownLevel");
	}
}

MHLOG_DEFINE(Global)

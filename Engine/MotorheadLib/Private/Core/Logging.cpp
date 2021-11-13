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
}

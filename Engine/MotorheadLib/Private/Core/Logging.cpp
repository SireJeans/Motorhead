#include "Motorhead/Core/Logging.h"

namespace motor::log {

	LoggerStatic::LoggerStatic()
		: m_name("UNNAMED_LOGGER")
	{
		LoggerStatic::s_loggers.push_back(this);
	}

	LoggerStatic::LoggerStatic(const charA* name, Level default_level)
		: m_name(name)
	{
		LoggerStatic::s_loggers.push_back(this);
	}

	core::List<LoggerStatic*> LoggerStatic::s_loggers;
}

#include "Logging/Logging.hpp"
#include <cstdio>
#include <iostream>

#define XNELO_LOGGING_BUFFER_SIZE 1024;

namespace XNELO
{
	namespace LOGGING
	{
		inline const char * _GET_LOGGING_LEVEL_STRING(int level)
		{
			switch (level)
			{
			case XNELO_LOGGING_EMERGENCY:
				return "EMERGENCY";
			case XNELO_LOGGING_ALERT:
				return "ALERT";
			case XNELO_LOGGING_CRITICAL:
				return "CRITICAL";
			case XNELO_LOGGING_ERROR:
				return "ERROR";
			case XNELO_LOGGING_WARNING:
				return "WARNING";
			case XNELO_LOGGING_NOTICE:
				return "NOTICE";
			case XNELO_LOGGING_INFO:
			//case XNELO_LOGGING_INFORMATIONAL:
				return "INFO";
			case XNELO_LOGGING_DEBUG:
			//case XNELO_LOGGING_DEBUG1:
				return "DEBUG1";
			case XNELO_LOGGING_DEBUG2:
				return "DEBUG2";
			case XNELO_LOGGING_DEBUG3:
				return "DEBUG3";
			case XNELO_LOGGING_DEBUG4:
				return "DEBUG4";
			default:
				return "DEBUG>4";
			}
		}

		char * _LOG_INTERNAL(const char * message, va_list args)
		{
			size_t size = XNELO_LOGGING_BUFFER_SIZE;

			int charsPrinted;
			char * buffer = NULL;

			while (true)
			{
				buffer = new char[size];
				charsPrinted = vsnprintf(buffer, size, message, args);

				if ((charsPrinted != -1) && (charsPrinted < size))
					break;

				delete buffer;
				size = size * 2;
			}

			return buffer;
		}

		void Log(int level, const char * message, ...)
		{
			char * buffer = NULL;

			va_list args;
			va_start(args, message);

			buffer = _LOG_INTERNAL(message, args);//vprintf(message, args);

			va_end(args);

			if (buffer != NULL)
			{
				std::cout << "[" << _GET_LOGGING_LEVEL_STRING(level) << "]: " << buffer << std::endl;

				delete buffer;
			}
		}
	}//namespace LOGGING
}//namespace XNELO

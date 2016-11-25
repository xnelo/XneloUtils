#ifndef ___XNELO_LOGGING_LOGGING__HPP__11_10_2016___
#define ___XNELO_LOGGING_LOGGING__HPP__11_10_2016___

#include <stdarg.h>

#define XNELO_LOGGING_EMERGENCY 0
#define XNELO_LOGGING_ALERT 1
#define XNELO_LOGGING_CRITICAL 2
#define XNELO_LOGGING_ERROR 3
#define XNELO_LOGGING_WARNING 4
#define XNELO_LOGGING_NOTICE 5
#define XNELO_LOGGING_INFO 6
#define XNELO_LOGGING_INFORMATIONAL XNELO_LOGGING_INFO
#define XNELO_LOGGING_DEBUG 7
#define XNELO_LOGGING_DEBUG1 XNELO_LOGGING_DEBUG
#define XNELO_LOGGING_DEBUG2 8
#define XNELO_LOGGING_DEBUG3 9
#define XNELO_LOGGING_DEBUG4 10

#define XNELO_LOG(level, message, ...) XNELO::LOGGING::Log(level, message, __VA_ARGS__);
#define XNELO_LOG_EMERGENCY(message, ...) XNELO_LOG(XNELO_LOGGING_EMERGENCY, message, __VA_ARGS__);
#define XNELO_LOG_ALERT(message, ...) XNELO_LOG(XNELO_LOGGING_ALERT, message, __VA_ARGS__);
#define XNELO_LOG_CRITICAL(message, ...) XNELO_LOG(XNELO_LOGGING_CRITICAL, message, __VA_ARGS__);
#define XNELO_LOG_ERROR(message, ...) XNELO_LOG(XNELO_LOGGING_ERROR, message, __VA_ARGS__);
#define XNELO_LOG_WARNING(message, ...) XNELO_LOG(XNELO_LOGGING_WARNING, message, __VA_ARGS__);
#define XNELO_LOG_NOTICE(message, ...) XNELO_LOG(XNELO_LOGGING_NOTICE, message, __VA_ARGS__);
#define XNELO_LOG_INFO(message, ...) XNELO_LOG(XNELO_LOGGING_INFO, message, __VA_ARGS__);
#define XNELO_LOG_INFORMATIONAL(message, ...) XNELO_LOG(XNELO_LOGGING_INFORMATIONAL, message, __VA_ARGS__);
#define XNELO_LOG_DEBUG(message, ...) XNELO_LOG(XNELO_LOGGING_DEBUG, message, __VA_ARGS__);
#define XNELO_LOG_DEBUG1(message, ...) XNELO_LOG(XNELO_LOGGING_DEBUG1, message, __VA_ARGS__);
#define XNELO_LOG_DEBUG2(message, ...) XNELO_LOG(XNELO_LOGGING_DEBUG2, message, __VA_ARGS__);
#define XNELO_LOG_DEBUG3(message, ...) XNELO_LOG(XNELO_LOGGING_DEBUG3, message, __VA_ARGS__);
#define XNELO_LOG_DEBUG4(message, ...) XNELO_LOG(XNELO_LOGGING_DEBUG4, message, __VA_ARGS__);


namespace XNELO
{
	namespace LOGGING
	{
		void Log(int level, const char * message, ...);
	} //namespace LOGGING
} //namespace XNELO

#endif //___XNELO_LOGGING_LOGGING__HPP__11_10_2016___

/**
* @file Logging.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Defines a logger for XneloUtils library. This defines macros to allow for turning off logging at
* compile time.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2016 Spencer Hoffa
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the
* use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
*		1. The origin of this software must not be misrepresented; you must not
*		claim that you wrote the original software. If you use this software in
*		a product, an acknowledgment in the product documentation would be
*		appreciated but is not required.
*
*		2. Altered source versions must be plainly marked as such, and must not
*		be misrepresented as being the original software.
*
*		3. This notice may not be removed or altered from any source
*		distribution.
*
* This liscense can also be found at: http://opensource.org/licenses/Zlib
*/

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

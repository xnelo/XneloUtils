/**
* @file Logging.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Implementation of the logging code.
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

#include "XneloUtils/Logging/Logging.hpp"
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

/**
* @file SystemFunction.hpp
* @author Spencer Hoffa
*
* @copyright 2017 Spencer Hoffa
*
* Common system functions.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2017 Spencer Hoffa
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

#ifndef ___XNELOUTILS_SYSTEMFUNCTIONS_HPP__3_24_2017___
#define ___XNELOUTILS_SYSTEMFUNCTIONS_HPP__3_24_2017___

#include "BasicTypes.hpp"
#include "../Config.hpp"
#include <string>
#include <vector>

#if PLATFORM == XNELO_PLATFORM_WINDOWS

#include <Windows.h>

#elif PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_UNIX

#include <unistd.h>

#endif

namespace XNELO
{
	namespace CORE
	{
		typedef LARGE_INTEGER LargeInt;
		/**
		* Sleep the threads execution for certain number of milliseconds. This calls the underlying
		* system sleep command. Windows: Sleep() Unix: usleep()
		*
		* @param milliseconds An integer with the number of seconds to sleep the process.
		*/
		XNELO_API void XneloSleep(XNELO::CORE::uint32 milliseconds);

		XNELO_API std::string GetExtension(std::string filePath);
		XNELO_API std::vector<std::string> GetFiles(std::string directory, bool recursive);
		XNELO_API std::vector<std::string> GetFiles(const char * directory, bool recursive);
		XNELO_API std::vector<std::string> GetFilesWithExtension(std::string directory, bool recursive, std::string extension);
		XNELO_API std::vector<std::string> GetFilesWithExtension(const char * directory, bool recursive, const char * extension);

		XNELO_API LargeInt GetFrequency();
		XNELO_API LargeInt GetTicks();
		XNELO_API double GetTime();
		XNELO_API double GetTime(LargeInt frequency);
	}
}

inline void XNELO::CORE::XneloSleep(XNELO::CORE::uint32 milliseconds)
{
#if PLATFORM == XNELO_PLATFORM_WINDOWS
	Sleep((DWORD)milliseconds);
#elif PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_UNIX
	usleepf(milliseconds * 1000);
#endif
}

inline std::vector<std::string> XNELO::CORE::GetFiles(std::string directory, bool recursive)
{
	return GetFiles(directory.c_str(), recursive);
}

inline std::vector<std::string> XNELO::CORE::GetFilesWithExtension(std::string directory, bool recursive, std::string extension)
{
	return GetFilesWithExtension(directory.c_str(), recursive, extension.c_str());
}

inline XNELO::CORE::LargeInt XNELO::CORE::GetFrequency()
{
	LargeInt frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

inline XNELO::CORE::LargeInt XNELO::CORE::GetTicks()
{
	LargeInt ticks;
	QueryPerformanceCounter(&ticks);
	return ticks;
}

inline double XNELO::CORE::GetTime()
{
	//LargeInt frequency = GetFrequency();
	//LargeInt ticks = GetTicks();
	//return (ticks.QuadPart * 1000.0) / frequency.QuadPart;
	return GetTime(GetFrequency());
}

inline double XNELO::CORE::GetTime(XNELO::CORE::LargeInt frequency)
{
	return (GetTicks().QuadPart * 1000.0) / frequency.QuadPart;
}

#endif //___XNELOUTILS_SYSTEMFUNCTIONS_HPP__3_24_2017___

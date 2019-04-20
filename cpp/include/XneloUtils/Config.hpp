/// <file> Config.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> A file to determine environment and configurations. </summary>
/// 
/// <copyright> Copyright (c) 2019 </copyright>
/// 
/// <license>
/// The zlib/libpng License
/// 
/// Copyright (c) 2019 Spencer Hoffa
/// 
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
/// 
/// Permission is granted to anyone to use this software for any purpose,
/// including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions:
/// 
/// 		1. The origin of this software must not be misrepresented; you must not
/// 		claim that you wrote the original software. If you use this software in
/// 		a product, an acknowledgment in the product documentation would be
/// 		appreciated but is not required.
/// 
/// 		2. Altered source versions must be plainly marked as such, and must not
/// 		be misrepresented as being the original software.
/// 
/// 		3. This notice may not be removed or altered from any source
/// 		distribution.
/// 
/// This liscense can also be found at: http://opensource.org/licenses/Zlib
/// </license>

#ifndef ___XNELO_CONFIG__HPP___10_2016___
#define ___XNELO_CONFIG__HPP___10_2016___

#define XNELO_PLATFORM_WINDOWS 1
#define XNELO_PLATFORM_LINUX 2
#define XNELO_PLATFORM_MAC 3

#define XNELO_ENVIRONMENT32 32
#define XNELO_ENVIRONMENT64 64

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(WIN64) || defined(_WIN64) || defined(__WIN64)
	#define PLATFORM XNELO_PLATFORM_WINDOWS

	#if defined(_WIN64) || defined(__WIN64)
		#define ENVIRONMENT XNELO_ENVIRONMENT64
	#else
		#define ENVIRONMENT XNELO_ENVIRONMENT32
	#endif

	//Define win32 lean and mean
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#endif // _WIN32

#elif defined(__APPLE__)
	#define PLATFORM XNELO_PLATFORM_MAC
#else
	#define PLATFORM XNELO_PLATFORM_LINUX

	#if defined(__LP64__) || defined(_LP64)
		#define ENVIRONMENT XNELO_ENVIRONMENT64
	#else
		#define ENVIRONMENT XNELO_ENVIRONMENT32
	#endif
#endif

// To build Xnelo UTILS as a static library, you must define XNELO_UTILS_STATIC_LIB 
// in both the Xnelo Testing library, *and* in the user application, before 
#if PLATFORM == XNELO_PLATFORM_WINDOWS && defined(XNELO_UTILS_DLL) 
	//Using or building the DLL version
	#ifdef XNELO_UTILS_DLL_EXPORT
		//Building DLL
		#define XNELO_API __declspec(dllexport)
	#else
		//Using DLL
		#define XNELO_API __declspec(dllimport)
	#endif
#else
	//Static library (DEFAULT)
	#define XNELO_API
#endif

//Define NULL if it's not defined.
#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif //!NULL

#endif //___XNELO_CONFIG__HPP___10_2016___

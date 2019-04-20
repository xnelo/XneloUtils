/// <file> NetworkCore.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> Includes information for all Xnelo network classes. </summary>
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

#ifndef ___XNELO_NETWORK_NETWORKCORE_HPP__7_16_2017___
#define ___XNELO_NETWORK_NETWORKCORE_HPP__7_16_2017___

#include "../Config.hpp"

#if PLATFORM == XNELO_PLATFORM_WINDOWS

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "wsock32.lib")

#elif PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_LINUX

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#endif

namespace XNELO
{
	namespace NETWORK
	{
		/**
		* Any initialization code to execute before any networking sockets are created.
		*
		* @return A boolean value, true if initialization succeded and false if an error occured.
		*/
		bool InitializeNetworking();

		/**
		* Shutdown any networking.
		*/
		void ShutdownNetworking();
	}//end namespace network
}//end namespace xnelo

#endif // !___XNELO_NETWORK_NETWORKCORE_HPP__7_16_2017___


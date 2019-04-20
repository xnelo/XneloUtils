/// <file> NetworkCore.cpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary>  </summary>
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

#include "XneloUtils/Network/NetworkCore.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		bool networking_initialized = false;

		bool InitializeNetworking()
		{
			if (networking_initialized)
				return true;

		#if PLATFORM == XNELO_PLATFORM_WINDOWS
			WSADATA WsaData;

			if (WSAStartup(MAKEWORD(2, 2), &WsaData) != NO_ERROR)
			{
				networking_initialized = false;
				return false;
			}

			networking_initialized = true;
		#else
			networking_initialized = true;
		#endif

			return networking_initialized;
		}

		void ShutdownNetworking()
		{
		#if PLATFORM == XNELO_PLATFORM_WINDOWS
			WSACleanup();
		#endif

			networking_initialized = false;
		}
	}//end namespace network
}//end namespace xnelo

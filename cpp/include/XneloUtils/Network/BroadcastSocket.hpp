/// <file> BroadcastSocket.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> Defines a socket that can be used to broadcast data. </summary>
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

#ifndef ___XNELOUTILS_NETWORK_BROADCASTSOCKET_HPP__3_24_2017___
#define ___XNELOUTILS_NETWORK_BROADCASTSOCKET_HPP__3_24_2017___

#include "UDPSocket.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		class BroadcastSocket: public UDPSocket
		{
		public:
			#pragma region Constructor / Destructor
			XNELO_API BroadcastSocket();
			XNELO_API BroadcastSocket(unsigned short port);
			XNELO_API virtual ~BroadcastSocket();
			#pragma endregion

			#pragma region Overrides
			XNELO_API bool OpenSocket();
			#pragma endregion

			XNELO_API int BroadcastAll(XNELO::CORE::uint16 portNumber, void * buffer, int bufferSize);
		};
	} //end namespace NETWORK
}//end namespace XNELO

#endif // ___XNELOUTILS_NETWORK_BROADCASTSOCKET_HPP__3_24_2017___


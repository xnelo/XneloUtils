/// <file> BroadcastSocket.cpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> Implementation of BroadcastSocket functions. </summary>
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

#include "XneloUtils/Network/BroadcastSocket.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		#pragma region Constructor / Destructor
		BroadcastSocket::BroadcastSocket() : UDPSocket()
		{}

		BroadcastSocket::BroadcastSocket(unsigned short port) : UDPSocket(port)
		{}

		BroadcastSocket::~BroadcastSocket() 
		{}
		#pragma endregion

		#pragma region Overrides
		bool BroadcastSocket::OpenSocket()
		{
			if (!UDPSocket::OpenSocket())
			{
				//error should already be set so just return false
				return false;
			}

			//Set the socket to broadcast
			int broadcastEnabled = 1;
			int returnValue = setsockopt(_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcastEnabled, sizeof(broadcastEnabled));

			if (returnValue != 0)
			{
				SetError(XNELO::ERRORS::SOCKET_FAILED_TO_ENABLE_BROADCAST, "Socket Failed to enable broadcast");
				return false;
			}

			SetError(XNELO::ERRORS::OK, "OK");
			return true;
		}
		#pragma endregion

		int BroadcastSocket::BroadcastAll(XNELO::CORE::uint16 portNumber, void * buffer, int bufferSize)
		{
			Address broadcastAddress(255, 255, 255, 255, portNumber);

			return SendData(broadcastAddress, buffer, bufferSize);
		}

	}//end namespace NETWORK
}//end namespace XNELO
/**
* @file UDPSocket.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Implementation of the UDPSocket class.
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

#include "XneloUtils/Network/UDPSocket.hpp"
#include "XneloUtils/Logging/Logging.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		UDPSocket::UDPSocket(): XneloSocket()
		{}

		UDPSocket::UDPSocket(unsigned short port) : XneloSocket(port)
		{}

		UDPSocket::~UDPSocket()
		{}

		bool UDPSocket::OpenSocket()
		{
			_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			if (_socket <= 0)
			{
				XNELO_LOG_ERROR("UDPSocket(0x%x) -- Error opening socket", this);
				SetError(XNELO::ERRORS::FAILED_TO_CREATE_SOCKET, "Error opening socket.");
				return false;
			}

			sockaddr_in address;
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(_port);

			if (bind(_socket, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
			{
				XNELO_LOG_ERROR("UDPSocket(0x%x) -- Error binding socket", this);
				SetError(XNELO::ERRORS::FAILED_TO_CREATE_SOCKET, "Error binding socket");
				CloseSocket();
				return false;
			}

			//set as non-blocking
#if PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_LINUX
			int nonBlocking = 1;
			if (fcntl(_socket, F_SETFL, O_NONBLOCK, nonblocking) == -1)
			{
				XNELO_LOG_ERROR("UDPSocket(0x%x) -- Error Setting socket to non-blocking", this);
				SetError(XNELO::ERRORS::FAILED_TO_CREATE_SOCKET, "Error Setting socket to non-blocking");
				CloseSocket();
				return false;
			}
#elif PLATFORM == XNELO_PLATFORM_WINDOWS
			DWORD nonBlocking = 1;
			if (ioctlsocket(_socket, FIONBIO, &nonBlocking) != 0)
			{
				
				XNELO_LOG_ERROR("UDPSocket(0x%x) -- Error Setting socket to non-blocking", this);
				SetError(XNELO::ERRORS::FAILED_TO_CREATE_SOCKET, "Error Setting socket to non-blocking");
				CloseSocket();
				return false;
			}
#else
			XNELO_LOG_ERROR("UDPSocket(0x%x) -- Platform is not recognized nor supported.", this);
			SetError(XNELO::ERRORS::PLATFORM_NOT_SUPPORTED, "Platform is not recognized nor supported.");
			CloseSocket();
			return false;
#endif

			SetError(XNELO::ERRORS::OK, "OK");
			return true;
		}

		int UDPSocket::ReceiveData(Address & sender, void * data, int size)
		{
			if (size <= 0)
			{
				XNELO_LOG_WARNING("UDPSocket(0x%x) -- %d is not a valid value for the size argument.", this, size);
				SetError(XNELO::ERRORS::SOCKET_FAILED_TO_RECEIVE_DATA, "Invalid Size input");
				return -1;
			}
			else if (data == NULL)
			{
				XNELO_LOG_WARNING("UDPSocket(0x%x) -- data argument cannot be NULL.", this);
				SetError(XNELO::ERRORS::SOCKET_FAILED_TO_RECEIVE_DATA, "data argument cannot be NULL");
				return -1;
			}

#if PLATFORM == XNELO_PLATFORM_WINDOWS
			typedef int socklen_t;
#endif

			sockaddr_in from;
			socklen_t fromLength = sizeof(from);

			int bytesReceived = recvfrom(_socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

			if (bytesReceived <= 0)
			{
				XNELO_LOG_DEBUG("UDPSocket(0x%x) -- no bytes recieved", this);
				return 0;
			}

			sender.SetAddress(from.sin_addr.s_addr);
			sender.SetAddressPort(ntohs(from.sin_port));

			return bytesReceived;
		}

		int UDPSocket::SendData(Address & address, void * buffer, int bufferSize)
		{
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = address.GetAddress();
			addr.sin_port = htons(address.GetPort());

			int sentBytes;
			sentBytes = sendto(_socket, (const char*)buffer, bufferSize, 0, (sockaddr*)&addr, sizeof(sockaddr_in));

			if (sentBytes != bufferSize)
			{
				XNELO_LOG_ERROR("UDPSocket(0x%x) -- Failed to send entire packet", this);
				SetError(XNELO::ERRORS::SOCKET_FAILED_TO_SEND_DATA, "Failed to send entire packet");
				return -1;
			}

			SetError(XNELO::ERRORS::OK, "OK");
			return sentBytes;
		}
	}//end namespace NETWORK
} //end namespace XNELO
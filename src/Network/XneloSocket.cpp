/**
* @file XneloSocket.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Implementation of the XneloSocket base class.
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

#include "XneloUtils/Network/XneloSocket.hpp"
#include "XneloUtils/Logging/Logging.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		XneloSocket::XneloSocket(): XNELO::CORE::Fallible(), _socket(0), _port(0)
		{
			XNELO_LOG_DEBUG("XneloSocket(0x%x): Initializing", this);
		}

		XneloSocket::XneloSocket(unsigned short port): XNELO::CORE::Fallible(), _socket(0), _port(0)
		{
			XNELO_LOG_DEBUG("XneloSocket(0x%x): Initializing", this);
			SetPortNumber(port);
		}

		XneloSocket::~XneloSocket()
		{
			XNELO_LOG_DEBUG("XneloSocket(0x%x): Destructing", this);
			CloseSocket();
		}

		void XneloSocket::CloseSocket()
		{
			if (_socket <= 0)
				return;

#if PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_LINUX
			close(_socket);
#elif PLATFORM == XNELO_PLATFORM_WINDOWS
			closesocket(_socket);
#else
			XNELO_LOG_NOTICE("UDPSocket(0x%x) -- Platform is not recognized. Defaulting to unix type", this);
			close(_socket);
#endif
			_socket = 0;
		}

		void XneloSocket::SetPortNumber(unsigned short port)
		{
			_port = port;
		}
	}//end namespace NETWORK
}// end namespace XNELO
/**
* @file UDPSocket.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Defines a UDPSocket class.
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

#ifndef ___XNELO_NETWORK_UDPSOCKET__HPP__11_10_2016___
#define ___XNELO_NETWORK_UDPSOCKET__HPP__11_10_2016___

#include "Network.hpp"
#include "XneloSocket.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		class UDPSocket : public XneloSocket
		{
		public:
			XNELO_API UDPSocket();
			XNELO_API UDPSocket(unsigned short port);
			XNELO_API virtual ~UDPSocket();

			XNELO_API bool OpenSocket();
			XNELO_API bool OpenSocket(unsigned short port);

			XNELO_API virtual int ReceiveData(Address & sender, void * data, int size);

			XNELO_API virtual int SendData(Address & address, void * buffer, int bufferSize);
		};
	} //end namespace NETWORK
} // end namespace XNELO

inline bool XNELO::NETWORK::UDPSocket::OpenSocket(unsigned short port)
{
	SetPortNumber(port);
	return OpenSocket();
}

#endif //___XNELO_NETWORK_UDPSOCKET__HPP__11_10_2016___

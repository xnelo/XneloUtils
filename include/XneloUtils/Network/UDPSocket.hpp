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

#include "NetworkCore.hpp"
#include "XneloSocket.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		class UDPSocket : public XneloSocket
		{
		public:
			/**
			* Constructor.
			*/
			XNELO_API UDPSocket();

			/**
			* Constructor with a port number.
			*
			* @param port An unsigned short number of the port the socket communicates on.
			*/
			XNELO_API UDPSocket(unsigned short port);

			/**
			* Destructor.
			*/
			XNELO_API virtual ~UDPSocket();

			/**
			* Opens the socket on the port specified. After this function finishes then the socket
			* will be ready to use for communication.
			*
			* @param port An unsigned short number for the port to connect to. If the port is 
			* passed in then it will override any ports previously set.
			*
			* @return A boolean value is returned. If true is returned then the socket is opened.
			*/
			XNELO_API bool OpenSocket();
			XNELO_API bool OpenSocket(unsigned short port);

			/**
			* Recieve data from the socket.
			*
			* @param sender A reference to an Address object. This object will be filled with the 
			* sender IP information.
			* @param data A void pointer to a chunck of memory to copy information received into.
			* @param size An integer with the size of the buffer passed into the data parameter.
			*
			* @return An integer with the amount of data actually copied.
			*/
			XNELO_API virtual int ReceiveData(Address & sender, void * data, int size);

			/**
			* Send data to a specific address.
			*
			* @param address A reference to an Address object. This object contains the address of
			* where to send the data.
			* @param buffer A void pointer to a chunck of data to send.
			* @param bufferSize An integer with the size of the data that must be sent.
			*
			* @return Returns an integer with the amount of data that was actually sent.
			*/
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

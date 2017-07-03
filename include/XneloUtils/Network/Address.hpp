/**
* @file Address.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Defines a class that holds IPv4 information.
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

#ifndef ___XNELO_NETWORK_ADDRESS__HPP__10_5_2016___
#define ___XNELO_NETWORK_ADDRESS__HPP__10_5_2016___

#include "Network.hpp"
#include "../Core/BasicTypes.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		class Address
		{
		private:
			XNELO::CORE::uint32 _address;
			XNELO::CORE::uint16 _port;
		public:
			XNELO_API static Address GetCurrentIPAddress();

			/**
			* Constructor
			*/
			XNELO_API Address();

			/**
			* Constructor. This one will set the IP address. The parameters corrospond to the parts
			* of the ip address (format: a.b.c.d).
			*
			* @param a An unsigned integer with 8 bits that define the first part of an IPv4 
			* address.
			* @param b An unsigned integer with 8 bits that define the second part of an IPv4
			* address.
			* @param c An unsigned integer with 8 bits that define the third part of an IPv4
			* address.
			* @param d An unsigned integer with 8 bits that define the fourth part of an IPv4
			* address.
			* @param port An unsigned integer with 16 bits that define the port of an IPv4 address.
			*/
			XNELO_API Address(XNELO::CORE::uint8 a, 
							  XNELO::CORE::uint8 b, 
							  XNELO::CORE::uint8 c, 
				              XNELO::CORE::uint8 d,
							  XNELO::CORE::uint16 port);

			/**
			* Copy Constructor.
			*/
			XNELO_API Address(const Address & other);

			/**
			* Destructor.
			*/
			XNELO_API ~Address();

			/**
			* Assignment operator.
			*/
			XNELO_API Address & operator=(const Address & other);

			/**
			* Get the 32 bit unsigned integer version of the address.
			*
			* @return An 32 bit unsigned integer with the address stored in it.
			*/
			XNELO_API XNELO::CORE::uint32 GetAddress() const;

			/**
			* Get the first part of the IPv4 address.
			*
			* @return An integer with the first part of the ip address.
			*/
			XNELO_API int GetA();

			/**
			* Get the second part of the IPv4 address.
			*
			* @return An integer with the second part of the ip address.
			*/
			XNELO_API int GetB();

			/**
			* Get the third part of the IPv4 address.
			*
			* @return An integer with the thrid part of the ip address.
			*/
			XNELO_API int GetC();

			/**
			* Get the fourth part of the IPv4 address.
			*
			* @return An integer with the fourth part of the ip address.
			*/
			XNELO_API int GetD();

			/**
			* Get the first part of the IPv4 address.
			*
			* @return An integer with the first part of the ip address.
			*/
			XNELO_API XNELO::CORE::uint16 GetPort() const;

			/**
			* Set the IPv4 address for this class.
			*
			* @param a An unsigned integer with 8 bits that define the first part of an IPv4 
			* address.
			* @param b An unsigned integer with 8 bits that define the second part of an IPv4
			* address.
			* @param c An unsigned integer with 8 bits that define the third part of an IPv4
			* address.
			* @param d An unsigned integer with 8 bits that define the fourth part of an IPv4
			* address.
			* @param port An unsigned integer with 16 bits that define the port of an IPv4 address.
			*/
			XNELO_API void SetAddress(XNELO::CORE::uint8 a,
									  XNELO::CORE::uint8 b,
									  XNELO::CORE::uint8 c,
									  XNELO::CORE::uint8 d);

			/**
			* Set the IPv4 address using the uint32 format.
			*
			* @param address An unsigned integer 32bit with an IPv4 address.
			*/
			XNELO_API void SetAddress(XNELO::CORE::uint32 address);

			/**
			* Set the port number of the address.
			*
			* @param port An unsigned integer 16bit with the port number.
			*/
			XNELO_API void SetAddressPort(XNELO::CORE::uint16 port);
		private:
			XNELO_API int _GetAddressPart(XNELO::CORE::uint8 bitsToShift);
			XNELO_API void _CopyData(const Address & other);
		};
	}//end namespace XNELO
}//end namespace XNELO

inline XNELO::NETWORK::Address::Address(): _address(0), _port(0)
{}

inline XNELO::NETWORK::Address::Address(XNELO::CORE::uint8 a,
										XNELO::CORE::uint8 b,
										XNELO::CORE::uint8 c,
										XNELO::CORE::uint8 d,
										XNELO::CORE::uint16 port) : _address(0), _port(0)
{
	SetAddress(a, b, c, d);
	SetAddressPort(port);
}

inline XNELO::NETWORK::Address::Address(const Address & other)
{
	_CopyData(other);
}

inline XNELO::NETWORK::Address::~Address()
{
	_address = 0;
	_port = 0;
}

inline XNELO::NETWORK::Address & XNELO::NETWORK::Address::operator=(const Address & other)
{
	_CopyData(other);
	return *this;
}

inline XNELO::CORE::uint32 XNELO::NETWORK::Address::GetAddress() const
{
	return _address;
}

inline XNELO::CORE::uint16 XNELO::NETWORK::Address::GetPort() const
{
	return _port;
}

inline void XNELO::NETWORK::Address::SetAddress(XNELO::CORE::uint32 address)
{
	_address = address;
}

inline void XNELO::NETWORK::Address::SetAddressPort(XNELO::CORE::uint16 port)
{
	_port = port;
}

inline int XNELO::NETWORK::Address::_GetAddressPart(XNELO::CORE::uint8 bitsToShift)
{
	const XNELO::CORE::uint8 mask = 255; // 1111 1111
	return (int)(ntohl(_address) >> bitsToShift) & mask;
}

inline void XNELO::NETWORK::Address::_CopyData(const XNELO::NETWORK::Address & other)
{
	if (this != &other)
	{
		_address = other._address;
		_port = other._port;
	}
}

inline bool operator==(const XNELO::NETWORK::Address & lhs, const XNELO::NETWORK::Address & rhs)
{
	return ((lhs.GetAddress() == rhs.GetAddress()) && (lhs.GetPort() == rhs.GetPort()));
}

inline bool operator!=(const XNELO::NETWORK::Address & lhs, const XNELO::NETWORK::Address & rhs)
{
	return !(lhs == rhs);
}

#endif //___XNELO_NETWORK_ADDRESS__HPP__10_5_2016___

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
			XNELO_API Address();
			XNELO_API Address(XNELO::CORE::uint8 a, 
							  XNELO::CORE::uint8 b, 
							  XNELO::CORE::uint8 c, 
				              XNELO::CORE::uint8 d,
							  XNELO::CORE::uint16 port);
			XNELO_API Address(const Address & other);
			XNELO_API ~Address();

			XNELO_API Address & operator=(const Address & other);

			XNELO_API XNELO::CORE::uint32 GetAddress();
			XNELO_API int GetA();
			XNELO_API int GetB();
			XNELO_API int GetC();
			XNELO_API int GetD();
			XNELO_API XNELO::CORE::uint16 GetPort();

			XNELO_API void SetAddress(XNELO::CORE::uint8 a,
									  XNELO::CORE::uint8 b,
									  XNELO::CORE::uint8 c,
									  XNELO::CORE::uint8 d);
			XNELO_API void SetAddress(XNELO::CORE::uint32 address);
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

inline XNELO::CORE::uint32 XNELO::NETWORK::Address::GetAddress()
{
	return _address;
}

inline XNELO::CORE::uint16 XNELO::NETWORK::Address::GetPort()
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

#endif //___XNELO_NETWORK_ADDRESS__HPP__10_5_2016___

/**
* @file Address.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Implementation of the Address class.
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

#include "XneloUtils/Network/Address.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		void Address::SetAddress(XNELO::CORE::uint8 a,
								 XNELO::CORE::uint8 b,
								 XNELO::CORE::uint8 c,
								 XNELO::CORE::uint8 d)
		{
			_address = (a << 24) | (b << 16) | (c << 8) | (d);
			_address = htonl(_address);
		}

		int Address::GetA()
		{
			return _GetAddressPart(24);
		}

		int Address::GetB()
		{
			return _GetAddressPart(16);
		}

		int Address::GetC()
		{
			return _GetAddressPart(8);
		}

		int Address::GetD()
		{
			return _GetAddressPart(0);
		}
	}// end namespace NETWORK
} //end namespace XNELO

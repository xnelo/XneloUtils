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
#include "XneloUtils/Logging/Logging.hpp"
#include <stdlib.h>

#if PLATFORM == XNELO_PLATFORM_WINDOWS
#include <IPHlpApi.h>
#include <WS2tcpip.h>
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")
#elif PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_LINUX

#endif


#define KB(x) ((size_t) (x) << 10)
#define MB(x) ((size_t) (x) << 20)

namespace XNELO
{
	namespace NETWORK
	{
		Address Address::GetCurrentIPAddress()
		{
			/*
			IP_ADAPTER_ADDRESSES* adapterAddresses(NULL);
			IP_ADAPTER_ADDRESSES* adapter(NULL);

			DWORD adapterAddressBufferSize = KB(16);
			
			for (int attempts = 0; attempts < 3; ++attempts)
			{
				adapterAddresses = (IP_ADAPTER_ADDRESSES*)malloc(adapterAddressBufferSize);

				DWORD error = GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_DNS_SERVER, NULL, adapterAddresses, &adapterAddressBufferSize);

				if (error == ERROR_SUCCESS)
				{
					break;
				}
				else if (error == ERROR_BUFFER_OVERFLOW)
				{
					free(adapterAddresses);
					adapterAddresses = NULL;

					adapterAddressBufferSize *= 2;
				}
				else
				{
					//unexpected error code
					free(adapterAddresses);
					adapterAddresses = NULL;
				}
			}

			// Iterate through all of the adapters
			for (adapter = adapterAddresses; NULL != adapter; adapter = adapter->Next)
			{
				// Skip loopback adapters
				if (IF_TYPE_SOFTWARE_LOOPBACK == adapter->IfType)
				{
					continue;
				}

				// Parse all IPv4 and IPv6 addresses
				for (
					IP_ADAPTER_UNICAST_ADDRESS* address = adapter->FirstUnicastAddress;
					NULL != address;
					address = address->Next)
				{
					auto family = address->Address.lpSockaddr->sa_family;
					if (AF_INET == family)
					{
						// IPv4
						SOCKADDR_IN* ipv4 = reinterpret_cast<SOCKADDR_IN*>(address->Address.lpSockaddr);

						char str_buffer[INET_ADDRSTRLEN] = { 0 };
						inet_ntop(AF_INET, &(ipv4->sin_addr), str_buffer, INET_ADDRSTRLEN);
						XNELO_LOG_DEBUG4("IP Address: %ls %s", adapter->FriendlyName, str_buffer);
					}
					else
					{
						// Skip all other types of addresses
						continue;
					}
				}
			}

			// Cleanup
			free(adapterAddresses);
			adapterAddresses = NULL;
			*/
			return Address(127, 0, 0, 1, 1025);
		}

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

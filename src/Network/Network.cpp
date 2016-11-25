/**
*/
#include "Network/Network.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		bool networking_initialized = false;

		bool InitializeNetworking()
		{
			if (networking_initialized)
				return true;

		#if PLATFORM == XNELO_PLATFORM_WINDOWS
			WSADATA WsaData;

			if (WSAStartup(MAKEWORD(2, 2), &WsaData) != NO_ERROR)
			{
				networking_initialized = false;
				return false;
			}

			networking_initialized = true;
		#else
			networking_initialized = true;
		#endif

			return networking_initialized;
		}

		void ShutdownNetworking()
		{
		#if PLATFORM == XNELO_PLATFORM_WINDOWS
			WSACleanup();
		#endif

			networking_initialized = false;
		}
	}//end namespace network
}//end namespace xnelo

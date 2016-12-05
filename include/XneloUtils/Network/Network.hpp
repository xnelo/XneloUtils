/**
*
*/
#ifndef ___XNELO_NETWORK_INCLUDES__HPP__11_5_2016___
#define ___XNELO_NETWORK_INCLUDES__HPP__11_5_2016___

#include "../Config.hpp"

#if PLATFORM == XNELO_PLATFORM_WINDOWS

	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <winsock2.h>
	#pragma comment(lib, "wsock32.lib")

#elif PLATFORM == XNELO_PLATFORM_MAC || PLATFORM == XNELO_PLATFORM_UNIX

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>

#endif


namespace XNELO
{
	namespace NETWORK
	{
		bool InitializeNetworking();
		void ShutdownNetworking();
	}//end namespace network
}//end namespace xnelo

#endif //___XNELO_NETWORK_INCLUDES__HPP__11_5_2016___

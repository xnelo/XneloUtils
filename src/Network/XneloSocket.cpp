#include "Network/XneloSocket.hpp"
#include "Logging/Logging.hpp"

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
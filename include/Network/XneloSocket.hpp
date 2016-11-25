#ifndef ___XNELO_NETWORK_SOCKET__HPP__11_10_2016___
#define ___XNELO_NETWORK_SOCKET__HPP__11_10_2016___

#include "Network/Network.hpp"
#include "Network/Address.hpp"
#include "Core/Fallible.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		class XneloSocket: public XNELO::CORE::Fallible
		{
		protected:
			int _socket;
			unsigned short _port;
		public:
			XNELO_API XneloSocket();
			XNELO_API XneloSocket(unsigned short port);
			XNELO_API virtual ~XneloSocket();

			XNELO_API void CloseSocket();

			XNELO_API int GetSocket();
			XNELO_API unsigned short GetPort();

			XNELO_API virtual int ReceiveData(Address & sender, void * data, int size) = 0;

			XNELO_API virtual int SendData(Address & address, void * buffer, int bufferSize) = 0;

			XNELO_API void SetPortNumber(unsigned short port);
		};
	}
}

inline int XNELO::NETWORK::XneloSocket::GetSocket()
{
	return _socket;
}

inline unsigned short XNELO::NETWORK::XneloSocket::GetPort()
{
	return _port;
}

#endif // ___XNELO_NETWORK_SOCKET__HPP__11_10_2016___
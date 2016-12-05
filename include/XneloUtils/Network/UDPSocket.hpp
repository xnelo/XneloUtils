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

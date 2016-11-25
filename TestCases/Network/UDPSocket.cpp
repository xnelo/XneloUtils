#include "Testing/Testing.hpp"
#include "Network/UDPSocket.hpp"

XNELO_TEST_CASE(UDPSocketTests, UDPSocket_Constructor)
{
	unsigned short portNumber = 0;
	XNELO::NETWORK::UDPSocket * udp = new XNELO::NETWORK::UDPSocket();

	XNELO_TEST_ASSERT_EQUAL(udp->GetSocket(), 0, "UDPSocket constructor socket at 0");
	XNELO_TEST_ASSERT_EQUAL(udp->GetPort(), portNumber, "UDPSocket constructor port at 0");
	XNELO_TEST_ASSERT_EQUAL(udp->GetErrorCode(), XNELO::ERRORS::OK, "UDPSocket constructor error is OK");

	delete udp;
}

XNELO_TEST_CASE(UDPSocketTests, UDPSocket_Constructor_Port)
{
	unsigned short portNumber = 12345;
	XNELO::NETWORK::UDPSocket * udp = new XNELO::NETWORK::UDPSocket(portNumber);

	XNELO_TEST_ASSERT_EQUAL(udp->GetSocket(), 0, "UDPSocket port constructor socket at 0");
	XNELO_TEST_ASSERT_EQUAL(udp->GetPort(), portNumber, "UDPSocket port constructor port at 12345");
	XNELO_TEST_ASSERT_EQUAL(udp->GetErrorCode(), XNELO::ERRORS::OK, "UDPSocket port constructor error is OK");

	delete udp;
}

XNELO_TEST_CASE(UDPSocketTests, UDPSocket_OpenSocket)
{
	unsigned short portNumber = 12345;
	XNELO::NETWORK::UDPSocket * udp = new XNELO::NETWORK::UDPSocket(portNumber);
	udp->OpenSocket();

	XNELO_TEST_ASSERT_NOT_EQUAL(udp->GetSocket(), 0, "UDPSocket is not 0");
	XNELO_TEST_ASSERT_EQUAL(udp->GetPort(), portNumber, "UDPSocket port at 12345");
	XNELO_TEST_ASSERT_EQUAL(udp->GetErrorCode(), XNELO::ERRORS::OK, "UDPSocket port constructor error is OK");

	udp->CloseSocket();

	XNELO_TEST_ASSERT_EQUAL(udp->GetSocket(), 0, "UDPSocket is 0");

	delete udp;
}

XNELO_TEST_CASE(UDPSocketTests, UDPSocket_OpenSocket_WithPort)
{
	unsigned short portNumber = 12345;
	XNELO::NETWORK::UDPSocket * udp = new XNELO::NETWORK::UDPSocket();
	udp->OpenSocket(portNumber);

	XNELO_TEST_ASSERT_NOT_EQUAL(udp->GetSocket(), 0, "UDPSocket is not 0");
	XNELO_TEST_ASSERT_EQUAL(udp->GetPort(), portNumber, "UDPSocket port at 12345");
	XNELO_TEST_ASSERT_EQUAL(udp->GetErrorCode(), XNELO::ERRORS::OK, "UDPSocket port constructor error is OK");

	udp->CloseSocket();

	XNELO_TEST_ASSERT_EQUAL(udp->GetSocket(), 0, "UDPSocket is 0");

	delete udp;
}

XNELO_TEST_CASE(UDPSocketTests, UDPSocket_SendData)
{
	unsigned short portNumberA = 12345;
	unsigned short portNumberB = 12346;

	XNELO::NETWORK::UDPSocket * udpA = new XNELO::NETWORK::UDPSocket(portNumberA);
	udpA->OpenSocket();

	XNELO::NETWORK::UDPSocket * udpB = new XNELO::NETWORK::UDPSocket(portNumberB);
	udpB->OpenSocket();

	const int dataASize = 5;
	char * dataA = "Dood";

	const int dataBSize = 25;
	char dataB[dataBSize];

	XNELO::NETWORK::Address addrA(127, 0, 0, 1, portNumberB);
	XNELO::NETWORK::Address addrB;

	XNELO_TEST_ASSERT_EQUAL(udpA->SendData(addrA, dataA, dataASize), dataASize, "UDPSocket sends data successfully");
	XNELO_TEST_ASSERT_EQUAL(udpB->ReceiveData(addrB, dataB, dataBSize), dataASize, "UDPSocket recieved data successfully");

	XNELO_TEST_ASSERT_EQUAL(udpA->GetErrorCode(), XNELO::ERRORS::OK, "UDPSocket sends data error code: OK");
	XNELO_TEST_ASSERT_EQUAL(udpB->GetErrorCode(), XNELO::ERRORS::OK, "UDPSocket sends data error code: OK");

	XNELO_TEST_ASSERT_EQUAL(strcmp(dataA, dataB), 0, "Data sent correctly");
	
	delete udpA;
	delete udpB;
}

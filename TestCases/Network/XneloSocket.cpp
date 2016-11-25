#include "Testing/Testing.hpp"
#include "Network/XneloSocket.hpp"

class XneloSocketTestImpl: public XNELO::NETWORK::XneloSocket
{
public:
	XneloSocketTestImpl() : XNELO::NETWORK::XneloSocket(){}
	XneloSocketTestImpl(unsigned short port) : XNELO::NETWORK::XneloSocket(port) {}
	virtual ~XneloSocketTestImpl(){}

	virtual int ReceiveData(XNELO::NETWORK::Address & sender, void * data, int size) { return 10; }

	virtual int SendData(XNELO::NETWORK::Address & address, void * packetData, int packetSize) { return 10; }
};

XNELO_TEST_CASE(XneloSocketTests, Constructor)
{
	XneloSocketTestImpl * tst = new XneloSocketTestImpl();

	XNELO_TEST_ASSERT_EQUAL(tst->GetErrorCode(), XNELO::ERRORS::OK, "Ensure ErrorCode is OK");
	XNELO_TEST_ASSERT_EQUAL(tst->GetSocket(), 0, "Ensure Socket is 0");
	XNELO_TEST_ASSERT_EQUAL(tst->GetPort(), (unsigned short)0, "Ensure Port is 0");

	delete tst;
}

XNELO_TEST_CASE(XneloSocketTests, SetPortFunction)
{
	XneloSocketTestImpl * tst = new XneloSocketTestImpl();

	tst->SetPortNumber(1234);

	XNELO_TEST_ASSERT_EQUAL(tst->GetPort(), (unsigned short)1234, "SetPortNumber function works");

	delete tst;
}

XNELO_TEST_CASE(XneloSocketTests, SetPortConstructor)
{
	unsigned short portNumber = 54321;

	XneloSocketTestImpl * tst = new XneloSocketTestImpl(portNumber);

	XNELO_TEST_ASSERT_EQUAL(tst->GetPort(), portNumber, "Constructor sets port properly");

	delete tst;
}

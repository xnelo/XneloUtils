/// <file> XneloSocket.cpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary>  </summary>
/// 
/// <copyright> Copyright (c) 2019 </copyright>
/// 
/// <license>
/// The zlib/libpng License
/// 
/// Copyright (c) 2019 Spencer Hoffa
/// 
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
/// 
/// Permission is granted to anyone to use this software for any purpose,
/// including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions:
/// 
/// 		1. The origin of this software must not be misrepresented; you must not
/// 		claim that you wrote the original software. If you use this software in
/// 		a product, an acknowledgment in the product documentation would be
/// 		appreciated but is not required.
/// 
/// 		2. Altered source versions must be plainly marked as such, and must not
/// 		be misrepresented as being the original software.
/// 
/// 		3. This notice may not be removed or altered from any source
/// 		distribution.
/// 
/// This liscense can also be found at: http://opensource.org/licenses/Zlib
/// </license>

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Network/XneloSocket.hpp"

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

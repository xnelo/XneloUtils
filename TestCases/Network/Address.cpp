/**
* @file Address.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Test file for the Address class.
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

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Network/Address.hpp"
#include <iostream>

XNELO_TEST_CASE(AddressTest, TestAddressDefaultConstructor)
{
	XNELO::NETWORK::Address * address;
	address = new XNELO::NETWORK::Address();
	XNELO_TEST_ASSERT_EQUAL(address->GetAddress(), (XNELO::CORE::uint32)0, "Ensure that default address is 0");
	XNELO_TEST_ASSERT_EQUAL(address->GetPort(), (XNELO::CORE::uint16)0, "Ensure that default address is 0");
	XNELO_TEST_ASSERT_EQUAL(address->GetA(), 0, "Ensure that default A part is 0");
	XNELO_TEST_ASSERT_EQUAL(address->GetB(), 0, "Ensure that default B part is 0");
	XNELO_TEST_ASSERT_EQUAL(address->GetC(), 0, "Ensure that default C part is 0");
	XNELO_TEST_ASSERT_EQUAL(address->GetD(), 0, "Ensure that default D part is 0");

	delete address;
}

XNELO_TEST_CASE(AddressTest, TestAddressSetters)
{
	XNELO::NETWORK::Address * address;
	address = new XNELO::NETWORK::Address();

	address->SetAddress(123, 124, 125, 126);

	XNELO_TEST_ASSERT_EQUAL(address->GetA(), 123, "Ensure that SetAddress A part is 123");
	XNELO_TEST_ASSERT_EQUAL(address->GetB(), 124, "Ensure that SetAddress B part is 124");
	XNELO_TEST_ASSERT_EQUAL(address->GetC(), 125, "Ensure that SetAddress C part is 125");
	XNELO_TEST_ASSERT_EQUAL(address->GetD(), 126, "Ensure that SetAddress D part is 126");

	address->SetAddressPort(12345);

	XNELO_TEST_ASSERT_EQUAL(address->GetPort(), (XNELO::CORE::uint16)12345, "Ensure that SetPort is 12345");

	delete address;
}

XNELO_TEST_CASE(AddressTest, TestAddressSettersInteger)
{
	XNELO::NETWORK::Address * address = new XNELO::NETWORK::Address();
	XNELO::CORE::uint32 addressInteger = inet_addr("192.168.2.176");

	address->SetAddress(addressInteger);

	XNELO_TEST_ASSERT_EQUAL(address->GetA(), 192, "Ensure that SetAddressInteger A part is 192");
	XNELO_TEST_ASSERT_EQUAL(address->GetB(), 168, "Ensure that SetAddressInteger B part is 168");
	XNELO_TEST_ASSERT_EQUAL(address->GetC(), 2, "Ensure that SetAddressInteger C part is 2");
	XNELO_TEST_ASSERT_EQUAL(address->GetD(), 176, "Ensure that SetAddressInteger D part is 176");

	delete address;
}

XNELO_TEST_CASE(AddressTest, TestAddressConstructor)
{
	XNELO::NETWORK::Address * address;
	address = new XNELO::NETWORK::Address(192, 168, 2, 176, 8080);
	XNELO::CORE::uint32 addressInteger = inet_addr("192.168.2.176");

	XNELO_TEST_ASSERT_EQUAL(address->GetAddress(), addressInteger, "Ensure that constructor sets address correctly");
	XNELO_TEST_ASSERT_EQUAL(address->GetPort(), (XNELO::CORE::uint16)8080, "Ensure that constructor sets port correctly");

	XNELO_TEST_ASSERT_EQUAL(address->GetA(), 192, "Ensure that constructor A part is 192");
	XNELO_TEST_ASSERT_EQUAL(address->GetB(), 168, "Ensure that constructor B part is 168");
	XNELO_TEST_ASSERT_EQUAL(address->GetC(), 2, "Ensure that constructor C part is 2");
	XNELO_TEST_ASSERT_EQUAL(address->GetD(), 176, "Ensure that constructor D part is 176");

	delete address;
}

XNELO_TEST_CASE(AddressTest, TestAddressCopyConstructor)
{
	XNELO::NETWORK::Address * address;
	address = new XNELO::NETWORK::Address(192, 168, 2, 176, 8080);
	XNELO::NETWORK::Address * address2 = new XNELO::NETWORK::Address(*address);
	XNELO::CORE::uint32 addressInteger = inet_addr("192.168.2.176");

	XNELO_TEST_ASSERT_EQUAL(address->GetAddress(), addressInteger, "Ensure that copy constructor sets address correctly");
	XNELO_TEST_ASSERT_EQUAL(address->GetPort(), (XNELO::CORE::uint16)8080, "Ensure that copy constructor sets port correctly");

	XNELO_TEST_ASSERT_EQUAL(address->GetA(), 192, "Ensure that copy constructor A part is 192");
	XNELO_TEST_ASSERT_EQUAL(address->GetB(), 168, "Ensure that copy constructor B part is 168");
	XNELO_TEST_ASSERT_EQUAL(address->GetC(), 2, "Ensure that copy constructor C part is 2");
	XNELO_TEST_ASSERT_EQUAL(address->GetD(), 176, "Ensure that copy constructor D part is 176");

	XNELO_TEST_ASSERT_EQUAL(address2->GetAddress(), addressInteger, "Ensure that copy constructor sets address 2 correctly");
	XNELO_TEST_ASSERT_EQUAL(address2->GetPort(), (XNELO::CORE::uint16)8080, "Ensure that copy constructor sets port 2 correctly");

	XNELO_TEST_ASSERT_EQUAL(address2->GetA(), 192, "Ensure that copy constructor A part 2 is 192");
	XNELO_TEST_ASSERT_EQUAL(address2->GetB(), 168, "Ensure that copy constructor B part 2 is 168");
	XNELO_TEST_ASSERT_EQUAL(address2->GetC(), 2, "Ensure that copy constructor C part 2 is 2");
	XNELO_TEST_ASSERT_EQUAL(address2->GetD(), 176, "Ensure that copy constructor D part 2 is 176");

	delete address;
	delete address2;
}

XNELO_TEST_CASE(AddressTest, TestAddressAssignmentOperator)
{
	XNELO::NETWORK::Address address;
	address.SetAddress(192, 168, 2, 176);

	XNELO_TEST_ASSERT_EQUAL(address.GetA(), 192, "Ensure that setup A is 192");
	XNELO_TEST_ASSERT_EQUAL(address.GetB(), 168, "Ensure that setup B  is 168");
	XNELO_TEST_ASSERT_EQUAL(address.GetC(), 2, "Ensure that setup C is 2");
	XNELO_TEST_ASSERT_EQUAL(address.GetD(), 176, "Ensure that setup D is 176");

	XNELO::NETWORK::Address address2;

	address2 = address;

	XNELO_TEST_ASSERT_EQUAL(address2.GetA(), 192, "Ensure that assignment A part 2 is 192");
	XNELO_TEST_ASSERT_EQUAL(address2.GetB(), 168, "Ensure that assignment B part 2 is 168");
	XNELO_TEST_ASSERT_EQUAL(address2.GetC(), 2, "Ensure that assignment C part 2 is 2");
	XNELO_TEST_ASSERT_EQUAL(address2.GetD(), 176, "Ensure that assignment D part 2 is 176");
}
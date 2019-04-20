/// <file> UUID.cpp </file>
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

#include <string>

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Core/BitwiseOperators.hpp"
#include "XneloUtils/Core/UUID.hpp"

XNELO_TEST_CASE(UUIDTests, CreationAndGettersWork)
{
	XNELO::CORE::UUID uuid;
	XNELO::CORE::UUID::NewUUID(&uuid);
	XNELO::CORE::uint8 byte = uuid.GetBytes()[6];
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(byte, XNELO::CORE::bit8), "Bit 8 of 7th byte is 0");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSet(byte, XNELO::CORE::bit7), "Bit 7 of 7th byte is 1");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(byte, XNELO::CORE::bit6), "Bit 6 of 7th byte is 0");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(byte, XNELO::CORE::bit5), "Bit 5 of 7th byte is 0");

	byte = uuid.GetBytes()[8];
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSet(byte, XNELO::CORE::bit8), "Bit 8 of 7th byte is 1");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(byte, XNELO::CORE::bit7), "Bit 7 of 7th byte is 0");
}

XNELO_TEST_CASE(UUIDTests, ParseText)
{
	std::string uuidString = "994EA474-E5AE-4281-B251-CA2B4BD8D563";

	XNELO::CORE::UUID uuid;
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::UUID::FromString(&uuid, uuidString), "Parsing successful");

	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[0], (XNELO::CORE::uint8)0x99, "1 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[1], (XNELO::CORE::uint8)0x4E, "2 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[2], (XNELO::CORE::uint8)0xA4, "3 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[3], (XNELO::CORE::uint8)0x74, "4 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[4], (XNELO::CORE::uint8)0xE5, "5 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[5], (XNELO::CORE::uint8)0xAE, "6 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[6], (XNELO::CORE::uint8)0x42, "7 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[7], (XNELO::CORE::uint8)0x81, "8 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[8], (XNELO::CORE::uint8)0xB2, "9 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[9], (XNELO::CORE::uint8)0x51, "10 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[10], (XNELO::CORE::uint8)0xCA, "11 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[11], (XNELO::CORE::uint8)0x2B, "12 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[12], (XNELO::CORE::uint8)0x4B, "13 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[13], (XNELO::CORE::uint8)0xD8, "14 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[14], (XNELO::CORE::uint8)0xD5, "15 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[15], (XNELO::CORE::uint8)0x63, "16 byte correct");
}

XNELO_TEST_CASE(UUIDTests, ParseByteArray)
{
	XNELO::CORE::uint8 uuidArray[16] = { 0x99, 0x4E, 0xA4, 0x74, 
										 0xE5, 0xAE, 
										 0x42, 0x81, 
										 0xB2, 0x51, 
										 0xCA, 0x2B, 0x4B, 0xD8, 0xD5, 0x63 };
	XNELO::CORE::UUID uuid;
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::UUID::FromByteArray(&uuid, uuidArray), "Parse from Byte Array");

	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[0], (XNELO::CORE::uint8)0x99, "1 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[1], (XNELO::CORE::uint8)0x4E, "2 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[2], (XNELO::CORE::uint8)0xA4, "3 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[3], (XNELO::CORE::uint8)0x74, "4 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[4], (XNELO::CORE::uint8)0xE5, "5 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[5], (XNELO::CORE::uint8)0xAE, "6 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[6], (XNELO::CORE::uint8)0x42, "7 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[7], (XNELO::CORE::uint8)0x81, "8 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[8], (XNELO::CORE::uint8)0xB2, "9 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[9], (XNELO::CORE::uint8)0x51, "10 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[10], (XNELO::CORE::uint8)0xCA, "11 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[11], (XNELO::CORE::uint8)0x2B, "12 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[12], (XNELO::CORE::uint8)0x4B, "13 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[13], (XNELO::CORE::uint8)0xD8, "14 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[14], (XNELO::CORE::uint8)0xD5, "15 byte correct");
	XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[15], (XNELO::CORE::uint8)0x63, "16 byte correct");
}

XNELO_TEST_CASE(UUIDTests, AssignmentAndCopyConstructor)
{
	XNELO::CORE::UUID uuid;
	XNELO::CORE::UUID::NewUUID(&uuid);

	XNELO::CORE::UUID uuid2(uuid);
	XNELO::CORE::UUID uuid3;

	uuid3 = uuid2;

	XNELO_TEST_ASSERT_TRUE(uuid == uuid2, "Check that uuid and uuid2 are same");
	XNELO_TEST_ASSERT_TRUE(uuid == uuid3, "Check that uuid and uuid3 are same");
	XNELO_TEST_ASSERT_TRUE(uuid2 == uuid3, "Check that uuid2 and uuid3 are same");
}

XNELO_TEST_CASE(UUIDTests, EqualityAndNotEquality)
{
	std::string uuidString = "994EA474-E5AE-4281-B251-CA2B4BD8D563";

	XNELO::CORE::UUID uuid1, uuid2, uuid3;
	XNELO::CORE::UUID::NewUUID(&uuid3);
	XNELO::CORE::UUID::FromString(&uuid1, uuidString);
	XNELO::CORE::UUID::FromString(&uuid2, uuidString);

	XNELO_TEST_ASSERT_TRUE(uuid1 == uuid2, "Check that two uuids equal true");
	XNELO_TEST_ASSERT_FALSE(uuid1 == uuid3, "Check that two uuids equal false");
	XNELO_TEST_ASSERT_TRUE(uuid1 != uuid3, "Check that two uuid not equal true");
	XNELO_TEST_ASSERT_FALSE(uuid1 != uuid2, "Check that tow uuid not equal false.")
}

XNELO_TEST_CASE(UUIDTests, UUIDToString)
{
	std::string uuidString = "994EA474-E5AE-4281-B251-CA2B4BD8D563";
	XNELO::CORE::UUID uuid;
	XNELO::CORE::UUID::FromString(&uuid, uuidString);
	//std::cout << uuid.ToString() << std::endl;
	XNELO_TEST_ASSERT_EQUAL(uuid.ToString(), uuidString, "Check to String correct");

	uuidString = "0940A474-E5AE-4281-B251-CA2B4BD8D563";
	XNELO::CORE::UUID::FromString(&uuid, uuidString);
	//std::cout << uuid.ToString() << std::endl;
	XNELO_TEST_ASSERT_EQUAL(uuid.ToString(), uuidString, "Check to String correct 2");
}

XNELO_TEST_CASE(UUIDTests, CheckNILCorrect)
{
	std::string nilUUID = "00000000-0000-0000-0000-000000000000";
	XNELO::CORE::UUID uuid;
	XNELO_TEST_ASSERT_EQUAL(uuid.ToString(), nilUUID, "Check Nil Value Correct");

	for (int i = 0; i < 16; ++i)
	{
		XNELO_TEST_ASSERT_EQUAL(uuid.GetBytes()[i], (XNELO::CORE::uint8)0, "Check byte.");
	}
}

XNELO_TEST_CASE(UUIDTests, CheckHash)
{
	std::string uuidString = "0940A474-E5AE-4281-B251-CA2B4BD8D563";
	XNELO::CORE::UUID uuid;
	XNELO::CORE::UUID::FromString(&uuid, uuidString);
	
	XNELO_TEST_ASSERT_EQUAL(uuid.GetHash(), (std::size_t)16327649465352458683, "Check hash calcualted correctly");
}

/**
* @file BufferStreamReader.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Test cases for the BufferStreamReader class.
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
#include "XneloUtils/Stream/BufferStreamReader.hpp"

XNELO_TEST_CASE(BufferStreamReaderTests, TestConstructor)
{
	XNELO::STREAM::BufferStreamReader * buff = new XNELO::STREAM::BufferStreamReader();

	XNELO_TEST_ASSERT_TRUE(buff->GetBuffer() == NULL, "Buffer is not NULL");
	XNELO_TEST_ASSERT_EQUAL(buff->GetSize(), (XNELO::CORE::uint32)0, "Buffer size is not 0");
	XNELO_TEST_ASSERT_EQUAL(buff->GetErrorCode(), XNELO::ERRORS::OK, "Buffer error code is not OK");

	delete buff;
}

XNELO_TEST_CASE(BufferStreamReaderTests, AddDataToBuffer)
{
	XNELO::STREAM::BufferStreamReader * buff = new XNELO::STREAM::BufferStreamReader();

	XNELO_TEST_ASSERT_TRUE(buff->AddDataToBuffer("Hello World", 11), "Add data to buffer failed");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(buff->GetBuffer(), "Hello World", 11), 0, "Buffer not copied correctly");
	XNELO_TEST_ASSERT_EQUAL(buff->GetSize(), (XNELO::CORE::uint32)11, "Size not correct");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 11, "Amount left is incorrect");

	XNELO_TEST_ASSERT_TRUE(buff->AddDataToBuffer(" I'm Here", 9), "Add data to buffer 2 failed");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(buff->GetBuffer(), "Hello World I'm Here", 20), 0, "Buffer not copied correctly 2");
	XNELO_TEST_ASSERT_EQUAL(buff->GetSize(), (XNELO::CORE::uint32)20, "Size not correct 2");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 20, "Amount left is incorrect 2");

	delete buff;
}

XNELO_TEST_CASE(BufferStreamReaderTests, CheckReadFunction)
{
	XNELO::STREAM::BufferStreamReader * buff = new XNELO::STREAM::BufferStreamReader();
	char resBuffer[25];

	XNELO_TEST_ASSERT_TRUE(buff->AddDataToBuffer("HelloWorld", 10), "Data added correctly");
	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 5), 5, "Read failed.");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(resBuffer, "Hello", 5), 0, "Read success [data copied]");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 5, "Amount left incorrect");

	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 2), 2, "Read failed 2");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(resBuffer, "Wo", 2), 0, "Read success [data copied] 2");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 3, "Amount left incorrect 2");

	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 2), 2, "Read failed 3");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(resBuffer, "rl", 2), 0, "Read success [data copied] 3");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 1, "Amount left incorrect 3");

	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 2), 1, "Read failed 4");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(resBuffer, "d", 1), 0, "Read success [data copied] 4");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 0, "Amount left incorrect 4");

	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 2), 0, "Read failed 5");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 0, "Amount left incorrect 5");

	delete buff;
}

XNELO_TEST_CASE(BufferStreamReaderTests, CheckReadFunctionAddData)
{
	XNELO::STREAM::BufferStreamReader * buff = new XNELO::STREAM::BufferStreamReader();
	char resBuffer[25];

	XNELO_TEST_ASSERT_TRUE(buff->AddDataToBuffer("HelloWorld", 10), "Data added correctly");
	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 5), 5, "Read failed.");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(resBuffer, "Hello", 5), 0, "Read success [data copied]");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 5, "Amount left incorrect");
	XNELO_TEST_ASSERT_TRUE(buff->IsOK(), "Buffer status not OK");

	XNELO_TEST_ASSERT_TRUE(buff->AddDataToBuffer("MoarData", 8), "Add data failed");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 13, "Amount left after add incorrect");
	XNELO_TEST_ASSERT_TRUE(buff->IsOK(), "Buffer status not OK");

	XNELO_TEST_ASSERT_EQUAL(buff->Read(resBuffer, 13), 13, "Read failed 2");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(resBuffer, "WorldMoarData", 13), 0, "Read success [data copied] 2");
	XNELO_TEST_ASSERT_EQUAL(buff->AmountLeft(), 0, "Amount left incorrect 2");
	XNELO_TEST_ASSERT_TRUE(buff->IsOK(), "Buffer status not OK 2");

	XNELO_TEST_ASSERT_EQUAL(buff->GetSize(), (XNELO::CORE::uint32)18, "Buffer size not correct");
	
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(buff->GetBuffer(), "HelloWorldMoarData", 18), 0, "Reader buffer is incorrect");

	delete buff;
}

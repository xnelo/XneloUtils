/**
* @file BufferStreamWriter.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Test cases for BufferStreamWriter class.
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
#include "XneloUtils/Stream/BufferStreamWriter.hpp"

#include <cstring>

XNELO_TEST_CASE(BufferStreamWriterTests, TestDefaultConstructor)
{
	XNELO::STREAM::BufferStreamWriter * buffer = new XNELO::STREAM::BufferStreamWriter();
	XNELO_TEST_ASSERT_TRUE(buffer->GetBuffer() != NULL, "Check that buffer is initialized");
	delete buffer;
}

XNELO_TEST_CASE(BufferStreamWriterTests, TestParameterConstructor)
{
	XNELO::STREAM::BufferStreamWriter * buffer = new XNELO::STREAM::BufferStreamWriter(100);
	XNELO_TEST_ASSERT_TRUE(buffer->GetBuffer() != NULL, "Check that buffer is initialized");
	delete buffer;
}

XNELO_TEST_CASE(BufferStreamWriterTests, TestWrite)
{
	XNELO::STREAM::BufferStreamWriter * buffer = new XNELO::STREAM::BufferStreamWriter(100);
	XNELO_TEST_ASSERT_EQUAL(buffer->Write("Hello World", 11), 11, "Check that Write function works");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(buffer->GetBuffer(), "Hello World", 11), 0, "Write Function copied data correctly.");
	XNELO_TEST_ASSERT_EQUAL(buffer->GetSize(), (XNELO::CORE::uint32)11, "Data buffer size correct");
	delete buffer;
}

XNELO_TEST_CASE(BufferStreamWriterTests, TestExpandBuffer)
{
	XNELO::STREAM::BufferStreamWriter * buffer = new XNELO::STREAM::BufferStreamWriter(25);
	XNELO_TEST_ASSERT_EQUAL(buffer->Write("Hello World this is a ", 22), 22, "Check that Write function 1");
	XNELO_TEST_ASSERT_EQUAL(buffer->Write("string copy test", 16), 16, "Check that Write function across boundry works");
	XNELO_TEST_ASSERT_EQUAL(std::strncmp(buffer->GetBuffer(), 
		                                 "Hello World this is a string copy test", 
		                                 38), 0, "Buffer contains correct string");
	XNELO_TEST_ASSERT_EQUAL(buffer->GetSize(), (XNELO::CORE::uint32)38, "Data buffer size correct");
	//std::cout << buffer->GetBuffer() << std::endl;
	delete buffer;
}

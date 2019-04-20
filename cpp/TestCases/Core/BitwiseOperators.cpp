// <file> Testing.hpp </file>
// <author> Spencer Hoffa </author>
//
// <copyright> 2019 Spencer Hoffa </copyright>
//
// <summary>
// This file includes all the header files needed to use the Xnelo Testing 
// library. For ease just include this file and you have access to the entire
// library.
// </summary>
//
// <license>
// The zlib/libpng License
//
// Copyright (c) 2019 Spencer Hoffa
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//		1. The origin of this software must not be misrepresented; you must not
//		claim that you wrote the original software. If you use this software in
//		a product, an acknowledgment in the product documentation would be
//		appreciated but is not required.
//
//		2. Altered source versions must be plainly marked as such, and must not
//		be misrepresented as being the original software.
//
//		3. This notice may not be removed or altered from any source
//		distribution.
//
// This liscense can also be found at: http://opensource.org/licenses/Zlib
// </license>

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Core/BitwiseOperators.hpp"

XNELO_TEST_CASE(BitwiseOperatorTests, TestEverything)
{
	XNELO::CORE::uint32 bits = 0;
	bits |= XNELO::CORE::bit3;
	bits |= XNELO::CORE::bit6;
	bits |= XNELO::CORE::bit4;

	XNELO_TEST_ASSERT_EQUAL(bits, (XNELO::CORE::uint32)44, "Start value Correct");
	
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSetBitNumber(bits, 0), "Check bit 0 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSetBitNumber(bits, 1), "Check bit 1 set");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSetBitNumber(bits, 2), "Check bit 2 set");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSetBitNumber(bits, 3), "Check bit 3 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSetBitNumber(bits, 4), "Check bit 4 set");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSetBitNumber(bits, 5), "Check bit 5 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSetBitNumber(bits, 6), "Check bit 6 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSetBitNumber(bits, 7), "Check bit 7 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSetBitNumber(bits, 8), "Check bit 8 set");
	/*test->UnitTest(IsBitSetBitNumber(bits, 9) == false, "Check bit 9 set");
	test->UnitTest(IsBitSetBitNumber(bits, 10) == false, "Check bit 10 set");
	test->UnitTest(IsBitSetBitNumber(bits, 11) == false, "Check bit 11 set");
	test->UnitTest(IsBitSetBitNumber(bits, 12) == false, "Check bit 12 set");
	test->UnitTest(IsBitSetBitNumber(bits, 13) == false, "Check bit 13 set");
	test->UnitTest(IsBitSetBitNumber(bits, 14) == true, "Check bit 14 set");
	test->UnitTest(IsBitSetBitNumber(bits, 15) == false, "Check bit 15 set");
	test->UnitTest(IsBitSetBitNumber(bits, 16) == false, "Check bit 16 set");
	test->UnitTest(IsBitSetBitNumber(bits, 17) == false, "Check bit 17 set");
	test->UnitTest(IsBitSetBitNumber(bits, 18) == false, "Check bit 18 set");*/

	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit1), "Check bit 0 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit2), "Check bit 1 set");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit3), "Check bit 2 set");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit4), "Check bit 3 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit5), "Check bit 4 set");
	XNELO_TEST_ASSERT_TRUE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit6), "Check bit 5 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit7), "Check bit 6 set");
	XNELO_TEST_ASSERT_FALSE(XNELO::CORE::IsBitSet(bits, (XNELO::CORE::uint32)XNELO::CORE::bit8), "Check bit 7 set");
	/*test->UnitTest(IsBitSet(bits, BIO::CORE::bit9) == true, "Check bit 8 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit10) == false, "Check bit 9 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit11) == false, "Check bit 10 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit12) == false, "Check bit 11 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit13) == false, "Check bit 12 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit14) == false, "Check bit 13 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit15) == true, "Check bit 14 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit16) == false, "Check bit 15 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit17) == false, "Check bit 16 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit18) == false, "Check bit 17 set");
	test->UnitTest(IsBitSet(bits, BIO::CORE::bit19) == false, "Check bit 18 set");
	*/
}
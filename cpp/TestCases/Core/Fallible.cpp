/**
* @file Fallible.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Test file for the XNELO::CORE::Fallible class.
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
#include "XneloUtils/Core/Fallible.hpp"

XNELO_TEST_CASE(FallibleTest, TestFallibleConstructor)
{
	XNELO::CORE::Fallible fail;
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorCode(), XNELO::ERRORS::OK, "Constructor sets error correctly");
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorMessage(), std::string("OK"), "Constructor sets error message correctly");
}

XNELO_TEST_CASE(FallibleTest, TestFallibleSetters)
{
	XNELO::CORE::Fallible fail;
	std::string errorMessage = "Network Failed To Initialize";
	fail.SetError(XNELO::ERRORS::NETWORKING_FAILED_TO_INITIALIZE, errorMessage);
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorCode(), XNELO::ERRORS::NETWORKING_FAILED_TO_INITIALIZE, "SetError set code correctly");
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorMessage(), errorMessage, "SetError set message correctly");
}

XNELO_TEST_CASE(FallibleTest, TestFallibleIsOK)
{
	XNELO::CORE::Fallible fail;
	std::string errorMessage = "Network Failed To Initialize";
	XNELO_TEST_ASSERT_EQUAL(fail.IsOK(), true, "Check that IsOK returns true");
	fail.SetError(XNELO::ERRORS::NETWORKING_FAILED_TO_INITIALIZE, errorMessage);
	XNELO_TEST_ASSERT_EQUAL(fail.IsOK(), false, "Check that IsOK returns false");
}
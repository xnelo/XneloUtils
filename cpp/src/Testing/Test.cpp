/**
* @file Test.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Implementation of the Test class.
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

#include "XneloUtils/Testing/Test.hpp"
#include "XneloUtils/Testing/TestMaster.hpp"

#include <iostream>

namespace XNELO
{
	namespace TESTING
	{

		Test::Test(std::string test_name): _test_name(test_name), _test_results(), _success(0), _failed(0)
		{
		}

		Test::Test(const char * test_name): _test_name(test_name), _test_results(), _success(0), _failed(0)
		{
		}

		Test::~Test()
		{
			for (std::vector<TestResult*>::iterator it = _test_results.begin(); it != _test_results.end(); ++it)
			{
				delete (*it);
			}

			_test_results.clear();
			_test_name = "";
			_success = 0;
			_failed = 0;
		}

		bool XNELO::TESTING::Test::AssertFalse(bool booleanValue, std::string description)
		{
			return AssertFalse(booleanValue, description.c_str());
		}

		bool XNELO::TESTING::Test::AssertFalse(bool booleanValue, const char * description)
		{
			return AssertEqual<bool>(booleanValue, true, description);
			//return false;
		}

		bool XNELO::TESTING::Test::AssertTrue(bool booleanValue, std::string description)
		{
			return AssertTrue(booleanValue, description.c_str());
		}

		bool XNELO::TESTING::Test::AssertTrue(bool booleanValue, const char * description)
		{
			return AssertEqual<bool>(booleanValue, true, description);
		}
	}//end namespace TEST
}//end namespace XNELO


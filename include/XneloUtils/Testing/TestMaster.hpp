/**
* @file TestMaster.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define a singleton class that controls all of the testing.
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

#ifndef ___XNELO_TESTING_TESTMASTER__HPP__10_06_2016___
#define ___XNELO_TESTING_TESTMASTER__HPP__10_06_2016___

#include "../Config.hpp"
#include "IReportGenerator.hpp"
#include "Test.hpp"
#include <string>
#include <vector>

#include <iostream> //for testing remove when creating build

namespace XNELO
{
	namespace TESTING
	{
		class TestMaster
		{
		private:
			std::vector<Test*> _test_classes;
			std::vector<TestResult*> _lone_test_results;
			IReportGenerator * _output_generator;

			static TestMaster * _instance;
			static void CleanUp();

			XNELO_API TestMaster();

		public:
			XNELO_API ~TestMaster();

			XNELO_API static TestMaster * GetInstance();
			
			template<typename T>
			XNELO_API static TestResult * CheckEqual(T condition, T expected, const char * description);
			template<typename T>
			XNELO_API static TestResult * CheckNotEqual(T condition, T expected, const char * description);

			/**
			  * Any 'Test' class added with this method will **NOT** be deleted by the 'TestMaster' instance.
			  */
			XNELO_API void AddTest(Test * to_add);

			/**
			  * Any 'TestResult' class added with this function will be deleted by this class.
			  */
			XNELO_API void AddTestResult(TestResult * to_add);

			XNELO_API IReportGenerator * GetReportGenerator();

			XNELO_API void RunAllTest();

			XNELO_API void PrintResults();
		};
	}
}

inline XNELO::TESTING::IReportGenerator * XNELO::TESTING::TestMaster::GetReportGenerator()
{
	return _output_generator;
}

template<typename T>
inline XNELO::TESTING::TestResult * XNELO::TESTING::TestMaster::CheckEqual(T condition, T expected, const char * description)
{
	XNELO::TESTING::TestResult * result = new XNELO::TESTING::TestResult();

	result->passed = (condition == expected);
	result->name = new char[std::strlen(description) + 1];
	std::strcpy(result->name, description);

	return result;
}

template<typename T>
inline XNELO::TESTING::TestResult * XNELO::TESTING::TestMaster::CheckNotEqual(T condition, T expected, const char * description)
{
	XNELO::TESTING::TestResult * result = new XNELO::TESTING::TestResult();

	result->passed = (condition != expected);
	result->name = new char[std::strlen(description) + 1];
	std::strcpy(result->name, description);

	return result;
}

#endif //___XNELO_TESTING_TESTMASTER__HPP__10_06_2016___

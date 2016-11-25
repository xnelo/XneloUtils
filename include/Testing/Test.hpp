/**
* @file Test.hpp
* @author Spencer Hoffa
*
* @copyright 2014 Spencer Hoffa
*
* A class that handles all of the testing. This class will keep track of each 
* individual tests and whether they wer a success or failure.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2014 Spencer Hoffa
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

#ifndef ___XNELO_TESTING_Test_H__2014___
#define ___XNELO_TESTING_Test_H__2014___

#include "Config.hpp"
#include "Testing/TestResult.hpp"
#include "Testing/IReportGenerator.hpp"
#include <string>
#include <vector>

namespace XNELO
{
	namespace TESTING
	{
		/**
		* A class that executes unit test and keeps track of their results.
		*/
		class Test
		{
		private:
			std::string _test_name;
			std::vector<TestResult*> _test_results;
			int _success;
			int _failed;
		public:
			XNELO_API Test(std::string test_name);
			XNELO_API Test(const char * test_name);
			XNELO_API ~Test();
			
			template<typename T>
			XNELO_API bool AssertEqual(T expression1, T expression2, const char * description = NULL);
			template<typename T>
			XNELO_API bool AssertEqual(T expression1, T expression2, std::string description);

			template<typename T>
			XNELO_API bool AssertNotEqual(T expression1, T expression2, const char * description = NULL);
			template<typename T>
			XNELO_API bool AssertNotEqual(T expression1, T expression2, std::string description);

			XNELO_API bool AssertFalse(bool booleanValue, const char * description = NULL);
			XNELO_API bool AssertFalse(bool booleanValue, std::string description);
			XNELO_API bool AssertTrue(bool booleanValue, const char * description = NULL);
			XNELO_API bool AssertTrue(bool booleanValue, std::string description);

			XNELO_API int GetNumFailed();
			XNELO_API int GetNumSuccess();
			XNELO_API int GetNumTestResults();
			XNELO_API std::string GetTestName();
			XNELO_API TestResult * GetTestResult(unsigned int index);

			XNELO_API virtual void Run() = 0;

			//XNELO_API bool UnitTest(bool condition, bool expected, const char * description=NULL);
			//XNELO_API bool UnitTest(bool condition, bool expected, std::string description);
		};
	}//end namespace TESTING
}//end namespace XNELO

inline int XNELO::TESTING::Test::GetNumFailed()
{
	return _failed;
}

inline int XNELO::TESTING::Test::GetNumSuccess()
{
	return _success;
}

inline std::string XNELO::TESTING::Test::GetTestName()
{
	return _test_name;
}

inline int XNELO::TESTING::Test::GetNumTestResults()
{
	return (int)_test_results.size();
}

inline XNELO::TESTING::TestResult * XNELO::TESTING::Test::GetTestResult(unsigned int index)
{
	if (index > _test_results.size())
		return NULL;

	return _test_results[index];
}

template<typename T>
inline bool XNELO::TESTING::Test::AssertEqual(T condition, T expected, std::string description)
{
	return AssertEqual<T>(condition, expected, description.c_str());
}

template<typename T>
inline bool XNELO::TESTING::Test::AssertEqual(T condition, T expected, const char * description)
{

	XNELO::TESTING::TestResult * result = XNELO::TESTING::TestMaster::CheckEqual<T>(condition, expected, description);

	if (result->passed)
		++_success;
	else
		++_failed;

	_test_results.push_back(result);

	XNELO::TESTING::TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(result);

	return result->passed;
}

template<typename T>
inline bool XNELO::TESTING::Test::AssertNotEqual(T expression1, T expression2, std::string description)
{
	return AssertNotEqual<T>(expression1, expression2, description.c_str());
}

template<typename T>
inline bool XNELO::TESTING::Test::AssertNotEqual(T expression1, T expression2, const char * description)
{
	XNELO::TESTING::TestResult * result = XNELO::TESTING::TestMaster::CheckNotEqual<T>(expression1, expression2, description);

	if (result->passed)
		++_success;
	else
		++_failed;

	_test_results.push_back(result);

	XNELO::TESTING::TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(result);

	return result->passed;
}

#endif //___XNELO_TESTING_Test_H__2014___

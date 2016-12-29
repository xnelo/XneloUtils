/**
* @file Testing.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* This file includes all the header files needed to use the Xnelo Testing 
* library. For ease just include this file and you have access to the entire
* library.
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

#ifndef ___XNELO_TESTING_Testing_H__2014___
#define ___XNELO_TESTING_Testing_H__2014___

#include "../Config.hpp"
#include "TestMaster.hpp"
#include "IReportGenerator.hpp"
#include "OutStreamGenerator.hpp"
#include "Test.hpp"
#include "TestResult.hpp"
//#include "TestSuite.hpp"

#include <string>
#include <sstream>

template<typename T>
inline bool AssertEqual(T condition, T expected, std::string description)
{
	return AssertEqual(condition, expected, description.c_str());
}

template<typename T>
inline bool AssertEqual(T condition, T expected, const char * description)
{
	XNELO::TESTING::TestResult * result;
	result = XNELO::TESTING::TestMaster::CheckEqual<T>(condition, expected, description);

	XNELO::TESTING::TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(result);

	return result->passed;
}

template<typename T>
inline bool AssertNotEqual(T expression1, T expression2, std::string description)
{
	return AssertNotEqual(expression1, expression2, description.c_str());
}

template<typename T>
inline bool AssertNotEqual(T expression1, T expression2, const char * description)
{
	XNELO::TESTING::TestResult * result;
	result = XNELO::TESTING::TestMaster::CheckNotEqual<T>(expression1, expression2, description);

	XNELO::TESTING::TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(result);

	return result->passed;
}

inline bool AssertFalse(bool booleanValue, const char * description)
{
	return AssertEqual<bool>(booleanValue, false, description);
}

inline bool AssertFalse(bool booleanValue, std::string description)
{
	return AssertFalse(booleanValue, description.c_str());
}

inline bool AssertTrue(bool booleanValue, const char * description)
{
	return AssertEqual<bool>(booleanValue, true, description);
}

inline bool AssertTrue(bool booleanValue, std::string description)
{
	return AssertTrue(booleanValue, description.c_str());
}

//Define the macros for this library
#define XNELO_TEST_ASSERT_EQUAL(condition, expected, description) \
if (!AssertEqual(condition, expected, description)) \
{\
	std::ostringstream oss; \
	oss << __FILE__ << "(Line: " << __LINE__ << ")"; \
	XNELO::TESTING::TestMaster::GetInstance()->GetReportGenerator()->PrintAdditionalString(oss.str().c_str()); \
}

#define XNELO_TEST_ASSERT_NOT_EQUAL(condition, expected, description) \
if (!AssertNotEqual(condition, expected, description)) \
{\
	std::ostringstream oss; \
	oss << __FILE__ << "(Line: " << __LINE__ << ")"; \
	XNELO::TESTING::TestMaster::GetInstance()->GetReportGenerator()->PrintAdditionalString(oss.str().c_str()); \
}

#define XNELO_TEST_ASSERT_TRUE(booleanValue, description) XNELO_TEST_ASSERT_EQUAL(booleanValue, true, description)
#define XNELO_TEST_ASSERT_FALSE(booleanValue, description) XNELO_TEST_ASSERT_EQUAL(booleanValue, false, description)

#define XNELO_CREATE_TESTCASE_CLASS_NAME(test_group, test_case_name) TestCase_Name_##test_group##_##test_case_name##_Class

#define XNELO_TEST_CASE(testCaseName, testName)\
  class XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName) : public XNELO::TESTING::Test \
	{ \
	public: \
		XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName)() : XNELO::TESTING::Test (#testCaseName) \
		{ \
			XNELO::TESTING::TestMaster::GetInstance()->AddTest(this); \
		} \
        void Run(); \
	} \
    XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName)Instance; \
	void XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName)::Run ()

#endif //___XNELO_TESTING_Testing_H__2014___

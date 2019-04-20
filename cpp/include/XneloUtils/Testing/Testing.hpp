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

#ifndef ___XNELO__TESTING_TESTING_HPP__4_7_2019___
#define ___XNELO__TESTING_TESTING_HPP__4_7_2019___

#include "TestResult.hpp"
#include "TestMaster.hpp"
#include "Test.hpp"

#include <string>
#include <sstream>
/*
namespace XNELO
{
	namespace TEST
	{
		template<typename T>
		inline bool AssertEqual(T condition, T expected, std::string description)
		{
			//TestResult * result;
			//result = new TestResult((condition == expected),
			//						description);
			TestResult result((condition == expected), description);

			XNELO::TEST::TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(&result);

			return result.GetPassed();
		}

		template<typename T>
		inline bool AssertNotEqual(T expression1, T expression2, std::string description)
		{
			//TestResult * result;
			//result = new TestResult((expression1 != expression2),
			//						description);
			TestResult result((expression1 != expression2), description);

			XNELO::TEST::TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(&result);

			return result.GetPassed();
		}

		inline bool AssertFalse(bool booleanValue, std::string description)
		{
			return AssertEqual<bool>(booleanValue, false, description);
		}

		inline bool AssertTrue(bool booleanValue, std::string description)
		{
			return AssertEqual<bool>(booleanValue, true, description);
		}
	} //!TEST
} //!XNELO
*/
//Define the macros for this library
#define XNELO_TEST_ASSERT_EQUAL(condition, expected, description) \
	if (!AssertEqual(condition, expected, description)) \
	{\
		std::ostringstream oss; \
		oss << __FILE__ << "(Line: " << __LINE__ << ")"; \
		XNELO::TEST::TestMaster::GetInstance()->GetReportGenerator()->PrintAdditionalString(oss.str()); \
	}

#define XNELO_TEST_ASSERT_NOT_EQUAL(condition, expected, description) \
	if (!AssertNotEqual(condition, expected, description)) \
	{\
		std::ostringstream oss; \
		oss << __FILE__ << "(Line: " << __LINE__ << ")"; \
		XNELO::TEST::TestMaster::GetInstance()->GetReportGenerator()->PrintAdditionalString(oss.str()); \
	}

#define XNELO_TEST_ASSERT_TRUE(booleanValue, description) \
	XNELO_TEST_ASSERT_EQUAL(booleanValue, true, description)

#define XNELO_TEST_ASSERT_FALSE(booleanValue, description) \
	XNELO_TEST_ASSERT_EQUAL(booleanValue, false, description)


/// <summary>
/// This macro will create a Testcase's class name with an instance at the end.
/// </summary>
#define XNELO_CREATE_TESTCASE_CLASS_NAME_INSTANCE(test_group, test_case_name, instance) \
	TestCase_Name_##test_group##_##test_case_name##_Class##instance

/// <summary> 
/// This macro will call the XNELO_CREATE_TESTCASE_CLASS_NAME_INSTANCE macro with a blank as the 
/// Instance argument.
/// </summary>
#define XNELO_CREATE_TESTCASE_CLASS_NAME(test_group, test_case_name)\
	XNELO_CREATE_TESTCASE_CLASS_NAME_INSTANCE(test_group, test_case_name, )

#define XNELO_TEST_CASE(testCaseName, testName)\
	class XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName) : public XNELO::TEST::Test \
	{ \
	public: \
		XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName)() : XNELO::TEST::Test (#testCaseName) \
		{ \
			XNELO::TEST::TestMaster::GetInstance()->AddTest(this); \
		} \
		void Run(); \
	} XNELO_CREATE_TESTCASE_CLASS_NAME_INSTANCE(testCaseName, testName, Instance); \
	void XNELO_CREATE_TESTCASE_CLASS_NAME(testCaseName, testName)::Run ()

#endif // !___XNELO__TESTING_TESTING_HPP__4_7_2019___
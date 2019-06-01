/// <file> Testing.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary>
/// This defines the public interface for the Testing section of XneloUtils. 
/// 
/// ONLY INCLUDE THIS FILE.
/// 
/// This file will expose all the needed classes, structures, and macros. Any other files are for 
/// internal implementation only.
/// </summary>
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

#ifndef ___XNELO__TESTING_TESTING_HPP__4_7_2019___
#define ___XNELO__TESTING_TESTING_HPP__4_7_2019___

#include "TestMaster.hpp"
#include "Test.hpp"

#include <string>
#include <sstream>

//Define the macros for this library
/// <summary>
/// 
/// </summary>
/// <remarks>
/// This must only be called from within a <see cref="XNELO_TEST_CASE"/> definition or from an 
/// instance of a <see cref="TEST"/> class.
/// </remarks>
#define XNELO_TEST_ASSERT_EQUAL(condition, expected, description) \
	if (!AssertEqual(condition, expected, description)) \
	{\
		std::ostringstream oss; \
		oss << __FILE__ << "(Line: " << __LINE__ << ")"; \
		if (m_ReportGenerator != NULL) \
			m_ReportGenerator->PrintLine(oss.str()); \
	}

#define XNELO_TEST_ASSERT_NOT_EQUAL(condition, expected, description) \
	if (!AssertNotEqual(condition, expected, description)) \
	{\
		std::ostringstream oss; \
		oss << __FILE__ << "(Line: " << __LINE__ << ")"; \
		if (m_ReportGenerator != NULL) \
			m_ReportGenerator->PrintLine(oss.str()); \
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

#define XNELO_TEST_CASE(testGroupName, testName)\
	class XNELO_CREATE_TESTCASE_CLASS_NAME(testGroupName, testName) : public XNELO::TEST::Test \
	{ \
	public: \
		XNELO_CREATE_TESTCASE_CLASS_NAME(testGroupName, testName)() : XNELO::TEST::Test (#testGroupName, #testName) \
		{ \
			XNELO::TEST::TestMaster::GetInstance()->AddTest(this); \
		} \
		void Run(); \
	} XNELO_CREATE_TESTCASE_CLASS_NAME_INSTANCE(testGroupName, testName, Instance); \
	void XNELO_CREATE_TESTCASE_CLASS_NAME(testGroupName, testName)::Run ()


#endif // !___XNELO__TESTING_TESTING_HPP__4_7_2019___

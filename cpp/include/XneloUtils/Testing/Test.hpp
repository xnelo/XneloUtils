/// <file> Test.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary>  </summary>
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

#ifndef ___XNELO_TEST_TEST_H__4_13_2019___
#define ___XNELO_TEST_TEST_H__4_13_2019___

#include "../Config.hpp"
#include "../Core/BasicTypes.hpp"
#include "IReportGenerator.hpp"
#include "TestResult.hpp"

#include <string>
#include <vector>

namespace XNELO
{
	namespace TEST
	{
		class Test
		{
		protected:
			IReportGenerator * m_ReportGenerator;
		private:
			
			XNELO::CORE::uint32 m_AssertsFailed;
			XNELO::CORE::uint32 m_AssertsPassed;
			XNELO::CORE::uint32 m_AssertsRun;
			std::string m_TestGroup;
			std::string m_TestName;
			std::vector<TestResult*> m_TestResults;
		public:
			/// <summary>
			/// Constructor
			/// </summary>
			/// 
			/// <param name="test_group">The test group this test belongs to.</param>
			/// <param name="test_name">The name of this test.</param>
			XNELO_API Test(std::string test_group, std::string test_name);

			/// <summary>
			/// Destructor.
			/// </summary>
			XNELO_API ~Test();

			/// <summary>
			/// Check that the two passed in esxpressions are equal.
			/// </summary>
			/// <param name="expression1">First value to check.</param>
			/// <param name="expression2">Second value to Check.</param>
			/// <param name="description">The description associated with this check.</param>
			/// <returns>True if the two values are equal. False if they are NOT equal.</returns>
			template<typename T>
			XNELO_API bool AssertEqual(T expression1, T expression2, std::string description);

			/// <summary>
			/// Check that the two passed in expressions are NOT equal
			/// </summary>
			/// <param name="expression1">First value to check.</param>
			/// <param name="expression2">Second Value to Check.</param>
			/// <param name="description">The description associated with this check.</param>
			/// <returns>True if the two value are NOT equal. False if they ARE equal.</returns>
			template<typename T>
			XNELO_API bool AssertNotEqual(T expression1, T expression2, std::string description);

			/// <summary>
			/// Get the number of tests (executed in the Run function), that failed. This value 
			/// will not be valid unless <see cref="Run()"> has been executed.
			/// </summary>
			/// 
			/// <returns>An integer with the number of failed tests.</returns>
			XNELO_API int GetAssertsFailed();

			/// <summary>
			/// Get the number of tests (exectued in the Run function), that succeeded. This value
			/// will not be valid unless <see cref="Run()"> has been executed.
			/// </summary>
			/// 
			/// <returns>An integer with the number of succeeded tests.</returns>
			XNELO_API int GetAssertsPassed();

			/// <summary>
			/// Get the number of tests (executed in the Run function). This value will not be 
			/// valid unless <see cref="Run()"/> has been executed.
			/// </summary>
			/// <returns>An unsigned int (32 bit) with the number of run tests.</returns>
			XNELO_API int GetAssertsRun();

			/// <summary>
			/// Get the name of the test group this test belongs to.
			/// </summary>
			/// <returns></returns>
			XNELO_API std::string GetTestGroupName();

			/// <summary> 
			/// Get the name of this test.
			/// </summary>
			/// 
			/// <returns>A string with the test name.</returns>
			XNELO_API std::string GetTestName();

			/// <summary>
			/// This defines the code that this test will run. When this is called the tests will
			/// execute and failures and successes will be tallied.
			/// </summary>
			XNELO_API virtual void Run() = 0;

			/// <summary>
			/// Set the report generator for this test to use.
			/// </summary>
			/// <param name="newReportGen">The report generator to use.</param>
			XNELO_API void SetReportGenerator(IReportGenerator * newReportGen);
		};
	}// !TEST
}// !XNELO

inline XNELO::TEST::Test::Test(std::string test_group, std::string test_name) :
	m_ReportGenerator(NULL),
	m_AssertsFailed(0),
	m_AssertsPassed(0),
	m_AssertsRun(0),
	m_TestGroup(test_group),
	m_TestName(test_name),
	m_TestResults()
{ }

inline XNELO::TEST::Test::~Test()
{
	for (std::vector<TestResult*>::iterator it = m_TestResults.begin();
	it != m_TestResults.end();
		++it)
	{
		delete (*it);
	}

	m_TestResults.clear();

	m_TestGroup = "";
	m_TestName = "";
	m_AssertsPassed = 0;
	m_AssertsFailed = 0;
	m_AssertsRun = 0;
	m_ReportGenerator = NULL;
}

template<typename T>
inline bool XNELO::TEST::Test::AssertEqual(T expression1, T expression2, std::string description)
{
	++m_AssertsRun;

	TestResult * result = new TestResult((expression1 == expression2), description);

	if (result->Passed())
		++m_AssertsPassed;
	else
		++m_AssertsFailed;

	m_TestResults.push_back(result);

	if (m_ReportGenerator != NULL)
		m_ReportGenerator->PrintTestResult(result);

	return result->Passed();
}

template<typename T>
inline bool XNELO::TEST::Test::AssertNotEqual(T expression1, T expression2, std::string description)
{
	++m_AssertsRun;

	TestResult * result = new TestResult((expression1 != expression2), description);

	if (result->Passed())
		++m_AssertsPassed;
	else
		++m_AssertsFailed;

	m_TestResults.push_back(result);
	if (m_ReportGenerator != NULL)
		m_ReportGenerator->PrintTestResult(result);

	return result->Passed();
}

inline int XNELO::TEST::Test::GetAssertsFailed()
{
	return m_AssertsFailed;
}

inline int XNELO::TEST::Test::GetAssertsPassed()
{
	return m_AssertsPassed;
}

inline int XNELO::TEST::Test::GetAssertsRun()
{
	return m_AssertsRun;
}

inline std::string XNELO::TEST::Test::GetTestGroupName()
{
	return m_TestGroup;
}

inline std::string XNELO::TEST::Test::GetTestName()
{
	return m_TestName;
}

inline void XNELO::TEST::Test::SetReportGenerator(IReportGenerator * newReportGen)
{
	m_ReportGenerator = newReportGen;
}

#endif // !___XNELO_TEST_TEST_H__4_13_2019___

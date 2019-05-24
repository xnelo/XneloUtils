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
#include "TestResult.hpp"
#include "TestMaster.hpp" // Circular Dependency

#include <string>
#include <vector>

namespace XNELO
{
	namespace TEST
	{
		//forward declaration
		class TestMaster;

		class Test
		{
		private:
			std::string m_TestGroup;
			std::string m_TestName;
			std::vector<TestResult*> m_TestResults;
			XNELO::CORE::uint32 m_Failed;
			XNELO::CORE::uint32 m_Success;
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

			template<typename T>
			XNELO_API bool AssertEqual(T expression1, T expression2, std::string description);
			XNELO_API bool AssertFalse(bool booleanValue, std::string description);
			template<typename T>
			XNELO_API bool AssertNotEqual(T expression1, T expression2, std::string description);
			XNELO_API bool AssertTrue(bool booleanValue, std::string description);

			/// <summary>
			/// Get the number of tests (executed in the Run function), that failed. This value 
			/// will not be valid unless <see cref="Run()"> has been executed.
			/// </summary>
			/// 
			/// <returns>An integer with the number of failed tests.</returns>
			XNELO_API int GetNumFailed();

			/// <summary>
			/// Get the number of tests (exectued in the Run function), that succeeded. This value
			/// will not be valid unless <see cref="Run()"> has been executed.
			/// </summary>
			/// 
			/// <returns>An integer with the number of succeeded tests.</returns>
			XNELO_API int GetNumSuccess();

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
		};
	}// !TEST
}// !XNELO

template<typename T>
inline bool XNELO::TEST::Test::AssertEqual(T expression1, T expression2, std::string description)
{
	TestResult * result = new TestResult((expression1 == expression2), description);

	if (result->GetPassed())
		++m_Success;
	else
		++m_Failed;

	m_TestResults.push_back(result);

	TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(result);

	return result->GetPassed();
}

template<typename T>
inline bool XNELO::TEST::Test::AssertNotEqual(T expression1, T expression2, std::string description)
{
	TestResult * result = new TestResult((expression1 != expression2), description);

	if (result->GetPassed())
		++m_Success;
	else
		++m_Failed;

	m_TestResults.push_back(result);

	TestMaster::GetInstance()->GetReportGenerator()->PrintTestResult(result);

	return result->GetPassed();
}

inline int XNELO::TEST::Test::GetNumFailed()
{
	return m_Failed;
}

inline int XNELO::TEST::Test::GetNumSuccess()
{
	return m_Success;
}

inline std::string XNELO::TEST::Test::GetTestGroupName()
{
	return m_TestGroup;
}

inline std::string XNELO::TEST::Test::GetTestName()
{
	return m_TestName;
}

#endif // !___XNELO_TEST_TEST_H__4_13_2019___
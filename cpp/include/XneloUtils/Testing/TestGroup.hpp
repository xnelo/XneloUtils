#pragma region Copyright 2019 Spencer Hoffa
/// <file> TestGroup.hpp </file>
/// <author> Spencer Hoffa </author>
///
/// <copyright> 2019 Spencer Hoffa </copyright>
/// 
/// <summary>
/// </summary>
/// 
/// <license>
/// The zlib/libpng License
/// Copyright(c) 2019 Spencer Hoffa
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is granted to anyone to use this software for any purpose,
///including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions :
///
///		1. The origin of this software must not be misrepresented; you must not
///		claim that you wrote the original software.If you use this software in
///		a product, an acknowledgment in the product documentation would be
///		appreciated but is not required.
///
///		2. Altered source versions must be plainly marked as such, and must not
///		be misrepresented as being the original software.
///
///		3. This notice may not be removed or altered from any source
///		distribution.
///
/// This liscense can also be found at : http ://opensource.org/licenses/Zlib
/// </license>
#pragma endregion

#ifndef ___XNELO_TESTING_TESTGROUP_HPP__5_24_2019___
#define ___XNELO_TESTING_TESTGROUP_HPP__5_24_2019___

#include "../Config.hpp"

#include "IReportGenerator.hpp"
#include "Test.hpp"

#include <string>
#include <vector>

namespace XNELO
{
	namespace TEST
	{
		class TestGroup
		{
		private:
			// Statistic variables
			XNELO::CORE::uint32 m_AssertsFailed;
			XNELO::CORE::uint32 m_AssertsPassed;
			XNELO::CORE::uint32 m_AssertsRun;
			XNELO::CORE::uint32 m_TestsFailed;
			XNELO::CORE::uint32 m_TestsPassed;
			XNELO::CORE::uint32 m_TestsRun;
			// -------------------
			IReportGenerator * m_ReportGenerator;
			std::string m_TestGroupName;
			std::vector<Test*> m_Tests;
		public:
			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="groupName">The name of this group.</param>
			XNELO_API TestGroup(std::string groupName);

			/// <summary>
			/// Destructor
			/// </summary>
			XNELO_API virtual ~TestGroup();

			/// <summary>
			/// Add a test to this test group.
			/// </summary>
			/// <remarks>This class does not delete any passed in pointers.</remarks>
			/// <param name="newTest">The test to add.</param>
			XNELO_API void AddTest(Test * newTest);

			XNELO_API XNELO::CORE::uint32 GetAssertsFailed();
			XNELO_API XNELO::CORE::uint32 GetAssertsPassed();
			XNELO_API XNELO::CORE::uint32 GetAssertsRun();

			/// <summary>
			/// Get the name of the group.
			/// </summary>
			/// <returns>A string with the name of the group.</returns>
			XNELO_API std::string GetGroupName();

			/// <summary>
			/// Get the number of tests failed.
			/// </summary>
			/// <returns>An unsigned integer (32 bit) of number of tests that failed.</returns>
			XNELO_API XNELO::CORE::uint32 GetTestCasesFailed();

			/// <summary>
			/// Get the number of tests passed.
			/// </summary>
			/// <returns>An unsigned integer (32 bit) of number of tests that passed.</returns>
			XNELO_API XNELO::CORE::uint32 GetTestCasesPassed();

			/// <summary>
			/// Get the number of tests run.
			/// </summary>
			/// <returns>An unsigned integer (32 bit) of number of tests run.</returns>
			XNELO_API XNELO::CORE::uint32 GetTestCasesRun();

			/// <summary>
			/// Run all the tests this group contains.
			/// </summary>
			XNELO_API void RunAllTests();

			/// <summary>
			/// Set the report generator for this group to use.
			/// </summary>
			/// <remarks>NULL is a valid value.</remarks>
			/// <param name="gen">The generator to use.</param>
			XNELO_API void SetReportGenerator(IReportGenerator * gen);
		};
	} // !TEST
} // !XNELO

inline XNELO::TEST::TestGroup::TestGroup(std::string groupName) : 
	m_AssertsFailed(0),
	m_AssertsPassed(0),
	m_AssertsRun(0),
	m_TestsFailed(0),
	m_TestsPassed(0),
	m_TestsRun(0),
	m_ReportGenerator(NULL), 
	m_TestGroupName(groupName), 
	m_Tests()
{ }

inline XNELO::TEST::TestGroup::~TestGroup()
{ 
	m_TestGroupName = "";
	m_Tests.clear();
	m_ReportGenerator = NULL;
}

inline void XNELO::TEST::TestGroup::AddTest(Test * newTest)
{
	if (newTest != NULL)
	{
		m_Tests.push_back(newTest);
	}
}

inline XNELO::CORE::uint32 XNELO::TEST::TestGroup::GetAssertsFailed() 
{
	return m_AssertsFailed;
}

inline XNELO::CORE::uint32 XNELO::TEST::TestGroup::GetAssertsPassed()
{
	return m_AssertsPassed;
}

inline XNELO::CORE::uint32 XNELO::TEST::TestGroup::GetAssertsRun()
{
	return m_AssertsRun;
}

inline std::string XNELO::TEST::TestGroup::GetGroupName()
{
	return m_TestGroupName;
}

inline XNELO::CORE::uint32 XNELO::TEST::TestGroup::GetTestCasesFailed()
{
	return m_TestsFailed;
}

inline XNELO::CORE::uint32 XNELO::TEST::TestGroup::GetTestCasesPassed()
{
	return m_TestsPassed;
}

inline XNELO::CORE::uint32 XNELO::TEST::TestGroup::GetTestCasesRun()
{
	return m_TestsRun;
}

inline void XNELO::TEST::TestGroup::RunAllTests()
{
	m_TestsFailed = m_TestsPassed = m_TestsRun = 0;

	for (std::vector<Test*>::iterator it = m_Tests.begin();
			it != m_Tests.end(); 
			++it)
	{
		if (m_ReportGenerator != NULL)
			m_ReportGenerator->StartTestCase(*it);

		++m_TestsRun;

		(*it)->SetReportGenerator(m_ReportGenerator);
		(*it)->Run();

		if ((*it)->GetAssertsFailed() > 0)
			++m_TestsFailed;
		else
			++m_TestsPassed;

		// update stats
		m_AssertsFailed += (*it)->GetAssertsFailed();
		m_AssertsPassed += (*it)->GetAssertsPassed();
		m_AssertsRun += (*it)->GetAssertsRun();

		if (m_ReportGenerator != NULL)
			m_ReportGenerator->EndTestCase(*it);
	}
}

inline void XNELO::TEST::TestGroup::SetReportGenerator(IReportGenerator * gen)
{
	m_ReportGenerator = gen;
}

#endif // ! ___XNELO_TESTING_TESTGROUP_HPP__5_24_2019___

// <file> TestMaster.hpp </file>
// <author> Spencer Hoffa </author>
//
// <copyright> 2019 Spencer Hoffa </copyright>
//
// <summary>
// Main file to run all the test cases for the XneloUtils library.
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
// 		1. The origin of this software must not be misrepresented; you must not
// 		claim that you wrote the original software. If you use this software in
// 		a product, an acknowledgment in the product documentation would be
// 		appreciated but is not required.
//
// 		2. Altered source versions must be plainly marked as such, and must not
// 		be misrepresented as being the original software.
//
// 		3. This notice may not be removed or altered from any source
// 		distribution.
//
// This liscense can also be found at: http://opensource.org/licenses/Zlib
// </license>

#ifndef ___XNELO_TEST_TESTMASTER_HPP__4_9_2019___
#define ___XNELO_TEST_TESTMASTER_HPP__4_9_2019___

#include "../Config.hpp"
#include "IReportGenerator.hpp"
#include "TestingStatistics.hpp"

#include <map>
#include <string>

namespace XNELO
{
	namespace TEST
	{
		//forward declaration
		class Test;
		class TestGroup;

		class TestMaster
		{
		private:
			IReportGenerator * m_OutputGenerator;
			TestingStatistics m_Stats;
			std::map<std::string, TestGroup*> m_TestGroups;

		public:
			/// <summary>
			/// Get the single instance of the TestMaster class and return a pointer to it.
			/// </summary>
			/// <returns>A pointer to the TestMaster singleton.</returns>
			XNELO_API static TestMaster * GetInstance();

			/// <summary> 
			/// Destroy the Test Master object.
			/// </summary>
			XNELO_API ~TestMaster();

			/// <summary> 
			/// Add a new test that will be run when the <see cref="RunAllTest()"/> method is 
			/// called. This class will not delete they pointer. You are required to do that.
			/// </summary>
			/// 
			/// <param name="newTest">The test to be added.</param>
			XNELO_API void AddTest(Test * newTest);

			/// <summary> 
			/// Run all the tests that have been added.
			/// </summary>
			XNELO_API void RunAllTests();

			/// <summary>
			/// Run all the tests in the specified group name.
			/// </summary>
			/// <param name="groupName">The name of the group to execute tests for.</param>
			XNELO_API void RunGroupTests(std::string groupName);
		private:
			/// <summary>
			/// Constructor
			/// </summary>
			XNELO_API TestMaster();

			/// <summary>
			/// Reset testing statistics
			/// </summary>
			/// <returns></returns>
			XNELO_API void ResetStats();

			/// <summary>
			/// Run all the tests in a specific group.
			/// </summary>
			/// <param name="grp">A pointer to a TestGroup object to run tests on.</param>
			XNELO_API void RunTestGroup(TestGroup * grp);
		};
	} // !TEST
} // !XNELO

inline void XNELO::TEST::TestMaster::ResetStats()
{
	m_Stats.TestCasesFailed =
		m_Stats.TestCasesPassed =
		m_Stats.TestCasesRun =
		m_Stats.TestGroupFailed =
		m_Stats.TestGroupPassed =
		m_Stats.TestGroupRun =
		m_Stats.TotalAssertsFailed = 
		m_Stats.TotalAssertsPassed = 
		m_Stats.TotalAssertsRun = 0;
}

#endif // !___XNELO_TEST_TESTMASTER_HPP__4_9_2019___

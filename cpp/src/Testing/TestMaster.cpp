// <file> TestMaster.cpp </file>
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

#include "XneloUtils/Testing/TestMaster.hpp"
#include "XneloUtils/Testing/OutStreamGenerator.hpp"
#include "XneloUtils/Testing/Test.hpp"
#include "XneloUtils/Testing/TestGroup.hpp"

#include <stdlib.h>

namespace XNELO
{
	namespace TEST	
	{
		// Static Methods -------------------------------------------------------------------------
		TestMaster * instance = NULL;

		void TestMasterExit()
		{
			if (instance != NULL)
			{
				delete instance;
				instance = NULL;
			}
		}

		TestMaster * TestMaster::GetInstance()
		{
			if (instance == NULL)
			{
				instance = new TestMaster();
				atexit(TestMasterExit);
			}

			return instance;
		}
		// !Static Methods ------------------------------------------------------------------------

		TestMaster::TestMaster() :
			m_OutputGenerator(NULL),
			m_TestGroups()
		{
			m_OutputGenerator = new OutStreamGenerator();
		}

		/// <summary> 
		/// Destroy the Test Master object.
		/// </summary>
		TestMaster::~TestMaster()
		{
			if (m_OutputGenerator != NULL)
			{
				delete m_OutputGenerator;
				m_OutputGenerator = NULL;
			}

			for (std::map<std::string, TestGroup*>::iterator it = m_TestGroups.begin();
			it != m_TestGroups.end();
				++it)
			{
				delete it->second;
			}
			m_TestGroups.clear();
		}

		/// <summary> 
		/// Add a new test that will be run when the <see cref="RunAllTest()"/> method is 
		/// called.
		/// </summary>
		/// 
		/// <param name="newTest">The test to be added.</param>
		void TestMaster::AddTest(Test * newTest)
		{
			if (newTest != NULL)
			{
				// add to appropriate group
				std::map<std::string, TestGroup*>::iterator it;
				it = m_TestGroups.find(newTest->GetTestGroupName());
				if (it != m_TestGroups.end())
				{
					(it->second)->AddTest(newTest);
				}
				else
				{
					TestGroup * newGroup = new TestGroup(newTest->GetTestGroupName());
					m_TestGroups[newTest->GetTestGroupName()] = newGroup;
					newGroup->AddTest(newTest);
				}
			}
		}

		void TestMaster::RunAllTests()
		{
			ResetStats();

			for (std::map<std::string, TestGroup*>::iterator it = m_TestGroups.begin();
					it != m_TestGroups.end();
					++it)
			{
				RunTestGroup(it->second);
			}

			m_OutputGenerator->FinalizeTestRun(&m_Stats);
		}

		void TestMaster::RunGroupTests(std::string groupName)
		{
			std::map<std::string, TestGroup*>::iterator it;
			it = m_TestGroups.find(groupName);
			if (it != m_TestGroups.end())
			{
				RunTestGroup(it->second);
			}
		}

		void TestMaster::RunTestGroup(TestGroup * grp)
		{
			++m_Stats.TestGroupRun;

			m_OutputGenerator->StartTestGroup(grp);
			grp->SetReportGenerator(m_OutputGenerator);
			grp->RunAllTests();

			// Update stats
			if (grp->GetTestCasesFailed() > 0)
				++m_Stats.TestGroupFailed;
			else
				++m_Stats.TestGroupPassed;

			m_Stats.TestCasesRun += grp->GetTestCasesRun();
			m_Stats.TestCasesFailed += grp->GetTestCasesFailed();
			m_Stats.TestCasesPassed += grp->GetTestCasesPassed();

			m_Stats.TotalAssertsFailed += grp->GetAssertsFailed();
			m_Stats.TotalAssertsPassed += grp->GetAssertsPassed();
			m_Stats.TotalAssertsRun += grp->GetAssertsRun();

			m_OutputGenerator->EndTestGroup(grp);
		}
	} // !TEST
} // !XNELO

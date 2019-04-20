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

#include <stdlib.h>

namespace XNELO
{
	namespace TEST	
	{
		TestMaster * instance = NULL;

		// Static Methods -------------------------------------------------------------------------
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

		TestMaster::TestMaster():
		m_AllTests(),
		m_OutputGenerator(NULL)
		{
			m_OutputGenerator = new OutStreamGenerator();
		}

		/// <summary> 
		/// Destroy the Test Master object.
		/// </summary>
		TestMaster::~TestMaster()
		{
			m_AllTests.clear();

			if (m_OutputGenerator != NULL)
			{
				delete m_OutputGenerator;
				m_OutputGenerator = NULL;
			}
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
				m_AllTests.push_back(newTest);
			}
		}

		// <summary> 
		/// Run all the tests that have been added.
		/// </summary>
		void TestMaster::RunAllTest()
		{
			int numberPassed = 0;
			int numberFailed = 0;

			for (std::vector<Test*>::iterator it = m_AllTests.begin(); it != m_AllTests.end(); ++it)
			{
				m_OutputGenerator->StartTestCase(*it);
				(*it)->Run();
				if ((*it)->GetNumFailed() > 0)
					++numberFailed; 
				else
					++numberPassed;

				m_OutputGenerator->EndTestCase(*it);
			}

			m_OutputGenerator->FinalizeTestRun(numberPassed, numberFailed);

			//this->PrintResults();
		}
	} // !TEST
} // !XNELO


/// <file> OutStreamGenerator.cpp </file>
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

#include "XneloUtils/Testing/OutStreamGenerator.hpp"
#include "XneloUtils/Testing/Test.hpp"
#include "XneloUtils/Testing/TestGroup.hpp"

#include <iostream>

namespace XNELO
{
	namespace TEST
	{
		std::string s_PassString = "[PASSED]";
		std::string s_FailString = "[FAILED]";
		std::string GetPassFailString(bool didFail)
		{
			if (didFail)
				return s_FailString;
			else
				return s_PassString;
		}

		OutStreamGenerator::OutStreamGenerator() : 
		IReportGenerator(&std::cout), 
		m_Indent("")
		{ }

		OutStreamGenerator::OutStreamGenerator(std::ostream * stream) : 
		IReportGenerator(stream), 
		m_Indent("")
		{ }

		OutStreamGenerator::~OutStreamGenerator()
		{}

		void OutStreamGenerator::EndTestCase(Test * test)
		{
			m_Indent = m_Indent.substr(0, m_Indent.size() - 3);

			// print test results
			(*m_Stream) << m_Indent << std::string(20, '-') << std::endl
				<< m_Indent << "Success: " << test->GetAssertsPassed() << std::endl 
				<< m_Indent << "Failed:  " << test->GetAssertsFailed() << std::endl 
				<< m_Indent << "RESULT: " << GetPassFailString(test->GetAssertsFailed() > 0) << std::endl
				<< std::endl;
		}

		void OutStreamGenerator::EndTestGroup(TestGroup * testGroup)
		{
			m_Indent = m_Indent.substr(0, m_Indent.size() - 3);

			// print group results
			(*m_Stream) << m_Indent << std::string(20, '*') << std::endl
				<< m_Indent << "Success: " << testGroup->GetTestCasesPassed() << std::endl
				<< m_Indent << "Failed:  " << testGroup->GetTestCasesFailed() << std::endl
				<< m_Indent << "RESULT: " << GetPassFailString(testGroup->GetTestCasesFailed() > 0) << std::endl //GetPassFailString(test->GetNumFailed() > 0) << std::endl
				<< std::endl;
		}

		void OutStreamGenerator::FinalizeTestRun(TestingStatistics * stats)
		{
			(*m_Stream) << std::endl << std::string(20, '=') << std::endl
				<< "Final Results" << std::endl
				<< std::endl
				<< "Test Groups Run:    " << stats->TestGroupRun << std::endl
				<< "Test Groups Pass:   " << stats->TestGroupPassed << std::endl
				<< "Test Groups Fail:   " << stats->TestGroupFailed << std::endl
				<< std::endl
				<< "Test Cases Run:     " << stats->TestCasesRun << std::endl
				<< "Test Cases Pass:    " << stats->TestCasesPassed << std::endl
				<< "Test Cases Fail:    " << stats->TestCasesFailed << std::endl
				<< std::endl
				<< "Total Asserts Run:  " << stats->TotalAssertsRun << std::endl
				<< "Total Asserts Pass: " << stats->TotalAssertsPassed << std::endl
				<< "Total Asserts Fail: " << stats->TotalAssertsFailed << std::endl
				<< std::endl
				<< "Results: " << GetPassFailString(stats->TestCasesFailed > 0) << std::endl
				<< std::endl;
		}

		/// <summary>
		/// Print a line of text to the file.
		/// </summary>
		/// <param name="to_print">The line to print.</param>
		void OutStreamGenerator::PrintLine(std::string to_print)
		{
			(*m_Stream) << m_Indent << to_print << std::endl;
		}

		void OutStreamGenerator::PrintTestResult(TestResult * result)
		{
			if (result == NULL)
				return;

			(*m_Stream) << m_Indent << result->GetDescription() << ": " << GetPassFailString(!result->Passed()) << std::endl;
		}

		void OutStreamGenerator::StartTestCase(Test * test)
		{
			(*m_Stream) << std::endl 
				<< m_Indent << test->GetTestName() << std::endl
				<< m_Indent << std::string(20, '-') << std::endl;
			
			m_Indent += "   ";
		}

		void OutStreamGenerator::StartTestGroup(TestGroup * testGroup)
		{
			(*m_Stream) << std::endl 
				<< testGroup->GetGroupName() << std::endl
				<< m_Indent << std::string(20, '=') << std::endl;
			
			m_Indent += "   ";
		}
	} // !TEST
} // !XNELO

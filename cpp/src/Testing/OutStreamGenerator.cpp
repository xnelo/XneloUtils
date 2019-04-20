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


#include <iostream>

namespace XNELO
{
	namespace TEST
	{
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
			//print test results
			(*m_Stream) << std::string(20, '-') << std::endl;

			(*m_Stream) << "Success: " << test->GetNumSuccess() << std::endl <<
				"Failed:  " << test->GetNumFailed() << std::endl <<
				"RESULT: " << (test->GetNumFailed() > 0 ? "[FAILED]" : "[PASSED]") << std::endl << std::endl;
				
			m_Indent = m_Indent.substr(0, m_Indent.size()-3);
		}

		void OutStreamGenerator::FinalizeTestRun(int runNumberSuccess, int runNumberFailures)
		{
			(*m_Stream) << std::endl << std::string(20, '=') << std::endl << 
				"Success: " << runNumberSuccess << std::endl <<
				"Failed: " << runNumberFailures << std::endl <<
				"All Tests: " << (runNumberFailures > 0 ? "[FAILED]" : "[PASSED]") << std::endl << std::endl;
		}

		void OutStreamGenerator::PrintAdditionalString(std::string to_print)
		{
			(*m_Stream) << m_Indent << to_print << std::endl;
		}

		void OutStreamGenerator::PrintTestResult(TestResult * result)
		{
			if (result == NULL)
				return;

			(*m_Stream) << m_Indent << result->GetName() << ": " << (result->GetPassed() ? "[PASSED]" : "[FAILED]") << std::endl;
		}

		void OutStreamGenerator::StartTestCase(Test * test)
		{
			(*m_Stream) << std::endl << test->GetTestName() << std::endl;
			(*m_Stream) << std::string(20, '-') << std::endl;
			m_Indent += "   ";
		}
	} // !TEST
} // !XNELO
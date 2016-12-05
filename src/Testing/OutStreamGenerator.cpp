/**
* @file OutStreamGenerator.cpp
* @author Spencer Hoffa
*
* @copyright 2014 Spencer Hoffa
*
* The implementation of the OutStreamGenerator class.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2014 Spencer Hoffa
* 
* This software is provided 'as-is', without any express or implied warranty. 
* In no event will the authors be held liable for any damages arising from the 
* use of this software.
*
* Permission is granted to anyone to use this software for any purpose, 
* including commercial applications, and to alter it and redistribute it 
* freely, subject to the following restrictions:
* 
*		1. The origin of this software must not be misrepresented; you must not 
*		claim that you wrote the original software. If you use this software in 
*		a product, an acknowledgment in the product documentation would be 
*		appreciated but is not required.
*
*		2. Altered source versions must be plainly marked as such, and must not 
*		be misrepresented as being the original software.
*
*		3. This notice may not be removed or altered from any source 
*		distribution.
*
* This liscense can also be found at: http://opensource.org/licenses/Zlib
*/

#include "XneloUtils/Testing/OutStreamGenerator.hpp"

#include <iostream>

namespace XNELO
{
	namespace TESTING
	{
		OutStreamGenerator::OutStreamGenerator() : IReportGenerator(&std::cout), _indent("")
		{
			return;
		}

		OutStreamGenerator::OutStreamGenerator(std::ostream * stream) : IReportGenerator(stream), _indent("")
		{
			return;
		}

		OutStreamGenerator::~OutStreamGenerator()
		{
			return;
		}

		void OutStreamGenerator::StartTestCase(Test * test)
		{
			(*_stream) << std::endl << test->GetTestName() << std::endl;
			(*_stream) << std::string(20, '-') << std::endl;
			_indent += "   ";
		}

		void OutStreamGenerator::EndTestCase(Test * test)
		{
			//print test results
			///*
			(*_stream) << std::string(20, '-') << std::endl;

			(*_stream) << "Success: " << test->GetNumSuccess() << std::endl <<
				"Failed:  " << test->GetNumFailed() << std::endl <<
				"RESULT: " << (test->GetNumFailed() > 0 ? "[FAILED]" : "[PASSED]") << std::endl << std::endl;
				//*/
			_indent = _indent.substr(0, _indent.size()-3);
		}

		void OutStreamGenerator::FinalizeTestRun(int runNumberSuccess, int runNumberFailures)
		{
			(*_stream) << std::endl << std::string(20, '=') << std::endl << 
				"Success: " << runNumberSuccess << std::endl <<
				"Failed: " << runNumberFailures << std::endl <<
				"All Tests: " << (runNumberFailures > 0 ? "[FAILED]" : "[PASSED]") << std::endl << std::endl;


		}

		void OutStreamGenerator::PrintAdditionalString(const char * to_print)
		{
			(*_stream) << _indent << to_print << std::endl;
		}

		void OutStreamGenerator::PrintTestResult(TestResult * result)
		{
			if (result == NULL)
				return;

			(*_stream) << _indent << result->name << ": " << (result->passed ? "[PASSED]" : "[FAILED]") << std::endl;
		}
	}//end namespace TESTING
}//end namespace XNELO

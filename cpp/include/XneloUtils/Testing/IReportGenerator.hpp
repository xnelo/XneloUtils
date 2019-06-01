/// <file> IReportGenerator.hpp </file>
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

#ifndef ___XNELO_TEST_IREPORTGENERATOR_HPP__4_16_2019___
#define ___XNELO_TEST_IREPORTGENERATOR_HPP__4_16_2019___

#include "../Config.hpp"
#include "TestResult.hpp"
#include "TestingStatistics.hpp"

#include <string>
#include <ostream>

namespace XNELO
{
	namespace TEST
	{
		//forward declaration
		class Test;
		class TestGroup;

		class IReportGenerator
		{
		protected:
			std::ostream * m_Stream;
		public:
			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="stream">The stream to print the text to.</param>
			XNELO_API IReportGenerator(std::ostream * stream);

			/// <summary>
			/// Descrutor
			/// </summary>
			XNELO_API virtual ~IReportGenerator();

			/// <summary>
			/// Print any data for the end of a test.
			/// </summary>
			/// <param name="test">The test to use.</param>
			XNELO_API virtual void EndTestCase(Test * test) = 0;

			/// <summary>
			/// Print any data for the end of a test group.
			/// </summary>
			/// <param name="testGroup">The test group to use.</param>
			XNELO_API virtual void EndTestGroup(TestGroup * testGroup) = 0;

			/// <summary>
			/// Print any data after all the tests are executed.
			/// </summary>
			/// <param name="stats">A pointer to the object that holds stats.</param>
			XNELO_API virtual void FinalizeTestRun(TestingStatistics * stats) = 0;

			/// <summary>
			/// Print a line of text to the file.
			/// </summary>
			/// <param name="to_print">The line to print.</param>
			XNELO_API virtual void PrintLine(std::string to_print) = 0;

			/// <summary>
			/// Print the results from a test.
			/// </summary>
			/// <param name="test_result">The test result to print.</param>
			XNELO_API virtual void PrintTestResult(TestResult * test_result) = 0;

			/// <summary>
			/// Print any data for the beginning of a test case
			/// </summary>
			/// <param name="test">The test to use.</param>
			XNELO_API virtual void StartTestCase(Test * test) = 0;

			/// <summary>
			/// Print any data for the beginning of a test group.
			/// </summary>
			/// <param name="testGroup">The test group to use.</param>
			XNELO_API virtual void StartTestGroup(TestGroup * testGroup) = 0;
		};
	} // !TEST
} // !XNELO

inline XNELO::TEST::IReportGenerator::IReportGenerator(std::ostream * stream): 
	m_Stream(stream)
{}

inline XNELO::TEST::IReportGenerator::~IReportGenerator()
{
	m_Stream = NULL;
}

#endif // !___XNELO_TEST_IREPORTGENERATOR_HPP__4_16_2019___

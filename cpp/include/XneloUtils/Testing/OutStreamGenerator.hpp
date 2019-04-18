/// <file> OutStreamGenerator.hpp </file>
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

#ifndef ___XNELO_TESTING_OUTSTREAMGENERATOR_HPP__4_17_2019___
#define ___XNELO_TESTING_OUTSTREAMGENERATOR_HPP__4_17_2019___

#include "../Config.hpp"

#include "IReportGenerator.hpp"

namespace XNELO
{
	namespace TEST
	{
		class OutStreamGenerator: public IReportGenerator
		{
		private:
			std::string m_Indent;
		public:
			XNELO_API OutStreamGenerator();

			XNELO_API OutStreamGenerator(std::ostream * stream);

			XNELO_API virtual ~OutStreamGenerator();

			XNELO_API virtual void StartTestCase(Test * test);

			XNELO_API virtual void EndTestCase(Test * test);

			XNELO_API virtual void FinalizeTestRun(int runNumberSuccess, int runNumberFailures);

			XNELO_API virtual void PrintAdditionalString(std::string to_print);

			XNELO_API virtual void PrintTestResult(TestResult * result);
		};
	} // !TEST
} // !XNELO

#endif //!___XNELO_TESTING_OUTSTREAMGENERATOR_HPP__4_17_2019___
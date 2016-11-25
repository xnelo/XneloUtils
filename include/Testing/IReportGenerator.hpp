/**
* @file IReportGenerator.hpp
* @author Spencer Hoffa
*
* @copyright 2014 Spencer Hoffa
*
* Defines the XNELO::TESTING::IReportGenerator interface class. This is an 
* interface from which all report generators should inherit.
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

#ifndef ___XNELO_TESTING_IReportGenerator_H__2014___
#define ___XNELO_TESTING_IReportGenerator_H__2014___

#include "Config.hpp"

#include "Testing/TestResult.hpp"
#include "Testing/Test.hpp"

#include <ostream>

namespace XNELO
{
	namespace TESTING
	{
		//forward declarations
		class Test;

		/**
		* Creates an Interface for all Report Generators.
		*/
		class IReportGenerator
		{
		protected:
			/**The stream we print results to.*/
			std::ostream * _stream;
		public:
			/**
			* Default Constructor
			*/
			IReportGenerator();

			/**
			* Constructor.
			*
			* @param stream A pointer to an std::ostream object where the output of 
			*			this report generator will go.
			*/
			IReportGenerator(std::ostream * stream);

			/**
			* Destructor.
			*/
			virtual ~IReportGenerator();

			virtual void StartTestCase(Test * test) = 0;

			virtual void EndTestCase(Test * test) = 0;

			virtual void FinalizeTestRun(int runNumberSuccess, int runNumberFailures) = 0;

			virtual void PrintTestResult(TestResult * test_result) = 0;

			virtual void PrintAdditionalString(const char * to_print) = 0;
		};
	}//end namespace TESTING
}//end namespace XNELO

inline XNELO::TESTING::IReportGenerator::IReportGenerator(): _stream(NULL)
{}

inline XNELO::TESTING::IReportGenerator::IReportGenerator(std::ostream * stream): _stream(stream)
{}

inline XNELO::TESTING::IReportGenerator::~IReportGenerator()
{
	_stream = NULL;
}

#endif //___XNELO_TESTING_IReportGenerator_H__2014___
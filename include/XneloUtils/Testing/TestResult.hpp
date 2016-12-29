/**
* @file Test_Result.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* This class holds the results of each individual tests. It holds the name of 
* the test and whether or not the test passed.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2016 Spencer Hoffa
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

#ifndef ___XNELO_TESTING_Test_Result_H__2014___
#define ___XNELO_TESTING_Test_Result_H__2014___


#include "../Config.hpp"

namespace XNELO
{
	namespace TESTING
	{
		/**
		* A class with the results of a test.
		*/
		class TestResult
		{
		public:
			/**If the test passed or falied. True if it passed false if not.*/
			bool passed;
			/**The name of the test that this result is from.*/
			char* name;

			/**
			* Default Constructor.
			*/
			XNELO_API TestResult();

			/**
			* Copy Constructor.
			*/
			XNELO_API TestResult(const TestResult & other);

			/**
			* Destructor.
			*/
			XNELO_API ~TestResult();

			/**
			* Assignment operator.
			*/
			XNELO_API TestResult& operator = (const TestResult & other);
		private:
			/**
			* Deep copy of the class.
			*
			* @param other The object to copy.
			*/
			XNELO_API void deepCopy(const TestResult & other);
		};
	}//end namespace TESTING
}//end namespace XNELO

#endif //___XNELO_TESTING_Test_Result_H__2014___
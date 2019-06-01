/// <file> TestResult.hpp </file>
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

#ifndef ___XNELO_TEST_TESTRESULT_HPP__4_16_2019___
#define ___XNELO_TEST_TESTRESULT_HPP__4_16_2019___

#include "../Config.hpp"
#include <string>

namespace XNELO
{
	namespace TEST
	{
		class TestResult
		{
		private:
			bool m_Passed;
			std::string m_Description;
		public:
			/// <summary>
			/// Constructor
			/// </summary>
			XNELO_API TestResult();

			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="passed">Is the result a success or failure.</param>
			/// <param name="description">The description of the test.</param>
			XNELO_API TestResult(bool passed, std::string description);

			/// <summary>
			/// Copy Constructor
			/// </summary>
			/// <param name="other">Instance to copy</param>
			XNELO_API TestResult(const TestResult & other);

			/// <summary>
			/// Descrutor
			/// </summary>
			XNELO_API ~TestResult();

			/// <summary>
			/// Assignment operator
			/// </summary>
			/// <param name="other">Instance to copy</param>
			/// <returns>A reference to the newyly created version.</returns>
			XNELO_API TestResult& operator = (const TestResult & other);

			/// <summary>
			/// Did is the result passing.
			/// </summary>
			/// <returns>
			/// A boolean. If true then the result was passed, if false the result is failed.
			/// </returns>
			XNELO_API bool Passed();

			/// <summary>
			/// Get the description of the test this result is for.
			/// </summary>
			/// <returns>A string with the test description this result is for.</returns>
			XNELO_API std::string GetDescription();
		private:
			/// <summary>
			/// Deep copy of the passed in instance to this instance.
			/// </summary>
			/// <param name="other">The instance to copy</param>
			XNELO_API void DeepCopy(const TestResult & other);
		};
	} // !TEST
} // !XNELO

inline XNELO::TEST::TestResult::TestResult(): 
m_Passed(false), m_Description("")
{}

inline XNELO::TEST::TestResult::TestResult(bool passed, std::string description): 
m_Passed(passed), m_Description(description)
{}

inline XNELO::TEST::TestResult::TestResult(const TestResult & other): 
m_Passed(false), m_Description(NULL)
{
	if (this != &other)
	{
		DeepCopy(other);
	}
}

inline XNELO::TEST::TestResult::~TestResult()
{}

inline XNELO::TEST::TestResult& XNELO::TEST::TestResult::operator = (const TestResult & other)
{
	if (this != &other)
	{
		DeepCopy(other);
	}

	return *this;
}

inline void XNELO::TEST::TestResult::DeepCopy(const TestResult & other)
{
	m_Description = other.m_Description;
	m_Passed = other.m_Passed;
}

inline bool XNELO::TEST::TestResult::Passed()
{
	return m_Passed;
}

inline std::string XNELO::TEST::TestResult::GetDescription()
{
	return m_Description;
}

#endif //!___XNELO_TEST_TESTRESULT_HPP__4_16_2019___

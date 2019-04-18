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
			std::string m_Name;
		public:
			XNELO_API TestResult();
			XNELO_API TestResult(bool passed, std::string name);
			XNELO_API TestResult(const TestResult & other);
			XNELO_API ~TestResult();

			XNELO_API TestResult& operator = (const TestResult & other);

			XNELO_API bool GetPassed();
			XNELO_API std::string GetName();

			XNELO_API void SetPassed(bool pass);
			XNELO_API void SetName(std::string name);
		private:
			XNELO_API void DeepCopy(const TestResult & other);
		};
	} // !TEST
} // !XNELO

inline XNELO::TEST::TestResult::TestResult(): 
m_Passed(false), m_Name("")
{}

inline XNELO::TEST::TestResult::TestResult(bool passed, std::string name): 
m_Passed(passed), m_Name(name)
{}

inline XNELO::TEST::TestResult::TestResult(const TestResult & other): 
m_Passed(false), m_Name(NULL)
{
	if (this != &other)
	{
		DeepCopy(other);
	}
}

inline XNELO::TEST::TestResult& XNELO::TEST::TestResult::operator = (const TestResult & other)
{
	if (this != &other)
	{
		DeepCopy(other);
	}

	return *this;
}

inline bool XNELO::TEST::TestResult::GetPassed()
{
	return m_Passed;
}

inline std::string XNELO::TEST::TestResult::GetName()
{
	return m_Name;
}

inline void XNELO::TEST::TestResult::SetPassed(bool pass)
{
	m_Passed = pass;
}

#endif //!___XNELO_TEST_TESTRESULT_HPP__4_16_2019___
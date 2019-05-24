/// <file> Test.cpp </file>
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

#include "XneloUtils/Testing/Test.hpp"

namespace XNELO
{
	namespace TEST
	{
		Test::Test(std::string test_group, std::string test_name):
			m_TestGroup(test_group),
			m_TestName(test_name), 
			m_Success(0), 
			m_Failed(0)
		{
		}

		Test::~Test()
		{
			for (std::vector<TestResult*>::iterator it = m_TestResults.begin(); 
				it != m_TestResults.end(); 
				++it)
			{
				delete (*it);
			}
			
			m_TestResults.clear();
			m_TestGroup = "";
			m_TestName = "";
			m_Success = 0;
			m_Failed = 0;
		}
	}// !TEST
}// !TEST
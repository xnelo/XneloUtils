#pragma region Copyright 2019 Spencer Hoffa
/// <file> TestingStatistics.hpp </file>
/// <author> Spencer Hoffa </author>
///
/// <copyright> 2019 Spencer Hoffa </copyright>
/// 
/// <summary>
/// </summary>
/// 
/// <license>
/// The zlib/libpng License
/// Copyright(c) 2019 Spencer Hoffa
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is granted to anyone to use this software for any purpose,
///including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions :
///
///		1. The origin of this software must not be misrepresented; you must not
///		claim that you wrote the original software.If you use this software in
///		a product, an acknowledgment in the product documentation would be
///		appreciated but is not required.
///
///		2. Altered source versions must be plainly marked as such, and must not
///		be misrepresented as being the original software.
///
///		3. This notice may not be removed or altered from any source
///		distribution.
///
/// This liscense can also be found at : http ://opensource.org/licenses/Zlib
/// </license>
#pragma endregion

#ifndef ___XNELO_TEST_TESTSTATISTICS_HPP__5_27_2019___
#define ___XNELO_TEST_TESTSTATISTICS_HPP__5_27_2019___

#include "XneloUtils/Core/BasicTypes.hpp"

namespace XNELO
{
	namespace TEST
	{
		struct TestingStatistics
		{
		public:
			// Test case stats
			XNELO::CORE::uint32 TestCasesFailed = 0;
			XNELO::CORE::uint32 TestCasesPassed = 0;
			XNELO::CORE::uint32 TestCasesRun = 0;

			// Test Group stats
			XNELO::CORE::uint32 TestGroupFailed = 0;
			XNELO::CORE::uint32 TestGroupPassed = 0;
			XNELO::CORE::uint32 TestGroupRun = 0;

			// Number of asserts
			XNELO::CORE::uint32 TotalAssertsFailed = 0;
			XNELO::CORE::uint32 TotalAssertsPassed = 0;
			XNELO::CORE::uint32 TotalAssertsRun = 0;
		};
	} // !TEST
} // !XNELO

#endif // !___XNELO_TEST_TESTSTATISTICS_HPP__5_27_2019___

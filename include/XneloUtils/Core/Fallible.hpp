/**
* @file Fallible.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define the Fallible class. This allows for easy way for classes to keep track, set, and read errors.
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

#ifndef ___XNELO_CORE_FALLIBLE__HPP__11_11_2016___
#define ___XNELO_CORE_FALLIBLE__HPP__11_11_2016___

#include "../Config.hpp"
#include "Errors.hpp"
#include <string>

namespace XNELO
{
	namespace CORE
	{
		class Fallible
		{
		private:
			XNELO::ERRORS::Error _error;
			std::string _errorMessage;
		public:
			XNELO_API Fallible();
			XNELO_API virtual ~Fallible();
			XNELO_API XNELO::ERRORS::Error GetErrorCode();
			XNELO_API std::string GetErrorMessage();
			XNELO_API bool IsOK();
			XNELO_API void SetError(XNELO::ERRORS::Error error, std::string message);
			XNELO_API void SetErrorCode(XNELO::ERRORS::Error error);
			XNELO_API void SetErrorMessage(std::string messge);
		};
	}//end namespace XNELO
} //end namespace XNELO
#endif //___XNELO_CORE_FALLIBLE__HPP__11_11_2016___

/**
* @file Fallible.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Implementation of Fallible class.
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

#include "XneloUtils/Core/Fallible.hpp"

namespace XNELO
{
	namespace CORE
	{
		Fallible::Fallible(): _error(XNELO::ERRORS::OK), _errorMessage("OK")
		{}

		Fallible::~Fallible()
		{}

		bool Fallible::IsOK()
		{
			return _error == XNELO::ERRORS::OK;
		}

		XNELO::ERRORS::Error Fallible::GetErrorCode()
		{
			return _error;
		}

		std::string Fallible::GetErrorMessage()
		{
		return _errorMessage;
		}

		void Fallible::SetError(XNELO::ERRORS::Error error, std::string message)
		{
			SetErrorCode(error);
			SetErrorMessage(message);
		}

		inline void XNELO::CORE::Fallible::SetErrorCode(XNELO::ERRORS::Error error)
		{
			_error = error;
		}

		inline void XNELO::CORE::Fallible::SetErrorMessage(std::string message)
		{
			_errorMessage = message;
		}
	}//end namespace CORE
}//end namespace XNELO

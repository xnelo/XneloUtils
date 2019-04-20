/// <file> Fallible.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> 
/// Define the Fallible class. This allows for easy way for classes to keep track, set, and read 
/// errors.
/// </summary>
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
			/**
			* Constructor
			*/
			XNELO_API Fallible();

			/**
			* Destructor
			*/
			XNELO_API virtual ~Fallible();

			/**
			* Get this classes current error code.
			*
			* @return An Error type with the error code of this class. The error type is a 
			* redefinition of an integer so that the error can be simplified into a number.
			*/
			XNELO_API XNELO::ERRORS::Error GetErrorCode();

			/**
			* Get the message with the error code.
			*
			* @return A string with the error message describing the current error. This should be
			* set to "OK" if there is no error.
			*/
			XNELO_API std::string GetErrorMessage();

			/**
			* Check to see if the class is OK, or there is no error.
			*
			* @return A boolean value that will be true if the error code is set to OK.
			*/
			XNELO_API bool IsOK();

			/**
			* Set the error code and message of the class. This should be used when an error occurs
			* to indicate that the class had an error occur. This is a method that combines setting 
			* the code and message into one function.
			*
			* @param error An Error type with the code for the error. The Error type is an integer
			* type so every error code should be associated with a number.
			* @param message A string describing the error that occured.
			*/
			XNELO_API void SetError(XNELO::ERRORS::Error error, std::string message);

			/**
			* The the error code for the class.
			*
			* @param error An error type that holds the number with the code.
			*/
			XNELO_API void SetErrorCode(XNELO::ERRORS::Error error);

			/**
			*
			*/
			XNELO_API void SetErrorMessage(std::string messge);
		};
	}//end namespace XNELO
} //end namespace XNELO
#endif //___XNELO_CORE_FALLIBLE__HPP__11_11_2016___

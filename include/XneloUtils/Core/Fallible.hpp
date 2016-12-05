/**
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

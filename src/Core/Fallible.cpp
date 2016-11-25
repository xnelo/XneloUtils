#include "Core/Fallible.hpp"

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

/**
*/
#ifndef ___XNELO_CORE_ERRORS__HPP__11_12_2016___
#define ___XNELO_CORE_ERRORS__HPP__11_12_2016___

#include "BasicTypes.hpp"

namespace XNELO
{
	namespace ERRORS
	{
		typedef XNELO::CORE::uint16 Error;
		
		const Error OK = 0;
		const Error PLATFORM_NOT_SUPPORTED = 1;
		const Error NETWORKING_FAILED_TO_INITIALIZE = 2;
		const Error FAILED_TO_CREATE_SOCKET = 3;
		const Error SOCKET_FAILED_TO_SEND_DATA = 4;
		const Error SOCKET_FAILED_TO_RECEIVE_DATA = 5;
	}//end namespace ERROR
}//end namespace XNELO

#endif //___XNELO_CORE_ERRORS__HPP__11_12_2016___

/**
* @file Errors.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define error types and errors to be used by the XneloUtils library.
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

#ifndef ___XNELO_CORE_ERRORS__HPP__11_12_2016___
#define ___XNELO_CORE_ERRORS__HPP__11_12_2016___

#include "BasicTypes.hpp"

namespace XNELO
{
	namespace ERRORS
	{
		/**Define an error type.*/
		typedef XNELO::CORE::uint16 Error;
		
		const Error OK = 0;
		const Error PLATFORM_NOT_SUPPORTED = 1;
		const Error NETWORKING_FAILED_TO_INITIALIZE = 2;
		const Error FAILED_TO_CREATE_SOCKET = 3;
		const Error SOCKET_FAILED_TO_SEND_DATA = 4;
		const Error SOCKET_FAILED_TO_RECEIVE_DATA = 5;
		const Error BUFFER_STREAM_WRITER_WRITE_FAILED_NULL_INPUT = 6;
		const Error BUFFER_STREAM_WRITER_WRITE_FAILED_INVALID_SIZE = 7;
		const Error BUFFER_TOO_SMALL = 8;
		const Error BUFFER_STREAM_READER_READ_FAILED_NULL_INPUT = 9;
		const Error BUFFER_STREAM_READER_READ_FAILED_INVALID_SIZE = 10;
		const Error BUFFER_STREAM_READER_NO_DATA = 11;
		const Error PACKET_POINTER_IS_NULL = 12;
		const Error PACKET_PROTOCOL_NUMBER_INCORRECT = 13;
		const Error ERROR_READING_DATA = 14;
		const Error PACKET_ERROR_NO_PACKET_MATCHING_TYPE = 15;
	}//end namespace ERROR
}//end namespace XNELO

#endif //___XNELO_CORE_ERRORS__HPP__11_12_2016___

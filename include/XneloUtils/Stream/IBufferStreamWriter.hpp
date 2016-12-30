/**
* @file IBufferStreamWriter.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define an interface for a buffered stream writer.
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

#ifndef ___XNELOUTILS_STREAM_IBUFFERSTREAMWRITER__HPP__12_8_2016___
#define ___XNELOUTILS_STREAM_IBUFFERSTREAMWRITER__HPP__12_8_2016___

#include "IBufferStream.hpp"

namespace XNELO
{
	namespace STREAM
	{
		class IBufferStreamWriter : public IBufferStream
		{
		public:
			static const bool IsWriting = true;
			static const bool IsReading = false;

			/**
			* Constructor
			*/
			XNELO_API IBufferStreamWriter();

			/**
			* Destructor
			*/
			XNELO_API virtual ~IBufferStreamWriter();

			/**
			* Get the internal buffer of data that has been written to this class so far.
			*
			* @return A pointer to the beginning of the data stored in this buffer.
			*/
			virtual char * GetBuffer() = 0;

			/**
			* Get the amount of data that has been written to this class.
			*
			* @return A uint32 variable with the number of bytes of data that has been written.
			*/
			virtual XNELO::CORE::uint32 GetSize() = 0;

			/**
			* Write data to this class' buffer.
			*
			* @param toWrite A void pointer to data to be written to this class.
			* @param sizeInBytes An integer with the number of bytes of data in the buffer to copy.
			*
			* @return An integer with the number of bytes of data that were actually copied.
			*/
			virtual int Write(const void * toWrite, int sizeInBytes) = 0;
		};
	} //end namespace STREAM
} //end namespace XNELO

#endif // ___XNELOUTILS_STREAM_ISTREAMWRITER__HPP__12_8_2016___

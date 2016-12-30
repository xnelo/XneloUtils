/**
* @file IBufferStreamReader.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define an interface class for a buffer stream reader class.
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

#ifndef ___XNELO_STREAM_IBUFFERSTREAMREADER_HPP__12_8_2016___
#define ___XNELO_STREAM_IBUFFERSTREAMREADER_HPP__12_8_2016___

#include "IBufferStream.hpp"

namespace XNELO
{
	namespace STREAM
	{
		class IBufferStreamReader : public IBufferStream
		{
		public:
			static const bool IsWriting = false;
			static const bool IsReading = true;

			/**
			* Constructor
			*/
			XNELO_API IBufferStreamReader();

			/**
			* Destructor
			*/
			XNELO_API virtual ~IBufferStreamReader();

			/**
			* Add Data to the buffer that is being read from.
			*
			* @param buffer A char buffer with data to add to the buffer being read from.
			* @param bufferSize An integer with the size of the buffer we are adding.
			*
			* @return A boolean value if the data was added successfully.
			*/
			virtual bool AddDataToBuffer(const char * buffer, int bufferSize) = 0;

			/**
			* How much data is left to be read from this stream.
			*
			* @return An integer with the number of bytes left to read.
			*/
			virtual int AmountLeft() = 0;

			/**
			* Read data from this class to the passed in buffer. The passed in buffer must be at
			* least the size that is passed into the 'readAmount' parameter.
			*
			* @param buffer A pointer to a chunk of memory to copy the data into.
			* @param readAmount An integer with the amount of data to read. The buffer passed into
			* the 'buffer' parameter must be at least as big as this value.
			*
			* @return An integer with the number of bytes that were successfully copied. Any return
			* value less than 0 is an error, and a return of 0 means no data was read/copied.
			*/
			virtual int Read(void * buffer, int readAmount) = 0;
		};
	}//end namespace STREAM
}//end namespace XNELO

#endif // !___XNELO_STREAM_ISTREAMREADER_HPP__12_8_2016___


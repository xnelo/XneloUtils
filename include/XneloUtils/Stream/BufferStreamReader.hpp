/**
* @file BufferStreamReader.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Defines a stream that you can read x number of bytes at a time.
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

#ifndef ___XNELOUTILS_STREAM_BUFFERSTREAMREADER_HPP__12_18_2016___
#define ___XNELOUTILS_STREAM_BUFFERSTREAMREADER_HPP__12_18_2016___

#include "IBufferStreamReader.hpp"
#include "XneloUtils\Core\Fallible.hpp"

namespace XNELO
{
	namespace STREAM
	{
		class BufferStreamReader : public XNELO::CORE::Fallible, IBufferStreamReader
		{
		private:
			char * _buffer;
			XNELO::CORE::uint32 _index;
			XNELO::CORE::uint32 _bufferSize;
		public:
			/**
			* Constructor
			*/
			XNELO_API BufferStreamReader();

			/**
			* Construtor with an initial amount of data to buffer then read from.
			*/
			XNELO_API BufferStreamReader(const char * buffer, int bufferSize);

			/**
			* Destructor
			*/
			XNELO_API virtual ~BufferStreamReader();

			/**
			* Add Data to the buffer that is being read from.
			*
			* @param buffer A char buffer with data to add to the buffer being read from.
			* @param bufferSize An integer with the size of the buffer we are adding.
			*
			* @return A boolean value if the data was added successfully.
			*/
			XNELO_API virtual bool AddDataToBuffer(const char * buffer, int bufferSize);

			/**
			* How much data is left to be read from this stream.
			*
			* @return An integer with the number of bytes left to read.
			*/
			XNELO_API virtual int AmountLeft();

			/**
			* Read data from this class to the passed in buffer. The passed in buffer must be at
			* least the size that is passed into the 'readAmount' parameter.
			*
			* @param buffer A pointer to a chunk of memory to copy the data into.
			* @param readAmount An integer with the amount of data to read. The buffer passed into
			* the 'buffer' parameter must be at least as big as this value.
			*
			* @return An integer with the number of bytes that were successfully copied. -1 is 
			* returned if the buffer passed in is NULL. -2 is returned if a value less than or 
			* equal to 0 is passed into readAmount variable. 0 is returned if no data is read.
			*/
			XNELO_API virtual int Read(void * buffer, int readAmount);

			/**
			* Get the buffer of data that is currently in this class. This function will return a 
			* pointer to the beginning of the buffer with the data in it.
			*
			* @return Return a char * pointer to the buffer of data.
			*/
			XNELO_API virtual char * GetBuffer();

			/**
			* Get the size of the internal buffer of data.
			*
			* @return A uint32 variable with the size of data in it.
			*/
			XNELO_API virtual XNELO::CORE::uint32 GetSize();
		};
	}//end namespace STEAM
}//end namespace XNELO

#endif // !___XNELOUTILS_STREAM_BUFFERSTREAMREADER_HPP__12_18_2016___

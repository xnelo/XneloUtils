/**
* @file BufferStreamWriter.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define a Stream class that you can write information to and it is stored in a buffer.
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

#ifndef ___XNELO_STREAM_BUFFERSTREAMWRITER_HPP__12_10_2016___
#define ___XNELO_STREAM_BUFFERSTREAMWRITER_HPP__12_10_2016___

#include "../Config.hpp"
#include "IBufferStreamWriter.hpp"
#include "../Core/Fallible.hpp"

namespace XNELO
{
	namespace STREAM
	{
		class BufferStreamWriter : public XNELO::CORE::Fallible, public IBufferStreamWriter
		{
		private:
			char * _buffer;
			XNELO::CORE::uint32 _bufferSize;
			XNELO::CORE::uint32 _bufferIndex;
			bool _autoExpand;
		public:
			/**
			* Constructor
			*/
			XNELO_API BufferStreamWriter();

			/**
			* Constructor with an initial buffersize.
			*
			* @param bufferSize A uint32 variable with the size of internal buffer to initially
			* create.
			*/
			XNELO_API BufferStreamWriter(XNELO::CORE::uint32 bufferSize);

			/**
			* Destructor
			*/
			XNELO_API ~BufferStreamWriter();

			/**
			* Get the internal buffer of data that has been written to this class so far.
			*
			* @return A pointer to the beginning of the data stored in this buffer.
			*/
			XNELO_API virtual char * GetBuffer();

			/**
			* Get the amount of data that has been written to this class.
			*
			* @return A uint32 variable with the number of bytes of data that has been written.
			*/
			XNELO_API virtual XNELO::CORE::uint32 GetSize();

			/**
			* Reset the class so that writing will begin at the beginning of the internal buffer;
			*/
			XNELO_API void Reset();

			/**
			* Reset the class so that writing will begin at the index specified by the parameter.
			*
			*@param index An unsigned integer of the index to reset the writer to.
			*/
			XNELO_API void Reset(XNELO::CORE::uint32 index);

			/**
			* Write data to this class' buffer. 
			*
			* @param toWrite A void pointer to data to be written to this class.
			* @param sizeInBytes An integer with the number of bytes of data in the buffer to copy.
			*
			* @return An integer with the number of bytes of data that were actually copied.
			*/
			XNELO_API virtual int Write(const void * toWrite, int sizeInBytes);
		private:
			XNELO_API void ExpandBuffer();

			//hide the copy constructor and assignment operator
			XNELO_API BufferStreamWriter(const BufferStreamWriter & other);
			XNELO_API BufferStreamWriter& operator = (const BufferStreamWriter & other);
		};
	}//end namespace STREAM
}// end namespace XNELO

inline void XNELO::STREAM::BufferStreamWriter::Reset()
{
	_bufferIndex = 0;
	SetError(XNELO::ERRORS::OK, "OK");
}

inline void XNELO::STREAM::BufferStreamWriter::Reset(XNELO::CORE::uint32 index)
{
	if (index >= _bufferSize)
		return;

	_bufferIndex = index;
	SetError(XNELO::ERRORS::OK, "OK");
}

#endif //___XNELO_STREAM_BUFFERSTREAMWRITER_HPP__12_10_2016___

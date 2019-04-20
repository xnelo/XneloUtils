/// <file> BufferStreamWriter.cpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary>  </summary>
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

#include "XneloUtils/Stream/BufferStreamWriter.hpp"

#include <cstring>

#define __XNELO_STREAM_DEFAULT_BUFFER_SIZE__ 1024

namespace XNELO
{
	namespace STREAM
	{
		BufferStreamWriter::BufferStreamWriter() : 
			Fallible(), 
			IBufferStreamWriter(), 
			_buffer(NULL), 
			_bufferSize(__XNELO_STREAM_DEFAULT_BUFFER_SIZE__),
			_bufferIndex(0),
			_autoExpand(true)
		{
			_buffer = new char[_bufferSize];
		}

		BufferStreamWriter::BufferStreamWriter(XNELO::CORE::uint32 bufferSize) :
			Fallible(),
			IBufferStreamWriter(),
			_buffer(NULL),
			_bufferSize(bufferSize),
			_bufferIndex(0),
			_autoExpand(true)
		{
			_buffer = new char[_bufferSize];
		}

		BufferStreamWriter::~BufferStreamWriter()
		{
			delete[] _buffer;
			_buffer = NULL;
		}

		char * BufferStreamWriter::GetBuffer()
		{
			return _buffer;
		}

		XNELO::CORE::uint32 BufferStreamWriter::GetSize()
		{
			return _bufferIndex;
		}

		int BufferStreamWriter::Write(const void * toWrite, int sizeInBytes)
		{
			if (toWrite == NULL)
			{
				SetError(XNELO::ERRORS::BUFFER_STREAM_WRITER_WRITE_FAILED_NULL_INPUT, 
					"Input buffer is NULL");
				return -1;
			}

			if (sizeInBytes <= 0)
			{
				SetError(XNELO::ERRORS::BUFFER_STREAM_WRITER_WRITE_FAILED_INVALID_SIZE, 
					"Input Size invalid");
				return -2;
			}

			if ((_bufferIndex + sizeInBytes) > _bufferSize)
			{
				if (_autoExpand)
				{
					ExpandBuffer();
				}
				else
				{
					SetError(XNELO::ERRORS::BUFFER_TOO_SMALL, "Buffer not big enough to write data");
					return -3;
				}
			}

			memcpy((_buffer + _bufferIndex), toWrite, sizeInBytes);
			_bufferIndex += sizeInBytes;

			SetError(XNELO::ERRORS::OK, "OK");
			return sizeInBytes;
		}

		void BufferStreamWriter::ExpandBuffer()
		{
			//create new buffer
			XNELO::CORE::uint32 newSize = _bufferSize * 2;
			char * newBuffer = new char[newSize];

			//copy old buffer
			memcpy(newBuffer, _buffer, _bufferSize);

			//delete old buffer
			delete[] _buffer;

			//set new as buffer;
			_buffer = newBuffer;
			_bufferSize = newSize;
		}
	}//end namespace STREAM
}// end namespace XNELO

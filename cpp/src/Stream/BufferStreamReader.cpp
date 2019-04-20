/// <file> BufferStreamReader.cpp </file>
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

#include "XneloUtils/Stream/BufferStreamReader.hpp"
#include <cstring>

namespace XNELO
{
	namespace STREAM
	{
		BufferStreamReader::BufferStreamReader(): Fallible(), IBufferStreamReader(), _buffer(NULL), _index(0), _bufferSize(0)
		{}

		BufferStreamReader::BufferStreamReader(const char * buffer, int bufferSize) :
			Fallible(),
			IBufferStreamReader(),
			_buffer(NULL),
			_index(0),
			_bufferSize(0)
		{
			AddDataToBuffer(buffer, bufferSize);
		}

		BufferStreamReader::~BufferStreamReader()
		{
			if (_buffer != NULL)
			{
				delete[] _buffer;
				_buffer = NULL;
			}

			_bufferSize = 0;
			_index = 0;
		}

		bool BufferStreamReader::AddDataToBuffer(const char * buffer, int bufferSize)
		{
			if (_buffer == NULL)
			{
				//create new buffer
				_buffer = new char[bufferSize];
				
				//copy data
				std::memcpy(_buffer, buffer, bufferSize);

				//set size and index
				_bufferSize = bufferSize;
				_index = 0;

				return true;
			}
			else
			{
				//create new buffer
				char * newBuffer = new char[_bufferSize + bufferSize];

				//copy old buffer to new buffer
				std::memcpy(newBuffer, _buffer, _bufferSize);

				//delete old buffer
				delete[] _buffer;

				//set old buffer to new buffer
				_buffer = newBuffer;

				//copy passed in buffer
				std::memcpy(_buffer + _bufferSize, buffer, bufferSize);

				//increase size
				_bufferSize += bufferSize;

				return true;
			}
		}

		int BufferStreamReader::AmountLeft()
		{
			return _bufferSize - _index;
		}

		char * BufferStreamReader::GetBuffer()
		{
			return _buffer;
		}

		XNELO::CORE::uint32 BufferStreamReader::GetSize()
		{
			return _bufferSize;
		}

		int BufferStreamReader::Read(void * buffer, int readAmount)
		{
			if (buffer == NULL)
			{
				SetError(XNELO::ERRORS::BUFFER_STREAM_READER_READ_FAILED_NULL_INPUT, "Copy To buffer is NULL.");
				return -1;
			}

			if (readAmount <= 0)
			{
				SetError(XNELO::ERRORS::BUFFER_STREAM_READER_READ_FAILED_INVALID_SIZE, "Read Amount is invalid. Must be greater than 0.");
				return -2;
			}

			if ((_buffer == NULL) || (_index >= _bufferSize))
			{
				SetError(XNELO::ERRORS::BUFFER_STREAM_READER_NO_DATA, "No Data to read.");
				return 0;
			}

			const char * ptr = _buffer;
			ptr += _index;

			int copyAmount = readAmount;

			if ((_index + readAmount) > _bufferSize)
				copyAmount = AmountLeft();

			std::memcpy(buffer, ptr, copyAmount);
			_index += copyAmount;

			SetError(XNELO::ERRORS::OK, "OK");

			return copyAmount;

			/*
			if ((_index + readAmount) <= _bufferSize)
			{
				//read requested amount
				std::memcpy(buffer, ptr, readAmount);
				_index += readAmount;

				return readAmount;
			}
			else
			{
				//read till end and return amount read
				int copyAmount = _bufferSize - _index;

				std::memcpy(buffer, ptr, copyAmount);
				_index = _bufferSize;

				return copyAmount;
			}
			//*/
		}
	}//namespace STREAM
}//namespace XNELO

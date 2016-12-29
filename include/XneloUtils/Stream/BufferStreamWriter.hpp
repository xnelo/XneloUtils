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
		class BufferStreamWriter : public XNELO::CORE::Fallible, IBufferStreamWriter
		{
		private:
			char * _buffer;
			XNELO::CORE::uint32 _bufferSize;
			XNELO::CORE::uint32 _bufferIndex;
			bool _autoExpand;
		public:
			XNELO_API BufferStreamWriter();
			XNELO_API BufferStreamWriter(XNELO::CORE::uint32 bufferSize);
			XNELO_API ~BufferStreamWriter();
			XNELO_API virtual char * GetBuffer();
			XNELO_API virtual XNELO::CORE::uint32 GetSize();
			XNELO_API virtual int Write(const void * toWrite, int sizeInBytes);
		private:
			XNELO_API void ExpandBuffer();

			//hide the copy constructor and assignment operator
			XNELO_API BufferStreamWriter(const BufferStreamWriter & other);
			XNELO_API BufferStreamWriter& operator = (const BufferStreamWriter & other);
		};
	}//end namespace STREAM
}// end namespace XNELO

#endif //___XNELO_STREAM_BUFFERSTREAMWRITER_HPP__12_10_2016___

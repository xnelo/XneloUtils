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
			XNELO_API BufferStreamReader();
			XNELO_API BufferStreamReader(const char * buffer, int bufferSize);
			XNELO_API virtual ~BufferStreamReader();
			XNELO_API virtual bool AddDataToBuffer(const char * buffer, int bufferSize);
			XNELO_API virtual int AmountLeft();
			XNELO_API virtual int Read(void * buffer, int readAmount);

			XNELO_API virtual char * GetBuffer();
			XNELO_API virtual XNELO::CORE::uint32 GetSize();
		};
	}//end namespace STEAM
}//end namespace XNELO

#endif // !___XNELOUTILS_STREAM_BUFFERSTREAMREADER_HPP__12_18_2016___

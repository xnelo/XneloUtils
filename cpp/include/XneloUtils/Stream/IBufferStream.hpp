/**
* @file IBufferStream.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define an interface for a streams that work on a buffer.
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

#ifndef ___XNELO_STREAM_IBUFFERSTREAM_HPP__12_8_2016___
#define ___XNELO_STREAM_IBUFFERSTREAM_HPP__12_8_2016___

#include "../Config.hpp"
#include "../Core/BasicTypes.hpp"

namespace XNELO
{
	namespace STREAM
	{
		class IBufferStream
		{
		public:
			//static const bool IsWriting; //<-+-- Subclasses should define these variables
			//static const bool IsReading; //<-+

			/**
			* Constructor
			*/
			IBufferStream();

			/**
			* Destructor
			*/
			virtual ~IBufferStream();

			/**
			* Get the internal buffer of data that this stream buffer contains.
			*
			* @return A pointer to the beginning of the data stored in this buffer.
			*/
			virtual char * GetBuffer() = 0;

			/**
			* Get the amount of data in bytes in the buffer of this class.
			*
			* @return A uint32 integer with the amount of data in the buffer.
			*/
			virtual XNELO::CORE::uint32 GetSize() = 0;
		};
	} //end namespace STREAM
} //end namespace XNELO

inline XNELO::STREAM::IBufferStream::IBufferStream() {}
inline XNELO::STREAM::IBufferStream::~IBufferStream() {}

#endif // ___XNELO_STREAM_ISTREAM_HPP__12_8_2016___


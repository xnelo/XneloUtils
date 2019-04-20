/// <file> IStreamReader.cpp </file>
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

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Stream/IBufferStreamReader.hpp"

class IBufferStreamReaderTestImpl : public XNELO::STREAM::IBufferStreamReader
{
public:
	IBufferStreamReaderTestImpl() : IBufferStreamReader()
	{}

	virtual char * GetBuffer() 
	{
		return NULL;
	}

	virtual XNELO::CORE::uint32 GetSize() 
	{
		return 0;
	}

	virtual bool AddDataToBuffer(const char * buffer, int bufferSize) 
	{
		return false;
	}

	virtual int AmountLeft() 
	{
		return 0;
	}

	virtual int Read(void * buffer, int readAmount) 
	{
		return 0;
	}
};

XNELO_TEST_CASE(IBufferStreamReaderTests, Constructors)
{
	XNELO::STREAM::IBufferStream * test = new IBufferStreamReaderTestImpl();

	XNELO_TEST_ASSERT_FALSE(test == NULL, "Constructor successful");

	delete test;
}

XNELO_TEST_CASE(IBufferStreamReaderTests, IsReadingValue)
{
	XNELO_TEST_ASSERT_TRUE(IBufferStreamReaderTestImpl::IsReading, "Make sure reader IsReading value is true");
}

XNELO_TEST_CASE(IBufferStreamReaderTests, IsWritingValue)
{
	XNELO_TEST_ASSERT_FALSE(IBufferStreamReaderTestImpl::IsWriting, "Make sure reader IsWriting value is false");
}

/// <file> XneloPacket.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> Defines a base class for all information received in a packet. </summary>
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

#ifndef ___XNELO_NETWORK_XNELOPACKET__HPP__02_08_2017___
#define ___XNELO_NETWORK_XNELOPACKET__HPP__02_08_2017___

#include "NetworkCore.hpp"
#include "../Core/BasicTypes.hpp"
#include "../Core/Errors.hpp"
#include "../Stream/IBufferStreamReader.hpp"
#include "../Stream/IBufferStreamWriter.hpp"
#include <string>

namespace XNELO
{
	namespace NETWORK
	{
		class XneloPacket
		{
		public:
			XNELO::CORE::uint32 protocolNumber;
			XNELO::CORE::uint32 sequenceNumber;
			XNELO::CORE::uint32 ackNumber;
			XNELO::CORE::uint32 ackBitmap;
			XNELO::CORE::uint16 packetType;
			//XNELO::CORE::uint32 dataSize;
			//XNELO::CORE::uint8 * data;

			//XNELO_API 
			XneloPacket();
			//XNELO_API 
			virtual ~XneloPacket();

			virtual XNELO::CORE::uint16 GetPacketType() = 0;
			virtual std::string GetPacketTypeString() = 0;

			virtual XNELO::ERRORS::Error ReadData(XNELO::STREAM::IBufferStreamReader * stream) = 0;
			virtual XNELO::ERRORS::Error WriteData(XNELO::STREAM::IBufferStreamWriter * stream) = 0;
		};
	}
}

inline XNELO::NETWORK::XneloPacket::XneloPacket() :
	protocolNumber(0),
	sequenceNumber(0),
	ackNumber(0),
	ackBitmap(0),
	packetType(0)//,
	//datasize(0),
	//data(NULL)
{}

inline XNELO::NETWORK::XneloPacket::~XneloPacket()
{
	//if (data != NULL)
	//{
	//	delete[] data;
	//	data = NULL;
	//}
}

#endif // !___XNELO_NETWORK_XNELOPACKET__HPP__02_08_2017___

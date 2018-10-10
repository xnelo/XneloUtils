/**
* @file PacketManager.hpp
* @author Spencer Hoffa
*
* @copyright 2017 Spencer Hoffa
*
* Manages packets for a program.
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

#ifndef ___XNELO_NETWORK_PACKETMANAGER_HPP__1_15_2017___
#define ___XNELO_NETWORK_PACKETMANAGER_HPP__1_15_2017___

#include "NetworkCore.hpp"
#include "XneloUtils/Core/BasicTypes.hpp"
#include "XneloUtils/Core/Errors.hpp"
#include "XneloUtils/Core/Fallible.hpp"
#include "XneloUtils/Stream/IBufferStreamWriter.hpp"
#include "XneloUtils/Stream/IBufferStreamReader.hpp"
#include "XneloPacket.hpp"
#include <list>
#include <vector>

#define NUMBER_OF_HISTORICAL_ENTRIES 33

namespace XNELO
{
	namespace NETWORK
	{
		class PacketManager: public XNELO::CORE::Fallible
		{
		private:
			struct SavePacketData
			{
				SavePacketData(XNELO::CORE::uint32 seqNum, XNELO::CORE::uint8 * data, XNELO::CORE::uint32 size)
					: sequenceNumber(seqNum), packetData(NULL), dataSize(size), acknowledged(false)
				{
					packetData = new XNELO::CORE::uint8[size];
					std::memcpy(packetData, data, size);
				}

				~SavePacketData()
				{
					delete[] packetData;
				}

				XNELO::CORE::uint32 sequenceNumber;
				XNELO::CORE::uint8 * packetData;
				XNELO::CORE::uint32 dataSize;
				bool acknowledged;
			};

			std::list<SavePacketData*> _sentPackets;
			std::list<SavePacketData*> _receivedPackets;

			XNELO::CORE::uint32 _sequence;
			XNELO::CORE::uint32 _remoteSequence;

			XNELO::CORE::uint32 _protocolID;
		public:
			//static const XNELO::CORE::uint32 PROTOCOL_ID = 1;

			/**
			 * Constructor
			 * @param protocolID An integer with the protocol ID this manager will create/interpret
			 *						(default value is 1).
			 */
			XNELO_API PacketManager(XNELO::CORE::uint32 protocolID = 1);
			XNELO_API virtual ~PacketManager();

			XNELO_API virtual XneloPacket * CreateCorrectPacket(XNELO::CORE::uint32 packetType) = 0;

			XNELO_API std::vector<XNELO::CORE::uint32> GetAcknowledgedList();

			XNELO_API XNELO::CORE::uint32 GetProtocolID();

			XNELO_API bool MarkAcknowledged(XNELO::CORE::uint32 sequenceNumber);

			/**
			* @return A newly created XneloPacket with the data from the stream read into it. This
			*			object is created on the heap and must be deleted by whomever calls this
			*			function.
			*/
			XNELO_API XneloPacket * ReadPacket(XNELO::STREAM::IBufferStreamReader * reader);

			/**
			* Read the data from the stream into the passed in packet structure. The passed in 
			* packet object must be the correct one passed in from the start of the function
			*
			* @NOTE This function is intended for internal use or cases where the packet type is 
			* predictable beforehand.
			*
			* @param reader An IBufferStreamReader class object that contains the stream data to 
			* read.
			* @param packet An XneloPacket subclass that is the appropriate packet type to hold 
			* the data.
			*
			* @return A type of XNELO::ERRORS::Error value is returned (wich is just an integer 
			* value). If XNELO::ERRORS::OK is returned then the data was read successfully. 
			* Otherwise one of the following values is returned:
			* PACKET_POINTER_IS_NULL: returned when the packeta argument is NULL.
			* ERROR_READING_DATA: An error occurred while reading data. The reader will have more 
			* details.
			* PACKET_PROTOCOL_NUMBER_INCORRECT: The packet protocol was not the same as defined in
			* this class instance. The packet was ignored.
			*/
			//XNELO_API XNELO::ERRORS::Error ReadPacket(XNELO::STREAM::IBufferStreamReader * reader, XneloPacket * packet);

			/**
			* Write the data from the packet object into the passed in writer object. When this 
			* function is completed then the writer will have the packet ready to send over the
			* network.
			*
			* @param writer A pointer to an object that implements the IBufferStreamWriter object.
			* @param packet A pointer to a packet object. This object must implement the 
			* XneloPacket interface.
			*/
			XNELO_API void WritePacket(XNELO::STREAM::IBufferStreamWriter * writer, XneloPacket * packet);
		private:
			XNELO_API void CheckAcks(XNELO::CORE::uint32 ackNumber, XNELO::CORE::uint32 ackBitmap);
			XNELO_API XNELO::CORE::uint32 CreatAckBitmap();
			XNELO_API void SavePacket(std::list<PacketManager::SavePacketData*>& container, XNELO::CORE::uint32 sequenceNumber, XNELO::CORE::uint8 * packetData, XNELO::CORE::uint32 dataSize);
			XNELO_API void SaveSentPacket(XNELO::CORE::uint32 sequenceNumber, XNELO::CORE::uint8 * packetData, XNELO::CORE::uint32 dataSize);
			XNELO_API void SaveReceivedPacket(XNELO::CORE::uint32 sequenceNumber, XNELO::CORE::uint8 * packetData, XNELO::CORE::uint32 dataSize);
		};
	}//end namespace NETWORK
}//end namespace XNELO

inline XNELO::CORE::uint32 XNELO::NETWORK::PacketManager::GetProtocolID()
{
	return _protocolID;
}

inline void XNELO::NETWORK::PacketManager::SavePacket(std::list<XNELO::NETWORK::PacketManager::SavePacketData*>& container, XNELO::CORE::uint32 sequenceNumber, XNELO::CORE::uint8 * packetData, XNELO::CORE::uint32 dataSize)
{
	SavePacketData * data = new SavePacketData(sequenceNumber, packetData, dataSize);

	container.push_front(data);

	if (container.size() > NUMBER_OF_HISTORICAL_ENTRIES)
	{
		data = container.back();
		delete data;
		container.pop_back();
	}
}

inline void XNELO::NETWORK::PacketManager::SaveSentPacket(XNELO::CORE::uint32 sequenceNumber, XNELO::CORE::uint8 * packetData, XNELO::CORE::uint32 dataSize)
{
	SavePacket(_sentPackets, sequenceNumber, packetData, dataSize);
}

inline void XNELO::NETWORK::PacketManager::SaveReceivedPacket(XNELO::CORE::uint32 sequenceNumber, XNELO::CORE::uint8 * packetData, XNELO::CORE::uint32 dataSize)
{
	SavePacket(_receivedPackets, sequenceNumber, packetData, dataSize);
}

#endif //___XNELO_NETWORK_PACKETMANAGER_HPP__1_15_2017___

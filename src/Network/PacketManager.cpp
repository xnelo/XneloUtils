/**
* @file PacketManager.cpp
* @author Spencer Hoffa
*
* @copyright 2017 Spencer Hoffa
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

#include "XneloUtils\Network\PacketManager.hpp"
#include "XneloUtils\Core\BitwiseOperators.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		PacketManager::PacketManager(): Fallible(), _sentPackets(), _receivedPackets(), _sequence(0), _remoteSequence(0)
		{
			SetError(XNELO::ERRORS::OK, "OK");
		}

		PacketManager::~PacketManager()
		{
			std::list<PacketManager::SavePacketData*>::iterator it;
			for (it = _sentPackets.begin(); it != _sentPackets.end(); ++it)
			{
				delete (*it);
			}
			_sentPackets.clear();

			for (it = _receivedPackets.begin(); it != _receivedPackets.end(); ++it)
			{
				delete (*it);
			}
			_receivedPackets.clear();
		}

		std::vector<XNELO::CORE::uint32> PacketManager::GetAcknowledgedList()
		{
			std::vector<XNELO::CORE::uint32> resultList;

			for (std::list<PacketManager::SavePacketData*>::iterator it = _sentPackets.begin();
			it != _sentPackets.end();
				++it)
			{
				if ((*it)->acknowledged)
					resultList.push_back((*it)->sequenceNumber);
			}

			return resultList;
		}

		bool PacketManager::MarkAcknowledged(XNELO::CORE::uint32 sequenceNumber)
		{
			for (std::list<PacketManager::SavePacketData*>::iterator it = _sentPackets.begin(); 
					it != _sentPackets.end(); 
					++it)
			{
				if ((*it)->sequenceNumber == sequenceNumber)
				{
					(*it)->acknowledged = true;
					return true;
				}
			}
			return false;
		}

		void PacketManager::WritePacket(XNELO::STREAM::IBufferStreamWriter * writer, XneloPacket * packet)//, void* data, XNELO::CORE::uint32 dataSize)
		{
			writer->Write((void*)&(PacketManager::PROTOCOL_ID), sizeof(PacketManager::PROTOCOL_ID));

			writer->Write((void*)&_sequence, sizeof(_sequence));

			//acknowledgment
			writer->Write((void*)&_remoteSequence, sizeof(_remoteSequence));

			//ack bitfield
			XNELO::CORE::uint32 ackBitmap = CreatAckBitmap();
			writer->Write((void*)&ackBitmap, sizeof(ackBitmap));

			//packet Type
			XNELO::CORE::uint16 packetType = packet->GetPacketType(); //<-- TODO: this needs to be the actual packet type
			writer->Write((void*)&packetType, sizeof(packetType));

			////data length
			//writer->Write((void *)&dataSize, sizeof(dataSize));
			//
			////copy data
			//writer->Write(data, dataSize);
			packet->WriteData(writer);

			SaveSentPacket(_sequence, (XNELO::CORE::uint8*)writer->GetBuffer(), writer->GetSize());
			++_sequence;
		}

		XneloPacket * PacketManager::ReadPacket(XNELO::STREAM::IBufferStreamReader * reader/*, XneloPacket * packet*/)
		{
			//if (packet == NULL)
			//	return XNELO::ERRORS::PACKET_POINTER_IS_NULL;

			XNELO::CORE::uint32 protocolNumber;

			if (reader->Read((void*)&protocolNumber, sizeof(protocolNumber)) != sizeof(protocolNumber))
			{
				SetError(XNELO::ERRORS::ERROR_READING_DATA, "Read function from reader returned incorrect number of bytes.");
				return NULL;
			}

			if (protocolNumber != PacketManager::PROTOCOL_ID)
			{
				//not our packet stop processing
				SetError(XNELO::ERRORS::PACKET_PROTOCOL_NUMBER_INCORRECT, "Packet protocol number is incorrect. Not our packet.");
				return NULL;
			}

			//packet->protocolNumber = protocolNumber;
			XNELO::CORE::uint32 sequenceNumber;

			//if (reader->Read((void*)&(packet->sequenceNumber), sizeof(packet->sequenceNumber)) != sizeof(packet->sequenceNumber))
			if (reader->Read((void*)&(sequenceNumber), sizeof(sequenceNumber)) != sizeof(sequenceNumber))
			{
				SetError(XNELO::ERRORS::ERROR_READING_DATA, "Read function from reader returned incorrect number of bytes.");
				return NULL;
			}

			//SaveReceivedPacket(packet->sequenceNumber, (XNELO::CORE::uint8*)reader->GetBuffer(), reader->GetSize());
			SaveReceivedPacket(sequenceNumber, (XNELO::CORE::uint8*)reader->GetBuffer(), reader->GetSize());

			if (sequenceNumber > _remoteSequence)
			{
				_remoteSequence = sequenceNumber;
			}

			XNELO::CORE::uint32 ackNumber;
			//read acknoledgment number
			//if (reader->Read((void*)&(packet->ackNumber), sizeof(packet->ackNumber)) != sizeof(packet->ackNumber))
			if (reader->Read((void*)&(ackNumber), sizeof(ackNumber)) != sizeof(ackNumber))
			{
				SetError(XNELO::ERRORS::ERROR_READING_DATA, "Read function from reader returned incorrect number of bytes.");
				return NULL;
			}

			XNELO::CORE::uint32 ackBitmap;
			//read acknowledgment bitmap
			//if (reader->Read((void*)&(packet->ackBitmap), sizeof(packet->ackBitmap)) != sizeof(packet->ackBitmap))
			if (reader->Read((void*)&(ackBitmap), sizeof(ackBitmap)) != sizeof(ackBitmap))
			{
				SetError(XNELO::ERRORS::ERROR_READING_DATA, "Read function from reader returned incorrect number of bytes.");
				return NULL;
			}

			CheckAcks(ackNumber, ackBitmap);

			XNELO::CORE::uint16 packetType;
			//Read the packet type
			//if (reader->Read((void*)&(packet->packetType), sizeof(packet->packetType)) != sizeof(packet->packetType))
			if (reader->Read((void*)&(packetType), sizeof(packetType)) != sizeof(packetType))
			{
				SetError(XNELO::ERRORS::ERROR_READING_DATA, "Read function from reader returned incorrect number of bytes.");
				return NULL;
			}

			XneloPacket * returnPacket = CreateCorrectPacket(packetType);
			if (returnPacket == NULL)
			{
				SetError(XNELO::ERRORS::PACKET_ERROR_NO_PACKET_MATCHING_TYPE, "No packet could be created for the passed in type");
				return NULL;
			}

			//Set the accumulated data so far
			returnPacket->protocolNumber = protocolNumber;
			returnPacket->sequenceNumber = sequenceNumber;
			returnPacket->ackNumber = ackNumber;
			returnPacket->ackBitmap = ackBitmap;
			returnPacket->packetType = packetType;

			////Read the data size variable
			//if (reader->Read((void*)&(returnData->dataSize), sizeof(returnData->dataSize)) != sizeof(returnData->dataSize))
			//{
			//	//error
			//}
			//
			//read all the data
			//returnData->data = new XNELO::CORE::uint8[returnData->dataSize];
			//if (reader->Read((void*)returnData->data, returnData->dataSize) != returnData->dataSize)
			//{
			//	//error
			//}

			XNELO::ERRORS::Error packetReadError = returnPacket->ReadData(reader);
			if (packetReadError != XNELO::ERRORS::OK)
			{
				SetError(packetReadError, "Error with individual packet reading.");
				delete returnPacket;
				return NULL;
			}

			return returnPacket;

			//return packet->ReadData(reader);
			
			//return XNELO::ERRORS::OK;
		}

		void PacketManager::CheckAcks(XNELO::CORE::uint32 ackNumber, XNELO::CORE::uint32 ackBitmap)
		{
			const int numberOfBits = 32;

			MarkAcknowledged(ackNumber);

			for (int i = 1; i <= numberOfBits; ++i)
			{
				if (XNELO::CORE::IsBitSetBitNumber(ackBitmap, i - 1))
				{
					XNELO::CORE::uint32 acked = ackNumber - i;
					MarkAcknowledged(acked);
				}
			}
		}

		XNELO::CORE::uint32 PacketManager::CreatAckBitmap()
		{
			XNELO::CORE::uint32 ackBitmap = 0;

			for (std::list<PacketManager::SavePacketData*>::iterator it = _receivedPackets.begin(); 
					it != _receivedPackets.end();
					++it)
			{
				//                     1 =               9 -                     8
				//                     6 =               9 -                     3
				//                    32 =              43 -                    11
				XNELO::CORE::uint32 diff = _remoteSequence - (*it)->sequenceNumber;
				
				if ((diff > 32) || (diff < 1)) continue;

				ackBitmap |= 1 << (diff - 1);
			}

			return ackBitmap;
		}
	}//end namespace NETWORK
}//end namespace XNELO
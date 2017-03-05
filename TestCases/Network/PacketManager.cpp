/**
* @file PacketManager.cpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Test file for the PacketManager test cases.
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

#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Network/PacketManager.hpp"
#include "XneloUtils/Stream/BufferStreamWriter.hpp"
#include "XneloUtils/Stream/BufferStreamReader.hpp"

class TestPacket : public XNELO::NETWORK::XneloPacket
{
public:
	XNELO::CORE::uint32 _dataSize;
	XNELO::CORE::uint8 * _data;

	TestPacket() : XNELO::NETWORK::XneloPacket(), _dataSize(0), _data(NULL) {}
	virtual ~TestPacket() 
	{
		Clear();
	}

	void Clear()
	{
		if (_data != NULL)
			delete[] _data;

		_data = NULL;
		_dataSize = 0;
	}

	virtual XNELO::CORE::uint16 GetPacketType()
	{
		return 1;
	}

	virtual std::string GetPacketTypeString()
	{
		return "Test Packet 1";
	}

	virtual XNELO::ERRORS::Error ReadData(XNELO::STREAM::IBufferStreamReader * stream) { return TestPacketSerialize(stream); };
	virtual XNELO::ERRORS::Error WriteData(XNELO::STREAM::IBufferStreamWriter * stream) { return TestPacketSerialize(stream); };

private:
	template <typename Stream>
	XNELO::ERRORS::Error TestPacketSerialize(Stream * stream)
	{
		if (stream->Serialize((void *)&_dataSize, sizeof(_dataSize)) != sizeof(_dataSize))
		{
			return Stream::IsWriting ? XNELO::ERRORS::BUFFER_STREAM_WRITER_WRITE_FAILED_INVALID_SIZE : XNELO::ERRORS::ERROR_READING_DATA;
		}
		
		if (Stream::IsReading)
		{
			_data = new XNELO::CORE::uint8[_dataSize];
		}

		if (stream->Serialize(_data, _dataSize) != _dataSize)
		{
			return Stream::IsWriting ? XNELO::ERRORS::BUFFER_STREAM_WRITER_WRITE_FAILED_INVALID_SIZE : XNELO::ERRORS::ERROR_READING_DATA;
		}

		return XNELO::ERRORS::OK;
	}
};

class TestPacketManager : public XNELO::NETWORK::PacketManager
{
public:
	TestPacketManager(): XNELO::NETWORK::PacketManager() {}
	virtual ~TestPacketManager(){}
	virtual XNELO::NETWORK::XneloPacket * CreateCorrectPacket(XNELO::CORE::uint32 packetType)
	{
		if (packetType == 1)
		{
			return new TestPacket();
		}
		else
			return NULL;
	}
};

bool VerifyPacketCorrect(char * data, int dataSize, int expectedSequenceNumber, int expectedAckNumber, int expectedAckBitmap, const char * expectedString, int StringSize)
{
	bool success = true;
	XNELO::CORE::uint32 protocolID;
	XNELO::CORE::uint32 sequenceNumber;
	XNELO::CORE::uint32 ack;
	XNELO::CORE::uint32 ackBitmap;
	XNELO::CORE::uint16 packetType;
	XNELO::CORE::uint32 packetDataSize;

	char packetData[11];

	char * buffer = data;

	std::memcpy((void*)&protocolID, buffer, sizeof(XNELO::CORE::uint32));
	buffer += sizeof(XNELO::CORE::uint32);

	if (protocolID != XNELO::NETWORK::PacketManager::PROTOCOL_ID)
	{
		success = false;
		std::cout << "Check protocol number correct [FAILED]" << std::endl;
	}
	else
		std::cout << "Check protocol number correct [PASSED]" << std::endl;

	std::memcpy((void*)&sequenceNumber, buffer, sizeof(XNELO::CORE::uint32));
	buffer += sizeof(XNELO::CORE::uint32);

	if (sequenceNumber != (XNELO::CORE::uint32)expectedSequenceNumber)
	{
		success = false;
		std::cout << "Check that the sequence number is correct [FAILED]" << std::endl;
	}
	else
		std::cout << "Check that the sequence number is correct [PASSED]" << std::endl;

	std::memcpy((void*)&ack, buffer, sizeof(XNELO::CORE::uint32));
	buffer += sizeof(XNELO::CORE::uint32);

	if (ack != (XNELO::CORE::uint32)expectedAckNumber)
	{
		success = false;
		std::cout << "Check that the ack number is correct [FAILED]" << std::endl;
	}
	else
		std::cout << "Check that the ack number is correct [PASSED]" << std::endl;

	std::memcpy((void*)&ackBitmap, buffer, sizeof(XNELO::CORE::uint32));
	buffer += sizeof(XNELO::CORE::uint32);

	if (ackBitmap != (XNELO::CORE::uint32)expectedAckBitmap)
	{
		success = false;
		std::cout << "Check that the ack bitmap is correct [FAILED]" << std::endl;
	}
	else
		std::cout << "Check that the ack bitmap is correct [PASSED]" << std::endl;

	std::memcpy((void*)&packetType, buffer, sizeof(XNELO::CORE::uint16));
	buffer += sizeof(XNELO::CORE::uint16);

	//check packet type if you want
	///////////////////////////////

	std::memcpy((void*)&packetDataSize, buffer, sizeof(packetDataSize));
	buffer += sizeof(packetDataSize);

	//check datasize if you want
	if (packetDataSize != StringSize)
	{
		success = false;
		std::cout << "Check that the packet datasize is correct [FAILED]" << std::endl;
	}
	else
		std::cout << "Check that the packet datasize is correct [PASSED]" << std::endl;
	////////////////////////////

	std::memcpy((void*)packetData, buffer, StringSize);
	buffer += StringSize;

	if (std::strncmp(packetData, expectedString, StringSize) != 0)
	{
		success = false;
		std::cout << "Check that the data is correct [FAILED]" << std::endl;
	}
	else
		std::cout << "Check that the data is correct [PASSED]" << std::endl;

	return success;
}

XNELO_TEST_CASE(PacketManager, Writing)
{
	TestPacket packet1;
	packet1._dataSize = 11;
	packet1._data = (XNELO::CORE::uint8*)new char[11];
	std::memcpy((void*)packet1._data, (void*)"Hello World", 11);

	TestPacketManager * pm = new TestPacketManager();
	XNELO::STREAM::BufferStreamWriter * sw = new XNELO::STREAM::BufferStreamWriter(1024);

	bool success;

	for (int i = 0; i < 10; ++i)
	{
		sw->Reset();

		//pm->WritePacket(sw, "Hello World", 11);
		pm->WritePacket(sw, &packet1);

		success = VerifyPacketCorrect(
			sw->GetBuffer(), 
			sw->GetSize(), 
			i,
			0,
			0,
			"Hello World",
			11);

		XNELO_TEST_ASSERT_TRUE(success, "Verify Packet was correct");
	}

	//TestPacket packet2;

	TestPacketManager * pm2 = new TestPacketManager();
	XNELO::STREAM::BufferStreamReader * sr = new XNELO::STREAM::BufferStreamReader(sw->GetBuffer(), sw->GetSize());
	
	//packet2.Clear();
	//XNELO::ERRORS::Error rc = pm2->ReadPacket(sr, &packet2);
	//XNELO_TEST_ASSERT_EQUAL(rc, XNELO::ERRORS::OK, "Read packet did not return OK");
	TestPacket * returnPacket = (TestPacket*)pm2->ReadPacket(sr);
	XNELO_TEST_ASSERT_FALSE(returnPacket == NULL, "Read Packet did not return A valid packet");
	if (returnPacket == NULL)
		return;

	//setup the data for the return packet
	std::memcpy((void*)returnPacket->_data, (void*)"Hello DOODS", 11);

	sw->Reset();
	pm2->WritePacket(sw, returnPacket);

	success = VerifyPacketCorrect(
		sw->GetBuffer(),
		sw->GetSize(),
		0,
		9,
		0,
		"Hello DOODS",
		11);

	XNELO_TEST_ASSERT_TRUE(success, "Verify return packet was correct");

	delete sr;
	sr = new XNELO::STREAM::BufferStreamReader(sw->GetBuffer(), sw->GetSize());

	delete returnPacket;
	returnPacket = (TestPacket*)pm->ReadPacket(sr);
	XNELO_TEST_ASSERT_FALSE(returnPacket == NULL, "Read Packet did not return A valid packet");
	if (returnPacket == NULL)
		return;
	
	for (int i = 0; i < 10; ++i)
	{
		sw->Reset();

		pm->WritePacket(sw, &packet1);

		success = VerifyPacketCorrect(
			sw->GetBuffer(),
			sw->GetSize(),
			i+10,
			0,
			0,
			"Hello World",
			11);

		XNELO_TEST_ASSERT_TRUE(success, "Verify Packet was correct");
	}
	
	delete sr;
	sr = new XNELO::STREAM::BufferStreamReader(sw->GetBuffer(), sw->GetSize());

	delete returnPacket;
	returnPacket = (TestPacket*)pm2->ReadPacket(sr);
	XNELO_TEST_ASSERT_FALSE(returnPacket == NULL, "Read Packet did not return A valid packet");
	if (returnPacket == NULL)
		return;

	//setup the data for the return packet
	std::memcpy((void*)returnPacket->_data, (void*)"Hello DOODS", 11);

	sw->Reset();
	pm2->WritePacket(sw, returnPacket);

	success = VerifyPacketCorrect(
		sw->GetBuffer(),
		sw->GetSize(),
		1,
		19,
		XNELO::CORE::bit10,
		"Hello DOODS",
		11);

	XNELO_TEST_ASSERT_TRUE(success, "Verify return packet was correct");

	delete sr;
	sr = new XNELO::STREAM::BufferStreamReader(sw->GetBuffer(), sw->GetSize());

	delete returnPacket;
	returnPacket = (TestPacket*)pm->ReadPacket(sr);
	XNELO_TEST_ASSERT_FALSE(returnPacket == NULL, "Read Packet did not return A valid packet");
	if (returnPacket == NULL)
		return;

	std::vector<XNELO::CORE::uint32> acked = pm->GetAcknowledgedList();
	XNELO_TEST_ASSERT_EQUAL(acked.size(), (size_t)2, "Correct number of acks");
	XNELO_TEST_ASSERT_EQUAL(acked[0], (XNELO::CORE::uint32)19, "Ack 1 correct");
	XNELO_TEST_ASSERT_EQUAL(acked[1], (XNELO::CORE::uint32)9, "Ack 2 correct");

	delete returnPacket;
	delete sw;
	delete pm;
	delete pm2;
	delete sr;
}
//*
XNELO_TEST_CASE(PacketManager, Communication)
{
	struct ComputerData
	{
		TestPacket * lastRecieved;
		TestPacket * lastSent;
		TestPacketManager pm;

		ComputerData(): lastRecieved(NULL), lastSent(NULL), pm()
		{}

		~ComputerData()
		{
			ClearLastSent();
			ClearLastRecieved();
		}

		void ClearLastSent()
		{
			if (lastSent != NULL)
				delete lastSent;

			lastSent = NULL;
		}

		void ClearLastRecieved()
		{
			if (lastRecieved != NULL)
				delete lastRecieved;

			lastRecieved = NULL;
		}

		XNELO::ERRORS::Error SendPacket(const char * data, int dataSize, ComputerData * receiver)
		{
			ClearLastSent();

			lastSent = new TestPacket();

			lastSent->_dataSize = dataSize;
			lastSent->_data = new XNELO::CORE::uint8[dataSize];
			std::memcpy(lastSent->_data, data, dataSize);

			XNELO::STREAM::BufferStreamWriter writer(1024);
			pm.WritePacket(&writer, lastSent);
			receiver->ReceivePacket(writer.GetBuffer(), writer.GetSize());

			return XNELO::ERRORS::OK;
		}

		XNELO::ERRORS::Error ReceivePacket(char * buffer, int bufferSize)
		{
			XNELO::STREAM::BufferStreamReader reader(buffer, bufferSize);
			
			ClearLastRecieved();

			lastRecieved = (TestPacket*)pm.ReadPacket(&reader);

			return XNELO::ERRORS::OK;
		}

		void CheckLastReceived()
		{}
	};

	ComputerData computer1;
	ComputerData computer2;

	computer1.SendPacket("Hello Comp2", 11, &computer2);
	XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer2.lastRecieved->_data, "Hello Comp2", computer2.lastRecieved->_dataSize), 0, "Data not correct for");
	XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)0, "Data not correct for sequence number");
	XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->ackNumber, (XNELO::CORE::uint32)0, "Data not correct for ack number");
	computer2.SendPacket("Hello Comp1", 11, &computer1);
	XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer1.lastRecieved->_data, "Hello Comp1", computer1.lastRecieved->_dataSize), 0, "Data not correct for");
	XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)0, "Data not correct for sequence number");
	XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->ackNumber, (XNELO::CORE::uint32)0, "Data not correct for ack number");

	computer1.SendPacket("I Am Good", 9, &computer2);
	XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer2.lastRecieved->_data, "I Am Good", computer2.lastRecieved->_dataSize), 0, "Data not correct for");
	XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)1, "Data not correct for sequence number");
	XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->ackNumber, (XNELO::CORE::uint32)0, "Data not correct for ack number");
	computer2.SendPacket("How are you", 11, &computer1);
	XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer1.lastRecieved->_data, "How are you", computer1.lastRecieved->_dataSize), 0, "Data not correct for");
	XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)1, "Data not correct for sequence number");
	XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->ackNumber, (XNELO::CORE::uint32)1, "Data not correct for ack number");

	computer1.SendPacket("DOOD YOU ARE", 12, &computer2);
	XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer2.lastRecieved->_data, "DOOD YOU ARE", computer2.lastRecieved->_dataSize), 0, "Data not correct for");
	XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)2, "Data not correct for sequence number");
	XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->ackNumber, (XNELO::CORE::uint32)1, "Data not correct for ack number");
	computer2.SendPacket("STUFFING", 8, &computer1);
	XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer1.lastRecieved->_data, "STUFFING", computer1.lastRecieved->_dataSize), 0, "Data not correct for");
	XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)2, "Data not correct for sequence number");
	XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->ackNumber, (XNELO::CORE::uint32)2, "Data not correct for ack number");

	for (int i = 1; i <= 200; i++)
	{
		computer1.SendPacket("DOOD YOU ARE", 12, &computer2);
		XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer2.lastRecieved->_data, "DOOD YOU ARE", computer2.lastRecieved->_dataSize), 0, "Data correct for computer2");
		XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)2 + i, "Sequence number is correct for computer 2");
		XNELO_TEST_ASSERT_EQUAL(computer2.lastRecieved->ackNumber, (XNELO::CORE::uint32)1 + i, "Ack number is correct for computer 2");
		std::vector<XNELO::CORE::uint32> comp2list = computer2.pm.GetAcknowledgedList();
		for (XNELO::CORE::uint32 j = 0; j < comp2list.size(); j++)
		{
			XNELO_TEST_ASSERT_EQUAL(comp2list[j], computer2.lastRecieved->ackNumber - j, "Ack list correct");
		}

		computer2.SendPacket("STUFFING", 8, &computer1);
		XNELO_TEST_ASSERT_EQUAL(std::strncmp((char*)computer1.lastRecieved->_data, "STUFFING", computer1.lastRecieved->_dataSize), 0, "Data correct for computer1");
		XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->sequenceNumber, (XNELO::CORE::uint32)2 + i, "Sequence number is correct for computer1");
		XNELO_TEST_ASSERT_EQUAL(computer1.lastRecieved->ackNumber, (XNELO::CORE::uint32)2 + i, "Ack number is correct for computer 1");
		std::vector<XNELO::CORE::uint32> comp1list = computer1.pm.GetAcknowledgedList();
		for (XNELO::CORE::uint32 j = 0; j < comp1list.size(); j++)
		{
			XNELO_TEST_ASSERT_EQUAL(comp1list[j], computer1.lastRecieved->ackNumber - j, "Ack list correct");
		}
	}
}
//*/

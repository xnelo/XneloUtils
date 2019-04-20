/// <file> UUID.cpp </file>
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

#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <sstream>

#include "XneloUtils/Core/UUID.hpp"
#include "XneloUtils/Core/StringUtils.hpp"

const int BYTES_AT_A_TYPE = 2;
const int ITERATIONS_NEEDED = XNELO::CORE::UUID::NUMBER_OF_BYTES_IN_UUID / BYTES_AT_A_TYPE;

namespace XNELO
{
	namespace CORE
	{
		bool UUID::m_IsSeeded = false;

		bool UUID::operator==(const UUID & other) const
		{
			return (m_UUID[0] == other.m_UUID[0] &&
					m_UUID[1] == other.m_UUID[1] &&
					m_UUID[2] == other.m_UUID[2] &&
					m_UUID[3] == other.m_UUID[3] &&
					m_UUID[4] == other.m_UUID[4] &&
					m_UUID[5] == other.m_UUID[5] &&
					m_UUID[6] == other.m_UUID[6] &&
					m_UUID[7] == other.m_UUID[7] &&
					m_UUID[8] == other.m_UUID[8] &&
					m_UUID[9] == other.m_UUID[9] &&
					m_UUID[10] == other.m_UUID[10] &&
					m_UUID[11] == other.m_UUID[11] &&
					m_UUID[12] == other.m_UUID[12] &&
					m_UUID[13] == other.m_UUID[13] &&
					m_UUID[14] == other.m_UUID[14] &&
					m_UUID[15] == other.m_UUID[15]);
		}

		std::string UUID::ToString()
		{
			const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
								   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

			std::string returnString;
			returnString.resize(HYPHENATED_UUID_LENGTH, '0');
			returnString[HYPHEN_INDEX_1] = 
				returnString[HYPHEN_INDEX_2] = 
				returnString[HYPHEN_INDEX_3] = 
				returnString[HYPHEN_INDEX_4] = '-';

			returnString[0] = hexmap[(m_UUID[0] & 0xF0) >> 4];
			returnString[1] = hexmap[m_UUID[0] & 0x0F];
			returnString[2] = hexmap[(m_UUID[1] & 0xF0) >> 4];
			returnString[3] = hexmap[m_UUID[1] & 0x0F];
			returnString[4] = hexmap[(m_UUID[2] & 0xF0) >> 4];
			returnString[5] = hexmap[m_UUID[2] & 0x0F];
			returnString[6] = hexmap[(m_UUID[3] & 0xF0) >> 4];
			returnString[7] = hexmap[m_UUID[3] & 0x0F];
			returnString[9] = hexmap[(m_UUID[4] & 0xF0) >> 4];
			returnString[10] = hexmap[m_UUID[4] & 0x0F];
			returnString[11] = hexmap[(m_UUID[5] & 0xF0) >> 4];
			returnString[12] = hexmap[m_UUID[5] & 0x0F];
			returnString[14] = hexmap[(m_UUID[6] & 0xF0) >> 4];
			returnString[15] = hexmap[m_UUID[6] & 0x0F];
			returnString[16] = hexmap[(m_UUID[7] & 0xF0) >> 4];
			returnString[17] = hexmap[m_UUID[7] & 0x0F];
			returnString[19] = hexmap[(m_UUID[8] & 0xF0) >> 4];
			returnString[20] = hexmap[m_UUID[8] & 0x0F];
			returnString[21] = hexmap[(m_UUID[9] & 0xF0) >> 4];
			returnString[22] = hexmap[m_UUID[9] & 0x0F];
			returnString[24] = hexmap[(m_UUID[10] & 0xF0) >> 4];
			returnString[25] = hexmap[m_UUID[10] & 0x0F];
			returnString[26] = hexmap[(m_UUID[11] & 0xF0) >> 4];
			returnString[27] = hexmap[m_UUID[11] & 0x0F];
			returnString[28] = hexmap[(m_UUID[12] & 0xF0) >> 4];
			returnString[29] = hexmap[m_UUID[12] & 0x0F];
			returnString[30] = hexmap[(m_UUID[13] & 0xF0) >> 4];
			returnString[31] = hexmap[m_UUID[13] & 0x0F];
			returnString[32] = hexmap[(m_UUID[14] & 0xF0) >> 4];
			returnString[33] = hexmap[m_UUID[14] & 0x0F];
			returnString[34] = hexmap[(m_UUID[15] & 0xF0) >> 4];
			returnString[35] = hexmap[m_UUID[15] & 0x0F];

			return returnString;
		}

		bool UUID::FromString(UUID * uuidClass, const char * uuid)
		{
			if (strlen(uuid) != HYPHENATED_UUID_LENGTH)
			{
				return false;
			}

			bool success = true;

			int index = 0;
			int destIndex = 0;
			while (index < HYPHENATED_UUID_LENGTH)
			{
				if (success != true)
					break;

				if (index == HYPHEN_INDEX_1 ||
					index == HYPHEN_INDEX_2 ||
					index == HYPHEN_INDEX_3 ||
					index == HYPHEN_INDEX_4)
				{ 
					if (uuid[index] != '-')
					{
						success = false;
						break;
					}
					++index;
				}
				else
				{
					// Conversion from hex to byte came from: Niels Keurentjes and Lysann Schlegel
					// see: https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
					uuidClass->m_UUID[destIndex] = XNELO::CORE::char2int(uuid[index], &success) * 16;
					++index;

					if (!success) break;

					uuidClass->m_UUID[destIndex] += XNELO::CORE::char2int(uuid[index], &success);
					++index;
					++destIndex;

					if (!success) break;
				}
			}
			return success;
		}

		std::size_t UUID::CalculateHash() const
		{
			int sizeInBytes = sizeof(std::size_t);

			// Create initial hash which is just the UUID
			int newSize = NUMBER_OF_BYTES_IN_UUID;
			XNELO::CORE::uint8 * hash = new XNELO::CORE::uint8[NUMBER_OF_BYTES_IN_UUID];
			std::memcpy(hash, m_UUID, NUMBER_OF_BYTES_IN_UUID);
			
			while (sizeInBytes < newSize)
			{
				newSize /= 2;
				XNELO::CORE::uint8 * newHash = new XNELO::CORE::uint8[newSize];
				for (int i = 0; i < newSize; ++i)
				{
					newHash[i] = hash[i] ^ hash[i + newSize];
				}

				delete[] hash;
				hash = newHash;
			}

			std::size_t retVal;
			std::memcpy(&retVal, hash, newSize);
			delete[] hash;
			return retVal;
		}

		void UUID::GetNIL(UUID * uuidClass)
		{
			if (uuidClass != NULL)
			{
				uuidClass->m_UUID[0] = 0x00;
				uuidClass->m_UUID[1] = 0x00;
				uuidClass->m_UUID[2] = 0x00;
				uuidClass->m_UUID[3] = 0x00;
				uuidClass->m_UUID[4] = 0x00;
				uuidClass->m_UUID[5] = 0x00;
				uuidClass->m_UUID[6] = 0x00;
				uuidClass->m_UUID[7] = 0x00;
				uuidClass->m_UUID[8] = 0x00;
				uuidClass->m_UUID[9] = 0x00;
				uuidClass->m_UUID[10] = 0x00;
				uuidClass->m_UUID[11] = 0x00;
				uuidClass->m_UUID[12] = 0x00;
				uuidClass->m_UUID[13] = 0x00;
				uuidClass->m_UUID[14] = 0x00;
				uuidClass->m_UUID[15] = 0x00;
			}
		}

		void UUID::NewUUID(UUID * uuidClass)
		{
			if (!m_IsSeeded) 
			{
				srand((int)time(NULL));
				m_IsSeeded = true;
			}

			unsigned int randNum;

			for (int i = 0; i < ITERATIONS_NEEDED; ++i)
			{
				randNum = (unsigned int)rand();
				std::memcpy(uuidClass->m_UUID + (i * BYTES_AT_A_TYPE), &randNum, BYTES_AT_A_TYPE);
			}

			// Using UUID version 4. The first 4 bits of the 7th byte need to be 0100
			// So clear bits 8, 6, and 5 and set bit 7
			uuidClass->m_UUID[6] = uuidClass->m_UUID[6] & (~(XNELO::CORE::bit8 | XNELO::CORE::bit6 | XNELO::CORE::bit5));
			uuidClass->m_UUID[6] = uuidClass->m_UUID[6] | XNELO::CORE::bit7;

			// Using UUID variant 1. The first 2 bits of the 9th byte needs to be 10
			// So clear bit 7 and set bit 8;
			uuidClass->m_UUID[8] &= (~XNELO::CORE::bit7);
			uuidClass->m_UUID[8] |= XNELO::CORE::bit8;
		}
	}// !Namespace CORE
} // !namespace XNELO

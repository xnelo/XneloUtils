#pragma region Copyright 2019 Spencer Hoffa
/// <file> UUID.hpp </file>
/// <author> Spencer Hoffa </author>
///
/// <copyright> 2019 Spencer Hoffa </copyright>
/// 
/// <summary>
/// </summary>
/// 
/// <license>
/// The zlib/libpng License
/// Copyright(c) 2019 Spencer Hoffa
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is granted to anyone to use this software for any purpose,
///including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions :
///
///		1. The origin of this software must not be misrepresented; you must not
///		claim that you wrote the original software.If you use this software in
///		a product, an acknowledgment in the product documentation would be
///		appreciated but is not required.
///
///		2. Altered source versions must be plainly marked as such, and must not
///		be misrepresented as being the original software.
///
///		3. This notice may not be removed or altered from any source
///		distribution.
///
/// This liscense can also be found at : http ://opensource.org/licenses/Zlib
/// </license>
#pragma endregion

#ifndef ___XNELO__CORE__UUID_HPP__2_13_2019___
#define ___XNELO__CORE__UUID_HPP__2_13_2019___

#include <string>
#include <cstring>

#include "../Config.hpp"
#include "BasicTypes.hpp"

namespace XNELO
{
	namespace CORE
	{
		class UUID
		{
		public:
			static const int NUMBER_OF_BYTES_IN_UUID = 16;
			static const int HYPHENATED_UUID_LENGTH = 36;
			static const int HYPHEN_INDEX_1 = 8;
			static const int HYPHEN_INDEX_2 = 13;
			static const int HYPHEN_INDEX_3 = 18;
			static const int HYPHEN_INDEX_4 = 23;
		private:
			bool m_HashCalculated;
			std::size_t m_HashValue;
			static bool m_IsSeeded;
			XNELO::CORE::uint8 m_UUID[NUMBER_OF_BYTES_IN_UUID];
		public:
			/// <summary>
			/// Constructor. This constructor NILL UUID in it.
			/// </summary>
			XNELO_API UUID();

			/// <summary>
			/// Constructor.
			/// </summary>
			/// <param name="uuid">An array of 16 uint8 values with the uuid in it.</param>
			XNELO_API UUID(XNELO::CORE::uint8 uuid[NUMBER_OF_BYTES_IN_UUID]);

			/// <summary>
			/// Copy Constructor
			/// </summary>
			/// <param name="other">Another instance of the UUID class.</param>
			XNELO_API UUID(const UUID & other);

			/// <summary>
			/// Destructor
			/// </summary>
			XNELO_API ~UUID();

			// Operators
			/// <summary>
			/// Assignment Operator.
			/// </summary>
			/// <param name="other">Another instance of UUID class.</param>
			/// <returns>A reference to this object.</returns>
			XNELO_API UUID& operator=(const UUID & other);

			/// <summary>
			/// Equality operator
			/// </summary>
			/// <param name="other">Another instance of UUID class</param>
			/// <returns>True if they are the same false if not.</returns>
			XNELO_API bool operator==(const UUID & other) const;

			/// <summary>
			/// Not equal operator
			/// </summary>
			/// <param name="other">Another instance of UUID class.</param>
			/// <returns>True if they are NOT the same. False if they are.</returns>
			XNELO_API bool operator!=(const UUID & other) const;

			// Static methods
			/// <summary>
			/// Copy the data from the source object into the destination object.
			/// </summary>
			/// <param name="source">An instance of the UUID class to copy data from.</param>
			/// <param name="destination">An instance of the UUID class to copy data into.</param>
			/// <returns>Return true if the copy was successful.</returns>
			XNELO_API static bool CopyTo(const UUID* source, UUID * destination);

			/// <summary>
			/// Take the values in the passed in array and set hthe class data from it.
			/// </summary>
			/// <param name="uuidClass">The class to put the data into.</param>
			/// <param name="uuid">The 16 element array of uint8 items.</param>
			/// <returns>True ithe copying was successful.</returns>
			XNELO_API static bool FromByteArray(UUID * uuidClass, XNELO::CORE::uint8 uuid[NUMBER_OF_BYTES_IN_UUID]);

			/// <summary>
			/// Take the values in the passed in array and set hthe class data from it.
			/// </summary>
			/// <param name="uuidClass">The class to put the data into.</param>
			/// <param name="uuid">The 16 element array of uint8 items.</param>
			/// <returns>True ithe copying was successful.</returns>
			XNELO_API static bool FromConstByteArray(UUID * uuidClass, const XNELO::CORE::uint8 uuid[NUMBER_OF_BYTES_IN_UUID]);

			/// <summary>
			/// Parse a string representing a UUID and place it into the UUID structure.
			/// </summary>
			/// <param name="uuidClass">The class to put the parsed string in.</param>
			/// <param name="uuid">The UUID string to parse</param>
			/// <returns>True if the data was parsed successfully.</returns>
			XNELO_API static bool FromString(UUID * uuidClass, std::string uuid);
			XNELO_API static bool FromString(UUID * uuidClass, const char * uuid);

			/// <summary>
			/// Get the pointer to the array of bytes;
			/// </summary>
			/// <returns>A pointer to the first element in the UUID array.</returns>
			XNELO_API XNELO::CORE::uint8 * GetBytes();

			/// <summary>
			/// Create a hash number for this UUID.
			/// </summary>
			/// <returns>A size_t integer representing a hash of this UUID.</returns>
			XNELO_API std::size_t GetHash();

			XNELO_API static void GetNIL(UUID * uuidClass);

			/// <summary>
			/// Generate a new UUID and place it in the passed in.
			/// </summary>
			/// <param name="uuidClass">Pointer to a class to put the new UUID in.</param>
			XNELO_API static void NewUUID(UUID * uuidClass);

			/// <summary>
			/// Write this class to a string.
			/// </summary>
			/// <returns>A string representation of the class.</returns>
			XNELO_API std::string ToString();
		private:
			/// <summary>
			/// Calculate a hash value of this UUID.
			/// </summary>
			/// <returns>A size_t variable with the hash in it.</returns>
			XNELO_API std::size_t CalculateHash() const;

			/// <summary>
			/// Declare the hash class a friend class.
			/// </summary>
			friend struct std::hash<XNELO::CORE::UUID>;
		};
	} // !namespace CORE
} // !namespace XNELO

// Define the hash class
namespace std 
{
	/// <summary>
	/// A hash class so that standard hash containers can use the UUID class.
	/// </summary>
	template <>
	struct hash<XNELO::CORE::UUID>
	{
		std::size_t operator()(const XNELO::CORE::UUID& k) const
		{
			return k.CalculateHash();
		}
	};
} // ! End namespace std

inline XNELO::CORE::UUID::UUID()
{
	m_HashCalculated = false;
	m_HashValue = 0;
	
	GetNIL(this);
}

inline XNELO::CORE::UUID::UUID(XNELO::CORE::uint8 uuid[NUMBER_OF_BYTES_IN_UUID])
{
	m_HashCalculated = false;
	m_HashValue = 0;

	FromByteArray(this, uuid);
}

inline XNELO::CORE::UUID::UUID(const UUID & other)
{
	m_HashCalculated = false;
	m_HashValue = 0;

	CopyTo(&other, this);
}

inline XNELO::CORE::UUID::~UUID()
{}

inline XNELO::CORE::UUID& XNELO::CORE::UUID::operator=(const UUID & other)
{
	CopyTo(&other, this);

	return *this;
}

inline bool XNELO::CORE::UUID::operator!=(const UUID & other) const
{
	return !(*this == other);
}

inline XNELO::CORE::uint8 * XNELO::CORE::UUID::GetBytes()
{
	return m_UUID;
}

inline bool XNELO::CORE::UUID::CopyTo(const UUID * source, UUID * destination)
{
	if (source == destination || 
		source == NULL || 
		destination == NULL) return false;

	destination->m_HashCalculated = source->m_HashCalculated;
	destination->m_HashValue = source->m_HashValue;

	std::memcpy(destination->m_UUID, source->m_UUID, UUID::NUMBER_OF_BYTES_IN_UUID);

	return true;
}

inline bool XNELO::CORE::UUID::FromByteArray(UUID * uuidClass, XNELO::CORE::uint8 uuid[NUMBER_OF_BYTES_IN_UUID])
{
	if (uuid == NULL || uuidClass == NULL) return false;

	std::memcpy(uuidClass->m_UUID, uuid, UUID::NUMBER_OF_BYTES_IN_UUID);

	return true;
}

inline bool XNELO::CORE::UUID::FromConstByteArray(UUID * uuidClass, const XNELO::CORE::uint8 uuid[NUMBER_OF_BYTES_IN_UUID])
{
	if (uuid == NULL || uuidClass == NULL) return false;

	std::memcpy(uuidClass->m_UUID, uuid, UUID::NUMBER_OF_BYTES_IN_UUID);

	return true;
}

inline bool XNELO::CORE::UUID::FromString(UUID * uuidClass, std::string uuid)
{
	return FromString(uuidClass, uuid.c_str());
}

inline std::size_t XNELO::CORE::UUID::GetHash()
{
	if (!m_HashCalculated)
	{
		m_HashValue = CalculateHash();
		m_HashCalculated = true;
	}

	return m_HashValue;
}

#endif // !___XNELO__CORE__UUID_HPP__3_19_2018___

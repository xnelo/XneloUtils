/// <file> BitwiseOperators.hpp </file>Z
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> 
/// Operators for easy operating of bits
/// </summary>
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

#include "BasicTypes.hpp"

namespace XNELO
{
	namespace CORE
	{
		/**
		* Check if a bit is set.
		*
		* @param[in] toCheck The integer variable to check if a bit is set.
		* @param[in] bitNumber The position (starting from 0) of the bit to check if set.
		*
		* @example 
		* 00010000 = toCheck 
		* 4 = bitNumber  
		* true = return value
		*
		* 00010000 = toCheck
		* 2 = bitNumber
		* false = return value
		*
		* @return Returns a boolean value. If the bit is set then true is returned. Otherwise
		*			false is returned.
		*/
		template<typename Type>
		bool IsBitSetBitNumber(Type toCheck, uint8 bitNumber);

		/**
		* Check if a bit is set.
		*
		* @param[in] toCheck The integer variable to check if a bit is set.
		* @param[in] bitNumber An integer that has the bit set to check for.
		*
		* @return Returns a boolean value. If the bit is set then true is returned. Otherwise
		*			false is returned.
		*/
		template<typename Type>
		bool IsBitSet(Type toCheck, Type bitNumber);
	}//end namespace CORE
}//end namespace XNELO

template<typename Type>
inline bool XNELO::CORE::IsBitSetBitNumber(Type toCheck, uint8 bitNumber)
{
	return (toCheck & (1 << bitNumber)) != 0;
}

template<typename Type>
inline bool XNELO::CORE::IsBitSet(Type toCheck, Type bitNumber)
{
	return (toCheck & bitNumber) != 0;
}

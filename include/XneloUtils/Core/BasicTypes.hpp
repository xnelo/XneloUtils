/**
* @file BasicTypes.hpp
* @author Spencer Hoffa
*
* @copyright 2016 Spencer Hoffa
*
* Define the types.
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

#ifndef ___XNELO_CORE_BASICTYPES__HPP__11_5_2016___
#define ___XNELO_CORE_BASICTYPES__HPP__11_5_2016___

namespace XNELO
{
	namespace CORE
	{
		/**Defines an unsigned 8 bit integer type.*/
		typedef unsigned char uint8;
		/**Defines a signed 8 bit integer type.*/
		typedef signed char sint8;
		typedef char int8;

		/**Defines a BYTE as an unsigned char.*/
		typedef unsigned char BYTE;

		/**Defines an unsigned 16 bit integer type.*/
		typedef unsigned short uint16;
		/**Defines a signed 16 bit integer type.*/
		typedef signed short sint16;
		typedef short int16;

		/**Defines an unsigned 32 bit integer type.*/
		typedef unsigned int uint32;
		/**Defines a signed 32 bit integer type.*/
		typedef signed int sint32;
		typedef int int32;

		/**Defines an unsigned 64 bit integer type.*/
		typedef unsigned long long uint64;
		/**Defines a signed 64 bit integer type.*/
		typedef signed long long sint64;
		typedef long long int64;

		//defining bits
		//       32 29   25   21   17   13    9    5    1
		//        |  |    |    |    |    |    |    |    |
		//32 bits 0000 0000 0000 0000 0000 0000 0000 0000
		const uint8 bit1 = 1;				//0000 0001
		const uint8 bit2 = 2;				//0000 0010
		const uint8 bit3 = 4;				//0000 0100
		const uint8 bit4 = 8;				//0000 1000
		const uint8 bit5 = 16;				//0001 0000
		const uint8 bit6 = 32;				//0010 0000
		const uint8 bit7 = 64;				//0100 0000
		const uint8 bit8 = 128;				//1000 0000

		const uint16 bit9 = 256;			//0000 0001 0000 0000
		const uint16 bit10 = 512;			//0000 0010 0000 0000
		const uint16 bit11 = 1024;			//0000 0100 0000 0000
		const uint16 bit12 = 2048;			//0000 1000 0000 0000
		const uint16 bit13 = 4096;			//0001 0000 0000 0000
		const uint16 bit14 = 8192;			//0010 0000 0000 0000
		const uint16 bit15 = 16384;			//0100 0000 0000 0000
		const uint16 bit16 = 32768;			//1000 0000 0000 0000
	} //end namespace CORE
} //end namespace XNELO

#endif // ___XNELO_CORE_BASICTYPES__HPP__11_5_2016___

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
	} //end namespace CORE
} //end namespace XNELO

#endif // ___XNELO_CORE_BASICTYPES__HPP__11_5_2016___

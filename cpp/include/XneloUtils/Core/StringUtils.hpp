/// <file> StringUtils.hpp </file>
/// <author>Spencer Hoffa (spencer.hoffa@gmail.com)</author>
/// <summary> 
/// String modification and compare functions.
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

#ifndef ___XNELOUTILS_CORE_STRINGUTILS_HPP__2015___
#define ___XNELOUTILS_CORE_STRINGUTILS_HPP__2015___

#include "XneloUtils/Core/BasicTypes.hpp"

#include <algorithm>
#include <cctype>
#include <vector>

namespace XNELO
{
	namespace CORE
	{
		/// <summary>
		/// Convert a character into an integer type. This function assumes you passed in a valid 
		/// character [0-9] || [A-F]. If an invalid character is passed in then 0 is returned. If 
		/// error checking is desired see the overloaded version of this function.
		/// 
		/// This function is a modified version from: Niels Keurentjes and Lysann Schlegel
		/// <see cref="https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array"/>
		/// </summary>
		/// <param name="input">A single character to convert to a number.</param>
		/// <returns>An integer with the integer.</returns>
		int char2int(char input);

		/// <summary>
		/// Convert a character into an integer type. This function assumes you passed in a valid 
		/// character [0-9] || [A-F]. If an invalid character is passed in then 0 is returned. Upon
		/// completion the success argument will have true if the character was converted and false
		/// if the character wasn't converted.
		/// 
		/// This function is a modified version from: Niels Keurentjes and Lysann Schlegel
		/// <see cref="https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array"/>
		/// </summary>
		/// <param name="input">A single character to convert to a number.</param>
		/// <param name="success">
		/// A pointer to a boolean variable that will contain if the conversion was successful or 
		/// not.
		/// </param>
		/// <returns>An integer with the integer.</returns>
		int char2int(char input, bool * success);

		/// <summary>
		/// Is the input string represent a valid unsigned integer.
		/// 
		/// Thanks to: James Kanze
		/// see https://stackoverflow.com/questions/14893264/how-to-check-conversion-from-c-string-to-unsigned-int
		/// Access on 6/9/2019
		/// </summary>
		/// <param name="input">The string to check.</param>
		/// <returns>True if it can be converted to an unsigned integer. False if not.</returns>
		bool IsUnsignedInt(std::string & input);

		/// <summary>
		/// Is the input string represent a valid unsigned integer.
		/// 
		/// Thanks to: James Kanze
		/// see https://stackoverflow.com/questions/14893264/how-to-check-conversion-from-c-string-to-unsigned-int
		/// Access on 6/9/2019
		/// 
		/// Slight modification by me to handle unsigned long.
		/// </summary>
		/// <param name="input">The string to check.</param>
		/// <returns>True if it can be converted to an unsigned integer. False if not.</returns>
		bool IsUnsignedLong(std::string & input);

		/// <summary>
		/// Is the input string representing a valid unsigned short.
		/// 
		/// /// Thanks to: James Kanze
		/// see https://stackoverflow.com/questions/14893264/how-to-check-conversion-from-c-string-to-unsigned-int
		/// Access on 6/9/2019
		/// 
		/// Slight modification by me to handle unsigned long.
		/// </summary>
		/// <param name="input">The string to check.</param>
		/// <returns>True if it can be converted to an unsigned short. False if not.</returns>
		bool IsUnsignedShort(std::string & input);

		/// <summary>
		/// Split a string byt a certain character. Return a list of all the found pieces.
		/// </summary>
		/// <param name="str">The string to split.</param>
		/// <param name="delim">The character to separate on.</param>
		/// <returns>A vector of the split tokens.</returns>
		std::vector<std::string> Split(std::string& str, char delim);

		/// <summary>
		/// String Compare Case Insensitive. Compare two c-strings to see if they are the same 
		/// without case sensitivity. A == a in this function. This function checks the entire string 
		/// and only stops when the null terminating('\0') character is reached. This function is the 
		/// same as standard C's strncmp except it is case insensitive.
		/// </summary>
		///
		/// thanks to: larsmans
		/// see http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
		///
		/// <param name="a">A c-string of the first string.</param>
		/// <param name="b">A c-string for the second string.</param>
		///
		/// <returns>
		/// Returns 0 if the two strings are equivalant. <0 is returned if a and b do not match and
		/// a comes before b. >0 is returned if a and b do not match and b comes before a.
		/// </returns>
		int strcmpCI(char const *a, char const *b);

		/// <summary> 
		/// A safe fersion of <see ref="strcmpCI"/>. This will make sure the buffer is not checked 
		/// beyond the size passed into the size parameters.
		/// </summary>
		/// 
		/// <param name="a">Pointer to the first string.</param>
		/// <param name="asize">Size of buffer for string A.</param>
		/// <param name="b">Pointer to the second string.</param>
		/// <param name="bsize">Size of buffer for string b.</param>
		/// <returns>
		/// Returns 0 if the two strings are equivalant. <0 is returned if a and b do not match and
		/// a comes before b. >0 is returned if a and b do not match and b comes before a.
		/// </returns>
		int strcmpCI_s(char const *a, int asize, char const *b, int bsize);

		/// <summary>
		/// A safe version of strcmp. This will make sure the buffer is not checked beyond the size
		/// passed into the size parameters.
		/// </summary>
		/// 
		/// <param name="a">Pointer to first string.</param>
		/// <param name="asize">Size of buffer for string A</param>
		/// <param name="b">Pointer to second string.</param>
		/// <param name="bsize">Size of buffer for string b.</param>
		/// <returns>
		/// 0 if the two strings are equivalant. <0 is returned if a and b do not match and a comes
		/// before b. >0 is returned if a and b do not match and b comes before a.
		/// </returns>
		int strcmp_s(char const *a, int asize, char const *b, int bsize);

		/// <summary>
		/// Convert a string to an unsigned short value.
		/// </summary>
		/// <param name="toConvert">The string to convert.</param>
		/// <param name="outVal">A pointer to the variable to store the converted value in.</param>
		/// <returns>True if the conversion is successful. False if not.</returns>
		bool StringToUint16(std::string toConvert, XNELO::CORE::uint16 * outVal);

		/// <summary>
		/// Convert a string to an unsigned char value.
		/// </summary>
		/// <param name="toConvert">The string to convert</param>
		/// <param name="outVal">A pointer to the variable to store the converted value in.</param>
		/// <returns>True if the conversion is successful. False if not.</returns>
		bool StringToUint8(std::string toConvert, XNELO::CORE::uint8 * outVal);

		/// <summary>
		/// String Compare Case Insensitive. Compare two c-strings to see if they are the same 
		/// without case sensitivity. A == a in this function. Only num number of characters are 
		/// checked. This function is the same as standard C's strncmp except it is case insensitive.
		///
		/// thanks to: larsmans
		/// see http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
		/// </summary>
		///
		/// <param name="a"> A c-string of the first string.</param>
		/// <param name="b"> A c-string for the second string.</param>
		/// <param name="num"> The number of characters to check.</param>
		///
		/// <returns>
		/// Returns 0 if the parts of the two strings are equivalant. <0 is returned if a and b do 
		/// not match and a comes before b. >0 is returned if a and b do not match and b comes 
		/// before a.
		/// </returns>
		///
		int strncmpCI(const char *a, const char *b, int num);

		/// <summary>
		/// Returns a the string value of the bool value passed in.
		/// </summary>
		/// <param name="boolean">The bool value we want the string of.</param>
		/// <returns>Returns a string of the bool.</returns>
		const char * BoolToString(bool boolean);
	}//end namespace STRING
}//end namespace BIO

inline int XNELO::CORE::char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;

	return 0;
}

inline int XNELO::CORE::char2int(char input, bool * success)
{
	(*success) = true;

	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;

	(*success) = false;
	return 0;
}

inline bool XNELO::CORE::IsUnsignedInt(std::string & input)
{
	char * end;
	errno = 0;
	unsigned long v = strtoul(input.c_str(), &end, 10);
	return errno == 0 &&
		*end == '\0' &&
		end != input.c_str() &&
		v <= UINT_MAX;
}

inline bool XNELO::CORE::IsUnsignedLong(std::string & input)
{
	char * end;
	errno = 0;
	unsigned long v = strtoul(input.c_str(), &end, 10);
	return errno == 0 &&
		*end == '\0' &&
		end != input.c_str() &&
		v <= ULONG_MAX;
}

inline bool XNELO::CORE::IsUnsignedShort(std::string & input)
{
	char * end;
	errno = 0;
	unsigned long v = strtoul(input.c_str(), &end, 10);
	return errno == 0 &&
		*end == '\0' &&
		end != input.c_str() &&
		v <= USHRT_MAX;
}

inline std::vector<std::string> XNELO::CORE::Split(std::string& str, char delim)
{
	std::vector<std::string> retVal;
	std::string currString = "";
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == delim)
		{
			if (currString.length() > 0)
			{
				retVal.push_back(currString);
			}
			currString = "";
		}
		else 
		{
			currString.push_back(str[i]);
		}
	}

	if (currString.length() > 0)
		retVal.push_back(currString);

	return retVal;
}

inline int XNELO::CORE::strcmpCI(char const *a, char const *b)
{
	while ((a[0] != '\0') && (b[0] != '\0'))
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0)
			return d;

		a++;
		b++;
	}

	return tolower(*a) - tolower(*b);
}

inline int XNELO::CORE::strcmpCI_s(char const *a, int asize, char const *b, int bsize)
{
	int numCheck = std::min<int>(asize, bsize);

	for (int i = 0; i < numCheck; a++, b++, i++)
	{
		if (a[0] == '\0' || b[0] == '\0')
			break;
		
		int d = tolower(*a) - tolower(*b);
		if (d != 0)
			return d;
	}
	
	return tolower(*a) - tolower(*b);
}

inline int XNELO::CORE::strcmp_s(char const *a, int asize, char const *b, int bsize)
{
	// The std:min needs the type specifier in 
	// order to ompile in the windows codes.
	int numCheck = std::min<int>(asize, bsize);

	for (int i = 0; i < numCheck; a++, b++, i++)
	{
		if (a[0] == '\0' || b[0] == '\0')
			break;
		
		int d = *a - *b;
		if (d != 0)
			return d;
	}

	return *a - *b;
}

inline bool XNELO::CORE::StringToUint16(std::string toConvert, XNELO::CORE::uint16 * outVal)
{
	bool retVal = false;

	if (outVal != NULL)
	{
		char * end;
		errno = 0;
		unsigned long v = strtoul(toConvert.c_str(), &end, 10);
		retVal = errno == 0 &&
					*end == '\0' &&
					end != toConvert.c_str() &&
					v <= USHRT_MAX;

		if (retVal)
		{
			*outVal = (unsigned short)v;
		}
	}

	return retVal;
}

inline bool XNELO::CORE::StringToUint8(std::string toConvert, XNELO::CORE::uint8 * outVal)
{
	bool retVal = false;

	if (outVal != NULL)
	{
		char * end;
		errno = 0;
		unsigned long v = strtoul(toConvert.c_str(), &end, 10);
		retVal = errno == 0 &&
			*end == '\0' &&
			end != toConvert.c_str() &&
			v <= UCHAR_MAX;

		if (retVal)
		{
			*outVal = (XNELO::CORE::uint8)v;
		}
	}

	return retVal;
}

inline int XNELO::CORE::strncmpCI(const char *a, const char *b, int num)
{
	for (int i = 0; i < num; a++, b++, i++)
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a || !*b)
			return d;
	}
	return 0;
}

inline const char * XNELO::CORE::BoolToString(bool boolean)
{
	return (boolean ? "True" : "False");
}

#endif//___BIO_CORE_STRINGUTILS_HPP__2015___



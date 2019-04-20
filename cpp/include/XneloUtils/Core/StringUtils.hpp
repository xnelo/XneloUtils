/// <file> StringUtils.hpp </file>
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

#ifndef ___XNELOUTILS_CORE_STRINGUTILS_HPP__2015___
#define ___XNELOUTILS_CORE_STRINGUTILS_HPP__2015___

#include <cctype>
#include <algorithm>

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

		/**
		* String Compare Case Insensitive. Compare two c-strings to see if they are the same 
		* without case sensitivity. A == a in this function. This function checks the entire string 
		* and only stops when the null terminating('\0') character is reached. This function is the 
		* same as standard C's strncmp except it is case insensitive.
		*
		* thanks to: larsmans
		* @see http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
		*
		* @param a A c-string of the first string.
		* @param b A c-string for the second string.
		*
		* @returns Returns 0 if the two strings are equivalant. <0 is returned if a and b do not 
		*			match and a comes before b. >0 is returned if a and b do not match and b comes 
		*			before a.
		*/
		int strcmpCI(char const *a, char const *b);

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

		/**
		* String Compare Case Insensitive. Compare two c-strings to see if they are the same 
		* without case sensitivity. A == a in this function. Only num number of characters are 
		* checked. This function is the same as standard C's strncmp except it is case insensitive.
		*
		* thanks to: larsmans
		* @see http://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
		*
		* @param a A c-string of the first string.
		* @param b A c-string for the second string.
		* @param num The number of characters to check.
		*
		* @returns Returns 0 if the parts of the two strings are equivalant. <0 is returned if a 
		*			and b do not match and a comes before b. >0 is returned if a and b do not match 
		*			and b comes before a.
		*/
		int strncmpCI(const char *a, const char *b, int num);

		/**
		* Returns a the string value of the bool value passed in.
		*
		* @param boolean The bool value we want the string of.
		*
		* @returns Returns a string of the bool.
		*/
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

inline int XNELO::CORE::strcmp_s(char const *a, int asize, char const *b, int bsize)
{
	int numCheck = std::min(asize, bsize);

	for (int i = 0; i < numCheck; a++, b++, i++)
	{
		if (a[0] == '\0' || b[0] == '\0')
			break;
		
		int d = *a - *b;
		if (d != 0)
			return d;
		a++;
		b++;
	}

	return *a - *b;
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



/**
* @file StringUtils.hpp
* @author Spencer Hoffa
*
* String utilities for the XneloUtils.
*/
/*
* Copyright (c)
* 2017
* Spencer Hoffa
*
* This software is provided 'as-is', without any express or implied warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose, including commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
*    original software. If you use this software in a product, an acknowledgement in the product
*    documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
*    being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef ___XNELOUTILS_CORE_STRINGUTILS_HPP__2015___
#define ___XNELOUTILS_CORE_STRINGUTILS_HPP__2015___

#include <cctype>

namespace XNELO
{
	namespace CORE
	{
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



/// <file> ArgData.hpp </file>
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

#ifndef ___XNELO_ARGPARSE_ARGDATA_HPP__5_1_2019___
#define ___XNELO_ARGPARSE_ARGDATA_HPP__5_1_2019___

#include "ArgDef.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace XNELO
{
	namespace ARGS
	{
		/// <summary>
		/// The value of an argument after it was parsed.
		/// </summary>
		struct ArgValue
		{
			/// <summary>
			/// The name of the argument.
			/// </summary>
			std::string Name;

			/// <summary>
			/// The value.
			/// </summary>
			std::string Value;

			/// <summary>
			/// The type that value is supposed to be.
			/// </summary>
			ArgValueTypeEnum ValueType;
		};

		/// <summary>
		/// A conglomeration of all the argument data that was parsed.
		/// </summary>
		struct ArgData
		{
		public:
			/// <summary>
			/// A map of all the optional arguments.
			/// </summary>
			std::unordered_map<std::string, ArgValue> OptionalArgValues;

			/// <summary>
			/// A vector of all the positional args that were parsed.
			/// </summary>
			std::vector<ArgValue> PositionalArgValues;

			/// <summary>
			/// Does the passed in key exist in the Optional argument value data. If the key exists
			/// and contains a value then true is returned. If the key does not exist or does has
			/// a value of NULL, Then false is returned.
			/// </summary>
			/// <remarks>
			/// Use this function if you just need to know if the key exists. If you will need to 
			/// access the element then use <see cref="GetOptionalArg"/>
			/// </remarks>
			/// <param name="key">The key to look up data for.</param>
			/// <returns> True if the key exists and contains a value. If the key does NOT exist or
			/// it has a value of NULL, then false is returned.
			/// </returns>
			bool ContainsOptionalArg(std::string key);

			/// <summary>
			/// Get the optional argument value data associated with the passed in key. If the key
			/// has no value associated with it then NULL is returned. 
			/// 
			/// DO NOT DELETE THE RETURNED POINTER. This class will handle cleaning up the data.
			/// </summary>
			/// <remarks>
			/// Use this function if you will need to access the element. If you just want to know 
			/// if it is present in the data then use <see cref="ContainsOptionalArg"/>
			/// </remarks>
			/// <param name="key">The key to look up data for.</param>
			/// <returns>
			/// A pointer to the argument data. If no data is associated with the 'key' then this 
			/// returns NULL.
			/// </returns>
			ArgValue * GetOptionalArg(std::string key);
		};
	} // !ARGS
} // !XNELO

inline bool XNELO::ARGS::ArgData::ContainsOptionalArg(std::string key)
{
	return OptionalArgValues.count(key) >= 1;
}

inline XNELO::ARGS::ArgValue * XNELO::ARGS::ArgData::GetOptionalArg(std::string key)
{
	std::unordered_map<std::string, ArgValue>::iterator it;
	it = OptionalArgValues.find(key);

	if (it == OptionalArgValues.end())
		return NULL;
	else
		return &(it->second);
}

#endif // !___XNELO_ARGPARSE_ARGDATA_HPP__5_1_2019___

/// <file> ArgDef.hpp </file>
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

#ifndef ___XNELO_ARGPARSER_ARGDEF_HPP__5_1_2019___
#define ___XNELO_ARGPARSER_ARGDEF_HPP__5_1_2019___

#include <string>
#include <vector>

namespace XNELO
{
	namespace ARGS
	{
		/// <summary> 
		/// The type of argument the definition defines.
		/// </summary>
		enum ArgDefTypeEnum
		{
			UNKNOWN_ARG_TYPE = 0,
			POSITIONAL,
			OPTIONAL
		};

		/// <summary> 
		/// The base type the argument should be able to be converted to.
		/// </summary>
		enum ArgValueTypeEnum
		{
			UNKNOWN_VALUE_TYPE = 0,
			BOOLEAN,
			INTEGER,
			FLOAT,
			DOUBLE,
			LONG,
			UNSIGNED_INTEGER,
			UNSIGNED_LONG,
			STRING
		};

		class ArgDef
		{
		protected:
			std::vector<std::string> m_Choices;
			std::string m_Description;
			std::string m_Name;
			ArgValueTypeEnum m_ValueType;
		public:
			ArgDef(std::string name, ArgValueTypeEnum valType, std::string description);
			ArgDef(std::string name, ArgValueTypeEnum valType, std::string description, std::vector<std::string> choices);
			virtual ~ArgDef();
			
			virtual ArgDefTypeEnum GetArgumentType() = 0;
			std::vector<std::string> GetChoices();
			std::string GetName();
			ArgValueTypeEnum GetValueType();
		};

		class PositionalArgDef: public ArgDef
		{
		public:
			PositionalArgDef(std::string name, ArgValueTypeEnum valType, std::string description);
			PositionalArgDef(std::string name, ArgValueTypeEnum valType, std::string description, std::vector<std::string> choices);
			virtual ~PositionalArgDef();
			virtual ArgDefTypeEnum GetArgumentType();
		};

		class OptionalArgDef: public ArgDef
		{
		private:
			std::string m_LongArgument;
			char m_ShortArgument;
			bool m_ValueRequired;
		public:
			XNELO_API OptionalArgDef(char shortArg, 
										std::string longArg, 
										std::string argName, 
										ArgValueTypeEnum valType,
										std::string description,
										bool valRequired);
			XNELO_API OptionalArgDef(char shortArg, 
										std::string longArg, 
										std::string argName, 
										ArgValueTypeEnum valType,
										std::string description,
										bool valRequired,
										std::vector<std::string> choices);
			XNELO_API virtual ~OptionalArgDef();
			XNELO_API virtual ArgDefTypeEnum GetArgumentType();
			XNELO_API bool IsValueRequired();
		};
	} // !Args
} // !XNELO

//  ================================================================================================
// | ArgDef Function definition
//  ================================================================================================
inline XNELO::ARGS::ArgDef::ArgDef(std::string name, 
									ArgValueTypeEnum valType, 
									std::string description):
	m_Description(description),
	m_Name(name),
	m_ValueType(valType)
{}

inline XNELO::ARGS::ArgDef::ArgDef(std::string name, 
									ArgValueTypeEnum valType, 
									std::string description, 
									std::vector<std::string> choices):
	m_Choices(choices),
	m_Description(description),
	m_Name(name),
	m_ValueType(valType)
{}

inline XNELO::ARGS::ArgDef::~ArgDef()
{
	m_Description.clear();
	m_Name.clear();
}

inline std::vector<std::string> XNELO::ARGS::ArgDef::GetChoices()
{
	return m_Choices;
}

inline std::string XNELO::ARGS::ArgDef::GetName()
{
	return m_Name;
}

inline XNELO::ARGS::ArgValueTypeEnum XNELO::ARGS::ArgDef::GetValueType()
{
	return m_ValueType;
}

//  ================================================================================================
// | PositionalArgDef Function definition
//  ================================================================================================
inline XNELO::ARGS::PositionalArgDef::PositionalArgDef(std::string name, 
														ArgValueTypeEnum valType, 
														std::string description):
	ArgDef(name, valType, description)
{}

inline XNELO::ARGS::PositionalArgDef::PositionalArgDef(std::string name, 
														ArgValueTypeEnum valType, 
														std::string description, 
														std::vector<std::string> choices):
	ArgDef(name, valType, description, choices)
{}

inline XNELO::ARGS::PositionalArgDef::~PositionalArgDef()
{}

inline XNELO::ARGS::ArgDefTypeEnum XNELO::ARGS::PositionalArgDef::GetArgumentType()
{
	return ArgDefTypeEnum::POSITIONAL;
}

#endif //!___XNELO_ARGPARSER_ARGDEF_HPP__5_1_2019___

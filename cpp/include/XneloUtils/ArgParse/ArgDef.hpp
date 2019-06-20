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
			POSITIONAL_ARG_TYPE,
			OPTIONAL_ARG_TYPE
		};

		/// <summary> 
		/// The base type the argument should be able to be converted to.
		/// </summary>
		enum ArgValueTypeEnum
		{
			UNKNOWN_VALUE_TYPE = 0,
			NONE,
			BOOLEAN,
			INTEGER,
			FLOAT,
			DOUBLE,
			LONG,
			SHORT,
			STRING,
			UNSIGNED_INTEGER,
			UNSIGNED_LONG,
			UNSIGNED_SHORT
		};

		/// <summary>
		/// An abstract base class to hold common variables and functions between the argument 
		/// types.
		/// </summary>
		class ArgDef
		{
		protected:
			std::vector<std::string> m_Choices;
			std::string m_Description;
			std::string m_Name;
			ArgValueTypeEnum m_ValueType;
		public:
			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="name">The name of this argument.</param>
			/// <param name="valType">The type of value this argument represents.</param>
			/// <param name="description">A description to be printed in the help.</param>
			ArgDef(std::string name, ArgValueTypeEnum valType, std::string description);
			
			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="name">The name of this argument.</param>
			/// <param name="valType">The type of value this argument represents.</param>
			/// <param name="description">A description to be printed in the help.</param>
			/// <param name="choices">
			/// A vector of strings representing the choices for this argument.
			/// </param>
			ArgDef(std::string name, ArgValueTypeEnum valType, std::string description, std::vector<std::string> choices);

			/// <summary>
			/// Destructor
			/// </summary>
			virtual ~ArgDef();
			
			/// <summary>
			/// Get the type of argument this is. Optional or Positional.
			/// </summary>
			/// <returns>An ArgDefTypeEnum of the type of argument.</returns>
			virtual ArgDefTypeEnum GetArgumentType() = 0;

			/// <summary>
			/// Get the choices for this argument.
			/// </summary>
			/// <returns>A vector of strings.</returns>
			std::vector<std::string> GetChoices();

			/// <summary>
			/// Get the description for this argument's definition.
			/// </summary>
			/// <returns>A string with the definition.</returns>
			std::string GetDescription();

			/// <summary>
			/// Get the name of this argument.
			/// </summary>
			/// <returns>A string with the name.</returns>
			std::string GetName();

			/// <summary>
			/// Get the type this value represents.
			/// </summary>
			/// <returns>The type enum.</returns>
			ArgValueTypeEnum GetValueType();
		};

		/// <summary>
		/// Define a positional argument.
		/// </summary>
		class PositionalArgDef: public ArgDef
		{
		public:
			/// <summary>
			/// Constructor.
			/// </summary>
			/// <param name="name">The name of this argument.</param>
			/// <param name="valType">The type of value this argument should be.</param>
			/// <param name="description">The description of the argument.</param>
			PositionalArgDef(std::string name, ArgValueTypeEnum valType, std::string description);

			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="name">The name of this argument.</param>
			/// <param name="valType">The type of value this argument should be.</param>
			/// <param name="description">The description of the argument.</param>
			/// <param name="choices">
			/// A vector of strings with the choices this argument will accept.
			/// </param>
			PositionalArgDef(std::string name, ArgValueTypeEnum valType, std::string description, std::vector<std::string> choices);

			/// <summary>
			/// Destructor
			/// </summary>
			virtual ~PositionalArgDef();

			/// <summary>
			/// Get the type of argument this is. Optional or Positional.
			/// </summary>
			/// <returns>An ArgDefTypeEnum of the type of argument.</returns>
			virtual ArgDefTypeEnum GetArgumentType();
		};

		/// <summary>
		/// Defines an optional argument.
		/// </summary>
		class OptionalArgDef: public ArgDef
		{
		private:
			std::string m_LongArgument;
			char m_ShortArgument;
			bool m_ValueRequired;
		public:
			/// <summary>
			/// Constructor.
			/// </summary>
			/// <param name="shortArg">
			/// The character that represents the short argument value for this definition.
			/// </param>
			/// <param name="longArg">
			/// A string representing the long argument value for this definition.
			/// </param>
			/// <param name="argName">
			/// The name of this argument. The value that will be in the map of results.
			/// </param>
			/// <param name="valType">The value type that is expected as input.</param>
			/// <param name="description">The description of the argument.</param>
			/// <param name="valRequired">Is a value required.</param>
			OptionalArgDef(char shortArg, 
							std::string longArg, 
							std::string argName, 
							ArgValueTypeEnum valType,
							std::string description,
							bool valRequired);

			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="shortArg">
			/// The character that represents the short argument value for this definition.
			/// </param>
			/// <param name="longArg">
			/// A string representing the long argument value for this definition.
			/// </param>
			/// <param name="argName">
			/// The name of this argument. The value that will be in the map of results.
			/// </param>
			/// <param name="valType">The value type that is expected as input.</param>
			/// <param name="description">The description of the argument.</param>
			/// <param name="valRequired">Is a value required.</param>
			/// <param name="choices">A list of possible valid values for the argument.</param>
			OptionalArgDef(char shortArg, 
							std::string longArg, 
							std::string argName, 
							ArgValueTypeEnum valType,
							std::string description,
							bool valRequired,
							std::vector<std::string> choices);

			/// <summary>
			/// Destructor
			/// </summary>
			virtual ~OptionalArgDef();

			/// <summary>
			/// Get the type of argument this is. Optional or Positional.
			/// </summary>
			/// <returns>An ArgDefTypeEnum of the type of argument.</returns>
			virtual ArgDefTypeEnum GetArgumentType();

			/// <summary>
			/// Get the string for the long for of the arguemtn.
			/// </summary>
			/// <returns>A string.</returns>
			std::string GetLongArg();

			/// <summary>
			/// Get the character for the short form of the argument.
			/// </summary>
			/// <returns>A single charater.</returns>
			char GetShortArgChar();

			/// <summary>
			/// Is a value required to follow this argument.
			/// </summary>
			/// <returns>True if a value must follow or false if one doesn't.</returns>
			bool IsValueRequired();
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

inline std::string XNELO::ARGS::ArgDef::GetDescription()
{
	return m_Description;
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
	return ArgDefTypeEnum::POSITIONAL_ARG_TYPE;
}

//  ================================================================================================
// | OptionalArgDef Function definition
//  ================================================================================================

inline XNELO::ARGS::OptionalArgDef::OptionalArgDef(char shortArg,
													std::string longArg,
													std::string argName,
													ArgValueTypeEnum valType,
													std::string description,
													bool valRequired):
	ArgDef(argName, valType, description),
	m_LongArgument(longArg),
	m_ShortArgument(shortArg),
	m_ValueRequired(valRequired)
{}

inline XNELO::ARGS::OptionalArgDef::OptionalArgDef(char shortArg,
													std::string longArg,
													std::string argName,
													ArgValueTypeEnum valType,
													std::string description,
													bool valRequired,
													std::vector<std::string> choices):
	ArgDef(argName, valType, description, choices),
	m_LongArgument(longArg),
	m_ShortArgument(shortArg),
	m_ValueRequired(valRequired)
{}

inline XNELO::ARGS::OptionalArgDef::~OptionalArgDef()
{}

inline XNELO::ARGS::ArgDefTypeEnum XNELO::ARGS::OptionalArgDef::GetArgumentType()
{
	return ArgDefTypeEnum::OPTIONAL_ARG_TYPE;
}

inline std::string XNELO::ARGS::OptionalArgDef::GetLongArg()
{
	return m_LongArgument;
}

inline char XNELO::ARGS::OptionalArgDef::GetShortArgChar()
{
	return m_ShortArgument;
}

inline bool XNELO::ARGS::OptionalArgDef::IsValueRequired()
{
	return m_ValueRequired;
}
#endif //!___XNELO_ARGPARSER_ARGDEF_HPP__5_1_2019___

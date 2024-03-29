/// <file> ArgParse.cpp </file>
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

#include "XneloUtils/ArgParse/ArgParse.hpp"
#include "XneloUtils/Core/Errors.hpp"
#include "XneloUtils/Core/StringUtils.hpp"

#include "XneloUtils/Logging/Logging.hpp"

#include <algorithm>
#include <sstream>

namespace XNELO
{
	namespace ARGS
	{
		// Define constants
		const std::string ArgParse::HELP_KEY_STRING = "HELP";

		//  =======================================================================================
		// | Parse helper function private to this class
		//  =======================================================================================
		bool IsArgInChoice(std::string valToCheck, std::vector<std::string> choices)
		{
			bool retVal = true;
			if(choices.size() > 0)
			{
				retVal = std::find(choices.begin(), choices.end(), valToCheck) != choices.end();
			}
			return retVal;
		}

		bool IsArgOptional(std::string valToCheck)
		{
			return valToCheck.length() > 0 && valToCheck[0] == '-';
		}

		bool IsTypeCorrect(ArgValueTypeEnum expectedType, std::string valToCheck)
		{
			int valLen = (int)valToCheck.length();
			switch (expectedType)
			{
				case ArgValueTypeEnum::BOOLEAN:
					return CORE::strcmpCI_s(valToCheck.c_str(), valLen, "true", 4) == 0 ||
							CORE::strcmpCI_s(valToCheck.c_str(), valLen, "t", 1) == 0 ||
							CORE::strcmpCI_s(valToCheck.c_str(), valLen, "1", 1) == 0 ||
							CORE::strcmpCI_s(valToCheck.c_str(), valLen, "false", 5) == 0 ||
							CORE::strcmpCI_s(valToCheck.c_str(), valLen, "f", 1) == 0 ||
							CORE::strcmpCI_s(valToCheck.c_str(), valLen, "0", 1) == 0;
				case ArgValueTypeEnum::DOUBLE:
				case ArgValueTypeEnum::FLOAT:
				case ArgValueTypeEnum::INTEGER:
				case ArgValueTypeEnum::LONG:
				case ArgValueTypeEnum::SHORT:
					XNELO_LOG_CRITICAL("%i Not Implemented", expectedType);
					return false;
				case ArgValueTypeEnum::STRING: // Intentional Fallthrough
				case ArgValueTypeEnum::UNKNOWN_VALUE_TYPE:
					// These always will be true
					return true;
				case ArgValueTypeEnum::UNSIGNED_INTEGER:
					return XNELO::CORE::IsUnsignedInt(valToCheck);
				case ArgValueTypeEnum::UNSIGNED_LONG:
					return XNELO::CORE::IsUnsignedLong(valToCheck);
				case ArgValueTypeEnum::UNSIGNED_SHORT:
					return XNELO::CORE::IsUnsignedShort(valToCheck);
				default:
					return false;
			}
		}
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		ArgParse::ArgParse(std::string progName, std::vector<ArgDef*> cliArgs, bool addHelp) :
			Fallible(),
			m_ArgumentsToParse(),
			m_HelpOption(NULL),
			m_OptionalArgs(),
			m_PositionalArgs(),
			m_ProgramName(progName),
			Results()
		{
			SetError(XNELO::ERRORS::OK, "OK");
			for (int i = 0; i < cliArgs.size(); ++i)
			{
				ArgDef* tmpArg = cliArgs[i];
				if (tmpArg->GetArgumentType() == ArgDefTypeEnum::POSITIONAL_ARG_TYPE)
				{
					m_PositionalArgs.push_back(static_cast<PositionalArgDef*>(tmpArg));
				}
				else if (tmpArg->GetArgumentType() == ArgDefTypeEnum::OPTIONAL_ARG_TYPE)
				{
					m_OptionalArgs.push_back(static_cast<OptionalArgDef*>(tmpArg));
				}
				else
				{
					// Some sort of wierd error here!
					std::ostringstream oss;
					oss << "[index: " << i << "]: CLI argument type of '" 
						<< tmpArg->GetArgumentType() << " is not supported.";

					SetError(XNELO::ERRORS::ARG_PARSER_UNKNOW_ARG_DEFINITION_TYPE, oss.str());
				}
			}

			if (addHelp)
			{
				m_HelpOption = new XNELO::ARGS::OptionalArgDef('h', "help", ArgParse::HELP_KEY_STRING, XNELO::ARGS::ArgValueTypeEnum::NONE, "Displays this help menu.", false);
				m_OptionalArgs.push_back(m_HelpOption);
			}
		}

		ArgParse::~ArgParse()
		{
			m_ArgumentsToParse.clear();
			m_OptionalArgs.clear();
			m_PositionalArgs.clear();
			Results.PositionalArgValues.clear();

			if (m_HelpOption != NULL)
			{
				delete m_HelpOption;
			}
		}

		OptionalArgDef * ArgParse::FindOptionalArg(const std::string arg)
		{
			OptionalArgDef * retVal = NULL;

			if (arg.length() == 2)
			{
				if (arg[0] == '-' && arg[1] != '-')
				{
					for (int i = 0; i < m_OptionalArgs.size(); ++i)
					{
						if (m_OptionalArgs[i]->GetShortArgChar() == arg[1])
						{
							retVal = m_OptionalArgs[i];
							break;
						}
					}
				}
			}
			else if (arg.length() > 2)
			{
				if (arg[0] == '-' && arg[1] == '-')
				{
					std::string strippedLongArg = arg.substr(2);
					for (int i = 0; i < m_OptionalArgs.size(); ++i)
					{
						if (m_OptionalArgs[i]->GetLongArg() == strippedLongArg)
						{
							retVal = m_OptionalArgs[i];
							break;
						}
					}
				}
			}

			return retVal;
		}

		bool ArgParse::Parse(const int argc, const char * argv[], bool ignoreFirstArg)
		{
			Results.PositionalArgValues.clear();
			// put elements into queue
			m_ArgumentsToParse.clear();

			int i = 0;
			if (ignoreFirstArg)
				i = 1;

			for (; i < argc; ++i)
			{
				m_ArgumentsToParse.push_back(std::string(argv[i]));
			}
			// -----------------------

			int positionalCount = 0;

			while(!m_ArgumentsToParse.empty())
			{
				std::string argRaw = m_ArgumentsToParse.front();
				m_ArgumentsToParse.pop_front();

				if (IsArgOptional(argRaw))
				{
					std::string arg = "";
					std::string val = "";

					// Does this have a value in it.
					size_t equalIndex = argRaw.find('=');
					if (equalIndex != std::string::npos && 
						equalIndex + 1 < argRaw.length())
					{
						arg = argRaw.substr(0, equalIndex);
						val = argRaw.substr(equalIndex + 1);
					}
					else
					{
						arg = argRaw;
					}

					OptionalArgDef * argDef = FindOptionalArg(arg);
					if (argDef == NULL)
					{
						std::ostringstream oss;
						oss << "Optional argument '" << arg << "' is not recognized.";
						SetError(XNELO::ERRORS::ARG_PARSER_OPTIONAL_ARG_NOT_FOUND, oss.str());
						return false;
					}
					else
					{
						if (argDef->IsValueRequired())
						{
							if (val.length() <= 0)
							{
								val = m_ArgumentsToParse.front();
								m_ArgumentsToParse.pop_front();
							}

							if (!ValidateArgument(argDef, val))
							{
								// Validate argument will set the error data.
								return false;
							}
						}

						ArgValue newVal;
						newVal.Name = argDef->GetName();
						newVal.Value = val;
						newVal.ValueType = argDef->GetValueType();
						Results.OptionalArgValues[newVal.Name] = newVal;
					}
				}
				else
				{
					if (positionalCount < m_PositionalArgs.size())
					{
						PositionalArgDef* tmpPosArg = m_PositionalArgs[positionalCount];
						if (!ValidateArgument(tmpPosArg, argRaw))
						{
							// Validate argument will set the error data.
							return false;
						}
						else 
						{
							// push the argument.
							ArgValue newVal;
							newVal.Name = tmpPosArg->GetName();
							newVal.Value = argRaw;
							newVal.ValueType = tmpPosArg->GetValueType();
							Results.PositionalArgValues.push_back(newVal);
						}
					}
					else
					{
						std::ostringstream oss;
						oss << "Additional positional args. " 
							<< "Expected : " << m_PositionalArgs.size() 
							<< " received: " << positionalCount + 1;
						SetError(XNELO::ERRORS::ARG_PARSER_ADDITIONAL_POSITIONAL_ARGS, 
									oss.str());
					}
					++positionalCount;
				}
			}

			if (positionalCount < m_PositionalArgs.size())
			{
				std::ostringstream oss;
				oss << "Expected " << m_PositionalArgs.size() 
					<< " but only found " << positionalCount
					<< " positional arguments.";
				SetError(XNELO::ERRORS::ARG_PARSER_NOT_ENOUGH_POSITIONAL_ARGS, 
							oss.str());
				return false;
			}
			else
				return true;
		}

		std::string ArgParse::PrintHelp()
		{
			std::ostringstream oss;

			oss << m_ProgramName << std::endl;
			
			for (int i = 0; i < m_PositionalArgs.size(); ++i)
			{
				oss << m_PositionalArgs[i]->GetName() << m_PositionalArgs[i]->GetDescription() << std::endl;
			}

			for (int i = 0; i < m_OptionalArgs.size(); ++i)
			{
				OptionalArgDef * op = m_OptionalArgs[i];
				oss << "-" << op->GetShortArgChar() << " --" << op->GetLongArg() << " ";
				
				if (op->IsValueRequired())
				{
					oss << op->GetName() << " ";
				}
				
				oss << op->GetDescription() << std::endl;
			}

			return oss.str();
		}

		bool ArgParse::ValidateArgument(ArgDef* arg, std::string argVal)
		{
			bool retVal = true;

			if (!IsArgInChoice(argVal, arg->GetChoices()))
			{
				std::ostringstream oss;
				oss << argVal << " is not one of the choices for '" 
					<< arg->GetName() << "' choices are: (";

				bool first = true;
				std::vector<std::string> choices = arg->GetChoices();
				for (int i = 0; i < choices.size(); ++i)
				{
					if (!first) oss << ", ";
					oss << choices[i];
					first = false;
				}
				
				oss << ")";
				SetError(XNELO::ERRORS::ARG_PARSER_VALUE_NOT_IN_CHOICES,
							oss.str());
				retVal = false;
			}
			else if (!IsTypeCorrect(arg->GetValueType(), argVal))
			{
				std::ostringstream oss;
				oss << argVal << " is not of type " << arg->GetValueType() 
					<< " for '"<< arg->GetName() << "'";
				SetError(XNELO::ERRORS::ARG_PARSER_INVALID_ARGUMENT_VALUE_TYPE, 
							oss.str());
				retVal = false;
			}

			return retVal;
		}
	} // !ARGS
} // !XNELO

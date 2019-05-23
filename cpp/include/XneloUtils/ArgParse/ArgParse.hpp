/// <file> ArgParse.hpp </file>
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

#ifndef ___XNELO_ARGPARSE_ARGPARSE_HPP__4_28_2019___
#define ___XNELO_ARGPARSE_ARGPARSE_HPP__4_28_2019___

#include "../Config.hpp"
#include "../Core/Fallible.hpp"
#include "ArgDef.hpp"
#include "ArgData.hpp"

#include <deque>
#include <string>
#include <vector>

namespace XNELO
{
	namespace ARGS
	{
		class ArgParse: public XNELO::CORE::Fallible
		{
		private:
			std::deque<std::string> m_ArgumentsToParse;
			//std::vector<OptionalArgDef*> m_OptionalArgs;
			std::vector<PositionalArgDef*> m_PositionalArgs;
		public:
			/// <summary> 
			/// This public variable will hold all the parsed arguments that this class parsed. 
			/// This variable will only have valid data if the <see ref="Parse"/> function has been
			/// called and returned 'true'.
			/// </summary>
			/// <remarks>
			/// This variable will be cleared at the beginning of the call to <see ref="Parse"/>.
			/// </remarks>
			ArgData Results;

			/// <summary> 
			/// Constructor
			/// </summary>
			/// <remarks>
			/// This will not delete the memory pointed to by the values in cliArgs. That is your 
			/// responsibility.
			/// </remarks>
			/// <param name="progName">The name of the program this parser is for.</param>
			/// <param name="cliArgs">Vector of argument definitions.</param>
			XNELO_API ArgParse(std::string progName, std::vector<ArgDef*> cliArgs);

			/// <summary> 
			/// Destructor
			/// </summary>
			XNELO_API ~ArgParse();

			/// <summary> 
			/// Parse the command line arguments.
			/// </summary>
			/// 
			/// <param name="argc">Number of arguments.</param>
			/// <param name="argv">An array with the arguments.</param>
			/// <returns>
			/// True if the parsing was success. False if not. Upon success the parsed argument 
			/// values will be contained in the 'Results' variable. If a failure occures then the
			/// error number and message will be contained in GetError and GetMessage;
			/// </returns>
			XNELO_API bool Parse(const int argc, const char * argv[]);

		private:
			/// <summary> 
			/// Validate that the argument value fullfills the requirements defined in the Argument
			/// definition.
			/// </summary>
			/// 
			/// <param name="arg">The definition of the argument.</param>
			/// <param name="argVal">The value to check.</param>
			/// <returns>True if the argument is valid. False if not.</returns>
			XNELO_API bool ValidateArgument(ArgDef* arg, std::string argVal);
		};
	} // !ARGS
} // !XNELO
#endif //!___XNELO_ARGPARSE_ARGPARSE_HPP__4_28_2019___

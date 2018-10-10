#region © 2018 Spencer Hoffa
// <file>TextValidator.cs</file>
// <author> Spencer Hoffa </author>
//
// <copyright> 2018 Spencer Hoffa </copyright>
//
// <license>
// The zlib/libpng License
// Copyright(c) 2017 Spencer Hoffa
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
//		1. The origin of this software must not be misrepresented; you must not
//		claim that you wrote the original software.If you use this software in
//		a product, an acknowledgment in the product documentation would be
//		appreciated but is not required.
//
//		2. Altered source versions must be plainly marked as such, and must not
//		be misrepresented as being the original software.
//
//		3. This notice may not be removed or altered from any source
//		distribution.
//
// This liscense can also be found at : http ://opensource.org/licenses/Zlib
//</license>
#endregion

using System.Collections.Generic;
using System.Globalization;
using System.Windows.Controls;

namespace XneloUtils.WPFUtils.Validators
{
	public class TextValidator : ValidationRule
	{
		#region Fields
		private List<RuleBase> m_Rules = new List<RuleBase>();
		#endregion

		#region Constructor
		/// <summary>
		/// Constructor
		/// </summary>
		public TextValidator()
		{
			CanBeEmpty = true;
			CharactersToMatch = "A-Za-z0-9";
		}
		#endregion

		#region Properties
		#region CanBeEmpty
		/// <summary>
		/// Will the text be valid if it is empty.
		/// </summary>
		public bool CanBeEmpty { get; set; }
		#endregion

		#region CanBeWhiteSpace
		/// <summary>
		/// Will the text be valid if it is only white spaces.
		/// </summary>
		public bool CanBeWhiteSpace { get; set; }
		#endregion

		#region CharactersToMatch
		private string m_CharactersToMatch;
		/// <summary>
		/// The characters that are valid characters. This is not a regular expression. If a 
		/// character is specified then it is valid anywhere in the string. If a - is put in the 
		/// string that means anything between the ascii value of the left hand side and the ascii 
		/// value of the right hand side is valid also. if a - is a valid character then do a --. 
		/// So a string of "a-zA-Z--_+=" will mean the chars of a thru z A thru Z - _ + = will be 
		/// valid.
		/// </summary>
		public string CharactersToMatch
		{
			get
			{
				return m_CharactersToMatch;
			}

			set
			{
				if (m_CharactersToMatch != value)
				{
					m_CharactersToMatch = value;
					m_Rules.Clear();

					for (int i = 0; i < m_CharactersToMatch.Length;)
					{
						int lookAhead = i + 1;
						if (m_CharactersToMatch[i] == '-' &&
							lookAhead < m_CharactersToMatch.Length &&
							m_CharactersToMatch[lookAhead] == '-')
						{
							// single char '-'
							m_Rules.Add(new SingleCharRule('-'));
							i += 2;
						}
						else if (lookAhead < m_CharactersToMatch.Length &&
								 m_CharactersToMatch[lookAhead] == '-')
						{
							int lookAhead2 = i + 2;
							if (lookAhead2 < m_CharactersToMatch.Length)
							{
								if (m_CharactersToMatch[lookAhead2] == '-')
								{
									// single char m_CharactersMatch[i]
									// single char '-'
									m_Rules.Add(new SingleCharRule(m_CharactersToMatch[i]));
									m_Rules.Add(new SingleCharRule('-'));
									i += 3;
								}
								else
								{
									// char to char 
									// m_CharactersToMatch[i] to m_CharactersToMatch[lookAhead2]
									m_Rules.Add(new CharToCharRule(m_CharactersToMatch[i],
																   m_CharactersToMatch[lookAhead2]));
									i += 3;
								}
							}
							else
							{
								// single char m_CharactersMatch[i]
								// single char '-'
								m_Rules.Add(new SingleCharRule(m_CharactersToMatch[i]));
								m_Rules.Add(new SingleCharRule('-'));
								i += 2;
							}
						}
						else
						{
							// single char m_CharactersMatch[i]
							m_Rules.Add(new SingleCharRule(m_CharactersToMatch[i]));
							++i;
						}
					}
				}
			}
		}
		#endregion
		#endregion

		#region Methods
		public override ValidationResult Validate(object value, CultureInfo cultureInfo)
		{
			ValidationResult retVal = ValidationResult.ValidResult;
			string toValidate = value as string;

			if (toValidate == null)
			{
				retVal = new ValidationResult(false, "Passed in value cannot be null.");
			}
			else if (CanBeEmpty == false && string.IsNullOrEmpty(toValidate))
			{
				retVal = new ValidationResult(false, "Text cannot be empty.");
			}
			else if (CanBeWhiteSpace == false && string.IsNullOrWhiteSpace(toValidate))
			{
				retVal = new ValidationResult(false, "Text cannot be whitespace.");
			}
			else
			{
				foreach (char c in toValidate)
				{
					bool success = false;
					foreach (RuleBase rule in m_Rules)
					{
						if (rule.CheckRule(c))
						{
							success = true;
							break;
						}
					}

					if (!success)
					{
						retVal = new ValidationResult(false, "Invalid character '" + c + "' detected.");
						break;
					}
				}
			}

			return retVal;
		}
		#endregion

		#region Private Classes / Structures
		private abstract class RuleBase
		{
			public abstract bool CheckRule(char toCheck);
		}

		private class SingleCharRule : RuleBase
		{
			private char m_Character;

			public SingleCharRule(char character)
			{
				m_Character = character;
			}

			public override bool CheckRule(char toCheck)
			{
				return toCheck == m_Character;
			}
		}

		private class CharToCharRule: RuleBase
		{
			private int m_FirstCharacter;
			private int m_SecondCharacter;

			public CharToCharRule(char firstChar, char secondChar)
			{
				m_FirstCharacter = (int)firstChar;
				m_SecondCharacter = (int)secondChar;
			}

			public override bool CheckRule(char toCheck)
			{
				int toCheckInt = (int)toCheck;
				return (m_FirstCharacter <= toCheckInt) && (toCheckInt <= m_SecondCharacter);
			}
		}
		#endregion
	}
}
